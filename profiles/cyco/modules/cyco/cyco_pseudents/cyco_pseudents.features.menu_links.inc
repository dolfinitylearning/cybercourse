<?php
/**
 * @file
 * cyco_pseudents.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function cyco_pseudents_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-cp-actions_add-a-new-pseudent-pose:node/add/pseudent-pose
  $menu_links['menu-cp-actions_add-a-new-pseudent-pose:node/add/pseudent-pose'] = array(
    'menu_name' => 'menu-cp-actions',
    'link_path' => 'node/add/pseudent-pose',
    'router_path' => 'node/add/pseudent-pose',
    'link_title' => 'Add a new pseudent pose.',
    'options' => array(
      'attributes' => array(
        'title' => 'Add a new pseudent pose.',
      ),
      'identifier' => 'menu-cp-actions_add-a-new-pseudent-pose:node/add/pseudent-pose',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-actions_pseudent-poses:pseudent-poses',
  );
  // Exported menu link: menu-cp-actions_list-pseudent-poses:pseudent-poses
  $menu_links['menu-cp-actions_list-pseudent-poses:pseudent-poses'] = array(
    'menu_name' => 'menu-cp-actions',
    'link_path' => 'pseudent-poses',
    'router_path' => 'pseudent-poses',
    'link_title' => 'List pseudent poses',
    'options' => array(
      'attributes' => array(
        'title' => 'See all of the pseudent poses.',
      ),
      'identifier' => 'menu-cp-actions_list-pseudent-poses:pseudent-poses',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-actions_pseudent-poses:pseudent-poses',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Add a new pseudent pose.');
  t('List pseudent poses');


  return $menu_links;
}
