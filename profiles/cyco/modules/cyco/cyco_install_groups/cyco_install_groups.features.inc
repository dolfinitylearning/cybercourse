<?php
/**
 * @file
 * cyco_install_groups.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cyco_install_groups_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function cyco_install_groups_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function cyco_install_groups_node_info() {
  $items = array(
    'class' => array(
      'name' => t('Class'),
      'base' => 'node_content',
      'description' => t('Class taking a course or courses. Students, graders, and instructors are all part of the class.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'class_post' => array(
      'name' => t('Class post'),
      'base' => 'node_content',
      'description' => t('Post to a class.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
