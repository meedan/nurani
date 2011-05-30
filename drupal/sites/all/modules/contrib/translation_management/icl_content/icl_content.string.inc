<?php
/*
 * $Id: icl_content.string.inc
 * 
 * @file ICanLocalize string handling
 */

module_load_include ( 'inc', 'icl_core', 'icl_core.module' );
module_load_include ( 'inc', 'icl_content', 'icl_content.dashboard' );

// String translation using ICanLocalize server

/*
 $strings - an array of strings to be sent for translation
 array('string_id' => 111, 'string_type' => 'locale')
 
 $target_languages - an array of languages to translate to
*/
function icl_content_send_strings($strings) {
  // send to each language
  $strings_waiting_for_translation = variable_get('icl_strings_queued_for_translation', array());
  foreach ($strings as $string) {
    $strings_waiting_for_translation[] = $string;
  }

  variable_set('icl_strings_queued_for_translation', $strings_waiting_for_translation);
}


function icl_decode_translation_status_id($status){
    switch($status){
        case CMS_TARGET_LANGUAGE_CREATED: $st = t('Waiting for translator');break;
        case CMS_TARGET_LANGUAGE_ASSIGNED: $st = t('In progress');break; 
        case CMS_TARGET_LANGUAGE_TRANSLATED: $st = t('Translation received');break;
        case CMS_TARGET_LANGUAGE_DONE:
        case ICL_STATUS_SUCCESSFUL:
          $st = t('Translation complete');break;
        case ICL_STATUS_FAILED: $st = t('Request failed');break;
        default: $st = t('Not translated');
    }
    
    return $st;
}


function icl_content_get_string_translation_status($string, $decode = true) {
  $sql = "
          SELECT
              cs.status , cs.target
          FROM
              {icl_core_status} cs
          JOIN 
             {icl_string_status} ss
          ON
             ss.rid = cs.rid
          JOIN 
             {icl_string_group} sg
          ON
             ss.translation_group_id = sg.translation_group_id
          WHERE
              sg.string_id=%d
              AND
              sg.string_type='%s'
          ";   

  $query = db_query($sql, $string['string_id'], $string['string_type']);
  while ( $item = db_fetch_object($query)) {
    if ($decode) {
      $status[$item->target] = icl_decode_translation_status_id($item->status);
    } else {
      $status[$item->target] = $item->status;
    }
  }

  return $status;
      
}


function icl_content_alter_locale_translate_seek_form(&$form, $form_state) {
  
  // @todo Check if needed here
  drupal_add_js ( drupal_get_path ( 'module', 'icl_core' ) . '/js/icl_reminders.js' );
  
  // @todo Check if needed
  drupal_add_js(array('text_group' => t('Text group')), 'setting');
  if (!module_exists('l10n_client')) {
    $ican_string_status_url = _icl_wrapper_url('icl_content/icl_string_status');
    drupal_add_js(
                  array('ican_url' =>
                        array('ican_string_status_url' => $ican_string_status_url)),
                        'setting');
    

    drupal_add_js(drupal_get_path('module', 'icl_content') . '/js/icl_string.js');
  }
  
  //$form['action'] = icl_content_dashboard_action_form($form, true);
  $form['action']['operations'] = array(
    '#type' => 'fieldset',
    '#title' => t('Translation options'),
    '#attributes' => array('id' => 'dashboard-actions'),
  );
  //$form['action']['operations']['#title'] = t('Translation options');
  $form['action']['#weight'] = -10; // put at the top.
  
  $form['action']['icl_check'] = array(
    '#type' => 'checkbox',
    '#title' => '',
    '#attributes' => array('style' => "display:none;"),
  );
  
  $form['action']['operations']['translate_request'] = array(
    '#type' => 'submit',
    '#validate' => array('icl_content_locale_translate_validate'),
    '#submit' => array('icl_content_locale_translate_submit'),
    '#value' => t('Queue selected strings for translation'),
  );
  
  //if (isset($form['action']['operations']['translate_request'])) {
    /*$form['action']['operations']['translate_request']['#validate'] = array('icl_content_locale_translate_validate');
    $form['action']['operations']['translate_request']['#submit'] = array('icl_content_locale_translate_submit');
    $form['action']['operations']['translate_request']['#value'] = t('Queue strings for translation');*/
  //}
  
}

function icl_content_locale_translate_validate($form, &$form_state) {
}

function icl_content_locale_translate_submit($form, &$form_state) {
  $strings = array();
  if (isset($_POST['icl_lid'])) {
    $cached_strings = variable_get('icl_strings_queued_for_translation', 0);
    foreach($_POST['icl_lid'] as $id => $state) {
      if ($state == '1') {
        // Check if string is already sent
        if ($cached_strings) {
          foreach ($cached_strings as $string) {
            if ($string['string_id'] == $id) {
              //drupal_set_message('String already sent for translation');
              continue;
            }
          }
        }
        else {
          $cached_strings = array();
        }
        $cached_strings[] = array('string_id' => $id, 'string_type' => 'locale');
      }
    }
    
    variable_set('icl_strings_queued_for_translation', $cached_strings);
    
    icl_content_set_string_queue_message();
    
  }
}

function icl_content_string_translation($content, $request_id) {
  foreach ( $content as $code => $data ) {
    $strings = array();
    foreach($data as $item) {
      $parts = explode('-', $item['type']);
      $strings[$parts[1]][$parts[2]] = $item['data'];
    }
    
    foreach($strings as $id => $string) {
      if (strpos($id, 'locale') === 0) {
        $lid = substr($id, 6);
        icl_content_update_locale_translation($lid, $code, $string['value']);
      }
    }
  }
  
  return TRUE;
}

function icl_content_is_string_queued($id) {
  $strings_waiting_for_translation = variable_get('icl_strings_queued_for_translation', array());
  
  foreach($strings_waiting_for_translation as $string) {
    if ($string['string_id'] == $id) {
      return TRUE;
    }
  }
  
  return FALSE;
}
function icl_content_string_status() {


  global $language;

  if (!isset($_POST['ican_string_token'])) {
    exit;
  }
  if (drupal_get_token('ican_string_token') != $_POST['ican_string_token']) {
    exit;
  }
  
  if ($_POST['icl_ajx_action'] == 'icl_string_status') {
    
    $source_lang = language_default()->language;
    $langs_targets = _icl_core_available_targets_for_origin ( $source_lang );
    
    $strings = explode(',', $_POST['string_ids']);
    foreach ($strings as $st_id) {
      $string['string_id'] = $st_id;
      $string['string_type'] = 'locale';
      
      if (icl_content_is_string_queued($st_id)) {
        echo $st_id . ',' . t('In queue') . '|';
      }
      
      $status = icl_content_get_string_translation_status($string);
      if ($status) {
      
        foreach($status as $lang => $stat) {
          echo $st_id . ',' . $lang . ',' . $stat . '|';
        }
      }
    }
  } else if ($_POST['icl_ajx_action'] == 'icl_single_string_status') {
    $st_id = _icl_wrapper_db_result(db_query("SELECT lid FROM {locales_source} WHERE source = '%s' AND textgroup = '%s'", $_POST['source'], 'default'));
    
    if (icl_content_is_string_queued($st_id)) {
      echo 1 . '|' . t("In queue");
    } else {
      $string['string_id'] = $st_id;
      $string['string_type'] = 'locale';
      
      $status = icl_content_get_string_translation_status($string, false);
      
      if ($status) {
      
        foreach($status as $lang => $stat) {
          if ($lang == $language->language) {
            echo $stat . '|' . icl_decode_translation_status_id($stat);
          }
        }
      }
    }
  } else if ($_POST['icl_ajx_action'] == 'icl_any_queued_strings') {
    $strings_waiting_for_translation = variable_get('icl_strings_queued_for_translation', array());
    if (sizeof($strings_waiting_for_translation) > 0) {
      echo '1';
    } else {
      echo '0';
    }
    
  }  
  
}

/**
 * handles queuing a string from the localization client l10n_client.
 */

function icl_content_string_send() {
  global $language;
  
  $string = $_POST['string'];
  $st_id = _icl_wrapper_db_result(db_query("SELECT lid FROM {locales_source} WHERE source = '%s' AND textgroup = '%s'", $string, 'default'));

  if (!$st_id) {
    db_query("INSERT INTO {locales_source} (location, source, textgroup) VALUES ('%s', '%s', '%s')", NULL, $string, 'default');
    $st_id = _icl_wrapper_db_result(db_query("SELECT lid FROM {locales_source} WHERE source = '%s' AND textgroup = '%s'", $source, 'default'));
  }
  
  if ($st_id === false) {
    echo '0|' . t('The source was not found.');
  } else {
    $strings[] = array('string_id' => $st_id, 'string_type' => 'locale');
    
    icl_content_send_strings($strings);
    
    echo '1|' . $st_id;
  }
}

function theme_icl_content_queued_strings($form) {
  drupal_add_css(drupal_get_path('module', 'icl_content').'/css/dashboard.css');
  
  $select_header = _icl_wrapper_table_select_header_cell('table_select_header_cell', array());
  $header = array($select_header, t('String'));
  
  foreach (element_children($form['id']) as $key) {
    $row = array();      
    $row[] = drupal_render($form['strings'][$key]);
    $row[] = drupal_render($form['string'][$key]);
    $rows[] = $row;
  }
  
  $output = _icl_wrapper_theme('table', array('header' => $header, 'rows' => $rows));
  
  return $output;
}

function icl_content_string_form_table($string_id) {
   $form = array(
    'id' => array(),
    'source' => array(),
    'string' => array(),
  );
  $form['#theme'] = 'icl_content_queued_strings';
  $strings = array();
  $source_lang = language_default()->language;

  if ($string_id == 'queued') {
    $strings_for_translation = variable_get('icl_strings_queued_for_translation', array());
  } else {
    // get the strings from the database table icl_string_group
    $strings_for_translation = array();
    $query = db_query("SELECT string_id, string_type FROM {icl_string_group} WHERE translation_group_id = %d", $string_id);
    while ($row = db_fetch_array($query)) {
      $strings_for_translation[] = $row;
    }
  }
  foreach ($strings_for_translation as $st_data) {
    $id = 'locale-' . $st_data['string_id'];
    $form['id'][$id] = array('#value' => $st_data['string_id']);
    
    if ($st_data['string_type'] == 'locale') {
      $string_source = _icl_wrapper_db_result(db_query("SELECT source FROM {locales_source} WHERE lid=%d", $st_data['string_id']));
      
      $form['string'][$id] = array('#value' => $string_source);
      $strings[$id] = $id;
    }
    
    $form['source'][$id] = array('#value' => $st_data['string_type']);
  }
  
  if ($string_id == 'queued') {
    $form['strings'] = array('#type' => 'checkboxes', '#options' => $strings);
  }
  return $form;
}

function icl_content_send_queued_strings() {
 
  $string_id = arg(2);
  
  $form['string_table'] = icl_content_string_form_table($string_id);
  
  if ($string_id == 'queued') {
    if (sizeof(variable_get('icl_strings_queued_for_translation', array())) == 0) {
      $form['no_strings'] = _icl_wrapper_form_create_markup(array (
            '#type' => 'markup', 
            '#prefix' => '<div class="status"><b>', 
            '#suffix' => '</b></div>', 
            '#value' => t('There are no strings queued for translation')
          ));
    
      
      
    } else {
      
      $form['action']['operations']['cancel_request'] = array(
        '#type' => 'submit',
        '#validate' => array('icl_content_send_queued_strings_validate'),
        '#submit' => array('icl_content_cancel_queued_strings_submit'),
        '#value' => t('Cancel selected strings'),
        '#weight' => -1,
        );
      
    }   
  } else {
    $form['notice'] = _icl_wrapper_form_create_markup(array(
      '#type' => 'markup',
      '#value' => t('These strings have been sent for translation'),
    ));
  }
  
  return $form;
}

function icl_content_send_queued_strings_validate($form, &$form_state) {
}

function _icl_content_string_get_parts($id) {
  $parts = explode('-', $id);
  if (sizeof($parts) > 3) {
    // Combine the language code parts that have been split.
    // eg. pt-pt, pt-br, zh-hans, zh-hant
    $parts[2] .= '-' . $parts[3];
  }
  
  return $parts;
    
}

function icl_content_cancel_queued_strings_submit($form, &$form_state) {
  if (isset($_POST['strings'])) {
    
    // remove the selected strings for the waiting list.

    $strings_waiting_for_translation = variable_get('icl_strings_queued_for_translation', array());
    
    foreach($_POST['strings'] as $id => $state) {
      $parts = _icl_content_string_get_parts($id);

      // remove from the waiting list.
      foreach ($strings_waiting_for_translation as $index_1 => $st_data) {
        if($st_data['string_type'] == $parts[0] && $st_data['string_id'] == $parts[1]) {
          unset($strings_waiting_for_translation[$index_1]);
          break;
        }
      }
    }

    // save the strings waiting.
    if (sizeof($strings_waiting_for_translation) == 0) {
      variable_del('icl_strings_queued_for_translation');
    } else {
      variable_set('icl_strings_queued_for_translation', $strings_waiting_for_translation);
    }
    
  }
}

function icl_content_set_string_queue_message() {
  $link = '<a href="' . _icl_wrapper_url(_icl_wrapper_get_root_menu('translation-management/dashboard'), array('query' => 'string=queued')) . '">';
  
  // remove any existing message
  if (isset($_SESSION['messages']['status'])) {
    foreach($_SESSION['messages']['status'] as $key => $value) {
      if (strpos($value, t('queued for translation')) !== FALSE) {
        unset($_SESSION['messages']['status'][$key]);
      }
    }
    if (sizeof($_SESSION['messages']['status']) == 0) {
      unset($_SESSION['messages']['status']);
    }
  }
  
  if (strpos(request_uri(), 'icl_content/icl_send_queued_strings') === FALSE) {
    // Add message about waiting string translations.
    $strings_waiting_for_translation = variable_get('icl_strings_queued_for_translation', '');
    
    if ($strings_waiting_for_translation != '') {
      $count = sizeof($strings_waiting_for_translation);
      
      if ($count == 1) {
        $message = t('There is 1 string queued for translation.<br />!linkGo to the translation dashboard to send to translation</a>', array('!link' => $link));
      } else {
        $message = t('There are @count strings queued for translation.<br />!linkGo to the translation dashboard to send to translation</a>', array('@count' => $count, '!link' => $link));
      }
  
      drupal_set_message($message, 'status', FALSE);
    }
  }
}


function icl_content_translate_strings($strings, $origin, $langcodes, $translators) {

  $site_languages = language_list('language', TRUE);

  // check for queued strings
  foreach ($strings as $k => $group) {
    if ($group == 'queued') {
      
      // create a new string group
      $translation_group_id = _icl_wrapper_db_result(db_query("SELECT max( translation_group_id ) FROM {icl_string_group}")) + 1;
      if ($cached_strings = variable_get('icl_strings_queued_for_translation', 0)) {
        foreach ($cached_strings as $string) {
          db_query("INSERT INTO {icl_string_group} (translation_group_id, string_type, string_id) VALUES (%d, '%s', %d)", $translation_group_id, $string['string_type'], $string['string_id']);
        }
      }
      
      $strings[$k] = $translation_group_id;
      
      break;
    }
  }
  
  // clear the queue
  variable_del('icl_strings_queued_for_translation');
  
  foreach ($strings as $k => $group) {
    
    // get all the strings in a group
    $query = db_query("SELECT string_id, string_type FROM {icl_string_group} WHERE translation_group_id = %d", $group);
    
    $string_items = array();
    while ( $result = db_fetch_array ( $query ) ) {
      $string_items[] = $result;
    }
    
    // Check if in progress
    foreach ($langcodes as $k => $target) {
      
      // see if this group is already in progress.
      $rid = _icl_wrapper_db_result(db_query("SELECT s.rid FROM
                          {icl_string_status} s
                          JOIN
                          {icl_core_status} c
                          ON
                          c.rid = s.rid
                          WHERE
                          s.translation_group_id = %d AND c.target = '%s'", $group, $target));
    
      if ($rid > 0) {
        // already in progress.
        drupal_set_message(t("'String group - @id' has already been sent for translation to @lang", array('@id' => $group, '@lang' => $site_languages[$target]->name)));
        continue;
      }
      $strings_to_send = array();
      
      foreach ($string_items as $string) {
        if (_icl_content_is_string_translation_in_progress($string, $target)) {
          drupal_set_message(t("Translation is in progress for 'Strings @id' to @lang", array('@id' => $string['string_id'], '@lang' => $site_languages[$target]->name)));
        } else {
          $strings_to_send[] = $string;
        }
      }
        
      $md5 = '';
      // Constuct fields for job insert
      $fields = array(0 => array('type' => 'sid', 'translate' => 0, 'text' => $group));
      foreach ($strings_to_send as $st) {
        $st_id = $st['string_id'];
        if ($st['string_type'] == 'locale') {
          $string = db_fetch_object(db_query("SELECT location, source FROM {locales_source} WHERE lid= %d", $st_id));
        }
        if ($string) {
          $fields[] = array(
            'translate'=>0,
            'text'=>$string->location,
            'type'=>'string-'.$st['string_type'].$st_id.'-name'
            );
          $fields[] = array(
            'translate'=>1,
            'text'=>$string->source,
            'type'=>'string-'.$st['string_type'].$st_id.'-value'
            );
          
          $md5 .= $string->source;
        }
      }
      
      $md5 = md5($md5);
        
      
      $rids_sent = icl_core_send_content_for_translation('icl_content',
                                            $fields,
                                            $site_languages[$origin],
                                            array($site_languages[$target]),
                                            NULL,
                                            "",
                                            "Strings",
                                            $translators
                                            );
      
      
      foreach ($rids_sent as $rid) {
        if ($rid != 0) {
          db_query ( "INSERT INTO {icl_string_status} VALUES(%d, %d, %d, '%s')", $rid, $group, time (), $md5 );
        }
      }      
    }
  }
}

function _icl_content_is_string_translation_in_progress($string, $target) {
  return FALSE;
}

function icl_content_get_strings_for_dashboard($icl_content_dashboard_filter) {
  $languages = locale_language_list();

  if ($icl_content_dashboard_filter) {
    if ($icl_content_dashboard_filter['language'] != 'en') {
      // Can only translate blocks from 'English'
      return array();
    }
    
    if (isset($icl_content_dashboard_filter['type_type']) && isset($icl_content_dashboard_filter['type_enabled'])) {
      if ($icl_content_dashboard_filter['type_enabled']) {
        if ($icl_content_dashboard_filter['type_type'] != 'strings') {
          // selecting a different type so return an empty array.
          return array();
        }
      }
    }
  }
  
  $content = array();

  $res = db_query("SELECT DISTINCT translation_group_id FROM {icl_string_group}");

  $result = array();
  $translation_group_id = array();
  while($row = db_fetch_array($res)){
    $result[] = $row;
    $translation_group_id[] = $row['translation_group_id'];
  }
    
  
  $status_id = array();
  
  if (sizeof($translation_group_id) > 0) {
    $translation_group_id = implode(',', $translation_group_id);
    foreach ($languages as $lang => $name) {

      $status_id[$lang] = array();
        $status_res = db_query("SELECT c.rid, c.status, s.translation_group_id
                                FROM
                                  {icl_string_status} s
                                JOIN
                                  {icl_core_status} c
                                ON
                                  s.rid = c.rid
                                  
                                WHERE s.translation_group_id IN (%s) AND c.target='%s'", $translation_group_id, $lang);
      
      while($row = db_fetch_array($status_res)){
        if (!isset($status_id[$lang][$row['translation_group_id']])) {
          $status_id[$lang][$row['translation_group_id']] = array();
        }
        $status_id[$lang][$row['translation_group_id']][] = $row;
      }

    }
    
  }
  
  
  foreach ($result as $row) {
    $status = array('id' => 'string-' . $row['translation_group_id'],
                    'link' => 'icl_content/icl_queued_strings/' . $row['translation_group_id'],
                    'type' => 'icl_strings_marker',
                    'status' => t('Queued'),
                    'title' => t('String group - ') . $row['translation_group_id'],
                    'targets' => array());
    foreach ($languages as $lang => $name) {
      if ($lang != $icl_content_dashboard_filter['language']) {
        $status['targets'][$lang] = array();
  
        // Find the current rid and rid_status.
        $status['targets'][$lang]['current_rid'] = 0;
        $status['targets'][$lang]['rid_status'] = 0;
        $status['targets'][$lang]['needs_update'] = 0;
        $status['targets'][$lang]['translated'] = FALSE;

        if (isset($status_id[$lang][$row['translation_group_id']])) {
          foreach($status_id[$lang][$row['translation_group_id']] as $status_row) {
            if ($status_row['rid'] > $status['targets'][$lang]['current_rid']) {
              $status['targets'][$lang]['current_rid'] = $status_row['rid'];
              $status['targets'][$lang]['rid_status'] = $status_row['status'];
            }
          }
        }
        
        
      }
    }
    $content[] = $status;
  }
  
  if ($content_strings = variable_get('icl_strings_queued_for_translation', 0)) {
    // Handle queued strings specially
    $languages_list = language_list('enabled');
    foreach($languages_list[1] as $lang){
      if ($lang->language == $icl_content_dashboard_filter['language']) {
        continue;
      }
      $item['targets'][$lang->language]['rid_status'] = 0;
      $item['targets'][$lang->language]['current_rid'] = 0;
      $item['targets'][$lang->language]['translated'] = 0;
      $item['targets'][$lang->language]['current_rid'] = 0;
      $item['targets'][$lang->language]['translated'] = FALSE;
    }
    $item['title'] = t('Queued strings');
    $item['id'] = 'string-queued';
    $item['type'] = 'icl_strings_marker';
    $item['status'] = t('Queued');
    $item['link'] = 'icl_content/icl_queued_strings/queued';
    $content[] = $item;
  }
  
  return $content;
}

function _icl_content_get_words_for_string($string_group) {
  // get all the strings in a group
  
  $string_items = array();
  if ($string_group == 'queued') {
    if ($cached_strings = variable_get('icl_strings_queued_for_translation', 0)) {
      $string_items = $cached_strings;
    }
  } else {
    $query = db_query("SELECT string_id, string_type FROM {icl_string_group} WHERE translation_group_id = %d", $string_group);
    
    $string_items = array();
    while ( $result = db_fetch_array ( $query ) ) {
      $string_items[] = $result;
    }
  }
  
  $fields = array();
  foreach ($string_items as $st) {
    $st_id = $st['string_id'];
    $string = null;
    if ($st['string_type'] == 'locale') {
      $string = db_fetch_object(db_query("SELECT location, source FROM {locales_source} WHERE lid=%d", $st_id));
    }
    if ($string) {
      $fields[] = array(
        'translate'=>0,
        'text'=>$string->location,
        'type'=>'string-'.$st['string_type'].$st_id.'-name'
        );
      $fields[] = array(
        'translate'=>1,
        'text'=>$string->source,
        'type'=>'string-'.$st['string_type'].$st_id.'-value'
        );
    }
  }
      
  $string_data = icl_content_calculate_md5_and_words_from_data($fields);
  
  return $string_data['words'];
}
