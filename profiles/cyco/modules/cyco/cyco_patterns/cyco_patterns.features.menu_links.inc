<?php
/**
 * @file
 * cyco_patterns.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function cyco_patterns_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-cp-authors_add-a-pattern:node/add/pattern
  $menu_links['menu-cp-authors_add-a-pattern:node/add/pattern'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'node/add/pattern',
    'router_path' => 'node/add',
    'link_title' => 'Add a pattern',
    'options' => array(
      'attributes' => array(
        'title' => 'Add a new pattern.',
      ),
      'identifier' => 'menu-cp-authors_add-a-pattern:node/add/pattern',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-authors_patterns:patterns',
  );
  // Exported menu link: menu-cp-authors_list-patterns:patterns
  $menu_links['menu-cp-authors_list-patterns:patterns'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'patterns',
    'router_path' => 'patterns',
    'link_title' => 'List patterns',
    'options' => array(
      'attributes' => array(
        'title' => 'See all of the patterns.',
      ),
      'identifier' => 'menu-cp-authors_list-patterns:patterns',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-authors_patterns:patterns',
  );
  // Exported menu link: menu-cp-authors_patterns:patterns
  $menu_links['menu-cp-authors_patterns:patterns'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'patterns',
    'router_path' => 'patterns',
    'link_title' => 'Patterns',
    'options' => array(
      'attributes' => array(
        'title' => 'See all of the patterns.',
      ),
      'identifier' => 'menu-cp-authors_patterns:patterns',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => -46,
    'customized' => 1,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Add a pattern');
  t('List patterns');
  t('Patterns');


  return $menu_links;
}
