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
          ->groupBy('t.nid')
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
        'moderator_s_thoughts' => $record->field_description_value,
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
      $entity->setHostEntity('node', $node);

      $entity->field_passage[$langcode][0]['osisIDWork']         = $pc_value['osisIDWork'];
      $entity->field_passage[$langcode][0]['osisID']             = $pc_value['osisID'];
      $entity->field_moderator_s_thoughts[$langcode][0]['value'] = $pc_value['moderator_s_thoughts'];
      $entity->field_visible[$langcode][0]['value']              = $pc_value['visible'];
      $entity->save(); // Important to save the host entity here too.
    }
  }

  // Statically generated map of D6 Text node ID to OSIS information.
  // This was generated by hand starting from this SQL query:
  //
  //     SELECT d.nid AS discussion_nid, d.title AS discussion_title,
  //            cft.delta, t.nid, t.title,
  //            tr.body,
  //            ctt.field_description_value AS description
  //     FROM node d
  //     INNER JOIN content_field_texts cft ON d.nid = cft.nid
  //     INNER JOIN node t ON cft.field_texts_nid = t.nid
  //     INNER JOIN node_revisions tr ON t.nid = tr.nid
  //     INNER JOIN content_type_text ctt ON t.nid = ctt.nid
  //     WHERE (d.TYPE = 'discussion')
  //       AND (d.language IN ('', 'en'))
  //       AND (t.TYPE = 'text')
  //       AND (t.language IN ('', 'en'))
  //     GROUP BY t.nid
  //     ORDER BY d.nid ASC, cft.delta ASC
  //
  public $textToBundlesMap = array(
    67 => array(
      'osisIDWork' => '', // TODO: Find the OSIS work for this passage.
      'osisID' => 'Deut.4.5-8',
    ),
    69 => array(
      'osisIDWork' => '', // TODO: Find the OSIS work for this passage.
      'osisID' => '1Chr.1.17-29',
    ),
    71 => array(
      'osisIDWork' => '', // TODO: Find the OSIS work for this passage.
      'osisID' => 'quran.2.8-18',
    ),
    73 => array(
      'osisIDWork' => 'nrsv_en',
      'osisID' => 'Gen.1.1-4',
    ),
    75 => array(
      'osisIDWork' => 'nrsv_en',
      'osisID' => 'John.1.1-9',
    ),
    77 => array(
      'osisIDWork' => '', // TODO: Find the OSIS work for this passage.
      'osisID' => 'quran.24.35',
    ),
    79 => array(
      'osisIDWork' => '', // TODO: Find the OSIS work for this passage.
      'osisID' => 'Gen.18.1-16',
    ),
    81 => array(
      'osisIDWork' => '', // TODO: Find the OSIS work for this passage.
      'osisID' => 'Heb.11.3-13',
    ),
    83 => array(
      'osisIDWork' => '', // TODO: Find the OSIS work for this passage.
      'osisID' => 'quran.15.51-56',
    ),
    85 => array(
      'osisIDWork' => '', // TODO: Find the OSIS work for this passage.
      'osisID' => 'quran.31.12-19',
    ),
    87 => array(
      'osisIDWork' => '', // TODO: Find the OSIS work for this passage.
      'osisID' => 'Ps.123.1-4',
    ),
    89 => array(
      'osisIDWork' => '', // TODO: Find the OSIS work for this passage.
      'osisID' => 'Rev.22.1-7;Rev.22.16-20',
    ),
    91 => array(
      'osisIDWork' => '', // TODO: Find the OSIS work for this passage.
      'osisID' => 'quran.12.11-13;quran.12.80-87',
    ),
    93 => array(
      'osisIDWork' => '', // TODO: Find the OSIS work for this passage.
      'osisID' => 'Job.38.1-8',
    ),
    95 => array(
      'osisIDWork' => '', // TODO: Find the OSIS work for this passage.
      'osisID' => 'Rom.1.16-32',
    ),
    211 => array(
      'osisIDWork' => '', // TODO: Find the OSIS work for this passage.
      'osisID' => 'Deut.6.4-9',
    ),
    217 => array(
      'osisIDWork' => '', // TODO: Find the OSIS work for this passage.
      'osisID' => 'Eph.4.11-16',
    ),
    221 => array(
      'osisIDWork' => '', // TODO: Find the OSIS work for this passage.
      'osisID' => 'quran.4.59',
    ),
    1036 => array(
      'osisIDWork' => 'nrsv_en',
      'osisID' => 'Luke.8.40-56',
    ),
    1048 => array(
      'osisIDWork' => 'nrsv_en',
      'osisID' => 'Mark.11.27-33',
    ),
    1065 => array(
      'osisIDWork' => 'quran_ahmedali_en',
      'osisID' => 'quran.2.247-249',
    ),
    1079 => array(
      'osisIDWork' => '', // TODO: Find the OSIS work for this passage.
      'osisID' => 'Josh.1.10-18',
    ),
    1093 => array(
      'osisIDWork' => 'nrsv_en',
      'osisID' => 'Acts.19.23-29',
    ),
    1091 => array(
      'osisIDWork' => 'quran_ahmedali_en',
      'osisID' => 'quran.58.7-10',
    ),
    1089 => array(
      'osisIDWork' => 'jps_2000_en',
      'osisID' => 'Num.16.1-6',
    ),
    1251 => array(
      'osisIDWork' => 'jps_1985_en',
      'osisID' => 'Gen.1.1-5',
    ),
    1123 => array(
      'osisIDWork' => 'nrsv_en',
      'osisID' => 'John.1.1-5',
    ),
    1425 => array(
      'osisIDWork' => 'quran_sahih_en',
      'osisID' => 'quran.41.9-12',
    ),
    1675 => array(
      'osisIDWork' => 'jps_1985_en',
      'osisID' => 'Exod.3.1-8',
    ),
    1765 => array(
      'osisIDWork' => 'quran_ahmedali_en',
      'osisID' => 'quran.20.9-23',
    ),
    1827 => array(
      'osisIDWork' => 'nrsv_en',
      'osisID' => 'Acts.9.1-9',
    ),
  );
}
