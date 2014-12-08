<?php
/**
 * @file
 * cyco_pseudents_import_terms.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function cyco_pseudents_import_terms_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'Positive',
    'description' => 'Positive expression. Happy, smiling.',
    'format' => 'plain_text',
    'weight' => 0,
    'uuid' => '28a64a9e-4391-4513-a69a-95f447057ae2',
    'vocabulary_machine_name' => 'pseudent_categories',
  );
  $terms[] = array(
    'name' => 'Teagan\'s character',
    'description' => 'Created by Teagan Mathieson, http://theapathyinitiative.com. Subject to the "Creative Commons Attribution-ShareAlike 4.0 International License":http://creativecommons.org/licenses/by-sa/4.0/.',
    'format' => 'plain_text',
    'weight' => 0,
    'uuid' => '2e15b0c6-c69a-46ec-b836-af21bb1cfd50',
    'vocabulary_machine_name' => 'pseudent_categories',
  );
  $terms[] = array(
    'name' => 'Neutral',
    'description' => 'Neutral expression.',
    'format' => 'plain_text',
    'weight' => 0,
    'uuid' => '305b8743-963d-40fb-87d5-3452853a95cb',
    'vocabulary_machine_name' => 'pseudent_categories',
  );
  $terms[] = array(
    'name' => 'Lily',
    'description' => 'One of Teagan\'s characters.',
    'format' => 'plain_text',
    'weight' => 0,
    'uuid' => '44e8b894-e715-4d0b-8e31-b853e996355c',
    'vocabulary_machine_name' => 'pseudent_categories',
  );
  $terms[] = array(
    'name' => 'Jeremy',
    'description' => 'One of Teagan\'s characters.',
    'format' => 'plain_text',
    'weight' => 0,
    'uuid' => '7ea8d0c6-47a4-4ebe-a1c7-6dc1e8a7604e',
    'vocabulary_machine_name' => 'pseudent_categories',
  );
  $terms[] = array(
    'name' => 'Simon',
    'description' => 'One of Teagan\'s characters.',
    'format' => 'plain_text',
    'weight' => 0,
    'uuid' => 'abce3c8a-90f6-48b9-a994-e395575537fe',
    'vocabulary_machine_name' => 'pseudent_categories',
  );
  $terms[] = array(
    'name' => 'Tara',
    'description' => 'One of Teagan\'s characters.',
    'format' => 'plain_text',
    'weight' => 0,
    'uuid' => 'b6fb56b4-86ab-4bdc-b9d5-d48b260a4f1d',
    'vocabulary_machine_name' => 'pseudent_categories',
  );
  $terms[] = array(
    'name' => 'Blank face',
    'description' => 'Customize to create a new expression.',
    'format' => 'plain_text',
    'weight' => 0,
    'uuid' => 'c5ad99cc-cb8e-475a-a7d3-3b9acb752733',
    'vocabulary_machine_name' => 'pseudent_categories',
  );
  $terms[] = array(
    'name' => 'Negative',
    'description' => 'Negative expression. Sad, angry, confused.',
    'format' => 'plain_text',
    'weight' => 0,
    'uuid' => 'e14e3939-e04e-4de1-b474-128916162b64',
    'vocabulary_machine_name' => 'pseudent_categories',
  );
  $terms[] = array(
    'name' => 'Klaus',
    'description' => 'One of Teagan\'s characters.',
    'format' => 'plain_text',
    'weight' => 0,
    'uuid' => 'e918b018-f13f-46f5-89e4-6bd774e6e9d5',
    'vocabulary_machine_name' => 'pseudent_categories',
  );
  return $terms;
}
