<?php
// icl_translate.editor_form.inc

module_load_include('inc', 'icl_translate', 'icl_translate.translator');
module_load_include('inc', 'icl_translate', 'icl_translate.notifications');

function icl_translate_editor($form) {
  
  $rid = arg(1);
  global $user;
  
  _icl_translate_add_scripts();
  drupal_add_css(drupal_get_path('module', 'icl_translate') . '/css/icl_translate_editor.css');
  drupal_add_js('misc/jquery.form.js');
  drupal_add_js(drupal_get_path('module', 'icl_translate') . '/js/icl_translate_editor.js');
  drupal_add_js('jQuery(document).ready(function () { jQuery("#edit-cancel").click(function() { if (!confirm(\'' . t('Your translation will be lost') . '\')) return false; }); });', 'inline');
  
  drupal_add_js(array('#icl-translate-editor' => array('submit' => t('Save translation'))), 'setting');
  
  // Get origin and target languages
  // @todo find better function for getting lang
  if ($core_status = _icl_translate_get_core_status($rid)) {
    $original_lang = db_fetch_array(_icl_wrapper_db_query("SELECT * FROM {icl_languages} WHERE code='%s'", $core_status['origin']));
    $target_lang = db_fetch_array(_icl_wrapper_db_query("SELECT * FROM {icl_languages} WHERE code='%s'", $core_status['target']));
  }
  
  if (!_icl_translate_can_translate($rid, TRUE)) {
    $form = array();
    // Display access message
    $form['message'] = _icl_wrapper_form_create_markup(array('#value' => t('Sorry, you don\'t have enough permissions to edit this translation')));
    return $form;
  }
  
  if (_icl_translator_check_unassigned($rid)) {
    drupal_add_js(array('icl_editor_unload' => array(
      'message' => t("Notice: you're removed from this job"),
      'ajax_url' => _icl_wrapper_url(_icl_wrapper_get_root_menu('translation-management/translator')),
      'uid' => $user->uid,
      'rid' => $rid)),
      'setting'
    );
    drupal_add_js('jQuery(document).ready(function () { iclTranslateEditorLeavePage(); });', 'inline');
  }
  
  _icl_translate_set_to_in_progress($rid);
  
  if ($fields = icl_translate_get_fields($rid)) {
    
    // Fetch previous data here, we'll need it anyway
    if ($fields[0]['previous_id']) {
      $previous_data = icl_translate_get_fields($fields[0]['previous_id']);
    }
    
    // Start setting form
    $form = array();
    
    // Set autosaves and determine type
    $autosaves = array();
    $type = FALSE;
    foreach ($fields as $k => $field) {
      if (strpos($field['field_type'], '-icl-autosave')) {
        $autosaves[$field['field_type']] = $field;
        unset($fields[$k]);
      }
      else if (!$type) {
        $type = _icl_translate_editor_get_id($field['field_type'], unserialize($field['field_data']));
      }
    }
    
    // @todo Add determination for Contact form
    if (!$type) {
      $type = array('id' => 1, 'type' => 'contact_form', 'element_id' => 'contact_form');
    }
    
    // Basic info
    $form['info'] = _icl_wrapper_form_create_markup(array(
      '#value' => '<p>' . t('You are translating !info from @origin to @target', array('!info' => _icl_translate_editor_get_title($type['type'], $type['id']),
                                                                                       '@origin' => $original_lang['icl_name'],
                                                                                       '@target' => $target_lang['icl_name'])) . '</p>'));
    
    // Set 'stop being translator button'
    $form['stop_being_translator'] = array(
      '#type' => 'submit',
      '#submit' => array('icl_translate_editor_submit_stop'),
      '#value' => t('Stop being the translator for this document'),
      '#name' => 'stop_being_translator',
      '#prefix' => '<p>' . t('This job is currently assigned to you') . '<br />',
      '#suffix' => '</p>',
      '#attributes' => _icl_wrapper_form_create_attributes(array('style' => 'margin:0;'))
    );
    
    if (module_exists('xliff')) {
      $form['xliff'] = _icl_translate_editor_xliff($form);
    }
    
    // Form redirection
    _icl_wrapper_form_create_redirect($form, array('translator', 'finished=' . $type['id'] . '&type=' . $type['type']));
    
    if ($type['type'] == 'node') {
      $format = _icl_translate_get_wysiwyg_support($type['id']);
    }
    
    foreach ($fields as $field) {
      
      // Skip untranslatable fields
      if (!$field['field_translate']) {
        continue;
      }
      
      // Set element name
      $name = _icl_translate_editor_sanitize_name('convert', $rid, $field['field_type']);
      
      // Set field original data
      $field_data = _icl_translate_editor_sanitize_serialized_data($field['field_data']);
      if (empty($field_data)) {
        $field_data = '';
      }
      
      // Set field original data
      $field_data_translated = _icl_translate_editor_sanitize_serialized_data($field['field_data_translated']);
      
      // Set 'this translation is finished' checkbox
      $finished = $field['finished'];
      
      if (empty($field_data_translated)) {
        // Use original data if translation is not set
        $field_data_translated = $field_data;
        // @todo Reconsider setting to unfinished if data is empty
        $finished = 0;
      }
      
      $title = ($type['type'] == 'strings') ? '' : $field['field_type'];
      
      // Set fieldset holder
      $form[$field['field_type']] = array (
        '#type' => 'fieldset', 
        '#title' => ucfirst(str_replace('_', ' ', t($title))),
        '#collapsible' => TRUE
      );
      
      // Check if doesn't need update, compare previous requests
      if ($field['previous_id']) {
        if (_icl_editor_translate_compare_to_previous($field['field_type'], $field_data, $previous_data)) {
          $form[$field['field_type']]['1_finished_message'] = _icl_wrapper_form_create_markup(array('#value' => '<div>' . t('This content was translated previously and the original has not changed since then.' . '</div>')));
          $finished = 1;
        }
      }
      
      // Display autosave toggle if necessary
      $autosave_data = '';
      if (isset($autosaves[$field['field_type'] . '-icl-autosave'])) {
        
        $autosave_data = unserialize($autosaves[$field['field_type'] . '-icl-autosave']['field_data_translated']);
        
        if (is_array($autosave_data)) {
          $autosave_data = implode(', ', array_values($autosave_data));
        }
        // Check if not empty, compare timestamp and content
        if (!empty($autosave_data)
            && $autosaves[$field['field_type'] . '-icl-autosave']['timestamp'] > $field['timestamp']
            && !_icl_translate_editor_compare_data($autosave_data, $field_data_translated)) {
          
          $form[$field['field_type']]['autosave'] = _icl_wrapper_form_create_markup(array(
            '#value' => '<div class="icl_translate_editor_load_autosave">'
            . t('More recent autosave available (click for toggle replace)')
            . '<div class="icl_translate_hidden">' . $autosave_data . '</div></div>'
          ));
        }
      }
      
      // Set 'this translation is finished' checkbox
      $form[$field['field_type']]['finished'] = array (
        '#type' => 'checkbox', 
        '#title' => t('This translation is finished'),
        '#attributes' => _icl_wrapper_form_create_attributes(array('class' => 'finished')),
        '#name' => $name . '[field_finished]',
        '#default_value' => $finished
      );
      
      // Set translation content field
      $element_type = _icl_translate_editor_get_element_type($field['field_type']);
      $lenght = strlen(strip_tags($field_data_translated));
      $rows = round($lenght/60) + 2;
      $form[$field['field_type']]['field_data_translated']['field_data_translated'] = array(
        '#title' => sprintf(t('Translated content - %s'), $target_lang['icl_name']),
        '#name'=> $name . '[field_data_translated]',
        '#type' => $element_type,
        '#default_value' => $field_data_translated,
        '#rows' => $rows,
        '#id' => 'edit-field-data-translated-' . _icl_translate_editor_sanitize_id($field['field_type']) . '-' . $type['element_id'],
      );
      
      if (user_access('administer filters') && $type['type'] == 'node' && $field['field_type'] == 'body') {
        $form[$field['field_type']]['field_data_translated']['format'] = filter_form($format, NULL, array($field['field_type'], 'field_data_translated_format'));
      }
      
      // Set original content field
      $form[$field['field_type']]['field_data'] = _icl_wrapper_form_create_markup(array(
        '#value' => '<div class="icl_translate_hidden original_data">'
        . sprintf(t('Original content - %s:'), $original_lang['icl_name'])
        . '<br /><div class="field_data">' . $field_data . '</div></div>'
      ));
      
      // Set hidden format field
      $form[$field['field_type']]['field_format']= array(
        '#name'=> $name . '[field_format]',
        '#type' => 'hidden',
        '#default_value' => $field['field_format']
      );
    }
    
    // Set hidden rid field
    $form['rid']= array(
      '#name'=> 'rid',
      '#type' => 'hidden',
      '#default_value' => $rid
    );
    
    // 'This translation is finished checkbox
    $form['finished'] = array(
      '#type' => 'checkbox',
      '#id' => 'icl-translate-editor-finished',
      '#title' => t('Translation of this document is complete'),
      '#attributes' => _icl_wrapper_form_create_attributes(array('disabled' => 'disabled')),
      '#name' => 'finished',
      '#default_value' => _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT translated FROM {icl_translate_job} WHERE rid=%d", $rid)),
    );
    
    // Set submit button
    $form['action'] = array(
      '#type' => 'submit',
      '#submit' => array('icl_translate_editor_submit'),
      '#value' => t('Save translation'),
      //'#attributes' => _icl_wrapper_form_create_attributes(array('disabled' => 'disabled')),
      '#name' => 'save_translation'
    );
    
    // Set cancel button
    $form['cancel'] = array(
      '#type' => 'submit',
      '#submit' => array('icl_translate_editor_submit_cancel'),
      '#value' => t('Cancel'),
      '#name' => 'cancel'
    );
    
    return $form;
  }
}

function icl_translate_editor_submit(&$form, &$form_state) {
  
  if (isset($_POST['rid'])) {
    $rid = $_POST['rid'];
  }
  
  if (!isset($_POST['finished'])) {
    _icl_wrapper_form_create_redirect($form, array('translator'));
  }
  
  if ($rid && _icl_translate_can_translate($rid)) {
    
    // Delete autosave
    _icl_translate_editor_autosave_delete($rid);
    
    // Check timeout
    if (isset($_REQUEST['icl_ajax'])) {
      if (_icl_translator_check_timeout($rid)) {
        global $user;
        _icl_translator_remove_job($user->uid, $rid);
        _icl_translator_remove_unassigned_job($rid);
        die();
      }
    }
    
    // Process fields
    foreach ($_POST[$rid] as $type => $data) {
      
      // Process CCK
      if ($type == 'CCK') {
        
        foreach ($data as $cck => $cck_data) {
          $cck_data['field_finished'] = isset($cck_data['field_finished']) ? 1 : 0;
          $cck_update = explode(',', $cck_data['field_data_translated']);
          
          foreach ($cck_update as $cck_update_key => $cck_update_value) {
            $cck_update[$cck_update_key] = trim($cck_update_value);
          }
          
          // Autosave
          if (isset($_REQUEST['icl_ajax'])) {
            _icl_translate_editor_autosave($rid, 'CCK[' . $cck . ']', $cck_update, $cck_data['field_finished']);
          }
          // Regular
          else {
            icl_translate_update_field_translation($rid, 'CCK[' . $cck . ']', $cck_update, $cck_data['field_finished']);
          }
        }
        continue;
      }
      
      // Process other

      $data['field_finished'] = isset($data['field_finished']) ? 1 : 0;

      if ($data['field_format'] == 'csv') {
        $data['field_data_translated'] = _icl_translate_editor_sanitize_serialized_data($data['field_data_translated'], 'revert');
      }
      
      // Autosave
      if (isset($_REQUEST['icl_ajax'])) {
        _icl_translate_editor_autosave($rid, _icl_translate_editor_sanitize_name('revert', $rid, $type), $data['field_data_translated'], $data['field_finished']);
      }
      // Regular
      else {
        icl_translate_update_field_translation($rid, _icl_translate_editor_sanitize_name('revert', $rid, $type), $data['field_data_translated'], $data['field_finished']);
      }
    }
    
    // Set job as finished
    if (!isset($_REQUEST['icl_ajax']) && isset($_REQUEST['finished'])) {
      _icl_translate_finish_job($rid);
      
      // unXLIFF rid
      $xliffed = variable_get('icl_translate_xliffed', array());
      unset($xliffed[$rid]);
      variable_set('icl_translate_xliffed', $xliffed);
    }
  }
  
  // If AJAX autosave die()
  if (isset($_REQUEST['icl_ajax'])) {
    die('autosaved');
  } else {
    // @todo Consider removing unassigned job if translator clicked 'Save translation'
    _icl_translator_remove_unassigned_job($rid);
  }
}








 /**
 * Autosave insert.
 */
function _icl_translate_editor_autosave($rid, $type, $data, $finished) {
  $finished = (bool)$finished ? 1 : 0;
  $data = array(
    'rid' => $rid,
    'timestamp' => time(),
    'field_type' => $type . '-icl-autosave',
    'field_data_translated' => serialize($data),
    'finished' => $finished
  );
  drupal_write_record('icl_translate', $data);
}

 /**
 * Autosave delete.
 */
function _icl_translate_editor_autosave_delete($rid) {
  _icl_wrapper_db_query("DELETE FROM {icl_translate} WHERE field_type LIKE '%-icl-autosave%' AND rid=%d", $rid);
}

 /**
 * Determine type.
 * @todo Remove
 */
function _icl_translate_editor_get_id($field_type, $data) {
  $types = array('nid' => 'node', 'bid' => 'block', 'sid' => 'strings');
  foreach ($types as $type_id => $type) {
    if ($field_type == $type_id) {
      if ($type == 'node') {
        $node = node_load($data);
        $element_id = 'node-' . $node->type . '-' . $data;
      }
      else if ($type == 'block') {
        $element_id = 'block-' . $data;
      }
      else if ($type = 'strings') {
        $element_id = 'strings-' . $data;
      }
      return array('type' => $type,
                   'type_id' => $type_id,
                   'id'=> $data,
                   'element_id' => $element_id);
    }
  }
  return FALSE;
}

 /**
 * Process serialized data.
 */
function _icl_translate_editor_sanitize_serialized_data($data, $action = 'convert') {
  switch ($action) {
    
    case 'revert':
      $data = explode(',', $data);
      foreach ($data as $k => $v) {
        $data[$k] = trim($v);
      }
      break;
    
    default:
      $data = unserialize($data);
      if (!empty($data)) {
        if (is_array($data)) {
          $data = implode(', ', array_values($data));
        }
      }
  }
  return $data;
}

 /**
 * Sanitize element name.
 * 
 * @param string $action
 *      convert/revert
 */
function _icl_translate_editor_sanitize_name($action = 'convert', $rid, $type) {
  switch ($action) {
    
    case 'revert':
      $name = str_replace('--bl--', '[', str_replace('--br--', ']', $type));
      break;
    
    default:
      if (strpos($type, 'CCK[') !== FALSE) {
        $name = explode('[', $type);
        $name = trim($name[1], ']');
        $name = $rid . '[CCK][' . $name . ']';
      }
      else if (preg_match_all('/\[([^]]+)\]/', $type, $matches)) {
        $name = $rid . '[' . str_replace('[', '--bl--', str_replace(']', '--br--', $type)) . ']';
      }
      else {
        $name = $rid . '[' . $type . ']';
      }
  }
  return $name;
}

 /**
 * Sanitize element id.
 * 
 */
function _icl_translate_editor_sanitize_id($type) {
  $patterns = array('/\]\[/', '/\[/', '/\]$/', '/\]/');
  $replace = array('-', '-', '', '-');
  return preg_replace($patterns, $replace, $type);
}

 /**
 * Compare previous version to current field.
 *
 * @param string $type
 *      Current field type (field_type)
 * @param string $data
 *      Current original field data (field_data)
 * @param array $previous
 *      Previous request data
 *
 * @return boolean
 */
function _icl_editor_translate_compare_to_previous($type, $data, $previous) {
  
  // Loop through previous fields
  foreach ($previous as $previous_field) {
    if ($previous_field['field_type'] == $type) {
      $data2 = _icl_translate_editor_sanitize_serialized_data($previous_field['field_data']);
      return _icl_translate_editor_compare_data($data2, $data);
    }
  }
  
  return FALSE;
}

 /**
 * Compare serialized data.
 */
function _icl_translate_editor_compare_data($data, $data2) {
  return ereg_replace("[\r\t\n\v]", "", trim($data)) === ereg_replace("[\r\t\n\v]", "", trim($data2));
}

 /**
 * Get node format.
 */
function _icl_translate_get_wysiwyg_support($nid) {
  $table_name = _icl_wrapper_table_name('node_revisions');
  $format = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT format FROM {" . $table_name . "} WHERE nid=%d", $nid));
  return $format;
}

 /**
 * Title/link for top basic info.
 */
function _icl_translate_editor_get_title($type, $id) {
  $table_name = _icl_wrapper_table_name('node_revisions');
  switch ($type) {
    
    case 'node':
      return '<a href="' . url('node/' . $id) . '">' . check_plain(_icl_wrapper_db_result(_icl_wrapper_db_query("SELECT title FROM {" . $table_name . "} WHERE nid=%d", $id))) . '</a>';
      break;
    
    case 'block':
      $table_name = _icl_wrapper_table_name('blocks');
      return '<strong>' . check_plain(_icl_wrapper_db_result(_icl_wrapper_db_query("SELECT title FROM {" . $table_name . "} WHERE bid=%d", $id))) . '</strong> block';
      break;
    
    case 'contact_form':
      return t('Contact form');
      break;
    
    case 'strings':
      return '<strong>'. t('Queued strings @id', array('@id'=> $id)) . '</strong>';
      break;
  }
}

 /**
 * Remove translator from job and reset job info.
 */
function icl_translate_editor_submit_stop() {
  global $user;
  $rid = arg(1);
  _icl_translate_notify($user->uid, 'translator_self_removed_from_job', $rid);
  _icl_translator_remove_job($user->uid, $rid);
  _icl_translator_remove_unassigned_job($rid);
  icl_translate_editor_submit_cancel();
}

 /**
 * Remove translator from job and reset job info.
 */
function icl_translate_editor_submit_cancel() {
  global $user;
  $rid = arg(1);
  if (_icl_translator_check_unassigned($rid)) {
    _icl_translator_remove_job($user->uid, $rid);
    _icl_translator_remove_unassigned_job($rid);
  }
  _icl_wrapper_drupal_goto('translator');
}

 /**
 * If XLIFF module enabled - offer download/upload in XLIFF format.
 */
function _icl_translate_editor_xliff(&$current_form) {
  
  // Check requirements
  if (!class_exists('DOMDocument', FALSE) || !class_exists('XSLTProcessor', FALSE)) {
    //drupal_set_message('XLIFF Export: no DOM or XSLT class', 'error');
    return FALSE;
  }
  
  $rid = arg(1);
  $xliffed = variable_get('icl_translate_xliffed', array());
  
  $form['xliff'] = array (
    '#type' => 'fieldset', 
    '#title' => 'Export/import translation as XLIFF',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  
  switch (isset($xliffed[$rid])) {
    
    case FALSE:
      $form['xliff']['download_xliff'] = array(
        '#type' => 'submit',
        '#submit' => array('icl_translate_editor_submit_xliff_download'),
        '#value' => t('Download as XLIFF'),
        '#name' => 'download_xliff',
        '#attributes' => _icl_wrapper_form_create_attributes(array('style' => 'margin:0;')),
      );
      break;
    
    case TRUE:
       $form['xliff']['upload_xliff_file'] = array(
        '#type' => 'file',
        '#submit' => array('icl_translate_editor_submit_xliff_upload'),
        '#title' => t('Upload XLIFF'),
        '#attributes' => _icl_wrapper_form_create_attributes(array('style' => 'margin:0;')),
        '#file_extensions' => 'xlf',
      );
      $form['xliff']['upload_xliff_submit'] = array(
        '#type' => 'submit',
        '#submit' => array('icl_translate_editor_submit_xliff_upload'),
        '#value' => t('Upload XLIFF'),
        '#name' => 'upload_xliff',
        '#attributes' => _icl_wrapper_form_create_attributes(array('style' => 'margin:0;')),
      );
      $form['xliff']['download_xliff'] = array(
        '#type' => 'submit',
        '#submit' => array('icl_translate_editor_submit_xliff_download'),
        '#value' => t('Download translation as XLIFF'),
        '#name' => 'download_xliff',
        '#attributes' => _icl_wrapper_form_create_attributes(array('style' => 'cursor: pointer; border:none; font-size:10px; margin:0;')),
      );
      $current_form['#attributes'] = _icl_wrapper_form_create_attributes(array('enctype' => "multipart/form-data"));
      drupal_add_js(array('icl_translate_editor_disable_autosave' => 1, 'icl_translate_editor_disable_leave' => 1), 'setting');
      break;
  }
  
  return $form;
}

 /**
 * Download XLIFF callback.
 */
function icl_translate_editor_submit_xliff_download() {
  if (!_icl_translate_export_xliffed(arg(1))) {
    drupal_set_massage(t('No translation fields for required document'), 'error');
  }
  _icl_wrapper_drupal_goto('translator');
  exit;
}

 /**
 * Serve XLIFF for download.
 */
function _icl_translate_export_xliffed($rid) {
  
  if (!$fields = icl_translate_get_fields($rid)) {
    return FALSE;
  }
  
  // Check reqirements
  if (!function_exists('xliff_html2unicode')) {
    module_load_include('module', 'xliff', 'xliff');
    if (!function_exists('xliff_html2unicode')) {
      drupal_set_message("Couldn't load XLIFF module", 'error');
      _icl_wrapper_drupal_goto('translate/' . $rid);
      return FALSE;
    }
  }
  
  $xliffed = variable_get('icl_translate_xliffed', array());
  
  // Set as XLIFFed
  $xliffed[$rid] = 1;
  variable_set('icl_translate_xliffed', $xliffed);
  
  // Remove from unassigned jobs
  _icl_translator_remove_unassigned_job($rid);
  
  // Create output
  
  $doc = new DOMDocument();
  $xsl = new DOMDocument();
  $proc = new XSLTProcessor();
  
  // Edit template
  $template = file_get_contents(drupal_get_path('module', 'xliff') . '/xsl/xml2xliff.xsl');
  $core_status = _icl_translate_get_core_status($rid);
  $template = str_replace('source-language="en"',
                          'source-language="' . $core_status['origin']
                          . '" target-language="' . $core_status['target'] . '"',
                          $template);
  
  $xsl->loadXML($template);
  
  $proc->ImportStyleSheet($xsl);
  
  $process = '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html>
  <head>
    <title>(don\'t translate)</title>
  </head>
  <body>';
  
  // Add fields to output
  foreach ($fields as $field) {
    
    if (!$field['field_translate']) {
      continue;
    }
    
    $data = _icl_translate_editor_sanitize_serialized_data($field['field_data']);
    $data_translated = _icl_translate_editor_sanitize_serialized_data($field['field_data_translated']);
    if (empty($data_translated)) {
      $data_translated = $data;
    }
    
    $origin = xliff_html2unicode($data);
    $translation = xliff_html2unicode($data_translated);
    $process .= '
    <div id="xliff-' . $field['field_type'] . '">' . $origin . '</div>';
  }
  
  $process .= '
  </body>
</html>';
  
  @$doc->loadXML($process);
  $content = $proc->transformToXML($doc);
  
  // Serve download
  
  if (function_exists('gzencode')) {
    $header = 'Content-type: application/x-gzip';
    $filename = 'xliff-bulk-export.tgz';
  }
  else {
    $header = 'Content-type: application/x-tar';
    $filename = 'xliff-bulk-export.tar';
  }
  
  $filename =  variable_get('site_name', 'Drupal') . '-translation-' . $rid . '.xlf';
  
  // Clear out output buffer to remove any garbage from tar output.
  if (ob_get_level()) {
    ob_end_clean();
  }
  
  
  // required for IE, otherwise Content-Disposition may be ignored
  if (ini_get('zlib.output_compression')) {
    ini_set('zlib.output_compression', 'Off');
  }
  _icl_wrapper_drupal_set_header('Content-Type', 'application/force-download');
  //drupal_set_header('Content-Type: ' . $mime_type);
  _icl_wrapper_drupal_set_header('Content-Disposition', 'attachment; filename="' . $filename . '"');
  //drupal_set_header("Content-Transfer-Encoding: binary");
  //drupal_set_header('Accept-Ranges: bytes');
  //drupal_set_header("Cache-control: private");
  //drupal_set_header('Pragma: private');
  //drupal_set_header("Expires: Mon, 26 Jul 1997 05:00:00 GMT");
  
  print $content;
  exit;
}

 /**
 * Handle XLIFF upload.
 */
function icl_translate_editor_submit_xliff_upload(&$form, &$form_state) {
  
  $rid = arg(1);
  
  if (_icl_translate_can_translate($rid) && $file = file_save_upload('upload_xliff_file', array('file_validate_extensions' => array('xlf')))) {
    
    // Delete autosave
    _icl_translate_editor_autosave_delete($rid);
    
    $doc = new DOMDocument();
    $xsl = new DOMDocument();
    $proc = new XSLTProcessor();
    
    $xsl->load(drupal_get_path('module', 'xliff') .'/xsl/xliff2xml.xsl');
    $proc->ImportStyleSheet($xsl);
    $process = file_get_contents($file->filepath);
    @$doc->loadXML($process);
    $content = $proc->transformToXML($doc);
    
    preg_match_all("/<div\sid\s*=\s*[\"\']xliff-([^\"]*)[\"']>(.*)<\/div>/siU", $content, $matches);
    $fields = array_combine($matches[1], $matches[2]);
    foreach ($fields as $type => $data) {
      if (strpos($type, 'CCK[') !== FALSE) {
        $data = _icl_translate_editor_sanitize_serialized_data($data, 'revert');
      }
      icl_translate_update_field_translation($rid, $type, $data, 1);
    }
    
    // unXLIFF rid
    $xliffed = variable_get('icl_translate_xliffed', array());
    unset($xliffed[$rid]);
    variable_set('icl_translate_xliffed', $xliffed);
  }
  _icl_wrapper_drupal_goto('translate/' . $rid);
}

 /**
 * Determine element type.
 */
function _icl_translate_editor_get_element_type($type) {
  
  $element_type = 'textfield';
  
  if ($type == 'body') {
    $element_type = 'textarea';
  }
  else if (strpos($type, 'CCK[') === 0) {
    $cck_field = explode('[', $type);
    $cck_field = trim($cck_field[1], ']');
    if (db_table_exists('content_node_field_instance') && $widget_type = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT widget_type FROM {content_node_field_instance} WHERE field_name='%s'", $cck_field))) {
      if (in_array($widget_type, array('text_textarea'))) {
        $element_type = 'textarea';
      }
    }
  }
  
  return $element_type;
}