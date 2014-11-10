<?php
/**
 * @file
 * cyco_pseudents.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function cyco_pseudents_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_enable_revisions_page_node_pseudent_pose';
  $strongarm->value = 1;
  $export['diff_enable_revisions_page_node_pseudent_pose'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_show_preview_changes_node_pseudent_pose';
  $strongarm->value = 0;
  $export['diff_show_preview_changes_node_pseudent_pose'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_view_mode_preview_node_pseudent_pose';
  $strongarm->value = 'full';
  $export['diff_view_mode_preview_node_pseudent_pose'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__pseudent_pose';
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
  $export['field_bundle_settings_node__pseudent_pose'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_pseudent_pose';
  $strongarm->value = array();
  $export['menu_options_pseudent_pose'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_pseudent_pose';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_pseudent_pose'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_pseudent_pose';
  $strongarm->value = array(
    0 => 'status',
    1 => 'revision',
  );
  $export['node_options_pseudent_pose'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_pseudent_pose';
  $strongarm->value = '1';
  $export['node_preview_pseudent_pose'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_pseudent_pose';
  $strongarm->value = 0;
  $export['node_submitted_pseudent_pose'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_pseudent_pose_pattern';
  $strongarm->value = 'pseudent-pose/[node:title]';
  $export['pathauto_node_pseudent_pose_pattern'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_taxonomy_term_pseudent_categories_pattern';
  $strongarm->value = '';
  $export['pathauto_taxonomy_term_pseudent_categories_pattern'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pseudents_poses_preview_data';
  $strongarm->value = array(
    14 => array(
      'nid' => 14,
      'title' => 'Angela',
      'url' => '/sites/default/files/course-resources/pseudent-images/doll7_medium.gif',
      'caption' => 'Angela',
      'categories' => array(
        4 => 'Serious',
      ),
    ),
    13 => array(
      'nid' => 13,
      'title' => 'Betty',
      'url' => '/sites/default/files/course-resources/pseudent-images/doll5_medium.gif',
      'caption' => 'Betty',
      'categories' => array(
        3 => 'Silly',
      ),
    ),
  );
  $export['pseudents_poses_preview_data'] = $strongarm;

  return $export;
}
