<?php
/**
 * @file
 * cyco_patterns.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function cyco_patterns_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create pattern content'.
  $permissions['create pattern content'] = array(
    'name' => 'create pattern content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any pattern content'.
  $permissions['delete any pattern content'] = array(
    'name' => 'delete any pattern content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own pattern content'.
  $permissions['delete own pattern content'] = array(
    'name' => 'delete own pattern content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete terms in pattern_categories'.
  $permissions['delete terms in pattern_categories'] = array(
    'name' => 'delete terms in pattern_categories',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit any pattern content'.
  $permissions['edit any pattern content'] = array(
    'name' => 'edit any pattern content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own pattern content'.
  $permissions['edit own pattern content'] = array(
    'name' => 'edit own pattern content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit terms in pattern_categories'.
  $permissions['edit terms in pattern_categories'] = array(
    'name' => 'edit terms in pattern_categories',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'search pattern content'.
  $permissions['search pattern content'] = array(
    'name' => 'search pattern content',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
      'author' => 'author',
      'grader' => 'grader',
      'instructor' => 'instructor',
      'reviewer' => 'reviewer',
      'student' => 'student',
    ),
    'module' => 'search_config',
  );

  return $permissions;
}
