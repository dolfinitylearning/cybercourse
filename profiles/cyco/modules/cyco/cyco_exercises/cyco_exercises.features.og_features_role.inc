<?php
/**
 * @file
 * cyco_exercises.features.og_features_role.inc
 */

/**
 * Implements hook_og_features_default_roles().
 */
function cyco_exercises_og_features_default_roles() {
  $roles = array();

  // Exported OG Role: 'node:class:instructor'.
  $roles['node:class:instructor'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'class',
    'name' => 'instructor',
  );

  return $roles;
}
