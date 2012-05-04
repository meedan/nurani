<?php

/**
 * Implementation of hook_views_data_alter()
 */
function views_filters_selective_views_data_alter(&$data) {
  foreach ($data as $table_name => $table_info) {
    foreach ($table_info as $field_name => $field_info) {
      if (!empty($field_info['filter']['handler']) && $field_info['filter']['handler'] != 'views_handler_filter_selective') {
        $selective = $field_info;
        $selective['title'] = $field_info['title'] . ' (selective)';
        $selective['filter']['handler'] = 'views_handler_filter_selective';
        $selective['filter']['proxy'] = $field_info['filter']['handler'];
        $selective['filter']['field'] = $field_name;
        unset($selective['argument'], $selective['field'], $selective['relationship'], $selective['sort']);
        $data[$table_name][$field_name . '_selective'] = $selective;
      }
    }
  }
}

/**
 * Implementation of hook_views_handlers()
 */
function views_filters_selective_views_handlers() {
  return array(
    'handlers' => array(
      'views_handler_filter_selective' => array(
        'parent' => 'views_handler_filter_in_operator',
      ),
    ),
  );
}

/**
 * Implementation of hook_views_plugins()
 */
function views_filters_selective_views_plugins() {
  return array(
    'exposed_form' => array(
      'views_filters_selective' => array(
        'title' => t('Selective Exposed Filters'),
        'help' => t('Restrict exposed filter values to those present in the result set.'),
        'handler' => 'views_filters_selective_exposed_form_plugin',
        'uses row plugin' => FALSE,
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
        'parent' => 'basic',
      ),
    ),
  );
}

/**
 * Implementation of hook_views_query_alter()
 */
function views_filters_selective_views_query_alter(&$view, &$query) {
  if (!empty($view->selective)) {
    if (!isset($view->query->fields[$view->base_field])) {
      $query->add_field($view->base_table, $view->base_field);
    }
  }
}

