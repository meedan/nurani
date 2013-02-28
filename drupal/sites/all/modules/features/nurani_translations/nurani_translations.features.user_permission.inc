<?php
/**
 * @file
 * nurani_translations.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function nurani_translations_user_default_permissions() {
  $permissions = array();

  // Exported permission: translate interface.
  $permissions['translate interface'] = array(
    'name' => 'translate interface',
    'roles' => array(
      0 => 'administrator',
      1 => 'translator',
    ),
    'module' => 'locale',
  );

  // Exported permission: use on-page translation.
  $permissions['use on-page translation'] = array(
    'name' => 'use on-page translation',
    'roles' => array(
      0 => 'administrator',
      1 => 'translator',
    ),
    'module' => 'l10n_client',
  );

  return $permissions;
}
