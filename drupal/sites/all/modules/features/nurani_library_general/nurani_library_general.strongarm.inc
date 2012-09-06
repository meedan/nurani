<?php
/**
 * @file
 * nurani_library_general.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function nurani_library_general_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'nurani_library_backend';
  $strongarm->value = 'Drupal';
  $export['nurani_library_backend'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'nurani_library_provider_works_path';
  $strongarm->value = 'sites/all/texts';
  $export['nurani_library_provider_works_path'] = $strongarm;

  return $export;
}
