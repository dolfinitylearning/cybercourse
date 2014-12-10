<?php
/**
 * @file
 * cyco_core.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function cyco_core_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'Review',
    'description' => NULL,
    'format' => NULL,
    'weight' => 1,
    'uuid' => '085cd9b3-fe77-4899-bf2e-d760be9693b9',
    'vocabulary_machine_name' => 'workflow_tags',
  );
  $terms[] = array(
    'name' => 'Create content',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '394129eb-66d0-4dc0-b620-15ecffcf2602',
    'vocabulary_machine_name' => 'workflow_tags',
  );
  return $terms;
}
