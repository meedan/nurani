<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function nurani_general_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "boxes" && $api == "box") {
    return array("version" => 1);
  }
  elseif ($module == "context" && $api == "context") {
    return array("version" => 3);
  }
  elseif ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_imagecache_default_presets().
 */
function nurani_general_imagecache_default_presets() {
  $items = array(
    'thumbnail' => array(
      'presetname' => 'thumbnail',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '85',
            'height' => '85',
          ),
        ),
      ),
    ),
    'thumbnail_view' => array(
      'presetname' => 'thumbnail_view',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '48',
            'height' => '48',
          ),
        ),
      ),
    ),
  );
  return $items;
}

/**
 * Implementation of hook_node_info().
 */
function nurani_general_node_info() {
  $items = array(
    'annotation' => array(
      'name' => t('Annotation'),
      'module' => 'features',
      'description' => t('A comment on a glossary term.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Annotation'),
      'min_word_count' => '0',
      'help' => '',
    ),
    'discussion' => array(
      'name' => t('Discussion'),
      'module' => 'features',
      'description' => t('A scholarly discussion.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Your Thoughts'),
      'min_word_count' => '0',
      'help' => '',
    ),
    'page' => array(
      'name' => t('Page'),
      'module' => 'features',
      'description' => t('A static page.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
    'profile' => array(
      'name' => t('Profile'),
      'module' => 'features',
      'description' => t('A user profile built as content.'),
      'has_title' => '1',
      'title_label' => t('Username'),
      'has_body' => '0',
      'body_label' => '',
      'min_word_count' => '0',
      'help' => '',
    ),
    'response' => array(
      'name' => t('Response'),
      'module' => 'features',
      'description' => t('A comment in a scholarly discussion.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Response'),
      'min_word_count' => '0',
      'help' => '',
    ),
    'term' => array(
      'name' => t('Term'),
      'module' => 'features',
      'description' => t('A glossary term.'),
      'has_title' => '1',
      'title_label' => t('Term'),
      'has_body' => '0',
      'body_label' => '',
      'min_word_count' => '0',
      'help' => '',
    ),
    'text' => array(
      'name' => t('Text'),
      'module' => 'features',
      'description' => t('A scholarly text.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Text Passage'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implementation of hook_views_api().
 */
function nurani_general_views_api() {
  return array(
    'api' => '2',
  );
}
