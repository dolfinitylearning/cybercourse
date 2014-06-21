<?php
/**
 * @file
 * cyco_groups.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cyco_groups_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function cyco_groups_node_info() {
  $items = array(
    'circle' => array(
      'name' => t('Circle'),
      'base' => 'node_content',
      'description' => t('A group of people, for any purpose.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'class' => array(
      'name' => t('Class'),
      'base' => 'node_content',
      'description' => t('Class taking a course or courses. Students, graders, and instructors are all part of the class.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'group_content' => array(
      'name' => t('Group content'),
      'base' => 'node_content',
      'description' => t('Content posted to a class or group.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
