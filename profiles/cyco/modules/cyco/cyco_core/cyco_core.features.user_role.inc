<?php
/**
 * @file
 * cyco_core.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function cyco_core_user_default_roles() {
  $roles = array();

  // Exported role: administrator.
  $roles['administrator'] = array(
    'name' => 'administrator',
    'weight' => 6,
  );

  // Exported role: author.
  $roles['author'] = array(
    'name' => 'author',
    'weight' => 5,
  );

  // Exported role: grader.
  $roles['grader'] = array(
    'name' => 'grader',
    'weight' => 3,
  );

  // Exported role: reviewer.
  $roles['reviewer'] = array(
    'name' => 'reviewer',
    'weight' => 4,
  );

  // Exported role: student.
  $roles['student'] = array(
    'name' => 'student',
    'weight' => 2,
  );

  return $roles;
}
