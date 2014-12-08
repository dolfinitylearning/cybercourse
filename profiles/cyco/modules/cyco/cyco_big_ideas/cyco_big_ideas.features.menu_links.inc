<?php
/**
 * @file
 * cyco_big_ideas.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function cyco_big_ideas_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-tools_big-ideas:big-ideas-public
  $menu_links['menu-tools_big-ideas:big-ideas-public'] = array(
    'menu_name' => 'menu-tools',
    'link_path' => 'big-ideas-public',
    'router_path' => 'big-ideas-public',
    'link_title' => 'Big ideas',
    'options' => array(
      'attributes' => array(
        'title' => 'See all of the big ideas used in the course',
      ),
      'identifier' => 'menu-tools_big-ideas:big-ideas-public',
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
  t('Big ideas');


  return $menu_links;
}
