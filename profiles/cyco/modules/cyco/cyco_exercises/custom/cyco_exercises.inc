<?php
/**
 * @file
 * Exercise system implementation.
 */

// First name to use when the user did not give one.
define( 'GENERIC_FIRST_NAME', 'Willow' );
// Last name to use when the user did not give one.
define( 'GENERIC_LAST_NAME', 'Rosenberg' );

/**
 * Implements hook_menu.
 */
function cyco_exercises_menu() {
  $items = array();
  // A page that just closes the window it is in.
  $items['cyco-exercises-close-popup'] = array(
    'title' => 'Done',
    'page callback' => '_cyco_exercises_close_popup',
    'access callback' => TRUE,
    'type' => MENU_CALLBACK,
  );
  $items['admin/config/cyco/exercise'] = array(
    'title' => 'Exercises settings',
    'description' => 'Configuration of the Cybercourse exercises module.',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('cyco_exercises_settings_form'),
    'access arguments' => array('admininster site configuration'),
    'file' => 'custom/cyco_exercises.admin.inc',
    'file path' => drupal_get_path('module', 'cyco_exercises'),
    );
  return $items;
}

/**
 * Implements hook_menu_local_tasks_alter
 */
function cyco_exercises_menu_local_tasks_alter(&$data, $router_item, $root_path) {
  switch ($root_path) {
    case 'exercises':
      if ( cyco_core_current_user_has_role( array('author', 'administrator') ) ) {
        // Link to add exercise.
        $item = menu_get_item('node/add/exercise');
        $item['title'] = t('Add exercise');
        $data['actions']['output'][] = array(
          '#theme' => 'menu_local_action',
          '#link' => $item,
        );
        // Link to add rubric item.
        $item = menu_get_item('node/add/rubric-item');
        $item['title'] = t('Add rubric item');
        $data['actions']['output'][] = array(
          '#theme' => 'menu_local_action',
          '#link' => $item,
        );
      }
      break;
    case 'node/%':
      $path = $router_item['href'];
      list( $ignore, $nid ) = explode('/', $path);
      $node = node_load($nid);
      switch ( $node->type ) {
        case 'rubric_item':
          // Link to add rubric item.
          $item = menu_get_item('node/add/rubric-item');
          $item['title'] = t('Add rubric item');
          $data['actions']['output'][] = array(
            '#theme' => 'menu_local_action',
            '#link' => $item,
          );
          //Link to list rubric items.
          $item = menu_get_item('rubric-items');
          $item['title'] = t('List rubric items');
          $data['actions']['output'][] = array(
            '#theme' => 'menu_local_action',
            '#link' => $item,
          );
          break;
        case 'exercise':
          if ( cyco_core_current_user_has_role( 
                array('author', 'administrator', 'grader', 'reviewer') 
              ) ) {
            //List exercises.
            $item = menu_get_item('exercises');
            $item['title'] = t('List exercises');
            $data['actions']['output'][] = array(
              '#theme' => 'menu_local_action',
              '#link' => $item,
            );
          }
          if ( cyco_core_current_user_has_role( array('author', 'administrator') ) ) {
            //Link to add exercise.
            $item = menu_get_item('node/add/exercise');
            $item['title'] = t('Add exercise');
            $data['actions']['output'][] = array(
              '#theme' => 'menu_local_action',
              '#link' => $item,
            );
            //Link to add rubric item.
            $item = menu_get_item('node/add/rubric-item');
            $item['title'] = t('Add rubric item');
            $data['actions']['output'][] = array(
              '#theme' => 'menu_local_action',
              '#link' => $item,
            );
          }
          break;
      }
      break;
  }
}

function cyco_exercises_permission() {
  return array(
    'administer exercises settings' => array(
      'title' => t('Administer exercises settings'),
      'restrict access' => TRUE,
    ),
  );
}

/**
 * Called in hook_menu, to close current browser window (a popup).
 */
function _cyco_exercises_close_popup() {
  global $base_url;
  $path = $base_url . '/' . drupal_get_path('module', 'cyco_exercises')
      . '/custom/js/close_popup.js';
  drupal_add_js($path);
  return '<h1>Done</h1>'; //Need to return something here.
}

/**
 * Implements hook_node_access().
 * 
 * Students can edit own submission only when it has not been graded.
 */
function cyco_exercises_node_access( $node, $op, $account ) {
  if ( $node == 'exercise_submission' ) {
    // It's a new exercise submission. Don't regulate it.
    return NODE_ACCESS_IGNORE;
  }
  if ( isset( $node->type ) && $node->type == 'exercise_submission' ) {
    // Don't restrict authors and admins.
    if (cyco_core_user_has_role($account, array( 'author', 'administrator') ) ) {
      return NODE_ACCESS_IGNORE;
    }
    // Instructors and graders can only work with submissions from their own groups.
    if (cyco_core_user_has_role($account, array( 'instructor', 'grader') ) ) {
      $gids = cyco_core_groups_get_groups_for_user('class');
      if (sizeof($gids) == 0 ) {
        return NODE_ACCESS_DENY;
      }
      // Get all users in those groups.
      $all_uids = array();
      foreach ($gids as $gid) {
        $uids = cyco_core_groups_get_group_users($gid);
        $all_uids = array_merge($all_uids, $uids);
      }
      // See if the user is in the list.
      if ( !in_array($account->uid, $all_uids) ) {
        return NODE_ACCESS_DENY;
      }
    }
    if ( cyco_core_user_has_role($account, 'student') ) {
      // Students can only view or change their own submissions.
      if ( $account->uid != $node->uid ) {
        return NODE_ACCESS_DENY;
      }
      if ( $op == 'update' || $op == 'delete' ) {
        // Students can only edit submissions that have no feedback.
        if ( isset( $node->field_when_feedback_given[ $node->language ][0]['value'] ) ) {
          return NODE_ACCESS_DENY;
        }
      }
    }
  }
  return NODE_ACCESS_IGNORE;
}

/**
 * Implements hook_swim_betwixt_markup_2_html_alter().
 * 
 * Translate exercise CyCo markup in $content to its 
 * viewHTML equivalent. 
 * 
 * [[[cycoexercise:123]]]
 * 
 * See SWIM docs for more.
 */
function cyco_exercises_swim_betwixt2html_alter(&$content) {
  $regex = '/\[\[\[\s*cycoexercise\:(\d+)\s*\]\]\]/';
  // [[[, optional whitespace, cycoexercise, optional whitespace, 
  // exercise number, optional whitespace, ]]]
  $content = preg_replace_callback($regex, '_cyco_exercises_make_replacements', $content);
}

/**
 * Generates the HTML for the exercise.
 */
function _cyco_exercises_make_replacements($matches) {
  $exercise_nid = $matches[1];
  $exercise_node = node_load($exercise_nid);
  // Make sure that this is the right type of node.
  if ($exercise_node == FALSE || !node_access('view', $exercise_node) || !$exercise_node->status || $exercise_node->type != 'exercise') {
    $message = t('Invalid exercise id: @id', array('@id' => $exercise_nid));
    drupal_set_message($message);
    watchdog('cyco_exercises', $message);
    return '<p>' . $message . '</p>';
  }
  else {
    //Make the submission links.
    global $user;
    $labeled_links = '';
    $too_bad_so_sad_message = '';
    if ( ! cyco_core_user_has_role($user, 'student') ) {
      $too_bad_so_sad_message = t('(If you were logged in as a student, '
          . 'you could submit an exercise solution, and get some feedback.)'
      );
    }
    else {
      // If there is no submission, there is only a link to create a new one.
      // If there is an existing submission:
      //   If there is no feedback yet, there is only an edit link.
      //   If there is feedback, there is a Review link, and a new version link.
      global $base_url;
      // Create submission links for this exercise.
      drupal_add_js(
          $base_url . '/' . drupal_get_path('module', 'cyco_exercises')
          . '/custom/js/cyco_exercises_submission_links.js'
      );
      // Send current user uid to client.
      drupal_add_js(
          array('cyco_exercises' => 
            array(
              'uid' => $user->uid,
            ),
          ),
          'setting'
      );
    }
    $body_content = swim_markdown2html(
        $exercise_node->field_body[LANGUAGE_NONE][0]['value']
    );
    $result = theme('cyco_embedded_exercise', array(
      'exercise_nid' => $exercise_nid,
      'title' => $exercise_node->title,
      'body' => $body_content,
      'labeled_links' => $labeled_links,
      'too_bad_so_sad_message' => $too_bad_so_sad_message,
    ));
    return $result;
  }
}

/**
 * Make links for exercise solution submission.
 * 
 * @param type $exercise_node The nid of the exercise.
 * @return array Labelled link data.
 */
function _cyco_exercises_make_submit_links() {
  // Make the submission links.
  global $user;
  $too_bad_so_sad_message = '';
  if ( ! cyco_core_user_has_role($user, 'student') ) {
    $too_bad_so_sad_message = t('(If you were logged in as a student, '
        . 'you could submit an exercise solution, and get some feedback.)'
    );
  }
  else {
    // If there is no submission, there is only a link to create a new one.
    // If there is an existing submission:
    //   If there is no feedback yet, there is only an edit link.
    //   If there is feedback, there is a Review link, and a new version link.
    global $base_url;
    // Create submission links for this exercise.
    drupal_add_js(
        $base_url . '/' . drupal_get_path('module', 'cyco_exercises')
        . '/custom/js/cyco_exercises_submission_links.js'
    );
    // Send current user uid to client.
    drupal_add_js(
        array('cyco_exercises' => 
          array(
            'uid' => $user->uid,
          ),
        ),
        'setting'
    );
  }
  return $too_bad_so_sad_message;
}

/**
 * Implement hook_theme().
 */
function cyco_exercises_theme() {
  $result = array(
    // HTML for rubric selection UI.
    'select_rubric_item' => array(
      'template' => 'custom/templates/cyco-exercises-select-rubric-item',
    ),
    'cyco_embedded_exercise' => array(
      'template' => 'custom/templates/cyco-inserted-exercise',
      // Default variable values
      'variables' => array(
        'title' => '(no title)',
        'body' => '(MT)',
        'labeled_links' => array(),
        'too_bad_so_sad_message' => '',
      ),
    ),
    'cyco_feedback_phrases' => array(
      'template' => 'custom/templates/cyco-feedback-phrase-preview',
      'variables' => array(
        'phrases_groups' => array(),
      )
    ),
    'cyco_exercises_model_solutions' => array(
      'template' => 'custom/templates/cyco-exercises-model-solutions',
      'variables' => array(
        'exer_nid' => NULL,
        'models' => array(),
      )
    )
  );
  return $result;
}

/**
 * Return the theme to use for popup windows, by inspecting the 
 * destination.
 */
function cyco_exercises_custom_theme() {
  if (_cyco_exercises_is_submission_page_in_popup() ) {
    return _cyco_exercises_get_submission_theme();
  }
}

/**
 * Remind user to set timezone.
 */
function cyco_exercises_page_alter(&$page) {
  global $user;
  if ( $user->uid > 0 ) {
    if ( ! _cyco_exercises_is_submission_page_in_popup() ) {
      global $user;
      if (!$user->timezone) {
        drupal_add_js(
            drupal_get_path('module', 'cyco_exercises')
            . '/custom/js/jstz.min.js'
        );
        drupal_add_js(
            drupal_get_path('module', 'cyco_exercises')
            . '/custom/js/cyco_exercises_guess_time_zone.js'
        );
        drupal_set_message(
            t('<strong id="set-time-zone">Important!</strong> Please set '
                  . 'your <a href="@user-edit">account time zone '
                  . 'setting</a>. <br><br>If you do not, then exercise submission '
                  . 'and other times may not be accurate.', 
                array(
                  '@user-edit' => 
                      url(
                          "user/$user->uid/edit",
                          array( 'fragment' => 'edit-timezone')
                      )
                )
            )
        );
      }
    }
  }
}

/**
 * Return true if the current page is an exercise submission shown in a popup.
 */
function _cyco_exercises_is_submission_page_in_popup() {
  static $is_submission_popup = FALSE;
  if ( !$is_submission_popup ) {
    //Is the page in a popup?
    if ((    isset($_GET['destination']) 
          && $_GET['destination'] == 'cyco-exercises-close-popup' ) ) {
      $is_submission_popup = TRUE;
    }
  }
  return $is_submission_popup;
  
}

/**
 * Get the machine name of the theme to use for the exercise submission form.
 * 
 * @global string $theme Machine name of current default theme.
 * 
 * @return string Machine theme name.
 */
function _cyco_exercises_get_submission_theme() {
  $theme_to_use = variable_get('cyco_exercises_submission_theme', 'default');
  if ( $theme_to_use == 'default' ) {
    //Grab the current default theme.
    global $theme;
    $theme_to_use = $theme;
  }
  return $theme_to_use;
}

/**
 * Implements hook_node_view().
 * 
 * If the user can edit course pages, then add the id of the exercise
 * to the end of the title. Helps when inserting exercise 
 * references in a course page.
 * 
 * Also does some token replacement.
 */
function cyco_exercises_node_view($node, $view_mode, $langcode) {
  if ($node->type == 'exercise' && $view_mode == 'full') {
    if ( user_access('edit any course_page content') ) {
      drupal_set_title($node->title . ' (' . $node->nid . ')');
    }
  }
}

/**
 * Implements hook_form_alter().
 * 
 * Hide the rubric items field, and add the replacement UI.
 * Add info on model solutions.
 */
function cyco_exercises_form_exercise_node_form_alter(&$form, $form_state) {
  $form['#submit'][] = '_cyco_exercises_form_submit';
  //Hide the standard field for rubric item creation.
  $form['field_rubric_items']['#type'] = 'hidden';
  //Pass nids of current rubric items to client in a hidden form field.
  $rubric_items = array();
  if (isset($form_state['node']->field_rubric_items[LANGUAGE_NONE])) {
    foreach ($form_state['node']->field_rubric_items[LANGUAGE_NONE] as $key => $value) {
      $rubric_items[] = intval($value['target_id']);
    }
  }
  $form['cyco_current_items'] = array(
    '#type' => 'hidden',
    '#value' => json_encode($rubric_items),
  );
  //Load the client UI stuff.
  drupal_add_library('system', 'ui.dialog');
  //Load Fancytree.
  $library_info = libraries_load('fancytree');
  $numFilesLoaded = libraries_load_files($library_info);
  if ($numFilesLoaded <= 0) {
    $mess = t('Error: no Fancytree files loaded. Is Fancytree installed?');
    watchdog('cyco_exercises', $mess);
    services_error($mess, 666);
  }
  //Add JS and CSS for the UI.
  drupal_add_js(
      drupal_get_path('module', 'cyco_exercises')
      . '/custom/js/cyco_exercises_select_rubrics_ui.js'
  );
  drupal_add_css(
      drupal_get_path('module', 'cyco_exercises')
      . '/custom/css/cyco_exercises_select_rubrics_ui.css'
  );
  drupal_add_js(
      drupal_get_path('module', 'cyco_exercises')
      . '/custom/js/cyco_exercises_create_rubric_ui.js'
  );
  drupal_add_css(
      drupal_get_path('module', 'cyco_exercises')
      . '/custom/css/cyco_exercises_create_rubric_ui.css'
  );
  //Grab HTML for UI from a template.
  $ui_html = theme('select_rubric_item');
  $form['ui_html'] = array(
    '#type' => 'markup',
    '#markup' => $ui_html,
    '#weight' => $form['field_rubric_items']['#weight'],
  );
  //Model solutions.
  //When creating an exercise, there is no nid.
  if ( isset( $form['#entity']->nid ) ) {
    $exer_nid = $form['#entity']->nid;
    $models = array();
    $models_efq = new EntityFieldQuery;
    $models_efq
      ->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'model_exercise_solution')
      ->propertyCondition('status', 1)
      ->fieldCondition('field_exercise_solved', 'target_id', $exer_nid)
      ->propertyOrderBy('title');
    $query_result = $models_efq->execute();
    if ( isset( $query_result['node'] ) ) {
      //Create the HTML.
      foreach ( $query_result['node'] as $nid => $ignore ) {
        $node = node_load( $nid );
        $models[$nid] = $node->title;
      }
    }
    $models_html = theme(
        'cyco_exercises_model_solutions', 
        array(
          'exer_nid' => $exer_nid,
          'models' => $models,
        ) 
    );
    $form['models'] = array(
      '#type' => 'markup',
      '#markup' => $models_html,
      '#weight' => $form['field_rubric_items']['#weight'],
    );
  }
}

function _cyco_exercises_form_submit($form, &$form_state) {
//  $form_state['values']['field_rubric_items'][LANGUAGE_NONE][0]['target_id'] = $nid;
//  $form_state['values']['field_rubric_items'][LANGUAGE_NONE][1]['target_id'] = $nid;
  $linked_items = $_POST['cyco_current_items'];
  $linked_items = json_decode($linked_items);
  $form_state['values']['field_rubric_items'][LANGUAGE_NONE] = array();
  foreach ($linked_items as $key => $nid) {
    $form_state['values']['field_rubric_items'][LANGUAGE_NONE][$key]['target_id'] = $nid;
  }
}


function cyco_exercises_form_course_page_node_form_alter(&$form, $form_state) {
  //Hide the exercise field. 
  if ( ! cyco_core_current_user_has_role('administrator') ) {
    $form['field_exercises']['#access'] = FALSE;
  }
  $form['#submit'][] = '_cyco_exercises_store_exercise_refs';
}

/**
 * Store references to exercises in the course page.
 */
function _cyco_exercises_store_exercise_refs($form, &$form_state) {
  $matches = array();
  $body_content = 
      $form_state['values']['field_body'][LANGUAGE_NONE][0]['value'];
  preg_match_all(
      '/\.\.\s+exercise\:\:\s+(\d+)/i', 
      $body_content,
      $matches
  );
  if ( sizeof( $matches ) > 0 ) {
    $form_state['values']['field_exercises'][LANGUAGE_NONE] = array();
    foreach ( $matches[1] as $index => $exercise_nid ) {
      $form_state['values']['field_exercises'][LANGUAGE_NONE][$index]
          = array('target_id' => $exercise_nid);
    }
  }
}

/**
 * Implements hook_libraries_info().
 * 
 * Define Fancytree in the libraries.
 */
function cyco_exercises_libraries_info() {
  $libraries = array();
  $libraries['fancytree'] = array(
    'name' => 'Fancytree',
    'vendor url' => 'https://github.com/mar10/fancytree',
    'download url' => 'https://github.com/mar10/fancytree',
    'path' => 'dist',
    'version arguments' => array(
      'file' => 'package.json',
      'pattern' => '/\"version\"\:\s*\"(.*)\"/',
      'lines' => 10,
    ),
    'files' => array(
      'js' => array(
        'jquery.fancytree-all.js',
      ),
      'css' => array(
        'skin-win8/ui.fancytree.min.css',
      )
    ),
  );
  return $libraries;
}


/**
 * Implements hook_form_alter() for exercise submission form.
 * 
 * If form is opened from "Work on it" link, add some stuff.
 */
function cyco_exercises_form_exercise_submission_node_form_alter(&$form, $form_state) {
  $parsed_url = drupal_parse_url( $form['#action'] );
    // Use $form['#action'] value, because $_GET not set correctly when 
    // uploading a file for a new submission.
  // Get operation from the URL.
  $operation = NULL;
  if ( isset( $parsed_url['query']['op'] ) ) {
    $operation = $parsed_url['query']['op'];
  }
  // If there is no op, this is a normal edit, not through a popup. 
  // Don't need to do any of the other processing here.
  if (is_null($operation) ) {
    return;
  }
  global $base_url;
  drupal_add_js(
      $base_url . '/' . drupal_get_path('module', 'cyco_exercises')
      . '/custom/js/cyco_exercises_prep_submission_form.js'
  );
  // Flag - has this been submitted?
  $has_been_submitted = FALSE;
  $language = $form['#entity']->language;
  // Compute exerice nid and version.
  if ( $operation == 'add' ) {
    // Compute the exercise id.
    if ( ! isset( $parsed_url['query']['field_exercise'] ) ) {
      $message = __FILE__ . ' (line ' . __LINE__ . ') ' . __FUNCTION__ 
          . ' exercise id not passed for add';
      cyco_core_handle_error( $message );
      return;
     }
    $exercise_id = $parsed_url['query']['field_exercise'];
    if ( is_nan($exercise_id) || $exercise_id < 1 ) {
      // Bad version.
      $message = __FILE__ . ' (line ' . __LINE__ . ') ' . __FUNCTION__ 
          . ' bad exercise_id: ' . $exercise_id;
      cyco_core_handle_error( $message );
      return;
    }
    //Save the exercise id in the form.
    $form['field_exercise'][$language]['#default_value'][0] = $exercise_id;
    //Version is 1, unless there is a value in the URL.
    $version = 1;
    if ( isset( $parsed_url['query']['version'] ) ) {
      $version = $parsed_url['query']['version'];
      if ( is_nan($version) || $version < 1 ) {
        // Bad version.
        $message = __FILE__ . ' (line ' . __LINE__ . ') ' . __FUNCTION__ 
            . ' bad version: ' . $version;
        cyco_core_handle_error( $message );
        return;
      }
    }
    $form['field_version'][$language][0]['value']['#default_value'] = $version;
  }
  elseif( $operation == 'edit' ) {
    $exercise_id = $form['field_exercise'][$language]['#default_value'][0];
    $version = $form['field_version'][$language][0]['value']['#default_value'];
  }
  else {
    // Bad operation.
    $message = __FILE__ . ' (line ' . __LINE__ . ') ' . __FUNCTION__ 
        . ' unknown operation: ' + $op;
    cyco_core_handle_error( $message );
    return;
  }
  $form['title']['#access'] = FALSE;
  
  //Hide the exercise field.
  $form['field_exercise']['#access'] = false;
  //Hide the version field.
  $form['field_version']['#access'] = false;
  //Send exercise id to JS.
  drupal_add_js(
      array('cyco_exercises' => 
        array(
          'exerciseNid' => $exercise_id,
        ),
      ),
      'setting'
  );
  // Show version number if > 1.
  if ( $version >= 1 ) {
    $form['version_display'] = array(
      '#type' => 'markup',
      '#markup' => 'Version ' . $version,
      '#weight' => $form['field_version']['#weight'],
      '#prefix' => '<div class="cyco-submission-version">',
      '#suffix' => '</div>',
    );
  }
  // Kill preview if showing.
  if ( isset( $form['actions']['preview'] ) ) {
    unset( $form['actions']['preview'] );
  }
  // Kill delete if showing.
  if ( isset( $form['actions']['delete'] ) ) {
    unset( $form['actions']['delete'] );
  }
  unset( $form['additional_settings'] );
  // Change the rest of the form, depending on the operation.
  if ( $operation == 'add' ) {
    // Adding a new submission.
    $form['field_when_submitted']['#access'] = FALSE;
    unset( $form['field_when_feedback_given'] );
    unset( $form['field_feedback_source'] );
    unset( $form['field_feedback'] );
    unset( $form['field_conversation'] );
    unset( $form['field_rubric_item_ratings'] );
    unset( $form['field_complete'] );
  }
  elseif ( $operation == 'edit' ) {
    //Show the when submitted field if there is something there.
    if ( isset( $form['field_when_submitted'][$language][0]['#default_value']['value'] ) ) {
      $has_been_submitted = TRUE;
      $when = $form['field_when_submitted'][$language][0]['#default_value'];
      $form['field_when_submitted_display'] = array(
        '#type' => '#markup',
        '#markup' => 'Submitted: ' 
            . cyco_core_utc_to_user_time_zone( $when['value'] ),
      );
      if ( isset( $form['field_when_submitted']['#weight'] ) ) {
        $form['field_when_submitted_display']['#weight'] = 
            $form['field_when_submitted']['#weight'];
      }
    }
    $form['field_when_submitted']['#access'] = FALSE;
    //Unset other things.
    unset( $form['field_when_feedback_given'] );
    unset( $form['field_feedback_source'] );
    unset( $form['field_feedback'] );
    unset( $form['field_conversation'] );
    unset( $form['field_rubric_item_ratings'] );
    unset( $form['field_complete'] );    
  }
  //Add Submit checkbox.
  $submit_button_weight = $form['actions']['submit']['#weight'];
  $form['submit_solution'] = array(
    '#type' => 'checkbox',
    '#title' => 'Submit for feedback',
    '#default_value' => $has_been_submitted,
    '#weight' => $submit_button_weight,
  );
  $form['actions']['submit']['#weight']++;
  //Add feedback reminder element for JS to use.
  $reminder = theme(
        'cyco_reminder', 
        array(
          'reminder' => t('Check Submit when your solution is ready. '
              . 'Graders only see submitted solutions.'),
          'hide_at_start' => TRUE,
        )
    );
  $form['reminder'] = array(
    '#type' => 'markup',
    '#markup' => $reminder,
    '#weight' => $submit_button_weight + 1,
  );
  $form['actions']['submit']['#weight']++;
  //Set the page title.
  $exercise_node = node_load( $exercise_id );
  drupal_set_title( $exercise_node->title );
  //Add validation processor.
  $form['#validate'][] = '_cyco_exercises_submission_form_validate';
  //Add submission processor.
  $form['#submit'][] = '_cyco_exercises_submission_form_submission';
  
  //Check whether this is a new-window submission.
  if (_cyco_exercises_is_submission_page_in_popup() ) {
    //Aye.
    module_invoke('admin_menu', 'suppress');
  }
}

/**
 * Validate exercise submission form. Make sure that there is content.
 * @param type $form You know what it is.
 * @param type $form_state You know what it is.
 */
function _cyco_exercises_submission_form_validate($form, &$form_state) {
  $content_given = FALSE;
  $language = $form_state['node']->language;
  //Check the solution text.
  if ( isset( $form_state['values']['field_solution'][ $language ][0]['value'] ) ) {
    $value = $form_state['values']['field_solution'][ $language ][0]['value'];
    if ( strlen(trim($value)) > 0 ) {
      $content_given = TRUE;
    }
  }
  if ( ! $content_given ) {
    //Check the attached files.
    if ( isset( $form_state['values']['field_attachments'][ $language ][0]['fid'] ) ) {
      $fid = $form_state['values']['field_attachments'][ $language ][0]['fid'];
      if ( $fid > 0 ) {
        $content_given = TRUE;
      }
    }
  }
  if ( ! $content_given ) {
    form_set_error( 'field_solution', 
        t('Sorry, you must give a solution and/or attachment before saving.')
    );
  }
}

/**
 * Exercise submission form has been submitted.
 * 
 * @param type $form
 * @param type $form_state
 */
function _cyco_exercises_submission_form_submission($form, &$form_state) {
  // Record whether it has been submitted.
  $submit_checked = ($form_state['values']['submit_solution'] == 1);
  if ( $submit_checked ) {
      //Record current date/time as the submission date/time.
      $now = cyco_core_get_now_utc();
      $form_state['values']['field_when_submitted'][LANGUAGE_NONE][0] = $now;
  }
  else {
    // Submit not checked.
    if ( ! isset($form_state['values']['field_when_submitted'][LANGUAGE_NONE][0]['value'] ) ) {
      // Nothing to change.
    }
    else {
      // There is a date. Clear it.
      $form_state['values']['field_when_submitted'][LANGUAGE_NONE][0] = '';
    }
  }
  // Set the submission title.
  $language = $form_state['node']->language;
  $exercise_nid = intval( 
      $form_state['values']['field_exercise'][ $language ][0]['target_id']
  );
  $exercise = node_load( $exercise_nid );
  $exercise_title = $exercise->title;
  $version = $form_state['values']['field_version'][ $language ][0]['value']; 
  global $user;
  $user_data = user_load($user->uid);
  $user_language = $user_data->language ? $user_data->language : LANGUAGE_NONE;
  $first_name = $user_data->field_first_name[ $user_language ][0]['value'];
  $last_name = $user_data->field_last_name[ $user_language ][0]['value'];
  $full_name = $user->name;
  if ( $first_name || $last_name ) {
    $full_name .= ' (' 
        . $first_name 
        . ($first_name ? ' ' : '') 
        . $last_name . ')';
  }
  $title = 'Sub by ' . $full_name . ' for ' . $exercise_title 
      . ' (ver ' . $version . ')';
  $form_state['values']['title'] = $title;
}

/**
 * Get the submissions ready to grade.
 * 
 * @global stdClass $user Current user object.
 * 
 * @param int $uid Grader UID, defaults to current user.
 * @return array Submission info.
 */
function cyco_exercises_get_submissions_to_grade($uid = NULL) {
  if ( is_null($uid) ) {
    global $user;
    $uid = $user->uid;
  }
  // Get the id of the grader group role.
  $query = db_select('og_role')
    ->fields('og_role', array('rid'))
    ->condition('group_type', 'node')
    ->condition('group_bundle', 'class')
    ->condition('name', 'grader');
  $grader_role_id = $query->execute()->fetchField();
  // Get the groups the user is a grader in.
  $query = db_select('og_membership', 'ogm');
  $query->fields('ogm', array('id', 'gid', 'group_type'))
    ->condition('entity_type', 'user')
    ->condition('etid', $uid)
    ->innerJoin('og_users_roles', 'usersroles', 
        'usersroles.uid = ' . $uid . ' and ogm.gid = usersroles.gid');
  $query->condition('usersroles.rid', $grader_role_id);
  $records = $query
    ->execute()
    ->fetchAll();
  $gids = array();
  foreach ( $records as $record ) {
    $gids[] = $record->gid;
  }
  // Is the user a grader in any group?
  if ( sizeof($gids) == 0 ) {
    return;
  }
  // Get the names of those groups.
  $groups = cyco_core_groups_get_group_names($gids);
  // Get all the members of those groups.
  $query = db_select('og_membership', 'ogm');
  $query
      ->distinct()
      ->fields( 'ogm', array('gid', 'etid') )
      ->condition('entity_type', 'user')
      ->condition('gid', $gids, 'IN');
  $records = $query->execute()->fetchAll();
  // Array of uids to be imploded to use in SQL INI.
  $users_in_groups = array();
  // Track the groups a user is in.
  $groups_users_are_in = array();
  foreach ( $records as $record ) {
    $gid = $record->gid;
    $etid = $record->etid;
    // Add to array of all members in all groups.
    $users_in_groups[] = $etid;
    // Track groups for each individual member.
    if ( ! isset( $groups_users_are_in[ $etid ] ) ) {
      $groups_users_are_in[ $etid ] = array();
    }
    $groups_users_are_in[ $etid ][] = $gid;
  }
  // Get the submissions for those users that have a submission date, but
  // no feedback date.
  $sql = "
select 
  submission_node.nid as submission_nid,
  submission_node.uid as submitter_uid,
  users.name as username,
  lastname_table.field_last_name_value as last_name,
  firstname_table.field_first_name_value as first_name,
  version_table.field_version_value as submission_version,
  when_submitted_table.field_when_submitted_value as when_submitted,
  when_feedback_table.field_when_feedback_given_value as when_feedback_given,
  exercise_node.nid as exercise_nid,
  exercise_node.title as exercise_title
from {node} as submission_node
/* Grad submitter's username. */
inner join {users} on
  users.uid = submission_node.uid
/* Grab the submitter's last name. */
left join {field_data_field_last_name} as lastname_table on 
  lastname_table.entity_id = submission_node.uid
/* Grab the submitter's first name. */
left join {field_data_field_first_name} as firstname_table on 
  firstname_table.entity_id = submission_node.uid
/* Grab the exericse title. */
inner join {field_data_field_exercise} as exercise_ref_table on 
  exercise_ref_table.entity_id = submission_node.nid
inner join {node} as exercise_node on 
  exercise_ref_table.field_exercise_target_id = exercise_node.nid
/* Grab the submission version. */
inner join {field_data_field_version} as version_table on 
  version_table.entity_id = submission_node.nid
/* Grab the date submitted for grading. */
inner join {field_data_field_when_submitted} as when_submitted_table on 
  when_submitted_table.entity_id = submission_node.nid
/* Grab the feedback date. */
left join {field_data_field_when_feedback_given} as when_feedback_table on 
  when_feedback_table.entity_id = submission_node.nid
where
  submission_node.type = 'exercise_submission'
  and submission_node.uid in (" . implode( ',', $users_in_groups ) . ")
  and when_submitted_table.field_when_submitted_value is not null
  and when_feedback_table.field_when_feedback_given_value is null
order by when_submitted_table.field_when_submitted_value asc;
";
  $records = db_query($sql);
  $submissions = array();
  if ( $records ) {
    while ( $row = $records->fetchAssoc() ) {
      $display_name = '';
      if ( isset( $first_name ) ) {
        $display_name = $row['first_name'];
      }
      if ( isset( $last_name ) ) {
        $display_name .= $row['last_name'];
      }
      if ( $display_name == '' ) {
        $display_name = $row['username'];
      }
      else {
        $display_name .= ' (' . $row['username'] . ')';
      }
      $row['display_name'] = $display_name;
      $submissions[] = $row;
    }
  }
  // Only pass group membership info for students with submissions.
  $memberships = array();
  
  foreach ( $submissions as $index => $submission ) {
    $submitter_uid = $submission['submitter_uid'];
    $memberships[ $submitter_uid ] = $groups_users_are_in[ $submitter_uid ];
    // When-submitted comes out in UTC. Convert to user time zone.
    $when_submitted = strtotime( $submission['when_submitted'] . ' UTC' );
    $interval = format_interval(
        time() - $when_submitted
    );
    $submissions[ $index ]['when_submitted'] = $interval . ' ago';
  }
  $result = array( 
    'submissions' => $submissions,
    'groups' => $groups,
    'memberships' => $memberships,
  );
  return $result;
}

/**
 * Find the number of submissions waiting for a grader.
 * @param int $uid Grader UID, defaults to current user.
 * @return int Number of submissions waiting.
 */
function cyco_exercises_get_number_submissions_to_grade($uid = NULL) {
  $submissions_data = cyco_exercises_get_submissions_to_grade($uid);
  $submissions = $submissions_data['submissions'];
  return sizeof($submissions);
}

/**
 * Implements hook_form_alter().
 * 
 * Change the user profile form, adjusting grading things.
 * Call JS time zone guesser.
 */
function cyco_exercises_form_user_profile_form_alter( &$form, $form_state ) {
  //Get the uid of the user who is the subject of this form.
  $subject_uid = $form['#entity']->uid;
  $subject = user_load($subject_uid);
  if (cyco_core_user_has_role( $subject, 'grader' ) ) {
//    $form['#validate'][] = '_cyco_exercises_user_profile_form_validate';
    $form['#submit'][] = '_cyco_exercises_user_profile_form_submit';
    //Insert the token display.
    $form['tokens'] = array(
      '#type' => 'fieldset',
      '#title' => t('Tokens'),
      '#description' => 
          t('Text like [feedback:student_first_name] are replaced with '
            . 'values like Sara or Mike when content is displayed. '
            . 'See the CyberCourse wiki for more information.'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#weight' => 8,
    );
    $form['tokens']['list'] = array(
      '#theme' => 'token_tree',
      '#token_types' => array('all'),
      '#global_types' => TRUE,
      '#click_insert' => FALSE,
    );
  }
  else {
    //Not a grader. Hide all thoe fields.
    field_group_hide_field_groups($form, array('group_feedback_phrases'));
  }
}

/**
 * Validate the user profile form.
 */
//function _cyco_exercises_user_profile_form_validate( $form, &$form_state ) {
//}

/**
 * Structure data needed to make a preview of a group of 
 * feedback phrases for the user.
 * @param array $form_state From form_submit.
 * @param string $field_name Name of the field to check.
 * @param string $group Title of the group.
 * @return array Data structured appropriately.
 */
function _cyco_structure_feedback_phrases_preview_data( $form_state, $field_name, $group ) {
  $result = array();
  if ( $form_state['values'][$field_name][LANGUAGE_NONE][0]['value'] ) {
    $result['group_title'] = $group;
    $phrases = array();
    foreach ( 
        $form_state['values'][$field_name][LANGUAGE_NONE] as $key => $entry ) {
      if ( $entry['value'] ) {
        $phrases[] = token_replace( $entry['value'] );
      }
    }
    $result['phrases'] = $phrases;
  }
  return $result;
}

function _cyco_exercises_user_profile_form_submit( $form, &$form_state ) {
  // Check the cutoff percentages.
  $good_cutoff = NULL;
  if ( $form_state['values']['field_good_cutoff'][LANGUAGE_NONE][0]['value'] ) {
    $good_cutoff = $form_state['values']['field_good_cutoff'][LANGUAGE_NONE][0]['value'];
  }
  $needs_work_cutoff = NULL;
  if ( $form_state['values']['field_needs_work_cutoff'][LANGUAGE_NONE][0]['value'] ) {
    $needs_work_cutoff = $form_state['values']['field_good_cutoff'][LANGUAGE_NONE][0]['value'];
  }
  if ( ! $good_cutoff || ! $needs_work_cutoff ) {
    drupal_set_message(
          'Note: both "good" cutoff and "needs work" cutoff need to '
        . 'be set before either will be used.');
  }
  else {
    if ( $good_cutoff <= $needs_work_cutoff ) {
      form_set_error(
          'field_good_cutoff', 
          'The "good" cutoff should be greater than the "needs work" cutoff.'
      );
    }
  }
  //Show the user samples of feedback messages with name replacements, so
  // s/he can check them.
  $phrases_groups = array();
  if ( $form_state['values']['field_greetings'][LANGUAGE_NONE][0]['value'] ) {
      $phrases_groups[] = _cyco_structure_feedback_phrases_preview_data( 
          $form_state, 'field_greetings', 'Greetings' 
        );
  }
  if ( $form_state['values']['field_overall_good'][LANGUAGE_NONE][0]['value'] ) {
      $phrases_groups[] = _cyco_structure_feedback_phrases_preview_data( 
          $form_state, 'field_overall_good', 'Overall good' 
        );
  }
  if ( $form_state['values']['field_overall_needs_work'][LANGUAGE_NONE][0]['value'] ) {
      $phrases_groups[] = _cyco_structure_feedback_phrases_preview_data( 
          $form_state, 'field_overall_needs_work', 'Overall needs work' 
        );
  }
  if ( $form_state['values']['field_overall_poor'][LANGUAGE_NONE][0]['value'] ) {
      $phrases_groups[] = _cyco_structure_feedback_phrases_preview_data( 
          $form_state, 'field_overall_poor', 'Overall poor' 
        );
  }
  if ( $form_state['values']['field_signature'][LANGUAGE_NONE][0]['value'] ) {
      $phrases_groups[] = _cyco_structure_feedback_phrases_preview_data( 
          $form_state, 'field_signature', 'Signature' 
        );
  }
  if ( sizeof( $phrases_groups > 0 ) ) {
    drupal_set_message( 
        theme(
            'cyco_feedback_phrases', 
            array( 'phrases_groups' => $phrases_groups)
        )
    );
  }
}

/**
 * Implements hook_token_info().
 */
function cyco_exercises_token_info() {
  $info = array(
    'types' => array(
      'feedback' => array(
        'name' => t('Feedback system tokens'),
        'description' => t('Used in the grading UI'),
      ),
    ),
    'tokens' => array(
      'feedback' => array(
        'student_first_name' => array(
          'name' => t('Student first name'),
          'description' => t('First name of the student receiving feedback.'),
        ),
        'student_last_name' => array(
          'name' => t('Student last name'),
          'description' => t('Last name of the student receiving feedback.'),
        ),
        'exercise_title' => array(
          'name' => t('Exercise title'),
          'description' => t('Title of the exercise being assessed.'),
        ),
      ),
    ),
  );
  return $info;
}

/**
 * Implements hook_tokens().
 */
function cyco_exercises_tokens($type, $tokens, array $data = array(), 
    array $options = array()) {
  //Default names depend on which page we are on. 
  global $user;
  $on_user_account_page = ( current_path() == 'user/' . $user->uid . '/edit' );
  $replacements = array();
  // The first thing that we're going to check for is the type of token - node,
  // user etc...
  if ($type == 'feedback') {
    // Loop through each of the available tokens.
    foreach ($tokens as $name => $original) {
      // Find the desired token by name.
      switch ($name) {
        case 'student_first_name':
          //Replace with the student's first name if the current user
          //has the student role, else use a generic name. 
          $first_name = $on_user_account_page ? 'Willow' : 'you'; //Default name.
          if ( 
                 isset( $data['context'] ) 
              && $data['context'] == 'creating_feedback_message' 
             ) {
            $student_uid = $data['student_uid'];
            $users = entity_load('user', array( $student_uid ) );
            $student_all_data = $users[ $student_uid ];
            if ( cyco_core_user_has_role( $student_all_data, 'student' ) ) {
              if ( isset( $student_all_data->field_first_name[LANGUAGE_NONE][0] ) ) {
                $first_name = $student_all_data->field_first_name[LANGUAGE_NONE][0]['value'];
              }
            }
             }
          // Add the new value into the replacements array.
          $replacements[$original] = $first_name;
          break;
        case 'student_last_name':
          //Replace with the student's last name if the current user
          //has the student role, else use a generic name.
          if ( $on_user_account_page ) {
            $last_name = 'Rosenberg';
          }
          else {
            $names = array(
              'rock star', 
              'student of life\'s mysteries', 
              'young whippersnapper', 
              'wanderer', 
              'worshipper', 
              'lover of leaving', 
            );
            $last_name = $names[ array_rand($names) ];
          }
          if ( cyco_core_current_user_has_role( 'student' ) ) {
            global $user;
            $users = entity_load('user', array($user->uid) );
            $user_all_data = $users[ $user->uid ];
            if ( isset( $user_all_data->field_last_name[LANGUAGE_NONE][0] ) ) {
              $last_name = $user_all_data->field_last_name[LANGUAGE_NONE][0]['value'];
            }
          }
          // Add the new value into the replacements array.
          $replacements[$original] = $last_name;
          break;
        case 'exercise_title':
          //Replace with an exercise's title if available, else 
          //use a generic title. 
          $exercise_title = 'Generic exercise title'; //Default name.
          if ( isset( $data['exercise_nid'] ) ) {
            $exercise = node_load( $data['exercise_nid'] );
            $exercise_title = $exercise->title;
          }
          // Add the new value into the replacements array.
          $replacements[$original] = $exercise_title;
          break;
      }
    }
  } //End processing feedback type.
  elseif ($type == 'current-user') {
    // Loop through each of the available tokens.
    foreach ($tokens as $name => $original) {
      // Find the desired token by name.
      switch ($name) {
        case 'field_first_name':
        case 'field-first-name':
          //Replace with a generic name for anonymous users, or
          //where the user did not give a first name.
          global $user;
          if ( $user->uid == 0 ) {
            $replacements[$original] = GENERIC_FIRST_NAME;
          }
          else {
            $users = entity_load('user', array($user->uid) );
            $user_all_data = $users[ $user->uid ];
            if ( _cyco_test_use_generic_name( $user_all_data->field_first_name ) ) {
              //Use the generic name.
              $replacements[$original] = GENERIC_FIRST_NAME;
            }
          }
          break;
        case 'field_last_name':
        case 'field-last-name':
          //Replace with a generic name for anonymous users, or
          //where the user did not give a last name.
          global $user;
          if ( $user->uid == 0 ) {
            $replacements[$original] = GENERIC_LAST_NAME;
          }
          else {
            $users = entity_load('user', array($user->uid) );
            $user_all_data = $users[ $user->uid ];
            if ( _cyco_test_use_generic_name( $user_all_data->field_last_name ) ) {
              //Use the generic name.
              $replacements[$original] = GENERIC_LAST_NAME;
            }
          }
          break;
      }
    } //End foreach
  }
  // Return the replacements.
  return $replacements;
}

/**
 * Test whether need to replace first/last name tokens with
 * a generic value.
 * @global stdClass $user The logged in user.
 * @param string $field_to_check Name of the user entity field that might
 * have a value for a name.
 * @return boolean True if the generic name should be used.
 */
function _cyco_test_use_generic_name( $field_to_check ) {
  //Replace with a generic name for anonymous users, or
  //where the user did not give a last name.
  $replace_flag = FALSE;
  if ( ! isset( $field_to_check[LANGUAGE_NONE][0]['value'] ) ) {
      $replace_flag = TRUE;
  }
  else {
    //Get the data in the field.
    $data = trim( $field_to_check[LANGUAGE_NONE][0]['value'] );
    if ( strlen($data) == 0 ) {
      $replace_flag = TRUE;
    }
  }
  return $replace_flag;
}

/**
 * Implements hook_views_api().
 */
function cyco_exercises_views_api_alter(&$vars) {
  if (isset($vars['cyco_exercises'])) {
    $vars['cyco_exercises']['path'] 
        = drupal_get_path('module', 'cyco_exercises') . '/custom/views';
  }
}

/**
 * Compute the status of a submission: 
 *  * Not submitted
 *  * Submitted, no feedback
 *  * Complete
 *  * Not complete
 * @param stdCkass $node Submission node
 * @return string Status
 */
function cyco_exercises_compute_submission_status( $node ) {
  $language = $node->language;
  if ( ! isset( $node->field_when_submitted[ $language ][0] ) ) {
    $status = t('Not submitted');
  }
  else {
    if ( ! isset( $node->field_when_feedback_given[ $language ][0] ) ) {
      $status = t('Submitted, no feedback');
    }
    else {
      if ( $node->field_complete[ $language ][0]['value'] == 1 ) {
        $status = t('Complete');
      }
      else {
        $status = t('Not complete');
      }
    }
  }
  return $status;
}


function cyco_exercises_preprocess_node(&$variables) {
  if ( $variables['type'] == 'exercise') {
    global $user;
    if (    $user->uid == 0
         || cyco_core_current_user_has_role( 'student' ) ) {
      $too_bad_so_sad_message = _cyco_exercises_make_submit_links();
      if ( $user->uid == 0 ) {
        $variables['content']['field_body'][0]['#markup'] 
            .= $too_bad_so_sad_message;
      }
      if ( cyco_core_current_user_has_role( 'student' ) ) {
        $variables['content']['field_body'][0]['#markup'] 
            .= '<div class="cyco-submission-links-container" '
               . 'data-nid="' . $variables['nid'] . '"></div>';
      }
    }
    
  }
  
}

/**
 * Implements hook_swim_markdown2html_TAG_alter
 * @param stdClass $args Content to translate
 */
function cyco_exercises_swim_markdown2html_exercise_alter( &$args ) {
  $exercise_nid = intval($args->args);
  $exercise_node = node_load($exercise_nid);
  //Make sure that this is the right type of node.
  if ($exercise_node == FALSE || !node_access('view', $exercise_node) || !$exercise_node->status || $exercise_node->type != 'exercise') {
    $message = t('Invalid exercise id: @id', array('@id' => $exercise_nid));
    drupal_set_message($message);
    watchdog('cyco_exercises', $message);
    return '<p>' . $message . '</p>';
  }
  //Make the submission links.
  global $user;
  $labeled_links = '';
  $too_bad_so_sad_message = '';
  if ( ! cyco_core_user_has_role($user, 'student') ) {
    $too_bad_so_sad_message = t('(If you were logged in as a student, '
        . 'you could submit an exercise solution, and get some feedback.)'
    );
  }
  else {
    //If there is no submission, there is only a link to create a new one.
    //If there is an existing submission:
    //  If there is no feedback yet, there is only an edit link.
    //  If there is feedback, there is a Review link, and a new version link.
    global $base_url;
    //Create submission links for this exercise.
    drupal_add_js(
        $base_url . '/' . drupal_get_path('module', 'cyco_exercises')
        . '/custom/js/cyco_exercises_submission_links.js'
    );
    //Send current user uid to client.
    drupal_add_js(
        array('cyco_exercises' => 
          array(
            'uid' => $user->uid,
          ),
        ),
        'setting'
    );
  }
  $body_content = swim_markdown2html(
      $exercise_node->field_body[LANGUAGE_NONE][0]['value']
  );
  $result = theme('cyco_embedded_exercise', array(
    'exercise_nid' => $exercise_nid,
    'title' => $exercise_node->title,
    'body' => $body_content,
    'labeled_links' => $labeled_links,
    'too_bad_so_sad_message' => $too_bad_so_sad_message,
  ));  
  $args->replacement_content = $result;
  $args->current_line ++;
}

