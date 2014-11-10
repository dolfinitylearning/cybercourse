<?php
/**
 * @file
 * cyco_install_course_blueprint_types.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function cyco_install_course_blueprint_types_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create blueprint_page content'.
  $permissions['create blueprint_page content'] = array(
    'name' => 'create blueprint_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create course_page content'.
  $permissions['create course_page content'] = array(
    'name' => 'create course_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any blueprint_page content'.
  $permissions['delete any blueprint_page content'] = array(
    'name' => 'delete any blueprint_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any course_page content'.
  $permissions['delete any course_page content'] = array(
    'name' => 'delete any course_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own blueprint_page content'.
  $permissions['delete own blueprint_page content'] = array(
    'name' => 'delete own blueprint_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own course_page content'.
  $permissions['delete own course_page content'] = array(
    'name' => 'delete own course_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete terms in blueprint_keywords'.
  $permissions['delete terms in blueprint_keywords'] = array(
    'name' => 'delete terms in blueprint_keywords',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit any blueprint_page content'.
  $permissions['edit any blueprint_page content'] = array(
    'name' => 'edit any blueprint_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any course_page content'.
  $permissions['edit any course_page content'] = array(
    'name' => 'edit any course_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own blueprint_page content'.
  $permissions['edit own blueprint_page content'] = array(
    'name' => 'edit own blueprint_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own course_page content'.
  $permissions['edit own course_page content'] = array(
    'name' => 'edit own course_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit terms in blueprint_keywords'.
  $permissions['edit terms in blueprint_keywords'] = array(
    'name' => 'edit terms in blueprint_keywords',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'search blueprint_page content'.
  $permissions['search blueprint_page content'] = array(
    'name' => 'search blueprint_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
      'grader' => 'grader',
      'instructor' => 'instructor',
      'reviewer' => 'reviewer',
    ),
    'module' => 'search_config',
  );

  // Exported permission: 'search course_page content'.
  $permissions['search course_page content'] = array(
    'name' => 'search course_page content',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'search_config',
  );

  return $permissions;
}
