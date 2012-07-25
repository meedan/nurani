<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function nurani_general_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: primary-links:overview
  $menu_links['primary-links:overview'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'overview',
    'router_path' => 'overview',
    'link_title' => 'Overview',
    'options' => array(),
    'module' => 'system',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
  );
  // Exported menu link: primary-links:texts
  $menu_links['primary-links:texts'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'texts',
    'router_path' => 'texts',
    'link_title' => 'Texts',
    'options' => array(),
    'module' => 'system',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '3',
  );
  // Exported menu link: secondary-links:node/3
  $menu_links['secondary-links:node/3'] = array(
    'menu_name' => 'secondary-links',
    'link_path' => 'node/3',
    'router_path' => 'node/%',
    'link_title' => 'Privacy',
    'options' => array(
      'attributes' => array(
        'title' => 'Privacy',
      ),
      'alter' => TRUE,
      'langcode' => 'en',
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-46',
  );
  // Exported menu link: secondary-links:node/4
  $menu_links['secondary-links:node/4'] = array(
    'menu_name' => 'secondary-links',
    'link_path' => 'node/4',
    'router_path' => 'node/%',
    'link_title' => 'Terms',
    'options' => array(
      'attributes' => array(
        'title' => 'Terms',
      ),
      'alter' => TRUE,
      'langcode' => 'en',
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-47',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Overview');
  t('Privacy');
  t('Terms');
  t('Texts');


  return $menu_links;
}
