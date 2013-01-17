<?php
/**
 * @file
 * Token callbacks for the realname_registration module.
 */

/**
 * Implements hook_token_info().
 */
function realname_registration_token_info() {
  $user['first-name'] = array(
    'name' => t('First name'),
    'description' => t("The first name of the user."),
  );
  $user['middle-name'] = array(
    'name' => t('Middle name'),
    'description' => t("The middle name of the user."),
  );
  $user['last-name'] = array(
    'name' => t('Last name'),
    'description' => t("The last name of the user."),
  );
  $user['first-initial'] = array(
    'name' => t('First inital'),
    'description' => t("The first initial of the user."),
  );
  $user['middle-initial'] = array(
    'name' => t('Middle inital'),
    'description' => t("The middle initial of the user."),
  );
  $user['last-initial'] = array(
    'name' => t('Last initial'),
    'description' => t("The last initial of the user."),
  );
  return array( 'tokens' => array('user' => $user) );
}

/**
 * Implements hook_tokens().
 */
function realname_registration_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $sanitize = !empty($options['sanitize']);
  $replacements = array();

  $field_firstname = variable_get('realname_registration_firstname_field');
  $field_middlename = variable_get('realname_registration_middlename_field');
  $field_lastname = variable_get('realname_registration_lastname_field');

  $field_firstname_profile_type = variable_get('realname_registration_profile2_firstname_field_profile_name');
  $field_middlename_profile_type = variable_get('realname_registration_profile2_middlename_field_profile_name');
  $field_lastname_profile_type = variable_get('realname_registration_profile2_lastname_field_profile_name');

  if (isset($field_firstname) && isset($field_lastname)) {
    if ($type == 'user' && !empty($data['user'])) {
      $account = $data['user'];
      foreach ($tokens as $name => $original) {
        switch ($name) {
          case 'first-name':
            if (variable_get('realname_registration_use_profile2_firstname_field')) {
              $result = db_query('SELECT p.pid FROM {profile} AS p WHERE p.uid = :uid AND p.type = :type', array(':uid' => $account->uid, ':type' => $field_firstname_profile_type));
              foreach ($result as $record) {
                $profile2_firstname = profile2_load($record->pid);
              }
              if (!empty($profile2_firstname->$field_firstname)) {
                $replacements[$original] = $sanitize ? check_plain($profile2_firstname->{$field_firstname}['und']['0']['value']) : $profile2_firstname->{$field_firstname}['und']['0']['value'];
              }
              else {
                $replacements[$original] =  '';
              }
            }
            else {
              if (!empty($account->$field_firstname)) {
                $replacements[$original] = $sanitize ? check_plain($account->{$field_firstname}['und']['0']['value']) : $account->{$field_firstname}['und']['0']['value'];
              }
              else {
                $replacements[$original] = '';
              }
            }
            break;

          case 'middle-name':
            if (variable_get('realname_registration_use_profile2_middlename_field')) {
              $result = db_query('SELECT p.pid FROM {profile} AS p WHERE p.uid = :uid AND p.type = :type', array(':uid' => $account->uid, ':type' => $field_middlename_profile_type));
              foreach ($result as $record) {
                $profile2_middlename = profile2_load($record->pid);
              }
              if (!empty($profile2_middlename->$field_middlename)) {
                $replacements[$original] = $sanitize ? check_plain($profile2_middlename->{$field_middlename}['und']['0']['value']) : $profile2_middlename->{$field_middlename}['und']['0']['value'];
              }
              else {
                $replacements[$original] = '';
              }
            }
            else {
              if (!empty($account->$field_middlename)) {
                $replacements[$original] = $sanitize ? check_plain($account->{$field_middlename}['und']['0']['value']) : $account->{$field_middlename}['und']['0']['value'];
              }
              else {
                $replacements[$original] = '';
              }
            }
            break;

          case 'last-name':
            if (variable_get('realname_registration_use_profile2_lastname_field')) {
              $result = db_query('SELECT p.pid FROM {profile} AS p WHERE p.uid = :uid AND p.type = :type', array(':uid' => $account->uid, ':type' => $field_lastname_profile_type));
              foreach ($result as $record) {
                $profile2_lastname = profile2_load($record->pid);
              }
              if (!empty($profile2_lastname->$field_lastname)) {
                $replacements[$original] = $sanitize ? check_plain($profile2_lastname->{$field_lastname}['und']['0']['value']) : $profile2_lastname->{$field_lastname}['und']['0']['value'];
              }
              else {
                $replacements[$original] = '';
              }
            }
            else {
              if (!empty($account->$field_lastname)) {
                $replacements[$original] = $sanitize ? check_plain($account->{$field_lastname}['und']['0']['value']) : $account->{$field_lastname}['und']['0']['value'];
              }
              else {
                $replacements[$original] = '';
              }
            }
            break;

          case 'first-initial':
            if (variable_get('realname_registration_use_profile2_firstname_field')) {
              $result = db_query('SELECT p.pid FROM {profile} AS p WHERE p.uid = :uid AND p.type = :type', array(':uid' => $account->uid, ':type' => $field_firstname_profile_type));
              foreach ($result as $record) {
                $profile2_firstname = profile2_load($record->pid);
              }
              if (!empty($profile2_firstname->$field_firstname)) {
                $replacements[$original] = $sanitize ?
                  check_plain(drupal_substr($profile2_firstname->{$field_firstname}['und']['0']['value'], 0, 1)) : drupal_substr($profile2_firstname->{$field_firstname}['und']['0']['value'], 0, 1);
              }
              else {
                $replacements[$original] = '';
              }
            }
            else {
              if (!empty($account->$field_firstname)) {
                $replacements[$original] = $sanitize ?
                  check_plain(drupal_substr($account->{$field_firstname}['und']['0']['value'], 0, 1)) : drupal_substr($account->{$field_firstname}['und']['0']['value'], 0, 1);
              }
              else {
                $replacements[$original] = '';
              }
            }
            break;

          case 'middle-initial':
            if (variable_get('realname_registration_use_profile2_middlename_field')) {
              $result = db_query('SELECT p.pid FROM {profile} AS p WHERE p.uid = :uid AND p.type = :type', array(':uid' => $account->uid, ':type' => $field_middlename_profile_type));
              foreach ($result as $record) {
                $profile2_middlename = profile2_load($record->pid);
              }
              if (!empty($profile2_middlename->$field_middlename)) {
                $replacements[$original] = $sanitize ?
                  check_plain(drupal_substr($profile2_middlename->{$field_middlename}['und']['0']['value'], 0, 1)) : drupal_substr($profile2_middlename->{$field_middlename}['und']['0']['value'], 0, 1);
              }
              else {
                $replacements[$original] = '';
              }
            }
            else {
              if (!empty($account->$field_middlename)) {
                $replacements[$original] = $sanitize ?
                  check_plain(drupal_substr($account->{$field_middlename}['und']['0']['value'], 0, 1)) : drupal_substr($account->{$field_middlename}['und']['0']['value'], 0, 1);
              }
              else {
                $replacements[$original] = '';
              }
            }
            break;

          case 'last-initial':
            if (variable_get('realname_registration_use_profile2_lastname_field')) {
              $result = db_query('SELECT p.pid FROM {profile} AS p WHERE p.uid = :uid AND p.type = :type', array(':uid' => $account->uid, ':type' => $field_lastname_profile_type));
              foreach ($result as $record) {
                $profile2_lastname = profile2_load($record->pid);
              }
              if (!empty($profile2_lastname->$field_lastname)) {
                $replacements[$original] = $sanitize ?
                  check_plain(drupal_substr($profile2_lastname->{$field_lastname}['und']['0']['value'], 0, 1)) : drupal_substr($profile2_lastname->{$field_lastname}['und']['0']['value'], 0, 1);
              }
              else {
                $replacements[$original] = '';
              }
            }
            else {
              if (!empty($account->$field_lastname)) {
                $replacements[$original] = $sanitize ?
                  check_plain(drupal_substr($account->{$field_lastname}['und']['0']['value'], 0, 1)) : drupal_substr($account->{$field_lastname}['und']['0']['value'], 0, 1);
              }
              else {
                $replacements[$original] = '';
              }
            }
            break;
        }
      }
    }
  }

  return $replacements;
}
