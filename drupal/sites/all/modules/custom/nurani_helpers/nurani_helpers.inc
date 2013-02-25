<?php

/**
 * Retrieves a list of recent annotations
 */
function nurani_helpers_recent_annotations($account, $page = 0, $pagesize = 20) {
  $authorUUID = $account->uuid;

  // Do not filter by author's UUID if the current account is allowed to see
  // all annotations
  if (user_access('view all nurani library annotations', $account)) {
    $authorUUID = 'all';
  }
  // For some reason this user has no UUID. Search by using an invalid UUID to
  // ensure they see only public annotations.
  else if (!$authorUUID) {
    $authorUUID = '-1';
  }

  $nl = nurani_library();
  return $nl->getAnnotations(NULL, $authorUUID, 'annotation', $page, $pagesize);
}
