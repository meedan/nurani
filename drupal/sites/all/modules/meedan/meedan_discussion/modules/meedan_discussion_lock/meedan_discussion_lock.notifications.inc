<?php

/**
 * Implements hook_meedan_notifications_recipients_alter().
 *
 * Invitees list for discussions and discussion comments.
 */
function meedan_discussion_lock_meedan_notifications_recipients_alter(&$uids, $object, $context) {
  if ($context['event'] == 'comment') {
    $discussion_node = node_load($object->nid);
  }
  else if ($context['event'] == 'discussion') {
    $discussion_node = $object;
  }

  if ($discussion_node->type != 'discussion') {
    return;
  }

  // Important to clear the user IDs set by meedan_notifications and/or
  // meedan_discussion. It is possible that a commenter has been removed
  // from the invitees list. Only the invitees list should be taken into
  // account for notifications.
  $uids = array();
  $uids[(int) $discussion_node->uid] = (int) $discussion_node->uid;

  foreach ($discussion_node->field_invitees[$discussion_node->language] as $delta => $item) {
    $uid = (int) $item['uid'];
    $uids[$uid] = $uid;
  }
}
