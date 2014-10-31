<?php
/**
 * @file
 * cyco_badges.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function cyco_badges_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-cp-actions_add-badge-type:node/add/badge
  $menu_links['menu-cp-actions_add-badge-type:node/add/badge'] = array(
    'menu_name' => 'menu-cp-actions',
    'link_path' => 'node/add/badge',
    'router_path' => 'node/add/badge',
    'link_title' => 'Add badge type',
    'options' => array(
      'attributes' => array(
        'title' => 'Define a new badge.',
      ),
      'identifier' => 'menu-cp-actions_add-badge-type:node/add/badge',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-actions_badges:badges',
  );
  // Exported menu link: menu-cp-actions_badges:badges
  $menu_links['menu-cp-actions_badges:badges'] = array(
    'menu_name' => 'menu-cp-actions',
    'link_path' => 'badges',
    'router_path' => 'badges',
    'link_title' => 'Badges',
    'options' => array(
      'attributes' => array(
        'title' => 'Students earn badges when they complete sets of exercises.',
      ),
      'identifier' => 'menu-cp-actions_badges:badges',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => -46,
    'customized' => 1,
  );
  // Exported menu link: menu-cp-actions_list-badges:badges
  $menu_links['menu-cp-actions_list-badges:badges'] = array(
    'menu_name' => 'menu-cp-actions',
    'link_path' => 'badges',
    'router_path' => 'badges',
    'link_title' => 'List badges',
    'options' => array(
      'attributes' => array(
        'title' => 'Show the badges students can earn.',
      ),
      'identifier' => 'menu-cp-actions_list-badges:badges',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-actions_badges:badges',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Add badge type');
  t('Badges');
  t('List badges');


  return $menu_links;
}
