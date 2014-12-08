<?php
/**
 * @file
 * cyco_exercises_submissions.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function cyco_exercises_submissions_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create exercise_submission content'.
  $permissions['create exercise_submission content'] = array(
    'name' => 'create exercise_submission content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
      'instructor' => 'instructor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create field_exercise_solved'.
  $permissions['create field_exercise_solved'] = array(
    'name' => 'create field_exercise_solved',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
      'instructor' => 'instructor',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'delete any exercise_submission content'.
  $permissions['delete any exercise_submission content'] = array(
    'name' => 'delete any exercise_submission content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
      'instructor' => 'instructor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own exercise_submission content'.
  $permissions['delete own exercise_submission content'] = array(
    'name' => 'delete own exercise_submission content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
      'instructor' => 'instructor',
      'student' => 'student',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any exercise_submission content'.
  $permissions['edit any exercise_submission content'] = array(
    'name' => 'edit any exercise_submission content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
      'instructor' => 'instructor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit field_exercise_solved'.
  $permissions['edit field_exercise_solved'] = array(
    'name' => 'edit field_exercise_solved',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own exercise_submission content'.
  $permissions['edit own exercise_submission content'] = array(
    'name' => 'edit own exercise_submission content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
      'instructor' => 'instructor',
      'student' => 'student',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own field_exercise_solved'.
  $permissions['edit own field_exercise_solved'] = array(
    'name' => 'edit own field_exercise_solved',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
      'instructor' => 'instructor',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'search exercise_submission content'.
  $permissions['search exercise_submission content'] = array(
    'name' => 'search exercise_submission content',
    'roles' => array(
      'administrator' => 'administrator',
      'grader' => 'grader',
      'instructor' => 'instructor',
    ),
    'module' => 'search_config',
  );

  // Exported permission: 'view field_exercise_solved'.
  $permissions['view field_exercise_solved'] = array(
    'name' => 'view field_exercise_solved',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
      'grader' => 'grader',
      'instructor' => 'instructor',
      'reviewer' => 'reviewer',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_exercise_solved'.
  $permissions['view own field_exercise_solved'] = array(
    'name' => 'view own field_exercise_solved',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'field_permissions',
  );

  return $permissions;
}
