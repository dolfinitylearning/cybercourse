<?php
/**
 * @file
 * cyco_big_ideas.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cyco_big_ideas_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function cyco_big_ideas_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function cyco_big_ideas_node_info() {
  $items = array(
    'big_idea' => array(
      'name' => t('Big idea'),
      'base' => 'node_content',
      'description' => t('A central concept that helps students understand patterns and their use.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
