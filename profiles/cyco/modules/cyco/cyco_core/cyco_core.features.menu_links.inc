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

  // Exported menu link: main-menu_about:node/6
  $menu_links['main-menu_about:node/6'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/6',
    'router_path' => 'node/%',
    'link_title' => 'About',
    'options' => array(
      'identifier' => 'main-menu_about:node/6',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 1,
    'customized' => 0,
  );
  // Exported menu link: main-menu_help:node/4
  $menu_links['main-menu_help:node/4'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/4',
    'router_path' => 'node/%',
    'link_title' => 'Help',
    'options' => array(
      'identifier' => 'main-menu_help:node/4',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 2,
    'customized' => 0,
  );
  // Exported menu link: main-menu_welcome:node/5
  $menu_links['main-menu_welcome:node/5'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/5',
    'router_path' => 'node/%',
    'link_title' => 'Welcome',
    'options' => array(
      'identifier' => 'main-menu_welcome:node/5',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: menu-cp-actions_basic-pages:basic-pages
  $menu_links['menu-cp-actions_basic-pages:basic-pages'] = array(
    'menu_name' => 'menu-cp-actions',
    'link_path' => 'basic-pages',
    'router_path' => 'basic-pages',
    'link_title' => 'Basic pages',
    'options' => array(
      'attributes' => array(
        'title' => 'Pages that are not part of a course or blueprint.',
      ),
      'identifier' => 'menu-cp-actions_basic-pages:basic-pages',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => -44,
    'customized' => 1,
  );
  // Exported menu link: menu-cp-actions_classes:classes
  $menu_links['menu-cp-actions_classes:classes'] = array(
    'menu_name' => 'menu-cp-actions',
    'link_path' => 'classes',
    'router_path' => 'classes',
    'link_title' => 'Classes',
    'options' => array(
      'attributes' => array(
        'title' => 'Classes are groups of students taking a course, with an instructor.',
      ),
      'identifier' => 'menu-cp-actions_classes:classes',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => -42,
    'customized' => 1,
  );
  // Exported menu link: menu-cp-actions_list-blueprint-pages-and-keywords:blueprints-and-keywords
  $menu_links['menu-cp-actions_list-blueprint-pages-and-keywords:blueprints-and-keywords'] = array(
    'menu_name' => 'menu-cp-actions',
    'link_path' => 'blueprints-and-keywords',
    'router_path' => 'blueprints-and-keywords',
    'link_title' => 'List blueprint pages and keywords',
    'options' => array(
      'attributes' => array(
        'title' => 'See all blueprint pages (including unpublished), and their keywords',
      ),
      'identifier' => 'menu-cp-actions_list-blueprint-pages-and-keywords:blueprints-and-keywords',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-actions_blueprints-and-keywords:blueprints-and-keywords',
  );
  // Exported menu link: menu-cp-actions_workflow-tagged:workflow-tagged
  $menu_links['menu-cp-actions_workflow-tagged:workflow-tagged'] = array(
    'menu_name' => 'menu-cp-actions',
    'link_path' => 'workflow-tagged',
    'router_path' => 'workflow-tagged',
    'link_title' => 'Workflow tagged',
    'options' => array(
      'attributes' => array(
        'title' => 'See items that have a workflow tag attached',
      ),
      'identifier' => 'menu-cp-actions_workflow-tagged:workflow-tagged',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'menu-cp-actions_list-tagged-content:workflow-tagged',
  );
  // Exported menu link: menu-footer_copyright-you-20xx:node/3
  $menu_links['menu-footer_copyright-you-20xx:node/3'] = array(
    'menu_name' => 'menu-footer',
    'link_path' => 'node/3',
    'router_path' => 'node/%',
    'link_title' => 'Copyright, you, 20xx',
    'options' => array(
      'identifier' => 'menu-footer_copyright-you-20xx:node/3',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: menu-footer_credits:node/2
  $menu_links['menu-footer_credits:node/2'] = array(
    'menu_name' => 'menu-footer',
    'link_path' => 'node/2',
    'router_path' => 'node/%',
    'link_title' => 'Credits',
    'options' => array(
      'identifier' => 'menu-footer_credits:node/2',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 6,
    'customized' => 0,
  );
  // Exported menu link: menu-footer_terms-of-use:node/63
  $menu_links['menu-footer_terms-of-use:node/63'] = array(
    'menu_name' => 'menu-footer',
    'link_path' => 'node/63',
    'router_path' => 'node/%',
    'link_title' => 'Terms of use',
    'options' => array(
      'attributes' => array(
        'title' => 'Conditions you accept by using this site.',
      ),
      'identifier' => 'menu-footer_terms-of-use:node/63',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
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
  t('About');
  t('Basic pages');
  t('Classes');
  t('Control panel');
  t('Copyright, you, 20xx');
  t('Credits');
  t('Help');
  t('List blueprint pages and keywords');
  t('Log out');
  t('Terms of use');
  t('User account');
  t('Welcome');
  t('Workflow tagged');


  return $menu_links;
}
