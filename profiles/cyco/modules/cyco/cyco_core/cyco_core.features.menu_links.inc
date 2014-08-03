<?php
/**
 * @file
 * cyco_core.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function cyco_core_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-cp-authors_add-basic-page:node/add/page
  $menu_links['menu-cp-authors_add-basic-page:node/add/page'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'node/add/page',
    'router_path' => 'node/add',
    'link_title' => 'Add basic page',
    'options' => array(
      'attributes' => array(
        'title' => 'Add a new basic page',
      ),
      'identifier' => 'menu-cp-authors_add-basic-page:node/add/page',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-authors_basic-pages:basic-pages',
  );
  // Exported menu link: menu-cp-authors_add-class:node/add/class
  $menu_links['menu-cp-authors_add-class:node/add/class'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'node/add/class',
    'router_path' => 'node/add/class',
    'link_title' => 'Add class',
    'options' => array(
      'attributes' => array(
        'title' => 'Add a new class.',
      ),
      'identifier' => 'menu-cp-authors_add-class:node/add/class',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => 3,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-authors_classes:classes',
  );
  // Exported menu link: menu-cp-authors_add-user:admin/people/create
  $menu_links['menu-cp-authors_add-user:admin/people/create'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'admin/people/create',
    'router_path' => 'admin/people/create',
    'link_title' => 'Add user',
    'options' => array(
      'attributes' => array(
        'title' => 'Add a new user account.',
      ),
      'identifier' => 'menu-cp-authors_add-user:admin/people/create',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-authors_users:admin/people',
  );
  // Exported menu link: menu-cp-authors_all-content:admin/content
  $menu_links['menu-cp-authors_all-content:admin/content'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'admin/content',
    'router_path' => 'admin/content',
    'link_title' => 'All content',
    'options' => array(
      'attributes' => array(
        'title' => 'View and manage all content on the site, no matter what type.',
      ),
      'identifier' => 'menu-cp-authors_all-content:admin/content',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-authors_other:admin/content',
  );
  // Exported menu link: menu-cp-authors_basic-pages:basic-pages
  $menu_links['menu-cp-authors_basic-pages:basic-pages'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'basic-pages',
    'router_path' => 'basic-pages',
    'link_title' => 'Basic pages',
    'options' => array(
      'attributes' => array(
        'title' => 'Pages that are not part of a course or blueprint.',
      ),
      'identifier' => 'menu-cp-authors_basic-pages:basic-pages',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => -45,
    'customized' => 1,
  );
  // Exported menu link: menu-cp-authors_blueprints-and-keywords:blueprints-and-keywords
  $menu_links['menu-cp-authors_blueprints-and-keywords:blueprints-and-keywords'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'blueprints-and-keywords',
    'router_path' => 'blueprints-and-keywords',
    'link_title' => 'Blueprints and keywords',
    'options' => array(
      'attributes' => array(
        'title' => 'Most work on blueprints is done with the course tree menu(s). From this page, you can add new blueprints, and manage blueprint keywords.',
      ),
      'identifier' => 'menu-cp-authors_blueprints-and-keywords:blueprints-and-keywords',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: menu-cp-authors_classes:classes
  $menu_links['menu-cp-authors_classes:classes'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'classes',
    'router_path' => 'classes',
    'link_title' => 'Classes',
    'options' => array(
      'attributes' => array(
        'title' => 'Classes are groups of students taking a course, with an instructor.',
      ),
      'identifier' => 'menu-cp-authors_classes:classes',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => -43,
    'customized' => 1,
  );
  // Exported menu link: menu-cp-authors_courses-and-keywords:courses-and-keywords
  $menu_links['menu-cp-authors_courses-and-keywords:courses-and-keywords'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'courses-and-keywords',
    'router_path' => 'courses-and-keywords',
    'link_title' => 'Courses and keywords',
    'options' => array(
      'attributes' => array(
        'title' => 'Manage course pages and keywords',
      ),
      'identifier' => 'menu-cp-authors_courses-and-keywords:courses-and-keywords',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: menu-cp-authors_create-a-new-blueprint:node/add/blueprint-page
  $menu_links['menu-cp-authors_create-a-new-blueprint:node/add/blueprint-page'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'node/add/blueprint-page',
    'router_path' => 'node/add',
    'link_title' => 'Create a new blueprint',
    'options' => array(
      'query' => array(
        'book_op' => 'newbook',
      ),
      'attributes' => array(
        'title' => 'Start a new top-level blueprint. You can add other pages underneath it.',
      ),
      'identifier' => 'menu-cp-authors_create-a-new-blueprint:node/add/blueprint-page',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-authors_blueprints-and-keywords:blueprints-and-keywords',
  );
  // Exported menu link: menu-cp-authors_create-a-new-course:node/add/course-page
  $menu_links['menu-cp-authors_create-a-new-course:node/add/course-page'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'node/add/course-page',
    'router_path' => 'node/add',
    'link_title' => 'Create a new course',
    'options' => array(
      'query' => array(
        'book_op' => 'newbook',
      ),
      'attributes' => array(
        'title' => 'Start a new top-level course. You can add other pages underneath it.',
      ),
      'identifier' => 'menu-cp-authors_create-a-new-course:node/add/course-page',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => 2,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-authors_courses-and-keywords:courses-and-keywords',
  );
  // Exported menu link: menu-cp-authors_custom-tokens:admin/structure/token-custom
  $menu_links['menu-cp-authors_custom-tokens:admin/structure/token-custom'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'admin/structure/token-custom',
    'router_path' => 'admin/structure',
    'link_title' => 'Custom tokens',
    'options' => array(
      'attributes' => array(
        'title' => 'Tokens are replaced by custom text when pages are shown. For example, the token [feedback:student_first_name] might be replaced by Ann for one student, Willow for another, and Mike for a third. ',
      ),
      'identifier' => 'menu-cp-authors_custom-tokens:admin/structure/token-custom',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-authors_other:admin/content',
  );
  // Exported menu link: menu-cp-authors_list-basic-pages:basic-pages
  $menu_links['menu-cp-authors_list-basic-pages:basic-pages'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'basic-pages',
    'router_path' => 'basic-pages',
    'link_title' => 'List basic pages',
    'options' => array(
      'attributes' => array(
        'title' => 'See all of the basic pages, and their workflow tags.',
      ),
      'identifier' => 'menu-cp-authors_list-basic-pages:basic-pages',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-authors_basic-pages:basic-pages',
  );
  // Exported menu link: menu-cp-authors_list-blueprint-pages-and-keywords:blueprints-and-keywords
  $menu_links['menu-cp-authors_list-blueprint-pages-and-keywords:blueprints-and-keywords'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'blueprints-and-keywords',
    'router_path' => 'blueprints-and-keywords',
    'link_title' => 'List blueprint pages and keywords',
    'options' => array(
      'attributes' => array(
        'title' => 'See all blueprint pages (including unpublished), and their keywords',
      ),
      'identifier' => 'menu-cp-authors_list-blueprint-pages-and-keywords:blueprints-and-keywords',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-authors_blueprints-and-keywords:blueprints-and-keywords',
  );
  // Exported menu link: menu-cp-authors_list-classes:classes
  $menu_links['menu-cp-authors_list-classes:classes'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'classes',
    'router_path' => 'classes',
    'link_title' => 'List classes',
    'options' => array(
      'attributes' => array(
        'title' => 'See a list of all the classes.',
      ),
      'identifier' => 'menu-cp-authors_list-classes:classes',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-authors_classes:classes',
  );
  // Exported menu link: menu-cp-authors_list-course-pages-and-keywords:courses-and-keywords
  $menu_links['menu-cp-authors_list-course-pages-and-keywords:courses-and-keywords'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'courses-and-keywords',
    'router_path' => 'courses-and-keywords',
    'link_title' => 'List course pages and keywords',
    'options' => array(
      'attributes' => array(
        'title' => 'See all course pages (including unpublished), and their keywords',
      ),
      'identifier' => 'menu-cp-authors_list-course-pages-and-keywords:courses-and-keywords',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-authors_courses-and-keywords:courses-and-keywords',
  );
  // Exported menu link: menu-cp-authors_list-tagged-content:workflow-tagged
  $menu_links['menu-cp-authors_list-tagged-content:workflow-tagged'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'workflow-tagged',
    'router_path' => 'workflow-tagged',
    'link_title' => 'List tagged content',
    'options' => array(
      'attributes' => array(
        'title' => 'See everything that has a workflow tag attached.',
      ),
      'identifier' => 'menu-cp-authors_list-tagged-content:workflow-tagged',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => -44,
    'customized' => 1,
  );
  // Exported menu link: menu-cp-authors_list-users:admin/people
  $menu_links['menu-cp-authors_list-users:admin/people'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'admin/people',
    'router_path' => 'admin/people',
    'link_title' => 'List users',
    'options' => array(
      'attributes' => array(
        'title' => 'List and manage all site users.',
      ),
      'identifier' => 'menu-cp-authors_list-users:admin/people',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-authors_users:admin/people',
  );
  // Exported menu link: menu-cp-authors_manage-blueprint-keywords:admin/structure/taxonomy/blueprint_keywords
  $menu_links['menu-cp-authors_manage-blueprint-keywords:admin/structure/taxonomy/blueprint_keywords'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'admin/structure/taxonomy/blueprint_keywords',
    'router_path' => 'admin/structure/taxonomy/%',
    'link_title' => 'Manage blueprint keywords',
    'options' => array(
      'attributes' => array(
        'title' => 'Add, delete, and edit blueprint keywords',
      ),
      'identifier' => 'menu-cp-authors_manage-blueprint-keywords:admin/structure/taxonomy/blueprint_keywords',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-authors_blueprints-and-keywords:blueprints-and-keywords',
  );
  // Exported menu link: menu-cp-authors_manage-keywords:admin/structure/taxonomy/keywords
  $menu_links['menu-cp-authors_manage-keywords:admin/structure/taxonomy/keywords'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'admin/structure/taxonomy/keywords',
    'router_path' => 'admin/structure/taxonomy/%',
    'link_title' => 'Manage keywords',
    'options' => array(
      'attributes' => array(
        'title' => 'Add, delete, and edit keywords',
      ),
      'identifier' => 'menu-cp-authors_manage-keywords:admin/structure/taxonomy/keywords',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => 6,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-authors_courses-and-keywords:courses-and-keywords',
  );
  // Exported menu link: menu-cp-authors_manage-workflow-tags:admin/structure/taxonomy/workflow_tags
  $menu_links['menu-cp-authors_manage-workflow-tags:admin/structure/taxonomy/workflow_tags'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'admin/structure/taxonomy/workflow_tags',
    'router_path' => 'admin/structure/taxonomy/%',
    'link_title' => 'Manage workflow tags',
    'options' => array(
      'attributes' => array(
        'title' => 'Add new tags, remove tags, and change tag wording.',
      ),
      'identifier' => 'menu-cp-authors_manage-workflow-tags:admin/structure/taxonomy/workflow_tags',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-authors_list-tagged-content:workflow-tagged',
  );
  // Exported menu link: menu-cp-authors_other:admin/content
  $menu_links['menu-cp-authors_other:admin/content'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'admin/content',
    'router_path' => 'admin/content',
    'link_title' => 'Other',
    'options' => array(
      'attributes' => array(
        'title' => 'See all content of all types, change site appearance...',
      ),
      'identifier' => 'menu-cp-authors_other:admin/content',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => -40,
    'customized' => 1,
  );
  // Exported menu link: menu-cp-authors_users:admin/people
  $menu_links['menu-cp-authors_users:admin/people'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'admin/people',
    'router_path' => 'admin/people',
    'link_title' => 'Users',
    'options' => array(
      'attributes' => array(
        'title' => 'Every author, reviewer, instructor, etc., has his/her own user account on the site. Manage accounts here.',
      ),
      'identifier' => 'menu-cp-authors_users:admin/people',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => -41,
    'customized' => 1,
  );
  // Exported menu link: menu-cp-authors_workflow-tagged:workflow-tagged
  $menu_links['menu-cp-authors_workflow-tagged:workflow-tagged'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'workflow-tagged',
    'router_path' => 'workflow-tagged',
    'link_title' => 'Workflow tagged',
    'options' => array(
      'attributes' => array(
        'title' => 'See items that have a workflow tag attached',
      ),
      'identifier' => 'menu-cp-authors_workflow-tagged:workflow-tagged',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-authors_list-tagged-content:workflow-tagged',
  );
  // Exported menu link: menu-cp-graders_blueprints-and-keywords:blueprints-and-keywords
  $menu_links['menu-cp-graders_blueprints-and-keywords:blueprints-and-keywords'] = array(
    'menu_name' => 'menu-cp-graders',
    'link_path' => 'blueprints-and-keywords',
    'router_path' => 'blueprints-and-keywords',
    'link_title' => 'Blueprints and keywords',
    'options' => array(
      'identifier' => 'menu-cp-graders_blueprints-and-keywords:blueprints-and-keywords',
      'attributes' => array(
        'title' => 'A list of all the blueprints pages and their keywords.',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: menu-cp-graders_courses-and-keywords:courses-and-keywords
  $menu_links['menu-cp-graders_courses-and-keywords:courses-and-keywords'] = array(
    'menu_name' => 'menu-cp-graders',
    'link_path' => 'courses-and-keywords',
    'router_path' => 'courses-and-keywords',
    'link_title' => 'Courses and keywords',
    'options' => array(
      'identifier' => 'menu-cp-graders_courses-and-keywords:courses-and-keywords',
      'attributes' => array(
        'title' => 'A list of all the course pages and their keywords.',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: menu-cp-instructors_add-user:admin/people/create
  $menu_links['menu-cp-instructors_add-user:admin/people/create'] = array(
    'menu_name' => 'menu-cp-instructors',
    'link_path' => 'admin/people/create',
    'router_path' => 'admin/people/create',
    'link_title' => 'Add user',
    'options' => array(
      'identifier' => 'menu-cp-instructors_add-user:admin/people/create',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 1,
    'customized' => 0,
    'parent_identifier' => 'menu-cp-instructors_users:admin/people',
  );
  // Exported menu link: menu-cp-instructors_blueprints-and-keywords:blueprints-and-keywords
  $menu_links['menu-cp-instructors_blueprints-and-keywords:blueprints-and-keywords'] = array(
    'menu_name' => 'menu-cp-instructors',
    'link_path' => 'blueprints-and-keywords',
    'router_path' => 'blueprints-and-keywords',
    'link_title' => 'Blueprints and keywords',
    'options' => array(
      'identifier' => 'menu-cp-instructors_blueprints-and-keywords:blueprints-and-keywords',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: menu-cp-instructors_courses-and-keywords:courses-and-keywords
  $menu_links['menu-cp-instructors_courses-and-keywords:courses-and-keywords'] = array(
    'menu_name' => 'menu-cp-instructors',
    'link_path' => 'courses-and-keywords',
    'router_path' => 'courses-and-keywords',
    'link_title' => 'Courses and keywords',
    'options' => array(
      'identifier' => 'menu-cp-instructors_courses-and-keywords:courses-and-keywords',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: menu-cp-instructors_list-users:admin/people
  $menu_links['menu-cp-instructors_list-users:admin/people'] = array(
    'menu_name' => 'menu-cp-instructors',
    'link_path' => 'admin/people',
    'router_path' => 'admin/people',
    'link_title' => 'List users',
    'options' => array(
      'identifier' => 'menu-cp-instructors_list-users:admin/people',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'menu-cp-instructors_users:admin/people',
  );
  // Exported menu link: menu-cp-instructors_users:admin/people
  $menu_links['menu-cp-instructors_users:admin/people'] = array(
    'menu_name' => 'menu-cp-instructors',
    'link_path' => 'admin/people',
    'router_path' => 'admin/people',
    'link_title' => 'Users',
    'options' => array(
      'identifier' => 'menu-cp-instructors_users:admin/people',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -45,
    'customized' => 1,
  );
  // Exported menu link: menu-cp-reviewers_blueprints-and-keywords:blueprints-and-keywords
  $menu_links['menu-cp-reviewers_blueprints-and-keywords:blueprints-and-keywords'] = array(
    'menu_name' => 'menu-cp-reviewers',
    'link_path' => 'blueprints-and-keywords',
    'router_path' => 'blueprints-and-keywords',
    'link_title' => 'Blueprints and keywords',
    'options' => array(
      'identifier' => 'menu-cp-reviewers_blueprints-and-keywords:blueprints-and-keywords',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 1,
    'customized' => 0,
  );
  // Exported menu link: menu-cp-reviewers_courses-and-keywords:courses-and-keywords
  $menu_links['menu-cp-reviewers_courses-and-keywords:courses-and-keywords'] = array(
    'menu_name' => 'menu-cp-reviewers',
    'link_path' => 'courses-and-keywords',
    'router_path' => 'courses-and-keywords',
    'link_title' => 'Courses and keywords',
    'options' => array(
      'identifier' => 'menu-cp-reviewers_courses-and-keywords:courses-and-keywords',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Add basic page');
  t('Add class');
  t('Add user');
  t('All content');
  t('Basic pages');
  t('Blueprints and keywords');
  t('Classes');
  t('Courses and keywords');
  t('Create a new blueprint');
  t('Create a new course');
  t('Custom tokens');
  t('List basic pages');
  t('List blueprint pages and keywords');
  t('List classes');
  t('List course pages and keywords');
  t('List tagged content');
  t('List users');
  t('Manage blueprint keywords');
  t('Manage keywords');
  t('Manage workflow tags');
  t('Other');
  t('Users');
  t('Workflow tagged');


  return $menu_links;
}
