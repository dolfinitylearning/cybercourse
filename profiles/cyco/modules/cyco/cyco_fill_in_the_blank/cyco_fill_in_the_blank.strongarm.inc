<?php
/**
 * @file
 * cyco_fill_in_the_blank.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function cyco_fill_in_the_blank_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_fill_in_the_blank';
  $strongarm->value = 0;
  $export['comment_anonymous_fill_in_the_blank'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_fill_in_the_blank';
  $strongarm->value = 1;
  $export['comment_default_mode_fill_in_the_blank'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_fill_in_the_blank';
  $strongarm->value = '50';
  $export['comment_default_per_page_fill_in_the_blank'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_fill_in_the_blank';
  $strongarm->value = '1';
  $export['comment_fill_in_the_blank'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_fill_in_the_blank';
  $strongarm->value = 1;
  $export['comment_form_location_fill_in_the_blank'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_fill_in_the_blank';
  $strongarm->value = '1';
  $export['comment_preview_fill_in_the_blank'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_fill_in_the_blank';
  $strongarm->value = 1;
  $export['comment_subject_field_fill_in_the_blank'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__fill_in_the_blank';
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
          'weight' => '10',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__fill_in_the_blank'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_fill_in_the_blank';
  $strongarm->value = array();
  $export['menu_options_fill_in_the_blank'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_fill_in_the_blank';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_fill_in_the_blank'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_fill_in_the_blank';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_fill_in_the_blank'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_fill_in_the_blank';
  $strongarm->value = '0';
  $export['node_preview_fill_in_the_blank'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_fill_in_the_blank';
  $strongarm->value = 0;
  $export['node_submitted_fill_in_the_blank'] = $strongarm;

  return $export;
}
