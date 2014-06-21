<?php
/**
 * @file
 * cyco_groups.features.og_features_role.inc
 */

/**
 * Implements hook_og_features_default_roles().
 */
function cyco_groups_og_features_default_roles() {
  $roles = array();

  // Exported OG Role: 'node:class:grader'.
  $roles['node:class:grader'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'class',
    'name' => 'grader',
  );

  return $roles;
}
