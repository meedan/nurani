<?php
/*
 * @file The ICanLocalize webservice abstractions
 */


define ( 'ICL_SANDBOX_URL', 'http://sandbox.icanlocalize.com' );
define ( 'ICL_PRODUCTION_URL', 'https://www.icanlocalize.com' );
define ( 'ICL_MODE_PRODUCTION', 'production' );
define ( 'ICL_MODE_SANDBOX', 'sandbox' );

$sandbox_file = dirname(__FILE__) . '/icl_core.sandbox.inc';
if(file_exists($sandbox_file)){
  require $sandbox_file;
}

function icl_core_get_icl_url() {
  $url = variable_get ( 'icl_core_mode', ICL_MODE_PRODUCTION ) == ICL_MODE_PRODUCTION ? ICL_PRODUCTION_URL : ICL_SANDBOX_URL;
  
  return $url;
}
/**
 * Calls a REST service URL
 *
 * @param string $uri The resource URL (without the host) you wish to call
 * @param bool $check_err_code Wether to check if error is returned
 * @param mixed $post Set this to an array of variables you wish to POST or leave it to false if you wish to call with GET
 * @return mixed Either an error message if something gone wrong or a SimpleXMLElement if everything is okay.
 */
function icl_core_call_service($uri, $check_err_code = FALSE, $post = FALSE) {
  global $base_url;

  $url = variable_get ( 'icl_core_mode', ICL_MODE_PRODUCTION ) == ICL_MODE_PRODUCTION ? ICL_PRODUCTION_URL : ICL_SANDBOX_URL;
  
  if(strpos($uri, '[wid]') !== FALSE) {
    $wid = variable_get ( 'icl_core_website_id', FALSE );
    if (! $wid) {
      $message = '-1 The Website ID is not set';
      watchdog ( 'icl_core', $message, array (), WATCHDOG_ERROR );
      return $message;
    }
    $accesskey = variable_get ( 'icl_core_accesskey', FALSE );
    if (! $accesskey) {
      $message = '-2 The Accesskey is not set';
      watchdog ( 'icl_core', $message, array (), WATCHDOG_ERROR );
      return $message;
    }
    
    $request_uri = $url . str_ireplace ( array (
        '[wid]', 
        '[accesskey]' ), array (
        $wid, 
        $accesskey ), $uri );
  } else {
    $request_uri = $url . $uri;
  }
  
  // get the project version from the info file.
  $info_file_name = drupal_get_path('module', 'icl_core') . '/icl_core.info';
  $module_info = drupal_parse_info_file($info_file_name);
  
  if (is_array( $post )) {

    $post['debug_cms'] = "Drupal";
    $post['debug_url'] = $base_url;
    if (isset($module_info['version'])) {
      $post['debug_version'] = $module_info['version'];
    }
    if (isset($module_info['project'])) {
      $post['debug_project'] = $module_info['project'];
    }
  } else {
    $get = array();
    $get['debug_cms'] = "Drupal";
    $get['debug_url'] = $base_url;
    if (isset($module_info['version'])) {
      $get['debug_version'] = $module_info['version'];
    }
    if (isset($module_info['project'])) {
      $get['debug_project'] = $module_info['project'];
    }
    foreach ( $get as $key => $value ) {
      if (strpos($request_uri, '?') !== FALSE) {
        $request_uri .= '&' . $key . '=' . urlencode ( $value );
      } else {
        $request_uri .= '?' . $key . '=' . urlencode ( $value );
      }
    }
  }
  
  if (variable_get('icl_force_http', FALSE)) {
    $request_uri = str_replace('https://', 'http://', $request_uri);
  }
  
  if (is_array ( $post )) {
    $data = array ();
    foreach ( $post as $key => $value ) {
      $data [] = $key . '=' . urlencode ( $value );
    }
    $response = _icl_wrapper_drupal_http_request( $request_uri, array (), 'POST', implode ( '&', $data ) );
  } else {
    $response = _icl_wrapper_drupal_http_request( $request_uri );
  }

  if (isset ( $response->error ) && strpos($request_uri, 'https') !== false) {
    $request_uri = str_replace('https://', 'http://', $request_uri);
    if (is_array ( $post )) {
      $response = _icl_wrapper_drupal_http_request( $request_uri, array (), 'POST', implode ( '&', $data ) );
    } else {
      $response = _icl_wrapper_drupal_http_request( $request_uri );
    }
    $https_reties = variable_get('icl_htpps_retries', 0);
    if (!isset ( $response->error )) {
      // Using http worked - count the number of times this succeeds.
      $https_reties += 1;
      if ($https_reties == 3) {
        variable_set('icl_force_http', TRUE);
      }
    }
    variable_set('icl_htpps_retries', $https_reties);
  }
  
  if (isset ( $response->error )) {
    $message = '-3 The request failed. ';
    if ($response->code < 0) {
      $message .= 'A network error occured: ' . ($response->code * - 1) . ' ' . $response->error;
    } else {
      $message .= 'A service error occured: ' . $response->code . ' ' . $response->error;
    }
    watchdog ( 'icl_core', $message, array (), WATCHDOG_ERROR );
    return $message;
  }
  
  $len = strlen ( $response->data );
  if ($len >= 18 && ! strcmp ( substr ( $response->data, 0, 2 ), "\x1f\x8b" )) {
    // GZIP format
    $error = '';
    $filename = '';
    $response->data = gzdecode ( $response->data, $filename, $error );
    if (! empty ( $error )) {
      $message = '-4 Unable to decompress GZIP response. ' . $error;
      watchdog ( 'icl_core', $message, array (), WATCHDOG_ERROR );
      return $message;
    }
  }
  
  if (module_exists ( 'icl_debug' )) {
    $data = formatXmlString ( $response->data );
    icl_debug_watchdog_debug ( 'icl_core', '%data', array (
        '%data' => $data ) );
  }
  
  $xml = new SimpleXMLElement ( $response->data );
  if ($check_err_code) {
    if ($xml->status ['err_code'] != 0) {
      $code = ( int ) $xml->status ['err_code'];
      $message = ( string ) $xml->status;
      watchdog ( 'icl_core', 'Failed to execute a web service. Returned error was %code %message', array (
          '%code' => $code, 
          '%message' => $message ), WATCHDOG_ERROR );
      return $code . ' ' . $message;
    }
  }
  
  return $xml;
}

function _icl_get_session_id() {
  $request_url = '/login/login.xml';    
  $request_url .= '?accesskey=[accesskey]';
  $request_url .= '&wid=[wid]';
  $request_url .= '&usertype=Client';
  $request_url .= '&compact=1';
  
  $langs = variable_get ( 'icl_core_languages', array() );

  $request_url .= '&email=' . $langs['email'];
  
  $res = icl_core_call_service ($request_url);
  if (is_string($res)) {
    // we have an error
    return NULL;
  } else {
    return (string)$res->session_num;
  }

}

function icl_get_current_session($refresh = false) {

  // see if we need to refresh the reminders from ICanLocalize
  $last_time = variable_get('last_icl_reminder_fetch', 0);
  if ($refresh || (time() - $last_time > 30 * 60)) {
    $session_id = _icl_get_session_id();

    $last_time = time();
    variable_set('icl_current_session', $session_id);
    return $session_id;
  } else {
    return variable_get('icl_current_session', '');
  }
    
}

function are_waiting_for_translators($langs) {
  if (!empty($langs) && isset($langs['available_translators'])) {
    foreach ($langs['available_translators'] as $from_lang => $to_langs) {
      foreach($to_langs as $to => $available) {
        if ($available > 0) {
          if ($langs['applications'][$from_lang][$to] == 0) {
            return true;
          }
        }
      }
    }
    
  }
  
  
  return false;
}

/**
 * Retrieves languages enabled for translation for this website
 *
 * @param bool $cache_clear Set to TRUE if you want to ignore cache.
 * @return mixed If successful, the arra of available language pairs. If fails then the error string is returned.
 */
function icl_core_fetch_languages($cache_clear = FALSE, $from_dashboard = FALSE, $call_once = TRUE) {
  static $langs = array();
  static $cache = array();
  
  if (empty($langs) && ! $cache_clear) {
    $langs = variable_get ( 'icl_core_languages', array() );
  }
  
  if ($from_dashboard && !$cache_clear) {
    $cache_clear = are_waiting_for_translators($langs);
  }
  
  if (!$cache_clear && !isset($langs['url'])) {
    $cache_clear = TRUE;
  }
  
  if (empty($langs) || $cache_clear) {
    
    $cache_id = 'icl_core_fetch_languages';
    
    if (isset($_POST['icl_ajx_action']) || isset($_POST['icl_translator_ajx_action'])) {
      if ($call_once && $cache = cache_get($cache_id)) {
        $langs = $cache->data;
      } else {
        $langs = _icl_core_fetch_languages_once();
      }
    }
    else {
      if ($call_once && isset($cache[$cache_id])) {
        $langs = $cache[$cache_id];
      }
      else {
        $langs = _icl_core_fetch_languages_once();
        $cache[$cache_id] = $langs;
        cache_set($cache_id, $langs);
      }
    }
  }
  
  if (is_string ( $langs )) {
    // There was an error.
    // return the last saved value.
    $saved_langs = variable_get ( 'icl_core_languages', FALSE );
    if ($saved_langs !== FALSE) {
      $langs = $saved_langs;
    }
  }
  
  return $langs;
}

function _icl_core_fetch_languages_once() {
  
  $xml = icl_core_call_service('/websites/[wid].xml?accesskey=[accesskey]', TRUE);
  
  if (is_string ( $xml )) {
      watchdog ( 'icl_core', $xml, array (), WATCHDOG_ERROR );

      return $xml;
    }
    
    $langs['langs'] = array();
    $langs['have_translators'] = array();
    $langs['cost_per_word'] = array();
    $langs['pay_per_ues'] = array();
    $langs['applications'] = array();
    $langs['available_translators'] = array();
    $langs['contract_id'] = array();
    $langs['offer_id'] = array();
    $langs['translators'] = array();
    
    foreach ( $xml->website->translation_languages->translation_language as $item ) {
      $from_name = ( string ) $item ['from_language_name'];
      $to_name = ( string ) $item ['to_language_name'];
      $langs ['langs'][$from_name] [] = $to_name;
      
      if(!isset($langs['have_translators'][$from_name])) {
        $langs['have_translators'][$from_name] = array();
      }
      $langs['have_translators'][$from_name][$to_name] = (int)$item['have_translators'];
      
      if(!isset($langs['cost_per_word'][$from_name])) {
        $langs['cost_per_word'][$from_name] = array();
      }
      $langs['cost_per_word'][$from_name][$to_name] = (float)$item['cost_per_word'];

      if(!isset($langs['pay_per_use'][$from_name])) {
        $langs['pay_per_use'][$from_name] = array();
      }
      $langs['pay_per_use'][$from_name][$to_name] = (int)$item['pay_per_use'];

      if(!isset($langs['applications'][$from_name])) {
        $langs['applications'][$from_name] = array();
      }
      $langs['applications'][$from_name][$to_name] = (int)$item['applications'];
      
      if(!isset($langs['offer_id'][$from_name])) {
        $langs['offer_id'][$from_name] = array();
      }
      $langs['offer_id'][$from_name][$to_name] = (int)$item['id'];
      
      if(!isset($langs['available_translators'][$from_name])) {
        $langs['available_translators'][$from_name] = array();
      }
      $langs['available_translators'][$from_name][$to_name] = (int)$item['available_translators'];

      if(!isset($langs['contract_id'][$from_name])) {
        $langs['contract_id'][$from_name] = array();
      }
      $langs['contract_id'][$from_name][$to_name] = (int)$item['contract_id'];

      if(!isset($langs['translators'][$from_name])) {
        $langs['translators'][$from_name] = array();
      }
      $langs['translators'][$from_name][$to_name] = array();
      
      foreach ( $item->translators->translator as $translator ) {
        $langs['translators'][$from_name][$to_name][] = array('name' => (string)$translator['nickname'], 'id' => (int)$translator['id']);
      }
      
    }
    
    $attrs = $xml->website->attributes();
    $langs['platform'] = (int) $attrs['platform_kind'];
    $langs['pickup'] = (int) $attrs['pickup_type'];
    $langs['name'] = (string) $attrs['name'];
    $langs['description'] = (string) $attrs['description'];
    $langs['free_usage'] = (int) $attrs['free_usage'];
    $langs['accesskey'] = (string) $attrs['accesskey'];
    $langs['support_ticket_id'] = (string) $attrs['support_ticket_id'];
    $langs['url'] = (string) $attrs['url'];

    $attrs = $xml->website->client->attributes();
    $langs['balance'] = (float) $attrs['balance'];
    $langs['userstatus'] = (int) $attrs['userstatus'];
    $langs['userid'] = (int) $attrs['id'];
    $langs['email'] = (string) $attrs['email'];
    $langs['anon'] = (string)  $attrs['anon'];

    $langs['unfunded_cms_requests'] = NULL;
    $unfunded = @$xml->website->unfunded_cms_requests->attributes()->missing_funds;
    if (isset($unfunded)) {
      $attrs = $xml->website->unfunded_cms_requests->attributes();
      $langs['unfunded_cms_requests'] = (string) $attrs['missing_funds'];
    }
    
    $langs['html_status'] = (string)$xml->website->html_status;
    $langs['translators_management_info'] = (string)$xml->website->translators_management_info;
    
    variable_set ( 'icl_core_user_status', $langs['userstatus']);
    variable_set ( 'icl_core_user_id', $langs['userid']);
    variable_set ( 'icl_core_languages', $langs );
  
  return $langs;
}

/**
 * Creates a translation request and posts it to the ICanLocalize server
 *
 * @param array $data The translation request elements
 * @param unknown_type $origLang
 * @param unknown_type $targetLangs
 * @param unknown_type $is_new
 * @param unknown_type $linkTo
 * @return unknown
 */
function icl_core_request_translation($data, $original_lang, $target_langs, $previous_id, $translator_id, $link_to = '', $title = '') {
  $wid = variable_get ( 'icl_core_website_id', 0 );
  $accesskey = variable_get ( 'icl_core_accesskey', 0 );
  $cms_request_details = _icl_core_build_xml ( $data, $original_lang, $target_langs, $previous_id, $link_to );
  
  $ssl = variable_get ( 'icl_core_mode', ICL_MODE_PRODUCTION ) == ICL_MODE_PRODUCTION ? true : false;
  
  $response = _icl_core_post_xml ( $cms_request_details, $accesskey, $wid, $original_lang, $target_langs, $translator_id, $title, $link_to, $ssl );
  
  if ($response == "") {
    return FALSE;
  }
  $xml = new SimpleXMLElement ( $response );
  $status = $xml->xpath ( '//status' );
  $status = $status [0]->attributes ();
  if ($status ['err_code'] == 0) {
    $elements = $xml->xpath ( '//result' );
    $result = $elements [0]->attributes ();
    
    return (int)$result ['id'];
  } else {
    return FALSE;
  }
}

/**
 * sends comments for instant translation.
 *
 * returns: request_id
 */

function icl_core_send_comment_for_translation($subject, $text, $format, $from_language, $to_language) {
  
  $subject_from_text = trim(truncate_utf8(decode_entities(strip_tags(check_markup($text, $format))), 29, TRUE));
  if ($subject == $subject_from_text) {
    // The subject is derived from the text, we don't need to send it.
    $subject = "";
  } else {
    $text = $subject . "\n{{T:1}}\n" . $text;
  }
  
  $all_languages = _icl_core_get_all_languages();
  
  foreach ($all_languages as $lang) {
    if ($lang['code'] == $from_language) {
      $from_language = $lang['name'];
    }
    if ($lang['code'] == $to_language) {
      $to_language = $lang['name'];
    }
  }
  $post = array(
    'body' => $text,
    'from_language' => $from_language,
    'to_language' => $to_language,
  );
  
  $xml = icl_core_call_service ( '/websites/[wid]/create_message.xml?accesskey=[accesskey]', TRUE, $post);
    
  if (is_string ( $xml )) {
    return 0;
  }
  
  $status = $xml->xpath ( '//status' );
  $status = $status [0]->attributes ();
  if ($status ['err_code'] == 0) {
    $elements = $xml->xpath ( '//result' );
    $result = $elements [0]->attributes ();
    
    return (int) $result ['id'];
  } else {
    return 0;
  }
  
}

/**
 * pickup comments
 *
 * returns: an array of ids and the data.
 */

function icl_core_comment_pickup() {
  
  
  $xml = icl_core_call_service ( '/websites/[wid]/web_messages_for_pickup.xml?accesskey=[accesskey]', FALSE);
    
  if (is_string ( $xml )) {
    return FALSE;
  }
  
  $comments = array();
  $last_message_id = -1;
  
  $status = $xml->xpath ( '//status' );
  $status = $status [0]->attributes ();
  if ($status ['err_code'] == 0) {
    $elements = $xml->xpath ( '//web_messages_for_pickup/web_message' );
    
    foreach($elements as $message) {
      $message_id = (int)$message['id'];
      $comments[$message_id] = base64_decode((string)$message);
      
      $last_message_id = max($last_message_id, $message_id);
    }
    
    if ($last_message_id > 0) {
      $post = array(
        'last_id' => $last_message_id,
      );
      $xml = icl_core_call_service ( '/websites/[wid]/ack_message_pickup.xml?accesskey=[accesskey]', FALSE, $post);
    }

    return $comments;
  } else {
    return FALSE;
  }
  
}

/**
 * Updates the status of a translation on the remote side
 *
 * @param int $rid
 * @param string $language
 * @param int $status
 */
function icl_core_update_remote_status($rid, $status, $language = null) {
  $accesskey = variable_get ( 'icl_core_accesskey', 0 );
  $data = array (
      'accesskey' => $accesskey, 
      'status' => $status );
  if ($language != null) {
    $data ['language'] = $language;
  }
  
  $response = icl_core_call_service ( '/websites/[wid]/cms_requests/' . $rid . '/update_status.xml', TRUE, $data );
  if (module_exists ( 'icl_debug' )) {
    icl_debug_watchdog_debug ( 'icl_core', '%data', array (
        '%data' => htmlentities ( $response->data, ENT_QUOTES ) ) );
  }
}

/**
 * Fetches a given translation from the server
 *
 * @param int $rid
 * @param string $lang
 * @return unknown
 */
function icl_core_fetch_translation($rid, $language = null) {
  $per_lang = $language == null ? '' : '&language=' . urlencode(icl_core_get_language_name($language));
  $xml = icl_core_call_service ( '/websites/[wid]/cms_requests/' . $rid . '/cms_download.xml?accesskey=[accesskey]' . $per_lang, TRUE );
  if (is_string ( $xml )) {
    return $xml;
  }
  
  if ($xml->status ['err_code'] == 0) {
    $data = icl_core_call_service ( '/websites/[wid]/cms_requests/' . $rid . '/cms_download?accesskey=[accesskey]' . $per_lang );
    if (! $data instanceof SimpleXMLElement) {
      return $data;
    }
    
    $langs = icl_core_available_languages ();
    $result = array ();
    foreach ( $data->xpath ( '//content' ) as $content ) {
      if (count ( $content->translations )) {
        foreach ( $content->translations as $translation ) {
          $item = array (
              'type' => ( string ) $content ['type'], 
              'translate' => ( int ) $content ['translate'] );
          
          switch (strtoupper ( ( string ) $content ['format'] )) {
            case 'CSV' :
              $text = ( string ) $translation->translation ['data'];
              $text = str_replace ( '&#0A;', "\n", $text );
              $text = substr($text, 2, strlen($text) - 4);
              $item ['data'] = explode("', '", $text );
              $item ['format'] = 'csv';
              $original_text = ( string ) $content['data'];
              $original_text = str_replace ( '&#0A;', "\n", $original_text );
              $item ['original_data'] = json_decode ( "[" . $original_text . "]");
              break;
            case 'CSV_BASE64' :
              $text = ( string ) $translation->translation ['data'];
              $text = str_replace ( '&#0A;', "\n", $text );
              $text = substr($text, 2, strlen($text) - 4);
              $encoded_data = explode("', '", $text );
              $item ['data'] = array();
              foreach($encoded_data as $encoded_text) {
                $item ['data'][] = base64_decode($encoded_text);
              }
              $item ['format'] = 'csv';
              $original_text = ( string ) $content['data'];
              $original_text = str_replace ( '&#0A;', "\n", $original_text );
              $original_data = json_decode ( "[" . $original_text . "]");
              $item ['original_data'] = array();
              foreach($original_data as $encoded_text) {
                $item['original_data'][] = base64_decode($encoded_text);
              }
              break;
            case 'BASE64' :
              $text = ( string ) $translation->translation ['data'];
              $text = base64_decode($text);
              $text = str_replace ( '&#0A;', "\n", $text );
              $item ['data'] = $text;
              $item ['format'] = 'plain';
              $original_text = ( string ) $content['data'];
              $original_text = base64_decode($original_text);
              $original_text = str_replace ( '&#0A;', "\n", $original_text );
              $item ['original_data'] = $original_text;
              break;
            default :
              $text = ( string ) $translation->translation ['data'];
              $text = str_replace ( '&#0A;', "\n", $text );
              $item ['data'] = $text;
              $item ['format'] = 'plain';
              $original_text = ( string ) $content['data'];
              $original_text = str_replace ( '&#0A;', "\n", $original_text );
              $item ['original_data'] = $original_text;
              break;
          }
          
          foreach ( $langs as $lang ) {
            if ($lang->name == ( string ) $translation ['lang']) {
              $item ['language'] = $lang;
            }
          }
          
          $result [] = $item;
        }
      } else {
        $item = array (
            'type' => ( string ) $content ['type'], 
            'translate' => ( int ) $content ['translate'] );
        
        switch (strtoupper ( ( string ) $content ['format'] )) {
          case 'CSV' :
            $text = strtr ( ( string ) $content ['data'], '\'', '"' );
            $item ['data'] = json_decode ( $text );
            break;
          case 'BASE64' :
            $text = ( string ) $content ['data'];
            $item ['data'] = base64_decode($text);
            break;
          default :
            $item ['data'] = ( string ) $content ['data'];
            break;
        }
        
        $item ['language'] = new StdClass ( );
        
        $result [] = $item;
      }
    }
    
    return $result;
  }
}

/**
 * Fetches translation request statuses
 *
 * @return mixed The request id keyed status array or the error message
 */
function icl_core_fetch_translation_statuses($filter = true) {
  $xml = icl_core_call_service ( '/websites/[wid]/cms_requests.xml?'.($filter ? 'filter=pickup&' : '').'accesskey=[accesskey]', TRUE );
  if (is_string ( $xml )) {
    return $xml;
  }
    
  $requests = array ();
  foreach ( $xml->xpath ( '//pending_cms_requests/cms_request' ) as $cms_request ) {
    $requests[] = (int) $cms_request['id'];
  }
  
  return $requests;
}

/**
 * Fetches translation request status for a specific language
 *
 * @return mixed The request id keyed status array or the error message
 */
function icl_core_fetch_translation_status($rid) {
  $xml = icl_core_call_service ( '/websites/[wid]/cms_requests/' . $rid . '.xml?accesskey=[accesskey]', TRUE );
  if (is_string ( $xml )) {
    return $xml;
  }
  
  $langs = _icl_core_available_targets ();
  $statuses = array ();
  foreach ( $xml->xpath ( '//cms_target_language' ) as $cms_target_language ) {
    foreach ( $langs as $lang ) {
      $id = ( int ) $cms_target_language ['language_id'];
      $status = ( int ) $cms_target_language ['status'];
      if (! empty ( $cms_target_language->cms_downloads->cms_download )) {
        $status = ICL_STATUS_READY;
      }
      else {
        $status = ICL_STATUS_REQUESTED;
      }
      
      $in_db = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT service_rid FROM {icl_core_status} WHERE service_rid=%d AND target='%s'", $rid, $lang->code));
      if ($lang->id == $id && $in_db == $rid) {
        $statuses [$lang->code] = $status;
      }
    }
  }
  
  return $statuses;
}

/**
 * Fetches original language code for a request
 *
 * @return mixed original language code or the error message
 */
function icl_core_fetch_original_language_code($rid) {
  $xml = icl_core_call_service ( '/websites/[wid]/cms_requests/' . $rid . '.xml?accesskey=[accesskey]', TRUE );
  if (is_string ( $xml )) {
    return $xml;
  }
  
  $all_langs = _icl_core_get_all_languages ();
  foreach ( $xml->xpath ( '//cms_request' ) as $cms_request ) {
    $id = ( int ) $cms_request ['language_id'];
    foreach ($all_langs as $lang) {
      if ( ( int ) ($lang['id']) == $id){
        return $lang;
      }
    }
  }
  
  return "original language not found";
}

/**
 * Fetches translators and word count for a cms_request
 *
 */
function icl_core_fetch_translators_and_word_count($rid) {
  $xml = icl_core_call_service ( '/websites/[wid]/cms_requests/' . $rid . '.xml?accesskey=[accesskey]', TRUE );
  if (is_string ( $xml )) {
    return array();
  }
  
  $translators = array();
  foreach ( $xml->xpath ( '//cms_target_languages' ) as $cms_target) {
    foreach ($cms_target->cms_target_language as $target_lang) {
      $lang_name = ( string ) $target_lang ['language'];
      
      $word_count = ( int ) $target_lang ['word_count'];
      
      $translator = (string)$target_lang->translator['nickname'];
      
      $codes = icl_core_get_language_codes($lang_name);
      foreach($codes as $code) {
        // see if we are translating to this language code
        $result = _icl_wrapper_db_query('SELECT target FROM {icl_core_status} WHERE service_rid=%d', $rid);
        while($result_code = db_fetch_object($result)) {
          if ($result_code->target == $code) {
            $translators[$code] = array('translator' => $translator, 'word_count' => $word_count, 'status' => (int) $target_lang ['status']);
          }
        }
      }
    }
  }
  
  return $translators;
}

function icl_core_create_anon_account($data = array()) {
  global $base_url;

  $post = array('anon' => '1',
                'platform_kind' => '2',
                'create_account' => '1',
                'ignore_languages' => '1',
                'pickup_type' => '0',
                'url' => $base_url,
               );
  if (is_array($data)) {
    $post = array_merge($post, $data);
  }
  $xml = icl_core_call_service ( '/websites/create_by_cms.xml', TRUE, $post);

  if (is_string ( $xml ) && $xml == '-1 Cannot access via XML-RPC') {
    // try polling mode
    $post['pickup_type'] = 1;
    $xml = icl_core_call_service ( '/websites/create_by_cms.xml', TRUE, $post);
    
    if (!is_string ( $xml )) {
      variable_set ( 'icl_core_receive_options', ICL_CORE_RECEIVE_POLL);
    }
    
  }
    

  if (is_string ( $xml )) {
    // this returns the error.
    return $xml;
  }
  
  // successful - so save website id and accesskey
  
  $elements = $xml->xpath ( '//website' );
  $result = $elements [0]->attributes ();
  variable_set('icl_core_website_id', (string)$result['id']);
  variable_set('icl_core_accesskey', (string)$result['accesskey']);
  

}

/**
 * icl_core_create_cms_project
 *
 * create a cms project on the icanlocalize server.
 * Will create a user account if one doesn't already exist.
 */
  
function icl_core_create_account($email,
                                 $create_account,
                                 $first_name,
                                 $last_name,
                                 $password,
                                 $interview_translators,
                                 $url,
                                 $project_name,
                                 $project_description,
                                 $pickup,
                                 $languages,
                                 $notifications,
                                 $project_kind,
                                 $affiliate_id,
                                 $affiliate_key) {
  static $all_langs = NULL;
  
  $post = array(
    'email' => $email,
    'create_account' => $create_account,
    'fname' => $first_name,
    'lname' => $last_name,
    'platform_kind' => '2',
    'interview_translators' => $interview_translators ? '1' : '0',
    'url' => $url,
    'title' => $project_name,
    'description' => $project_description,
    'pickup_type' => $pickup ? '1' : '0',
    'notifications' => $notifications,
    'project_kind' => $project_kind,
    'is_verified' => 1,
  );
  
  if (!$create_account) {
    $post['password'] = $password;
  }

  if ($affiliate_id && $affiliate_id != '' && $affiliate_key && $affiliate_key != '') {
    $post['affiliate_id'] = $affiliate_id;
    $post['affiliate_key'] = $affiliate_key;
  }
  
  _icl_core_build_post_languages($languages, $post);
  
  $xml = icl_core_call_service ( '/websites/create_by_cms.xml', TRUE, $post);
  if (is_string ( $xml )) {
    // this returns the error.
    return $xml;
  }
  
  // successful - so save website id and accesskey
  
  $elements = $xml->xpath ( '//website' );
  $result = $elements [0]->attributes ();
  variable_set('icl_core_website_id', (string)$result['id']);
  variable_set('icl_core_accesskey', (string)$result['accesskey']);
  
  
}

function icl_core_add_language($from_name, $to_name, $existing_langs, $website_id, $accesskey) {
  $post = array(
    'accesskey' => $accesskey,
  );

  $count = 1;
  foreach ($existing_langs as $existing_from => $existing_to) {
    foreach ($existing_to as $existing_to_name) {
      $post['from_language' . $count] = $existing_from;
      $post['to_language' . $count] = $existing_to_name;
      $count += 1;
    }
  }
  $post['from_language' . $count] = $from_name;
  $post['to_language' . $count] = $to_name;

  $xml = icl_core_call_service ( '/websites/' . $website_id . '/update_by_cms.xml', TRUE, $post);
  if (is_string ( $xml )) {
    // this returns the error.
    return $xml;
  }
  
  
}

function _icl_core_build_post_languages($languages, &$post) {
  $all_languages = _icl_core_get_all_languages();
  
  $lang_number = 1;
  
  foreach($languages as $code => $targets) {
    $source_lang = icl_core_get_language_name($code);
    $pay_langs = array();
    foreach($targets as $dest_lang) {
      if (strpos($dest_lang, "own_") === 0) {
        $pay_langs[] = substr($dest_lang, 4);
      }
    }
    
    foreach($targets as $dest_lang) {
      if (strpos($dest_lang, "own_") === FALSE) {
        
        $dest_lang_name = icl_core_get_language_name($dest_lang);
        $post['from_language' . $lang_number] = $source_lang;
        $post['to_language' . $lang_number] = $dest_lang_name;
        
        if (in_array($dest_lang, $pay_langs)) {
          $post['pay_per_use' . $lang_number] = 1;
          variable_set('icl_core_'.$code.'_own_'.$dest_lang, TRUE);
        } else {
          variable_set('icl_core_'.$code.'_own_'.$dest_lang, FALSE);
        }
        
        $lang_number += 1;
      }
    }
  }
}

/**
 * update the cms settings on icanlocalize
 */

function icl_core_update_cms($accesskey,
                             $website_id,
                             $interview_translators,
                             $url,
                             $project_name,
                             $project_description,
                             $pickup,
                             $languages,
                             $notifications,
                             $project_kind,
                             $affiliate_id,
                             $affiliate_key) {
  

  static $all_langs = NULL;
  
  $post = array(
    'accesskey' => $accesskey,
    'url' => $url,
    //'title' => $project_name,
    //'description' => $project_description,
    'pickup_type' => $pickup ? '1' : '0',
    'notifications' => $notifications,
    'project_kind' => $project_kind,
  );

  if ($affiliate_id && $affiliate_id != '' && $affiliate_key && $affiliate_key != '') {
    $post['affiliate_id'] = $affiliate_id;
    $post['affiliate_key'] = $affiliate_key;
  }

  if ($languages != FALSE) {
    _icl_core_build_post_languages($languages, $post);
  } else {
    $post['ignore_languages'] = '1';
  }
  
  $xml = icl_core_call_service ( '/websites/' . $website_id . '/update_by_cms.xml', TRUE, $post);
  if (is_string ( $xml )) {
    // this returns the error.
    return $xml;
  }
  
 
  
}

function icl_core_update_url_by_cms($accesskey,
                             $website_id,
                             $url) {
  
  $post = array(
    'accesskey' => $accesskey,
    'url' => $url,
    'ignore_languages' => '1',
  );

  
  $xml = icl_core_call_service ( '/websites/' . $website_id . '/update_by_cms.xml', TRUE, $post);
  if (is_string ( $xml )) {
    // this returns the error.
    return $xml;
  }
}

/**
 * Builds the cms_request_details.xml file content and returns it
 *
 * @param string $link     The link the translatable content comes from.
 * @param array  $data     The data to translate (or not - depending on key translate)
 * @param string $orig_lang The originating language
 * @param array   $langs    The languages to translate to. The array keys MUST begin with 0 and must be incremental integers.
 * @return string        The XML file content to send with the HTTP POST.
 */
function _icl_core_build_xml($data, $orig_lang, $langs, $previous_rid = false, $linkTo = '') {
  
  $tab = "\t";
  $nl = PHP_EOL;
  if($previous_rid){
    $command = 'update_page';
    $previous_rid = 'previous_cms_request_id="'.$previous_rid.'"';
  }else{
    $command = 'new_page';
    $previous_rid = '';
  }
  
  $xml  = "<?xml version=\"1.0\" encoding=\"utf-8\"?>".$nl;
  $xml .= '<cms_request_details type="drupal" command="'.$command.'" from_lang="'.$orig_lang.'" '.$previous_rid.'>'.$nl;

  if ( empty ( $linkTo )) {
    $linkTo = url ( '<front>', array ( 'absolute' => TRUE ) );
  }
  $xml .= $tab.'<link url="'.$linkTo.'" />'.$nl;

  $xml .= $tab.'<contents>'.$nl;

  foreach ( $data as $item ) {

    if (is_array($item['text'])) {
      $item['format'] = 'csv';
    }
    
    
    switch (strtoupper ( $item ['format'] )) {
      case 'CSV' :
        $texts = array();
        foreach ( $item ['text'] as $text ) {
          $texts [] = '"' . base64_encode($text) . '"';
        }
        $item_data = implode ( ',', $texts );
        $item_data = str_replace('"', '&quot;', $item_data);

        $translated_texts = array();
        if (isset($item ['translation'])) {
          foreach ( $item ['translation'] as $text ) {
            $translated_texts [] = '"' . base64_encode($text) . '"';
          }
        }
        $item_data_translated = implode ( ',', $translated_texts );
        $item_data_translated = str_replace('"', '&quot;', $item_data_translated);
        
        $item_format = 'csv_base64';
        break;
    
      default :
        // if a format isn't specified we will base64 encode it
        $item_data = base64_encode($item ['text']);
        if (isset($item ['translation'])) {
          $item_data_translated = base64_encode($item ['translation']);
        } else {
          $item_data_translated = '';
        }
        $item_format = 'base64';
        break;
    }
    
    $filter_line_breaks = 1;
    if (isset($item['filter_line_breaks'])) {
      $filter_line_breaks = $item['filter_line_breaks'];
    }

    $xml .= $tab.$tab.'<content type="'. $item ['type'] .'" translate="'. $item ['translate'] . '" filter_line_breaks="'. $filter_line_breaks . '" data="'. $item_data . '" translation="'. $item_data_translated . '"';
    $xml .= ' format="'.$item_format.'"';
    $xml .=  ' />'.$nl;
    
    
  }
  
  $xml .= $tab.'</contents>'.$nl;
  $xml .= $tab.'<cms_target_languages>'.$nl;
  foreach ( $langs as $lang ) {
    $xml .= $tab.$tab.'<target_language lang="'.utf8_encode($lang).'" />'.$nl;    
  }                
  $xml .= $tab.'</cms_target_languages>'.$nl;
  $xml .= '</cms_request_details>';                

  if (module_exists ( 'icl_debug' )) {
    icl_debug_watchdog_debug ( 'icl_core', '@xml', array ( '@xml' => formatXmlString ( $xml ) ) );
  }
  
  return $xml;
}

/**
 * This function builds up a multipart form request adds the necessary headers and
 * send it to the icantranslate site.
 * Please note that this function contains the hardcoded SANDBOX URL, so it needs to be refactored
 * before production!
 *
 * @param string $xml       The content of cms_request_details.xml or the result of function build_xml(...).
 * @param string $accesskey    The accesskey for icantranslate,
 * @param int    $wid      The website ID from icantranslate.
 * @param string $orig_lang   The originating language.
 * @param array   $to_langs    The numeric keyed array of translation languages where keys begin with 0 and increments by 1.
 * @param string $description  Whatever description to be sent to ICanTranslate
 * @param bool   $ssl       Wether to use encrypted connection (it is required for production mode)
 * @return array         The parsed XML response as an array.
 */
function _icl_core_post_xml($xml, $accesskey, $wid, $orig_lang, $to_langs, $translator_id, $title = '', $link = '', $ssl = false) {
  $url = variable_get ( 'icl_core_mode', ICL_MODE_PRODUCTION ) == ICL_MODE_PRODUCTION ? ICL_PRODUCTION_URL : ICL_SANDBOX_URL;
  
  $url = parse_url ( $url );
  $boundary = '---------------------------' . md5 ( uniqid ( time () ) );
  
  // Builds the multipart data to transfer
  $data = '--' . $boundary . "\r\n";
  $data .= "Content-Disposition: form-data; name=\"accesskey\"\r\n\r\n";
  $data .= $accesskey . "\r\n";
  $data .= '--' . $boundary . "\r\n";
  $data .= "Content-Disposition: form-data; name=\"file1[uploaded_data]\"; filename=\"cms_request_details.xml.gz\"\r\n";
  $data .= "Content-Type: application/x-gzip\r\n\r\n";
  $data .= gzencode ( $xml, 9, FORCE_GZIP ) . "\r\n";
  $data .= '--' . $boundary . "\r\n";
  $data .= "Content-Disposition: form-data; name=\"doc_count\"\r\n\r\n";
  $data .= "1\r\n";
  $data .= '--' . $boundary . "\r\n";
  $data .= "Content-Disposition: form-data; name=\"orig_language\"\r\n\r\n";
  $data .= $orig_lang . "\r\n";
  $data .= '--' . $boundary . "\r\n";
  $data .= "Content-Disposition: form-data; name=\"title\"\r\n\r\n";
  $data .= $title . "\r\n";
  $data .= '--' . $boundary . "\r\n";
  $data .= "Content-Disposition: form-data; name=\"permlink\"\r\n\r\n";
  $data .= $link . "\r\n";
  $data .= '--' . $boundary . "\r\n";
  $data .= "Content-Disposition: form-data; name=\"translator_id\"\r\n\r\n";
  $data .= $translator_id . "\r\n";
  $data .= '--' . $boundary . "\r\n";
  foreach ( $to_langs as $key => $lang ) {
    $data .= sprintf ( "Content-Disposition: form-data; name=\"to_language%d\"\r\n\r\n", (( int ) $key) + 1 );
    $data .= $lang . "\r\n";
    $data .= '--' . $boundary . "\r\n";
  }
  
  $data .= "Content-Disposition: form-data; name=\"key\"\r\n\r\n";
  $data .= md5($xml) . "\r\n";
  $data .= '--' . $boundary . "\r\n";
  
  $data .= "Content-Disposition: form-data; name=\"file1[description]\"\r\n\r\n";
  $data .= "cms_request_details\r\n";
  $data .= '--' . $boundary . "--\r\n";
  
  // Add the required headers to the request and append the multipart encoded data
  $request = "POST /websites/" . $wid . "/cms_requests.xml HTTP/1.1\r\n";
  $request .= "Host: " . $url ['host'] . "\r\n";
  $request .= "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n";
  $request .= "Accept-Encoding: gzip,deflate\r\n";
  $request .= "Content-Type: multipart/form-data; boundary=" . $boundary . "\r\n";
  $request .= sprintf ( "Content-Length: %d\r\n", strlen ( $data ) );
  $request .= "Connection: close\r\n\r\n";
  $request .= $data;
  
  // Do the HTTP call
  $response = '';
  $ssl = $url ['scheme'] == 'https';
  $uri = ($ssl ? 'ssl://' : '') . $url ['host'];
  $port = $ssl ? 443 : 80;
  try {
    $socket = fsockopen ( $uri, $port, $errno, $errstr, 15 );
  } catch (Exception $e) {
    $socket = NULL;
  }
  
  if ($socket) {
    fwrite ( $socket, $request );
    while ( $tmp = fread ( $socket, 64 ) ) {
      $response .= $tmp;
    }
    fclose ( $socket );
  }
  
  $response = explode ( "\r\n", $response );
  do {
    $item = trim ( array_shift ( $response ) );
  } while ( ! empty ( $item ) );
  $response = implode ( "\r\n", $response );
  $responseXml = gzdecode ( $response ); // The server allows only gzipped HTTP connection, we have to decode
  

  return $responseXml;
}


function icl_core_get_reminders($refresh = false) {
    
  // see if we need to refresh the reminders from ICanLocalize
  $last_time = variable_get('last_icl_reminder_fetch', 0);
  $website_id = variable_get ( 'icl_core_website_id', FALSE );
  if ($website_id === FALSE) {
    return array();
  }
  
  // Check if the client is 'anon'
  // 'anon' client wont show reminders.
  $langs = variable_get ( 'icl_core_languages', array() );
  if (isset($langs['anon']) ) {
    if ($langs['anon'] == '1') {
      return array();
    }
    
  }

  
  if (!$refresh && ((time() - $last_time) > 60) && _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT COUNT(*) FROM {icl_reminders} w WHERE w.show=1")) == 0) {
      $refresh = true;
  }
  
  if (((time() - $last_time) > 10 * 60) || $refresh) {
    $session_id = icl_get_current_session();

    $request_url = '/reminders.xml?session=' . $session_id . '&wid=' . $website_id;    

    $res = icl_core_call_service($request_url);
    if($res->status['err_code'] == '3'){
      // not logged in get a new session_id
      $session_id = _icl_get_session_id();

      $request_url = '/reminders.xml?session=' . $session_id . '&wid=' . $website_id;    

      $res = icl_core_call_service($request_url);
    }
        
    if($res->status['err_code'] == '0'){
        
      _icl_wrapper_db_query("TRUNCATE {icl_reminders}");
      
      // First add any low funding warning.
      
      $website_data = variable_get ( 'icl_core_languages', NULL );
      if (isset($website_data['unfunded_cms_requests'])) {
          $missing_funds = $website_data['unfunded_cms_requests'];

          _icl_wrapper_db_query("INSERT INTO {icl_reminders} VALUES(%d, '%s', '%s', %d, 1)",
                      (int)-1,
                      (string)sprintf(t('You don\'t have enough funds in your ICanLocalize account - [b]Funds required - $%s[/b]'), $missing_funds),
                      (string)'/finance',
                      (string)1);
          
      }
      
      
      // Now add the reminders.
      foreach ( $res->xpath ( '//reminders/reminder' ) as $reminder) {
        if (isset($reminder['id'])) {
          _icl_wrapper_db_query("INSERT INTO {icl_reminders} VALUES(%d, '%s', '%s', %d, 1)",
                      (int)$reminder['id'],
                      (string)$reminder['message'],
                      (string)$reminder['url'],
                      (string)$reminder['can_delete'] == 'true' ? 1 : 0);
        }      
      }

      $last_time = time();
      variable_set('last_icl_reminder_fetch', $last_time);
      variable_set('icl_current_session', (string)$session_id);
    }
  }

  // check if low funding is still valid
  if (_icl_wrapper_db_result(_icl_wrapper_db_query("SELECT id FROM {icl_reminders} WHERE id=-1")) == -1) {
  
    $website_data = variable_get ( 'icl_core_languages', NULL );
    if (!isset($website_data['unfunded_cms_requests'])) {
        _icl_wrapper_db_query("DELETE FROM {icl_reminders} WHERE id=-1");
    }
  }

  $reminders = array();
  $query = _icl_wrapper_db_query("SELECT * FROM {icl_reminders} w WHERE w.show=1 ORDER BY id");
  while ( $result = db_fetch_object ( $query ) ) {
    $reminders[] = $result;
  }
    
  return $reminders;
}

function icl_core_fetch_reminders() {

  $output = '';

  if (isset($_POST['refresh']) && $_POST['refresh'] == 1) {
    $reminders = icl_core_get_reminders(true);
  } else {
    $reminders = icl_core_get_reminders();
  }
  
  $count = 0;
  foreach($reminders as $r) {
    $message = $r->message;
    $message = str_replace('[', '<', $message);
    $message = str_replace(']', '>', $message);
    $url = $r->url;
    $anchor_pos = strpos($url, '#');
    if ($anchor_pos !== false) {
      $url = substr($url, 0, $anchor_pos);
    }
    $output .= $message . ' - ' . icl_create_icl_popup_link($url . '&message_id=' . $r->id. '&TB_iframe=true') . t('View') . '</a>';

    if ($r->can_delete == '1') {
      $on_click = 'dismiss_message(' . $r->id . ')';
        
      $output .= ' - <a href="#" onclick="'. $on_click . '">Dismiss</a>';
    }
    $output .= '<br />';
    
    $count += 1;
    if ($count > 5) {
        break;
    }
    
  }
  
  if ($output != '') {
    echo '1|'.$output;
  } else {
    echo '0|';
  }
  
}

function icl_core_delete_reminder() {
  $message_id = $_POST['message_id'];
  
  if ((int)$message_id >= 0) {
    $session_id = icl_get_current_session();

    $request_url = '/reminders/' . $message_id . '.xml';
    
    $data = array('session' => $session_id,
                  '_method' => 'DELETE');

    $res = icl_core_call_service($request_url, FALSE, $data);
    
    if($res->status['err_code']=='3'){
        // not logged in get a new session_id
      $session_id = _icl_get_session_id();

      $res = icl_core_call_service($request_url, FALSE, $data);
    }

    if($res->result=='Reminder deleted' || $res->result == 'Reminder not found'){
        // successfully deleted on the server.
        _icl_wrapper_db_query("DELETE FROM {icl_reminders} WHERE id={$message_id}");
    }

      
  } else {
    // this is the low funding reminder.
    _icl_wrapper_db_query("DELETE FROM {icl_reminders} WHERE id={$message_id}");
  }
      
  
}

function icl_core_update_translation_link($request_id,
                                          $language,
                                          $translation_nid) {
  
  $available_translation_services = module_invoke_all('translation_service');
  foreach ($available_translation_services as $module => $service) {
    module_invoke($module, 'update_translation_link', $request_id, $language, $translation_nid);
  }
  
}

/*
 * If gzdecode is apparently missing
 * then we provide one for this operation
 * 
 */
if (! function_exists ( 'gzdecode' )) {
  /**
   * gzdecode implementation
   *
   * @see http://hu.php.net/manual/en/function.gzencode.php#44470
   * 
   * @param string $data
   * @param string $filename
   * @param string $error
   * @param int $maxlength
   * @return string
   */
  function gzdecode($data, &$filename = '', &$error = '', $maxlength = null) {
    $len = strlen ( $data );
    if ($len < 18 || strcmp ( substr ( $data, 0, 2 ), "\x1f\x8b" )) {
      $error = "Not in GZIP format.";
      return null; // Not GZIP format (See RFC 1952)
    }
    $method = ord ( substr ( $data, 2, 1 ) ); // Compression method
    $flags = ord ( substr ( $data, 3, 1 ) ); // Flags
    if ($flags & 31 != $flags) {
      $error = "Reserved bits not allowed.";
      return null;
    }
    // NOTE: $mtime may be negative (PHP integer limitations)
    $mtime = unpack ( "V", substr ( $data, 4, 4 ) );
    $mtime = $mtime [1];
    $xfl = substr ( $data, 8, 1 );
    $os = substr ( $data, 8, 1 );
    $headerlen = 10;
    $extralen = 0;
    $extra = "";
    if ($flags & 4) {
      // 2-byte length prefixed EXTRA data in header
      if ($len - $headerlen - 2 < 8) {
        return false; // invalid
      }
      $extralen = unpack ( "v", substr ( $data, 8, 2 ) );
      $extralen = $extralen [1];
      if ($len - $headerlen - 2 - $extralen < 8) {
        return false; // invalid
      }
      $extra = substr ( $data, 10, $extralen );
      $headerlen += 2 + $extralen;
    }
    $filenamelen = 0;
    $filename = "";
    if ($flags & 8) {
      // C-style string
      if ($len - $headerlen - 1 < 8) {
        return false; // invalid
      }
      $filenamelen = strpos ( substr ( $data, $headerlen ), chr ( 0 ) );
      if ($filenamelen === false || $len - $headerlen - $filenamelen - 1 < 8) {
        return false; // invalid
      }
      $filename = substr ( $data, $headerlen, $filenamelen );
      $headerlen += $filenamelen + 1;
    }
    $commentlen = 0;
    $comment = "";
    if ($flags & 16) {
      // C-style string COMMENT data in header
      if ($len - $headerlen - 1 < 8) {
        return false; // invalid
      }
      $commentlen = strpos ( substr ( $data, $headerlen ), chr ( 0 ) );
      if ($commentlen === false || $len - $headerlen - $commentlen - 1 < 8) {
        return false; // Invalid header format
      }
      $comment = substr ( $data, $headerlen, $commentlen );
      $headerlen += $commentlen + 1;
    }
    $headercrc = "";
    if ($flags & 2) {
      // 2-bytes (lowest order) of CRC32 on header present
      if ($len - $headerlen - 2 < 8) {
        return false; // invalid
      }
      $calccrc = crc32 ( substr ( $data, 0, $headerlen ) ) & 0xffff;
      $headercrc = unpack ( "v", substr ( $data, $headerlen, 2 ) );
      $headercrc = $headercrc [1];
      if ($headercrc != $calccrc) {
        $error = "Header checksum failed.";
        return false; // Bad header CRC
      }
      $headerlen += 2;
    }
    // GZIP FOOTER
    $datacrc = unpack ( "V", substr ( $data, - 8, 4 ) );
    $datacrc = sprintf ( '%u', $datacrc [1] & 0xFFFFFFFF );
    $isize = unpack ( "V", substr ( $data, - 4 ) );
    $isize = $isize [1];
    // decompression:
    $bodylen = $len - $headerlen - 8;
    if ($bodylen < 1) {
      // IMPLEMENTATION BUG!
      return null;
    }
    $body = substr ( $data, $headerlen, $bodylen );
    $data = "";
    if ($bodylen > 0) {
      switch ($method) {
        case 8 :
          // Currently the only supported compression method:
          $data = gzinflate ( $body, $maxlength );
          break;
        default :
          $error = "Unknown compression method.";
          return false;
      }
    } // zero-byte body content is allowed
    // Verifiy CRC32
    $crc = sprintf ( "%u", crc32 ( $data ) );
    $crcOK = $crc == $datacrc;
    $lenOK = $isize == strlen ( $data );
    if (! $lenOK || ! $crcOK) {
      $error = ($lenOK ? '' : 'Length check FAILED. ') . ($crcOK ? '' : 'Checksum FAILED.');
      return false;
    }
    return $data;
  }
}

function icl_core_update_account($data) {
  $uri = '/websites/[wid]/update_by_cms.xml';
  unset($data['site_id']);
  return icl_core_call_service($uri, TRUE, $data);
}