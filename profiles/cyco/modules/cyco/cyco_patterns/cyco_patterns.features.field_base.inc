<?php
/**
 * @file
 * cyco_patterns.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function cyco_patterns_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_actions'
  $field_bases['field_actions'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_actions',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'swim',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'swim_field',
  );

  // Exported field_base: 'field_explanation'
  $field_bases['field_explanation'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_explanation',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'swim',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'swim_with_summary_field',
  );

  // Exported field_base: 'field_situation'
  $field_bases['field_situation'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_situation',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'swim',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'swim_field',
  );

  return $field_bases;
}
