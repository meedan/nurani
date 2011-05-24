<?php
if (function_exists('curl_init') && function_exists('json_decode')) {
  require_once 'OHTAPI.php';
  
  define('OHT_API_STATUS_OK', 0);
  define('OHT_API_STATUS_UNKNOWN', 100);
  define('OHT_API_STATUS_UNAUTHORIZED', 101);
  define('OHT_API_STATUS_FORBIDDEN', 102);
  define('OHT_API_STATUS_VALIDATION_FAILED', 103);
  define('OHT_API_STATUS_INSUFFICIENT_CREDITS', 200);
  define('OHT_API_STATUS_INVALID_LANGUAGE_PAIR', 201);
  define('OHT_API_STATUS_INVALID_PROJECT_ID', 202);
  define('OHT_API_STATUS_TRANSLATION_NOT_SUBMITTED', 203);
  define('OHT_API_STATUS_INTERNAL_ERROR', 900);
  
  OHTAPI::config(array(
    'account_id' => _one_hour_translations_get_account_id(),
    'secret_key' => _one_hour_translations_get_secret_key(),
  ));
  $api = OHTAPI::instance();
  $api->setSandbox(FALSE);
}
