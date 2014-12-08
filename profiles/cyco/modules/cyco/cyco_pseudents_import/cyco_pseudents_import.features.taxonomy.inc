<?php
/**
 * @file
 * cyco_pseudents_import.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function cyco_pseudents_import_taxonomy_default_vocabularies() {
  return array(
    'pseudent_categories' => array(
      'name' => 'Pseudent categories',
      'machine_name' => 'pseudent_categories',
      'description' => 'Categories used to group pseudents. Makes pseudent selection easier in the SWIM editor.',
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
