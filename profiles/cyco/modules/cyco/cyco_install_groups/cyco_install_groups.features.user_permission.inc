<?php
/**
 * @file
 * cyco_install_groups.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function cyco_install_groups_user_default_permissions() {
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

  // Exported permission: 'execute _cyco_core_approve_student_membership_action'.
  $permissions['execute _cyco_core_approve_student_membership_action'] = array(
    'name' => 'execute _cyco_core_approve_student_membership_action',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
      'instructor' => 'instructor',
    ),
    'module' => 'actions_permissions',
  );

  // Exported permission: 'execute _cyco_core_deny_student_membership_action'.
  $permissions['execute _cyco_core_deny_student_membership_action'] = array(
    'name' => 'execute _cyco_core_deny_student_membership_action',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
      'instructor' => 'instructor',
    ),
    'module' => 'actions_permissions',
  );

  // Exported permission: 'execute og_membership_delete_action'.
  $permissions['execute og_membership_delete_action'] = array(
    'name' => 'execute og_membership_delete_action',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
      'instructor' => 'instructor',
    ),
    'module' => 'actions_permissions',
  );

  // Exported permission: 'execute og_set_state_action'.
  $permissions['execute og_set_state_action'] = array(
    'name' => 'execute og_set_state_action',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
      'instructor' => 'instructor',
    ),
    'module' => 'actions_permissions',
  );

  // Exported permission: 'execute og_user_roles_action'.
  $permissions['execute og_user_roles_action'] = array(
    'name' => 'execute og_user_roles_action',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
      'instructor' => 'instructor',
    ),
    'module' => 'actions_permissions',
  );

  // Exported permission: 'execute system_message_action'.
  $permissions['execute system_message_action'] = array(
    'name' => 'execute system_message_action',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
      'instructor' => 'instructor',
    ),
    'module' => 'actions_permissions',
  );

  // Exported permission: 'execute system_send_email_action'.
  $permissions['execute system_send_email_action'] = array(
    'name' => 'execute system_send_email_action',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
      'instructor' => 'instructor',
    ),
    'module' => 'actions_permissions',
  );

  // Exported permission: 'search class content'.
  $permissions['search class content'] = array(
    'name' => 'search class content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
      'grader' => 'grader',
      'instructor' => 'instructor',
      'reviewer' => 'reviewer',
      'student' => 'student',
    ),
    'module' => 'search_config',
  );

  // Exported permission: 'search class_post content'.
  $permissions['search class_post content'] = array(
    'name' => 'search class_post content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
      'grader' => 'grader',
      'instructor' => 'instructor',
      'reviewer' => 'reviewer',
      'student' => 'student',
    ),
    'module' => 'search_config',
  );

  return $permissions;
}
