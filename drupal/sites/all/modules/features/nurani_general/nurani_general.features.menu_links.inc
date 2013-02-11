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
  // Exported menu link: user-menu:legal
  $menu_links['user-menu:legal'] = array(
    'menu_name' => 'user-menu',
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
    'weight' => '-46',
  );
  // Exported menu link: user-menu:node/2304
  $menu_links['user-menu:node/2304'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'node/2304',
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
    'weight' => '-49',
  );
  // Exported menu link: user-menu:node/2305
  $menu_links['user-menu:node/2305'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'node/2305',
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
    'weight' => '-48',
  );
  // Exported menu link: user-menu:node/2306
  $menu_links['user-menu:node/2306'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'node/2306',
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
    'weight' => '-47',
  );
  // Exported menu link: user-menu:node/2308
  $menu_links['user-menu:node/2308'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'node/2308',
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
    'weight' => '-45',
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
