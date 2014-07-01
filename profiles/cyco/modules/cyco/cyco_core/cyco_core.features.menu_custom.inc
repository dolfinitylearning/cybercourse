<?php
/**
 * @file
 * cyco_core.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function cyco_core_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: main-menu.
  $menus['main-menu'] = array(
    'menu_name' => 'main-menu',
    'title' => 'Main menu',
    'description' => 'The <em>Main</em> menu is used on many sites to show the major sections of the site, often in a top navigation bar.',
  );
  // Exported menu: menu-cp-authors.
  $menus['menu-cp-authors'] = array(
    'menu_name' => 'menu-cp-authors',
    'title' => 'CP authors',
    'description' => 'Control panel menu for authors.',
  );
  // Exported menu: menu-cp-reviewers.
  $menus['menu-cp-reviewers'] = array(
    'menu_name' => 'menu-cp-reviewers',
    'title' => 'CP reviewers',
    'description' => 'Control panel menu for reviewers.',
  );
  // Exported menu: menu-cp-students.
  $menus['menu-cp-students'] = array(
    'menu_name' => 'menu-cp-students',
    'title' => 'CP students',
    'description' => 'Control panel menu for students.',
  );
  // Exported menu: menu-menu-cp-graders.
  $menus['menu-menu-cp-graders'] = array(
    'menu_name' => 'menu-menu-cp-graders',
    'title' => 'CP graders',
    'description' => 'Control panel menu for graders.',
  );
  // Exported menu: menu-menu-cp-instructors.
  $menus['menu-menu-cp-instructors'] = array(
    'menu_name' => 'menu-menu-cp-instructors',
    'title' => 'CP instructors',
    'description' => 'Control panel menu for instructors.',
  );
  // Exported menu: menu-tools.
  $menus['menu-tools'] = array(
    'menu_name' => 'menu-tools',
    'title' => 'Tools',
    'description' => 'Tools for students.',
  );
  // Exported menu: user-menu.
  $menus['user-menu'] = array(
    'menu_name' => 'user-menu',
    'title' => 'User menu',
    'description' => 'The <em>User</em> menu contains links related to the user\'s account, as well as the \'Log out\' link.',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('CP authors');
  t('CP graders');
  t('CP instructors');
  t('CP reviewers');
  t('CP students');
  t('Control panel menu for authors.');
  t('Control panel menu for graders.');
  t('Control panel menu for instructors.');
  t('Control panel menu for reviewers.');
  t('Control panel menu for students.');
  t('Main menu');
  t('The <em>Main</em> menu is used on many sites to show the major sections of the site, often in a top navigation bar.');
  t('The <em>User</em> menu contains links related to the user\'s account, as well as the \'Log out\' link.');
  t('Tools');
  t('Tools for students.');
  t('User menu');


  return $menus;
}
