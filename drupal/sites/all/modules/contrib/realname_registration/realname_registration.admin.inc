<?php
/**
 * @file
 * Admin page callbacks for the realname_registration module.
 *
 */

/**
 * Form builder;
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function realname_registration_settings_form() {
  $form = array();

  if (!module_exists('profile2')) {
    variable_del('realname_registration_use_profile2_firstname_field');
    variable_del('realname_registration_profile2_firstname_field_profile_name');
    variable_del('realname_registration_use_profile2_middlename_field');
    variable_del('realname_registration_profile2_middlename_field_profile_name');
    variable_del('realname_registration_use_profile2_lastname_field');
    variable_del('realname_registration_profile2_lastname_field_profile_name');
  }

  $field_req = '
<ul>
  <li>' . t('The field name is correct and represents an existing field') . '</li>
  <li>' . t('The field is associated with the') . ' <em>' . t('user or profile2') . '</em> ' . t('entity') . '</li>
  <li>' . t('The field is required and displays on the registration form') . '</li>
</ul>
';

  $form['fields'] = array(
    '#type' => 'fieldset',
    '#title' => t('Realname registration fields'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['fields']['firstname'] = array(
    '#type' => 'fieldset',
    '#title' => t('First name field'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['fields']['firstname']['realname_registration_firstname_field'] = array(
    '#type' => 'textfield',
    '#title' => t('First name field'),
    '#default_value' => variable_get('realname_registration_firstname_field'),
    '#description' => t('The name of your first name field. Ensure that:') . $field_req,
    '#required' => TRUE,
  );

  if (module_exists('profile2')) {
    $form['fields']['firstname']['profile2_firstname'] = array(
      '#type' => 'fieldset',
      '#title' => t('Profile2 first name'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );

    $form['fields']['firstname']['profile2_firstname']['realname_registration_use_profile2_firstname_field'] = array(
        '#type' => 'checkbox',
        '#title' => t('Use the profile2 module to store your first names.'),
        '#default_value' => variable_get('realname_registration_use_profile2_firstname_field'),
        '#description' => t('When this checkbox is checked, Realname registration will use profile2 fields to store first names.'),
    );
    $form['fields']['firstname']['profile2_firstname']['realname_registration_profile2_firstname_field_profile_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Profile2 type'),
      '#default_value' => variable_get('realname_registration_profile2_firstname_field_profile_name'),
      '#description' => t('Provide the profile2 machine name that will be used during registration.'),
    );
  }

  $form['fields']['middlename'] = array(
    '#type' => 'fieldset',
    '#title' => t('Middle name field'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['fields']['middlename']['realname_registration_middlename_field'] = array(
    '#type' => 'textfield',
    '#title' => t('Middle name field'),
    '#default_value' => variable_get('realname_registration_middlename_field'),
    '#description' => 
      t('The name of your middle name field. Ensure that:')
      . '<ul>'
      . '<li>' . t('The field name is correct and represents an existing field') . '</li>'
      . '<li>' . t('The field is associated with the') . ' <em>' . t('user') . '</em> ' . t('entity') . '</li>'
      . '</ul>',
  );

  if (module_exists('profile2')) {
    $form['fields']['middlename']['profile2_middlename'] = array(
      '#type' => 'fieldset',
      '#title' => t('Profile2 middle name'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['fields']['middlename']['profile2_middlename']['realname_registration_use_profile2_middlename_field'] = array(
        '#type' => 'checkbox',
        '#title' => t('Use the profile2 module to store your middle names.'),
        '#default_value' => variable_get('realname_registration_use_profile2_middlename_field'),
        '#description' => t('When this checkbox is checked, Realname registration will use profile2 fields to store middle names.'),
    );
    $form['fields']['middlename']['profile2_middlename']['realname_registration_profile2_middlename_field_profile_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Profile2 type'),
      '#default_value' => variable_get('realname_registration_profile2_middlename_field_profile_name'),
      '#description' => t('Provide the profile2 machine name that will be used during registration.'),
    );
  }

  $form['fields']['lastname'] = array(
    '#type' => 'fieldset',
    '#title' => t('Last name field'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['fields']['lastname']['realname_registration_lastname_field'] = array(
    '#type' => 'textfield',
    '#title' => t('Last name field'),
    '#default_value' => variable_get('realname_registration_lastname_field'),
    '#description' => t('The name of your last name field. Ensure that:') . $field_req,
    '#required' => TRUE,
  );

  if (module_exists('profile2')) {
    $form['fields']['lastname']['profile2_lastname'] = array(
      '#type' => 'fieldset',
      '#title' => t('Profile2 last name'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );

    $form['fields']['lastname']['profile2_lastname']['realname_registration_use_profile2_lastname_field'] = array(
        '#type' => 'checkbox',
        '#title' => t('Use the profile2 module to store your last names.'),
        '#default_value' => variable_get('realname_registration_use_profile2_lastname_field'),
        '#description' => t('When this checkbox is checked, Realname registration will use profile2 fields to store last names.'),
    );
    $form['fields']['lastname']['profile2_lastname']['realname_registration_profile2_lastname_field_profile_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Profile2 type'),
      '#default_value' => variable_get('realname_registration_profile2_lastname_field_profile_name'),
      '#description' => t('Provide the profile2 machine name that will be used during registration.'),
    );
  }

  $form['fields']['realname_registration_ucfirst'] = array(
    '#type' => 'checkbox',
    '#title' => t('Force the first letters of the first, middle, and last names to uppercase'),
    '#default_value' => variable_get('realname_registration_ucfirst', TRUE),
    '#description' => t('Ensures that the first letter of the users first name, middle name, and last name are capitalized.'),
  );

  $form['username_format'] = array(
    '#type' => 'fieldset',
    '#title' => t('Realname registration username creation'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['username_format']['realname_registration_format'] = array(
    '#type' => 'radios',
    '#title' => t('Username format'),
    '#description' => t('Select the format in which Realname registration will create new usernames.'),
    '#default_value' => variable_get('realname_registration_format', 0),
    '#options' => array(
      t('First name and last name (e.g., John Smith)'),
      t('First initial and last name (e.g., JSmith)'),
      t('First name, middle name, and last name (e.g., John Jacob Smith)'),
      t('First name, middle initial, and last name (e.g., John J Smith)'),
      t('First initial, middle initial, and last name (e.g., JJSmith)'),
      t('First name and last name without spaces (e.g., JohnSmith)'),
      t('First name, middle name, and last name without spaces (e.g., JohnJacobSmith)'),
      t('First name, middle initial, and last name without spaces (e.g., JohnJSmith)')
    ),
    '#required' => TRUE,
  );

  $form['username_format']['realname_registration_tolower'] = array(
    '#type' => 'checkbox',
    '#title' => t('Force lowercase'),
    '#default_value' => variable_get('realname_registration_tolower', TRUE),
    '#description' => t('Usernames will be created using only lowercase characters.'),
  );

  $form['username_format']['realname_registration_use_validation'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use Realname registration validation'),
    '#default_value' => variable_get('realname_registration_use_validation', TRUE),
    '#description' => t('Use regex to validate real names.'),
  );

  $form['#validate'][] = 'realname_registration_settings_validate';
  return system_settings_form($form);
}

function realname_registration_settings_validate($form, &$form_state) {
  $err_pretext      = t('The field name') . ', <em>';
  $err_req          = '</em>, ' . t("you've provided must be required.");
  $err_unknown      = '</em>, ' . t("you've provided either does not exist or is not associated with the corresponding entity.");
  $err_textfield    = '</em>, ' . t("must use textfield widget.");
  $err_register     = '</em>, ' . t("must be displayed on the registration form.") . '<em>';
  $err_profile2_req = t("You must specify a profile2 machine name for the field,") . ' <em>';

  // If we are told to use profile2 fields to store values, we need to know which profile2 type.
  if (module_exists('profile2')) {
    if ($form_state['values']['realname_registration_use_profile2_firstname_field'] && empty($form_state['values']['realname_registration_profile2_firstname_field_profile_name'])) {
      form_set_error('realname_registration_profile2_firstname_field_profile_name', $err_profile2_req . $form_state['values']['realname_registration_firstname_field'] . '</em>');
    }
    if ($form_state['values']['realname_registration_use_profile2_middlename_field'] && empty($form_state['values']['realname_registration_profile2_middlename_field_profile_name'])) {
      form_set_error('realname_registration_profile2_middlename_field_profile_name', $err_profile2_req . $form_state['values']['realname_registration_middlename_field'] . '</em>');
    }
    if ($form_state['values']['realname_registration_use_profile2_lastname_field'] && empty($form_state['values']['realname_registration_profile2_lastname_field_profile_name'])) {
      form_set_error('realname_registration_profile2_lastname_field_profile_name', $err_profile2_req . $form_state['values']['realname_registration_firstname_field'] . '</em>');
    }
  }

  // Validate the first name field.
  if (module_exists('profile2') && $form_state['values']['realname_registration_use_profile2_firstname_field']) {
    $firstname_field = field_info_field($form_state['values']['realname_registration_firstname_field']);
    $match = FALSE;
    foreach (profile2_get_types() as $type_name => $profile_type) {
      if ($profile_type->data['registration'] && is_array($firstname_field['bundles']['profile2'])) {
        foreach ($firstname_field['bundles']['profile2'] as $key => $value) {
          if ($value == $profile_type->type) {
            $match = TRUE;
          }
        }
      }
    }
    if (!$match) {
      form_set_error('realname_registration_firstname_field', $err_pretext . $form_state['values']['realname_registration_firstname_field'] . $err_register );
    }
  }

  if (module_exists('profile2') && $form_state['values']['realname_registration_use_profile2_firstname_field']) {
    $firstname_instance = field_info_instance('profile2', $form_state['values']['realname_registration_firstname_field'], $form_state['values']['realname_registration_profile2_firstname_field_profile_name']);
  }
  else {
    $firstname_instance = field_info_instance('user', $form_state['values']['realname_registration_firstname_field'], 'user');
  }
  if (!isset($firstname_instance)) {
    form_set_error('realname_registration_firstname_field', $err_pretext . $form_state['values']['realname_registration_firstname_field'] . $err_unknown);
  }
  if ($firstname_instance['widget']['type'] != 'text_textfield') {
    form_set_error('realname_registration_firstname_field', $err_pretext . $form_state['values']['realname_registration_firstname_field'] . $err_textfield);
  }
  if ($firstname_instance['required'] != 1) {
    form_set_error('realname_registration_firstname_field', $err_pretext . $form_state['values']['realname_registration_firstname_field'] . $err_req);
  }

  // Validate the middle name field if it is used.
  if (module_exists('profile2') && $form_state['values']['realname_registration_use_profile2_middlename_field']) {
    $middlename_field = field_info_field($form_state['values']['realname_registration_middlename_field']);
    $match = FALSE;
    foreach (profile2_get_types() as $type_name => $profile_type) {
      if ($profile_type->data['registration'] && is_array($middlename_field['bundles']['profile2'])) {
        foreach ($middlename_field['bundles']['profile2'] as $key => $value) {
          if ($value == $profile_type->type) {
            $match = TRUE;
          }
        }
      }
    }
    if (!$match) {
      form_set_error('realname_registration_middlename_field', $err_pretext . $form_state['values']['realname_registration_middlename_field'] . $err_register);
    }
  }

  if (!empty($form_state['values']['realname_registration_middlename_field'])) {
    if (module_exists('profile2') && $form_state['values']['realname_registration_use_profile2_middlename_field']) {
      $middlename_instance = field_info_instance('profile2', $form_state['values']['realname_registration_middlename_field'], $form_state['values']['realname_registration_profile2_middlename_field_profile_name']);
    }
    else {
      $middlename_instance = field_info_instance('user', $form_state['values']['realname_registration_middlename_field'], 'user');
    }
    if (!isset($middlename_instance)) {
      form_set_error('realname_registration_middlename_field', $err_pretext . $form_state['values']['realname_registration_middlename_field'] . $err_unknown);
    }
    if ($middlename_instance['widget']['type'] != 'text_textfield') {
      form_set_error('realname_registration_middlename_field', $err_pretext . $form_state['values']['realname_registration_middlename_field'] . $err_textfield);
    }
  }
  else {
    // If there is no middle name field provided, we can't base usernames off the middle initial.
    if ($form_state['values']['realname_registration_format'] == 2 || $form_state['values']['realname_registration_format'] == 3) {
      form_set_error('realname_registration_format', t('A valid middle name field is required for this username format.'));
    }
  }

  // Validate the last name field.
  if (module_exists('profile2') && $form_state['values']['realname_registration_use_profile2_lastname_field']) {
    $lastname_field = field_info_field($form_state['values']['realname_registration_lastname_field']);
    $match = FALSE;
    foreach (profile2_get_types() as $type_name => $profile_type) {
      if ($profile_type->data['registration'] && is_array($lastname_field['bundles']['profile2'])) {
        foreach ($lastname_field['bundles']['profile2'] as $key => $value) {
          if ($value == $profile_type->type) {
            $match = TRUE;
          }
        }
      }
    }
    if (!$match) {
      form_set_error('realname_registration_lastname_field', $err_pretext . $form_state['values']['realname_registration_lastname_field'] . $err_register);
    }
  }

  if (module_exists('profile2') && $form_state['values']['realname_registration_use_profile2_lastname_field']) {
    $lastname_instance = field_info_instance('profile2', $form_state['values']['realname_registration_lastname_field'], $form_state['values']['realname_registration_profile2_lastname_field_profile_name']);
  }
  else {
    $lastname_instance = field_info_instance('user', $form_state['values']['realname_registration_lastname_field'], 'user');
  }
  if (!isset($lastname_instance)) {
    form_set_error('realname_registration_lastname_field', $err_pretext . $form_state['values']['realname_registration_lastname_field'] . $err_unknown);
  }
  if ($lastname_instance['widget']['type'] != 'text_textfield') {
    form_set_error('realname_registration_lastname_field', $err_pretext . $form_state['values']['realname_registration_lastname_field'] . $err_textfield);
  }
  if ($lastname_instance['required'] != 1) {
    form_set_error('realname_registration_lastname_field', $err_pretext . $form_state['values']['realname_registration_lastname_field'] . $err_req);
  }
}