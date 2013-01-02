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
          'alias' => 'n',
        )
      ),
      MigrateDestinationNode::getKeySchema()
    );

    // Select fields from the Drupal 6 node table.
    $query = $this
               ->d6Connection
               ->select('node', 'n');               // 't' == Text node
    $query->join('users', 'u', 'n.uid = u.uid');    // 'u' == Discussion / Text author (admin / moderator)
    $query->join('node', 'd', 'd.nid = n.nid');     // 'd' == Discussion node
    $query->join('content_field_texts', 't', 'n.nid = t.field_texts_nid');
    $query->fields(
              'n',
              array(
                'nid', 'vid', 'type', 'language', 'title', 'uid',
                'status', 'created', 'changed', 'comment', 'promote',
                'moderate', 'sticky', 'tnid', 'translate'
              )
            )
          ->fields('u', array('name'));
    $query->addField('n', 'nid', 'discussion_nid'); // Cannot add a field alias with SelectQuery::fields()
    $query->condition('n.type', 'text')
          ->condition('n.uid', 0, '>')
          ->condition('d.language', array('', 'en'), 'IN')
          ->condition('t.delta', 0)
          ->groupBy('n.nid')
          ->orderBy('n.nid')
          ->orderBy('t.delta');

    // Set source and destination.
    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationNode('bundle');

    // Basic node mapping
    $this->addFieldMapping('is_new')->defaultValue(TRUE);
    $this->addFieldMapping('nid', 'nid');
    $this->addFieldMapping('vid', 'vid');
    $this->addFieldMapping('type')->defaultValue('bundle');
    $this->addFieldMapping('language', 'language')->defaultValue(LANGUAGE_NONE);
    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('uid', 'uid');
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
    $this->addUnmigratedDestinations(array('tnid', 'log'));
  }

  public function prepareRow($row) {
    parent::prepareRow($row);

    // Fetch all texts for this discussion
    $query = $this
               ->d6Connection
               ->select('content_field_texts', 't');
    $query->join('node', 'n', 't.field_texts_nid = n.nid');
    $query->fields(
              'n',
              array(
                'nid', 'vid', 'type', 'language', 'title', 'uid',
                'status', 'created', 'changed', 'comment', 'promote',
                'moderate', 'sticky', 'tnid', 'translate'
              )
            )
          ->condition('t.nid', $row->discussion_nid)
          ->orderBy('t.delta');
    $results = $query->execute();

    foreach ($results as $record) {
      // NOTE: For the passage_collection see nurani_bundle_node_submit()
    }

    // TODO: Create the 'passage_collection' data and assign it to $row.
    $row->bundle_nid = NULL; // TEMPORARY, until this migration is ready
  }
}
