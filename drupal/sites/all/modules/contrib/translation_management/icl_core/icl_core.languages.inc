<?php

function icl_core_custom_languages_form() {
  $languages = language_list('language', TRUE);
  $icl_names = icl_core_get_icl_language_names();
  
  array_unshift($icl_names, '---');
  
  $form = array();

  $form['lang_options'] = array(
    '#type' => 'value',
    '#value' => $icl_names,
    );
  
  $form['icl_name'] = array('#tree' => TRUE);
  foreach ($languages as $langcode => $language) {
    
    $form['name'][$langcode] = array('#value' => check_plain($language->name));
    $form['native'][$langcode] = array('#value' => check_plain($language->native));
    
    $form['icl_name'][$langcode] = array(
      '#type' => 'select',
      '#options' => $form['lang_options']['#value'],
      );
    
    $current_icl = icl_core_get_language_name($langcode);
    if ($current_icl != NULL) {
      $form['icl_name'][$langcode]['#default_value'] = array_search($current_icl, $icl_names);
    }
  }
  $form['submit'] = array('#type' => 'submit', '#value' => t('Save configuration'));
  $form['#theme'] = 'icl_core_custom_languages_form';

  return $form;  
}

/**
 * Theme the language overview form.
 *
 * @ingroup themeable
 */
function theme_icl_core_custom_languages_form($form) {
  $default = language_default();
  foreach ($form['name'] as $key => $element) {
    // Do not take form control structures.
    if (is_array($element) && element_child($key)) {
      $rows[] = array(
        check_plain($key),
        '<strong>'. drupal_render($form['name'][$key]) .'</strong>',
        drupal_render($form['native'][$key]),
        drupal_render($form['icl_name'][$key]),
      );
    }
  }
  $header = array(array('data' => t('Code')),
                    array('data' => t('English name')),
                    array('data' => t('Native name')),
                    array('data' => t('ICanLocalize name'))
                    );
  $output = _icl_wrapper_theme('table', array('header' => $header, 'rows' => $rows));
  $output .= drupal_render($form);

  return $output;
}

function icl_core_custom_languages_form_submit($form, &$form_state) {
  $languages = language_list();
  foreach ($languages as $langcode => $language) {
    $index = $form_state['values']['icl_name'][$langcode];
    if ($index == 0) {
      _icl_wrapper_db_query( "DELETE FROM {icl_languages} WHERE code = '%s'", $langcode);
    } else {
      $icl_name = $form['lang_options']['#value'][$index];
      $icl_id = icl_core_get_icl_language_id($icl_name);

      // Affected rows change
      $exists = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT icl_name FROM {icl_languages} WHERE code = '%s'", $langcode));

      if ($exists) {
        _icl_wrapper_db_query( "UPDATE {icl_languages} SET icl_name = '%s', icl_id = %d WHERE code = '%s'", $icl_name, $icl_id, $langcode );
      } else {
        _icl_wrapper_db_query( "INSERT INTO {icl_languages} (code, icl_name, icl_id) VALUES('%s', '%s', %d)", $langcode, $icl_name, $icl_id);
      }
    }
  }
  drupal_set_message(t('Configuration saved.'));

  // Changing the language settings impacts the interface.
  cache_clear_all('*', 'cache_page', TRUE);

  $form_state['redirect'] = _icl_wrapper_get_drupal_menu('admin/settings/language/ican_localize');
  return;
}

/**
 * Get the ICanLocalize language names.
 */
 
function icl_core_get_icl_language_names() {
  
  $all_langs = _icl_core_get_all_languages();
  
  $names = array();
  
  foreach ( $all_langs as $lang ) {
    $names[] = $lang['name'];
  }
 
  sort($names);
  
  return $names;
}

function icl_core_get_icl_language_id($name) {
  $all_langs = _icl_core_get_all_languages();
  
  foreach ( $all_langs as $lang ) {
    if ( $lang['name'] == $name ) {
      return $lang['id'];
    }
  }
  
  return 0;
}

