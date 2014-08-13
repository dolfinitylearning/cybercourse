<?php
/**
 * @file
 * cyco_patterns.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cyco_patterns_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function cyco_patterns_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function cyco_patterns_node_info() {
  $items = array(
    'pattern' => array(
      'name' => t('Pattern'),
      'base' => 'node_content',
      'description' => t('A pattern is a way of doing something that people find works for them.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
