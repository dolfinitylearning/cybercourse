<?php
/**
 * @file
 * cyco_fill_in_the_blank.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function cyco_fill_in_the_blank_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create fill_in_the_blank content'.
  $permissions['create fill_in_the_blank content'] = array(
    'name' => 'create fill_in_the_blank content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any fill_in_the_blank content'.
  $permissions['delete any fill_in_the_blank content'] = array(
    'name' => 'delete any fill_in_the_blank content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own fill_in_the_blank content'.
  $permissions['delete own fill_in_the_blank content'] = array(
    'name' => 'delete own fill_in_the_blank content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any fill_in_the_blank content'.
  $permissions['edit any fill_in_the_blank content'] = array(
    'name' => 'edit any fill_in_the_blank content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own fill_in_the_blank content'.
  $permissions['edit own fill_in_the_blank content'] = array(
    'name' => 'edit own fill_in_the_blank content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'search fill_in_the_blank content'.
  $permissions['search fill_in_the_blank content'] = array(
    'name' => 'search fill_in_the_blank content',
    'roles' => array(),
    'module' => 'search_config',
  );

  return $permissions;
}
