<?php
/**
 * @file
 * nurani_api.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function nurani_api_user_default_permissions() {
  $permissions = array();

  // Exported permission: access nurani library.
  $permissions['access nurani library'] = array(
    'name' => 'access nurani library',
    'roles' => array(
      0 => 'administrator',
      1 => 'moderator',
    ),
    'module' => 'nurani_library',
  );

  // Exported permission: create nurani library annotations.
  $permissions['create nurani library annotations'] = array(
    'name' => 'create nurani library annotations',
    'roles' => array(
      0 => 'authenticated user',
    ),
    'module' => 'nurani_library',
  );

  // Exported permission: delete nurani library annotations.
  $permissions['delete nurani library annotations'] = array(
    'name' => 'delete nurani library annotations',
    'roles' => array(
      0 => 'authenticated user',
    ),
    'module' => 'nurani_library',
  );

  // Exported permission: edit all nurani library annotations.
  $permissions['edit all nurani library annotations'] = array(
    'name' => 'edit all nurani library annotations',
    'roles' => array(
      0 => 'administrator',
      1 => 'moderator',
    ),
    'module' => 'nurani_library',
  );

  // Exported permission: update nurani library annotations.
  $permissions['update nurani library annotations'] = array(
    'name' => 'update nurani library annotations',
    'roles' => array(
      0 => 'authenticated user',
    ),
    'module' => 'nurani_library',
  );

  // Exported permission: view all nurani library annotations.
  $permissions['view all nurani library annotations'] = array(
    'name' => 'view all nurani library annotations',
    'roles' => array(
      0 => 'administrator',
      1 => 'moderator',
    ),
    'module' => 'nurani_library',
  );

  return $permissions;
}
