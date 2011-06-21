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
    $operations[] = array('nurani_import_texts', array());
    $operations[] = array('nurani_import_discussions', array());
    $operations[] = array('nurani_import_comments', array('discussion'));
    $operations[] = array('nurani_import_terms', array());
    $operations[] = array('nurani_import_comments', array('glossary_term'));
  
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

  set_time_limit(0);

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

  $roles = array();
  $result = db_query("
SELECT * FROM {users_roles}
  ");
  while ($role = db_fetch_object($result)) {
    $roles[$role->uid][] = $role;
  }
  $role_map = array(
    3 => array('rid' => 3, 'name' => 'administrator'),
    4 => array('rid' => 6, 'name' => 'moderator'),
    5 => array('rid' => 7, 'name' => 'scholar'),
    6 => array('rid' => 8, 'name' => 'translator'),
  );

  // Recreate users.
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
    if (!empty($roles[$legacy->uid])) foreach ($roles[$legacy->uid] as $role) {
      $user['roles'][$role_map[$role->rid]['rid']] = $role_map[$role->rid]['name'];
    }
    $account = user_save(NULL, $user);
    if (empty($account)) {
      watchdog('nurani', 'Could not create user: !user', array('!user' => print_r($user, TRUE)), WATCHDOG_ERROR);
    }
    else {
      $_SESSION['nurani']['user'][$legacy->uid] = $account->uid;

      if (!empty($legacy->agreed_date)) {
        // Save agreement.
        $agreement = array(
          'uid' => $account->uid,
          'agreed' => 1,
          'agreed_date' => $legacy->agreed_date,
        );
        drupal_write_record('agreement', $agreement);
        $form_values = array('values' => array(
          'agree' => 1,
          'uid' => $account->uid,
        ));
        nurani_notifications_subscribe(NULL, $form_values);
      }

      // Save profile.
      $profile = new StdClass;
      $profile->type = 'profile';
      node_object_prepare($profile);
      $profile->uid = $account->uid;
      $profile->name = $account->name;
      $profile->title = $account->name;
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
      $profile->skip_updateindex = TRUE;
      $profile->notifications_content_disable = TRUE;
      node_save(node_submit($profile));
      if (empty($profile->nid)) {
        watchdog('nurani', 'Could not create profile: !profile', array('!profile' => print_r($profile, TRUE)), WATCHDOG_ERROR);
      }
    }
  }
}

/**
 * Import migrated texts
 */
function nurani_import_texts() {
  global $db_url;
  if (empty($db_url['legacy'])) {
    return;
  }

  set_time_limit(0);

  // Read legacy texts.
  db_set_active('legacy');
  $texts = array();
  $result = db_query("
SELECT 
  n.*, 
  revision.*,
  body.body_value,
  description.field_text_description_value,
  source.field_text_source_value
FROM {node} n
INNER JOIN {node_revision} revision 
  ON n.vid = revision.vid
LEFT JOIN {field_data_body} body 
  ON body.entity_id = n.nid AND body.revision_id = revision.vid AND body.entity_type = 'node' AND body.language = n.language
LEFT JOIN {field_data_field_text_description} description 
  ON description.entity_id = n.nid AND description.revision_id = revision.vid AND description.entity_type = 'node' AND description.language = n.language
LEFT JOIN {field_data_field_text_source} source 
  ON source.entity_id = n.nid AND source.revision_id = revision.vid AND source.entity_type = 'node' AND source.language = n.language
WHERE n.type = 'text'
ORDER BY n.nid
  ");
  while ($text = db_fetch_object($result)) {
    $texts[] = $text;
  }

  $translations = array();
  $result = db_query("
SELECT 
  n.*, 
  revision.*,
  body.language AS other_language,
  body.body_value,
  description.field_text_description_value,
  source.field_text_source_value
FROM {node} n
INNER JOIN {node_revision} revision 
  ON n.vid = revision.vid
LEFT JOIN {field_data_body} body 
  ON body.entity_id = n.nid AND body.revision_id = revision.vid AND body.entity_type = 'node' AND body.language != n.language
LEFT JOIN {field_data_field_text_description} description 
  ON description.entity_id = n.nid AND description.revision_id = revision.vid AND description.entity_type = 'node' AND description.language != n.language
LEFT JOIN {field_data_field_text_source} source 
  ON source.entity_id = n.nid AND source.revision_id = revision.vid AND source.entity_type = 'node' AND source.language != n.language
WHERE n.type = 'text'
AND (
  body.body_value IS NOT NULL OR
  description.field_text_description_value IS NOT NULL OR
  source.field_text_source_value IS NOT NULL
)
ORDER BY n.nid
  ");
  while ($text = db_fetch_object($result)) {
    $translations[$text->nid] = $text;
  }

  // Recreate texts.
  db_set_active();
  nurani_load_autoload();
  module_load_include('inc', 'node', 'node.pages');
  foreach ($texts as $legacy) {
    $text = new StdClass;
    $text->type = 'text';
    node_object_prepare($text);
    $text->status = $legacy->status;
    $text->comment = $legacy->comment;
    $text->uid = $_SESSION['nurani']['user'][$legacy->uid];
    $text->name = user_load($text->uid)->name;
    $text->created = $legacy->created;
    $text->changed = $legacy->changed;
    $text->language = $legacy->language;
    $text->title = $legacy->title;
    $text->body = $legacy->body_value;
    $description = array();
    foreach (array($legacy->field_text_source_value, $legacy->field_text_description_value) as $field) {
      if (!empty($field)) {
        $description[] = $field;
      }
    }
    $text->field_description[0]['value'] = implode(' ', $description);
    $text->skip_updateindex = TRUE;
    $text->notifications_content_disable = TRUE;
    node_save(node_submit($text));
    if (empty($text->nid)) {
      watchdog('nurani', 'Could not create text: !text', array('!text' => print_r($text, TRUE)), WATCHDOG_ERROR);
    }
    else {
      $_SESSION['nurani']['text'][$legacy->nid] = $text->nid;

      if (!empty($translations[$legacy->nid])) {
        $legacy_translation = $translations[$legacy->nid];
        $tnids = translation_node_get_translations($text->nid);
        $translation = node_load($tnids[$legacy_translation->other_language]->nid);
        $translation->body = empty($legacy_translation->body_value) ? $text->body : $legacy_translation->body_value;
        $description = array();
        foreach (array($legacy_translation->field_text_source_value, $legacy_translation->field_text_description_value) as $field) {
          if (!empty($field)) {
            $description[] = $field;
          }
        }
        $translation->field_description[0]['value'] = empty($description) ? $text->field_description[0]['value'] : implode(' ', $description);
        $translation->skip_updateindex = TRUE;
        $translation->notifications_content_disable = TRUE;
        node_save($translation);
      }
    }
  }
}

function nurani_import_terms() {
  global $db_url;
  if (empty($db_url['legacy'])) {
    return;
  }

  set_time_limit(0);

  // Read legacy users.
  db_set_active('legacy');
  $terms = array();
  $result = db_query("
SELECT 
  n.*, 
  revision.*,
  pos.field_pos_value
FROM {node} n
INNER JOIN {node_revision} revision 
  ON n.vid = revision.vid
LEFT JOIN {field_data_field_pos} pos 
  ON n.nid = pos.entity_id AND pos.entity_type = 'node'
WHERE n.type = 'glossary_term'
ORDER BY n.nid
  ");
  while ($term = db_fetch_object($result)) {
    $terms[] = $term;
  }

  $translations = array();
  $result = db_query("
SELECT 
  entity_id AS nid,
  field_ibis_translations_nid AS rid,
  field_ibis_translations_tid AS tid
FROM {field_data_field_ibis_translations}
WHERE 
  entity_type = 'node' AND
  bundle = 'glossary_term'
  ");
  while ($translation = db_fetch_object($result)) {
    $translations[$translation->nid][] = $translation;
  }

  $pos_map = array(
    'noun' => 'noun',
    'verb' => 'verb',
    'adj' => 'adjective',
  );

  $taxonomy_map = array(
    1 => 4,
    2 => 3,
    3 => 2,
    4 => 5,
    5 => 6,
    6 => 8,
    7 => 9,
    8 => 13,
    9 => 1,
    10 => 7,
    11 => 14,
    12 => 10,
    13 => 11,
    14 => 12,
  );

  // Recreate terms.
  db_set_active();
  nurani_load_autoload();
  module_load_include('inc', 'node', 'node.pages');
  foreach ($terms as $legacy) {
    $term = new StdClass;
    $term->type = 'term';
    node_object_prepare($term);
    $term->status = $legacy->status;
    $term->comment = $legacy->comment;
    $term->uid = $_SESSION['nurani']['user'][$legacy->uid];
    $term->name = user_load($term->uid)->name;
    $term->created = $legacy->created;
    $term->changed = $legacy->changed;
    $term->language = $legacy->language;
    $term->title = $legacy->title;
    $term->field_part_of_speech[0]['value'] = $pos_map[$legacy->field_pos_value];
    $term->skip_updateindex = TRUE;
    $term->notifications_content_disable = TRUE;
    node_save(node_submit($term));
    if (empty($term->nid)) {
      watchdog('nurani', 'Could not create term: !term', array('!term' => print_r($term, TRUE)), WATCHDOG_ERROR);
    }
    else {
      $_SESSION['nurani']['term'][$legacy->nid] = $term->nid;
    }
  }

  foreach ($_SESSION['nurani']['term'] as $legacy_nid => $term_nid) {
    if (!empty($translations[$legacy_nid])) {
      $term = node_load($term_nid);
      foreach ($translations[$legacy_nid] as $translation) {
        $term->field_translation_term[]['nid'] = $_SESSION['nurani']['term'][$translation->rid];
        $term->field_translation_context[]['value'] = $taxonomy_map[$translation->tid];
      }
      $term->skip_updateindex = TRUE;
      $term->notifications_content_disable = TRUE;
      node_save($term);
    }
  }
}

function nurani_import_discussions() {
  global $db_url;
  if (empty($db_url['legacy'])) {
    return;
  }

  set_time_limit(0);

  // Read legacy discussions.
  db_set_active('legacy');
  $discussions = array();
  $result = db_query("
SELECT 
  n.*, 
  revision.*,
  body.body_value
FROM {node} n
INNER JOIN {node_revision} revision 
  ON n.vid = revision.vid
LEFT JOIN {field_data_body} body 
  ON body.entity_id = n.nid AND body.revision_id = revision.vid AND body.entity_type = 'node' AND body.language = n.language
WHERE n.type = 'discussion'
ORDER BY n.nid
  ");
  while ($discussion = db_fetch_object($result)) {
    $discussions[] = $discussion;
  }

  $additionals = array();
  foreach (array(
    'texts' => array('table' => 'field_data_field_discussion_text', 'field' => 'field_discussion_text_nid'),
    'moderators' => array('table' => 'field_data_field_moderators', 'field' => 'field_moderators_uid'),
    'translators' => array('table' => 'field_data_field_translators', 'field' => 'field_translators_uid'),
    'scholars' => array('table' => 'field_data_field_scholars', 'field' => 'field_scholars_uid'),
  ) as $key => $additional) {
    $result = db_query("
SELECT
  entity_id AS nid,
  delta,
  {$additional['field']}
FROM {{$additional['table']}}
WHERE
  entity_type = 'node' AND
  bundle = 'discussion'
    ");
    while ($row = db_fetch_object($result)) {
      $additionals[$key][$row->nid][] = $row;
    }
  }

  $translations = array();
  $result = db_query("
SELECT 
  n.*, 
  revision.*,
  body.language AS other_language,
  body.body_value
FROM {node} n
INNER JOIN {node_revision} revision 
  ON n.vid = revision.vid
INNER JOIN {field_data_body} body 
  ON body.entity_id = n.nid AND body.revision_id = revision.vid AND body.entity_type = 'node' AND body.language != n.language
WHERE n.type = 'discussion'
ORDER BY n.nid
  ");
  while ($discussion = db_fetch_object($result)) {
    $translations[$discussion->nid] = $discussion;
  }

  // Recreate discussions.
  db_set_active();
  nurani_load_autoload();
  module_load_include('inc', 'node', 'node.pages');
  foreach ($discussions as $legacy) {
    $discussion = new StdClass;
    $discussion->type = 'discussion';
    node_object_prepare($discussion);
    $discussion->status = $legacy->status;
    $discussion->comment = $legacy->comment;
    $discussion->uid = $_SESSION['nurani']['user'][$legacy->uid];
    $discussion->name = user_load($discussion->uid)->name;
    $discussion->created = $legacy->created;
    $discussion->changed = $legacy->changed;
    $discussion->language = $legacy->language;
    $discussion->title = $legacy->title;
    $discussion->body = $legacy->body_value;
    if (!empty($additionals['texts'][$legacy->nid])) foreach ($additionals['texts'][$legacy->nid] as $text) {
      $discussion->field_texts[]['nid'] = $_SESSION['nurani']['text'][$text->field_discussion_text_nid];
    }
    if (!empty($additionals['moderators'][$legacy->nid])) foreach ($additionals['moderators'][$legacy->nid] as $moderator) {
      if ($moderator->field_moderators_uid != $legacy->uid) {
        $discussion->field_moderators[]['uid'] = $_SESSION['nurani']['user'][$moderator->field_moderators_uid];
      }
    }
    if (!empty($additionals['translators'][$legacy->nid])) foreach ($additionals['translators'][$legacy->nid] as $translator) {
      if ($translator->field_translators_uid != $legacy->uid) {
        $discussion->field_translators[]['uid'] = $_SESSION['nurani']['user'][$translator->field_translators_uid];
      }
    }
    if (!empty($additionals['scholars'][$legacy->nid])) foreach ($additionals['scholars'][$legacy->nid] as $scholar) {
      if ($scholar->field_scholars_uid != $legacy->uid) {
        $discussion->field_scholars[]['uid'] = $_SESSION['nurani']['user'][$scholar->field_scholars_uid];
      }
    }
    $discussion->skip_updateindex = TRUE;
    $discussion->notifications_content_disable = TRUE;
    node_save(node_submit($discussion));
    if (empty($discussion->nid)) {
      watchdog('nurani', 'Could not create discussion: !discussion', array('!discussion' => print_r($discussion, TRUE)), WATCHDOG_ERROR);
    }
    else {
      $_SESSION['nurani']['discussion'][$legacy->nid] = $discussion->nid;

      if (!empty($translations[$legacy->nid])) {
        $legacy_translation = $translations[$legacy->nid];
        $tnids = translation_node_get_translations($discussion->nid);
        $translation = node_load($tnids[$legacy_translation->other_language]->nid);
        $translation->body = empty($legacy_translation->body_value) ? $discussion->body : $legacy_translation->body_value;
        $translation->skip_updateindex = TRUE;
        $translation->notifications_content_disable = TRUE;
        node_save($translation);
      }
    }
  }
}

function nurani_import_comments($type) {
  global $db_url;
  if (empty($db_url['legacy'])) {
    return;
  }

  set_time_limit(0);

  // Read legacy comments.
  db_set_active('legacy');
  $comments = array();
  $language_clause = ($type == 'discussion') ? "AND body.language = comment.language" : '';
  $result = db_query("
SELECT 
  comment.*,
  node.title AS parent_title,
  body.comment_body_value AS body_value
FROM {comment} comment
INNER JOIN {node} node 
  ON comment.nid = node.nid
LEFT JOIN {field_data_comment_body} body 
  ON body.entity_id = comment.cid AND body.entity_type = 'comment' {$language_clause}
WHERE
  node.type = '%s' 
ORDER BY 
  comment.cid
  ", $type);
  while ($comment = db_fetch_object($result)) {
    $comments[] = $comment;
  }

  $translations = array();
  if ($type == 'discussion') {
    $result = db_query("
  SELECT 
    comment.*,
    body.comment_body_value AS body_value,
    body.language AS other_language
  FROM {comment} comment
  INNER JOIN {node} node 
    ON comment.nid = node.nid
  INNER JOIN {field_data_comment_body} body 
    ON body.entity_id = comment.cid AND body.entity_type = 'comment' AND body.language != comment.language
  WHERE
    node.type = '%s' 
  ORDER BY 
    comment.cid
    ", $type);
    while ($translation = db_fetch_object($result)) {
      $translations[$translation->cid] = $translation;
    }
  }

  $comment_map = array(
    'discussion' => array(
      'comment' => 'response',
      'type' => 'discussion',
    ),
    'glossary_term' => array(
      'comment' => 'annotation',
      'type' => 'term',
    ),
  );

  // Recreate comments.
  db_set_active();
  nurani_load_autoload();
  module_load_include('inc', 'node', 'node.pages');
  foreach ($comments as $legacy) {
    $comment = new StdClass();
    $comment->type = $comment_map[$type]['comment'];
    node_object_prepare($comment);
    $comment->status = $legacy->status;
    $comment->uid = $_SESSION['nurani']['user'][$legacy->uid];
    $comment->name = $legacy->name;
    $comment->created = $legacy->created;
    $comment->changed = $legacy->changed;
    $comment->language = $legacy->language;
    $comment->title = t('Re: !title', array('!title' => $legacy->parent_title));
    $comment->body = $legacy->body_value;
    $comment->comment_target_nid = $_SESSION['nurani'][$comment_map[$type]['type']][$legacy->nid];
    $comment->comment_target_cid = $_SESSION['nurani']['comment'][$legacy->pid];
    $comment->thread = $legacy->thread;
    $comment->hostname = $legacy->hostname;
    $comment->skip_updateindex = TRUE;
    $comment->notifications_content_disable = TRUE;
    node_save(node_submit($comment));
    if (empty($comment->nid)) {
      watchdog('nurani', 'Could not create comment: !comment', array('!comment' => print_r($comment, TRUE)), WATCHDOG_ERROR);
    }
    else {
      $_SESSION['nurani']['comment'][$legacy->cid] = $comment->nid;

      if (!empty($translations[$legacy->cid])) {
        $legacy_translation = $translations[$legacy->cid];
        $tnids = translation_node_get_translations($comment->nid);
        $translation = node_load($tnids[$legacy_translation->other_language]->nid);
        $translation->body = empty($legacy_translation->body_value) ? $comment->body : $legacy_translation->body_value;
        $translation->skip_updateindex = TRUE;
        $translation->notifications_content_disable = TRUE;
        node_save($translation);
      }
    }
  }
}

/**
 * Various actions needed to clean up after the installation
 */
function nurani_cleanup() {
  // Clear migration data.
  unset($_SESSION['nurani']);

  // Rebuild node access database - required after OG installation
  node_access_rebuild();
  
  // Rebuild node types
  node_types_rebuild();
  
  // Clear drupal message queue for non-warning/errors
  drupal_get_messages('status', TRUE);

  // Clear out caches
  drupal_flush_all_caches();
 
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

