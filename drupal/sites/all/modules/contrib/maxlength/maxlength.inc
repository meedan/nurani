<?php
/**
 * @file
 *   Business logic for maxlength
 */

function _maxlength_content_form_alter(&$form, &$form_state, $form_id) {
  $type = $form['type']['#value'];
  // update the title as needed
  if (isset($form['title']) && ($values = maxlength_get_values('title', $type))) {
    $form['title']['#max_length_properties'] = $values;
  }

  // Update the body as needed
  if (isset($form['body_field']['body']) && ($values = maxlength_get_values('body', $type))) {
    $form['body_field']['body']['#max_length_properties'] = $values;
  }


  if (module_exists('content')) {
    // Get a list of all the CCK fields for this content type
    $info = content_types($type);
    $list = array_keys($info['fields']);

    // Update CCK fields as needed
    foreach ($list as $field) {
      if (isset($form[$field])) {
        foreach (element_children($form[$field]) as $key) {
          // For example #markup doens't have a #type element.
          if (!empty($form[$field][$key]['#type']) && _maxlength_is_supported_widget($form[$field][$key]['#type'])) {
            if ($values = maxlength_get_values($field, $type)) {
              $form[$field][$key]['#max_length_properties'] = $values;
            }
          }
        }
      }
    }
  }
}

function _maxlength_comment_form_alter(&$form, &$form_state, $form_id) {
  $node = node_load($form['nid']['#value']);
  $type = $node->type;
  // Add a max length formatter to the comment subject and body.
  if (isset($form['subject']) && ($values = maxlength_get_values('comment_subject', $type))) {
    $form['subject']['#max_length_properties'] = $values;
  }

  if (isset($form['comment_filter']['comment']) && ($values = maxlength_get_values('comment_comment', $type))) {
    $form['comment_filter']['comment']['#max_length_properties'] = $values;
  }
}

/**
 * Decides if the given widget is supported or not
 *
 * @param
 *   Widget machine-readable name
 * @return
 *   TRUE if supported, FALSE if not
 */
function _maxlength_is_supported_widget($widget) {
  $supported = array(
    'text_textfield',
    'text_textarea',
  );
  return in_array($widget, $supported);
}

/**
 * Editing a Content Type.
 *
 * Provide the fields for the user to choose maxlength settings on:
 * Title
 * Body
 * Comment Title
 * Comment Body
*/
function _maxlength_content_type_form_alter(&$form, &$form_state, $form_id) {
  $type = $form['#node_type']->type;

  $labels = array(
    'title' => array('parent_form' => 'submission', 'weight' => '-3'),
    'body' => array('parent_form' => 'submission', 'weight' => '-1'),
    'comment_subject' => array('parent_form' => 'comment', 'weight' => '-1'),
    'comment_comment' => array('parent_form' => 'comment', 'weight' => '0'),
  );

  foreach ($labels as $label => $options) {
    $parent_form = $options['parent_form'];
    $weight = $options['weight'];

    if ($parent_form == 'submission') {
      // Ensure that the "limit title length" / "limit body length" fieldsets we create 
      // are placed directly beneath the "title field label" / "body field label" form elements.
      $form[$parent_form][$label .'_label']['#weight'] = $weight - 1;
    }

    $form[$parent_form]['maxlength_' . $label]['maxlength_' . $label] = array(
      '#type' => 'fieldset',
      '#weight' => $weight,
      '#title' => t('Limit !type  length', array('!type ' => $label)),
      '#title' => t('Limit !type  length', array('!type ' => $label)),
      '#collapsible' => TRUE,
      '#collapsed' => strlen(variable_get($type .'_'. $label, '')) == 0,
    );

    $form[$parent_form]['maxlength_' . $label]['maxlength_' . $label] = array(
      '#type' => 'textfield',
      '#title' => t('!label max length', array('!label' => ucwords($label))),
      '#field_suffix' => t('characters'),
      '#return_value' => 1,
      '#size' => 4,
      '#default_value' => variable_get('maxlength_' . $label .'_'. $type, MAXLENGTH_DEFAULT_LENGTH),
      '#description' => t('Maximum number of characters allowed for the !type field of this content type. Leave blank for an unlimited size.', array('!type' => $label)) .'<br/>'.
      '<b>'. t('Please remember, it counts all characters, including HTML, so may not work as expected with rich text editors e.g. FCKeditor / tinyMCE.') .'</b>',
    );
    $form[$parent_form]['maxlength_' . $label]['maxlength_' . $label .'_js'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable remaining characters countdown for the !label', array('!label' => ucwords($label))),
      '#default_value' => variable_get('maxlength_' . $label .'_js_'. $type, MAXLENGTH_DEFAULT_USE_JS),
      '#description' => t('This will enable a Javascript based count down, as well as the client side validation for the !type field of this content type. If no limit set this is ignored.', array('!type' => $label)),
    );
    $form[$parent_form]['maxlength_' . $label]['maxlength_' . $label .'_text'] = array(
      '#type' => 'textarea',
      '#title' => t('!label count down message', array('!label' => ucwords($label))),
      '#default_value' => variable_get('maxlength_' . $label .'_text_'. $type, MAXLENGTH_DEFAULT_TEXT),
      '#description' => t('The text used in the Javascript message under the !type input, where "!limit", "!remaining" and "!count" are replaced by the appropriate numbers.', array('!type' => $label)),
    );
  }
}

function _maxlength_cck_form_alter(&$form, &$form_state, $form_id) {
  $form['field']['maxlength_' . $form['field_name']['#value'] . '_length'] = array(
    '#type' => 'textfield',
    '#title' => t('Maxlength limit'),
    '#description' => t('If you want to use maxlength interactive counter and validation on a CCK field, let\'s leave the normal CCK length unlimited and set this value to the desired one to let maxlength count the real length of the text'),
    '#max_length_properties' => 6,
    '#default_value' => variable_get('maxlength_' . $form['field_name']['#value'], MAXLENGTH_DEFAULT_LENGTH),
  );
  $form['field']['maxlength_' . $form['field_name']['#value'] .'_js'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable remaining characters countdown for this field'),
    '#default_value' => variable_get('maxlength_' . $form['field_name']['#value'] .'_js', MAXLENGTH_DEFAULT_USE_JS),
    '#description' => t('This will enable a Javascript based count down, as well as the client side validation for this field. If no limit set this is ignored.'),
  );
  $form['field']['maxlength_' . $form['field_name']['#value'] .'_text'] = array(
    '#type' => 'textarea',
    '#title' => t('Count down message'),
    '#default_value' => variable_get('maxlength_' . $form['field_name']['#value'] .'_text', MAXLENGTH_DEFAULT_TEXT),
    '#description' => t('The text used in the Javascript message under the input, where "!limit", "!remaining" and "!count" are replaced by the appropriate numbers.'),
  );
  $form['#submit'][] = '_maxlength_cck_form_submit';
}

function _maxlength_cck_form_submit($form, &$form_state) {
  //note, max lenght for the CCK field is stored in this way as for textareas, its not in $element var passed to theme functions.
  variable_set('maxlength_' . $form['field_name']['#value'], $form['#post']['maxlength_' . $form['field_name']['#value'] .'_length']);
  variable_set('maxlength_' . $form['field_name']['#value'] .'_js', $form['#post']['maxlength_' . $form['field_name']['#value'] .'_js']);
  variable_set('maxlength_' . $form['field_name']['#value'] .'_text', $form['#post']['maxlength_' . $form['field_name']['#value'] .'_text']);
}

/**
 * Load maxlength settings for a certain fieldtype.
 *
 * @param $field
 *    The field from which the maxlength settings should be loaded.
 * @param $type
 *    The nodetype which is used for loading the settings.
 *
 * @return
 *    The settings for a certain field.
 */
function maxlength_get_values($field = 'body', $type = '') {
  $values = array();
  $values['limit'] = FALSE;

  // CCK fields
  if (strpos($field, 'field_') === 0) {
    $values['limit'] = variable_get('maxlength_' . $field, MAXLENGTH_DEFAULT_LENGTH);
    $values['use_js'] = variable_get('maxlength_' . $field .'_js', MAXLENGTH_DEFAULT_USE_JS);
    $values['text'] = variable_get('maxlength_' . $field .'_text', MAXLENGTH_DEFAULT_TEXT);
    $values['key'] = 'value';
  }
  // Values per nodetype.
  elseif ($type != '') {
    $values['limit'] = variable_get('maxlength_' . $field .'_'. $type, MAXLENGTH_DEFAULT_LENGTH);
    $values['use_js'] = variable_get('maxlength_' . $field .'_js_'. $type, MAXLENGTH_DEFAULT_USE_JS);
    $values['text'] = variable_get('maxlength_' . $field .'_text_'. $type, MAXLENGTH_DEFAULT_TEXT);
  }
  // Values for other fields
  else {
    $values['limit'] = variable_get('maxlength_' . $field, MAXLENGTH_DEFAULT_LENGTH);
    $values['use_js'] = variable_get('maxlength_' . $field .'_js', MAXLENGTH_DEFAULT_USE_JS);
    $values['text'] = variable_get('maxlength_' . $field .'_text', MAXLENGTH_DEFAULT_TEXT);
  }

  if ($values['limit']) {
    return $values;
  }
  else {
    return FALSE;
  }
}

