<?php

/**
 * Import items from the migrate_example_beer_comment table and make them into
 * Drupal comment objects.
 */
class NuraniCommentMigration extends NuraniMigration {
  public function __construct() {
    parent::__construct();

    $this->description = 'Comments on discussions';

    $this->dependencies = array('NuraniUser', 'NuraniDiscussion');

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'cid' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'Discussion comment ID.',
          'alias' => 'nc',
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
    $query->join('node_revisions', 'nr', 'n.nid = nr.nid');
    $query->fields(
                    'nc',
                    array(
                      'cid', 'pid', 'nid', 'hostname', 'thread', 'name', 'uid',
                      'mail', 'homepage'
                    )
                  )
          ->fields(
                    'n',
                    array(
                      'title', 'created', 'changed', 'status',
                    )
                  )
          ->fields('nr', array('body'))
          ->condition('n.type', 'response')
          ->groupBy('nc.cid')
          ->orderBy('nc.pid', 'ASC');

    // Set source and destination.
    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationComment('comment_node_discussion');

    // Mapped fields
    $this->addFieldMapping('is_new')->defaultValue(TRUE);
    // $this->addFieldMapping('pid', 'pid')
    //      ->sourceMigration('NuraniComment')
    //      ->description('Parent comment.')
    //      ->defaultValue(0);
    $this->addFieldMapping('nid', 'nid');
    $this->addFieldMapping('uid', 'uid')
         ->sourceMigration('NuraniUser')
         ->defaultValue(0);
    $this->addFieldMapping('subject', 'title');
    $this->addFieldMapping('comment_body', 'body')->callbacks(array($this, 'clean_comment_body'));
    $this->addFieldMapping('comment_body:format', 'filtered_html');
    $this->addFieldMapping('hostname', 'hostname');
    $this->addFieldMapping('created', 'created');
    $this->addFieldMapping('changed', 'changed');
    $this->addFieldMapping('status', 'status')
         ->defaultValue(COMMENT_PUBLISHED);
    // $this->addFieldMapping('thread', 'thread');
    $this->addFieldMapping('name', 'name');
    $this->addFieldMapping('mail', 'mail');
    $this->addFieldMapping('homepage', 'homepage');
    $this->addFieldMapping('language')->defaultValue(LANGUAGE_NONE);

    // Unmapped destination fields
    $this->addUnmigratedDestinations(array('cid', 'pid', 'thread', 'comment_body:format', 'comment_body:language'));
  }

  public function clean_comment_body($body) {
    $body = preg_replace('@</p>@', "</p>\n\n", $body);
    $body = strip_tags($body);
    $body = str_replace('&nbsp;', ' ', $body);
    $body = html_entity_decode($body, ENT_QUOTES, 'UTF-8');
    return $body;
  }
}
