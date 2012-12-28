<?php

/**
 * Shared aspects of all migrations are stored in this parent class.
 */
abstract class NuraniMigration extends DynamicMigration {
  public function __construct() {
    parent::__construct();

    $this->d6Connection = Database::getConnection('default', 'migrate');
  }

  public function fuzzy_match($string, $options) {
    $best_match = $string;
    $best_lev   = strlen($string);

    foreach ($options as $option) {
      $lev = levenshtein(strtolower($string), strtolower($option));

      if ($lev == 0) { // Direct hit
        return $option;
      }
      else if ($lev < $best_lev) {
        $best_match = $option;
        $best_lev = $lev;
      }
    }

    return $best_match;
  }
}



/**
 * Migrates D6 users to D7.
 */
class NuraniUserMigration extends NuraniMigration {
  public function __construct() {
    parent::__construct();

    $this->dependencies = array('NuraniUserPictures');

    // Select fields from the Drupal 6 user table.
    $query = $this
               ->d6Connection
               ->select('users', 'u');
    $query->join('node', 'n', 'n.uid = u.uid');
    $query->join('content_type_profile', 'p', 'p.nid = n.nid');
    $query->fields(
              'u',
              array(
                'uid', 'name', 'pass', 'mail', 'created', 'access',
                'login', 'status', 'picture', 'init'
              )
            )
          ->fields(
              'p',
              array(
                'field_city_value', 'field_country_value', 'field_education_value',
                'field_experience_value', 'field_fluency_ar_value',
                'field_fluency_en_value', 'field_fullname_value',
                'field_position_value', 'field_publications_value',
                'field_research_value', 'field_societies_value',
                'field_title_value'
              )
            )
          ->condition('u.uid', 2, '>')
          ->condition('n.type', 'profile')
          ->orderBy('u.uid', 'ASC');

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
    $this->addFieldMapping('picture', 'picture')->sourceMigration('NuraniUserPictures');
    $this->addFieldMapping('init', 'init');
    $this->addFieldMapping('timezone')->defaultValue(NULL);
    // $this->addFieldMapping('roles', 'roles');
    $this->addFieldMapping('roles', 'roles')->defaultValue(DRUPAL_AUTHENTICATED_RID);

    // Nurani profile
    $this->addFieldMapping('field_title', 'field_title_value')->callbacks(array($this, 'fuzzy_match_title'));
    $this->addFieldMapping('field_first_name', 'field_first_name_value');
    $this->addFieldMapping('field_last_name', 'field_first_name_value');
    // $this->addFieldMapping('field_date_of_birth', '');

    // Invitation request details
    $this->addFieldMapping('field_postal_address', 'field_city_value');
    // $this->addFieldMapping('field_post_code', '');
    $this->addFieldMapping('field_country', 'field_country_value');
    // $this->addFieldMapping('field_mobile_phone', '');
    // $this->addFieldMapping('field_landline_phone', '');
    $this->addFieldMapping('field_occupation', 'field_position_value');

    // Additional details
    // $this->addFieldMapping('field_religious_tradition', '');
    $this->addFieldMapping('field_previous_experience', 'field_experience_value');
    // $this->addFieldMapping('field_how_did_you_hear_about_us', '');
    // $this->addFieldMapping('field_reasons', '');
    // $this->addFieldMapping('field_subjects_of_interest', '');
    // $this->addFieldMapping('field_social_media_usage', '');

    $this->addUnmigratedDestinations(array(
      'field_date_of_birth', 'field_post_code', 'field_mobile_phone',
      'field_landline_phone', 'field_religious_tradition',
      'field_how_did_you_hear_about_us', 'field_reasons',
      'field_subjects_of_interest', 'field_social_media_usage'
    ));
  }

  // TODO: Migrate 'moderator' and 'traslator' roles across.
  public function prepareRow($row) {
    // Migrate roles
    $query = $this
               ->d6Connection
               ->select('users_roles', 'r')
               ->fields('r', array('uid', 'rid'))
               ->condition('r.uid', $row->uid, '=');
    $results = $query->execute();
    $roles = array();
    foreach ($results as $record) {
      // Old 'moderator' role is rid 5 in the new system
      if ($record->rid == 6) {
        $roles['5'] = '5';
      }
    }
    $row->roles = $roles;

    // Split fullname into a first and last name column
    $name = explode(' ', $row->field_fullname_value);
    $row->field_first_name_value = array_shift($name);
    $row->field_last_name_value = implode(' ', $name);

    // return FALSE if you wish to skip a particular row
  }

  public function fuzzy_match_title($title) {
    return $this->fuzzy_match($title, array('Ms', 'Miss', 'Mrs', 'Mr', 'Master', 'Rev', 'Fr', 'Dr', 'Prof', 'Hon', 'Pres'));
  }
}



class NuraniUserPicturesMigration extends NuraniMigration {
  public function __construct() {
    parent::__construct();

    $this->pictures_path = 'public://' . variable_get('user_picture_path', 'pictures');

    $this->description = t('User pictures');

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'picture' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
          'description' => 'Image URI.'
        )
      ),
      MigrateDestinationFile::getKeySchema()
    );

    $query = $this
               ->d6Connection
               ->select('users', 'u')
               ->fields('u', array('picture'))
               ->isNotNull('picture')
               ->condition('picture', '', '!=');
    $query->distinct();
    $this->source = new MigrateSourceSQL($query, array(), null, array('map_joinable' => false));

    $this->destination = new MigrateDestinationFile();

    // Just map the incoming URL to the destination's 'uri'
    $this->addFieldMapping('value', 'picture')->callbacks(array($this, 'path_to_uri'));
    $this->addUnmigratedDestinations(array('fid', 'uid', 'timestamp',
      'destination_dir', 'destination_file', 'source_dir', 'preserve_files',
      'file_replace'));
    $this->removeFieldMapping('path');
    $this->removeFieldMapping('pathauto');

  }

  public function path_to_uri($path) {
    return $this->pictures_path . '/' . str_replace('sites/default/files/pictures/', '', $path);
  }
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
                 )
               ->condition('n.type', 'discussion');

    // Set source and destination.
    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationNode('discussion');

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
