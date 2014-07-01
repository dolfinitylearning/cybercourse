<?php
/**
 * @file
 * cyco_pseudents.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function cyco_pseudents_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer pseudents'.
  $permissions['administer pseudents'] = array(
    'name' => 'administer pseudents',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'cyco_pseudents',
  );

  // Exported permission: 'create pseudent_pose content'.
  $permissions['create pseudent_pose content'] = array(
    'name' => 'create pseudent_pose content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any pseudent_pose content'.
  $permissions['delete any pseudent_pose content'] = array(
    'name' => 'delete any pseudent_pose content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own pseudent_pose content'.
  $permissions['delete own pseudent_pose content'] = array(
    'name' => 'delete own pseudent_pose content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete terms in pseudent_categories'.
  $permissions['delete terms in pseudent_categories'] = array(
    'name' => 'delete terms in pseudent_categories',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit any pseudent_pose content'.
  $permissions['edit any pseudent_pose content'] = array(
    'name' => 'edit any pseudent_pose content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own pseudent_pose content'.
  $permissions['edit own pseudent_pose content'] = array(
    'name' => 'edit own pseudent_pose content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit terms in pseudent_categories'.
  $permissions['edit terms in pseudent_categories'] = array(
    'name' => 'edit terms in pseudent_categories',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'search pseudent_pose content'.
  $permissions['search pseudent_pose content'] = array(
    'name' => 'search pseudent_pose content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
      'grader' => 'grader',
      'reviewer' => 'reviewer',
    ),
    'module' => 'search_config',
  );

  return $permissions;
}
