<?php
/**
 * @file
 * cyco_install_groups.features.og_features_role.inc
 */

/**
 * Implements hook_og_features_default_roles().
 */
function cyco_install_groups_og_features_default_roles() {
  $roles = array();

  // Exported OG Role: 'node:class:grader'.
  $roles['node:class:grader'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'class',
    'name' => 'grader',
  );

  // Exported OG Role: 'node:class:instructor'.
  $roles['node:class:instructor'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'class',
    'name' => 'instructor',
  );

  // Exported OG Role: 'node:class:student'.
  $roles['node:class:student'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'class',
    'name' => 'student',
  );

  return $roles;
}
