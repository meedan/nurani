<?php
/**
 * @file
 * nurani_accounts.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function nurani_accounts_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_additional_details|user|user|default';
  $field_group->group_name = 'group_additional_details';
  $field_group->entity_type = 'user';
  $field_group->bundle = 'user';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Additional details',
    'weight' => '2',
    'children' => array(
      0 => 'field_how_did_you_hear_about_us',
      1 => 'field_previous_experience',
      2 => 'field_reasons',
      3 => 'field_religious_tradition',
      4 => 'field_social_media_usage',
      5 => 'field_subjects_of_interest',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Additional details',
      'instance_settings' => array(
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_additional_details|user|user|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_additional_details|user|user|form';
  $field_group->group_name = 'group_additional_details';
  $field_group->entity_type = 'user';
  $field_group->bundle = 'user';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Additional details',
    'weight' => '5',
    'children' => array(
      0 => 'field_how_did_you_hear_about_us',
      1 => 'field_previous_experience',
      2 => 'field_reasons',
      3 => 'field_religious_tradition',
      4 => 'field_social_media_usage',
      5 => 'field_subjects_of_interest',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Additional details',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_additional_details|user|user|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_details|user|user|default';
  $field_group->group_name = 'group_details';
  $field_group->entity_type = 'user';
  $field_group->bundle = 'user';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Invitation request details',
    'weight' => '1',
    'children' => array(
      0 => 'field_country',
      1 => 'field_landline_phone',
      2 => 'field_mobile_phone',
      3 => 'field_occupation',
      4 => 'field_post_code',
      5 => 'field_postal_address',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Invitation request details',
      'instance_settings' => array(
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_details|user|user|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_details|user|user|form';
  $field_group->group_name = 'group_details';
  $field_group->entity_type = 'user';
  $field_group->bundle = 'user';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Invitation request details',
    'weight' => '4',
    'children' => array(
      0 => 'field_country',
      1 => 'field_landline_phone',
      2 => 'field_mobile_phone',
      3 => 'field_occupation',
      4 => 'field_post_code',
      5 => 'field_postal_address',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Invitation request details',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_details|user|user|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_name|user|user|default';
  $field_group->group_name = 'group_name';
  $field_group->entity_type = 'user';
  $field_group->bundle = 'user';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_profile';
  $field_group->data = array(
    'label' => 'Name',
    'weight' => '1',
    'children' => array(
      0 => 'field_first_name',
      1 => 'field_last_name',
      2 => 'field_title',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Name',
      'instance_settings' => array(
        'classes' => '',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'none',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_name|user|user|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_name|user|user|tooltip';
  $field_group->group_name = 'group_name';
  $field_group->entity_type = 'user';
  $field_group->bundle = 'user';
  $field_group->mode = 'tooltip';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Name',
    'weight' => '0',
    'children' => array(
      0 => 'field_first_name',
      1 => 'field_last_name',
      2 => 'field_title',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'show_label' => 1,
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
        'classes' => '',
      ),
    ),
  );
  $export['group_name|user|user|tooltip'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_profile|user|user|default';
  $field_group->group_name = 'group_profile';
  $field_group->entity_type = 'user';
  $field_group->bundle = 'user';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Your Nurani profile',
    'weight' => '0',
    'children' => array(
      0 => 'field_date_of_birth',
      1 => 'group_name',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Your Nurani profile',
      'instance_settings' => array(
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_profile|user|user|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_profile|user|user|form';
  $field_group->group_name = 'group_profile';
  $field_group->entity_type = 'user';
  $field_group->bundle = 'user';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Your Nurani profile',
    'weight' => '0',
    'children' => array(
      0 => 'field_date_of_birth',
      1 => 'field_first_name',
      2 => 'field_last_name',
      3 => 'field_title',
      4 => 'field_age',
      5 => 'account',
      6 => 'timezone',
      7 => 'picture',
      8 => 'overlay_control',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Your Nurani profile',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_profile|user|user|form'] = $field_group;

  return $export;
}
