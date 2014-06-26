<?php
/**
 * @file
 * cyco_patterns.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function cyco_patterns_taxonomy_default_vocabularies() {
  return array(
    'pattern_categories' => array(
      'name' => 'Pattern categories',
      'machine_name' => 'pattern_categories',
      'description' => 'Categories for patterns. A pattern is a common way of doing something.',
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
