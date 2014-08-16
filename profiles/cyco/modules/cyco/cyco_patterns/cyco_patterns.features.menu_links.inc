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
  // Exported menu link: menu-cp-authors_manage-pattern-categories:admin/structure/taxonomy/pattern_categories
  $menu_links['menu-cp-authors_manage-pattern-categories:admin/structure/taxonomy/pattern_categories'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'admin/structure/taxonomy/pattern_categories',
    'router_path' => 'admin/structure/taxonomy/%',
    'link_title' => 'Manage pattern categories',
    'options' => array(
      'attributes' => array(
        'title' => 'Group patterns into categories to make them easier to work with. Manage the categories here.',
      ),
      'identifier' => 'menu-cp-authors_manage-pattern-categories:admin/structure/taxonomy/pattern_categories',
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
  // Exported menu link: menu-cp-graders_patterns:patterns
  $menu_links['menu-cp-graders_patterns:patterns'] = array(
    'menu_name' => 'menu-cp-graders',
    'link_path' => 'patterns',
    'router_path' => 'patterns',
    'link_title' => 'Patterns',
    'options' => array(
      'attributes' => array(
        'title' => 'A list of all the patterns.',
      ),
      'identifier' => 'menu-cp-graders_patterns:patterns',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => 3,
    'customized' => 1,
  );
  // Exported menu link: menu-cp-instructors_patterns:patterns
  $menu_links['menu-cp-instructors_patterns:patterns'] = array(
    'menu_name' => 'menu-cp-instructors',
    'link_path' => 'patterns',
    'router_path' => 'patterns',
    'link_title' => 'Patterns',
    'options' => array(
      'identifier' => 'menu-cp-instructors_patterns:patterns',
      'attributes' => array(
        'title' => 'A pattern is a common way of doing something',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -48,
    'customized' => 1,
  );
  // Exported menu link: menu-cp-reviewers_patterns:patterns
  $menu_links['menu-cp-reviewers_patterns:patterns'] = array(
    'menu_name' => 'menu-cp-reviewers',
    'link_path' => 'patterns',
    'router_path' => 'patterns',
    'link_title' => 'Patterns',
    'options' => array(
      'identifier' => 'menu-cp-reviewers_patterns:patterns',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 3,
    'customized' => 0,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Add a pattern');
  t('List patterns');
  t('Manage pattern categories');
  t('Patterns');


  return $menu_links;
}
