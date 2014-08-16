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

  // Exported menu link: menu-cp-authors_add-pseudent-pose:node/add/pseudent_pose
  $menu_links['menu-cp-authors_add-pseudent-pose:node/add/pseudent_pose'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'node/add/pseudent_pose',
    'router_path' => 'node/add',
    'link_title' => 'Add pseudent pose',
    'options' => array(
      'attributes' => array(
        'title' => 'Add a new pseudent pose.',
      ),
      'identifier' => 'menu-cp-authors_add-pseudent-pose:node/add/pseudent_pose',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-authors_pseudent-poses:pseudent-poses',
  );
  // Exported menu link: menu-cp-authors_list-pseudent-poses:pseudent-poses
  $menu_links['menu-cp-authors_list-pseudent-poses:pseudent-poses'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'pseudent-poses',
    'router_path' => 'pseudent-poses',
    'link_title' => 'List pseudent poses',
    'options' => array(
      'attributes' => array(
        'title' => 'See all of the pseudent poses.',
      ),
      'identifier' => 'menu-cp-authors_list-pseudent-poses:pseudent-poses',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-authors_pseudent-poses:pseudent-poses',
  );
  // Exported menu link: menu-cp-authors_manage-pseudent-categories:admin/structure/taxonomy/pseudent_categories
  $menu_links['menu-cp-authors_manage-pseudent-categories:admin/structure/taxonomy/pseudent_categories'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'admin/structure/taxonomy/pseudent_categories',
    'router_path' => 'admin/structure/taxonomy/%',
    'link_title' => 'Manage pseudent categories',
    'options' => array(
      'attributes' => array(
        'title' => 'Add, delete, and edit pseudent pose categories.',
      ),
      'identifier' => 'menu-cp-authors_manage-pseudent-categories:admin/structure/taxonomy/pseudent_categories',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-authors_pseudent-poses:pseudent-poses',
  );
  // Exported menu link: menu-cp-authors_pseudent-poses:pseudent-poses
  $menu_links['menu-cp-authors_pseudent-poses:pseudent-poses'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'pseudent-poses',
    'router_path' => 'pseudent-poses',
    'link_title' => 'Pseudent poses',
    'options' => array(
      'attributes' => array(
        'title' => 'Pseudo students, who take courses along with real students.',
      ),
      'identifier' => 'menu-cp-authors_pseudent-poses:pseudent-poses',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => -47,
    'customized' => 1,
  );
  // Exported menu link: menu-cp-graders_pseudent-poses:pseudent-poses
  $menu_links['menu-cp-graders_pseudent-poses:pseudent-poses'] = array(
    'menu_name' => 'menu-cp-graders',
    'link_path' => 'pseudent-poses',
    'router_path' => 'pseudent-poses',
    'link_title' => 'Pseudent poses',
    'options' => array(
      'attributes' => array(
        'title' => 'A list of all the pseudent poses.',
      ),
      'identifier' => 'menu-cp-graders_pseudent-poses:pseudent-poses',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => 2,
    'customized' => 1,
  );
  // Exported menu link: menu-cp-instructors_pseudent-poses:pseudent-poses
  $menu_links['menu-cp-instructors_pseudent-poses:pseudent-poses'] = array(
    'menu_name' => 'menu-cp-instructors',
    'link_path' => 'pseudent-poses',
    'router_path' => 'pseudent-poses',
    'link_title' => 'Pseudent poses',
    'options' => array(
      'identifier' => 'menu-cp-instructors_pseudent-poses:pseudent-poses',
      'attributes' => array(
        'title' => 'Show pseudent images and captions',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -47,
    'customized' => 1,
  );
  // Exported menu link: menu-cp-reviewers_pseudent-poses:pseudent-poses
  $menu_links['menu-cp-reviewers_pseudent-poses:pseudent-poses'] = array(
    'menu_name' => 'menu-cp-reviewers',
    'link_path' => 'pseudent-poses',
    'router_path' => 'pseudent-poses',
    'link_title' => 'Pseudent poses',
    'options' => array(
      'identifier' => 'menu-cp-reviewers_pseudent-poses:pseudent-poses',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 2,
    'customized' => 0,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Add pseudent pose');
  t('List pseudent poses');
  t('Manage pseudent categories');
  t('Pseudent poses');


  return $menu_links;
}
