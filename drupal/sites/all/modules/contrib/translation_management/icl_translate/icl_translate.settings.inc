<?php

module_load_include('inc', 'icl_content', 'icl_content.settings' );

function icl_translate_admin_settings() {
  $form = array();
  if (module_exists('icl_content')) {
    $form = icl_content_admin_settings();
  }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 9999
  );
  return $form;
}

function icl_translate_admin_settings_submit($form_id, $form_values) {
  system_settings_form_submit($form_id, $form_values);
}