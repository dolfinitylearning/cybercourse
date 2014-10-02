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

  // Exported menu link: menu-tools_patterns:patterns-public
  $menu_links['menu-tools_patterns:patterns-public'] = array(
    'menu_name' => 'menu-tools',
    'link_path' => 'patterns-public',
    'router_path' => 'patterns-public',
    'link_title' => 'Patterns',
    'options' => array(
      'attributes' => array(
        'title' => 'See all of the patterns used in the course',
      ),
      'identifier' => 'menu-tools_patterns:patterns-public',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Patterns');


  return $menu_links;
}
