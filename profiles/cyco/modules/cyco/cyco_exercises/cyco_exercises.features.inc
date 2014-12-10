<?php
/**
 * @file
 * cyco_exercises.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cyco_exercises_ctools_plugin_api($module = NULL, $api = NULL) {
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
function cyco_exercises_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function cyco_exercises_node_info() {
  $items = array(
    'exercise' => array(
      'name' => t('Exercise'),
      'base' => 'node_content',
      'description' => t('Something for students to do.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'rubric_item' => array(
      'name' => t('Rubric item'),
      'base' => 'node_content',
      'description' => t('One rubric item. It can be used in many exercises.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
