<?php
/**
 * @file
 * Load custom code chunks.
 */

require_once realpath(dirname(__FILE__)) . '/cyco_core_utilities.inc';
require_once realpath(dirname(__FILE__)) . '/cyco_core_error_handler.inc';
require_once realpath(dirname(__FILE__)) . '/cyco_core_control_panel.inc';
require_once realpath(dirname(__FILE__)) . '/cyco_core_control_panel.inc';
require_once realpath(dirname(__FILE__)) . '/cyco_core_groups.inc';

/**
 * URL of the CyCo wiki home page.
 */
define('CYCO_WIKI_MAIN_URL', 'https://wiki.cybercour.se');

/**
 * Implements hook_permission().
 */
function cyco_core_permission() {
  return array(
    'view unpublished cyco course content' => array(
      'title' => t('View unpublished course content'),
      'description' => t('User can see course content that has not been published.'),
    ),
    'view unpublished cyco blueprint content' => array(
      'title' => t('View unpublished blueprint content'),
      'description' => t('User can see blueprint content that has not been published.'),
    ),
  );
}

/**
 * Implements hook_menu().
 */
function cyco_core_menu() {
  $items = array();
  $items['admin/config/cyco'] = array(
    'title' => 'CyberCourse',
    'description' => 'Configuration of the CyberCourse system.',
    'page callback' => 'system_admin_menu_block_page',
    'access arguments' => array('administer site configuration'),
    'file' => 'system.admin.inc',
    'file path' => drupal_get_path('module', 'system'),
  );
  $items['admin/config/cyco/base'] = array(
    'title' => 'Basic CyberCourse stuff',
    'description' => 'Base configuration of the CyberCourse system.',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('cyco_core_settings_form'),
    'access arguments' => array('administer site configuration'),
  );
  //Create a new course page book. Redirects.
  $items['new-course'] = array(
    'page callback' => '_cyco_new_course',
    'access callback' => 'user_access',
    'access arguments' => array('create course_page content'),
  );
  //Create a new course page book. Redirects.
  $items['new-blueprint'] = array(
    'page callback' => '_cyco_new_blueprint',
    'access callback' => 'user_access',
    'access arguments' => array('create blueprint_page content'),
  );
  // Let other files add their own menu items.
  _cyco_core_error_add_menu_items($items);
  _cyco_core_cp_add_menu_items($items);
  _cyco_core_groups_add_menu_items($items);
  return $items;
}


/**
 * Implements hook_node_view().
 */
function cyco_core_node_view($node, $view_mode, $langcode) {
  //Call hooky thing in cyco_core_groups.inc.
  _cyco_core_groups_node_view($node, $view_mode, $langcode);
//  if ( module_exists('cyco_events_log') && $view_mode == 'full') {
//    if ( $node->type == 'course_page' || $node->type == 'basic_page' ) {
//      cyco_events_log_log_node_view($node, $view_mode, $langcode);
//    }
//  }
}


/**
 * Redirect to a page that will create a new course.
 */
function _cyco_new_course() {
//  drupal_goto('node/add/course-page?book_op=newbook');
  drupal_goto('node/add/course-page', 
      array('query' => 
        array('book_op' => 'newbook',)
      )
  );
}

/**
 * Redirect to a page that will create a new blueprint.
 */
function _cyco_new_blueprint() {
//  drupal_goto('node/add/blueprint-page?book_op=newbook');
  drupal_goto('node/add/blueprint-page', 
      array('query' => 
        array('book_op' => 'newbook',)
      )
  );
}

/**
 * Change the text of the You account link.
 * 
 * @param array $items Menu item data.
 */
function cyco_core_menu_alter(&$items) {
  $items['user']['title callback'] = '_cyco_core_user_menu_item_title';
}

/**
 * Implements hook_form_alter().
 */
function cyco_core_form_alter(&$form, $form_state, $form_id) {
  _cyco_core_utilities_form_alter($form, $form_state, $form_id);
  _cyco_core_groups_form_alter($form, $form_state, $form_id);
  if (module_exists('feedback') && $form_id == 'feedback_form' ) {
    $form['help']['#markup'] = 
          '<p>'
            . t(
                'Spot an error? Got a suggestion? Let us know! '
                . 'Feel free to cut-and-paste.'
                )
        . '</p>'
        . '<p>'
          . t(
              'For questions about assignments or grades, please '
              . 'contact your instructor directly.'
            )
        . '</p>';
    $form['message']['#cols'] = 40;
  }
  //Tweak node edit forms.
  if (strpos($form_id, 'node') !== FALSE) {
    $settings = array(
      'enabled' => TRUE,
    );
    drupal_add_js(
        array('cycoNodeEditTweaks' => $settings),
        'setting'
    );
    drupal_add_js(
        drupal_get_path('module', 'cyco_core') 
          . '/custom/js/cyco_node_edit_tweaks.js'
    );
    drupal_add_css(
        drupal_get_path('module', 'cyco_core') 
          . '/custom/css/cyco_node_edit_tweaks.css'
    );
    if (isset($form['field_attachments'])) {
      //Create the fieldset
      $form['attachments_fieldset'] = array(
        '#type' => 'fieldset',
        '#title' => t('Attach files'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );
      if (isset($form['field_attachments']['#weight'])) {
        $form['attachments_fieldset']['#weight'] = $form['field_attachments']['#weight'];
      }
      // Move the field into the fieldset
      $form['attachments_fieldset']['field_attachments'] = $form['field_attachments'];
      // Unset the original field
      unset($form['field_attachments']);
      // Are there hidden attachments?
      if (isset($form['field_hidden_attachments'])) {
        $form['attachments_fieldset']['field_hidden_attachments'] 
            = $form['field_hidden_attachments'];
        unset( $form['field_hidden_attachments'] );
      }
    }
  }
}

/**
 * Add user name to "Your account" link.
 * 
 * @global stdClass $user Current user.
 * 
 * @return string New title.
 */
function _cyco_core_user_menu_item_title() {
  global $user;
  if ($user->uid != 0) {
    $title = 'Your account (' . $user->name . ')';
    return $title;
  }
}

/**
 * Implements hook_init().
 */
function cyco_core_init() {
  // Let other files add their stuff.
  _cyco_core_error_init();
  _cyco_core_config_client_services();
}

/**
 * Define base config form.
 */
function cyco_core_settings_form($form, &$form_state) {
  $form['explanation'] = array(
    '#type' => 'markup',
    '#markup' => '<p>' . t(
      'If the tree menus get out of sync with the course/blueprint '
        . 'pages, click this button to rebuild the tree menus.' . '</p>'
    ),
  );
  $form['clear_cache'] = array(
    '#type' => 'submit',
    '#value' => t('Clear tree menu caches'),
    '#submit' => array('cyco_core_flush_tree_menu_caches'),
  );
  return $form;
}

/** 
 * Flush all the tree menu caches.
 */
function cyco_core_flush_tree_menu_caches() {
  if (function_exists('cyco_book_blocks_flush_all_tree_menu_caches')) {
    cyco_book_blocks_flush_all_tree_menu_caches();
    drupal_set_message(t('Tree menu caches cleared.'));
  }
  else {
    $message = __FILE__ . ' (line ' . __LINE__ . ') ' . __FUNCTION__
        . ' Flush function not found.';
    cyco_core_handle_error( $message );
  }
  drupal_goto('admin/config/cyco/base');
}

/**
 * Implements hook_theme().
 */
function cyco_core_theme() {
  $theme_defs = array();
  $theme_defs['cyco_reminder'] = array(
      'variables' => array(
        'reminder' => '',
        'hide_at_start' => FALSE,
      ),
  );
  //Let other files add their stuff.
  _cyco_control_panel_theme($theme_defs);
  return $theme_defs;
}

/**
 * Theme a reminder message.
 */
function theme_cyco_reminder($variables) {
  $reminder = $variables['reminder'];
  $result = '<p class="cyco_reminder" ';
  if ($variables['hide_at_start']) {
    $result .= ' style="display:none" ';
  }
  $result .= '>' . t($reminder) . '</p>';
  return $result;
}


