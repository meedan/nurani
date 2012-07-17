<?php
/**
 * @file
 * nurani_core.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function nurani_core_user_default_permissions() {
  $permissions = array();

  // Exported permission: access administration pages.
  $permissions['access administration pages'] = array(
    'name' => 'access administration pages',
    'roles' => array(
      0 => 'administrator',
      1 => 'moderator',
    ),
    'module' => 'system',
  );

  // Exported permission: access overlay.
  $permissions['access overlay'] = array(
    'name' => 'access overlay',
    'roles' => array(
      0 => 'administrator',
      1 => 'moderator',
    ),
    'module' => 'overlay',
  );

  // Exported permission: administer users.
  $permissions['administer users'] = array(
    'name' => 'administer users',
    'roles' => array(
      0 => 'administrator',
      1 => 'moderator',
    ),
    'module' => 'user',
  );

  // Exported permission: create bundle content.
  $permissions['create bundle content'] = array(
    'name' => 'create bundle content',
    'roles' => array(
      0 => 'moderator',
    ),
    'module' => 'node',
  );

  // Exported permission: create discussion content.
  $permissions['create discussion content'] = array(
    'name' => 'create discussion content',
    'roles' => array(
      0 => 'moderator',
    ),
    'module' => 'node',
  );

  // Exported permission: create passage content.
  $permissions['create passage content'] = array(
    'name' => 'create passage content',
    'roles' => array(
      0 => 'moderator',
    ),
    'module' => 'node',
  );

  // Exported permission: create url aliases.
  $permissions['create url aliases'] = array(
    'name' => 'create url aliases',
    'roles' => array(
      0 => 'administrator',
      1 => 'moderator',
    ),
    'module' => 'path',
  );

  // Exported permission: delete any bundle content.
  $permissions['delete any bundle content'] = array(
    'name' => 'delete any bundle content',
    'roles' => array(
      0 => 'moderator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any discussion content.
  $permissions['delete any discussion content'] = array(
    'name' => 'delete any discussion content',
    'roles' => array(
      0 => 'moderator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any passage content.
  $permissions['delete any passage content'] = array(
    'name' => 'delete any passage content',
    'roles' => array(
      0 => 'moderator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own bundle content.
  $permissions['delete own bundle content'] = array(
    'name' => 'delete own bundle content',
    'roles' => array(
      0 => 'moderator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own discussion content.
  $permissions['delete own discussion content'] = array(
    'name' => 'delete own discussion content',
    'roles' => array(
      0 => 'moderator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own passage content.
  $permissions['delete own passage content'] = array(
    'name' => 'delete own passage content',
    'roles' => array(
      0 => 'moderator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete terms in 1.
  $permissions['delete terms in 1'] = array(
    'name' => 'delete terms in 1',
    'roles' => array(
      0 => 'administrator',
      1 => 'moderator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: delete terms in 2.
  $permissions['delete terms in 2'] = array(
    'name' => 'delete terms in 2',
    'roles' => array(
      0 => 'moderator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: edit any bundle content.
  $permissions['edit any bundle content'] = array(
    'name' => 'edit any bundle content',
    'roles' => array(
      0 => 'moderator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any discussion content.
  $permissions['edit any discussion content'] = array(
    'name' => 'edit any discussion content',
    'roles' => array(
      0 => 'moderator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any passage content.
  $permissions['edit any passage content'] = array(
    'name' => 'edit any passage content',
    'roles' => array(
      0 => 'moderator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own bundle content.
  $permissions['edit own bundle content'] = array(
    'name' => 'edit own bundle content',
    'roles' => array(
      0 => 'moderator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own discussion content.
  $permissions['edit own discussion content'] = array(
    'name' => 'edit own discussion content',
    'roles' => array(
      0 => 'moderator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own passage content.
  $permissions['edit own passage content'] = array(
    'name' => 'edit own passage content',
    'roles' => array(
      0 => 'moderator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit terms in 1.
  $permissions['edit terms in 1'] = array(
    'name' => 'edit terms in 1',
    'roles' => array(
      0 => 'administrator',
      1 => 'moderator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: edit terms in 2.
  $permissions['edit terms in 2'] = array(
    'name' => 'edit terms in 2',
    'roles' => array(
      0 => 'moderator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: view the administration theme.
  $permissions['view the administration theme'] = array(
    'name' => 'view the administration theme',
    'roles' => array(
      0 => 'administrator',
      1 => 'moderator',
    ),
    'module' => 'system',
  );

  return $permissions;
}
