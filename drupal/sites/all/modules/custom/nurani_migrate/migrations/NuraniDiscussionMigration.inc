<?php

/**
 * Migrates D6 discussion nodes to D7 discussion nodes.
 */
class NuraniDiscussionMigration extends NuraniMigration {
  public function __construct() {
    parent::__construct();

    $this->description = t('Nurani discussion nodes.');

    $this->dependencies = array('NuraniUser', 'NuraniDiscussionBundle');

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'nid' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'D6 discussion node ID.',
          'alias' => 'n',
        )
      ),
      MigrateDestinationNode::getKeySchema()
    );

    // Select fields from the Drupal 6 node table.
    $query = $this
               ->d6Connection
               ->select('node', 'n');
    $query->join('users', 'u', 'n.uid = u.uid');
    $query->join('content_type_discussion', 'cd', 'n.nid = cd.nid');
    $query->leftJoin('url_alias', 'a', "CONCAT('node/', n.nid) = a.src AND n.language = a.language");
    $query->fields(
              'n',
              array(
                'nid', 'vid', 'type', 'language', 'title', 'uid',
                'status', 'created', 'changed', 'comment', 'promote',
                'moderate', 'sticky', 'tnid', 'translate'
              )
            )
          ->fields('cd', array('field_exp_comments_value'))
          ->fields('u', array('name'))
          ->fields('a', array('dst'))
          ->condition('n.type', 'discussion')
          ->condition('n.uid', 0, '>')
          ->condition('n.language', array('', 'en'), 'IN')
          ->condition('n.language', array('', 'en'), 'IN')
          ->groupBy('n.nid')
          ->orderBy('n.nid');

    // Set source and destination.
    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationNode('discussion');

    // Basic node mapping
    $this->addFieldMapping('is_new')->defaultValue(TRUE);
    $this->addFieldMapping('nid', 'nid');
    $this->addFieldMapping('vid', 'vid');
    $this->addFieldMapping('type', 'type');
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
    $this->addFieldMapping('path', 'dst');

    // Node fields
    $this->addFieldMapping('field_content_body', 'body');

    // Fields
    $this->addFieldMapping('field_subtitle')->defaultValue('');
    $this->addFieldMapping('field_subtitle:language')->defaultValue(LANGUAGE_NONE);
    $this->addFieldMapping('field_bundle', 'bundle_nid')->sourceMigration('NuraniDiscussionBundle');
    $this->addFieldMapping('field_invitees', 'invitees_uids');
    $this->addFieldMapping('field_discussion_closing_date', 'field_exp_comments_value');

    // Unmapped destination fields
    $this->addUnmigratedDestinations(array('tnid', 'log'));
  }

  public function prepareRow($row) {
    parent::prepareRow($row);

    // Create a stack of invited uids
    $invitees = array();
    $query = $this
               ->d6Connection
               ->select('content_field_moderators', 'm');
    $query->leftJoin('content_field_translators', 't', 'm.nid = t.nid');
    $query->leftJoin('content_field_scholars', 's', 'm.nid = s.nid');
    $query->addField('m', 'field_moderators_uid');
    $query->addField('t', 'field_translators_uid');
    $query->addField('s', 'field_scholars_uid');
    $query->condition('m.nid', $row->nid);

    $result = $query->execute();
    foreach ($result as $record) {
      $invitees[$record->field_moderators_uid] = $record->field_moderators_uid;
      $invitees[$record->field_translators_uid] = $record->field_translators_uid;
      $invitees[$record->field_scholars_uid] = $record->field_scholars_uid;
    }
    $invitees = array_diff($invitees, array('', NULL));

    $row->invitees_uids = $invitees;
  }
}
