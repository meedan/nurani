<?php

include_once dirname(__FILE__) . '/icl_content.node.inc';
include_once dirname(__FILE__) . '/icl_content.block.inc';
include_once dirname(__FILE__) . '/icl_content.contact_form.inc';

function icl_content_do_translation_status_report() {
  $last_sent = variable_get('icl_content_report_last_sent', 0);
  if (time() - $last_sent > 24 * 60 * 60) {
    
    $stats = icl_content_get_stats();
    icl_content_send_stats($stats);
    
    variable_set('icl_content_report_last_sent', time());
  }
}

function icl_content_get_stats() {

  module_load_include ( 'inc', 'icl_content', 'icl_content.dashboard' );

  $filter = array('language' => language_default()->language);
  $contents = icl_content_get_nodes_for_dashboard($filter);
  if (module_exists('block')) {
  
    $content_blocks = icl_content_get_blocks_for_dashboard($filter);
    foreach ($content_blocks as $item) {
      $contents[] = $item;
    }
  }
  
  $content_contact_form = icl_content_get_contact_form_for_dashboard($filter);
  if ($content_contact_form) {
    $contents[] = $content_contact_form;
  }
  
  
  $total = sizeof($contents);
  
  $stats = array();
  
  foreach ($contents as $content) {
    $status = _icl_content_dasboard_check_status($content);
    
    foreach ($content['targets'] as $lang => $target) {
      
      if (!isset($stats[$lang])) {
        $stats[$lang] = array();
      }
      if (!isset($target['translation_service']) || $target['translation_service'] == '') {
        $target['translation_service'] = 'NONE';
      }
      
      if (!isset($stats[$lang][$target['translation_service']])) {
        $stats[$lang][$target['translation_service']] = array('in_progress' => 0,
                                                              'translated' => 0,
                                                              'waiting' => 0,
                                                              'needs_update' => 0);
      }
      
      switch ($status[$lang]) {
        case 'in_progress':
          $stats[$lang][$target['translation_service']]['in_progress'] += 1;
          break;
        
        case 'complete':
        case 'verification':
          $stats[$lang][$target['translation_service']]['translated'] += 1;
          break;

        case 'update':
          $stats[$lang][$target['translation_service']]['needs_update'] += 1;
          break;
        
      }
      
    }
  }
  
  return array('total' => $total, 'lang' => $filter['language'], 'stats' => $stats);

}

function icl_content_send_stats($stats) {
  // create an anonymous account
  $wid = variable_get ( 'icl_core_website_id', FALSE );
  $accesskey = variable_get ( 'icl_core_accesskey', FALSE );
  if ($wid == FALSE || $accesskey == FALSE) {
    // Create a temporary account.
    
    icl_core_create_anon_account();
    $wid = variable_get ( 'icl_core_website_id', FALSE );
    $accesskey = variable_get ( 'icl_core_accesskey', FALSE );
  }
  
  $source = $stats['lang'];
  $total = $stats['total'];

  $langs = icl_core_fetch_languages(TRUE);
  
  $count = 1;
  $post = array();
  
  foreach ($stats['stats'] as $lang => $target) {
    // add language to account
    
    $lang_pair_exists = FALSE;
  
    $from_name = icl_core_get_language_name($source);
    $to_name = icl_core_get_language_name($lang);
    
    if (isset($langs['langs'][$from_name])) {
      foreach ($langs['langs'][$from_name] as $to_lang) {
        if ($to_lang == $to_name) {
          $lang_pair_exists = TRUE;
          break;
        }
      }
    }
  
    if ( !$lang_pair_exists ) {
      // need to add the language pair.

      icl_core_add_language($from_name, $to_name, $langs['langs'], $wid, $accesskey);
      $langs = icl_core_fetch_languages(TRUE, FALSE, FALSE);
    }

    $offer_id = $langs['offer_id'][$from_name][$to_name];
    
    if (isset($offer_id)) {
    
      // now send the statistics.
      
      $post['kind' . $count] = 1;
      $post['status' . $count] = 0;
      $post['count' . $count] = $total;
      $post['offer_id' . $count] = $offer_id;
      
      foreach ($target as $service => $data) {
        foreach (array(2 => 'in_progress', 10 => 'translated', 1 => 'waiting', 5 => 'needs_update') as $code => $key) {
          $post['kind' . $count] = 1;
          $post['status' . $count] = $code;
          $post['count' . $count] = $data[$key];
          $post['service' . $count] = $service;
          $post['offer_id' . $count] = $offer_id;
          
          $count ++;
        }
      }
      
    }
    
  }

  $post['num_elements'] = $count - 1;  
  $result = icl_core_call_service('/websites/[wid]/add_counts.xml?accesskey=[accesskey]', TRUE, $post);
  
  
}

function icl_content_status_report() {
  
  drupal_add_js ( drupal_get_path ( 'module', 'icl_content' ) . '/js/icl_stats.js' );
  
  $form = array();
  
  $form['info'] = _icl_wrapper_form_create_markup(array(
    '#type' => 'markup',
    '#value' => t('<p>Get real time statistics about the status of translations in this site.</p>
                   <p>
                    <ul>
                      <li>See overall status</li>
                      <li>See which languages are lagging behind</li>
                      <li>See languages where you need more translators</li>
                    </ul>
                  </p>

                  <p>Translation statistics are collected and sent to the ICanLocalize server. You can then use ICanLocalize\'s translation statistics to see the current state of translations on your website and analize the progress of those translations.</p>
                  <p><a href="@demo_url">See demonstation</a></p>',
                  array('@demo_url' => 'http://www.icanlocalize.com/translation_statistics_demo'))
  ));

  if (!variable_get('icl_translate_reports_enabled', FALSE)) {
    $form['i_understand'] = array(   
      '#type' => 'checkbox',
      '#title' => t('I understand that translation statistics will be sent to ICanLocalize'),
    );
    $form['enable'] = array(
      '#value' => t('Enable Status Reports'),
      '#type' => 'submit',
      '#submit' => array('icl_content_status_report_enable'),
      '#disabled' => TRUE,
    );
  } else {

    $form['reporting'] = array(
      '#type' => 'fieldset',
      '#title' => t('Reporting'),
    );
    $form['reporting']['report_info'] = _icl_wrapper_form_create_markup(array(
      '#type' => 'markup',
      '#value' => t('The translation statistics that are collected are:
                    <ul>
                      <li>Untranslated documents</li>
                      <li>Documents waiting for translator</li>
                      <li>Translations in progress</li>
                      <li>Translations complete</li>
                    </ul>'
                    )
    ));
    /*
    $form['reporting']['include_words'] = array(   
      '#type' => 'checkbox',
      '#title' => t('Include word count in statitics'),
      '#disabled' => TRUE,
    );
    */
    $form['reporting']['icl_report_use_crop'] = array(   
      '#type' => 'checkbox',
      '#title' => t('Report translation statistics via cron'),
      '#default_value' => variable_get('icl_report_use_crop', FALSE),
    );
    $form['reporting']['icl_report_on_status_change'] = array(   
      '#type' => 'checkbox',
      '#title' => t('Report translation statistics whenever translation status changes'),
      '#default_value' => variable_get('icl_report_on_status_change', TRUE),
    );

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
      '#weight' => 9999
    );

    /*    
    $form['disable'] = array(
      '#value' => t('Disable Status Reports'),
      '#type' => 'submit',
      '#submit' => array('icl_content_status_report_disable'),
    );
    */
  }
  
  return $form;
}

function icl_content_status_report_enable($form, &$form_values) {
  variable_set('icl_translate_reports_enabled', TRUE);
}

function icl_content_status_report_disable($form, &$form_values) {
  variable_set('icl_translate_reports_enabled', FALSE);
}

function icl_content_status_report_submit($form_id, $form_values) {
  system_settings_form_submit($form_id, $form_values);
}