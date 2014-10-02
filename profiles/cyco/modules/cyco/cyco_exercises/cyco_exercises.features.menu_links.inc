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
  t('Your submissions');


  return $menu_links;
}
