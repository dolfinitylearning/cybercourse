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

  // Exported menu link: menu-cp-actions_add-a-big-idea:node/add/big-idea
  $menu_links['menu-cp-actions_add-a-big-idea:node/add/big-idea'] = array(
    'menu_name' => 'menu-cp-actions',
    'link_path' => 'node/add/big-idea',
    'router_path' => 'node/add/big-idea',
    'link_title' => 'Add a big idea',
    'options' => array(
      'attributes' => array(
        'title' => 'Add a new big idea.',
      ),
      'identifier' => 'menu-cp-actions_add-a-big-idea:node/add/big-idea',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-actions_big-ideas:big-ideas',
  );
  // Exported menu link: menu-cp-actions_big-ideas:big-ideas
  $menu_links['menu-cp-actions_big-ideas:big-ideas'] = array(
    'menu_name' => 'menu-cp-actions',
    'link_path' => 'big-ideas',
    'router_path' => 'big-ideas',
    'link_title' => 'Big ideas',
    'options' => array(
      'attributes' => array(
        'title' => 'Manage big ideas.',
      ),
      'identifier' => 'menu-cp-actions_big-ideas:big-ideas',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => -48,
    'customized' => 1,
  );
  // Exported menu link: menu-cp-actions_list-big-ideas:big-ideas
  $menu_links['menu-cp-actions_list-big-ideas:big-ideas'] = array(
    'menu_name' => 'menu-cp-actions',
    'link_path' => 'big-ideas',
    'router_path' => 'big-ideas',
    'link_title' => 'List big ideas',
    'options' => array(
      'attributes' => array(
        'title' => 'See all of the big ideas.',
      ),
      'identifier' => 'menu-cp-actions_list-big-ideas:big-ideas',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-actions_big-ideas:big-ideas',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Add a big idea');
  t('Big ideas');
  t('List big ideas');


  return $menu_links;
}
