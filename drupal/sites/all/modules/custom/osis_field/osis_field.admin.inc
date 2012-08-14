<?php

/**
 * OSIS Field administrative form for managing texts.
 */
function osis_field_texts_form($form, &$form_state) {
  drupal_add_js(drupal_get_path('module', 'osis_field') . '/osis_field.js');

  $form['texts'] = array(
    '#type' => 'fieldset',
    '#title' => t('Texts'),
    '#collapsible' => FALSE,
    'table' => array(
      '#tree' => TRUE,
      '#theme' => 'osis_field_texts_form_table',
    )
  );
  $row = 0;
  $type_options = osis_field_text_type_options();
  foreach (osis_field_texts() as $text) {
    $form['texts'][$row] = array(
      '#text' => $text,
    );

    foreach ($text as $col => $value) {
      switch ($col) {
        case 'type':
          $form['texts']['table'][$row][$col] = array(
            '#type' => 'select',
            '#title' => $col,
            '#default_value' => $value,
            '#options' => $type_options,
          );
          break;

        default: 
          $form['texts']['table'][$row][$col] = array(
            '#type' => 'textfield',
            '#title' => $col,
            '#size' => 16,
            '#maxlength' => 64,
            '#default_value' => $value,
            '#disabled' => ($col == 'machine_name'),
          );
          break;
      }

      $form['texts']['table'][$row][$col]['#required'] = TRUE;
    }

    $form['texts']['table'][$row]['actions'] = array(
      'delete' => array(
        '#type' => 'button',
        '#value' => t('Delete'),
        '#attributes' => array('data-machine_name' => $text->machine_name, 'class' => array('delete-action')),
      ),
    );

    $row += 1;
  }

  $form['texts']['add'] = array(
    '#type' => 'button',
    '#value' => t('New text'),
    '#attributes' => array('class' => array('add-action')),
  );

  return $form;
}

/**
 * Theme function to render the form elements for each Text as a table.
 */
function theme_osis_field_texts_form_table(&$variables) {
  $output = '';

  $rows = array();
  $header = array();
  $element = &$variables['element'];

  foreach (element_children($element) as $row) {
    foreach (element_children($element[$row]) as $col) {
      if ($row == 0) {
        $header[] = $col;
      }

      unset($element[$row][$col]['#title']);

      $rows[$row][] = drupal_render($element[$row][$col]);
    }
  }

  drupal_add_css(drupal_get_path('module', 'osis_field') . '/osis_field.css');
  return theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('class' => array('osis-field-texts-form-table'))));
}
