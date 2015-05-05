<?php
/**
 * @file
 * cyco_last_page.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function cyco_last_page_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create field_last_course_page_seen'.
  $permissions['create field_last_course_page_seen'] = array(
    'name' => 'create field_last_course_page_seen',
    'roles' => array(
      'anonymous user' => 'anonymous user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_last_course_page_seen'.
  $permissions['edit field_last_course_page_seen'] = array(
    'name' => 'edit field_last_course_page_seen',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_last_course_page_seen'.
  $permissions['edit own field_last_course_page_seen'] = array(
    'name' => 'edit own field_last_course_page_seen',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_last_course_page_seen'.
  $permissions['view field_last_course_page_seen'] = array(
    'name' => 'view field_last_course_page_seen',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_last_course_page_seen'.
  $permissions['view own field_last_course_page_seen'] = array(
    'name' => 'view own field_last_course_page_seen',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  return $permissions;
}
