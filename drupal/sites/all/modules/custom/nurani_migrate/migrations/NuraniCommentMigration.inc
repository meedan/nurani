<?php

/**
 * Import items from the migrate_example_beer_comment table and make them into
 * Drupal comment objects.
 */
class NuraniCommentMigration extends NuraniMigration {
  public function __construct() {
    parent::__construct();

    $this->description = 'Comments about beers';

    $this->dependencies = array('NuraniUser', 'NuraniDiscussion');

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'cid' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'Discussion comment ID.',
        )
      ),
      MigrateDestinationComment::getKeySchema()
    );

    // Select fields from the Drupal 6 comments table.
    // Select fields from the Drupal 6 node table.
    $query = $this
               ->d6Connection
               ->select('node_comments', 'nc');
    $query->join('node', 'n', 'n.nid = nc.cid');
    $query->fields(
                   'nc',
                   array(
                     'cid', 'pid', 'nid', 'hostname', 'thread', 'name', 'uid',
                     'mail', 'homepage'
                   )
                 )
               ->condition('n.type', 'response');

    // Set source and destination.
    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationComment('discussion');


    // // Mapped fields
    // $this->addSimpleMappings(array('name', 'subject', 'mail'));
    // $this->addFieldMapping('status')
    //      ->defaultValue(COMMENT_PUBLISHED);

    // // We preserved bid => nid ids during NuraniNode import so simple mapping suffices.
    // $this->addFieldMapping('nid', 'bid');

    // $this->addFieldMapping('uid', 'aid')
    //      ->sourceMigration('NuraniUser')
    //      ->defaultValue(0);

    // $this->addFieldMapping('pid', 'cid_parent')
    //      ->sourceMigration('NuraniComment')
    //      ->description('Parent comment.');

    // $this->addFieldMapping('comment_body', 'body');

    // // No unmapped source fields

    // // Unmapped destination fields
    // $this->addUnmigratedDestinations(array('hostname', 'created', 'changed',
    //   'thread', 'homepage', 'language', 'comment_body:format', 'comment_body:language'));
  }
}
