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
