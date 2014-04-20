<?php

/**
 * Implements hook_views_data().
 */
function meedan_discussion_lock_views_data_alter(&$data) {
  if (isset($data['field_data_field_discussion_closing_date'])) {
    $data['field_data_field_discussion_closing_date']['field_discussion_closing_date']['field']['handler'] = 'views_handler_field_date_closing';
  }
}
