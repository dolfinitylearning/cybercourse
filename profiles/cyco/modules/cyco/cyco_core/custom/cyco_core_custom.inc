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
    'toggle event logging' => array(
      'title' => t('Toggle event logging'),
      'description' => t('User is able to turn event logging on and off.'),
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
  //Toggle event logging.
  $items['toggle-event-logging'] = array(
    'page callback' => '_cyco_toggle_event_logging',
    'access callback' => 'user_access',
    'access arguments' => array('toggle event logging'),
  );
  
  // Let other files add their own menu items.
  _cyco_core_error_add_menu_items($items);
  _cyco_core_cp_add_menu_items($items);
  _cyco_core_groups_add_menu_items($items);
  return $items;
}

/**
 * Implements hook_user_login().
 */
function cyco_core_user_login(&$edit, $account) {
  global $base_url;
  if ( _cyco_core_should_log_events() ) {
    //Log it.
    $entity_type = 'cyco_event';
    $entity = entity_create($entity_type, array('type' => 'log_in'));
    $wrapper = entity_metadata_wrapper($entity_type, $entity);
    $wrapper->uid = $account->uid;
    $wrapper->field_summary->set( 
        array('value' => t('Login by ') . '<a href="' . $base_url .'/users/' . $account->name 
          . '">' . $account->name . '</a>',
          'format'=>'limited_html',
        )
      );
    $wrapper->save();
  }
}

/**
 * Implements hook_user_login().
 */
function cyco_core_user_logout($account) {
  global $base_url;
  if ( _cyco_core_should_log_events() ) {
    //Log it.
    $entity_type = 'cyco_event';
    $entity = entity_create($entity_type, array('type' => 'log_out'));
    $wrapper = entity_metadata_wrapper($entity_type, $entity);
    $wrapper->uid = $account->uid;
    $wrapper->field_summary->set( 
        array('value' => t('Logout by ') . '<a href="' . $base_url .'/users/' . $account->name 
          . '">' . $account->name . '</a>',
          'format'=>'limited_html',
        )
      );
    $wrapper->save();
  }
}

/**
 * Implements hook_node_view().
 */
function cyco_core_node_view($node, $view_mode, $langcode) {
  global $base_url;
  if ( variable_get('cyco_event_logging', 'off') === 'on' ) {
    if ( $view_mode == 'full' && cyco_core_current_user_has_role('student') ) {
      //Log it.
      $entity_type = 'cyco_event';
      $entity = entity_create($entity_type, array('type' => 'view_node'));
      $wrapper = entity_metadata_wrapper($entity_type, $entity);
      global $user;
      $wrapper->uid = $user->uid;
      $user_name = ($user->uid === 0) ? 'Anonymous' : $user->name;
      $node_link = '<a href="' . $base_url .'/node/' . $node->nid 
            . '">' . $node->title . '</a>';
      $user_link = '<a href="' . $base_url .'/users/' . $user_name 
            . '">' . $user_name . '</a>';
      $message = t('View node ') . $node_link . t(' by ') . $user_link . '.';
      $wrapper->field_summary->set( 
          array('value' => $message,
            'format'=>'limited_html',
          )
        );
      $wrapper->field_node->set( $node->nid );
      $wrapper->save();
    }
  }
  //Call hooky thing in cyco_core_groups.inc.
  _cyco_core_groups_node_view($node, $view_mode, $langcode);
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
 * Toggle event logging.
 */
function _cyco_toggle_event_logging() {
  $logging = variable_get('cyco_event_logging', 'off');
  if ( $logging === 'on' ) {
    variable_set('cyco_event_logging', 'off');
    $message = t('Event logging is now off.');
  }
  else {
    variable_set('cyco_event_logging', 'on');
    $message = t('Event logging is now on.');
  }
  drupal_set_message( $message );
  drupal_goto('control-panel');
}

/**
 * Implements hook_form_alter().
 */
function cyco_core_form_alter(&$form, $form_state, $form_id) {
  _cyco_core_utilities_form_alter($form, $form_state, $form_id);
  _cyco_core_groups_form_alter($form, $form_state, $form_id);
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

/**
* Implements hook_services_resources().
 * 
 * Define all the services for the exercises module.
*/
function cyco_core_services_resources() {
  $api = array(
    /** Should save events flag. **/
    'event_logging' => array(
      'actions' => array(
        'shouldLogEvents' => array(
          'help' => t('Return yes/no, whether should log events for this user.'),
          'access arguments' => array('access content'),
          'callback' => '_cyco_core_get_should_log_events',
        ),
        'logEvent' => array(
          'help' => t('Log an event.'),
          'access arguments' => array('access content'),
          'callback' => '_cyco_core_log_event',
          'args' => array(
            array(
             'name' => 'data',
             'type' => 'struct',
             'description' => 'Event log data',
             'source' => 'data',
             'optional' => FALSE,
             ),
           ), //End args.
        ), // End LogEvent
      ),
    ),
  );
  return $api;
}

/**
 * Should log events?
 * @return string yes or no.
 */
function _cyco_core_get_should_log_events() {
  return 'yes';
  global $user;
  if ( variable_get('cyco_event_logging', 'off') === 'on' ) {
    if (cyco_core_user_has_role($user, 'student') ) {
      return 'yes';
    }
  }
  return 'no';
}

/**
 * Should log events?
 * @return boolean True if event logging is on, and the current user is a student.
 */
function _cyco_core_should_log_events() {
  return ( _cyco_core_get_should_log_events() == 'yes' );
}


function _cyco_core_log_event($data) {
  if (_cyco_core_should_log_events() ) {
    global $user;
    //Extract data.
    $bundle = $data['bundle'];
    $activity_type = $data['activityType'];
    $summary = $data['summary'];
    $params = $data['params'];
    //Log.
    $entity_type = 'cyco_event';
    $entity = entity_create($entity_type, array('type' => $bundle));
    $wrapper = entity_metadata_wrapper($entity_type, $entity);
    $wrapper->uid = $user->uid;
    $wrapper->field_summary->set( 
        array('value' => $summary,
          'format'=>'limited_html',
        )
    );
    $wrapper->field_activity_type->set( $activity_type );
    $wrapper->field_activity_params->set( $params );  
    $wrapper->save();
    return 'OK';
  }
}