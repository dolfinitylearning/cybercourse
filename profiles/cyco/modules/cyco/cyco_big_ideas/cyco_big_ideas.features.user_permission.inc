<?php
/**
 * @file
 * cyco_big_ideas.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function cyco_big_ideas_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create big_idea content'.
  $permissions['create big_idea content'] = array(
    'name' => 'create big_idea content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any big_idea content'.
  $permissions['delete any big_idea content'] = array(
    'name' => 'delete any big_idea content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own big_idea content'.
  $permissions['delete own big_idea content'] = array(
    'name' => 'delete own big_idea content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any big_idea content'.
  $permissions['edit any big_idea content'] = array(
    'name' => 'edit any big_idea content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own big_idea content'.
  $permissions['edit own big_idea content'] = array(
    'name' => 'edit own big_idea content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'search big_idea content'.
  $permissions['search big_idea content'] = array(
    'name' => 'search big_idea content',
    'roles' => array(),
    'module' => 'search_config',
  );

  return $permissions;
}
