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

  // Exported menu link: menu-cp-actions_list-exercises:exercises
  $menu_links['menu-cp-actions_list-exercises:exercises'] = array(
    'menu_name' => 'menu-cp-actions',
    'link_path' => 'exercises',
    'router_path' => 'exercises',
    'link_title' => 'List exercises',
    'options' => array(
      'attributes' => array(
        'title' => 'See all the exercises',
      ),
      'identifier' => 'menu-cp-actions_list-exercises:exercises',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-actions_exercises-and-rubics:exercises',
  );
  // Exported menu link: menu-cp-actions_list-model-solutions:list-model-solutions
  $menu_links['menu-cp-actions_list-model-solutions:list-model-solutions'] = array(
    'menu_name' => 'menu-cp-actions',
    'link_path' => 'list-model-solutions',
    'router_path' => 'list-model-solutions',
    'link_title' => 'List model solutions',
    'options' => array(
      'attributes' => array(
        'title' => 'Model solutions to exercises.',
      ),
      'identifier' => 'menu-cp-actions_list-model-solutions:list-model-solutions',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -44,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-actions_exercises-and-rubics:exercises',
  );
  // Exported menu link: menu-cp-actions_list-rubric-items:rubric-items
  $menu_links['menu-cp-actions_list-rubric-items:rubric-items'] = array(
    'menu_name' => 'menu-cp-actions',
    'link_path' => 'rubric-items',
    'router_path' => 'rubric-items',
    'link_title' => 'List rubric items',
    'options' => array(
      'attributes' => array(
        'title' => 'See all rubric items.',
      ),
      'identifier' => 'menu-cp-actions_list-rubric-items:rubric-items',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -47,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-actions_exercises-and-rubics:exercises',
  );
  // Exported menu link: menu-tools_your-submissions:submissions-student-report
  $menu_links['menu-tools_your-submissions:submissions-student-report'] = array(
    'menu_name' => 'menu-tools',
    'link_path' => 'submissions-student-report',
    'router_path' => 'submissions-student-report',
    'link_title' => 'Your submissions',
    'options' => array(
      'attributes' => array(
        'title' => 'Your exercise submissions',
      ),
      'identifier' => 'menu-tools_your-submissions:submissions-student-report',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('List exercises');
  t('List model solutions');
  t('List rubric items');
  t('Your submissions');


  return $menu_links;
}
