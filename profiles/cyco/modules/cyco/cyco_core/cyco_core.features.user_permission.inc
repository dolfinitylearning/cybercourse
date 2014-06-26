<?php
/**
 * @file
 * cyco_core.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function cyco_core_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access comments'.
  $permissions['access comments'] = array(
    'name' => 'access comments',
    'roles' => array(
      'author' => 'author',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'access content'.
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'add content to books'.
  $permissions['add content to books'] = array(
    'name' => 'add content to books',
    'roles' => array(
      'author' => 'author',
    ),
    'module' => 'book',
  );

  // Exported permission: 'administer book outlines'.
  $permissions['administer book outlines'] = array(
    'name' => 'administer book outlines',
    'roles' => array(
      'author' => 'author',
    ),
    'module' => 'book',
  );

  // Exported permission: 'administer comments'.
  $permissions['administer comments'] = array(
    'name' => 'administer comments',
    'roles' => array(
      'author' => 'author',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'administer nodes'.
  $permissions['administer nodes'] = array(
    'name' => 'administer nodes',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'administer permissions'.
  $permissions['administer permissions'] = array(
    'name' => 'administer permissions',
    'roles' => array(),
    'module' => 'user',
  );

  // Exported permission: 'administer taxonomy'.
  $permissions['administer taxonomy'] = array(
    'name' => 'administer taxonomy',
    'roles' => array(
      'author' => 'author',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'administer users'.
  $permissions['administer users'] = array(
    'name' => 'administer users',
    'roles' => array(
      'author' => 'author',
    ),
    'module' => 'user',
  );

  // Exported permission: 'clone node'.
  $permissions['clone node'] = array(
    'name' => 'clone node',
    'roles' => array(
      'author' => 'author',
    ),
    'module' => 'clone',
  );

  // Exported permission: 'clone own nodes'.
  $permissions['clone own nodes'] = array(
    'name' => 'clone own nodes',
    'roles' => array(
      'author' => 'author',
    ),
    'module' => 'clone',
  );

  // Exported permission: 'create blueprint_page content'.
  $permissions['create blueprint_page content'] = array(
    'name' => 'create blueprint_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create course_page content'.
  $permissions['create course_page content'] = array(
    'name' => 'create course_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create new books'.
  $permissions['create new books'] = array(
    'name' => 'create new books',
    'roles' => array(
      'author' => 'author',
    ),
    'module' => 'book',
  );

  // Exported permission: 'create page content'.
  $permissions['create page content'] = array(
    'name' => 'create page content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any blueprint_page content'.
  $permissions['delete any blueprint_page content'] = array(
    'name' => 'delete any blueprint_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any course_page content'.
  $permissions['delete any course_page content'] = array(
    'name' => 'delete any course_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any page content'.
  $permissions['delete any page content'] = array(
    'name' => 'delete any page content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own blueprint_page content'.
  $permissions['delete own blueprint_page content'] = array(
    'name' => 'delete own blueprint_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own course_page content'.
  $permissions['delete own course_page content'] = array(
    'name' => 'delete own course_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own page content'.
  $permissions['delete own page content'] = array(
    'name' => 'delete own page content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete terms in blueprint_keywords'.
  $permissions['delete terms in blueprint_keywords'] = array(
    'name' => 'delete terms in blueprint_keywords',
    'roles' => array(
      'author' => 'author',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in keywords'.
  $permissions['delete terms in keywords'] = array(
    'name' => 'delete terms in keywords',
    'roles' => array(
      'author' => 'author',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in workflow_tags'.
  $permissions['delete terms in workflow_tags'] = array(
    'name' => 'delete terms in workflow_tags',
    'roles' => array(
      'author' => 'author',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit any blueprint_page content'.
  $permissions['edit any blueprint_page content'] = array(
    'name' => 'edit any blueprint_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any course_page content'.
  $permissions['edit any course_page content'] = array(
    'name' => 'edit any course_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any page content'.
  $permissions['edit any page content'] = array(
    'name' => 'edit any page content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own blueprint_page content'.
  $permissions['edit own blueprint_page content'] = array(
    'name' => 'edit own blueprint_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own comments'.
  $permissions['edit own comments'] = array(
    'name' => 'edit own comments',
    'roles' => array(
      'author' => 'author',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'edit own course_page content'.
  $permissions['edit own course_page content'] = array(
    'name' => 'edit own course_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own page content'.
  $permissions['edit own page content'] = array(
    'name' => 'edit own page content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit terms in blueprint_keywords'.
  $permissions['edit terms in blueprint_keywords'] = array(
    'name' => 'edit terms in blueprint_keywords',
    'roles' => array(
      'author' => 'author',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in keywords'.
  $permissions['edit terms in keywords'] = array(
    'name' => 'edit terms in keywords',
    'roles' => array(
      'author' => 'author',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in workflow_tags'.
  $permissions['edit terms in workflow_tags'] = array(
    'name' => 'edit terms in workflow_tags',
    'roles' => array(
      'author' => 'author',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'post comments'.
  $permissions['post comments'] = array(
    'name' => 'post comments',
    'roles' => array(
      'author' => 'author',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'revert revisions'.
  $permissions['revert revisions'] = array(
    'name' => 'revert revisions',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'skip comment approval'.
  $permissions['skip comment approval'] = array(
    'name' => 'skip comment approval',
    'roles' => array(
      'author' => 'author',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'use text format rest'.
  $permissions['use text format rest'] = array(
    'name' => 'use text format rest',
    'roles' => array(
      'author' => 'author',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'view own unpublished content'.
  $permissions['view own unpublished content'] = array(
    'name' => 'view own unpublished content',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'view revisions'.
  $permissions['view revisions'] = array(
    'name' => 'view revisions',
    'roles' => array(
      'administrator' => 'administrator',
      'author' => 'author',
    ),
    'module' => 'node',
  );

  return $permissions;
}
