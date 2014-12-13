<?php
/**
 * @file
 * cyco_badges.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function cyco_badges_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access achievements'.
  $permissions['access achievements'] = array(
    'name' => 'access achievements',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
      'grader' => 'grader',
      'instructor' => 'instructor',
      'reviewer' => 'reviewer',
      'student' => 'student',
    ),
    'module' => 'achievements',
  );

  // Exported permission: 'administer achievements'.
  $permissions['administer achievements'] = array(
    'name' => 'administer achievements',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'achievements',
  );

  // Exported permission: 'create badge content'.
  $permissions['create badge content'] = array(
    'name' => 'create badge content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any badge content'.
  $permissions['delete any badge content'] = array(
    'name' => 'delete any badge content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own badge content'.
  $permissions['delete own badge content'] = array(
    'name' => 'delete own badge content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'earn achievements'.
  $permissions['earn achievements'] = array(
    'name' => 'earn achievements',
    'roles' => array(
      'student' => 'student',
    ),
    'module' => 'achievements',
  );

  // Exported permission: 'edit any badge content'.
  $permissions['edit any badge content'] = array(
    'name' => 'edit any badge content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own badge content'.
  $permissions['edit own badge content'] = array(
    'name' => 'edit own badge content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'search badge content'.
  $permissions['search badge content'] = array(
    'name' => 'search badge content',
    'roles' => array(),
    'module' => 'search_config',
  );

  return $permissions;
}
