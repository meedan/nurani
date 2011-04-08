<?php
/*
 * icl_translate.jobs.inc
 * 
 * @file This provides the API for management of translation jobs
 * Handles both local jobs and ICanLocalize jobs
 */

 /**
 * Inserts fields for translation into {icl_translate}
 * @todo Move here _icl_translate_insert_bulk() if not needed somewhere else
 * 
 * @param array $fields
 *      Array of content fields
 * @param int $previous_id
 *      If request is already sent
 */
function icl_translate_create_translation_job($fields, $target, $previous_id = 0) {
  $rid = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT max( rid ) FROM {icl_core_status}")) + 1;
  _icl_translate_insert_bulk($rid, $fields, $target, $previous_id);
  
  return $rid;
}

 /**
 * Repacks local translation.
 */
function icl_translate_fetch_translation_wrapper($rid, $language = null) {
  $data = array ();
  if ($language == null) {
    $langs = language_list('language', TRUE);
    $query = _icl_wrapper_db_query( "SELECT target FROM {icl_core_status} WHERE rid = %d", $rid );
    while ( $target = _icl_wrapper_db_result( $query ) ) {
      $data[$target] = _icl_translate_send_to_icl_content_icanlocalize($rid, $langs[$target]);
    }
  } else {
    $data [$language->language] = _icl_translate_send_to_icl_content_icanlocalize($rid, $language);
  }
  return $data;
}


 /**
 * Registers translation with icl_content.module.
 * @see icl_content_icanlocalize(), icl_content.module
 */
function _icl_translate_send_to_icl_content_icanlocalize($rid, $lang) {
  $fields = icl_translate_get_fields($rid);
  $content = array();
  if (!empty($fields)) {
    foreach ($fields as $k => $data) {
      $content[] = _icl_translate_repack($data, $lang->language);
    }
  }
  return $content;
}

 /**
 * Repacks translation data for icl_content.module.
 * @see _icl_translate_send_to_icl_content_icanlocalize()
 */
function _icl_translate_repack($data, $lang) {
  if ($data['field_translate']) {
    $repack['data'] = unserialize($data['field_data_translated']);
    $repack['original_data'] = unserialize($data['field_data']);
  }
  else {
    $repack['data'] = unserialize($data['field_data']);
    $repack['original_data'] = unserialize($data['field_data']);
  }
  $repack['type'] = $data['field_type'];
  $repack['translate'] = $data['field_translate'];
  $repack['format'] = $data['field_format'];
  $repack['language'] = $lang;
  
  return $repack;
}