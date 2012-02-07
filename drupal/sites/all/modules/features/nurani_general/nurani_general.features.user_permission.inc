<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function nurani_general_user_default_permissions() {
  $permissions = array();

  // Exported permission: access comments
  $permissions['access comments'] = array(
    'name' => 'access comments',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'anonymous user',
      '2' => 'authenticated user',
    ),
  );

  // Exported permission: access content
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'anonymous user',
      '2' => 'authenticated user',
    ),
  );

  // Exported permission: access user profiles
  $permissions['access user profiles'] = array(
    'name' => 'access user profiles',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: administer icanlocalize
  $permissions['administer icanlocalize'] = array(
    'name' => 'administer icanlocalize',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: administer permissions
  $permissions['administer permissions'] = array(
    'name' => 'administer permissions',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'moderator',
    ),
  );

  // Exported permission: administer users
  $permissions['administer users'] = array(
    'name' => 'administer users',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'moderator',
    ),
  );

  // Exported permission: can do translation jobs
  $permissions['can do translation jobs'] = array(
    'name' => 'can do translation jobs',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'translator',
    ),
  );

  // Exported permission: can manage translation jobs
  $permissions['can manage translation jobs'] = array(
    'name' => 'can manage translation jobs',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'moderator',
      '2' => 'translator',
    ),
  );

  // Exported permission: can view translation jobs
  $permissions['can view translation jobs'] = array(
    'name' => 'can view translation jobs',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'translator',
    ),
  );

  // Exported permission: create annotation content
  $permissions['create annotation content'] = array(
    'name' => 'create annotation content',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: create discussion content
  $permissions['create discussion content'] = array(
    'name' => 'create discussion content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'moderator',
    ),
  );

  // Exported permission: create page content
  $permissions['create page content'] = array(
    'name' => 'create page content',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: create profile content
  $permissions['create profile content'] = array(
    'name' => 'create profile content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: create response content
  $permissions['create response content'] = array(
    'name' => 'create response content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: create term content
  $permissions['create term content'] = array(
    'name' => 'create term content',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: create text content
  $permissions['create text content'] = array(
    'name' => 'create text content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'moderator',
    ),
  );

  // Exported permission: edit own annotation content
  $permissions['edit own annotation content'] = array(
    'name' => 'edit own annotation content',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: edit own discussion content
  $permissions['edit own discussion content'] = array(
    'name' => 'edit own discussion content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'moderator',
    ),
  );

  // Exported permission: edit own page content
  $permissions['edit own page content'] = array(
    'name' => 'edit own page content',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: edit own profile content
  $permissions['edit own profile content'] = array(
    'name' => 'edit own profile content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: edit own response content
  $permissions['edit own response content'] = array(
    'name' => 'edit own response content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: edit own term content
  $permissions['edit own term content'] = array(
    'name' => 'edit own term content',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: edit own text content
  $permissions['edit own text content'] = array(
    'name' => 'edit own text content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: moderate comments in own language
  $permissions['moderate comments in own language'] = array(
    'name' => 'moderate comments in own language',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: opt out from ICL notifications
  $permissions['opt out from ICL notifications'] = array(
    'name' => 'opt out from ICL notifications',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: post comments
  $permissions['post comments'] = array(
    'name' => 'post comments',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: post comments without approval
  $permissions['post comments without approval'] = array(
    'name' => 'post comments without approval',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: search content
  $permissions['search content'] = array(
    'name' => 'search content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: submit content for translation
  $permissions['submit content for translation'] = array(
    'name' => 'submit content for translation',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: translate content
  $permissions['translate content'] = array(
    'name' => 'translate content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'translator',
    ),
  );

  // Exported permission: view imagecache thumbnail
  $permissions['view imagecache thumbnail'] = array(
    'name' => 'view imagecache thumbnail',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view imagecache thumbnail_view
  $permissions['view imagecache thumbnail_view'] = array(
    'name' => 'view imagecache thumbnail_view',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'authenticated user',
    ),
  );

  return $permissions;
}
