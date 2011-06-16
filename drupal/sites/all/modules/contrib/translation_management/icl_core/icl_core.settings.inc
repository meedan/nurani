<?php
/* 
 * icl_core.settings.inc
 * 
 * @file Page handler for admin settings callback
 */

module_load_include ( 'inc', 'icl_core', 'icl_core.webservices' );
module_load_include ( 'inc', 'icl_core', 'icl_core.constants' );

/**
 * temp class for storing target languages
 */

class lang_targets {
  public $targets = array();
}

function icl_core_elements() {
  $type = array();
  $type['checkbox_columns'] = array('#input' => TRUE, '#process' => array('icl_core_expand_checkbox_columns'), '#tree' => TRUE);
  return $type;
}

function icl_core_expand_checkbox_columns($element) {
  $value = is_array($element['#value']) ? $element['#value'] : array();
  $element['#type'] = 'checkboxes';
  $element['#tree'] = TRUE;
  if (count($element['#options']) > 0) {
    if (!isset($element['#default_value']) || $element['#default_value'] == 0) {
      $element['#default_value'] = array();
    }
    foreach ($element['#options'] as $key => $choice) {
      $class = ($column % $element['#columns']) && $column ? 'checkbox-columns' : 'checkbox-columns-clear';
      if (!isset($element[$key])) {
        $element[$key] = array('#type' => 'checkbox', '#processed' => TRUE, '#title' => $choice, '#default_value' => in_array($key, $value), '#attributes' => $element['#attributes'], '#prefix' => '<div class="' . $class . '">', '#suffix' => '</div>');
      }
      $column++;
    }
  }
  return $element;
}


/**
 * This is a page callback for the ICanLocalize Core admin page
 *
 * @return array The system settings form.
 */
function icl_core_admin_settings() {
  
  drupal_add_js(drupal_get_path('module', 'icl_core') . '/js/icl_core.js');
  drupal_add_css(drupal_get_path('module', 'icl_core').'/css/icl_core.css');

  icl_core_add_thickbox();

  if (variable_get ( 'icl_core_website_id', '' ) != '' && variable_get ( 'icl_core_accesskey', '' ) != '') {
    variable_set ( 'icl_core_setup_wizard_complete' , TRUE);
  }
    
  if (variable_get ('icl_core_setup_wizard_complete', FALSE) == TRUE) {
    return icl_core_setup_complete_form();
  } else {
    // need to run the setup wizard.
    $wizard_step = variable_get ('icl_core_setup_wizard_step', 0);
    if ($wizard_step == 0) {
      return icl_core_setup_wizard_step_1();
    } elseif ($wizard_step == 1) {
      return icl_core_setup_wizard_step_2();
    } else {
      return icl_core_setup_wizard_step_3();
    }
  }
}

function icl_core_show_logo($form) {
  global $base_url;
  $path = $base_url . '/' . drupal_get_path('module', 'icl_core') . '/images/web_logo_large.png';
  $form ['icl_logo'] = _icl_wrapper_form_create_markup(array(
    '#type' => 'markup',
    '#value' => '<img src="' . $path . '"  style="margin: 0px 0px -5px 0px; float: left; "><br clear="all" />',
    ));

  return $form;
}
function icl_core_show_wizard_step($form, $sw_width) {
  
  $form = icl_core_add_reminders($form);
  $form['icl_support'] =  _icl_wrapper_form_create_markup(array(
    '#type' => 'markup',
    '#prefix' => '<div class="icl_cyan_box">',
    '#suffix' => '</div>',
    '#value' => icl_core_get_support_help(),
  ));

  
  $wizard_message = t ('Before you can start using Professional translation, it needs to be set up');
  $wizard_message .= '<br style="clear:both;" />';
  $wizard_message .= '<div id="icl_setup_wizard_2"><div class="icl_setup_wizard_step"><strong>';
  $wizard_message .= t('1. Translation Languages');
  $wizard_message .= '</strong></div>';
  $wizard_message .= '<div class="icl_setup_wizard_step"><strong>';
  $wizard_message .= t('2. Options');
  $wizard_message .= '</strong></div>';
  $wizard_message .= '<div class="icl_setup_wizard_step"><strong>';
  $wizard_message .= t('3. Account setup');
  $wizard_message .= '</strong></div></div><br clear="all" />';
  $wizard_message .= '<div id="icl_setup_wizard_progress"><div id="icl_setup_wizard_progress_bar" style="width:';
  $wizard_message .= $sw_width;
  $wizard_message .= '%">&nbsp;</div></div>';
  
  $form ['wizard']  = _icl_wrapper_form_create_markup(array (
      '#type' => 'markup', 
      '#prefix' => '<div id="icl_setup_wizard_wrap">', 
      '#suffix' => '</div>', 
      '#value' =>  $wizard_message));

  return $form;  

}
function icl_core_setup_wizard_step_1 () {
  $form = array();
  $platform_info = array();
  
  $form = icl_core_show_logo($form);
  
  $form = icl_core_show_wizard_step ($form, 15);
  $form = icl_core_setup_languages($form, $platform_info);
  
  //$form = system_settings_form ( $form );
  
  //unset($form['buttons']['reset']);
  
  $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Next'),
      );
  //$form['buttons']['submit']['#value'] = t('Next');
  //$form['#submit'] = array('icl_core_admin_settings_submit_1' => array());
  
  
  return $form;
}
  
function icl_core_admin_settings_submit($form_id, $form_values) {
  if (variable_get ('icl_core_setup_wizard_complete', TRUE) == TRUE) {
    system_settings_form_submit($form_id, $form_values);
  }
}

function icl_core_setup_wizard_step_2 () {
  $form = array();
  
  $form = icl_core_show_logo($form);
  $form = icl_core_show_wizard_step ($form, 40);
  #$form = icl_core_setup_languages($form);

  $form ['website_desciption'] = array (
      '#type' => 'fieldset', 
      '#title' => t ( '<b>Information about your website</b>' ), 
      '#collapsible' => false,
      '#access' => true,
      );
  $form ['website_desciption']['icl_core_project_description'] = array (
      '#type' => 'textarea', 
      '#title' => t ( 'Describe your website' ), 
      '#description' => t ( 'Please describe your site, target audience and preferred writing style. This would allow the most suitable translators to apply for this job.' ),
      '#required' => true,
      '#rows' => 3,
      );
  
  $form ['options'] = array (
      '#type' => 'fieldset', 
      '#title' => t ( '<b>Translation options</b>' ), 
      '#collapsible' => false,
      '#access' => true,
      );
  
  $options = array (
      ICL_CORE_RECEIVE_XMLRPC => t ( 'Translations will be posted back to this Drupal website via XML-RPC' ), 
      ICL_CORE_RECEIVE_POLL => t ( 'This Drupal installation will poll for translations' ) );
  $form ['options']['icl_core_receive_options'] = array (
      '#type' => 'radios', 
      '#title' => t ( 'Select the desired translation delivery method' ), 
      '#multiple' => FALSE, 
      '#options' => $options, 
      '#default_value' => variable_get ( 'icl_core_receive_options', ICL_CORE_RECEIVE_XMLRPC ), 
      '#description' => t ( 'Choose polling if your site is inaccessible from the Internet' ) );
  
  
  $form['back'] = array(
        '#type' => 'button',
        '#value' => t('Back'),
        '#executes_submit_callback' => TRUE,
        '#submit' => array('icl_core_wizard_back'),
        );

  $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Next'),
      );
  
  return $form;
}

function icl_core_setup_wizard_step_3 () {
  $form = array();
  
  $form = icl_core_show_logo($form);
  $form = icl_core_show_wizard_step ($form, 75);
  #$form = icl_core_setup_languages($form);
  
  $form ['project_setup'] = array (
      '#type' => 'fieldset', 
      '#title' => t ( '<b>Project settings</b>' ), 
      '#collapsible' => false,
      '#access' => false,
      );
  
  $form ['project_setup'] ['icl_core_project_name'] = array (
      '#type' => 'textfield', 
      '#title' => t ( 'Project name' ), 
      '#default_value' => variable_get('icl_core_project_name', variable_get('site_name', '')),
      '#description' => t ( 'Used to identify the project. Use a clear descriptive name.') );
  $form ['project_setup'] ['icl_core_project_description'] = array (
      '#type' => 'textarea', 
      '#title' => t ( 'Project description' ), 
      '#default_value' => variable_get('icl_core_project_description', variable_get('site_slogan', '')), 
      '#description' => t ( 'Provide a short description of the website so that translators know what background is required from them.') );
  
  // we don't have a website id or accesskey so assume a new setup.
  $form ['icanlocalize_setup'] = array (
      '#type' => 'fieldset', 
      '#title' => t ( '<b>ICanLocalize Account</b>' ), 
      '#collapsible' => false );
  $form ['icanlocalize_setup'] ['message'] = _icl_wrapper_form_create_markup(array (
        '#type' => 'markup',
        '#prefix' => '<div id="icl_core_account_message">',
        '#suffix' => '</div>',
        '#value' => t("An account will be created for you in ICanLocalize, in order to do translations.")
      ));
  $form ['icanlocalize_setup'] ['icl_core_first_name'] = array (
      '#type' => 'textfield', 
      '#title' => t ( 'First name' ), 
      '#default_value' => variable_get('icl_core_first_name', ''), 
      '#description' => t ( 'Used for the ICanLocalize account. Will not be shared with other users'),
      );
  $form ['icanlocalize_setup'] ['icl_core_last_name'] = array (
      '#type' => 'textfield', 
      '#title' => t ( 'Last name' ), 
      '#default_value' => variable_get('icl_core_last_name', ''), 
      '#description' => t ( 'Used for the ICanLocalize account. Will not be shared with other users.'),
      );
  $form ['icanlocalize_setup'] ['icl_core_email_address'] = array (
      '#type' => 'textfield', 
      '#title' => t ( 'Email address' ), 
      '#default_value' => variable_get('icl_core_email_address', ''), 
      '#description' => t ( 'The administrative contact for your account. Not shared with other users.'),
      '#required' => TRUE);
  $form ['icanlocalize_setup'] ['icl_core_password'] = array (
      '#type' => 'password', 
      '#title' => t ( 'Password' ), 
      '#default_value' => variable_get('icl_core_password', ''), 
      '#description' => t ( "Enter your ICanlocalize password. If you don't have a password, select 'I need to create an account at ICanLocalize' below."),
      );
  $form ['icanlocalize_setup'] ['icl_core_button'] = array (
      '#type' => 'button', 
      '#value' => t ( 'I already have an account at ICanLocalize' ),
      '#attributes' => _icl_wrapper_form_create_attributes(array('onclick' => "javascript:on_account_button();return false;")),
      );
  $form ['icanlocalize_setup'] ['icl_core_do_create'] = array (
      '#type' => 'hidden',
      '#value' => TRUE,
      );
  
  _icl_core_add_affiliate($form);

  $form['back'] = array(
        '#type' => 'button',
        '#value' => t('Back'),
        '#executes_submit_callback' => TRUE,
        '#submit' => array('icl_core_wizard_back'),
        );

  $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Create account and Finish'),
      );
  
  return $form;
}
  
function _icl_core_add_affiliate(&$form) {
  $form ['icanlocalize_affiliate'] = array (
      '#type' => 'fieldset', 
      '#title' => t ( 'Using ICanLocalize for a client site?' ), 
      '#collapsible' => true,
      '#collapsed' => true);
  
  $form ['icanlocalize_affiliate']['info'] = _icl_wrapper_form_create_markup(array (
      '#type' => 'markup', 
        '#prefix' => '<div>',
        '#suffix' => '</div>',
      '#value' => t ( 'If you’re setting up ICanLocalize translation for a client site, enter your affiliate ID and key below. We’ll credit your account for every translation we do for this project.'),
      ));
  $form ['icanlocalize_affiliate'] ['icl_affiliate_id'] = array (
      '#type' => 'textfield', 
      '#title' => t ( 'Affiliate ID' ), 
      '#default_value' => variable_get('icl_affiliate_id', ''), 
      );
  $form ['icanlocalize_affiliate'] ['icl_affiliate_key'] = array (
      '#type' => 'textfield', 
      '#title' => t ( 'Affiliate key' ), 
      '#default_value' => variable_get('icl_affiliate_key', ''), 
      );
  
  $form ['icanlocalize_affiliate']['how'] = _icl_wrapper_form_create_markup(array (
      '#type' => 'markup', 
        '#prefix' => '<div>',
        '#suffix' => '</div>',
        '#value' => t ("Don't yet have an affiliate ID? <a href='@url'>Sign up for an account</a>. It only takes a minute. When you’re done, click on the Affiliate tab. <a href='@url_more'>More info</a>.",
                       array('@url' => ICL_ACCOUNT_SIGNUP, '@url_more' => ICL_SETUP_INFO)),
        ));
  
  
}
function icl_core_wizard_back() {
  variable_set ('icl_core_setup_wizard_step', variable_get ('icl_core_setup_wizard_step', 1) - 1);
  _icl_wrapper_drupal_goto(_icl_wrapper_get_drupal_menu('admin/settings/icl-core'));
}
/**
 * This form is shown after the setup wizard is complete.
 *
 */

function icl_core_add_reminders($form) {
  
  $ican_reminder_url = _icl_wrapper_url('icl_core/fetch_reminders');
  drupal_add_js(
                array('ican_fetch' =>
                      array('ican_reminder_url' => $ican_reminder_url)),
                      'setting');
  $ican_delete_reminder_url = _icl_wrapper_url('icl_core/delete_reminder');
  drupal_add_js(
                array('ican_fetch' =>
                      array('ican_delete_reminder_url' => $ican_delete_reminder_url)),
                      'setting');
  $ican_show_reminders_url = _icl_wrapper_url('icl_core/show_reminders');
  drupal_add_js(
                array('ican_fetch' =>
                      array('ican_show_reminders_url' => $ican_show_reminders_url)),
                      'setting');
  drupal_add_js ( drupal_get_path ( 'module', 'icl_core' ) . '/js/icl_reminders.js' );

  $show = variable_get('icl_show_reminders', true);
  $markup = '<div id="icl_reminder_message" class="icl_status" style="clear:both;margin-top:5px;display:none;padding: 1px;">
    
    <table width="100%" style="margin: 0 0;">
        <tbody style="border-top:0px">
        <tr>
            <td><h3><b>' . t('ICanLocalize Reminders') . '</b></h3></td>
            <td align="right"><a id="icl_reminder_show" href="#" style="text-align:right">
            <span id="icl_show_text"';
            
  if ($show) {
    $markup .= ' style="display:none">' . t('Show reminders') . '</span><span> ' . t('Hide reminders') . '</span>';
  } else {
    $markup .= '>' . t('Show reminders') . '</span><span style="display:none"> ' . t('Hide reminders') . '</span>';
  }
  $markup .= '
            </a></td>
        </tr>
        </tbody>
    </table>';
    
  if ($show) {
    $markup .= '<div id="icl_reminder_list" style="margin-left: 5px;">';
  } else {
    $markup .= '<div id="icl_reminder_list" style="margin-left: 5px;display:none;">';
  }
  $markup .= '
    </div>
</div>';
  
  $form ['icl_core_reminders'] = _icl_wrapper_form_create_markup(array (
      '#type' => 'markup', 
      '#value' => $markup,
      ));

  return $form;  
}

/*
  ajax callback to save the show reminders state.
*/
  
function icl_core_show_reminders() {
  variable_set('icl_show_reminders', $_POST['state'] == 'show' ? 1 : 0);
}

function icl_core_setup_complete_form () {
  $form = array ();
  $platform_info = array();
  
  /*
   $form ['icl_core_setup_instructions'] = array (
      '#type' => 'fieldset', 
      '#title' => t ( 'Getting started' ),
      '#value' => t ( 'Need help setting up ICanLocalize Translator? Visit the ') . '<a href="'. ICL_INSTALL_AND_SETUP_GUIDE . '">'. t ( 'getting started guide') . '</a>'
      );
  */
  $form = icl_core_show_logo($form);
  
  $form = icl_core_add_reminders($form);

  $form['icl_url_changed'] = _icl_wrapper_form_create_markup(array(
    '#type' => 'markup',
    '#prefix' => '<div class="icl_red_box">',
    '#suffix' => '</div>',
    '#value' => '',
  ));

  $form['icl_support'] =  _icl_wrapper_form_create_markup(array(
    '#type' => 'markup',
    '#prefix' => '<div class="icl_cyan_box">',
    '#suffix' => '</div>',
    '#value' => icl_core_get_support_help(),
  ));

  
  $form ['icl_core_project_kind'] = array (
      '#type' => 'fieldset', 
      '#title' => t ( 'What kind of website is this?' ),
      '#access' => FALSE,
      );

    $form ['icl_core_project_kind'] ['message'] = _icl_wrapper_form_create_markup(array (
        '#type' => 'markup', 
        '#prefix' => '<div class="status"><b>', 
        '#suffix' => '</b></div>', 
        '#value' => t ("ICanLocalize needs to assign professional translators to each website that we translate. Please help us by indicating what kind of website you're setting up.")
        ));

  $options = array (
      0 => t ( "Test site - I'm only testing out the system and don't need to have translators assigned yet." ), 
      1 => t ( 'Development site with real contents - This site includes real contents that need to be translated, but still running on a development server.' ),
      2 => t ( 'Production site (running on the live server) - This is the actual production site with contents that need to be translated.' ) );
  $form ['icl_core_project_kind'] ['icl_core_project_kind_options'] = array (
      '#type' => 'radios', 
      '#title' => t ( '' ), 
      '#multiple' => FALSE, 
      '#options' => $options, 
      '#default_value' => variable_get ( 'icl_core_project_kind_options', 2 ), 
       );

  $i18n_not_installed = _icl_wrapper_check_i18n_installed();
  if (sizeof($i18n_not_installed) > 0) {
    $form['i18n_errors'] = array (
      '#type' => 'fieldset', 
      '#title' => t ( 'Missing i18n modules.' ), 
      '#collapsible' => false );
  
    foreach($i18n_not_installed as $id => $module) {
      $form ['i18n_errors'] [$module['module']] = _icl_wrapper_form_create_markup(array (
          '#type' => 'markup', 
          '#prefix' => '<div class="error">', 
          '#suffix' => '</div>', 
          '#value' => $module['message']
          ));
    }
  }

  $form = icl_core_setup_languages($form, $platform_info);
  
  if (icl_core_is_icl_stored_url_ok($platform_info)) {
    unset ( $form['icl_url_changed'] );
  } else {
    icl_core_get_url_changed_message ( $form['icl_url_changed'], $platform_info );
  }
  
  $form ['icl_core_translator_selection'] = array (
      '#type' => 'fieldset', 
      '#title' => t ( 'Translator selection' ), 
      '#collapsible' => FALSE,
      '#access' => FALSE,
      );

  $options = array (
      //ICL_CORE_SELECT_TRANSLATORS_ICANLOCALIZE => t ( 'Let ICanLocalize choose the best translator for me.' ), 
      ICL_CORE_SELECT_TRANSLATORS_CLIENT => t ( 'Choose translators from ICanLocalize.' ),
      ICL_CORE_SELECT_TRANSLATORS_PRIVATE => t ( 'Use my own translators.' ),
      );
  $form ['icl_core_translator_selection'] ['icl_core_translator_selection'] = array (
      '#type' => 'radios', 
      '#title' => t ( 'Select how you want to select translators' ), 
      '#multiple' => FALSE, 
      '#options' => $options, 
      '#default_value' => variable_get ( 'icl_core_translator_selection', ICL_CORE_SELECT_TRANSLATORS_CLIENT ), 
      '#description' => t ( 'If you want to choose translators, you will be notified by email whenever a translator applies to work on your project.' ),
      '#attributes' => _icl_wrapper_form_create_attributes(array('onclick' => "javascript:on_translator_select();")),
      );
  $form['icl_core_translator_selection'] ['private_transaltors'] = _icl_wrapper_form_create_markup(array(
            '#type' => 'markup', 
          '#prefix' => '<div id="icl_core_private_translator_message">', 
          '#suffix' => '</div>', 
          '#value' => t('To invite your own translators to work on this project, visit your !private_translators page (requires logging in to ICanLocalize)', array('!private_translators' => ICL_PRIVATE_TRANSLATORS))
      ));

  if ($platform_info['free_usage']) {
    $form['icl_core_translator_selection'] ['free_usage'] = _icl_wrapper_form_create_markup(array(
            '#type' => 'markup',
            '#prefix' => '<div class="status"><b>', 
            '#suffix' => '</b></div>', 
            '#value' => t('Usage fees for ICanLocalize Translator have been waived for this project.')
        ));
  }

  $options = array (
      ICL_CORE_RECEIVE_XMLRPC => t ( 'Translations will be posted back to this Drupal website via XML-RPC' ), 
      ICL_CORE_RECEIVE_POLL => t ( 'This Drupal installation will poll for translations' ) );
  $form ['icl_core_translation_options'] = array (
      '#type' => 'fieldset', 
      '#title' => t ( 'Translation options' ), 
      '#collapsible' => TRUE,
      '#collapsed' => TRUE);
  $form ['icl_core_translation_options'] ['icl_core_receive_options'] = array (
      '#type' => 'radios', 
      '#title' => t ( 'Select the desired translation delivery method' ), 
      '#multiple' => FALSE, 
      '#options' => $options, 
      '#default_value' => variable_get ( 'icl_core_receive_options', ICL_CORE_RECEIVE_XMLRPC ), 
      '#description' => t ( 'Choose polling if your site is inaccessible from the Internet' ) );
  $form ['icl_core_translation_options'] ['icl_core_notifications'] = array (
      '#type' => 'checkboxes', 
      '#title' => t ( 'Notification preferences' ), 
      '#options' => array('1' => 'Send an email notification when translations complete',
                          '2' => 'Send an alert when translations delay for more than 4 days'),
      '#default_value' => variable_get('icl_core_notifications', array('1', '2')),
      '#description' => t("ICanLocalize will send notifications messages via email of these events"),
      );

  if (module_exists('icl_content')) {
    module_load_include ( 'inc', 'icl_content', 'icl_content.settings' );
    $content_form = icl_content_admin_settings();
    $form ['icl_conenet_translation_options'] = array (
        '#type' => 'fieldset', 
        '#title' => t ( 'Content translation options' ), 
        '#collapsible' => TRUE,
        '#collapsed' => TRUE);
    $form ['icl_conenet_translation_options'] ['form_items'] = $content_form;
  }

  $disable_save = FALSE;
  
  if (variable_get ( 'icl_core_website_id', '' ) != '' && variable_get ( 'icl_core_accesskey', '' ) != '') {

    $user_status = variable_get('icl_core_user_status', -1);
    if ($user_status != ICL_USER_STATUS_CLOSED) {
      $form ['icl_core_translation_options']['icl_core_balance_message'] = _icl_wrapper_form_create_markup(array (
          '#type' => 'markup',
          '#value' => t ("<b>ICanLocalize Account</b><br>There's no up-front or subscription payment for using ICanLocalize Translator. You pay only for translation jobs that you send. You can make your first payment when sending documents to translation. !more_info", array('!more_info' => ICL_DRUPAL_TRANSLATION_INFO)),
          '#prefix' => '<div id="icl_core_balance_message">',
          '#suffix' => '</div>',
          ));
      $form ['icl_core_translation_options'] ['icl_balance_warning'] = array (
          '#type' => 'textfield', 
          '#title' => t ( 'Account balance warning' ), 
          '#default_value' => number_format((float)variable_get ( 'icl_balance_warning', 50 ), 2, '.', ''), 
          '#description' => t ( 'Warn me when the account balance goes below this value, in USD'));
      
    } else {
      $form ['icl_core_user'] = array (
          '#type' => 'fieldset', 
          '#title' => t ( 'ICanLocalize account closed' ), 
          '#collapsible' => FALSE);
      $form ['icl_core_user'] ['icl_core_user_message'] = _icl_wrapper_form_create_markup(array(
        '#type' => 'markup',
        '#value' => 'Your ICanLocalize account has been closed. Translation is disabled.',
      ));
      
      $disable_save = TRUE;
      
    } 
      
      
  

    $form ['access_settings'] = array (
        '#type' => 'fieldset', 
        '#title' => t ( 'Access settings' ), 
        '#collapsible' => true,
        '#collapsed' => true);
    $form ['access_settings'] ['icl_core_website_id'] = array (
        '#type' => 'textfield', 
        '#title' => t ( 'Website ID' ), 
        '#default_value' => variable_get ( 'icl_core_website_id', '' ), 
        '#description' => t ( 'The website ID you received from ') . ICL_ICANLOCALIZE_LINK );
    $form ['access_settings'] ['icl_core_accesskey'] = array (
        '#type' => 'textfield', 
        '#title' => t ( 'Accesskey' ), 
        '#default_value' => variable_get ( 'icl_core_accesskey', '' ), 
        '#description' => t ( 'The accesskey you received from ') . ICL_ICANLOCALIZE_LINK );

    if (is_string ( $ican_languages )) {
      // we have an error.
      $form ['access_settings']['#collapsed'] = FALSE;
      
      $form ['access_settings'] ['access_error'] = _icl_wrapper_form_create_markup(array (
          '#type' => 'markup', 
          '#prefix' => '<div class="error">', 
          '#suffix' => '</div>', 
          '#value' => $ican_languages
          ));
    } else {
      // website id and accesskey are ok.
      
      $form ['access_settings'] ['access_ok'] = _icl_wrapper_form_create_markup(array (
          '#type' => 'markup', 
          '#prefix' => '<div class="status">', 
          '#suffix' => '</div>', 
          '#value' => t("Webite ID and Accesskey verified.")
          ));
      $form ['access_settings'] ['site_info'] = _icl_wrapper_form_create_markup(array (
          '#type' => 'markup', 
          '#prefix' => '<div id="language-wrapper">', 
          '#suffix' => '</div>', 
          '#value' => t("ICanLocalize project name:") . $platform_info['name']
          ));
      
      $form ['access_settings'] ['icl_core_project_description'] = array (
        '#type' => 'textarea', 
        '#title' => t ( 'Project description' ), 
        '#default_value' => variable_get('icl_core_project_description', variable_get('site_slogan', '')), 
        '#description' => t ( 'Provide a short description of the website so that translators know what background is required from them.') );
      
    }
  } else {
    $form ['project_setup'] = array (
        '#type' => 'fieldset', 
        '#title' => t ( '<b>Project settings</b>' ), 
        '#collapsible' => false );
    
    $form ['project_setup'] ['icl_core_project_name'] = array (
        '#type' => 'textfield', 
        '#title' => t ( 'Project name' ), 
        '#default_value' => variable_get('icl_core_project_name', variable_get('site_name', '')),
        '#description' => t ( 'Used to identify the project. Use a clear descriptive name.') );
    $form ['project_setup'] ['icl_core_project_description'] = array (
        '#type' => 'textarea', 
        '#title' => t ( 'Project description' ), 
        '#default_value' => variable_get('icl_core_project_description', variable_get('site_slogan', '')), 
        '#description' => t ( 'Provide a short description of the website so that translators know what background is required from them.') );
    
    // we don't have a website id or accesskey so assume a new setup.
    $form ['icanlocalize_setup'] = array (
        '#type' => 'fieldset', 
        '#title' => t ( '<b>ICanLocalize Account</b>' ), 
        '#collapsible' => false );
    $form ['icanlocalize_setup'] ['message'] = _icl_wrapper_form_create_markup(array (
          '#type' => 'markup',
          '#prefix' => '<div id="icl_core_account_message">',
          '#suffix' => '</div>',
          '#value' => t("An account will be created for you in ICanLocalize, in order to do translations.")
        ));
    $form ['icanlocalize_setup'] ['icl_core_first_name'] = array (
        '#type' => 'textfield', 
        '#title' => t ( 'First name' ), 
        '#default_value' => variable_get('icl_core_first_name', ''), 
        '#description' => t ( 'Used for the ICanLocalize account. Will not be shared with other users'),
        );
    $form ['icanlocalize_setup'] ['icl_core_last_name'] = array (
        '#type' => 'textfield', 
        '#title' => t ( 'Last name' ), 
        '#default_value' => variable_get('icl_core_last_name', ''), 
        '#description' => t ( 'Used for the ICanLocalize account. Will not be shared with other users.'),
        );
    $form ['icanlocalize_setup'] ['icl_core_email_address'] = array (
        '#type' => 'textfield', 
        '#title' => t ( 'Email address' ), 
        '#default_value' => variable_get('icl_core_email_address', ''), 
        '#description' => t ( 'The administrative contact for your account. Not shared with other users.'),
        '#required' => TRUE);
    $form ['icanlocalize_setup'] ['icl_core_password'] = array (
        '#type' => 'password', 
        '#title' => t ( 'Password' ), 
        '#default_value' => variable_get('icl_core_password', ''), 
        '#description' => t ( "Enter your ICanlocalize password. If you don't have a password, select 'I need to create an account at ICanLocalize' below."),
        );
    $form ['icanlocalize_setup'] ['icl_core_button'] = array (
        '#type' => 'button', 
        '#value' => t ( 'I already have an account at ICanLocalize' ),
        '#attributes' => _icl_wrapper_form_create_attributes(array('onclick' => "javascript:on_account_button();return false;")),
        );
    $form ['icanlocalize_setup'] ['icl_core_do_create'] = array (
        '#type' => 'hidden',
        '#value' => TRUE,
        );
    
  }

  _icl_core_add_affiliate($form);
  
  
  if (variable_get ( 'icl_core_mode', ICL_MODE_PRODUCTION ) == ICL_MODE_SANDBOX) {
    $form ['trouble_shoot'] = array (
        '#type' => 'fieldset', 
        '#title' => t ( '<b>Reset ICanLocalize ** Debug **</b>' ), 
        '#collapsible' => false );
    $form ['trouble_shoot'] ['icl_reset'] = array (
        '#type' => 'checkboxes',
        '#options' => array('reset' => 'reset ICL settings'),
        );
  }    
  
  //$form = system_settings_form ( $form );
  
  //unset($form['buttons']['reset']);
  
  $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
      );
  if ($disable_save) {
  
    $form['submit']['#attributes'] = _icl_wrapper_form_create_attributes(array('disabled' => 'disabled'));

    //$form['buttons']['submit']['#attributes'] = _icl_wrapper_form_create_attributes(array('disabled' => 'disabled'));
  }
  return $form;
}

function icl_core_setup_languages ( $form, &$platform_info ) {
  // get the installed languages.
  
  $default_language = language_default();
  $default_language_code = $default_language->language;
  $icl_default_id = icl_core_get_lang_id($default_language_code);
  
  $languages = language_list('enabled');
  $languages = $languages[1];
  
  // only include languages support in icanlocalize.
  $all_langs = _icl_core_get_all_languages();
  $supported_langs = array();
  
  foreach($languages as $code => $lang) {
    $icl_lang_name = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT icl_name FROM {icl_languages} WHERE code='%s'", $code));
    foreach ($all_langs as $lang_details) {
      if ($lang_details['name'] == $icl_lang_name) {
        if ((int)$lang_details['id'] != 0) {
          $supported_langs[$lang_details['code']] = $icl_lang_name;
        }
        
        break;
      }
    }
  }
  
  $languages = $supported_langs;

  foreach ($all_langs as $name => $lang) {
    if ($lang['id'] == $icl_default_id) {
      $default_language_code = $lang['code'];
      break;
    }
  }
  
  $ican_languages = NULL;

  // do we have a website id or accesskey
  
  $icl_account_setup = variable_get ( 'icl_core_website_id', '' ) != '' && variable_get ( 'icl_core_accesskey', '' ) != '';
  
  if ($icl_account_setup) {
    // check we can access with this info.
    $clear_cache = FALSE;
    if (isset($_GET['icl_refresh_langs'])){
      $clear_cache = TRUE;
    }
    $ican_languages = icl_core_available_languages ( $clear_cache, $platform_info );
  } else {
    $step_langauges = array();
    if ( variable_get ('icl_core_setup_wizard_complete', FALSE) == FALSE) {
      $step_languages = variable_get ('icl_core_setup_wizard_languages', array());
    }
    
    if (sizeof($step_languages) == 0) {
      // set up the default to translate from the default language to all other languages.
      
      $ican_languages = array(
        $default_language_code => new lang_targets(),
      );
      foreach ($languages as $code => $lang) {
        if ($code != $default_language_code) {
          $ican_languages[$default_language_code]->targets[$code] = 1;
        }
      }
    } else {
      // use the languages that have been saved.

      $ican_languages = array();
      
      foreach ($step_languages as $code => $targets) {
        if (sizeof($targets) > 0) {

          $ican_languages[$code] = new lang_targets();
          
          foreach ($targets as $target) {
            $ican_languages[$code]->targets[$target] = 1;
            
          }
        }        
      }
    }
  }
  
  
  $form ['language_settings'] = array (
      '#type' => 'fieldset', 
      '#title' => t ( 'Languages' ), 
      '#collapsible' => FALSE);
  
  if (sizeof($languages) == 1) {  
    $form ['language_settings'] ['no_languages'] = _icl_wrapper_form_create_markup(array (
        '#type' => 'markup', 
        '#prefix' => '<div class="error"><b>', 
        '#suffix' => '</b></div>', 
        '#value' => t ('You only have one language setup or enabled on your Drupal site. Please add or enable additional languages - <a href="!add_languages">Add languages.</a>', array('!add_languages' => _icl_wrapper_url(_icl_wrapper_get_drupal_menu('admin/settings/language/add'))))
        ));
  } else {
    
    $sorted_languages = array();
    
    // put default language first.
    foreach ($languages as $code => $lang) {
      if ($code == $default_language_code) {
        $sorted_languages[$code] = $lang;
        unset($languages[$code]);
        break;
      }
    }
    
    // put any enabled source languages next.

    foreach ($languages as $code => $lang) {
      if (isset($ican_languages[$code])) {
        $sorted_languages[$code] = $lang;
        unset($languages[$code]);
      }
    }

    // now add any that are left.
    
    foreach ($languages as $code => $lang) {
      $sorted_languages[$code] = $lang;
    }
    
    $base = $form ['language_settings'];
    $finished_enabled_languages = false;
    foreach ($sorted_languages as $code => $lang) {
      
      if (!$finished_enabled_languages && !isset($ican_languages[$code])){
        $finished_enabled_languages = true;
        $form ['language_settings'] = $base;
        $form ['language_settings'] ['not_enabled'] = array (
            '#type' => 'fieldset', 
            '#title' => t ( 'More translation pairs' ), 
            '#collapsible' => true,
            '#collapsed' => true,
            );
        $base = $form ['language_settings'] ['not_enabled'];
      }
      
      $base ['source_languages_' . $code] = array (
        '#type' => 'checkbox',
        '#title' => t("Translate from @language", array('@language' => $lang)),
        '#default_value' => isset($ican_languages[$code]),
        //'#description' => t("Allows content to be translated from @language to other languages.", array('@language' => $lang->name)),
        '#attributes' => _icl_wrapper_form_create_attributes(array('onclick' => "javascript:on_lang_from(jQuery(this), '" . $code . "');")),
        );
      $dest_languages = array();
      
      $dest_languages_enabled = array();
      
      foreach ($sorted_languages as $dest_code => $dest_lang) {
        if ($dest_code != $code) {
          $dest_languages[$dest_code] = $dest_lang;
          $dest_languages[$dest_code] .= ' ' . icl_get_language_status_text($ican_languages, $platform_info, $code, $dest_code);
          if (isset($ican_languages[$code]->targets[$dest_code])) {
            $dest_languages_enabled[] = $dest_code;
          }
        }
      }
      
      $attributes = array('id' => 'dest_languages_' . $code);
      if (!isset($ican_languages[$code])){
        // hide the to languages
        $attributes['style'] = "display: none;";
      }
      
      
      $base ['field_dest_languages_' . $code] = _icl_wrapper_form_create_markup(array(
          '#type' => 'markup', 
          '#value' => t ( 'Translate to these languages' ), 
          '#prefix' => '<div id="' . $attributes['id'] . '" style="margin:0px 20px;' . $attributes['style'] . '">',
          '#suffix' => '</div>'
          ));
      
      $base ['field_dest_languages_' . $code] ['dest_languages_' . $code] = array (
        '#type' => 'checkboxes',
        '#title' => "",
        '#columns' => 2,
        '#options' => $dest_languages,
        '#default_value' => $dest_languages_enabled,
        //'#description' => '<br style="clear:both"/>' . t("Allows content to be translated from !language to these languages. Languages that don't have a translator available for doing translations are marked as (No translators have been assigned yet)", array('!language' => $lang->name)),
        '#attributes' => _icl_wrapper_form_create_attributes(array('onclick' => "javascript:on_translator_select();")),
        '#suffix' => '<br style="clear:both"/>',
      );
      
    }
  }

  if ($finished_enabled_languages) {
    $form ['language_settings'] ['not_enabled'] = $base;
  } else {
    $form ['language_settings'] = $base;
  }
  return $form;
}


/**
 * Validate the form and make sure we have a website id and accesskey
 *
 */

function icl_core_admin_settings_validate($form, &$form_state) {
  
  global $base_url;
  
  if ($form_state['clicked_button']['#value'] == t('Back')) {
    return;
  }
  
  if ((string)$form_state['values'] ['icl_reset'] ['reset'] == 'reset') {
    variable_set ( 'icl_core_website_id', '' );
    variable_set ( 'icl_core_accesskey', '' );
    
    variable_set('icl_current_session', '');

    variable_set ('icl_core_setup_wizard_complete', FALSE);
    variable_set ('icl_core_setup_wizard_step', 0);

    variable_set ( 'icl_core_user_status', '');
    variable_set ( 'icl_core_user_id', '');
    variable_set ( 'icl_core_languages', '');
    
    variable_set ('icl_core_setup_wizard_languages', array());
    
    variable_del ('icl_strings_for_translation');
    
    _icl_wrapper_db_query("TRUNCATE {icl_block}");
    _icl_wrapper_db_query("TRUNCATE {icl_block_status}");
    _icl_wrapper_db_query("TRUNCATE {icl_comment_translation}");
    _icl_wrapper_db_query("TRUNCATE {icl_content_status}");
    _icl_wrapper_db_query("TRUNCATE {icl_core_status}");
    _icl_wrapper_db_query("TRUNCATE {icl_node}");
    _icl_wrapper_db_query("TRUNCATE {icl_reminders}");
    
    return;  
  }

  $languages = array();
  
  foreach ($form_state['values'] as $key => $value) {
    if (strpos($key, 'dest_languages_') === 0) {
      $source_lang = substr($key, strlen('dest_languages_'));
      $languages[$source_lang] = array();
      
      if ($form_state['values']['source_languages_' . $source_lang]) {
        foreach ($form_state['values'][$key] as $key_dest => $value_dest) {
          if ($value_dest) {
            $languages[$source_lang][] = $key_dest;              
            
          }
        }        
      }
    }
  }

  if (variable_get ('icl_core_setup_wizard_complete', FALSE) == FALSE) {
    // the wizard is in progress.
    $wizard_step = variable_get ('icl_core_setup_wizard_step', 0);
    if ($wizard_step == 0) {
      variable_set ('icl_core_setup_wizard_languages', $languages);
      variable_set ('icl_core_setup_wizard_step', 1);
      return;
    } elseif ($wizard_step == 1) {
      variable_set('icl_core_receive_options', $form_state['values']['icl_core_receive_options']);
      variable_set('icl_core_project_description', $form_state['values']['icl_core_project_description']);
      variable_set ('icl_core_setup_wizard_step', 2);
      return;
    }

    $languages = variable_get ('icl_core_setup_wizard_languages', array());
    $notifications = 3;
    $project_kind = 2;
    
    $form_state['values']['icl_core_translator_selection'] = ICL_CORE_SELECT_TRANSLATORS_ICANLOCALIZE;
    $form_state['values']['icl_core_receive_options'] = variable_get('icl_core_receive_options', ICL_CORE_RECEIVE_POLL);
    
  } else {
  
    $notifications = 0;
    foreach($form_state['values']['icl_core_notifications'] as $key => $value) {
      if ($key == $value) {
        $notifications += pow(2, (int)$key - 1);
      }
    }
    
    $project_kind = $form_state['values']['icl_core_project_kind_options'];
  }
  
  if (isset($form['access_settings'])) {
      
    if($form_state['values']['icl_core_website_id'] == '') {
      form_set_error('', t('Please enter a website ID that you received from ') . ICL_ICANLOCALIZE_LINK );
    }
    elseif($form_state['values']['icl_core_accesskey'] == '') {
      form_set_error('', t('Please enter an accesskey that you received from ') . ICL_ICANLOCALIZE_LINK );
    }
    
    // we have a website id and access key.

    // set update settings to icanlocalize
    
    $affiliate_id = $form_state['values']['icl_affiliate_id'];
    $affiliate_key = $form_state['values']['icl_affiliate_key'];
    
    $result = icl_core_update_cms($form_state['values']['icl_core_accesskey'],
                                      $form_state['values']['icl_core_website_id'],
                                      $form_state['values']['icl_core_translator_selection'] == ICL_CORE_SELECT_TRANSLATORS_ICANLOCALIZE ? 0 : 1,
                                      $base_url,
                                      variable_get('icl_core_project_name', ''),
                                      $form_state['values']['icl_core_project_description'],
                                      $form_state['values']['icl_core_receive_options'] == ICL_CORE_RECEIVE_POLL,
                                      $languages,
                                      $notifications,
                                      $project_kind,
                                      $affiliate_id,
                                      $affiliate_key);
    if (is_string ( $result )) {
      // we got an error
      form_set_error('', $result);
    } else {
      // refresh the languages.
      $platform_info = NULL;
      icl_core_available_languages ( true, $platform_info );
    }
    
    
    
  } else {
    if(!valid_email_address($form_state['values']['icl_core_email_address'])) {
      form_set_error('', t('Please enter a valid email address'));
    } else {
      
      // Accound setup mode.
      
      $create_account = $_POST['icl_core_do_create'] == '1';
      
      $first = $form_state['values']['icl_core_first_name'];
      $last = $form_state['values']['icl_core_last_name'];
      $pass = $form_state['values']['icl_core_password'];
      
      if ($create_account) {
        if($first == '') {
          form_set_error('', t('Please enter your first name') );
          return;
        }
        if($last == '') {
          form_set_error('', t('Please enter your last name') );
          return;
        }

        $pass = "";
      } else {
        if($pass == '') {
          form_set_error('', t('Please enter your password for access to ICanLocalize') );
          return;
        }
        
        $first = "";
        $last = "";
      }

      $affiliate_id = $form_state['values']['icl_affiliate_id'];
      $affiliate_key = $form_state['values']['icl_affiliate_key'];
      
      // everything is ok so we can submit to icanlocalize
      $result = icl_core_create_account($form_state['values']['icl_core_email_address'],
                                        $create_account,
                                        $first,
                                        $last,
                                        $pass,
                                        $form_state['values']['icl_core_translator_selection'] == ICL_CORE_SELECT_TRANSLATORS_ICANLOCALIZE ? 1 : 0,
                                        $base_url,
                                        $form_state['values']['icl_core_project_name'],
                                        $form_state['values']['icl_core_project_description'],
                                        $form_state['values']['icl_core_receive_options'] == ICL_CORE_RECEIVE_POLL,
                                        $languages,
                                        $notifications,
                                        $project_kind,
                                        $affiliate_id,
                                        $affiliate_key);
      if (is_string ( $result )) {
        // we got an error
        form_set_error('', '<b>' . t('ICanLocalize Account creation error: ') . $result . '</b>');
      } else {
    
        // All is ok so inform the user.
        
        variable_set('icl_core_email_address', $form_state['values']['icl_core_email_address']);
        variable_set('icl_affiliate_id', $form_state['values']['icl_affiliate_id']);
        variable_set('icl_affiliate_key', $form_state['values']['icl_affiliate_key']);
        
        $message_data = array('!email_address' => $form_state['values']['icl_core_email_address'],
                              '!password_reminder' => ICL_PASSWORD_REMINDER);
        drupal_set_message(t ('<b>An account was created for you in ICanLocalize</b> - Next step:<br />Use the <a href="!link">Translation Dashboard</a> to send documents to translation.', array('!link' => _icl_wrapper_url(_icl_wrapper_get_drupal_menu('/admin/content/translation-management/dashboard')))));
      }
    }
    
  }
}

/**
 * AHAH callback for ICanLocalize admin page
 * Returns the enabled languages for translation or an error message
 * when no languages are enabled.
 *
 */
function icl_core_retrieve_langs_js() {
  print _icl_wrapper_drupal_to_js( array (
      'status' => TRUE, 
      'data' => _icl_core_settings_language_list ( TRUE ) ) );
  exit ();
}

/*
 * Creates the available language list
 * 
 * @param $cache_clear TRUE to empty the internal caches, FALSE otherwise
 */
function _icl_core_settings_language_list($clear_cache = FALSE) {
  
  if ($clear_cache) {
    // we need record the current website id and accesskey and then
    // use the ones the user has entered on the settings page to get
    // the langauges setup on icanlocalize.
    
    $original_wid = variable_get ( 'icl_core_website_id', FALSE );    
    $original_accesskey = variable_get ( 'icl_core_accesskey', FALSE );
    
    // get the form state
    
    $form_state = array('storage' => NULL, 'submitted' => FALSE);
  
    $form = form_get_cache($_POST['form_build_id'], $form_state);
    $form['#post'] = $_POST;
  
    drupal_process_form('icl_core_admin_settings', $form, $form_state);
    
    // Use the website and accesskey the user has entered.
    
    variable_set('icl_core_website_id', $form_state['values']['icl_core_website_id']);
    variable_set('icl_core_accesskey', $form_state['values']['icl_core_accesskey']);
  }
  
  if($form_state['values']['icl_core_website_id'] != variable_get ( 'icl_core_website_id', '' ) || 
    $form_state['values']['icl_core_website_id'] != variable_get ( 'icl_core_website_id', '' ))
  {
        $clear_cache = TRUE;
        variable_set ( 'icl_core_languages', array() );
        $original_wid = variable_get ( 'icl_core_website_id', FALSE );    
        $original_accesskey = variable_get ( 'icl_core_accesskey', FALSE );
  }
  
  $platform_info = array();
  $languages = icl_core_available_languages ( $clear_cache, $platform_info );

  if ($clear_cache) {
    variable_set('icl_core_website_id', $original_wid);
    variable_set('icl_core_accesskey', $original_accesskey);
  }
  
  if (is_string ( $languages )) {
    if ($languages == '-1 cannot access') {
      $languages = t ('Cannot retrieve the languages from the ICanLocalize server. Please check the website ID and access key.');
    }
    return '<div class="error">' . $languages . '</div>';
  }
  
  if (empty ( $languages )) {
    $output = '<div class="error">' . t ( 'No languages have been defined. Please define at least one in your setup on ' ) . ICL_ICANLOCALIZE_LINK . '<br>' . t ('See ') . '<a href="' . ICL_INSTALL_AND_SETUP_GUIDE_LANGUAGES . '">' . t ('Install and setup guide') . '</a>' . t(' for details.') . '</div>';
  } else {
    $pairs = array ();
    if ($platform_info['platform'] != ICL_DRUPAL_PROJECT_KIND) {
      // not a drupal platform
      $output = '<div class="error">' . t ( 'The project is not setup as a Drupal project on ICanLocalize. Please goto !ICanLocalize and correct the project kink.', array("!ICanLocalize" => ICL_ICANLOCALIZE_LINK)) . "</div>";
    } else {
      
      $output = "";
      
      $output .= t("ICanLocalize project name: <b>") . $platform_info['name'] . "</b><br />";
      $output .= t("ICanLocalize project description: <b>") . $platform_info['description'] . "</b><br />";
      
      $pickup = variable_get ( 'icl_core_receive_options', ICL_CORE_RECEIVE_XMLRPC ) == ICL_CORE_RECEIVE_POLL;
      if (isset($form_state['values']['icl_core_receive_options'])) {
        $pickup = $form_state['values']['icl_core_receive_options'] == ICL_CORE_RECEIVE_POLL;
      }
      
      if($platform_info['pickup'] != $pickup) {
        $output .= '<div class="error">' . t ( 'The translation delivery method is different on ICanLocalize. Please select the same delivery method as set on !ICanLocalize.', array("!ICanLocalize" => ICL_ICANLOCALIZE_LINK)) . "</div>";
      }

      
      foreach ( $languages as $from ) {
        foreach ( $from->targets as $to ) {
          $temp = t ( 'From %from to %to', array (
              '%from' => $from->name, 
              '%to' => $to->name ) );
          if (! $from->enabled || ! $to->enabled) {
            $temp .=  '<div class="error">'. t ('Disabled or not selected in Drupal.') . '</div>' . t ('Add appropriate languages on !locale settings page or enable them if they are already added.', array (
                '!locale' => l ( t ( 'Language' ), _icl_wrapper_get_drupal_menu('admin/settings/language/add'), array (
                    'query' => 'destination=admin/settings/icl-core' ) ) ) ) ;
          }
          $pairs [] = $temp;
        }
      }
      $output .= '<ul><li>' . implode ( '</li><li>', $pairs ) . '</li></ul>';
    }
  }
  
  return $output;
}

function icl_core_reminders() {
  global $base_url;
  $session_id = icl_get_current_session();
  
  $target = icl_core_get_icl_url() . $_GET['target'];
  
  if ($session_id != '') {
    if (strpos($target, '?') === false) {
      $target .= '?';
    } else {
      $target .= '&';
    }
    $target .= "session=" . $session_id;
  }
  
  $image_path = $base_url . '/' . drupal_get_path('module', 'icl_core') . '/images/web_logo_small.png';
  echo '<img src="' . $image_path . '"  style="margin: 0px 0px 0px; float: left; "><br clear="all" />';
  ?>
  
  <iframe src="<?php echo $target;?>" style="width:99%; height:90%"></iframe>
  <?php
}