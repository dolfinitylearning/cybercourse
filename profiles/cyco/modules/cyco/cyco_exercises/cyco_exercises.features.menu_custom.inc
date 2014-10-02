<?php
/**
 * @file
 * cyco_exercises.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function cyco_exercises_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-cp-students.
  $menus['menu-cp-students'] = array(
    'menu_name' => 'menu-cp-students',
    'title' => 'CP students',
    'description' => 'Control panel menu for students.',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('CP students');
  t('Control panel menu for students.');


  return $menus;
}
