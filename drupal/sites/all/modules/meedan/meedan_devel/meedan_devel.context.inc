<?php
/**
 * @file
 * meedan_devel.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function meedan_devel_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'meedan_devel_dashboard';
  $context->description = 'Meedan development dashboard';
  $context->tag = 'Meedan';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'admin/dashboard' => 'admin/dashboard',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'devel-switch_user' => array(
          'module' => 'devel',
          'delta' => 'switch_user',
          'region' => 'dashboard_sidebar',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Meedan');
  t('Meedan development dashboard');
  $export['meedan_devel_dashboard'] = $context;

  return $export;
}
