<?php
/**
 * @file
 * nurani_accounts.features.field.inc
 */

/**
 * Implements hook_field_default_fields().
 */
function nurani_accounts_field_default_fields() {
  $fields = array();

  // Exported field: 'user-user-field_country'.
  $fields['user-user-field_country'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_country',
      'foreign keys' => array(),
      'indexes' => array(
        'value' => array(
          0 => 'value',
        ),
      ),
      'locked' => '0',
      'module' => 'list',
      'settings' => array(
        'allowed_values' => array(
          'Andorra' => 'Andorra',
          'United Arab Emirates' => 'United Arab Emirates',
          'Afghanistan' => 'Afghanistan',
          'Antigua and Barbuda' => 'Antigua and Barbuda',
          'Anguilla' => 'Anguilla',
          'Albania' => 'Albania',
          'Armenia' => 'Armenia',
          'Netherlands Antilles' => 'Netherlands Antilles',
          'Angola' => 'Angola',
          'Antarctica' => 'Antarctica',
          'Argentina' => 'Argentina',
          'American Samoa' => 'American Samoa',
          'Austria' => 'Austria',
          'Australia' => 'Australia',
          'Aruba' => 'Aruba',
          'Aland Islands' => 'Aland Islands',
          'Azerbaijan' => 'Azerbaijan',
          'Bosnia and Herzegovina' => 'Bosnia and Herzegovina',
          'Barbados' => 'Barbados',
          'Bangladesh' => 'Bangladesh',
          'Belgium' => 'Belgium',
          'Burkina Faso' => 'Burkina Faso',
          'Bulgaria' => 'Bulgaria',
          'Bahrain' => 'Bahrain',
          'Burundi' => 'Burundi',
          'Benin' => 'Benin',
          'Saint Barthélemy' => 'Saint Barthélemy',
          'Bermuda' => 'Bermuda',
          'Brunei' => 'Brunei',
          'Bolivia' => 'Bolivia',
          'Brazil' => 'Brazil',
          'Bahamas' => 'Bahamas',
          'Bhutan' => 'Bhutan',
          'Bouvet Island' => 'Bouvet Island',
          'Botswana' => 'Botswana',
          'Belarus' => 'Belarus',
          'Belize' => 'Belize',
          'Canada' => 'Canada',
          'Cocos (Keeling) Islands' => 'Cocos (Keeling) Islands',
          'Congo (Kinshasa)' => 'Congo (Kinshasa)',
          'Central African Republic' => 'Central African Republic',
          'Congo (Brazzaville)' => 'Congo (Brazzaville)',
          'Switzerland' => 'Switzerland',
          'Ivory Coast' => 'Ivory Coast',
          'Cook Islands' => 'Cook Islands',
          'Chile' => 'Chile',
          'Cameroon' => 'Cameroon',
          'China' => 'China',
          'Colombia' => 'Colombia',
          'Costa Rica' => 'Costa Rica',
          'Cuba' => 'Cuba',
          'Curaçao' => 'Curaçao',
          'Cape Verde' => 'Cape Verde',
          'Christmas Island' => 'Christmas Island',
          'Cyprus' => 'Cyprus',
          'Czech Republic' => 'Czech Republic',
          'Germany' => 'Germany',
          'Djibouti' => 'Djibouti',
          'Denmark' => 'Denmark',
          'Dominica' => 'Dominica',
          'Dominican Republic' => 'Dominican Republic',
          'Algeria' => 'Algeria',
          'Ecuador' => 'Ecuador',
          'Estonia' => 'Estonia',
          'Egypt' => 'Egypt',
          'Western Sahara' => 'Western Sahara',
          'Eritrea' => 'Eritrea',
          'Spain' => 'Spain',
          'Ethiopia' => 'Ethiopia',
          'Finland' => 'Finland',
          'Fiji' => 'Fiji',
          'Falkland Islands' => 'Falkland Islands',
          'Micronesia' => 'Micronesia',
          'Faroe Islands' => 'Faroe Islands',
          'France' => 'France',
          'Gabon' => 'Gabon',
          'United Kingdom' => 'United Kingdom',
          'Grenada' => 'Grenada',
          'Georgia' => 'Georgia',
          'French Guiana' => 'French Guiana',
          'Guernsey' => 'Guernsey',
          'Ghana' => 'Ghana',
          'Gibraltar' => 'Gibraltar',
          'Greenland' => 'Greenland',
          'Gambia' => 'Gambia',
          'Guinea' => 'Guinea',
          'Guadeloupe' => 'Guadeloupe',
          'Equatorial Guinea' => 'Equatorial Guinea',
          'Greece' => 'Greece',
          'South Georgia and the South Sandwich Islands' => 'South Georgia and the South Sandwich Islands',
          'Guatemala' => 'Guatemala',
          'Guam' => 'Guam',
          'Guinea-Bissau' => 'Guinea-Bissau',
          'Guyana' => 'Guyana',
          'Hong Kong S.A.R., China' => 'Hong Kong S.A.R., China',
          'Heard Island and McDonald Islands' => 'Heard Island and McDonald Islands',
          'Honduras' => 'Honduras',
          'Croatia' => 'Croatia',
          'Haiti' => 'Haiti',
          'Hungary' => 'Hungary',
          'Indonesia' => 'Indonesia',
          'Ireland' => 'Ireland',
          'Israel' => 'Israel',
          'Isle of Man' => 'Isle of Man',
          'India' => 'India',
          'British Indian Ocean Territory' => 'British Indian Ocean Territory',
          'Iraq' => 'Iraq',
          'Iran' => 'Iran',
          'Iceland' => 'Iceland',
          'Italy' => 'Italy',
          'Jersey' => 'Jersey',
          'Jamaica' => 'Jamaica',
          'Jordan' => 'Jordan',
          'Japan' => 'Japan',
          'Kenya' => 'Kenya',
          'Kyrgyzstan' => 'Kyrgyzstan',
          'Cambodia' => 'Cambodia',
          'Kiribati' => 'Kiribati',
          'Comoros' => 'Comoros',
          'Saint Kitts and Nevis' => 'Saint Kitts and Nevis',
          'North Korea' => 'North Korea',
          'South Korea' => 'South Korea',
          'Kuwait' => 'Kuwait',
          'Cayman Islands' => 'Cayman Islands',
          'Kazakhstan' => 'Kazakhstan',
          'Laos' => 'Laos',
          'Lebanon' => 'Lebanon',
          'Saint Lucia' => 'Saint Lucia',
          'Liechtenstein' => 'Liechtenstein',
          'Sri Lanka' => 'Sri Lanka',
          'Liberia' => 'Liberia',
          'Lesotho' => 'Lesotho',
          'Lithuania' => 'Lithuania',
          'Luxembourg' => 'Luxembourg',
          'Latvia' => 'Latvia',
          'Libya' => 'Libya',
          'Morocco' => 'Morocco',
          'Monaco' => 'Monaco',
          'Moldova' => 'Moldova',
          'Montenegro' => 'Montenegro',
          'Saint Martin (French part)' => 'Saint Martin (French part)',
          'Madagascar' => 'Madagascar',
          'Marshall Islands' => 'Marshall Islands',
          'Macedonia' => 'Macedonia',
          'Mali' => 'Mali',
          'Myanmar' => 'Myanmar',
          'Mongolia' => 'Mongolia',
          'Macao S.A.R., China' => 'Macao S.A.R., China',
          'Northern Mariana Islands' => 'Northern Mariana Islands',
          'Martinique' => 'Martinique',
          'Mauritania' => 'Mauritania',
          'Montserrat' => 'Montserrat',
          'Malta' => 'Malta',
          'Mauritius' => 'Mauritius',
          'Maldives' => 'Maldives',
          'Malawi' => 'Malawi',
          'Mexico' => 'Mexico',
          'Malaysia' => 'Malaysia',
          'Mozambique' => 'Mozambique',
          'Namibia' => 'Namibia',
          'New Caledonia' => 'New Caledonia',
          'Niger' => 'Niger',
          'Norfolk Island' => 'Norfolk Island',
          'Nigeria' => 'Nigeria',
          'Nicaragua' => 'Nicaragua',
          'Netherlands' => 'Netherlands',
          'Norway' => 'Norway',
          'Nepal' => 'Nepal',
          'Nauru' => 'Nauru',
          'Niue' => 'Niue',
          'New Zealand' => 'New Zealand',
          'Oman' => 'Oman',
          'Panama' => 'Panama',
          'Peru' => 'Peru',
          'French Polynesia' => 'French Polynesia',
          'Papua New Guinea' => 'Papua New Guinea',
          'Philippines' => 'Philippines',
          'Pakistan' => 'Pakistan',
          'Poland' => 'Poland',
          'Saint Pierre and Miquelon' => 'Saint Pierre and Miquelon',
          'Pitcairn' => 'Pitcairn',
          'Puerto Rico' => 'Puerto Rico',
          'Palestinian Territory' => 'Palestinian Territory',
          'Portugal' => 'Portugal',
          'Palau' => 'Palau',
          'Paraguay' => 'Paraguay',
          'Qatar' => 'Qatar',
          'Reunion' => 'Reunion',
          'Romania' => 'Romania',
          'Serbia' => 'Serbia',
          'Russia' => 'Russia',
          'Rwanda' => 'Rwanda',
          'Saudi Arabia' => 'Saudi Arabia',
          'Solomon Islands' => 'Solomon Islands',
          'Seychelles' => 'Seychelles',
          'Sudan' => 'Sudan',
          'Sweden' => 'Sweden',
          'Singapore' => 'Singapore',
          'Saint Helena' => 'Saint Helena',
          'Slovenia' => 'Slovenia',
          'Svalbard and Jan Mayen' => 'Svalbard and Jan Mayen',
          'Slovakia' => 'Slovakia',
          'Sierra Leone' => 'Sierra Leone',
          'San Marino' => 'San Marino',
          'Senegal' => 'Senegal',
          'Somalia' => 'Somalia',
          'Suriname' => 'Suriname',
          'Sao Tome and Principe' => 'Sao Tome and Principe',
          'El Salvador' => 'El Salvador',
          'Syria' => 'Syria',
          'Swaziland' => 'Swaziland',
          'Turks and Caicos Islands' => 'Turks and Caicos Islands',
          'Chad' => 'Chad',
          'French Southern Territories' => 'French Southern Territories',
          'Togo' => 'Togo',
          'Thailand' => 'Thailand',
          'Tajikistan' => 'Tajikistan',
          'Tokelau' => 'Tokelau',
          'Timor-Leste' => 'Timor-Leste',
          'Turkmenistan' => 'Turkmenistan',
          'Tunisia' => 'Tunisia',
          'Tonga' => 'Tonga',
          'Turkey' => 'Turkey',
          'Trinidad and Tobago' => 'Trinidad and Tobago',
          'Tuvalu' => 'Tuvalu',
          'Taiwan' => 'Taiwan',
          'Tanzania' => 'Tanzania',
          'Ukraine' => 'Ukraine',
          'Uganda' => 'Uganda',
          'United States Minor Outlying Islands' => 'United States Minor Outlying Islands',
          'United States' => 'United States',
          'Uruguay' => 'Uruguay',
          'Uzbekistan' => 'Uzbekistan',
          'Vatican' => 'Vatican',
          'Saint Vincent and the Grenadines' => 'Saint Vincent and the Grenadines',
          'Venezuela' => 'Venezuela',
          'British Virgin Islands' => 'British Virgin Islands',
          'U.S. Virgin Islands' => 'U.S. Virgin Islands',
          'Vietnam' => 'Vietnam',
          'Vanuatu' => 'Vanuatu',
          'Wallis and Futuna' => 'Wallis and Futuna',
          'Samoa' => 'Samoa',
          'Yemen' => 'Yemen',
          'Mayotte' => 'Mayotte',
          'South Africa' => 'South Africa',
          'Zambia' => 'Zambia',
          'Zimbabwe' => 'Zimbabwe',
        ),
        'allowed_values_function' => '',
      ),
      'translatable' => '0',
      'type' => 'list_text',
    ),
    'field_instance' => array(
      'bundle' => 'user',
      'default_value' => array(
        0 => array(
          'value' => 'United Kingdom',
        ),
      ),
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'inline',
          'module' => 'list',
          'settings' => array(),
          'type' => 'list_default',
          'weight' => '5',
        ),
        'tooltip' => array(
          'label' => 'inline',
          'module' => 'list',
          'settings' => array(),
          'type' => 'list_default',
          'weight' => '1',
        ),
      ),
      'entity_type' => 'user',
      'field_name' => 'field_country',
      'label' => 'Country',
      'required' => 1,
      'settings' => array(
        'user_register_form' => 1,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'options',
        'settings' => array(),
        'type' => 'options_select',
        'weight' => '11',
      ),
    ),
  );

  // Exported field: 'user-user-field_date_of_birth'.
  $fields['user-user-field_date_of_birth'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_date_of_birth',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'date',
      'settings' => array(
        'cache_count' => '4',
        'cache_enabled' => 0,
        'granularity' => array(
          'day' => 'day',
          'hour' => 0,
          'minute' => 0,
          'month' => 'month',
          'second' => 0,
          'year' => 'year',
        ),
        'timezone_db' => '',
        'todate' => '',
        'tz_handling' => 'none',
      ),
      'translatable' => '0',
      'type' => 'datetime',
    ),
    'field_instance' => array(
      'bundle' => 'user',
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'inline',
          'module' => 'date',
          'settings' => array(
            'format_type' => 'date_of_birth',
            'fromto' => 'both',
            'multiple_from' => '',
            'multiple_number' => '',
            'multiple_to' => '',
          ),
          'type' => 'date_default',
          'weight' => '2',
        ),
        'tooltip' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '10',
        ),
      ),
      'entity_type' => 'user',
      'field_name' => 'field_date_of_birth',
      'label' => 'Date of birth',
      'required' => 1,
      'settings' => array(
        'default_value' => 'blank',
        'default_value2' => 'same',
        'default_value_code' => '',
        'default_value_code2' => '',
        'user_register_form' => 1,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'date',
        'settings' => array(
          'increment' => '15',
          'input_format' => 'm/d/Y - H:i:s',
          'input_format_custom' => '',
          'label_position' => 'above',
          'text_parts' => array(),
          'year_range' => '-100:+0',
        ),
        'type' => 'date_select',
        'weight' => '8',
      ),
    ),
  );

  // Exported field: 'user-user-field_first_name'.
  $fields['user-user-field_first_name'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_first_name',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => '0',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'translatable' => '0',
      'type' => 'text',
    ),
    'field_instance' => array(
      'bundle' => 'user',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => '2',
        ),
        'tooltip' => array(
          'label' => 'hidden',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => '2',
        ),
      ),
      'entity_type' => 'user',
      'field_name' => 'field_first_name',
      'label' => 'First name',
      'required' => 1,
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => 1,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '6',
      ),
    ),
  );

  // Exported field: 'user-user-field_how_did_you_hear_about_us'.
  $fields['user-user-field_how_did_you_hear_about_us'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_how_did_you_hear_about_us',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => '0',
      'module' => 'text',
      'settings' => array(),
      'translatable' => '0',
      'type' => 'text_long',
    ),
    'field_instance' => array(
      'bundle' => 'user',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => '6',
        ),
        'tooltip' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '4',
        ),
      ),
      'entity_type' => 'user',
      'field_name' => 'field_how_did_you_hear_about_us',
      'label' => 'How did you hear about Scriptural Reasoning online?',
      'required' => 0,
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => 1,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'rows' => '5',
        ),
        'type' => 'text_textarea',
        'weight' => '12',
      ),
    ),
  );

  // Exported field: 'user-user-field_landline_phone'.
  $fields['user-user-field_landline_phone'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_landline_phone',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => '0',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'translatable' => '0',
      'type' => 'text',
    ),
    'field_instance' => array(
      'bundle' => 'user',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'inline',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => '7',
        ),
        'tooltip' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '9',
        ),
      ),
      'entity_type' => 'user',
      'field_name' => 'field_landline_phone',
      'label' => 'Landline phone',
      'required' => 0,
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => 1,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '13',
      ),
    ),
  );

  // Exported field: 'user-user-field_last_name'.
  $fields['user-user-field_last_name'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_last_name',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => '0',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'translatable' => '0',
      'type' => 'text',
    ),
    'field_instance' => array(
      'bundle' => 'user',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => '3',
        ),
        'tooltip' => array(
          'label' => 'hidden',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => '3',
        ),
      ),
      'entity_type' => 'user',
      'field_name' => 'field_last_name',
      'label' => 'Last name',
      'required' => 1,
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => 1,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '7',
      ),
    ),
  );

  // Exported field: 'user-user-field_mobile_phone'.
  $fields['user-user-field_mobile_phone'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_mobile_phone',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => '0',
      'module' => 'text',
      'settings' => array(
        'max_length' => '64',
      ),
      'translatable' => '0',
      'type' => 'text',
    ),
    'field_instance' => array(
      'bundle' => 'user',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'inline',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => '6',
        ),
        'tooltip' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '13',
        ),
      ),
      'entity_type' => 'user',
      'field_name' => 'field_mobile_phone',
      'label' => 'Mobile phone',
      'required' => 0,
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => 1,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '12',
      ),
    ),
  );

  // Exported field: 'user-user-field_occupation'.
  $fields['user-user-field_occupation'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_occupation',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => '0',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'translatable' => '0',
      'type' => 'text',
    ),
    'field_instance' => array(
      'bundle' => 'user',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'inline',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => '8',
        ),
        'tooltip' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '8',
        ),
      ),
      'entity_type' => 'user',
      'field_name' => 'field_occupation',
      'label' => 'Occupation',
      'required' => 0,
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => 1,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '14',
      ),
    ),
  );

  // Exported field: 'user-user-field_post_code'.
  $fields['user-user-field_post_code'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_post_code',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => '0',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
      ),
      'translatable' => '0',
      'type' => 'text',
    ),
    'field_instance' => array(
      'bundle' => 'user',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'inline',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => '4',
        ),
        'tooltip' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '12',
        ),
      ),
      'entity_type' => 'user',
      'field_name' => 'field_post_code',
      'label' => 'ZIP / Post code',
      'required' => 1,
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => 1,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '10',
      ),
    ),
  );

  // Exported field: 'user-user-field_postal_address'.
  $fields['user-user-field_postal_address'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_postal_address',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => '0',
      'module' => 'text',
      'settings' => array(),
      'translatable' => '0',
      'type' => 'text_long',
    ),
    'field_instance' => array(
      'bundle' => 'user',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'inline',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => '3',
        ),
        'tooltip' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '11',
        ),
      ),
      'entity_type' => 'user',
      'field_name' => 'field_postal_address',
      'label' => 'Postal address',
      'required' => 1,
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => 1,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'rows' => '5',
        ),
        'type' => 'text_textarea',
        'weight' => '9',
      ),
    ),
  );

  // Exported field: 'user-user-field_previous_experience'.
  $fields['user-user-field_previous_experience'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_previous_experience',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => '0',
      'module' => 'text',
      'settings' => array(),
      'translatable' => '0',
      'type' => 'text_long',
    ),
    'field_instance' => array(
      'bundle' => 'user',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => '5',
        ),
        'tooltip' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '2',
        ),
      ),
      'entity_type' => 'user',
      'field_name' => 'field_previous_experience',
      'label' => 'Have you any previous experience of Scriptural Reasoning and/or inter-faith dialogue?',
      'required' => 0,
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => 1,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'rows' => '5',
        ),
        'type' => 'text_textarea',
        'weight' => '11',
      ),
    ),
  );

  // Exported field: 'user-user-field_reasons'.
  $fields['user-user-field_reasons'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_reasons',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => '0',
      'module' => 'text',
      'settings' => array(),
      'translatable' => '0',
      'type' => 'text_long',
    ),
    'field_instance' => array(
      'bundle' => 'user',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => '7',
        ),
        'tooltip' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '5',
        ),
      ),
      'entity_type' => 'user',
      'field_name' => 'field_reasons',
      'label' => 'What are your reasons for wanting to be involved in SR online?',
      'required' => 0,
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => 1,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'rows' => '5',
        ),
        'type' => 'text_textarea',
        'weight' => '13',
      ),
    ),
  );

  // Exported field: 'user-user-field_religious_tradition'.
  $fields['user-user-field_religious_tradition'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_religious_tradition',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => '0',
      'module' => 'text',
      'settings' => array(),
      'translatable' => '0',
      'type' => 'text_long',
    ),
    'field_instance' => array(
      'bundle' => 'user',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => '4',
        ),
        'tooltip' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '3',
        ),
      ),
      'entity_type' => 'user',
      'field_name' => 'field_religious_tradition',
      'label' => 'What religious tradition do you belong to? What is your level of involvement?',
      'required' => 0,
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => 1,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'rows' => '5',
        ),
        'type' => 'text_textarea',
        'weight' => '10',
      ),
    ),
  );

  // Exported field: 'user-user-field_social_media_usage'.
  $fields['user-user-field_social_media_usage'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_social_media_usage',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => '0',
      'module' => 'text',
      'settings' => array(),
      'translatable' => '0',
      'type' => 'text_long',
    ),
    'field_instance' => array(
      'bundle' => 'user',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => '9',
        ),
        'tooltip' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '6',
        ),
      ),
      'entity_type' => 'user',
      'field_name' => 'field_social_media_usage',
      'label' => 'How often do you use online social media (Facebook, Twitter etc)?',
      'required' => 0,
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => 1,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'rows' => '5',
        ),
        'type' => 'text_textarea',
        'weight' => '15',
      ),
    ),
  );

  // Exported field: 'user-user-field_subjects_of_interest'.
  $fields['user-user-field_subjects_of_interest'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_subjects_of_interest',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => '0',
      'module' => 'text',
      'settings' => array(),
      'translatable' => '0',
      'type' => 'text_long',
    ),
    'field_instance' => array(
      'bundle' => 'user',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => '8',
        ),
        'tooltip' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '7',
        ),
      ),
      'entity_type' => 'user',
      'field_name' => 'field_subjects_of_interest',
      'label' => 'Are there particular subjects that are of interest to you? (NB we cannot guaranteethese will be included in discussion themes).',
      'required' => 0,
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => 1,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'rows' => '5',
        ),
        'type' => 'text_textarea',
        'weight' => '14',
      ),
    ),
  );

  // Exported field: 'user-user-field_title'.
  $fields['user-user-field_title'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_title',
      'foreign keys' => array(),
      'indexes' => array(
        'value' => array(
          0 => 'value',
        ),
      ),
      'locked' => '0',
      'module' => 'list',
      'settings' => array(
        'allowed_values' => array(
          'Ms' => 'Ms',
          'Miss' => 'Miss',
          'Mrs' => 'Mrs',
          'Mr' => 'Mr',
          'Master' => 'Master',
          'Rev' => 'Rev',
          'Fr' => 'Fr',
          'Dr' => 'Dr',
          'Prof' => 'Prof',
          'Hon' => 'Hon',
          'Pres' => 'Pres',
        ),
        'allowed_values_function' => '',
      ),
      'translatable' => '0',
      'type' => 'list_text',
    ),
    'field_instance' => array(
      'bundle' => 'user',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'list',
          'settings' => array(),
          'type' => 'list_default',
          'weight' => '1',
        ),
        'tooltip' => array(
          'label' => 'hidden',
          'module' => 'list',
          'settings' => array(),
          'type' => 'list_default',
          'weight' => '1',
        ),
      ),
      'entity_type' => 'user',
      'field_name' => 'field_title',
      'label' => 'Title',
      'required' => 0,
      'settings' => array(
        'user_register_form' => 1,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'options',
        'settings' => array(),
        'type' => 'options_select',
        'weight' => '5',
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Are there particular subjects that are of interest to you? (NB we cannot guaranteethese will be included in discussion themes).');
  t('Country');
  t('Date of birth');
  t('First name');
  t('Have you any previous experience of Scriptural Reasoning and/or inter-faith dialogue?');
  t('How did you hear about Scriptural Reasoning online?');
  t('How often do you use online social media (Facebook, Twitter etc)?');
  t('Landline phone');
  t('Last name');
  t('Mobile phone');
  t('Occupation');
  t('Postal address');
  t('Title');
  t('What are your reasons for wanting to be involved in SR online?');
  t('What religious tradition do you belong to? What is your level of involvement?');
  t('ZIP / Post code');

  return $fields;
}
