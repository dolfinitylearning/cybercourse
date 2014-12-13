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

  // Exported menu: menu-cp-actions.
  $menus['menu-cp-actions'] = array(
    'menu_name' => 'menu-cp-actions',
    'title' => 'CP actions',
    'description' => 'Control panel actions menu.',
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
  // Translatables
  // Included for use with string extractors like potx.
  t('CP actions');
  t('Control panel actions menu.');
  t('Footer');
  t('Menu for the bottom of the page.');
  t('Tools');
  t('Tools for students.');


  return $menus;
}
