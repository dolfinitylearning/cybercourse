<?php
/**
 * @file
 * cyco_core.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function cyco_core_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-cp-authors_blueprints-and-keywords:<front>
  $menu_links['menu-cp-authors_blueprints-and-keywords:<front>'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Blueprints and keywords',
    'options' => array(
      'attributes' => array(
        'title' => 'Most blueprint work is done by navigating to a blueprint page and selecting an action from there. Here are some extra things you can do.',
      ),
      'identifier' => 'menu-cp-authors_blueprints-and-keywords:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: menu-cp-authors_list-blueprint-pages-and-keywords:blueprints-and-keywords
  $menu_links['menu-cp-authors_list-blueprint-pages-and-keywords:blueprints-and-keywords'] = array(
    'menu_name' => 'menu-cp-authors',
    'link_path' => 'blueprints-and-keywords',
    'router_path' => 'blueprints-and-keywords',
    'link_title' => 'List blueprint pages and keywords',
    'options' => array(
      'attributes' => array(
        'title' => 'See all blueprint pages (including unpublished), and their keywords',
      ),
      'identifier' => 'menu-cp-authors_list-blueprint-pages-and-keywords:blueprints-and-keywords',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-authors_blueprints-and-keywords:<front>',
  );
  // Exported menu link: user-menu_control-panel:user/control-panel
  $menu_links['user-menu_control-panel:user/control-panel'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'user/control-panel',
    'router_path' => 'user/control-panel',
    'link_title' => 'Control panel',
    'options' => array(
      'attributes' => array(
        'title' => 'CyberCourse control panel.',
      ),
      'identifier' => 'user-menu_control-panel:user/control-panel',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: user-menu_log-out:user/logout
  $menu_links['user-menu_log-out:user/logout'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'user/logout',
    'router_path' => 'user/logout',
    'link_title' => 'Log out',
    'options' => array(
      'identifier' => 'user-menu_log-out:user/logout',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 10,
    'customized' => 0,
  );
  // Exported menu link: user-menu_user-account:user
  $menu_links['user-menu_user-account:user'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'user',
    'router_path' => 'user',
    'link_title' => 'User account',
    'options' => array(
      'alter' => TRUE,
      'identifier' => 'user-menu_user-account:user',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -10,
    'customized' => 0,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Blueprints and keywords');
  t('Control panel');
  t('List blueprint pages and keywords');
  t('Log out');
  t('User account');


  return $menu_links;
}
