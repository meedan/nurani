<?php

/**
 * Migrates the 3 'text' nodes from D6 to a single 'bundle' node with
 * field_passage_collection in D7.
 */
class NuraniDiscussionBundleMigration extends NuraniMigration {
  public function __construct() {
    parent::__construct();

    $this->description = t('Discussion bundles');

    $this->dependencies = array('NuraniUser');

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'nid' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'D6 text (delta 0) node ID.',
          'alias' => 't',
        )
      ),
      MigrateDestinationNode::getKeySchema()
    );

    // Select fields from the Drupal 6 node table.
    $query = $this->query();
    $query->condition('cft.delta', 0);

    // Set source and destination.
    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationNode('bundle');

    // Basic node mapping
    $this->addFieldMapping('is_new')->defaultValue(TRUE);
    $this->addFieldMapping('nid', 'nid');
    $this->addFieldMapping('vid', 'vid');
    $this->addFieldMapping('type')->defaultValue('bundle');
    $this->addFieldMapping('language')->defaultValue(LANGUAGE_NONE);
    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('uid', 'uid')->defaultValue(1);
    $this->addFieldMapping('status', 'status');
    $this->addFieldMapping('created', 'created');
    $this->addFieldMapping('changed', 'changed');
    $this->addFieldMapping('comment', 'comment');
    $this->addFieldMapping('promote', 'promote');
    $this->addFieldMapping('moderate', 'moderate');
    $this->addFieldMapping('sticky', 'sticky');
    $this->addFieldMapping('translate', 'translate');

    // Node fields
    $this->addFieldMapping('field_content_body', 'body');

    // Special D7 node_save fields
    $this->addFieldMapping('pathauto_perform_alias')->defaultValue('1');

    // Fields
    $this->addFieldMapping('field_passage_collection', 'passage_collection');

    // Unmapped destination fields
    $this->addUnmigratedDestinations(array('tnid', 'log', 'revision', 'revision_uid'));
  }

  public function query() {
    $query = $this
               ->d6Connection
               ->select('node', 'd');
    $query->join('content_field_texts', 'cft', 'd.nid = cft.nid');
    $query->join('node', 't', 'cft.field_texts_nid = t.nid');
    $query->join('node_revisions', 'tr', 't.nid = tr.nid');
    $query->join('content_type_text', 'ctt', 't.nid = ctt.nid');
    $query->fields(
              't',
              array(
                'nid', 'vid', 'type', 'language', 'title', 'uid',
                'status', 'created', 'changed', 'comment', 'promote',
                'moderate', 'sticky', 'tnid', 'translate'
              )
            )
          ->fields('cft', array('delta'))
          ->fields('ctt', array('field_description_value'))
          ->fields('tr', array('body'));
    $query->addField('d', 'nid', 'discussion_nid');
    $query->addField('d', 'title', 'discussion_title');
    $query->condition('d.type', 'discussion')
          ->condition('d.language', array('', 'en'), 'IN')
          ->condition('t.type', 'text')
          ->condition('t.language', array('', 'en'), 'IN')
          ->groupBy('t.vid')
          ->orderBy('d.nid')
          ->orderBy('cft.delta');
    return $query;
  }

  public function prepareRow($row) {
    parent::prepareRow($row);

    // Ensure any Anonymous records are owned by admin
    $row->uid = $row->uid > 0 ? $row->uid : 1;

    // Fetch all texts for this discussion, not just the delta == 0 texts
    $query = $this->query();
    $query->condition('d.nid', $row->discussion_nid);
    $results = $query->execute();

    $row->passages = array();
    foreach ($results as $record) {
      $row->passages[$record->delta] = array(
        'osisIDWork'           => $this->textToBundlesMap[$record->nid]['osisIDWork'],
        'osisID'               => $this->textToBundlesMap[$record->nid]['osisID'],
        'notes' => $record->field_description_value,
        'visible'              => '1', // FIXME: For some reason field_collection is failing to set passages as visible.
      );
    }
  }

  /**
   * Attaches the discussion helper object to the bundle node. This is required
   * by nurani_bundle_node_presave() to properly set the bundle title.
   *
   * This is a critical step because 'bundle' nodes are imported before
   * 'discussion' nodes, hence nurani_bundle_node_load() will fail to attach
   * its data.
   */
  public function prepare($node, $row) {
    $node->revision = FALSE;
    $node->discussion = (object) array(
      'nid'   => $row->discussion_nid,
      'title' => $row->discussion_title,
    );
  }

  /**
   * Create / update field_passage_collection.
   * Code based on nurani_bundle_node_submit()
   */
  public function complete($node, $row) {
    $langcode   = $node->language;

    $passages_collection = $node->field_passage_collection;

    $node->revision = FALSE;

    foreach ($row->passages as $pc_delta => $pc_value) {
      if (!isset($passages_collection[$langcode][$pc_delta])) {
        $item = array(
          'field_name' => 'field_passage_collection',
        );
        $entity = entity_create('field_collection_item', $item);
        $entity->setHostEntity('node', $node);
        $entity->save();

        $passages_collection[$langcode][$pc_delta]['value'] = entity_id('field_collection_item', $entity);
      }

      $entity = entity_load_single('field_collection_item', $passages_collection[$langcode][$pc_delta]['value']);

      // HACK: Reset the host entity to force $entity->save() to node_save
      //       OUR $node rather than one it node_load()'s itself. This is
      //       critical because our node contains the $node->discussion data
      //       set in $this->prepare().
      // $entity->setHostEntity('node', $node); // NOTE: Not needed with field_collection-7.x-1.0-beta4

      $entity->field_passage[$langcode][0]['osisIDWork']         = $pc_value['osisIDWork'];
      $entity->field_passage[$langcode][0]['osisID']             = $pc_value['osisID'];
      $entity->field_notes[$langcode][0]['value'] = $pc_value['notes'];
      $entity->field_visible[$langcode][0]['value']              = $pc_value['visible'];
      $entity->save(); // Important to save the host entity here too.
    }
  }

  // Statically generated map of D6 Text node ID to OSIS information.
  // See migrations/README.md for more information.
  public $textToBundlesMap = array(
    67 => array(
      'osisIDWork' => 'njps_en',
      'osisID'     => 'Deut.4.5-8',
    ),
    69 => array(
      'osisIDWork' => 'nrsv_en',
      'osisID'     => '1Chr.1.17-29',
    ),
    71 => array(
      'osisIDWork' => 'quran_ahmedali_en',
      'osisID'     => 'Quran.2.8-18',
    ),
    73 => array(
      'osisIDWork' => 'nrsv_en',
      'osisID'     => 'Gen.1.1-4',
    ),
    75 => array(
      'osisIDWork' => 'nrsv_en',
      'osisID'     => 'John.1.1-9',
    ),
    77 => array(
      'osisIDWork' => 'quran_ahmedali_en',
      'osisID'     => 'Quran.24.35',
    ),
    79 => array(
      'osisIDWork' => 'njps_en',
      'osisID'     => 'Gen.18.1-16',
    ),
    81 => array(
      'osisIDWork' => 'nrsv_en',
      'osisID'     => 'Heb.11.3-13',
    ),
    83 => array(
      'osisIDWork' => 'quran_ahmedali_en',
      'osisID'     => 'Quran.15.51-56',
    ),
    85 => array(
      'osisIDWork' => 'quran_ahmedali_en',
      'osisID'     => 'Quran.31.12-19',
    ),
    87 => array(
      'osisIDWork' => 'njps_en',
      'osisID'     => 'Ps.123.1-4',
    ),
    89 => array(
      'osisIDWork' => 'nrsv_en',
      'osisID'     => 'Rev.22.1-7;Rev.22.16-20',
    ),
    91 => array(
      'osisIDWork' => 'quran_ahmedali_en',
      'osisID'     => 'Quran.12.11-13;Quran.12.80-87',
    ),
    93 => array(
      'osisIDWork' => 'njps_en',
      'osisID'     => 'Job.38.1-8',
    ),
    95 => array(
      'osisIDWork' => 'nrsv_en',
      'osisID'     => 'Rom.1.16-32',
    ),
    211 => array(
      'osisIDWork' => 'njps_en',
      'osisID'     => 'Deut.6.4-9',
    ),
    217 => array(
      'osisIDWork' => 'nrsv_en',
      'osisID'     => 'Eph.4.11-16',
    ),
    221 => array(
      'osisIDWork' => 'quran_ahmedali_en',
      'osisID'     => 'Quran.4.59',
    ),
    1036 => array(
      'osisIDWork' => 'nrsv_en',
      'osisID'     => 'Luke.8.40-56',
    ),
    1048 => array(
      'osisIDWork' => 'nrsv_en',
      'osisID'     => 'Mark.11.27-33',
    ),
    1065 => array(
      'osisIDWork' => 'quran_ahmedali_en',
      'osisID'     => 'Quran.2.247-249',
    ),
    1079 => array(
      'osisIDWork' => 'njps_en',
      'osisID'     => 'Josh.1.10-18',
    ),
    1093 => array(
      'osisIDWork' => 'nrsv_en',
      'osisID'     => 'Acts.19.23-29',
    ),
    1091 => array(
      'osisIDWork' => 'quran_ahmedali_en',
      'osisID'     => 'Quran.58.7-10',
    ),
    1089 => array(
      'osisIDWork' => 'njps_en',
      'osisID'     => 'Num.16.1-6',
    ),
    1123 => array(
      'osisIDWork' => 'njps_en',
      'osisID'     => 'Gen.1.1-5',
    ),
    1251 => array(
      'osisIDWork' => 'nrsv_en',
      'osisID'     => 'John.1.1-5',
    ),
    1425 => array(
      'osisIDWork' => 'quran_sahih_en',
      'osisID'     => 'Quran.41.9-12',
    ),
    1675 => array(
      'osisIDWork' => 'njps_en',
      'osisID'     => 'Exod.3.1-8',
    ),
    1765 => array(
      'osisIDWork' => 'quran_ahmedali_en',
      'osisID'     => 'Quran.20.9-23',
    ),
    1827 => array(
      'osisIDWork' => 'nrsv_en',
      'osisID'     => 'Acts.9.1-9',
    ),
    2047 => array(
      'osisIDWork' => 'njps_en',
      'osisID'     => 'Gen.38.6-26',
    ),
    2199 => array(
      'osisIDWork' => 'nrsv_en',
      'osisID'     => 'John.8.2-11',
    ),
    2309 => array(
      'osisIDWork' => 'quran_ahmedali_en',
      'osisID'     => 'Quran.3.35-43',
    ),
    2053 => array(
      'osisIDWork' => 'njps_en',
      'osisID'     => 'Num.20.1-12',
    ),
    2205 => array(
      'osisIDWork' => 'nrsv_en',
      'osisID'     => 'Luke.8.22-26',
    ),
    2307 => array(
      'osisIDWork' => 'quran_hilali_en',
      'osisID'     => 'Quran.11.40-44',
    ),
    2061 => array(
      'osisIDWork' => 'njps_en',
      'osisID'     => 'Josh.1.10-18',
    ),
    2331 => array(
      'osisIDWork' => 'quran_ahmedali_en',
      'osisID'     => 'Quran.20.9-23',
    ),
    2441 => array(
      'osisIDWork' => 'njps_en',
      'osisID'     => 'Exod.3.1-8',
    ),
    2565 => array(
      'osisIDWork' => 'nrsv_en',
      'osisID'     => 'Acts.9.1-9',
    ),
    2601 => array(
      'osisIDWork' => 'quran_hilali_en',
      'osisID'     => 'Quran.11.40-44',
    ),
    2659 => array(
      'osisIDWork' => 'njps_en',
      'osisID'     => 'Num.20.1-13',
    ),
    2679 => array(
      'osisIDWork' => 'njps_en',
      'osisID'     => 'Gen.7.1-5',
    ),
    2771 => array(
      'osisIDWork' => 'quran_ahmedali_en',
      'osisID'     => 'Quran.11.25-32',
    ),
    2801 => array(
      'osisIDWork' => 'nrsv_en',
      'osisID'     => 'Matt.24.35-42',
    ),
    2683 => array(
      'osisIDWork' => 'njps_en',
      'osisID'     => 'Gen.1.26-28',
    ),
    2781 => array(
      'osisIDWork' => 'quran_yusufali_en',
      'osisID'     => 'Quran.39.6',
    ),
    2811 => array(
      'osisIDWork' => 'nrsv_en',
      'osisID'     => '1Cor.15.47-49',
    ),
    2867 => array(
      'osisIDWork' => 'quran_ahmedali_en',
      'osisID'     => 'Quran.31.12-19',
    ),
    2947 => array(
      'osisIDWork' => 'njps_en',
      'osisID'     => 'Deut.4.5-9',
    ),
    3025 => array(
      'osisIDWork' => 'nrsv_en',
      'osisID'     => 'Jas.3.13-18',
    ),
    2873 => array(
      'osisIDWork' => 'quran_ahmedali_en',
      'osisID'     => 'Quran.31.12-19',
    ),
    2951 => array(
      'osisIDWork' => 'njps_en',
      'osisID'     => 'Deut.4.5-9',
    ),
    3031 => array(
      'osisIDWork' => 'nrsv_en',
      'osisID'     => 'Jas.3.13-18',
    ),
  );
}
