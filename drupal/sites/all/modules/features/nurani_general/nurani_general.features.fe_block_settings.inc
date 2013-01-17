<?php
/**
 * @file
 * nurani_general.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function nurani_general_default_fe_block_settings() {
  $export = array();

  $export['version'] = '1.0';

  // Theme independent visibility settings.
  $export['visibility'] = array(
    'menu_block-nurani_main_menu' => array(
      'delta' => 'nurani_main_menu',
      'module' => 'menu_block',
    ),
  );

  // bartik
  $theme = array();

  $theme['menu_block-nurani_main_menu'] = array(
    'module' => 'menu_block',
    'delta' => 'nurani_main_menu',
    'theme' => 'bartik',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '<none>',
    'cache' => -1,
  );

  $export['theme']['bartik'] = $theme;

  // nurani
  $theme = array();

  $theme['menu_block-nurani_main_menu'] = array(
    'module' => 'menu_block',
    'delta' => 'nurani_main_menu',
    'theme' => 'nurani',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '<none>',
    'cache' => -1,
  );

  $export['theme']['nurani'] = $theme;

  // seven
  $theme = array();

  $theme['menu_block-nurani_main_menu'] = array(
    'module' => 'menu_block',
    'delta' => 'nurani_main_menu',
    'theme' => 'seven',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '<none>',
    'cache' => -1,
  );

  $export['theme']['seven'] = $theme;

  $theme_default = variable_get('theme_default', 'garland');
  $themes = list_themes();
  foreach ($export as $theme_key => $settings) {
    if ($theme_key != $theme_default && empty($themes[$theme_key]->status)) {
      unset($export['theme'][$theme_key]);
    }
  }
  return $export;
}
