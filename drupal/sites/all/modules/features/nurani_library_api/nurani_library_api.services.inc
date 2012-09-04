<?php
/**
 * @file
 * nurani_library_api.services.inc
 */

/**
 * Implements hook_default_services_endpoint().
 */
function nurani_library_api_default_services_endpoint() {
  $export = array();

  $endpoint = new stdClass();
  $endpoint->disabled = FALSE; /* Edit this to true to make a default endpoint disabled initially */
  $endpoint->api_version = 3;
  $endpoint->name = 'api';
  $endpoint->server = 'rest_server';
  $endpoint->path = 'api';
  $endpoint->authentication = array(
    'services' => 'services',
  );
  $endpoint->server_settings = array(
    'rest_server' => array(
      'formatters' => array(
        'json' => TRUE,
        'jsonp' => TRUE,
        'bencode' => FALSE,
        'php' => FALSE,
        'rss' => FALSE,
        'xml' => FALSE,
        'yaml' => FALSE,
      ),
      'parsers' => array(
        'application/json' => TRUE,
        'application/x-www-form-urlencoded' => TRUE,
        'application/vnd.php.serialized' => FALSE,
        'application/x-yaml' => FALSE,
        'multipart/form-data' => FALSE,
      ),
    ),
  );
  $endpoint->resources = array(
    'passage' => array(
      'actions' => array(
        'validate' => array(
          'enabled' => 1,
        ),
      ),
      'operations' => array(
        'retrieve' => array(
          'enabled' => 1,
        ),
        'index' => array(
          'enabled' => 1,
        ),
      ),
    ),
    'work' => array(
      'operations' => array(
        'retrieve' => array(
          'enabled' => 1,
        ),
        'index' => array(
          'enabled' => 1,
        ),
      ),
    ),
    'system' => array(
      'actions' => array(
        'connect' => array(
          'enabled' => 1,
        ),
      ),
    ),
  );
  $endpoint->debug = 1;
  $export['api'] = $endpoint;

  return $export;
}
