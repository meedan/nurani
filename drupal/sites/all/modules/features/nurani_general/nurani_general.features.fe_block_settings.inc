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

  $export['version'] = '2.0';

  $export['menu-menu-footer-links'] = array(
    'cache' => -1,
    'custom' => '0',
    'delta' => 'menu-footer-links',
    'module' => 'menu',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'nurani' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'nurani',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '<none>',
    'visibility' => '0',
  );

  $export['menu_block-nurani_main_menu'] = array(
    'cache' => -1,
    'custom' => '0',
    'delta' => 'nurani_main_menu',
    'module' => 'menu_block',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'nurani' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'nurani',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '<none>',
    'visibility' => '0',
  );

  return $export;
}
