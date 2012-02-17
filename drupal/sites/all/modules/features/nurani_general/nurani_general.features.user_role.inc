<?php

/**
 * Implementation of hook_user_default_roles().
 */
function nurani_general_user_default_roles() {
  $roles = array();

  // Exported role: administrator
  $roles['administrator'] = array(
    'name' => 'administrator',
  );

  // Exported role: anonymous user
  $roles['anonymous user'] = array(
    'name' => 'anonymous user',
  );

  // Exported role: authenticated user
  $roles['authenticated user'] = array(
    'name' => 'authenticated user',
  );

  // Exported role: moderator
  $roles['moderator'] = array(
    'name' => 'moderator',
  );

  // Exported role: scholar
  $roles['scholar'] = array(
    'name' => 'scholar',
  );

  // Exported role: translator
  $roles['translator'] = array(
    'name' => 'translator',
  );

  return $roles;
}
