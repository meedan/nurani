<?php
/*
 *
 * @file D6 to D7 migration wrapper.
 */

/**
 * Implements hook_permission().
 *
 * @return array
 */
function icl_content_permission() {
  
  return array(
    ICL_CONTENT_PERM_COMMENT => array(
      'title' => t('Moderate comments in own language'),
      'description' => ''
    ),
    ICL_CONTENT_PERM_TRANSLATE => array(
      'title' => t('Submit content for translation'),
      'description' => ''
    )
  );
}

/**
 * Implements hook_node_insert().
 */
function icl_content_node_insert(&$node) {
  icl_content_nodeapi($node, 'insert');
}

/**
 * Implements hook_node_update().
 */
function icl_content_node_update(&$node) {
  icl_content_nodeapi($node, 'update');
}

/**
 * Implements hook_node_delete().
 */
function icl_content_node_delete(&$node) {
  icl_content_nodeapi($node, 'delete');
}

/**
 * Implements hook_node_load().
 */
function icl_content_node_load(&$node) {
  icl_content_nodeapi($node, 'load');
}

/**
 * Implements hook_node_prepare().
 */
function icl_content_node_prepare(&$node) {
  icl_content_nodeapi($node, 'prepare');
}

/**
 * Implements hook_node_prepare_translation().
 */
function icl_content_node_prepare_translation(&$node) {
  icl_content_nodeapi($node, 'prepare_translation');
}

/**
 * Implements hook_node_search_result().
 */
function icl_content_node_search_result(&$node) {
  icl_content_nodeapi($node, 'search_result');
}

/**
 * Implements hook_node_presave().
 */
function icl_content_node_presave(&$node) {
  icl_content_nodeapi($node, 'presave');
}

/**
 * Implements hook_node_update_index().
 */
function icl_content_node_update_index(&$node) {
  icl_content_nodeapi($node, 'update_index');
}

/**
 * Implements hook_node_validate().
 */
function icl_content_node_validate(&$node) {
  icl_content_nodeapi($node, 'validate');
}

/**
 * Implements hook_node_view().
 */
function icl_content_node_view(&$node) {
  icl_content_nodeapi($node, 'view');
}