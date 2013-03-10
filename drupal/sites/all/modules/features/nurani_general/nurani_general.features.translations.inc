<?php
/**
 * @file
 * nurani_general.features.translations.inc
 */

/**
 * Implements hook_translations_defaults().
 */
function nurani_general_translations_defaults() {
  $translations = array();
  $translations['ar:field'][5857] = array(
    'lid' => '5857',
    'source' => '20 - 25',
    'context' => 'field_age:#allowed_values:20-25',
    'location' => 'field:field_age:#allowed_values:20-25',
    'translation' => '20 - 25',
    'plid' => '0',
    'plural' => '0',
  );
  return $translations;
}
