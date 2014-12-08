<?php
/**
 * @file
 * cyco_exercises_submissions.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cyco_exercises_submissions_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function cyco_exercises_submissions_node_info() {
  $items = array(
    'exercise_submission' => array(
      'name' => t('Exercise submission'),
      'base' => 'node_content',
      'description' => t('A submission for one exercise from one student. '),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
