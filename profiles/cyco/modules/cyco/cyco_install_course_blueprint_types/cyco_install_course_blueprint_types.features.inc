<?php
/**
 * @file
 * cyco_install_course_blueprint_types.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cyco_install_course_blueprint_types_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function cyco_install_course_blueprint_types_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function cyco_install_course_blueprint_types_node_info() {
  $items = array(
    'blueprint_page' => array(
      'name' => t('Blueprint page'),
      'base' => 'node_content',
      'description' => t('A page about the design of the cybercourse.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'course_page' => array(
      'name' => t('Course page'),
      'base' => 'node_content',
      'description' => t('A page that\'s part of a course.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
