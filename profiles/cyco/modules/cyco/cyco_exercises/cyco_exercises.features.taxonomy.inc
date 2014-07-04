<?php
/**
 * @file
 * cyco_exercises.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function cyco_exercises_taxonomy_default_vocabularies() {
  return array(
    'rubric_item_categories' => array(
      'name' => 'Rubric item categories',
      'machine_name' => 'rubric_item_categories',
      'description' => 'Classifications for rubric items.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
  );
}
