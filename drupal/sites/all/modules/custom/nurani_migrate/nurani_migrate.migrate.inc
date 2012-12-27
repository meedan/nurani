<?php

/**
 * Implements hook_migrate_api().
 */
function nurani_migrate_migrate_api() {
  $api = array(
    'api' => 2,
    'migrations' => array(
      'NuraniUser' => array('class_name' => 'NuraniUserMigration'),
      'NuraniDiscussion' => array('class_name' => 'NuraniDiscussionMigration'),
      'NuraniComment' => array('class_name' => 'NuraniCommentMigration'),
    ),
  );
  return $api;
}
