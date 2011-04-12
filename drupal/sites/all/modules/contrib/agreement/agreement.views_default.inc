<?php
// $Id: agreement.views_default.inc,v 1.2 2010/05/05 06:21:47 pagaille Exp $

/**
 * Implementation of hook_views_default_views().
 */
function agreement_views_default_views() {
  /*
   * View 'agreements'
   */
  $view = new view;
  $view->name = 'Agreements';
  $view->description = 'A list of all agreements';
  $view->tag = 'agreement';
  $view->view_php = '';
  $view->base_table = 'users';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
  'name' => array(
    'label' => 'Name',
    'alter' => array(
      'alter_text' => 0,
      'text' => '',
      'make_link' => 0,
      'path' => '',
      'link_class' => '',
      'alt' => '',
      'prefix' => '',
      'suffix' => '',
      'target' => '',
      'help' => '',
      'trim' => 0,
      'max_length' => '',
      'word_boundary' => 1,
      'ellipsis' => 1,
      'html' => 0,
      'strip_tags' => 0,
  ),
    'empty' => '',
    'hide_empty' => 0,
    'empty_zero' => 0,
    'link_to_user' => 1,
    'overwrite_anonymous' => 0,
    'anonymous_text' => '',
    'exclude' => 0,
    'id' => 'name',
    'table' => 'users',
    'field' => 'name',
    'relationship' => 'none',
  ),
  'agreed_date' => array(
    'label' => 'Agreement date',
    'alter' => array(
      'alter_text' => 0,
      'text' => '',
      'make_link' => 0,
      'path' => '',
      'link_class' => '',
      'alt' => '',
      'prefix' => '',
      'suffix' => '',
      'target' => '',
      'help' => '',
      'trim' => 0,
      'max_length' => '',
      'word_boundary' => 1,
      'ellipsis' => 1,
      'html' => 0,
      'strip_tags' => 0,
  ),
    'empty' => 'Unknown',
    'hide_empty' => 0,
    'empty_zero' => 1,
    'date_format' => 'small',
    'custom_date_format' => '',
    'exclude' => 0,
    'id' => 'agreed_date',
    'table' => 'agreement',
    'field' => 'agreed_date',
    'relationship' => 'none',
  ),
  ));
  $handler->override_option('filters', array(
  'uid_1' => array(
    'operator' => 'not in',
    'value' => array(
      '0' => 0,
  ),
    'group' => '0',
    'exposed' => FALSE,
    'expose' => array(
      'operator' => FALSE,
      'label' => '',
  ),
    'id' => 'uid_1',
    'table' => 'users',
    'field' => 'uid',
    'relationship' => 'none',
  ),
  'uid' => array(
    'operator' => 'in',
    'value' => '',
    'group' => '0',
    'exposed' => TRUE,
    'expose' => array(
      'use_operator' => 0,
      'operator' => 'uid_op',
      'identifier' => 'uid',
      'label' => 'Username',
      'optional' => 1,
      'remember' => 0,
      'reduce' => 0,
  ),
    'id' => 'uid',
    'table' => 'users',
    'field' => 'uid',
    'relationship' => 'none',
  ),
  'agreed_date' => array(
    'operator' => 'between',
    'value' => array(
      'type' => 'date',
      'value' => '',
      'min' => '',
      'max' => '',
  ),
    'group' => '0',
    'exposed' => TRUE,
    'expose' => array(
      'use_operator' => 0,
      'operator' => 'agreed_date_op',
      'identifier' => 'agreed_date',
      'label' => 'Agreement date between',
      'optional' => 1,
      'remember' => 0,
  ),
    'id' => 'agreed_date',
    'table' => 'agreement',
    'field' => 'agreed_date',
    'relationship' => 'none',
  ),
  ));
  $handler->override_option('access', array(
  'type' => 'perm',
  'perm' => 'administer users',
  ));
  $handler->override_option('cache', array(
  'type' => 'none',
  ));
  $handler->override_option('title', 'Agreements');
  $handler->override_option('items_per_page', 30);
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
  'grouping' => '',
  'override' => 1,
  'sticky' => 0,
  'order' => 'asc',
  'columns' => array(
    'name' => 'name',
    'agreed_date' => 'agreed_date',
    'status' => 'status',
  ),
  'info' => array(
    'name' => array(
      'sortable' => 1,
      'separator' => '',
  ),
    'agreed_date' => array(
      'sortable' => 1,
      'separator' => '',
  ),
    'status' => array(
      'sortable' => 1,
      'separator' => '',
  ),
  ),
  'default' => 'name',
  ));
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->override_option('path', 'admin/user/agreements');
  $handler->override_option('menu', array(
  'type' => 'normal',
  'title' => 'Agreements',
  'description' => 'A list of all agreements',
  'weight' => '0',
  'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
  'type' => 'none',
  'title' => '',
  'description' => '',
  'weight' => 0,
  'name' => 'navigation',
  ));

  $views[$view->name] = $view;

  return $views;
}
