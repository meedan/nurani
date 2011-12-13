<?php

/**
 * Implements hook_rules_event_info().
 */
function yallah_notifications_rules_event_info() {
  $events = array();
  $events['agreement_event'] = array(
    'label' => t('User signed agreement'),
    'module' => 'Agreement',
    'arguments' => array(
      'user' => array('type' => 'user', 'label' => t('User who signed the agreement')), 
    ),
    'help' => 'Triggered when a user agrees to the terms of service.',
  );
  return $events;
}

