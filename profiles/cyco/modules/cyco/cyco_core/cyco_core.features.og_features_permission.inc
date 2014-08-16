<?php
/**
 * @file
 * cyco_core.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function cyco_core_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:class:add user'
  $permissions['node:class:add user'] = array(
    'roles' => array(
      'instructor' => 'instructor',
    ),
  );

  // Exported og permission: 'node:class:administer group'
  $permissions['node:class:administer group'] = array(
    'roles' => array(
      'instructor' => 'instructor',
    ),
  );

  // Exported og permission: 'node:class:approve and deny subscription'
  $permissions['node:class:approve and deny subscription'] = array(
    'roles' => array(
      'instructor' => 'instructor',
    ),
  );

  // Exported og permission: 'node:class:create class_post content'
  $permissions['node:class:create class_post content'] = array(
    'roles' => array(
      'instructor' => 'instructor',
    ),
  );

  // Exported og permission: 'node:class:delete any class_post content'
  $permissions['node:class:delete any class_post content'] = array(
    'roles' => array(
      'instructor' => 'instructor',
    ),
  );

  // Exported og permission: 'node:class:delete own class_post content'
  $permissions['node:class:delete own class_post content'] = array(
    'roles' => array(
      'instructor' => 'instructor',
    ),
  );

  // Exported og permission: 'node:class:manage members'
  $permissions['node:class:manage members'] = array(
    'roles' => array(
      'instructor' => 'instructor',
    ),
  );

  // Exported og permission: 'node:class:manage permissions'
  $permissions['node:class:manage permissions'] = array(
    'roles' => array(
      'instructor' => 'instructor',
    ),
  );

  // Exported og permission: 'node:class:manage roles'
  $permissions['node:class:manage roles'] = array(
    'roles' => array(
      'instructor' => 'instructor',
    ),
  );

  // Exported og permission: 'node:class:subscribe'
  $permissions['node:class:subscribe'] = array(
    'roles' => array(
      'non-member' => 'non-member',
    ),
  );

  // Exported og permission: 'node:class:subscribe without approval'
  $permissions['node:class:subscribe without approval'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:class:unsubscribe'
  $permissions['node:class:unsubscribe'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:class:update any class_post content'
  $permissions['node:class:update any class_post content'] = array(
    'roles' => array(
      'instructor' => 'instructor',
    ),
  );

  // Exported og permission: 'node:class:update group'
  $permissions['node:class:update group'] = array(
    'roles' => array(
      'instructor' => 'instructor',
    ),
  );

  // Exported og permission: 'node:class:update own class_post content'
  $permissions['node:class:update own class_post content'] = array(
    'roles' => array(
      'instructor' => 'instructor',
    ),
  );

  return $permissions;
}
