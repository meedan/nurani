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
          'region' => 'content_bottom_left',
          'weight' => '-10',
        ),
        'nurani_comment-comment_form' => array(
          'module' => 'nurani_comment',
          'delta' => 'comment_form',
          'region' => 'content_bottom_right',
          'weight' => '-10',
        ),
        'meedan_discussion_lock-countdown' => array(
          'module' => 'meedan_discussion_lock',
          'delta' => 'countdown',
          'region' => 'content_bottom_right',
          'weight' => '-9',
        ),
        'views-43f29b2e1398197d59c83af85707ecf6' => array(
          'module' => 'views',
          'delta' => '43f29b2e1398197d59c83af85707ecf6',
          'region' => 'content_bottom_right',
          'weight' => '-8',
        ),
        'views-a9783f21c43180e1982dd660596c3c9c' => array(
          'module' => 'views',
          'delta' => 'a9783f21c43180e1982dd660596c3c9c',
          'region' => 'content_bottom_right',
          'weight' => '-7',
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

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'top_strip';
  $context->description = 'block that displays main menu and User welcome info';
  $context->tag = '';
  $context->conditions = array(
    'sitewide' => array(
      'values' => array(
        1 => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'menu_block-nurani_main_menu' => array(
          'module' => 'menu_block',
          'delta' => 'nurani_main_menu',
          'region' => 'top_strip',
          'weight' => '-16',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('block that displays main menu and User welcome info');
  $export['top_strip'] = $context;

  return $export;
}
