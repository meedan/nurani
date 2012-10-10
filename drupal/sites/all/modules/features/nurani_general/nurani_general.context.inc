<?php
/**
 * @file
 * nurani_general.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function nurani_general_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'nurani_discussion';
  $context->description = 'Discussion page for nurani';
  $context->tag = 'nurani';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'discussion' => 'discussion',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-nurani_comment_list-block' => array(
          'module' => 'views',
          'delta' => 'nurani_comment_list-block',
          'region' => 'content',
          'weight' => '1',
        ),
        'nurani_comment-comment_form' => array(
          'module' => 'nurani_comment',
          'delta' => 'comment_form',
          'region' => 'content',
          'weight' => '2',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Discussion page for nurani');
  t('nurani');
  $export['nurani_discussion'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'nurani_home';
  $context->description = 'Nurani.org website homepage blocks.';
  $context->tag = 'Nurani';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '<front>' => '<front>',
      ),
    ),
  );
  $context->reactions = array();
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Nurani');
  t('Nurani.org website homepage blocks.');
  $export['nurani_home'] = $context;

  return $export;
}
