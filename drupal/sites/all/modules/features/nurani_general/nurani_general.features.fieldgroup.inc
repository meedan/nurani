<?php

/**
 * Implementation of hook_fieldgroup_default_groups().
 */
function nurani_general_fieldgroup_default_groups() {
  $groups = array();

  // Exported group: group_translations
  $groups['term-group_translations'] = array(
    'group_type' => 'multigroup',
    'type_name' => 'term',
    'group_name' => 'group_translations',
    'parent' => '',
    'label' => 'Translations',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'weight' => '-2',
        'parent' => '',
        'full' => array(
          'format' => 'simple',
          'exclude' => 0,
        ),
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'sticky' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'settings' => array(),
        'label' => 'above',
        'description' => '',
        'text_summary' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'discussion_participants' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
      ),
      'multigroup' => array(
        'multiple-columns' => 0,
        'required' => 0,
        'multiple' => '1',
        'labels' => array(
          '0' => '',
          '1' => '',
          '2' => '',
          '3' => '',
          '4' => '',
          '5' => '',
          '6' => '',
          '7' => '',
          '8' => '',
          '9' => '',
        ),
        'subgroup' => array(
          'weight' => -20,
          'teaser' => array(
            'format' => 'fieldset',
            'exclude' => 0,
          ),
          'full' => array(
            'format' => 'fieldset',
            'exclude' => 0,
          ),
          '4' => array(
            'format' => 'fieldset',
            'exclude' => 0,
          ),
          '2' => array(
            'format' => 'fieldset',
            'exclude' => 0,
          ),
          '3' => array(
            'format' => 'fieldset',
            'exclude' => 0,
          ),
          'sticky' => array(
            'format' => 'fieldset',
            'exclude' => 0,
          ),
          'text_summary' => array(
            'format' => 'fieldset',
            'exclude' => 0,
          ),
          'discussion_participants' => array(
            'format' => 'fieldset',
            'exclude' => 0,
          ),
          'token' => array(
            'format' => 'fieldset',
            'exclude' => 0,
          ),
        ),
      ),
    ),
    'weight' => '-2',
    'fields' => array(
      '0' => 'field_translation_term',
      '1' => 'field_translation_context',
    ),
    'depth' => 0,
    'parents' => array(
      '0' => '',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Translations');

  return $groups;
}
