<?php

/**
 * Rules action callback
 *
 * This action will unset a DS/ND field from the node object so it won't be displayed.
 *
 * @param $node
 *   The active node.
 * @param $settings
 *   An array of configuration set in the action callback form.
 */
function nd_rules_disable_fields($node, $settings) {
  $ds_fields = ds_get_fields('nd', $node->type, $node->build_mode);
  $key = $settings['disable_this_field'];
  $key_rendered = $key . '_rendered';

  $field = $ds_fields[$settings['disable_this_field']];

  switch ($field['type']) {
    case DS_FIELD_TYPE_PREPROCESS:
    case DS_FIELD_TYPE_IGNORE:
      unset($node->{$key});
      break;
    case DS_FIELD_TYPE_CODE:
    case DS_FIELD_TYPE_BLOCK:
    case DS_FIELD_TYPE_FUNCTION:
    case DS_FIELD_TYPE_THEME:
      unset($node->{$key_rendered});
      break;
  }
}

/**
 * Rules action callback form.
 *
 * The administration form. Select which DS/ND field you want to omit from display.
 * Does not take build modes into account.
 *
 * @param $settings
 *   The settings array
 * @param $form
 *   The form array
 */
function nd_rules_disable_fields_form($settings, &$form) {
  $fields = array();
  $build_modes = ds_get_build_modes('nd');
  $types = node_get_types();
  foreach (array_keys($types) as $type) {
    foreach (array_keys($build_modes) as $build_mode) {
      $ds_fields = ds_get_fields('nd', $type, $build_mode);
      $values = array_keys($ds_fields);
      $fields[$type] = array_combine($values, $values);
    }
  }

  $settings += array('disable_this_field' => array());
  $form['settings']['disable_this_field'] = array(
    '#type' => 'select',
    '#title' => t('Disable this field'),
    '#options' => $fields,
    '#default_value' => $settings['disable_this_field'],
  );
}