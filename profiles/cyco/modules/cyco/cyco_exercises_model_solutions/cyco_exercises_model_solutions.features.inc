<?php
/**
 * @file
 * cyco_exercises_model_solutions.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cyco_exercises_model_solutions_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function cyco_exercises_model_solutions_node_info() {
  $items = array(
    'model_exercise_solution' => array(
      'name' => t('Model exercise solution'),
      'base' => 'node_content',
      'description' => t('A solution to an exercise. Created by an author or instructor, as a model to be used in grading.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
