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

  // Exported permission: 'administer exercises settings'.
  $permissions['administer exercises settings'] = array(
    'name' => 'administer exercises settings',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'cyco_exercises',
  );

  // Exported permission: 'administer services'.
  $permissions['administer services'] = array(
    'name' => 'administer services',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'services',
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

  // Exported permission: 'create field_hidden_attachments'.
  $permissions['create field_hidden_attachments'] = array(
    'name' => 'create field_hidden_attachments',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_internal_name'.
  $permissions['create field_internal_name'] = array(
    'name' => 'create field_internal_name',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_notes'.
  $permissions['create field_notes'] = array(
    'name' => 'create field_notes',
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

  // Exported permission: 'create rubric_item content'.
  $permissions['create rubric_item content'] = array(
    'name' => 'create rubric_item content',
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

  // Exported permission: 'delete any rubric_item content'.
  $permissions['delete any rubric_item content'] = array(
    'name' => 'delete any rubric_item content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
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
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'taxonomy',
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

  // Exported permission: 'edit field_internal_name'.
  $permissions['edit field_internal_name'] = array(
    'name' => 'edit field_internal_name',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_notes'.
  $permissions['edit field_notes'] = array(
    'name' => 'edit field_notes',
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

  // Exported permission: 'edit own exercise content'.
  $permissions['edit own exercise content'] = array(
    'name' => 'edit own exercise content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
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

  // Exported permission: 'edit own field_internal_name'.
  $permissions['edit own field_internal_name'] = array(
    'name' => 'edit own field_internal_name',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_notes'.
  $permissions['edit own field_notes'] = array(
    'name' => 'edit own field_notes',
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
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'get a system variable'.
  $permissions['get a system variable'] = array(
    'name' => 'get a system variable',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'services',
  );

  // Exported permission: 'get any binary files'.
  $permissions['get any binary files'] = array(
    'name' => 'get any binary files',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'services',
  );

  // Exported permission: 'get own binary files'.
  $permissions['get own binary files'] = array(
    'name' => 'get own binary files',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'services',
  );

  // Exported permission: 'perform unlimited index queries'.
  $permissions['perform unlimited index queries'] = array(
    'name' => 'perform unlimited index queries',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'services',
  );

  // Exported permission: 'retrieve definition'.
  $permissions['retrieve definition'] = array(
    'name' => 'retrieve definition',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'services_definition',
  );

  // Exported permission: 'save file information'.
  $permissions['save file information'] = array(
    'name' => 'save file information',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'services',
  );

  // Exported permission: 'search exercise content'.
  $permissions['search exercise content'] = array(
    'name' => 'search exercise content',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'search_config',
  );

  // Exported permission: 'search rubric_item content'.
  $permissions['search rubric_item content'] = array(
    'name' => 'search rubric_item content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
      'grader' => 'grader',
      'instructor' => 'instructor',
      'reviewer' => 'reviewer',
    ),
    'module' => 'search_config',
  );

  // Exported permission: 'set a system variable'.
  $permissions['set a system variable'] = array(
    'name' => 'set a system variable',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'services',
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

  // Exported permission: 'view field_internal_name'.
  $permissions['view field_internal_name'] = array(
    'name' => 'view field_internal_name',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_notes'.
  $permissions['view field_notes'] = array(
    'name' => 'view field_notes',
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
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_internal_name'.
  $permissions['view own field_internal_name'] = array(
    'name' => 'view own field_internal_name',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_notes'.
  $permissions['view own field_notes'] = array(
    'name' => 'view own field_notes',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
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
