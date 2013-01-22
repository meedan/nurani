<?php

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
          ->condition('u.uid', 0, '>')
          ->condition('n.type', 'profile')
          ->groupBy('u.uid')
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
    $this->addFieldMapping('is_new')->defaultValue(TRUE);
    $this->addFieldMapping('uid', 'uid');
    $this->addFieldMapping('name', 'name')->dedupe('users', 'name');
    $this->addFieldMapping('pass', 'pass');
    $this->addFieldMapping('mail', 'mail')->dedupe('users', 'mail');
    $this->addFieldMapping('language');
    $this->addFieldMapping('theme');
    $this->addFieldMapping('signature');
    $this->addFieldMapping('signature_format')->defaultValue('filtered_html');
    $this->addFieldMapping('created', 'created');
    $this->addFieldMapping('access', 'access');
    $this->addFieldMapping('login', 'login');
    $this->addFieldMapping('status', 'status');
    $this->addFieldMapping('picture', 'picture')->sourceMigration('NuraniUserPictures');
    $this->addFieldMapping('init', 'init');
    $this->addFieldMapping('timezone');
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
      'role_names', 'data',
      'field_date_of_birth', 'field_post_code', 'field_mobile_phone',
      'field_landline_phone', 'field_religious_tradition',
      'field_how_did_you_hear_about_us', 'field_reasons',
      'field_subjects_of_interest', 'field_social_media_usage',
      'path',
    ));
  }

  public function prepareRow($row) {
    parent::prepareRow($row);

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
      // TODO: Migrate 'traslator' roles across.
    }
    $row->roles = $roles;

    // Split fullname into a first and last name column
    $name = explode(' ', $row->field_fullname_value);
    $row->field_first_name_value = array_shift($name);
    $row->field_last_name_value = implode(' ', $name);

    // return FALSE if you wish to skip a particular row
  }

  public function prepare($user, $row) {
    $user->meedan_notifications = drupal_map_assoc(array_keys(meedan_notifications_get_events()));
  }

  public function fuzzy_match_title($title) {
    return $this->fuzzy_match($title, array('Ms', 'Miss', 'Mrs', 'Mr', 'Master', 'Rev', 'Fr', 'Dr', 'Prof', 'Hon', 'Pres'));
  }
}
