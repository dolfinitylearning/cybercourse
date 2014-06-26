<?php
/**
 * @file
 * cyco_core.features.roles_permissions.inc
 */

/**
 * Implements hook_default_roles_permissions().
 */
function cyco_core_default_roles_permissions() {
  $roles = array();

  // Exported role: administrator
  $roles['administrator'] = array(
    'name' => 'administrator',
    'weight' => 6,
    'permissions' => array(
      'access content' => TRUE,
      'access content overview' => TRUE,
      'administer content types' => TRUE,
      'administer nodes' => TRUE,
      'administer uuid' => TRUE,
      'bypass node access' => TRUE,
      'create blueprint_page content' => TRUE,
      'create course_page content' => TRUE,
      'create page content' => TRUE,
      'create pattern content' => TRUE,
      'create pseudent_pose content' => TRUE,
      'delete any blueprint_page content' => TRUE,
      'delete any course_page content' => TRUE,
      'delete any page content' => TRUE,
      'delete any pattern content' => TRUE,
      'delete any pseudent_pose content' => TRUE,
      'delete own blueprint_page content' => TRUE,
      'delete own course_page content' => TRUE,
      'delete own page content' => TRUE,
      'delete own pattern content' => TRUE,
      'delete own pseudent_pose content' => TRUE,
      'delete revisions' => TRUE,
      'edit any blueprint_page content' => TRUE,
      'edit any course_page content' => TRUE,
      'edit any page content' => TRUE,
      'edit any pattern content' => TRUE,
      'edit any pseudent_pose content' => TRUE,
      'edit own blueprint_page content' => TRUE,
      'edit own course_page content' => TRUE,
      'edit own page content' => TRUE,
      'edit own pattern content' => TRUE,
      'edit own pseudent_pose content' => TRUE,
      'revert revisions' => TRUE,
      'view own unpublished content' => TRUE,
      'view revisions' => TRUE,
    ),
  );

  // Exported role: author
  $roles['author'] = array(
    'name' => 'author',
    'weight' => 5,
    'permissions' => array(
      'access administration menu' => TRUE,
      'access administration pages' => TRUE,
      'access backup and migrate' => TRUE,
      'access backup files' => TRUE,
      'access comments' => TRUE,
      'access content' => TRUE,
      'access content overview' => TRUE,
      'access contextual links' => TRUE,
      'access site in maintenance mode' => TRUE,
      'access site-wide contact form' => TRUE,
      'access user contact forms' => TRUE,
      'add content to books' => TRUE,
      'admin node search exlusions' => TRUE,
      'administer book outlines' => TRUE,
      'administer comments' => TRUE,
      'administer group' => TRUE,
      'administer nodes' => TRUE,
      'administer pseudents' => TRUE,
      'administer scroll to top' => TRUE,
      'administer search' => TRUE,
      'administer taxonomy' => TRUE,
      'administer url aliases' => TRUE,
      'administer users' => TRUE,
      'clone node' => TRUE,
      'clone own nodes' => TRUE,
      'create blueprint_page content' => TRUE,
      'create course_page content' => TRUE,
      'create new books' => TRUE,
      'create page content' => TRUE,
      'create pattern content' => TRUE,
      'create pseudent_pose content' => TRUE,
      'create url aliases' => TRUE,
      'delete any blueprint_page content' => TRUE,
      'delete any course_page content' => TRUE,
      'delete any page content' => TRUE,
      'delete any pattern content' => TRUE,
      'delete any pseudent_pose content' => TRUE,
      'delete backup files' => TRUE,
      'delete own blueprint_page content' => TRUE,
      'delete own course_page content' => TRUE,
      'delete own page content' => TRUE,
      'delete own pattern content' => TRUE,
      'delete own pseudent_pose content' => TRUE,
      'delete revisions' => TRUE,
      'delete terms in 1' => TRUE,
      'delete terms in 2' => TRUE,
      'delete terms in 3' => TRUE,
      'delete terms in 4' => TRUE,
      'edit any blueprint_page content' => TRUE,
      'edit any course_page content' => TRUE,
      'edit any page content' => TRUE,
      'edit any pattern content' => TRUE,
      'edit any pseudent_pose content' => TRUE,
      'edit own blueprint_page content' => TRUE,
      'edit own comments' => TRUE,
      'edit own course_page content' => TRUE,
      'edit own page content' => TRUE,
      'edit own pattern content' => TRUE,
      'edit own pseudent_pose content' => TRUE,
      'edit terms in 1' => TRUE,
      'edit terms in 2' => TRUE,
      'edit terms in 3' => TRUE,
      'edit terms in 4' => TRUE,
      'list custom tokens' => TRUE,
      'peek content' => TRUE,
      'perform backup' => TRUE,
      'post comments' => TRUE,
      'revert revisions' => TRUE,
      'search all content' => TRUE,
      'search all excluded entities' => TRUE,
      'search blueprint_page content' => TRUE,
      'search content' => TRUE,
      'search course_page content' => TRUE,
      'search page content' => TRUE,
      'search pseudent_pose content' => TRUE,
      'skip comment approval' => TRUE,
      'use advanced search' => TRUE,
      'use save and edit' => TRUE,
      'use text format rest' => TRUE,
      'view own unpublished content' => TRUE,
      'view revisions' => TRUE,
      'view the administration theme' => TRUE,
      'view unpublished cyco blueprint content' => TRUE,
      'view unpublished cyco course content' => TRUE,
    ),
  );

  // Exported role: grader
  $roles['grader'] = array(
    'name' => 'grader',
    'weight' => 3,
    'permissions' => array(),
  );

  // Exported role: reviewer
  $roles['reviewer'] = array(
    'name' => 'reviewer',
    'weight' => 4,
    'permissions' => array(),
  );

  // Exported role: student
  $roles['student'] = array(
    'name' => 'student',
    'weight' => 2,
    'permissions' => array(),
  );

  return $roles;
}
