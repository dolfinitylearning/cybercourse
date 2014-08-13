<?php
/**
 * @file
 * cyco_exercises.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function cyco_exercises_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-cp-authors_add-model-solution:node/add/model-exercise-solution
  $menu_links['menu-cp-authors_add-model-solution:node/add/model-exercise-solution'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'node/add/model-exercise-solution',
    'router_path' => 'node/add/model-exercise-solution',
    'link_title' => 'Add model solution',
    'options' => array(
      'attributes' => array(
        'title' => 'Add a new model exercise solution.',
      ),
      'identifier' => 'menu-cp-authors_add-model-solution:node/add/model-exercise-solution',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -43,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-authors_exercises-and-rubics:exercises',
  );
  // Exported menu link: menu-cp-authors_add-new-exercise:node/add/exercise
  $menu_links['menu-cp-authors_add-new-exercise:node/add/exercise'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'node/add/exercise',
    'router_path' => 'node/add',
    'link_title' => 'Add new exercise',
    'options' => array(
      'attributes' => array(
        'title' => 'Create a new exercise.',
      ),
      'identifier' => 'menu-cp-authors_add-new-exercise:node/add/exercise',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-authors_exercises-and-rubics:exercises',
  );
  // Exported menu link: menu-cp-authors_add-new-rubric-item:node/add/rubric-item
  $menu_links['menu-cp-authors_add-new-rubric-item:node/add/rubric-item'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'node/add/rubric-item',
    'router_path' => 'node/add',
    'link_title' => 'Add new rubric item',
    'options' => array(
      'attributes' => array(
        'title' => 'Create a new rubric item for grading exercises.',
      ),
      'identifier' => 'menu-cp-authors_add-new-rubric-item:node/add/rubric-item',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -46,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-authors_exercises-and-rubics:exercises',
  );
  // Exported menu link: menu-cp-authors_exercises-and-rubics:exercises
  $menu_links['menu-cp-authors_exercises-and-rubics:exercises'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'exercises',
    'router_path' => 'exercises',
    'link_title' => 'Exercises and rubics',
    'options' => array(
      'attributes' => array(
        'title' => 'Exercises are tasks that students do. Rubrics are used to grade students\' work.',
      ),
      'identifier' => 'menu-cp-authors_exercises-and-rubics:exercises',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => -48,
    'customized' => 1,
  );
  // Exported menu link: menu-cp-authors_list-exercises:exercises
  $menu_links['menu-cp-authors_list-exercises:exercises'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'exercises',
    'router_path' => 'exercises',
    'link_title' => 'List exercises',
    'options' => array(
      'attributes' => array(
        'title' => 'See all the exercises',
      ),
      'identifier' => 'menu-cp-authors_list-exercises:exercises',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-authors_exercises-and-rubics:exercises',
  );
  // Exported menu link: menu-cp-authors_list-model-solutions:list-model-solutions
  $menu_links['menu-cp-authors_list-model-solutions:list-model-solutions'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'list-model-solutions',
    'router_path' => 'list-model-solutions',
    'link_title' => 'List model solutions',
    'options' => array(
      'attributes' => array(
        'title' => 'Model solutions to exercises.',
      ),
      'identifier' => 'menu-cp-authors_list-model-solutions:list-model-solutions',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -44,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-authors_exercises-and-rubics:exercises',
  );
  // Exported menu link: menu-cp-authors_list-rubric-items:rubric-items
  $menu_links['menu-cp-authors_list-rubric-items:rubric-items'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'rubric-items',
    'router_path' => 'rubric-items',
    'link_title' => 'List rubric items',
    'options' => array(
      'attributes' => array(
        'title' => 'See all rubric items.',
      ),
      'identifier' => 'menu-cp-authors_list-rubric-items:rubric-items',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -47,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-authors_exercises-and-rubics:exercises',
  );
  // Exported menu link: menu-cp-authors_manage-exercise-keywords:admin/structure/taxonomy/keywords
  $menu_links['menu-cp-authors_manage-exercise-keywords:admin/structure/taxonomy/keywords'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'admin/structure/taxonomy/keywords',
    'router_path' => 'admin/structure/taxonomy/%',
    'link_title' => 'Manage exercise keywords',
    'options' => array(
      'attributes' => array(
        'title' => 'Add, delete, and edit keywords',
      ),
      'identifier' => 'menu-cp-authors_manage-exercise-keywords:admin/structure/taxonomy/keywords',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-authors_exercises-and-rubics:exercises',
  );
  // Exported menu link: menu-cp-authors_manage-rubric-item-categories:admin/structure/taxonomy/rubric_item_categories
  $menu_links['menu-cp-authors_manage-rubric-item-categories:admin/structure/taxonomy/rubric_item_categories'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'admin/structure/taxonomy/rubric_item_categories',
    'router_path' => 'admin/structure/taxonomy/%',
    'link_title' => 'Manage rubric item categories',
    'options' => array(
      'attributes' => array(
        'title' => 'Group rubric items into categories to make them easier to work with. Manage the categories here.',
      ),
      'identifier' => 'menu-cp-authors_manage-rubric-item-categories:admin/structure/taxonomy/rubric_item_categories',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -45,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-authors_exercises-and-rubics:exercises',
  );
  // Exported menu link: menu-cp-graders_exercises:exercises
  $menu_links['menu-cp-graders_exercises:exercises'] = array(
    'menu_name' => 'menu-cp-graders',
    'link_path' => 'exercises',
    'router_path' => 'exercises',
    'link_title' => 'Exercises',
    'options' => array(
      'attributes' => array(
        'title' => 'See all the exercises.',
      ),
      'identifier' => 'menu-cp-graders_exercises:exercises',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -48,
    'customized' => 1,
  );
  // Exported menu link: menu-cp-graders_rubric-items:rubric-items
  $menu_links['menu-cp-graders_rubric-items:rubric-items'] = array(
    'menu_name' => 'menu-cp-graders',
    'link_path' => 'rubric-items',
    'router_path' => 'rubric-items',
    'link_title' => 'Rubric items',
    'options' => array(
      'attributes' => array(
        'title' => 'See all the rubric items.',
      ),
      'identifier' => 'menu-cp-graders_rubric-items:rubric-items',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -47,
    'customized' => 1,
  );
  // Exported menu link: menu-cp-instructors_exercises:exercises
  $menu_links['menu-cp-instructors_exercises:exercises'] = array(
    'menu_name' => 'menu-cp-instructors',
    'link_path' => 'exercises',
    'router_path' => 'exercises',
    'link_title' => 'Exercises',
    'options' => array(
      'attributes' => array(
        'title' => 'List exercises that students complete',
      ),
      'identifier' => 'menu-cp-instructors_exercises:exercises',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -46,
    'customized' => 1,
  );
  // Exported menu link: menu-cp-instructors_rubric-items:rubric-items
  $menu_links['menu-cp-instructors_rubric-items:rubric-items'] = array(
    'menu_name' => 'menu-cp-instructors',
    'link_path' => 'rubric-items',
    'router_path' => 'rubric-items',
    'link_title' => 'Rubric items',
    'options' => array(
      'attributes' => array(
        'title' => 'List rubric items used to grade exercises',
      ),
      'identifier' => 'menu-cp-instructors_rubric-items:rubric-items',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -45,
    'customized' => 1,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Add model solution');
  t('Add new exercise');
  t('Add new rubric item');
  t('Exercises');
  t('Exercises and rubics');
  t('List exercises');
  t('List model solutions');
  t('List rubric items');
  t('Manage exercise keywords');
  t('Manage rubric item categories');
  t('Rubric items');


  return $menu_links;
}
