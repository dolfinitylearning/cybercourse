<?php
/**
 * @file
 * cyco_pseudents.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cyco_pseudents_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function cyco_pseudents_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function cyco_pseudents_node_info() {
  $items = array(
    'pseudent_pose' => array(
      'name' => t('Pseudent pose'),
      'base' => 'node_content',
      'description' => t('A look for a pseudent, e.g., happy, sad, or confused. '),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
