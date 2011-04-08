<?php

function _icl_translate_test() {
  switch ($_GET['icl_translate_test']) {
    
    case 1:
      drupal_set_message('testing mail');
		  _icl_translate_notify_daily_digest_process(1);
      break;
  }
}

function _icl_translate_test_get_node_and_save_to_database($nid, $rid) {
  $node = node_load($nid);
  $data = _icl_content_extract_node($node);
  _icl_translate_insert_bulk($rid, $data);
}

function _icl_translate_test_repack($rid = 1234) {
  echo '<pre>'; print_r(_icl_translate_send_to_icl_content_icanlocalize($rid)); echo '</pre>';
}