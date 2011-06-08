<?php

/**
 * @file nodereference_explorer.util.inc
 * This files holds several utility functions.
 */

/**
 * Get the added JS in a format that is readable by explorer.js (copied from popups.js).
 * @return
 *   array of formatted js html header header includes, e. g. <script type="text/javascript" src=....>
 */
function nodereference_explorer_util_get_js() {
  $javascript = array_merge_recursive(drupal_add_js(), drupal_add_js(NULL, NULL, 'footer'));
  $output = '';
  $query_string = '?'. drupal_substr(variable_get('css_js_query_string', '0'), 0, 1);

  // For inline Javascript to validate as XHTML, all Javascript containing
  // XHTML needs to be wrapped in CDATA. To make that backwards compatible
  // with HTML 4, we need to comment out the CDATA-tag.
  $embed_prefix = "\n<!--//--><![CDATA[//><!--\n";
  $embed_suffix = "\n//--><!]]>\n";

  foreach ($javascript as $type => $data) {

    if (!$data) continue;

    switch ($type) {
      case 'setting':
        /* Why not just array_merge_recursive($data); */
        $output['setting'] = call_user_func_array('array_merge_recursive', $data);
        break;
      case 'inline':
        foreach ($data as $info) {
          $output['inline'][] = '<script type="text/javascript"' . ($info['defer'] ? ' defer="defer"' : '') . '>' . $embed_prefix . $info['code'] . $embed_suffix . "</script>\n";
        }
        break;
      default:
        foreach ($data as $path => $info) {
          $output[$type][$path] = '<script type="text/javascript"'. ($info['defer'] ? ' defer="defer"' : '') .' src="'. base_path() . $path . $query_string ."\"></script>\n";
        }
    }
  }
  return $output;
}

/**
 * Get the added CSSes in a format that is readable by explorer.js (copied from popups.js).
 * @return
 *   array of formatted css links, e. g. <link type="text/css" rel="stylesheet"....>
 */
function nodereference_explorer_util_get_css() {
  $css = drupal_add_css();
  $explorer_css = array();

  $query_string = '?'. substr(variable_get('css_js_query_string', '0'), 0, 1);

  // Only process styles added to "all".
  $media = 'all';
  foreach ($css[$media] as $type => $files) {
    if ($type == 'module') {
      // Setup theme overrides for module styles.
      $theme_styles = array();
      foreach (array_keys($css[$media]['theme']) as $theme_style) {
        $theme_styles[] = basename($theme_style);
      }
    }
    foreach($css[$media][$type] as $file => $preprocess) {
      // If the theme supplies its own style using the name of the module style, skip its inclusion.
      // This includes any RTL styles associated with its main LTR counterpart.
      if ($type == 'module' && in_array(str_replace('-rtl.css', '.css', basename($file)), $theme_styles)) {
        // Unset the file to prevent its inclusion when CSS aggregation is enabled.
        unset($css[$media][$type][$file]);
        continue;
      }
      // Only include the stylesheet if it exists.
      if (file_exists($file)) {
        // If a CSS file is not to be preprocessed and it's a module CSS file, it needs to *always* appear at the *top*,
        // regardless of whether preprocessing is on or off.
        if ($type == 'module') {
          $explorer_css['module'][$file] = '<link type="text/css" rel="stylesheet" media="'. $media .'" href="'. base_path() . $file . $query_string .'" />'."\n";
        }
        // If a CSS file is not to be preprocessed and it's a theme CSS file, it needs to *always* appear at the *bottom*,
        // regardless of whether preprocessing is on or off.
        else if ($type == 'theme') {
          $explorer_css['theme'][$file] = '<link type="text/css" rel="stylesheet" media="'. $media .'" href="'. base_path() . $file . $query_string .'" />'."\n";
        }
        else {
          $explorer_css['unknown'][$file] = '<link type="text/css" rel="stylesheet" media="'. $media .'" href="'. base_path() . $file . $query_string .'" />'."\n";
        }
      }
    }
  }
  return $explorer_css;
}

/**
 * Parse the widget settings according to their type.
 * @param $field
 *   is passed by reference now to add additional external settings
 * @param $domain
 *   settings types
 * @return
 *   array of settings of a specific type
 */
function nodereference_explorer_util_parse_settings(&$field, $domain) {
  //get additional settings when integrating into a third party CCK field, e. g. link
  //Field and widget settings are stored in the field['widget'] array. Bring field
  //settings one level higher, as a usual nodereference.
  //NOTE: This doesn't fix the problem of these settings being global, they cannot be shared!
  if (!isset($field['referenceable_types']))
    $field['referenceable_types'] = $field['widget']['referenceable_types'];

  if (!isset($field['advanced_view']))
    $field['advanced_view'] = $field['widget']['advanced_view'];

  if (!isset($field['advanced_view_args']))
    $field['advanced_view_args'] = $field['widget']['advanced_view_args'];

  $settings = array();
  foreach (array_keys($field['widget']) as $widget_key) {
    if (strstr($widget_key, $domain)) {
      //$pos = strpos($widget_key, $domain);
      if (strstr($widget_key, '@')) {
        $pos_at = strpos($widget_key, '@');
        $type = drupal_substr($widget_key, $pos_at+1);
        $widget_key = drupal_substr($widget_key, 0, $pos_at);
      }
      //$widget_key = substr($widget_key, $pos + strlen($domain));
      $delimit = strpos($widget_key, '_');
      $key = drupal_substr($widget_key, $delimit+1);

      if (isset($type)) { //interprete data type properly
        switch ($type) {
          case 'int':
            $settings[$key] = intval($field['widget'][$widget_key .'@int']);
            break;
          case 'boolean':
            $settings[$key] = $field['widget'][$widget_key .'@boolean'] == 0 ? TRUE : FALSE;
            break;
        }
        unset($type);
      }
      else {
        $settings[$key] = $field['widget'][$widget_key];
      }
    }
  }
  return $settings;
}

/**
 * Load the specified theme css files
 * @param $theme
 *  theme modes: global, jquery ui or module
 */
function nodereference_explorer_util_theme_css($theme) {
  switch ($theme['css']) {
    case '<module>':
      nodereference_explorer_add_css('explorer.all');
      break;
    case '<global>':
      //do nothring
      break;
   default: //jquery_ui theme
     $path = JQUERY_UI_PATH . '/themes/'. $theme['css'];
     $css_files = file_scan_directory($path, '\.all\.css$');
     if (empty($css_files)) //include all css files, if no overall css header can be found
       $css_files = file_scan_directory($path, '\.css$');

     foreach($css_files as $css)
         drupal_add_css($css->filename);
   }
}

/**
 * Load necessary jquery_ui dialog libs
 * @param $dialog
 *   dialog settings
 */
function nodereference_explorer_util_jquery_ui_js($dialog) {
  $jq_ui_files = array('ui.dialog', 'ui.tabs');
  if ($dialog['draggable']) //can the dialog window be moved
    array_push($jq_ui_files, 'ui.draggable');

  if ($dialog['resizable']) //can the dialog window be resized
    array_push($jq_ui_files, 'ui.resizable');

  if ($dialog['bgiframe']) //patch for IE 6 z-Index problem, i. e. overlay of controls over dialog
    nodereference_explorer_add_js('jquery.bgiframe', true);
  jquery_ui_add($jq_ui_files);
}

/**
 * Commcon JS for an explorer widget, not specific for dialog API.
 * @param $field
 *   CCK content field
 */
function nodereference_explorer_util_explorer_js($field) {
  //preload the theme due to better performance and working in IE 8
  //TODO: Avoid loadin CSS files as they may be overridden by a global theme anyway
  $theme = nodereference_explorer_util_parse_settings($field, 'theme'); //theme mode
  nodereference_explorer_util_theme_css($theme); //load necessary css files
  nodereference_explorer_add_css('explorer.tabs');
  nodereference_explorer_add_css('explorer.selection');
  
  //preload explorer relevant javascript
  $dialog = nodereference_explorer_util_parse_settings($field, 'dialog');  
  nodereference_explorer_util_jquery_ui_js($dialog); //add dialog related js files
  nodereference_explorer_add_js('explorer.tabs'); //dialog tabs 
  nodereference_explorer_add_js('explorer.selection');
}

/**
 * Get the used dialog api of the CCK field.
 * @param $field
 * @return
 *   id of dialog api (built-in or modalframe)
 */
function nodereference_explorer_util_dialog_api($field) {
  $dialog_settings = nodereference_explorer_util_parse_settings($field, 'dialog');
  if (isset($dialog_settings['api'])) { //dialog api stored in field settings
    return $dialog_settings['api'];
  }
  else { //if nothing found, search in external settings
    $extended_settings = variable_get('nodereference_explorer_settings_'. $field['field_name'], NULL);
    if (!$extended_settings) //return default dialog api
      return 'nodereference_explorer';
    else {
      return $extended_settings['dialog_api'];
    }
  }
}

function nodereference_explorer_util_get_all_referenceable_node_types() {
  //build node types
  $node_types = array();
  foreach (array_keys(node_get_types('types')) as $type) {
    $node_types[$type] = $type;
  }
  return $node_types;
}