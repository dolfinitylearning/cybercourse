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

  // Exported menu link: menu-cp-authors_add-new-exercise:node/add/exercise
  $menu_links['menu-cp-authors_add-new-exercise:node/add/exercise'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'node/add/exercise',
    'router_path' => 'node/add/exercise',
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
    'router_path' => 'node/add/rubric-item',
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
    'weight' => -47,
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
    'weight' => -48,
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
        'title' => 'List exercises',
      ),
      'identifier' => 'menu-cp-instructors_exercises:exercises',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -47,
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
        'title' => 'List rubric items',
      ),
      'identifier' => 'menu-cp-instructors_rubric-items:rubric-items',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -46,
    'customized' => 1,
  );
  // Exported menu link: menu-tools_exercises:exercises-public
  $menu_links['menu-tools_exercises:exercises-public'] = array(
    'menu_name' => 'menu-tools',
    'link_path' => 'exercises-public',
    'router_path' => 'exercises-public',
    'link_title' => 'Exercises',
    'options' => array(
      'attributes' => array(
        'title' => 'Exercises used in the course',
      ),
      'identifier' => 'menu-tools_exercises:exercises-public',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Add new exercise');
  t('Add new rubric item');
  t('Exercises');
  t('Exercises and rubics');
  t('List exercises');
  t('List rubric items');
  t('Rubric items');


  return $menu_links;
}
