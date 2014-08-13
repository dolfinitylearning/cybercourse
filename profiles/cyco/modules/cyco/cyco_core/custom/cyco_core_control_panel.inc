<?php
/**
 * @file
 * Implements the control panel for CyberCourse.
 */

/**
 * Add menu item.
 */
function _cyco_core_cp_add_menu_items( &$items ) {
  $items['user/control-panel'] = array(
    'title' => 'Control panel',
    'description' => 'CyberCourse control panel.',
    'page callback' => '_cyco_render_control_panel',
    'access callback' => 'cyco_core_current_user_has_role',
    'access arguments' => array('authenticated user'),
    'menu_name' => 'user-menu',
    'weight' => 0,
    'type' => MENU_NORMAL_ITEM,
  );
}

/**
 * Implements hook_menu_link_alter().
 */
function cyco_core_menu_link_alter(&$link) {
  // Force the control panel link to appear on the top-level of 'user-menu'.
  if ($link['link_path'] == 'user/control-panel') {
    $link['plid'] = 0;
  }
}

/**
 * Generate HTML for the control panel.
 * @return string HTML.
 */
function _cyco_render_control_panel() {
  //Add JS to show menu titles as text.
  //Flag to tell JS to do its Evil Work.
  $settings = array(
    'showMenuTitles' => TRUE,
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
  //Wrap all in a class with a known name, so JS menu code can target.
  $result['all_content'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'cyco-control-panel',
      ),
    ),
  );
  //Add intro elements.
  $wiki_link = l( t('The CyberCourse wiki'), CYCO_WIKI_MAIN_URL );
  $message = $wiki_link . t( ' explains how to use the control panel. ' );
  if ( cyco_core_current_user_has_role('author') ) {
    $message .= 'For complete control, log in as an administrator.';
  }
  $result['all_content']['introduction'] = array(
    '#type' => 'markup',
    '#markup' => $message,
  );
  //Show user's groups.
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
    );    
  }
  if ( cyco_core_current_user_has_role( array('author') ) ) {
    $result['all_content']['author_title'] = 
        _cyco_control_panel_show_title( 'Author actions' );
    $result['all_content']['author_menu'] = 
        _cyco_control_panel_show_menu_block( 'menu-cp-authors' );
  }
  if ( cyco_core_current_user_has_role( array('instructor') ) ) {
    $result['all_content']['instructor_title'] = 
        _cyco_control_panel_show_title( 'Instructor actions' );
    $result['all_content']['instructor_menu'] = 
        _cyco_control_panel_show_menu_block( 'menu-cp-instructors' );
  }
  if ( cyco_core_current_user_has_role( array('grader') ) ) {
    $result['all_content']['grader_title'] = 
        _cyco_control_panel_show_title( 'Grader actions' );
    $result['all_content']['num_submissions'] = 
        _cyco_control_panel_show_waiting_submissions();
    $result['all_content']['grader_menu'] = 
        _cyco_control_panel_show_menu_block( 'menu-cp-graders' );
  }
  if ( cyco_core_current_user_has_role( array('reviewer') ) ) {
    $result['all_content']['reviewer_title'] = 
      _cyco_control_panel_show_title( 'Reviewer actions' );
    $result['all_content']['reviewer_menu'] = 
      _cyco_control_panel_show_menu_block( 'menu-cp-reviewers' );
  }
  if ( cyco_core_current_user_has_role( array('student') ) ) {
    $result['all_content']['student_title'] = 
      _cyco_control_panel_show_title( 'Student actions' );
    $result['all_content']['student_menu'] = 
      _cyco_control_panel_show_menu_block( 'menu-cp-students' );
  }
  return $result;
}

/**
 * Make a renderable array element for a title.
 * @param string $title Title.
 * @return array Renderable element.
 */
function _cyco_control_panel_show_title( $title ) {
  $title_element = array(
    '#type' => 'markup',
    '#markup' => theme(
        'cyco_control_panel_section_title', 
         array( 'title' => $title )
    ),
  );
  return $title_element;
}

/**
 * Make a renderable array element for a menu block.
 * @param string $block_name Block name, e.g., menu-cp-authors.
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
  $html =  '<h3 class="cyco-control-panel-section-title">' . $title . '</h3>';
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
    $message = t('You have no submissions to grade.');
  }
  else {
    if ( $num_submissions == 1 ) {
      $message = t('You have one submission to grade. ');
    }
    else {
      $message = t('You have ' . $num_submissions . ' submissions to grade. ');
    }
    $link = l( 
      'Give feedback', 
      drupal_get_path('module', 'cyco_exercises') 
        . '/custom/feedback_client/index.html', 
      array( 'attributes' => 
        array( 'class' => 
          array ( 'cyco-control-panel-grade-link' ) 
        ), 
      ) 
    );
    drupal_add_js(
        $base_path . drupal_get_path('module', 'cyco_exercises')
          . '/custom/js/cyco_exercises_start_grading_ui.js'
    );
  }
  $html =  '<p class="cyco-control-panel-submissions-waiting">'
      . $message . $link . '</p>';
  return $html;  
}
