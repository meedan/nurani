<?php
/**
 * @file
 * nurani_core.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function nurani_core_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function nurani_core_node_info() {
  $items = array(
    'bundle' => array(
      'name' => t('Bundle'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'discussion' => array(
      'name' => t('Discussion'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
