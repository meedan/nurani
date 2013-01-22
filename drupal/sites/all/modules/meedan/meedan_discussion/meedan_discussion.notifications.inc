<?php

/**
 * Implements hook_meedan_notifications_events().
 */
function meedan_discussion_meedan_notifications_events() {
  return array(
    'discussion' => array(
      'label' => t('New discussion'),
      'token type' => 'node',
    )
  );
}

/**
 * Implements hook_meedan_notifications_recipients().
 *
 * Recipients list for discussions.
 */
function meedan_discussion_meedan_notifications_recipients($object, $context) {
  if ($context['event'] != 'discussion' || $object->type != 'discussion') {
    return;
  }

  // All commenters on this discussion
  $uids = db_select('comment', 'c')
            ->fields('c', array('uid'))
            ->condition('c.nid', $object->nid)
            ->execute()
            ->fetchCol();

  // Discussion author
  $uids[] = $object->uid;

  return $uids;
}

/**
 * Implements hook_meedan_notifications_recipients_alter().
 *
 * Recipients list for discussion comments.
 */
function meedan_discussion_meedan_notifications_recipients_alter(&$uids, $object, $context) {
  if ($context['event'] != 'comment') {
    return;
  }

  $discussion_node = node_load($object->nid);

  // Important to clear the user IDs set by meedan_notifications. It is
  // possible that a commenter has been removed from the invitees list. Only
  // the invitees list should be taken into account for notifications.
  $uids = array();

  $uids = meedan_discussion_meedan_notifications_recipients($discussion_node, array('event' => 'discussion'));
  $uids = drupal_map_assoc(array_map('intval', $uids));
}
