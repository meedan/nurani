<?php
/**
 * @file
 * nurani_general.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function nurani_general_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu:<front>
  $menu_links['main-menu:<front>'] = array(
    'menu_name' => 'main-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Home',
    'options' => array(),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '1',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-50',
  );
  // Exported menu link: main-menu:node/1
  $menu_links['main-menu:node/1'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/1',
    'router_path' => 'node/%',
    'link_title' => 'Contact Us',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
  );
  // Exported menu link: menu-footer-links:legal
  $menu_links['menu-footer-links:legal'] = array(
    'menu_name' => 'menu-footer-links',
    'link_path' => 'legal',
    'router_path' => 'legal',
    'link_title' => 'Terms',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
  );
  // Exported menu link: menu-footer-links:node/2
  $menu_links['menu-footer-links:node/2'] = array(
    'menu_name' => 'menu-footer-links',
    'link_path' => 'node/2',
    'router_path' => 'node/%',
    'link_title' => 'Getting Started',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
  );
  // Exported menu link: menu-footer-links:node/3
  $menu_links['menu-footer-links:node/3'] = array(
    'menu_name' => 'menu-footer-links',
    'link_path' => 'node/3',
    'router_path' => 'node/%',
    'link_title' => 'About Nurani.org',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
  );
  // Exported menu link: menu-footer-links:node/4
  $menu_links['menu-footer-links:node/4'] = array(
    'menu_name' => 'menu-footer-links',
    'link_path' => 'node/4',
    'router_path' => 'node/%',
    'link_title' => 'Privacy',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
  );
  // Exported menu link: menu-footer-links:node/5
  $menu_links['menu-footer-links:node/5'] = array(
    'menu_name' => 'menu-footer-links',
    'link_path' => 'node/5',
    'router_path' => 'node/%',
    'link_title' => 'How to do Scriptural Reasoning',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('About Nurani.org');
  t('Contact Us');
  t('Getting Started');
  t('Home');
  t('How to do Scriptural Reasoning');
  t('Privacy');
  t('Terms');


  return $menu_links;
}
