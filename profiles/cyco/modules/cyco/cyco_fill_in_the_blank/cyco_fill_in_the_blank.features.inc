<?php
/**
 * @file
 * cyco_fill_in_the_blank.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cyco_fill_in_the_blank_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "services" && $api == "services") {
    return array("version" => "3");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function cyco_fill_in_the_blank_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_menu_item_visibility_export_fields().
 */
function cyco_fill_in_the_blank_menu_item_visibility_export_fields() {
  $items = array(
    'menu-cp-actions_add-fill-in-the-blank:node/add/fill-in-the-blank' => array(
      0 => array(
        'rid' => 3,
      ),
      1 => array(
        'rid' => 4,
      ),
    ),
    'menu-cp-actions_fill-in-the-blanks:fill-in-the-blanks' => array(
      0 => array(
        'rid' => 3,
      ),
      1 => array(
        'rid' => 4,
      ),
      2 => array(
        'rid' => 5,
      ),
      3 => array(
        'rid' => 6,
      ),
      4 => array(
        'rid' => 7,
      ),
    ),
    'menu-cp-actions_list-fill-in-the-blanks:fill-in-the-blanks' => array(
      0 => array(
        'rid' => 3,
      ),
      1 => array(
        'rid' => 4,
      ),
      2 => array(
        'rid' => 5,
      ),
      3 => array(
        'rid' => 6,
      ),
      4 => array(
        'rid' => 7,
      ),
    ),
  );
  return $items;
}

/**
 * Implements hook_node_info().
 */
function cyco_fill_in_the_blank_node_info() {
  $items = array(
    'fill_in_the_blank' => array(
      'name' => t('Fill-in-the-blank'),
      'base' => 'node_content',
      'description' => t('Questions for students with immediate feedback.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
