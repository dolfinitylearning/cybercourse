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
  // Exported menu: menu-cp-actions.
  $menus['menu-cp-actions'] = array(
    'menu_name' => 'menu-cp-actions',
    'title' => 'CP actions',
    'description' => 'Control panel actions menu.',
  );
  // Exported menu: menu-cp-students.
  $menus['menu-cp-students'] = array(
    'menu_name' => 'menu-cp-students',
    'title' => 'CP students',
    'description' => 'Control panel menu for students.',
  );
  // Exported menu: menu-footer.
  $menus['menu-footer'] = array(
    'menu_name' => 'menu-footer',
    'title' => 'Footer',
    'description' => 'Menu for the bottom of the page.',
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
  t('CP actions');
  t('CP students');
  t('Control panel actions menu.');
  t('Control panel menu for students.');
  t('Footer');
  t('Main menu');
  t('Menu for the bottom of the page.');
  t('The <em>Main</em> menu is used on many sites to show the major sections of the site, often in a top navigation bar.');
  t('The <em>User</em> menu contains links related to the user\'s account, as well as the \'Log out\' link.');
  t('Tools');
  t('Tools for students.');
  t('User menu');


  return $menus;
}
