<?php

/**
 * @file
 * Features support.
 */

/**
 * Return API information for features.
 */
function _ds_features_api() {
  return array(
    'ds' => array(
      'name' => t('Display suite'),
      'default_hook' => 'ds_default_settings',
      'default_file' => FEATURES_DEFAULTS_INCLUDED,
      'features_source' => TRUE,
      'file' => drupal_get_path('module', 'ds') .'/includes/ds.features.inc',
    ),
  );
}

/**
 * Implementation of hook_features_export_options().
 */
function ds_features_export_options() {
  return _ds_features_get_types();
}

/**
 * Get types for features.
 */
function _ds_features_get_types() {
  $types = array();
  foreach (module_implements('ds_api') as $module) {
    $api_info = ds_api_info($module);

    foreach ($api_info['types']() as $tkey => $type) {

      $global_exclude = variable_get($module .'_type_'. $tkey, FALSE);

      // Views displays is special case.
      if ($module == 'vd') {
        if ($global_exclude == TRUE) {
          continue;
        }
      }
      $types[$module .'-'. $type->type] = $type->name;
    }
  }
  return $types;
}

/**
 * Implementation of hook_features_export().
 */
function ds_features_export($data, &$export, $module_name = '') {
  $pipe = array();

  foreach ($data as $module) {
    list($dependency, $feature) = explode('-', $module);
    $export['dependencies'][$dependency] = $dependency;
    $export['features']['ds'][$module] = $module;
  }

  return $pipe;
}

/**
 * Implementation of hook_features_pipe_component_alter() for ds component.
 * Add node type variables on behalf of nd.
 */
function ds_features_pipe_ds_alter(&$pipe, $data, $export) {
  foreach ($data as $nd_type) {
    if (substr($nd_type, 0, 3) == 'nd-') {
      $pipe['variable'][] = 'nd_display_settings_'. str_replace('nd-', '', $nd_type);
    }
  }
}

/**
 * Implementation of hook_features_export_render().
 */
function ds_features_export_render($module = 'foo', $data) {

  $return = array();
  module_load_include('inc', 'ds', 'includes/ds.tools');

  // Create nice build data.
  $build_data = array();
  foreach ($data as $ds_setting) {
    $build_data[$ds_setting] = $ds_setting;
  }
  $export = ds_export_build($build_data);

  // Display settings.
  if (isset($export['ds']['settings'])) {
    $return['ds_default_settings'] = '  $data = '. ds_var_export($export['ds']['settings']) .";\n  return \$data;";
  }

  if (!empty($return)) {
    return $return;
  }
}

/**
 * Implementation of hook_features_export_revert().
 */
function ds_features_revert($module = NULL) {

  // Display settings.
  if ($display_settings = module_invoke($module, 'ds_default_settings')) {
    foreach ($display_settings as $ds_module => $settings) {
      foreach ($settings as $object_type => $setting) {
        foreach ($setting as $build_mode => $conf) {

          // Remove old settings.
          db_query("DELETE FROM {ds_settings} WHERE build_mode = '%s' AND module = '%s' AND type = '%s'", $build_mode, $ds_module, $object_type);

          // Catch situations where the feature name has crept into the table
          db_query("DELETE FROM {ds_settings} WHERE build_mode = '%s' AND module = '%s' AND type = '%s'", $build_mode, $module, $object_type);

          // Iterate over fields and ditch those which are hidden.
          // This is for sites have upgraded but haven't re-exported their settings.
          foreach ($conf['fields'] as $field_key => $field_value) {
            if ($field_value['region'] == 'disabled') {
              unset($conf['fields'][$field_key]);
            }
          }

          // Save new settings.
          $record = new stdClass();
          $record->module = $ds_module;
          $record->type = $object_type;
          $record->build_mode = $build_mode;
          $record->settings = serialize($conf);
          drupal_write_record('ds_settings', $record);
        }
      }
    }
  }
}
