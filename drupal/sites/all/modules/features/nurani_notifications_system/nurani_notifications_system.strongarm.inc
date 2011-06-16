<?php

/**
 * Implementation of hook_strongarm().
 */
function nurani_notifications_system_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_content_per_type';
  $strongarm->value = '0';

  $export['notifications_content_per_type'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_content_type';
  $strongarm->value = array(
    'thread' => 'thread',
    'nodetype' => 'nodetype',
    'author' => 'author',
    'taxonomy' => 0,
    'typeauthor' => 0,
  );

  $export['notifications_content_type'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_default_auto';
  $strongarm->value = 1;

  $export['notifications_default_auto'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_default_send_interval';
  $strongarm->value = '0';

  $export['notifications_default_send_interval'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_event_enabled';
  $strongarm->value = array(
    'lite-default' => 1,
    'node-insert' => 1,
    'node-annotation-insert' => 0,
    'node-discussion-insert' => 0,
    'node-page-insert' => 0,
    'node-profile-insert' => 0,
    'node-response-insert' => 0,
    'node-term-insert' => 0,
    'node-text-insert' => 0,
    'node-comment-insert' => 0,
    'node-update' => 0,
    'node-annotation-update' => 0,
    'node-discussion-update' => 0,
    'node-page-update' => 0,
    'node-profile-update' => 0,
    'node-response-update' => 0,
    'node-term-update' => 0,
    'node-text-update' => 0,
    'node-comment-update' => 0,
    'node-comment' => 1,
    'node-annotation-comment' => 0,
    'node-discussion-comment' => 0,
    'node-page-comment' => 0,
    'node-profile-comment' => 0,
    'node-response-comment' => 0,
    'node-term-comment' => 0,
    'node-text-comment' => 0,
    'node-comment-comment' => 0,
  );

  $export['notifications_event_enabled'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_event_template';
  $strongarm->value = array(
    'lite-default' => 'notifications-event-lite',
    'node-insert' => 'notifications-event-node-insert',
    'node-annotation-insert' => 'notifications-content-annotation-insert',
    'node-discussion-insert' => 'notifications-content-discussion-insert',
    'node-page-insert' => 'notifications-content-page-insert',
    'node-profile-insert' => 'notifications-content-profile-insert',
    'node-response-insert' => 'notifications-content-response-insert',
    'node-term-insert' => 'notifications-content-term-insert',
    'node-text-insert' => 'notifications-content-text-insert',
    'node-comment-insert' => 'notifications-content-comment-insert',
    'node-update' => 'notifications-event-node-update',
    'node-annotation-update' => 'notifications-content-annotation-update',
    'node-discussion-update' => 'notifications-content-discussion-update',
    'node-page-update' => 'notifications-content-page-update',
    'node-profile-update' => 'notifications-content-profile-update',
    'node-response-update' => 'notifications-content-response-update',
    'node-term-update' => 'notifications-content-term-update',
    'node-text-update' => 'notifications-content-text-update',
    'node-comment-update' => 'notifications-content-comment-update',
    'node-comment' => 'notifications-event-node-comment',
    'node-annotation-comment' => 'notifications-content-annotation-comment',
    'node-discussion-comment' => 'notifications-content-discussion-comment',
    'node-page-comment' => 'notifications-content-page-comment',
    'node-profile-comment' => 'notifications-content-profile-comment',
    'node-response-comment' => 'notifications-content-response-comment',
    'node-term-comment' => 'notifications-content-term-comment',
    'node-text-comment' => 'notifications-content-text-comment',
    'node-comment-comment' => 'notifications-content-comment-comment',
  );

  $export['notifications_event_template'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_send_immediate';
  $strongarm->value = 1;

  $export['notifications_send_immediate'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_sender';
  $strongarm->value = '0';

  $export['notifications_sender'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_sendself';
  $strongarm->value = 1;

  $export['notifications_sendself'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_subscription_types';
  $strongarm->value = array(
    'taxonomy' => 'taxonomy',
    'thread' => 'thread',
    'nodetype' => 'nodetype',
    'author' => 'author',
    'typeauthor' => 'typeauthor',
  );

  $export['notifications_subscription_types'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_tags_showsubscribed';
  $strongarm->value = 0;

  $export['notifications_tags_showsubscribed'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_tags_vocabularies';
  $strongarm->value = array(
    1 => 0,
  );

  $export['notifications_tags_vocabularies'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_ui_subscribe_links';
  $strongarm->value = '0';

  $export['notifications_ui_subscribe_links'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_ui_unsubscribe_links';
  $strongarm->value = '0';

  $export['notifications_ui_unsubscribe_links'] = $strongarm;
  return $export;
}
