<?php
/**
 * @file
 * cyco_exercises.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cyco_exercises_ctools_plugin_api($module = NULL, $api = NULL) {
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
    'exercise' => array(
      'name' => t('Exercise'),
      'base' => 'node_content',
      'description' => t('Something for students to do.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'exercise_submission' => array(
      'name' => t('Exercise submission'),
      'base' => 'node_content',
      'description' => t('A submission for one exercise from one student. '),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'exercise_submission_rubric_item_' => array(
      'name' => t('Exercise submission rubric item rating'),
      'base' => 'node_content',
      'description' => t('Rating of one submission on one rubric item.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'model_exercise_solution' => array(
      'name' => t('Model exercise solution'),
      'base' => 'node_content',
      'description' => t('A solution to an exercise. Created by an author or instructor, as a model to be used in grading.'),
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
  return $items;
}
