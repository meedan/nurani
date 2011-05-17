<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function nurani_general_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: primary-links:glossary
  $menu_links['primary-links:glossary'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'glossary',
    'router_path' => 'glossary',
    'link_title' => 'Glossary',
    'options' => array(),
    'module' => 'system',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '1',
  );
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
  // Exported menu link: secondary-links:node/24
  $menu_links['secondary-links:node/24'] = array(
    'menu_name' => 'secondary-links',
    'link_path' => 'node/24',
    'router_path' => 'node/%',
    'link_title' => 'About Nurani.org',
    'options' => array(
      'attributes' => array(
        'title' => 'About Nurani.org',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
  );
  // Exported menu link: secondary-links:node/25
  $menu_links['secondary-links:node/25'] = array(
    'menu_name' => 'secondary-links',
    'link_path' => 'node/25',
    'router_path' => 'node/%',
    'link_title' => 'Guidance',
    'options' => array(
      'attributes' => array(
        'title' => 'Guidance',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '1',
  );
  // Exported menu link: secondary-links:node/26
  $menu_links['secondary-links:node/26'] = array(
    'menu_name' => 'secondary-links',
    'link_path' => 'node/26',
    'router_path' => 'node/%',
    'link_title' => 'Privacy',
    'options' => array(
      'attributes' => array(
        'title' => 'Privacy',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '3',
  );
  // Exported menu link: secondary-links:node/27
  $menu_links['secondary-links:node/27'] = array(
    'menu_name' => 'secondary-links',
    'link_path' => 'node/27',
    'router_path' => 'node/%',
    'link_title' => 'Terms',
    'options' => array(
      'attributes' => array(
        'title' => 'Terms',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '3',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('About Nurani.org');
  t('Glossary');
  t('Guidance');
  t('Overview');
  t('Privacy');
  t('Terms');
  t('Texts');


  return $menu_links;
}
