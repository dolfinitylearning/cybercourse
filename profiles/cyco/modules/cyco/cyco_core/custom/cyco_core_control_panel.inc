<?php
/**
 * @file
 * Implements the control panel for CyberCourse.
 */

/**
 * Add menu item.
 */
function _cyco_core_cp_add_menu_items( &$items ) {
  $items['control-panel'] = array(
    'title' => 'Control panel',
    'description' => 'CyberCourse control panel.',
    'page callback' => '_cyco_render_control_panel',
    'access callback' => 'cyco_core_current_user_has_role',
    'access arguments' => array('authenticated user'),
    'menu_name' => 'user-menu',
    'weight' => -50,
    'type' => MENU_NORMAL_ITEM,
  );
  $items['clear-all-caches'] = array(
    'title' => 'Flush all caches',
    'page callback' => '_cyco_core_cp_flush_cache',
    'access callback' => '_cyco_core_cp_flush_cache_access',
    'type' => MENU_NORMAL_ITEM, //MENU_CALLBACK,
  );
}

/**
 * Is the current user allowed to flush all caches?
 * @return boolean True of allowed
 */
function _cyco_core_cp_flush_cache_access() {
  return cyco_core_current_user_has_role('author', 'administrator');
}

/**
 * Flush all caches.
 */
function _cyco_core_cp_flush_cache() {
  drupal_flush_all_caches();
  drupal_set_message(t('Drupal caches cleared.'));
  if (function_exists('cyco_book_blocks_flush_all_tree_menu_caches')) {
    cyco_book_blocks_flush_all_tree_menu_caches();
    drupal_set_message(t('Book tree menu caches cleared.'));
  }
  if (function_exists('_cyco_pseudents_generate_ck_pseudent_table')) {
    _cyco_pseudents_generate_ck_pseudent_table();
    drupal_set_message(t('Pseudent caches cleared.'));
  }
  if ( function_exists('cyco_badges_clear_cache') ) {
    cyco_badges_clear_cache();
    drupal_set_message( t('Badges cache cleared.') );
  }
  drupal_goto('control-panel');
}

/**
 * Implements hook_menu_link_alter().
 */
//function cyco_core_menu_link_alter(&$link) {
//  // Force the control panel link to appear on the top-level of 'user-menu'.
//  if ($link['link_path'] == 'user/control-panel') {
//    $link['plid'] = 0;
//  }
//}

/**
 * Generate HTML for the control panel.
 * @return string HTML.
 */
function _cyco_render_control_panel() {
  // Add JS to show menu titles as text.
  // Flag to tell JS to do its Evil Work.
  $settings = array(
    'showMenuTitles' => TRUE,
  );
  drupal_add_js(
      drupal_get_path('module', 'cyco_core')
        . '/custom/js/cyco_control_panel.js'
  );
  drupal_add_css(
      drupal_get_path('module', 'cyco_core')
      . '/custom/css/cyco_control_panel.css'
  );
  drupal_add_js(
      drupal_get_path('module', 'cyco_core')
        . '/custom/js/cyco_core_xkcd.js'
  );
  drupal_add_js(
      array('cycoControlPanel' => $settings),
      'setting'
  );
  $result = array();
  // Wrap all in a class with a known name, so JS menu code can target.
  $result['all_content'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'cyco-control-panel',
      ),
    ),
  );
  // Add intro elements.
  $wiki_link = l( t('CyberCourse wiki'), CYCO_WIKI_MAIN_URL );
  $message = t('The') . ' ' . $wiki_link . ' ' 
      . t('explains how to use the control panel.' );
  $result['all_content']['introduction'] = array(
    '#type' => 'markup',
    '#markup' => $message,
  );
  // Show user's groups.
  if ( module_exists( 'og' ) ) {
    $groups = cyco_core_groups_render_basic_list();
    if ( strstr($groups, 'views-row') === FALSE ) {
      $groups .= '<p>You are not a member of any groups.</p>';
    }
    $result['all_content']['groups_title'] =
          _cyco_control_panel_show_title( 'Your groups' );
    $result['all_content']['groups'] = array(
      '#type' => 'markup',
      '#markup' => $groups,
      '#prefix' => '<div class="groups-section">',
      '#suffix' => '</div>',
    );
    $result['all_content']['groups-list'] = array(
      '#type' => 'markup',
      '#markup' => l(t('List of classes'), 'classes-public',
        array( 'attributes' => 
          array(
            'class' => array('cyco_control_panel_group_list'), 
          ) 
        )
      ),
      '#prefix' => '<div class="groups-section">',
      '#suffix' => '</div>',
    );
  }
  if ( cyco_core_current_user_has_role( array('grader') ) ) {
    $result['all_content']['grader_title'] = 
        _cyco_control_panel_show_title( 'Grading' );
    $result['all_content']['num_submissions'] = 
        _cyco_control_panel_show_waiting_submissions();
//    $result['all_content']['grader_menu'] = 
//        _cyco_control_panel_show_menu_block( 'menu-cp-graders' );
  }
//  if ( cyco_core_current_user_has_role( array('student') ) ) {
//    $result['all_content']['student_title'] = 
//      _cyco_control_panel_show_title( 'Your stuff' );
//    $result['all_content']['student_menu'] = 
//      _cyco_control_panel_show_menu_block( 'menu-cp-students' );
//  }
//  else {
    $result['all_content']['actions_title'] = 
        _cyco_control_panel_show_title( 'Actions' );
    $result['all_content']['actions_menu'] = 
        _cyco_control_panel_show_menu_block( 'menu-cp-actions' );
//  }
  return $result;
}

/**
 * Make a renderable array element for a title.
 * @param string $title Title.
 * @return array Renderable element.
 */
function _cyco_control_panel_show_title( $title, $section_id = FALSE ) {
  $title_element = array(
    '#type' => 'markup',
    '#markup' => theme(
        'cyco_control_panel_section_title', 
         array( 
           'title' => $title,
           'id' => $section_id,
        )
    ),
  );
  return $title_element;
}

/**
 * Make a renderable array element for a menu block.
 * @param string $block_name Block name, e.g., menu-cp-actions.
 */
function _cyco_control_panel_show_menu_block( $block_name ) {
  $block = module_invoke('menu', 'block_view', $block_name);
  $markup = render($block['content']);
  $element = array(
    '#type' => 'markup',
    '#markup' => $markup,
  );
  return $element;
}

/**
 * Contributes hook_theme() pieces.
 */
function _cyco_control_panel_theme( &$theme_defs ) {
  $theme_defs['cyco_control_panel_section_title']
    = array(
      //Default variable values
      'variables' => array(
        'title' => '(no title)',
      ),
    );
  $theme_defs['cyco_control_panel_submissions_waiting_grading']
    = array(
      //Default variable values
      'variables' => array(
        'num_submissions' => 0,
      ),
    );
}

/**
 * Theme the title for a section on the CP.
 * @param type $variables Array with title.
 * @return string HTML.
 */
function theme_cyco_control_panel_section_title( $variables ) {
  $title = $variables['title'];
  $id = $variables['id'];
  $html =  '<h3 ';
  if ( $id ) {
    $html .= 'id="' . $id . '" ';
  }
  $html .= 'class="cyco-control-panel-section-title">' . $title . '</h3>';
  return $html;
}

/**
 * Show how many submissions are waiting the grader.
 * @return array Renderable element.
 */
function _cyco_control_panel_show_waiting_submissions() {
  $num_submissions = cyco_exercises_get_number_submissions_to_grade();
  $result = array(
    '#type' => 'markup',
    '#markup' => theme(
        'cyco_control_panel_submissions_waiting_grading', 
         array( 'num_submissions' => $num_submissions )
    ),
    '#prefix' => '<div class="grading-section">',
    '#suffix' => '</div>',
  );  
  return $result;
}

/**
 * Theme the number of submissions waiting for grading.
 * @param type $variables
 * @return string HTML.
 */
function theme_cyco_control_panel_submissions_waiting_grading( $variables ) {
  global $base_path;
  $num_submissions = $variables['num_submissions'];
  $message = '';
  $link = '';
  if ( $num_submissions == 0 ) {
    $message = t('You have no submissions to grade. ');
  }
  else {
    if ( $num_submissions == 1 ) {
      $message = t('You have one submission to grade. ');
    }
    else {
      $message 
          = t('You have ' . $num_submissions . ' submissions to grade. ');
    }
    $link = l( 
      'Give feedback', 
      drupal_get_path('module', 'cyco_exercises') 
        . '/custom/feedback_client/index.html', 
      array( 'attributes' => 
        array( 'class' => 
          array ( 'cyco-control-panel-grade-link' ) ,
        ), 
      ) 
    );
    drupal_add_js(
        drupal_get_path('module', 'cyco_exercises')
          . '/custom/js/cyco_exercises_start_grading_ui.js'
    );
  }
  $html =  '<p class="cyco-control-panel-submissions-waiting">'
      . $message . $link . '</p>';
  return $html;  
}
