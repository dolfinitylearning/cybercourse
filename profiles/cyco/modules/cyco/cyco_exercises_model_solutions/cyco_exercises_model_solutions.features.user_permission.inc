<?php
/**
 * @file
 * cyco_exercises_model_solutions.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function cyco_exercises_model_solutions_user_default_permissions() {
  $permissions = array();

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

  // Exported permission: 'create model_exercise_solution content'.
  $permissions['create model_exercise_solution content'] = array(
    'name' => 'create model_exercise_solution content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any model_exercise_solution content'.
  $permissions['delete any model_exercise_solution content'] = array(
    'name' => 'delete any model_exercise_solution content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own model_exercise_solution content'.
  $permissions['delete own model_exercise_solution content'] = array(
    'name' => 'delete own model_exercise_solution content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any model_exercise_solution content'.
  $permissions['edit any model_exercise_solution content'] = array(
    'name' => 'edit any model_exercise_solution content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
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

  // Exported permission: 'edit own model_exercise_solution content'.
  $permissions['edit own model_exercise_solution content'] = array(
    'name' => 'edit own model_exercise_solution content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'search model_exercise_solution content'.
  $permissions['search model_exercise_solution content'] = array(
    'name' => 'search model_exercise_solution content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
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
