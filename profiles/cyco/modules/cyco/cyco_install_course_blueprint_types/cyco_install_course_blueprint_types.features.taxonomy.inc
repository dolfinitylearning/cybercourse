<?php
/**
 * @file
 * cyco_install_course_blueprint_types.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function cyco_install_course_blueprint_types_taxonomy_default_vocabularies() {
  return array(
    'blueprint_keywords' => array(
      'name' => 'Blueprint keywords',
      'machine_name' => 'blueprint_keywords',
      'description' => 'Keywords used only in the blueprint.',
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
