<?php
/**
 * @file
 * cyco_exercises_model_solutions.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function cyco_exercises_model_solutions_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'additional_settings__active_tab_model_exercise_solution';
  $strongarm->value = 'edit-diff';
  $export['additional_settings__active_tab_model_exercise_solution'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'auto_entitylabel_node_model_exercise_solution';
  $strongarm->value = '1';
  $export['auto_entitylabel_node_model_exercise_solution'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'auto_entitylabel_pattern_node_model_exercise_solution';
  $strongarm->value = 'Model solution for [node:field_exercise_solved]';
  $export['auto_entitylabel_pattern_node_model_exercise_solution'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'auto_entitylabel_php_node_model_exercise_solution';
  $strongarm->value = 0;
  $export['auto_entitylabel_php_node_model_exercise_solution'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_access_model_exercise_solution';
  $strongarm->value = array(
    'view_own' => array(
      0 => 5,
      1 => 6,
      2 => 7,
      3 => 4,
      4 => 3,
    ),
    'view' => array(
      0 => 5,
      1 => 6,
      2 => 7,
      3 => 4,
      4 => 3,
    ),
  );
  $export['content_access_model_exercise_solution'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_enable_revisions_page_node_model_exercise_solution';
  $strongarm->value = 1;
  $export['diff_enable_revisions_page_node_model_exercise_solution'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_show_preview_changes_node_model_exercise_solution';
  $strongarm->value = 0;
  $export['diff_show_preview_changes_node_model_exercise_solution'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_view_mode_preview_node_model_exercise_solution';
  $strongarm->value = 'full';
  $export['diff_view_mode_preview_node_model_exercise_solution'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__model_exercise_solution';
  $strongarm->value = array(
    'view_modes' => array(
      'teaser' => array(
        'custom_settings' => TRUE,
      ),
      'full' => array(
        'custom_settings' => FALSE,
      ),
      'rss' => array(
        'custom_settings' => FALSE,
      ),
      'search_index' => array(
        'custom_settings' => FALSE,
      ),
      'search_result' => array(
        'custom_settings' => FALSE,
      ),
      'print' => array(
        'custom_settings' => FALSE,
      ),
      'diff_standard' => array(
        'custom_settings' => FALSE,
      ),
      'token' => array(
        'custom_settings' => FALSE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '0',
        ),
        'path' => array(
          'weight' => '6',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__model_exercise_solution'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_model_exercise_solution';
  $strongarm->value = array();
  $export['menu_options_model_exercise_solution'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_model_exercise_solution';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_model_exercise_solution'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_model_exercise_solution';
  $strongarm->value = array(
    0 => 'status',
    1 => 'revision',
  );
  $export['node_options_model_exercise_solution'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_model_exercise_solution';
  $strongarm->value = '1';
  $export['node_preview_model_exercise_solution'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_model_exercise_solution';
  $strongarm->value = 0;
  $export['node_submitted_model_exercise_solution'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_model_exercise_solution_pattern';
  $strongarm->value = 'model-exercise-solution/[node:title]';
  $export['pathauto_node_model_exercise_solution_pattern'] = $strongarm;

  return $export;
}
