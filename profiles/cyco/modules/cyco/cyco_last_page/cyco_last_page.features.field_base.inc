<?php
/**
 * @file
 * cyco_last_page.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function cyco_last_page_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_last_course_page_seen'
  $field_bases['field_last_course_page_seen'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_last_course_page_seen',
    'field_permissions' => array(
      'type' => 2,
    ),
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  return $field_bases;
}
