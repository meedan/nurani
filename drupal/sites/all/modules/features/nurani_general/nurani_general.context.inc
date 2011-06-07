<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function nurani_general_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'discussion';
  $context->description = 'Discussion page';
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
        'views-discussion_texts-block_1' => array(
          'module' => 'views',
          'delta' => 'discussion_texts-block_1',
          'region' => 'content_top',
          'weight' => 0,
        ),
        'views-nuranis-block_2' => array(
          'module' => 'views',
          'delta' => 'nuranis-block_2',
          'region' => 'right',
          'weight' => 0,
        ),
        'boxes-discussion_info' => array(
          'module' => 'boxes',
          'delta' => 'discussion_info',
          'region' => 'right',
          'weight' => 1,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Discussion page');
  t('nurani');

  $export['discussion'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'general';
  $context->description = 'General blocks for all pages';
  $context->tag = 'nurani';
  $context->conditions = array(
    'user' => array(
      'values' => array(
        'authenticated user' => 'authenticated user',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'menu-primary-links' => array(
          'module' => 'menu',
          'delta' => 'primary-links',
          'region' => 'header',
          'weight' => 0,
        ),
        'menu-secondary-links' => array(
          'module' => 'menu',
          'delta' => 'secondary-links',
          'region' => 'footer_block',
          'weight' => 0,
        ),
        'locale-0' => array(
          'module' => 'locale',
          'delta' => 0,
          'region' => 'top_strip',
          'weight' => 0,
        ),
        'boxes-action_links' => array(
          'module' => 'boxes',
          'delta' => 'action_links',
          'region' => 'top_strip',
          'weight' => 1,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('General blocks for all pages');
  t('nurani');

  $export['general'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'glossary';
  $context->description = 'List of glossary terms and their translations';
  $context->tag = 'nurani';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'glossary_terms:page_1' => 'glossary_terms:page_1',
      ),
    ),
  );
  $context->reactions = array();
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('List of glossary terms and their translations');
  t('nurani');

  $export['glossary'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'login';
  $context->description = 'Login page';
  $context->tag = 'nurani';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'user' => 'user',
        'user/login' => 'user/login',
        'user/password' => 'user/password',
      ),
    ),
    'user' => array(
      'values' => array(
        'anonymous user' => 'anonymous user',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'boxes-login_title' => array(
          'module' => 'boxes',
          'delta' => 'login_title',
          'region' => 'content_top',
          'weight' => 0,
        ),
        'boxes-login_footer' => array(
          'module' => 'boxes',
          'delta' => 'login_footer',
          'region' => 'content_bottom',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Login page');
  t('nurani');

  $export['login'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'overview';
  $context->description = 'Discussions overview';
  $context->tag = 'nurani';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'discussions:page_1' => 'discussions:page_1',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'boxes-welcome_box' => array(
          'module' => 'boxes',
          'delta' => 'welcome_box',
          'region' => 'content_top',
          'weight' => 0,
        ),
        'views-discussion_texts-block_1' => array(
          'module' => 'views',
          'delta' => 'discussion_texts-block_1',
          'region' => 'content_top',
          'weight' => 1,
        ),
        'views-nuranis-block_1' => array(
          'module' => 'views',
          'delta' => 'nuranis-block_1',
          'region' => 'right',
          'weight' => 0,
        ),
        'views-new_glossary_terms-block_1' => array(
          'module' => 'views',
          'delta' => 'new_glossary_terms-block_1',
          'region' => 'right',
          'weight' => 1,
        ),
        'views-new_texts-block_1' => array(
          'module' => 'views',
          'delta' => 'new_texts-block_1',
          'region' => 'right',
          'weight' => 2,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Discussions overview');
  t('nurani');

  $export['overview'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'texts';
  $context->description = 'Texts page';
  $context->tag = 'nurani';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'texts:page_1' => 'texts:page_1',
      ),
    ),
  );
  $context->reactions = array();
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Texts page');
  t('nurani');

  $export['texts'] = $context;
  return $export;
}
