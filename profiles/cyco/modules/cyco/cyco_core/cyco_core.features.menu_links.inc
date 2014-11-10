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
//KRM
return;
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
    'weight' => -50,
    'customized' => 1,
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
    'weight' => -10,
    'customized' => 1,
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
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -30,
    'customized' => 1,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Control panel');
  t('Log out');
  t('User account');


  return $menu_links;
}
