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
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'create field_badge_machine_name'.
  $permissions['create field_badge_machine_name'] = array(
    'name' => 'create field_badge_machine_name',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'delete any badge content'.
  $permissions['delete any badge content'] = array(
    'name' => 'delete any badge content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own badge content'.
  $permissions['delete own badge content'] = array(
    'name' => 'delete own badge content',
    'roles' => array(),
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
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit field_badge_machine_name'.
  $permissions['edit field_badge_machine_name'] = array(
    'name' => 'edit field_badge_machine_name',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own badge content'.
  $permissions['edit own badge content'] = array(
    'name' => 'edit own badge content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit own field_badge_machine_name'.
  $permissions['edit own field_badge_machine_name'] = array(
    'name' => 'edit own field_badge_machine_name',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'search badge content'.
  $permissions['search badge content'] = array(
    'name' => 'search badge content',
    'roles' => array(),
    'module' => 'search_config',
  );

  // Exported permission: 'view field_badge_machine_name'.
  $permissions['view field_badge_machine_name'] = array(
    'name' => 'view field_badge_machine_name',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_badge_machine_name'.
  $permissions['view own field_badge_machine_name'] = array(
    'name' => 'view own field_badge_machine_name',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'field_permissions',
  );

  return $permissions;
}
