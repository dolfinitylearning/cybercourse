<?php
/**
 * @file
 * cyco_badges.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cyco_badges_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function cyco_badges_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function cyco_badges_node_info() {
  $items = array(
    'badge' => array(
      'name' => t('Badge'),
      'base' => 'node_content',
      'description' => t('A badge students can earn.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
