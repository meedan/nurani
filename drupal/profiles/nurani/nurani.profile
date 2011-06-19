<?php

// Define the default theme
define('NURANI_THEME', 'nurani');

/**
 * Return an array of the modules to be enabled when this profile is installed.
 * 
 * To save time during installation, only enable module here that are either
 * required by Features or not included in any Nurani features
 *
 * @return
 *   An array of modules to enable.
 */
function nurani_profile_modules() {
  $modules = array(
    // Default Drupal modules.
    'color', 'comment', 'help', 'menu', 'taxonomy', 'dblog',
    'search', 'php', 'path', 'locale', 'translation', 'update',
    
    // CTools
    'ctools', 
    
    // Panels
    'page_manager', 'panels', 
    
    // Context
    'context',
    
    // Date
    'date_api', 'date_timezone',

    // Misc
    'vertical_tabs', 'admin_menu', 'adminrole', 
    'token', 'pathauto', 'auto_nodetitle', 'agreement',
    'taxonomy_export', 'logintoboggan', 'login_destination',

    // CCK
    'content',

    // i18n
    'i18nblocks', 'i18ncck', 'i18ncontent', 'i18n', 'l10n_client', 'i18nstrings', 'i18ntaxonomy', 'i18nsync', 'i18nmenu',
    'icl_content', 'icl_core', 'icl_translate', 'local_translations',

    // jQuery
    'jquery_update', 'jquery_ui', 
    'modalframe',

    // Strongarm
    'strongarm', 
    
    // Features
    'features',
  );

  return $modules;
}

/**
 * Return a description of the profile for the initial installation screen.
 *
 * @return
 *   An array with keys 'name' and 'description' describing this profile,
 *   and optional 'language' to override the language selection for
 *   language-specific profiles.
 */
function nurani_profile_details() {
  return array(
    'name' => 'Nurani',
    'description' => 'Install profile for Nurani.',
  );
}

/**
 * Return a list of tasks that this profile supports.
 *
 * @return
 *   A keyed array of tasks the profile will perform during
 *   the final stage. The keys of the array will be used internally,
 *   while the values will be displayed to the user in the installer
 *   task list.
 */
function nurani_profile_task_list() {
  $tasks = array();
  $tasks['configure-nurani'] = st('Configure Nurani');
  $tasks['install-nurani'] = st('Install Nurani');
  return $tasks;
}

/**
 * Perform any final installation tasks for this profile.
 *
 * @param $task
 *   The current $task of the install system. When hook_profile_tasks()
 *   is first called, this is 'profile'.
 * @param $url
 *   Complete URL to be used for a link or form action on a custom page,
 *   if providing any, to allow the user to proceed with the installation.
 *
 * @return
 *   An optional HTML string to display to the user. Only used if you
 *   modify the $task, otherwise discarded.
 */
function nurani_profile_tasks(&$task, $url) {
  // Skip to the configure task
  if ($task == 'profile') {
    $task = 'configure-nurani';  
  }
  
  // Provide a form to choose features
  if ($task == 'configure-nurani') {
    $features = array(
      'nurani_general',
      'nurani_notifications_system',
    );
    variable_set('nurani_selected_features', $features);

    // Initiate the next installation step
    $task = 'install-nurani';
    variable_set('install_task', $task);
  }
  
  // Installation batch process
  if ($task == 'install-nurani') {
    // Determine the installation operations
    $operations = array();
    
    // Pre-installation operations
    $operations[] = array('nurani_build_directories', array());
    $operations[] = array('nurani_install_languages', array());
    
    // Feature installation operations
    $features = variable_get('nurani_selected_features', array());
    foreach ($features as $feature) {
      $operations[] = array('features_install_modules', array(array($feature)));
    }

    // Post-installation operations
    $operations[] = array('nurani_config_filters', array());
    $operations[] = array('nurani_config_ctools', array());
    $operations[] = array('nurani_config_taxonomy', array());
    $operations[] = array('nurani_config_theme', array());
    $operations[] = array('nurani_config_icl', array());
    $operations[] = array('nurani_config_nodes', array());
    $operations[] = array('nurani_config_noderelationships', array());
    $operations[] = array('nurani_config_i18n', array());
    $operations[] = array('nurani_import_users', array());
    $operations[] = array('nurani_import_nodes', array());
  
    // Build the batch process
    $batch = array(
      'operations' => $operations,
      'title' => st('Configuring Nurani'),
      'error_message' => st('An error occurred. Please try reinstalling again.'),
      'finished' => 'nurani_cleanup',
    );
  
    // Start the batch
    variable_set('install_task', 'install-nurani-batch');
    batch_set($batch);
    batch_process($url, $url);
  }
  
  // Persist the page while batch executes
  if ($task == 'install-nurani-batch') {
    include_once 'includes/batch.inc';
    $output = _batch_page();
  }
  
  return $output;
}

/**
 * Create necessary directories
 */
function nurani_build_directories() {
  $dirs = array('ctools', 'ctools/css', 'pictures', 'imagecache', 'css', 'js');
  
  foreach ($dirs as $dir) {
    $dir = file_directory_path() . '/' . $dir;
    file_check_directory($dir, TRUE);
  }
}

/**
 * Install needed languages
 */
function nurani_install_languages() {
  include_once './includes/locale.inc';
  $langcode = 'ar';

  // Predefined language selection.
  $predefined = _locale_get_predefined_list();
  locale_add_language($langcode);
  // See if we have language files to import for the newly added
  // language, collect and import them.
  if ($batch = locale_batch_by_language($langcode, '_locale_batch_language_finished')) {
    batch_set($batch);
  }

  // Language configure.
  db_query('UPDATE {languages} SET prefix = \'en\' WHERE language=\'en\' ');
  variable_set('language_negotiation', LANGUAGE_NEGOTIATION_PATH_DEFAULT);

  // Import .po files.
  $path = drupal_get_path('profile', 'nurani') . '/po';
  $files = drupal_system_listing('.po$', $path, 'name', 0);
  foreach ($files as $file) {
    $po_file = array(
      'filename' => $file->basename,
      'filepath' => $file->filename,
      );
    _locale_import_po((object)$po_file, $langcode, LOCALE_IMPORT_OVERWRITE, 'default');
  }

  drupal_flush_all_caches();
}

/**
 * Configure filters
 */
function nurani_config_filters() {
  // Add Nurani glossary filter to Filtered HTML
  $filter = new stdClass;
  $filter->format = 1;
  $filter->module = 'nurani_glossary';
  $filter->delta = 0;
  $filter->weight = 10;
  drupal_write_record('filters', $filter);

  db_query("UPDATE {filter_formats} SET cache = 0 WHERE format = 1");
}

/**
 * Configure ctools
 */
function nurani_config_ctools() {
  ctools_include('context');
  ctools_include('plugins');
  
  // Enable node view override (variants imported via Features)
  $page = page_manager_get_page_cache('node_view');
  if ($function = ctools_plugin_get_function($page->subtask, 'enable callback')) {
    $result = $function($page, FALSE);

    if (!empty($page->changed)) {
      page_manager_set_page_cache($page);
    }
  }
  
  // Enable profile view override (variant imported via Features) 
  $page = page_manager_get_page_cache('user_view');
  if ($function = ctools_plugin_get_function($page->subtask, 'enable callback')) {
    $result = $function($page, FALSE);

    if (!empty($page->changed)) {
      page_manager_set_page_cache($page);
    }
  }
}

/**
 * Configure taxonomy
 */
function nurani_config_taxonomy() {
  module_load_include('inc', 'install_profile_api', 'contrib/taxonomy_export');
  $path = drupal_get_path('profile', 'nurani') . '/taxonomy/*.inc';
  foreach (glob($path) as $file) {
    install_taxonomy_export_import_from_file($file);
  }
}
 
/**
 * Configure theme
 */
function nurani_config_theme() {
  // Enable Nurani theme
  db_query("UPDATE {system} SET status = 1 WHERE type = 'theme' and name = '%s'", NURANI_THEME);
  
  // Set Nurani theme as the default
  variable_set('theme_default', NURANI_THEME);
  
  // Refresh registry
  list_themes(TRUE);
  drupal_rebuild_theme_registry();
}

/**
 * Configure ICanLocalize
 */
function nurani_config_icl() {
  variable_set('icl_translate_role', 8);
  variable_set('icl_manager_role', 6);
  db_query("DELETE FROM {role} WHERE name IN ('ICanLocalize translator', 'ICanLocalize manager')");
}

function nurani_load_autoload() {
  foreach (module_implements('autoload_info') as $module) {
    $function = $module . '_autoload_info';
    foreach ($function() as $info) {
      include_once(drupal_get_path('module', $module) . '/' . $info['file']);
    }
  }
}

/**
 * Import static nodes
 */
function nurani_config_nodes() {
  nurani_load_autoload();
  $path = drupal_get_path('profile', 'nurani') . '/nodes/*.inc';
  foreach (glob($path) as $file) {
    $node_code = file_get_contents($file);
    node_export_import($node_code);
  }
}

/**
 * Configure Node Relationships
 */
function nurani_config_noderelationships() {
  $noderelationships_setting = array(
    'type_name' => 'discussion',
    'relation_type' => 'noderef',
    'related_type' => '',
    'field_name' => 'field_texts',
    'settings' => 'a:2:{s:25:\"search_and_reference_view\";s:26:\"text_references:page_table\";s:20:\"create_and_reference\";s:11:\"field_texts\";}',
  );
  drupal_write_record('noderelationships_settings', $noderelationships_setting);
}

/**
 * Configure internationalization features
 */
function nurani_config_i18n() {
  // TODO: Fix this
  // Update all secondary menu items.
  module_load_include('inc', 'install_profile_api', 'core/menu');
  $items = install_menu_get_items(NULL, NULL, NULL, 'secondary-links');
  foreach ($items as $item) {
    _i18nmenu_update_item($item);
  }

  // TODO: Fix this.
  // Update block information 
  $i18n_blocks = array(
    array('ibid'=>1,'module'=>'boxes','delta'=>'welcome_box','type'=>0,'language'=>'')
  );
  foreach ($i18n_blocks as $i18n_block) {
    drupal_write_record('i18n_blocks', $i18n_block);
  }
}

/**
 * Import migrated users
 */
function nurani_import_users() {
  global $db_url;
  if (empty($db_url['legacy'])) {
    return;
  }

  // Read legacy users.
  db_set_active('legacy');
  $users = array();
  $result = db_query("
SELECT 
  u.*, 
  arabic.field_user_arabic_value,
  city.field_user_city_value,
  country.field_user_country_value,
  education.field_user_education_value,
  english.field_user_english_value,
  experience.field_user_experience_value,
  fname.field_user_fname_value,
  lname.field_user_lname_value,
  position.field_user_position_value,
  publications.field_user_publications_value,
  research.field_user_research_value,
  societies.field_user_societies_value,
  title.field_user_title_value,
  agreement.agreed_date,
  file.filename
FROM {users} u
LEFT JOIN {field_data_field_user_arabic} arabic on u.uid = arabic.entity_id
LEFT JOIN {field_data_field_user_city} city on u.uid = city.entity_id
LEFT JOIN {field_data_field_user_country} country on u.uid = country.entity_id
LEFT JOIN {field_data_field_user_education} education on u.uid = education.entity_id
LEFT JOIN {field_data_field_user_english} english on u.uid = english.entity_id
LEFT JOIN {field_data_field_user_experience} experience on u.uid = experience.entity_id
LEFT JOIN {field_data_field_user_fname} fname on u.uid = fname.entity_id
LEFT JOIN {field_data_field_user_lname} lname on u.uid = lname.entity_id
LEFT JOIN {field_data_field_user_position} position on u.uid = position.entity_id
LEFT JOIN {field_data_field_user_publications} publications on u.uid = publications.entity_id
LEFT JOIN {field_data_field_user_research} research on u.uid = research.entity_id
LEFT JOIN {field_data_field_user_societies} societies on u.uid = societies.entity_id
LEFT JOIN {field_data_field_user_title} title on u.uid = title.entity_id
LEFT JOIN {agreement} agreement on u.uid = agreement.uid
LEFT JOIN {file_managed} file on u.uid = file.uid
WHERE
  u.uid > 1
  ");
  while ($user = db_fetch_object($result)) {
    $users[] = $user;
  }

  // Recreate users.
  set_time_limit(0);
  db_set_active();
  nurani_load_autoload();
  module_load_include('inc', 'node', 'node.pages');
  features_rebuild();
  foreach ($users as $legacy) {
    $user = array(
      'name' => $legacy->name,
      'pass' => 'test',
      'mail' => $legacy->mail,
      'created' => $legacy->created,
      'access' => $legacy->access,
      'login' => $legacy->login,
      'status' => $legacy->status,
      'timezone_name' => $legacy->timezone,
      'timezone' => date_offset_get(date_make_date('now', $legacy->timezone)),
      'language' => $legacy->language,
      'init' => $legacy->init,
      'picture' => empty($legacy->filename) ? '' : file_create_path('sites/default/files/pictures/' . $legacy->filename),
    );
    $user = user_save(NULL, $user);
    if ($user) {
      if (!empty($legacy->agreed_date)) {
        // Save agreement.
        $agreement = array(
          'uid' => $user->uid,
          'agreed' => 1,
          'agreed_date' => $legacy->agreed_date,
        );
        drupal_write_record('agreement', $agreement);
        $form_values = array('values' => array(
          'agree' => 1,
          'uid' => $user->uid,
        ));
        nurani_notifications_subscribe(NULL, $form_values);
      }

      // Save profile.
      $profile = new StdClass;
      $profile->type = 'profile';
      node_object_prepare($profile);
      $profile->uid = $user->uid;
      $profile->name = $user->name;
      $profile->title = $user->name;
      $profile->created = $legacy->created;
      $profile->changed = $legacy->created;
      $profile->field_city[0]['value'] = $legacy->field_user_city_value;
      $profile->field_country[0]['value'] = $legacy->field_user_country_value;
      $profile->field_education[0]['value'] = $legacy->field_user_education_value;
      $profile->field_experience[0]['value'] = $legacy->field_user_experience_value;
      $profile->field_fluency_ar[0]['value'] = $legacy->field_user_arabic_value;
      $profile->field_fluency_en[0]['value'] = $legacy->field_user_english_value;
      $fullname = array();
      foreach (array($legacy->field_user_fname_value, $legacy->field_user_lname_value) as $name) {
        if (!empty($name)) {
          $fullname[] = $name;
        }
      }
      $profile->field_fullname[0]['value'] = implode(' ', $fullname);
      $profile->field_position[0]['value'] = $legacy->field_user_position_value;
      $profile->field_publications[0]['value'] = $legacy->field_user_publications_value;
      $profile->field_research[0]['value'] = $legacy->field_user_research_value;
      $profile->field_societies[0]['value'] = $legacy->field_user_societies_value;
      $profile->field_title[0]['value'] = $legacy->field_user_title_value;
      node_save(node_submit($profile));
    }
  }
}

/**
 * Import migrated nodes
 */
function nurani_import_nodes() {
  global $db_url;
  if (empty($db_url['legacy'])) {
    return;
  }
}

/**
 * Various actions needed to clean up after the installation
 */
function nurani_cleanup() {
  // Rebuild node access database - required after OG installation
  node_access_rebuild();
  
  // Rebuild node types
  node_types_rebuild();
  
  // Clear drupal message queue for non-warning/errors
  drupal_get_messages('status', TRUE);

  // Clear out caches
  $core = array('cache', 'cache_block', 'cache_filter', 'cache_page');
  $cache_tables = array_merge(module_invoke_all('flush_caches'), $core);
  foreach ($cache_tables as $table) {
    cache_clear_all('*', $table, TRUE);
  }
  
  // Clear out JS and CSS caches
  drupal_clear_css_cache();
  drupal_clear_js_cache();
  
  // Some features will need reverting
  $revert = array(
    'nurani_general' => array('menu_links'),
  );
  
  // Make sure we only try to revert features we've enabled
  $enabled = variable_get('nurani_selected_features', array('nurani_general'));
  foreach ($revert as $feature => $value) {
    if (!in_array($feature, $enabled)) {
      unset($revert[$feature]);
    }
  }
  features_revert($revert);
  
  // Say hello to the dog!
  watchdog('nurani', st('Welcome to Nurani!'));
  
  // Remove the feature choices
  variable_del('nurani_selected_features');
  
  // Finish the installation
  variable_set('install_task', 'profile-finished');
}

/**
 * Alter the install profile configuration
 */
function system_form_install_configure_form_alter(&$form, $form_state) {
  // Add timezone options required by date (Taken from Open Atrium)
  if (function_exists('date_timezone_names') && function_exists('date_timezone_update_site')) {
    $form['server_settings']['date_default_timezone']['#access'] = FALSE;
    $form['server_settings']['#element_validate'] = array('date_timezone_update_site');
    $form['server_settings']['date_default_timezone_name'] = array(
      '#type' => 'select',
      '#title' => st('Default time zone'),
      '#default_value' => 'Europe/London',
      '#options' => date_timezone_names(FALSE, TRUE),
      '#description' => st('Select the default site time zone. If in doubt, choose the timezone that is closest to your location which has the same rules for daylight saving time.'),
      '#required' => TRUE,
    );
  }
}

