<?php

/**
 * Shared aspects of all migrations are stored in this parent class.
 */
abstract class NuraniMigration extends DynamicMigration {
  public function __construct() {
    parent::__construct();

    $this->d6Connection = Database::getConnection('default', 'migrate');
  }
}



/**
 * Migrates D6 users to D7.
 */
class NuraniUserMigration extends NuraniMigration {
  public function __construct() {
    parent::__construct();

    // Select fields from the Drupal 6 user table.
    $query = $this
               ->d6Connection
               ->select('users', 'u')
               ->fields(
                   'u',
                   array(
                     'uid', 'name', 'pass', 'mail', 'created', 'access',
                     'login', 'status', 'picture', 'init'
                   )
                 );

    // This is supposed to get roles not sure how.
    $source_fields = array(
      'uid' => t('User ID'),
      'roles' => t('The set of roles assigned to a user.'),
    );

    // Set source and destination.
    $this->source = new MigrateSourceSQL($query, $source_fields);
    $this->destination = new MigrateDestinationUser(array('md5_passwords' => TRUE));

    // Set up database maping.
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'uid' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'D6 Unique User ID',
          'alias' => 'u',
        )
      ),
      MigrateDestinationUser::getKeySchema()
    );

    // Add simple field mappings
    $this->addFieldMapping('name', 'name')->dedupe('users', 'name');
    $this->addFieldMapping('pass', 'pass');
    $this->addFieldMapping('mail', 'mail')->dedupe('users', 'mail');
    $this->addFieldMapping('language')->defaultValue('');
    $this->addFieldMapping('theme')->defaultValue('');
    $this->addFieldMapping('signature')->defaultValue('');
    $this->addFieldMapping('signature_format')->defaultValue('filtered_html');
    $this->addFieldMapping('created', 'created');
    $this->addFieldMapping('access', 'access');
    $this->addFieldMapping('login', 'login');
    $this->addFieldMapping('status', 'status');
    $this->addFieldMapping('picture')->defaultValue(0);
    $this->addFieldMapping('init', 'init');
    $this->addFieldMapping('timezone')->defaultValue(NULL);
    // $this->addFieldMapping('roles', 'roles');
    $this->addFieldMapping('roles', 'roles')->defaultValue(DRUPAL_AUTHENTICATED_RID);
  }

  // // Set up Roles.
  // public function prepareRow($current_row) {
  //   // Additional query on the roles table.
  //   $source_id = $current_row->uid;
  //   $query = db_select('sourcetable.users_roles', 'r')
  //     ->fields('r', array('uid', 'rid'))
  //     ->condition('r.uid', $source_id, '=');
  //   $results = $query->execute();

  //   // Add the Authenticated role for everyone.
  //   $roles = array('2' => '2');
  //   foreach ($results as $row) {

  //     // Subscriber role should be transfered.
  //     if ($row->rid == 6) {
  //       $roles['5'] = '5';
  //     }
  //   }
  //   $current_row->roles = $roles;
  //   return TRUE;
  //   // return FALSE if you wish to skip a particular row
  // }
}



/**
 * Migrates D6 discussion nodes to D7 discussion nodes.
 */
class NuraniDiscussionMigration extends NuraniMigration {
  public function __construct() {
    parent::__construct();

    $this->description = t('Nurani discussion nodes.');

    $this->dependencies = array('NuraniUser');

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'nid' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'Discussion node ID.',
        )
      ),
      MigrateDestinationNode::getKeySchema()
    );

    // Select fields from the Drupal 6 node table.
    $query = $this
               ->d6Connection
               ->select('node', 'n')
               ->fields(
                   'n',
                   array(
                     'nid', 'vid', 'type', 'language', 'title', 'uid',
                     'status', 'created', 'changed', 'comment', 'promote',
                     'moderate', 'sticky', 'tnid', 'translate'
                   )
                 );

    // Set source and destination.
    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationNode();

    // // Mapped fields
    // $this->addFieldMapping('title', 'name')
    //      ->description(t('Mapping beer name in source to node title'));
    // $this->addFieldMapping('sticky')
    //      ->description(t('Should we default this to 0 or 1?'))
    //      ->issueGroup(t('Client questions'))
    //      ->issueNumber(765736)
    //      ->issuePriority(MigrateFieldMapping::ISSUE_PRIORITY_LOW);

    // // To maintain node identities between the old and new systems (i.e., have
    // // the same unique IDs), map the ID column from the old system to nid and
    // // set is_new to TRUE. This works only if we're importing into a system that
    // // has no existing nodes with the nids being imported.
    // $this->addFieldMapping('nid', 'bid')
    //      ->description(t('Preserve old beer ID as nid in Drupal'));
    // $this->addFieldMapping('is_new')
    //      ->defaultValue(TRUE);

    // // References to related objects (such as the author of the content) are
    // // most likely going to be identifiers from the source data, not Drupal
    // // identifiers (such as uids). You can use the mapping from the relevant
    // // migration to translate from the old ID to the Drupal identifier.
    // // Note that we also provide a default value of 1 - if the lookup fails to
    // // find a corresponding uid for the aid, the owner will be the administrative
    // // account.
    // $this->addFieldMapping('uid', 'aid')
    //      ->sourceMigration('NuraniUser')
    //      ->defaultValue(1);

    // // This is a multi-value text field
    // $this->addFieldMapping('field_migrate_example_country', 'countries')
    //      ->separator('|');
    // // These are related terms, which by default will be looked up by name
    // $this->addFieldMapping('migrate_example_beer_styles', 'terms')
    //      ->separator(',');

    // // Some fields may have subfields such as text formats or summaries
    // // (equivalent to teasers in previous Drupal versions).
    // // These can be individually mapped as we see here.
    // $this->addFieldMapping('body', 'body');
    // $this->addFieldMapping('body:summary', 'excerpt');

    // // Copy an image file, write DB record to files table, and save in Field storage.
    // // We map the filename (relative to the source_dir below) to the field itself.
    // $this->addFieldMapping('field_migrate_example_image', 'image');
    // // Here we specify the directory containing the source files.
    // $this->addFieldMapping('field_migrate_example_image:source_dir')
    //      ->defaultValue(drupal_get_path('module', 'migrate_example'));
    // // And we map the alt and title values in the database to those on the image.
    // $this->addFieldMapping('field_migrate_example_image:alt', 'image_alt');
    // $this->addFieldMapping('field_migrate_example_image:title', 'image_title');

    // // No description for images, only alt and title
    // $this->addUnmigratedSources(array('image_description'));

    // // Unmapped destination fields
    // $this->addUnmigratedDestinations(array('created', 'changed', 'status',
    //   'promote', 'revision', 'language', 'revision_uid', 'log', 'tnid',
    //   'body:format', 'body:language', 'migrate_example_beer_styles:source_type',
    //   'migrate_example_beer_styles:create_term', 'field_migrate_example_image:destination_dir',
    //   'field_migrate_example_image:language', 'field_migrate_example_image:file_replace',
    //   'field_migrate_example_image:preserve_files', 'field_migrate_example_country:language', 'comment',
    //   'field_migrate_example_image:file_class', 'field_migrate_example_image:destination_file'));

    // if (module_exists('path')) {
    //   $this->addFieldMapping('path')
    //        ->issueGroup(t('DNM'));
    //   if (module_exists('pathauto')) {
    //     $this->addFieldMapping('pathauto')
    //          ->issueGroup(t('DNM'));
    //   }
    // }
    // if (module_exists('statistics')) {
    //   $this->addUnmigratedDestinations(array('totalcount', 'daycount', 'timestamp'));
    // }
  }
}




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
    $query = $this
               ->d6Connection
               ->select('comments', 'c')
               ->fields(
                   'c',
                   array(
                     'cid', 'pid', 'nid', 'uid', 'subject', 'comment',
                     'hostname', 'timestamp', 'status', 'format', 'thread',
                     'name', 'mail', 'homepage'
                   )
                 );

    // Set source and destination.
    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationComment();


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
