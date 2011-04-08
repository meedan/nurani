<?php
/*
 * 
 * @file D6 to D7 migration wrapper.
 */

/*
 * Global wrapper functions have '_icl_wrapper' prefix.
 * Module specific wrapper functions have '_icl_$module_wrapper' prefix
 * and stored in icl_$module_wrapper.inc.
 *
 * NOTES:
 * Try to keep function name close to original Drupal's function name.
 * Use D6 function name if possible.
 */

/**
 * Root directory of Drupal installation.
 * D6 only.
 * @todo Remove this
 */
//define('DRUPAL_ROOT', getcwd());

/**
 * @todo Where to add this?
 */
function _icl_core_wrapper_init() {
//  drupal_add_js(array('icl_D7' => 1), 'setting');
//  drupal_add_js('var icl_D7 = 1;', 'inline');
}

/**
 * Create roles.
 * @see http://drupal.org/node/283261
 * @todo D7 wait for user_role_set_permissions() to be added
 *
 * @param array $roles
 *   'icanlocalize translator' => array(
 *     'name' => 'icanlocalize translator',
 *     'title' => 'ICanLocalize translator',
 *     'variable' => 'icl_translate_role'
 *     'variable_check' => 'icl_creating_translate_role'
 *     'permission' => 'can do translation jobs');
 */
function _icl_wrapper_create_roles($roles = array()) {
  foreach ($roles as $lowercase_name => $role) {
    require_once(drupal_get_path('module', 'user') . "/user.admin.inc");
    $key = array_search($role['title'], user_roles());
    if ($key) {
      variable_set($role['variable'], $key);
      if (variable_get($role['variable_check'], 0) == 1) {
        // we have created the role.
        // we can safely set the permissions

        db_query("INSERT INTO {permission} (rid, perm) VALUES ( %d, '%s')", $key, $role['permission']);
        variable_set($role['variable_check'], 0);
      }
    } else {
      variable_set($role['variable_check'], 1);
      $form_id = "user_admin_new_role";
      $form_values = array();
      $form_values["name"] = $role['title'];
      $form_values["op"] = t('Add role');
      $form_state = array();
      $form_state["values"] = $form_values;
      drupal_execute($form_id, $form_state);
    }
    // D7
    //$role = (object) $role;
    //user_role_save($role);
    //user_role_set_permissions(); // not documented yet, can't find it in D7 code
    //db_query("INSERT INTO {role_permission} (rid, perm) VALUES ( %s, '" . $role['permission'] . "')", $key);
  }
}

/**
 * db_result() wrapper.
 * Fetches one field.
 *
 * @param mixed $query Database query result resource
 * @return mixed Resulting field or FALSE
 */
function _icl_wrapper_db_result($query) {
  
  return db_result($query);

  // D7
  //return $query->fetchField();
}

/**
 * DB table name wrapper.
 *
 * @param string $table_name D6 table name
 * @return string D6|D7 table name
 */
function _icl_wrapper_table_name($table_name) {

  return $table_name;

  // D7
//  switch ($table_name) {
//    case 'permission':
//      return 'role_permission';
//      break;
//
//    case 'term_data':
//      return 'taxonomy_term_data';
//      break;
//
//    case 'blocks':
//      return 'block';
//      break;
//
//    case 'blocks_roles':
//      return 'block_role';
//      break;
//
//    case 'boxes':
//      return 'block_custom';
//      break;
//
//    default:
//      return $table_name;
//      break;
//  }
}

/**
 * Form markup wrapper.
 *
 * @param array $element
 * @return array Form element array
 */
function _icl_wrapper_form_create_markup($element) {
  if (isset($element['#markup'])) {
    $element['#type'] = 'markup';
    $element['#value'] = $element['#markup'];
    unset($element['#markup']);
  }
  
  return $element;

  // D7
  // if (isset($element['#value'])) {
  //   $element['#markup'] => element('#value');
  //}
  // unset($element['#value']);
  // unset($elemet['#type']);
  // return $element;
}

/**
 * Converts form element's ahah to ajax.
 *
 * @param array $element Form element
 * @return array
 */
function _icl_wrapper_form_convert_ahah_to_ajax($element) {
  if (isset($element['#ahah'])) {
    unset($element['#ahah']['callback']);
  }
  
  return $element;

  // D7
  // $element['#ajax'] = $element['#ahah'];
  // unset($element['#ahah']);
  //
}

/**
 * Creates form redirection element.
 * @todo Check if parsing works for D7
 *
 * @param array $form
 * @param array $goto
 */
function _icl_wrapper_form_create_redirect(&$form, $goto = array()) {
  
  $form['#redirect'] = $goto;

//  D7
//
//  $options = array();
//  if (isset($goto[1]) && is_string($goto[1])) {
//    parse_str($goto[1], $options);
//    $goto = array($goto[0], $options);
//  }
//  
//  $form['redirect'] = $goto;
}

/**
 * Creates D6 attributes array
 *
 * @param array $attributes
 * @return array
 */
function _icl_wrapper_form_create_attributes($attributes) {

  return $attributes;
}

/**
 * drupal_get_form() wrapper
 *
 * @param string $name
 * @param array $array
 * @return string
 */
function _icl_wrapper_drupal_get_form($name, $array = array()) {

  return drupal_get_form($name, $array);
//  D7
//  return drupal_render(drupal_get_form($name, $array));
}

/**
 * drupal_to_js() wrapper.
 * Function name has changed.
 *
 * @param mixed $var
 * @return string JSON encoded
 */
function _icl_wrapper_drupal_to_js($var) {

  return drupal_to_js($var);
//  D7
//  return drupal_json_encode($var);
}

/**
 * drupal_json() wrapper.
 * Function name has changed.
 *
 * @param mixed $var
 */
function _icl_wrapper_drupal_json($var) {

  drupal_json($var);
//  D7
//  drupal_json_output($var);
}

/**
 * drupal_http_request() wrapper.
 * Parameters changed.
 *
 * @param string $request_uri
 * @param array $headers
 * @param string $method
 * @param string $data
 * @param int $retry
 * @return object Response object
 */
function _icl_wrapper_drupal_http_request(
        $request_uri,
        $headers = array(),
        $method = 'GET',
        $data = NULL,
        $retry = 3)
{
  return drupal_http_request($request_uri, $headers, $method, $data, $retry);
//  D7
//  return drupal_http_request(
//    $request_uri,
//    array(
//      'headers' => $headers,
//      'method' => $method,
//      'data' => $data,
//      'method' => $method
//    )
//   );
}

/**
 * drupal_set_header() wrapper.
 * Function name has changed.
 * Uses D7 parametres
 * 
 * @param string $name HTTP header name
 * @param string $value
 */
function _icl_wrapper_drupal_set_header($name, $value, $append = FALSE) {
  drupal_set_header($name . ': ' . $value);
//  D7
//  drupal_add_http_header($name, $value, $append);
}

/**
 * drupal_set_html_head() wrapper.
 * Function name has changed.
 * @todo Check if this works
 *
 * @param mixed $data
 * @param string $key Unique identifier
 */
function _icl_wrapper_drupal_set_html_head($data, $key = NULL) {
  drupal_set_html_head($data);
//  D7
//  drupal_add_html_head($data, $key);
}

/**
 * drupal_goto() wrapper.
 * Parameters changed, follows D6 parameter order.
 * @todo Check if parsing works for D7
 *
 * @param string $path
 * @param string $query
 * @param int $http_response_code
 * @param string $fragment
 * @param array $options Extra options for D7
 */
function _icl_wrapper_drupal_goto(
  $path,
  $query = NULL,
  $fragment = NULL,
  $http_response_code = 302,
  $options = array()
  )
{
  drupal_goto($path, $query, $fragment, $http_response_code);
//  D7
//  if (!is_null($query)) {
//    parse_str($query, $query_array);
//    $options['query'] = $query_array;
//  }
//  if (!is_null($fragment)) {
//    $options['fragment'] = $fragment;
//  }
//  drupal_goto($path, $options, $http_response_code);
}

/**
 * drupal_clone() wrapper.
 *
 * @param object $object
 * @return object
 */
function _icl_wrapper_drupal_clone($object) {
  return drupal_clone($object);
//  D7
//  return clone($object);
}

/**
 * url() wrapper.
 * Parameters changed.
 * @todo Check parsing and URL encoding
 *
 * @param string $path
 * @param array $options
 * @return string
 */
function _icl_wrapper_url($path, $options = array()) {

  return url($path, $options);
//  D7
//  if (!isset($options['query'])) {
//    parse_str($options['query'], $query_array);
//    $options['query'] = $query_array;
//  }
//  return url($path, $options);
}

/**
 * book_toc() wrapper.
 * Parameters changed order. Follows D6 order.
 *
 * @param int $bid Book ID
 * @param array $exclude Optional mlid values
 * @param int $depth_limit
 * @return array of mlid
 */
function _icl_wrapper_book_toc($bid, $exclude = array(), $depth_limit) {

  return book_toc($bid, $exclude, $depth_limit);
//  D7
//  return book_toc($bid, $depth_linit, $exclude);
}

/**
 * node_get_types() wrapper.
 * Function replaced.
 * @todo Check if D7 call works
 *
 * @param string $op
 * @param object|array|string $node
 * @param boolean $reset
 * @return mixed
 */
function _icl_wrapper_node_get_types($op = 'types', $node = NULL, $reset = FALSE) {

  return node_get_types($op, $node, $reset);
//  D7
//  node_type_get_{$op}($node);
}

/**
 * block_box_get() wrapper.
 * Function name has changed.
 *
 * @param int $bid Block ID
 * @return array
 */
function _icl_wrapper_block_box_get($bid) {

  return block_box_get($bid);
//  D7
//  return block_custom_block_get($bid);
}

/**
 * module_rebuild_cache() wrapper.
 * Function name has changed.
 */
function _icl_wrapper_module_rebuild_cache() {
  module_rebuild_cache();
//  D7
//  system_rebuild_module_data();
}

/**
 * taxonomy_get_term() wrapper.
 * Function name has changed.
 *
 * @param int $tid Term's ID
 * @param boolean $reset
 * @return object Term object
 */
function _icl_wrapper_taxonomy_get_term($tid, $reset = FALSE) {
  return taxonomy_get_term($tid, $reset);
//  D7
//  return taxonomy_term_load($tid);
}

/**
 * taxonomy_save_term() wrapper.
 * Function name has changed.
 *
 * @param array $form_values
 */
function _icl_wrapper_taxonomy_save_term(&$form_values) {

  taxonomy_save_term($form_values);
//  D7
//  taxonomy_term_save($form_values);
}

/**
 * theme() wrapper.
 * Parameters changed.
 * @todo Check if custom compatibility works with D7
 *
 * @param string $hook
 * @param array $variables
 */
function _icl_wrapper_theme($hook, $variables = array()) {

  $args = array();
  $args[0] = $hook;
  
  foreach ($variables as $key => $value) {
    $args[] = $value;
  }
  
  return call_user_func_array('theme', $args);
//  D7
//  Keep compatibility with our custom hooks
//  if (strpos($hook, 'icl_') === 0) {
//    $args = array();
//    $args[0] = $hook;
//
//    foreach ($variables as $key => $value) {
//      $args[] = $value;
//    }
//
//    return call_user_func_array('theme', $args);
//  } else {
//  return theme($hook, $variables);
//  }
}

/**
 *
 * @param string $hook
 * @param <type> $param
 * @return <type> 
 */
function _icl_wrapper_table_select_header_cell($hook, $param) {

  return theme($hook, $param);
}

/**
 * hook_theme() wrapper.
 * @todo Check if works for D7
 *
 * @param array $array
 * @return array
 */
function _icl_wrapper_hook_theme($array) {

  return $array;
//  D7
//  foreach ($array as $key => $value) {
//    if (is_array($value) && isset($value['arguments']) && is_array($value['arguments'])) {
//       if (array_key_exists('form', $value['arguments'])) {
//         $array[$key]['render element'] = 'form';
//       }
//       else {
//         $array[$key]['variables'] = $value['arguments'];
//       }
//       unset($array[$key]['arguments']);
//    }
//  }
//
//  return $array;
}

/**
 * Implements hook_permission().
 *
 * @return array
 */
function icl_core_permission() {
  return array(
    ICL_PERM_ADMINISTER => array(
      'title' => t('Administer ICanLocalize'),
      'description' => ''
    )
  );
}

/**
 * Implements hook_element_info().
 *
 * @return array
 */
function icl_core_element_info($param) {
  $type = array();
  $type['checkbox_columns'] = array(
    '#input' => TRUE,
    '#process' => array('icl_core_expand_checkbox_columns'),
    '#tree' => TRUE
  );
  return $type;
}

/**
 * Implement drupal_set_session
 *
 */

function _icl_wrapper_drupal_set_session($name, $value) {
  
  // D6 - set directly
  $_SESSION[$name] = $value;
  
  // D7 - use drupal_set_session
  // drupal_set_session($name, $value);
}

function _icl_wrapper_fetch_term($table_name, $name, $vid) {
  // D6 - we can use db_rewrite_sql
  return db_fetch_object ( db_query ( db_rewrite_sql ( "SELECT t.tid, t.* FROM {" . $table_name . "} t WHERE LOWER(t.name) = LOWER('%s') AND vid = %d", 't', 'tid' ), $name, $vid ) );
  
  // D7 - http://drupal.org/update/modules/6/7#db_rewrite_sql
  // We need to use the new dynamic query and tag it "term_access"
  // ?????
}

function _icl_wrapper_add_locale_source($string) {
  // D6
  t($string, array(), $langcode = 'es'); // add to the locale sources. We can use any $langcode for this except 'en'

  // D7
  // t($string, array(), array(langcode => 'es')); // add to the locale sources. We can use any $langcode for this except 'en'

}

function _icl_wrapper_is_language_neutral($lang) {
  // D6
  if (!isset($lang)) {
    return FALSE;
  }
  return $lang == ' ';

  // D7
  //return $lang = LANGUAGE_NONE;
}

/**
 *
 * check to see if the required i18n mdules are installed
 *
 * @return a list of modules not installed.
 */

function _icl_wrapper_check_i18n_installed() {
  $not_installed = array();
  
  // D6
  
  if (!module_exists ( 'i18ntaxonomy' )) {
    $not_installed[] = array(
                             "module" => 'i18ntaxonomy',
                             "message" => t ('Please enable the i18n taxonomy module so taxonomy can be translated.'),
                            );
  }
  if (!module_exists ( 'i18nblocks' )) {
    $not_installed[] = array(
                             "module" => 'i18nblocks',
                             "message" => t ('Please enable the i18n blocks module so user defined blocks can be translated.'),
                            );
  }

  // D7 should return an empty array for now.
  // When the the i18n module has been ported to D7 we should then show the warnings if required.

  return $not_installed;
}

/**
 * Returns ICL modules root menu
 *
 * @param string $menu_item Menu item appended to root
 * @return string
 */
function _icl_wrapper_get_root_menu($menu_item) {

  return 'admin/content/' . $menu_item;
//  D7
//  return 'admin/international';
}

/**
 * Gets right arg
 *
 * @param int $arg Level from root e.g translation-management/edit/% - 3
 * @return mixed
 */
function _icl_wrapper_root_arg($arg) {
  $arg = 1+$arg;
  return arg($arg);
}

/**
 * Returns right admin links
 * 
 * @param string $menu_item
 * @return string
 */
function _icl_wrapper_get_drupal_menu($menu_item) {

  return $menu_item;
//  $aliases = array(
//      // Exceptions
//      'admin/build/modules' => 'admin/modules',
//      'admin/build/themes' => 'admin/appearance',
//      'admin/build/path' => 'admin/config/search/path',
//      'admin/build/block' => 'admin/structure/block',
//      'admin/build/menu' => 'admin/structure/menu',
//      'admin/content/types' => 'admin/structure/types',
//      'admin/content/taxonomy' => 'admin/structure/taxonomy',
//      'admin/content/forum' => 'admin/structure/forum',
//      'admin/build/testing' => 'admin/config/development/testing',
//      'admin/settings/site-maintenance' => 'admin/config/development/maintenance',
//      'admin/settings/performance' => 'admin/config/development/performance',
//      'admin/settings/contact' => 'admin/structure/contact/settings',
//      'admin/settings/filters' => 'admin/config/content/formats',
//      'admin/user/user' => 'admin/people',
//      'admin/user/permissions' => 'admin/people/permissions',
//      'admin/user/roles' => 'admin/people/permissions/roles',
//      // Generic
//      'admin/settings' => 'admin/config',
//      'admin/build' => 'admin/structure/',
//  );
//
//  foreach ($aliases as $d6 => $d7) {
//    if (strpos($menu_item, $d6) === 0) {
//      $menu_item = substr_replace($menu_item, $d7, 0, strlen($d6));
//      return $menu_item;
//    }
//  }
//
//  return $menu_item;
}

// DB TESTS
//$result = _icl_wrapper_db_query("INSERT INTO {role} (name, weight) VALUES ('%s', %d)", 'node_content2', 23);
//$result = _icl_wrapper_db_query("UPDATE {role} SET name='%s', weight=%d WHERE name='%s'", 'other role', 3, 'node_content2');
//$result = _icl_wrapper_db_query("SELECT * FROM {role} WHERE name!='%s'", 'administrator');
//$result = _icl_wrapper_db_query("SELECT * FROM {role} WHERE name='%s' OR WEIGHT = %d", 'administrator', 0);

//while ($record = db_fetch_array($result)) {
//  echo $record['name'];
//}

//while ($record = db_fetch_object($result)) {
//  echo $record->type;
//}

function _icl_wrapper_db_query() {
  $args = func_get_args();

  return call_user_func_array('db_query', $args);
}

function _icl_wrapper_t($string, $args = array(), $langcode = NULL) {
  return t($string, $args, $langcode);
}


function _icl_wrapper_user_mail_tokens($account, $language) {
  return user_mail_tokens($account, $language);
}

function _icl_wrapper_check_node_body(&$node) {
}

function _icl_wrapper_is_line_break_filter($filter) {
  return $filter->delta == 1;
}

function icl_wrapper_node_teaser($text) {
  return node_teaser($text);
}