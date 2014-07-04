<?php
/**
 * @file
 * cyco_exercises.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function cyco_exercises_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer group'.
  $permissions['administer group'] = array(
    'name' => 'administer group',
    'roles' => array(),
    'module' => 'og',
  );

  // Exported permission: 'create class content'.
  $permissions['create class content'] = array(
    'name' => 'create class content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
      'instructor' => 'instructor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create class_post content'.
  $permissions['create class_post content'] = array(
    'name' => 'create class_post content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
      'instructor' => 'instructor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create exercise content'.
  $permissions['create exercise content'] = array(
    'name' => 'create exercise content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create exercise_submission content'.
  $permissions['create exercise_submission content'] = array(
    'name' => 'create exercise_submission content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'student' => 'student',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create exercise_submission_rubric_item_ content'.
  $permissions['create exercise_submission_rubric_item_ content'] = array(
    'name' => 'create exercise_submission_rubric_item_ content',
    'roles' => array(
      'administrator' => 'administrator',
      'grader' => 'grader',
      'instructor' => 'instructor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create field_hidden_attachments'.
  $permissions['create field_hidden_attachments'] = array(
    'name' => 'create field_hidden_attachments',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_rubric_items'.
  $permissions['create field_rubric_items'] = array(
    'name' => 'create field_rubric_items',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create model_exercise_solution content'.
  $permissions['create model_exercise_solution content'] = array(
    'name' => 'create model_exercise_solution content',
    'roles' => array(
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create rubric_item content'.
  $permissions['create rubric_item content'] = array(
    'name' => 'create rubric_item content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any class content'.
  $permissions['delete any class content'] = array(
    'name' => 'delete any class content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any class_post content'.
  $permissions['delete any class_post content'] = array(
    'name' => 'delete any class_post content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any exercise content'.
  $permissions['delete any exercise content'] = array(
    'name' => 'delete any exercise content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any exercise_submission content'.
  $permissions['delete any exercise_submission content'] = array(
    'name' => 'delete any exercise_submission content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any exercise_submission_rubric_item_ content'.
  $permissions['delete any exercise_submission_rubric_item_ content'] = array(
    'name' => 'delete any exercise_submission_rubric_item_ content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
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

  // Exported permission: 'delete any rubric_item content'.
  $permissions['delete any rubric_item content'] = array(
    'name' => 'delete any rubric_item content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own class content'.
  $permissions['delete own class content'] = array(
    'name' => 'delete own class content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
      'instructor' => 'instructor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own class_post content'.
  $permissions['delete own class_post content'] = array(
    'name' => 'delete own class_post content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
      'instructor' => 'instructor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own exercise content'.
  $permissions['delete own exercise content'] = array(
    'name' => 'delete own exercise content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own exercise_submission content'.
  $permissions['delete own exercise_submission content'] = array(
    'name' => 'delete own exercise_submission content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'student' => 'student',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own exercise_submission_rubric_item_ content'.
  $permissions['delete own exercise_submission_rubric_item_ content'] = array(
    'name' => 'delete own exercise_submission_rubric_item_ content',
    'roles' => array(
      'administrator' => 'administrator',
      'grader' => 'grader',
      'instructor' => 'instructor',
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

  // Exported permission: 'delete own rubric_item content'.
  $permissions['delete own rubric_item content'] = array(
    'name' => 'delete own rubric_item content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete terms in rubric_item_categories'.
  $permissions['delete terms in rubric_item_categories'] = array(
    'name' => 'delete terms in rubric_item_categories',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit any class content'.
  $permissions['edit any class content'] = array(
    'name' => 'edit any class content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any class_post content'.
  $permissions['edit any class_post content'] = array(
    'name' => 'edit any class_post content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any exercise content'.
  $permissions['edit any exercise content'] = array(
    'name' => 'edit any exercise content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any exercise_submission content'.
  $permissions['edit any exercise_submission content'] = array(
    'name' => 'edit any exercise_submission content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any exercise_submission_rubric_item_ content'.
  $permissions['edit any exercise_submission_rubric_item_ content'] = array(
    'name' => 'edit any exercise_submission_rubric_item_ content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
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

  // Exported permission: 'edit any rubric_item content'.
  $permissions['edit any rubric_item content'] = array(
    'name' => 'edit any rubric_item content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit field_hidden_attachments'.
  $permissions['edit field_hidden_attachments'] = array(
    'name' => 'edit field_hidden_attachments',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_rubric_items'.
  $permissions['edit field_rubric_items'] = array(
    'name' => 'edit field_rubric_items',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own class content'.
  $permissions['edit own class content'] = array(
    'name' => 'edit own class content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
      'instructor' => 'instructor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own class_post content'.
  $permissions['edit own class_post content'] = array(
    'name' => 'edit own class_post content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
      'instructor' => 'instructor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own exercise content'.
  $permissions['edit own exercise content'] = array(
    'name' => 'edit own exercise content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own exercise_submission content'.
  $permissions['edit own exercise_submission content'] = array(
    'name' => 'edit own exercise_submission content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'student' => 'student',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own exercise_submission_rubric_item_ content'.
  $permissions['edit own exercise_submission_rubric_item_ content'] = array(
    'name' => 'edit own exercise_submission_rubric_item_ content',
    'roles' => array(
      'administrator' => 'administrator',
      'grader' => 'grader',
      'instructor' => 'instructor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own field_hidden_attachments'.
  $permissions['edit own field_hidden_attachments'] = array(
    'name' => 'edit own field_hidden_attachments',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_rubric_items'.
  $permissions['edit own field_rubric_items'] = array(
    'name' => 'edit own field_rubric_items',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
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

  // Exported permission: 'edit own rubric_item content'.
  $permissions['edit own rubric_item content'] = array(
    'name' => 'edit own rubric_item content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit terms in rubric_item_categories'.
  $permissions['edit terms in rubric_item_categories'] = array(
    'name' => 'edit terms in rubric_item_categories',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'search class content'.
  $permissions['search class content'] = array(
    'name' => 'search class content',
    'roles' => array(),
    'module' => 'search_config',
  );

  // Exported permission: 'search class_post content'.
  $permissions['search class_post content'] = array(
    'name' => 'search class_post content',
    'roles' => array(),
    'module' => 'search_config',
  );

  // Exported permission: 'search exercise content'.
  $permissions['search exercise content'] = array(
    'name' => 'search exercise content',
    'roles' => array(),
    'module' => 'search_config',
  );

  // Exported permission: 'search exercise_submission content'.
  $permissions['search exercise_submission content'] = array(
    'name' => 'search exercise_submission content',
    'roles' => array(),
    'module' => 'search_config',
  );

  // Exported permission: 'search exercise_submission_rubric_item_ content'.
  $permissions['search exercise_submission_rubric_item_ content'] = array(
    'name' => 'search exercise_submission_rubric_item_ content',
    'roles' => array(),
    'module' => 'search_config',
  );

  // Exported permission: 'search model_exercise_solution content'.
  $permissions['search model_exercise_solution content'] = array(
    'name' => 'search model_exercise_solution content',
    'roles' => array(),
    'module' => 'search_config',
  );

  // Exported permission: 'search rubric_item content'.
  $permissions['search rubric_item content'] = array(
    'name' => 'search rubric_item content',
    'roles' => array(),
    'module' => 'search_config',
  );

  // Exported permission: 'view field_hidden_attachments'.
  $permissions['view field_hidden_attachments'] = array(
    'name' => 'view field_hidden_attachments',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
      'grader' => 'grader',
      'instructor' => 'instructor',
      'reviewer' => 'reviewer',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_rubric_items'.
  $permissions['view field_rubric_items'] = array(
    'name' => 'view field_rubric_items',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
      'grader' => 'grader',
      'instructor' => 'instructor',
      'reviewer' => 'reviewer',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_hidden_attachments'.
  $permissions['view own field_hidden_attachments'] = array(
    'name' => 'view own field_hidden_attachments',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
      'grader' => 'grader',
      'instructor' => 'instructor',
      'reviewer' => 'reviewer',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_rubric_items'.
  $permissions['view own field_rubric_items'] = array(
    'name' => 'view own field_rubric_items',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
      'grader' => 'grader',
      'instructor' => 'instructor',
      'reviewer' => 'reviewer',
    ),
    'module' => 'field_permissions',
  );

  return $permissions;
}
