<?php
/**
 * @file
 * nurani_library_api.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function nurani_library_api_user_default_permissions() {
  $permissions = array();

  // Exported permission: access nurani library.
  $permissions['access nurani library'] = array(
    'name' => 'access nurani library',
    'roles' => array(
      0 => 'API',
      1 => 'administrator',
      2 => 'anonymous user',
      3 => 'authenticated user',
    ),
    'module' => 'nurani_library_provider',
  );

  // Exported permission: validate passages.
  $permissions['validate passages'] = array(
    'name' => 'validate passages',
    'roles' => array(
      0 => 'API',
      1 => 'administrator',
    ),
    'module' => 'nurani_library_provider',
  );

  return $permissions;
}
