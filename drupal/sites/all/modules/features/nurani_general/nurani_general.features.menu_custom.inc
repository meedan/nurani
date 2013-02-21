<?php
/**
 * @file
 * nurani_general.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function nurani_general_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: main-menu.
  $menus['main-menu'] = array(
    'menu_name' => 'main-menu',
    'title' => 'Main menu',
    'description' => 'The <em>Main</em> menu is used on many sites to show the major sections of the site, often in a top navigation bar.',
  );
  // Exported menu: menu-footer-links.
  $menus['menu-footer-links'] = array(
    'menu_name' => 'menu-footer-links',
    'title' => 'Footer links',
    'description' => '',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Footer links');
  t('Main menu');
  t('The <em>Main</em> menu is used on many sites to show the major sections of the site, often in a top navigation bar.');


  return $menus;
}
