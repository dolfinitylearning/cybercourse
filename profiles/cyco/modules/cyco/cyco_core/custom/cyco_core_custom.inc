<?php
/**
 * @file
 * Load custom code chunks.
 */

include_once realpath(dirname(__FILE__)) . '/cyco_core_utilities.inc';
include_once realpath(dirname(__FILE__)) . '/cyco_core_error_handler.inc';
include_once realpath(dirname(__FILE__)) . '/cyco_core_control_panel.inc';

/**
 * Implements hook_menu().
 */
function cyco_core_menu() {
  $items = array();
  $items['admin/config/cyco'] = array(
    'title' => 'CyberCourse',
    'description' => 'Configuration of the CyberCourse system.',
    'page callback' => 'system_admin_menu_block_page',
    'access arguments' => array('administer site configuration'),
    'file' => 'system.admin.inc',
    'file path' => drupal_get_path('module', 'system'),
  );
  $items['admin/config/cyco/base'] = array(
    'title' => 'Basic settings',
    'description' => 'Base configuration of the CyberCourse system.',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('cyco_core_settings_form'),
    'access arguments' => array('administer site configuration'),
  );
  //Let other files add their own menu items.
  _cyco_core_error_add_menu_items( $items );
  _cyco_core_cp_add_menu_items( $items );
  
  return $items;
}

/**
 * Implements hook_init().
 */
function cyco_core_init() {
  //Let other files add their stuff.
  _cyco_core_error_init();
}

/**
 * Implements hook_theme().
 */
function cyco_core_theme() {
  $theme_defs = array();
  //Let other files add their stuff.
  _cyco_control_panel_theme( $theme_defs );
  return $theme_defs;
}
