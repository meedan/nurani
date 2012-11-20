<?php
/**
 * @file
 * nurani_general.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function nurani_general_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ajax_comments_node_types';
  $strongarm->value = array(
    'page' => 'page',
    'bundle' => 'bundle',
    'discussion' => 'discussion',
  );
  $export['ajax_comments_node_types'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ajax_comments_notify';
  $strongarm->value = 0;
  $export['ajax_comments_notify'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'nurani_library_rest_path';
  $strongarm->value = 'api';
  $export['nurani_library_rest_path'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'nurani_library_rest_user';
  $strongarm->value = 'API';
  $export['nurani_library_rest_user'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'theme_default';
  $strongarm->value = 'nurani';
  $export['theme_default'] = $strongarm;

  return $export;
}
