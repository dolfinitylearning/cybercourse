<?php

/**
 * @file
 * Defines some CyCo utilities used by other modules.
 */

/**
 * Add client-side data for services.
 */
function _cyco_core_config_client_services() {
  global $base_url;
  $settings = array(
    'baseUrl' => $base_url,
  );
  drupal_add_js(
      array('cycoCoreServices' => $settings),
      'setting'
  );
}

/**
 * Handle a client-side error.
 * Most of the error handling is in another file. 
 * This function is here so the menu processor can handle it.
 * @param string $message The Bad Thing that happened.
 */
function cyco_core_client_error() {
  $message = t( $_GET['message'] );
  $message = 'Something bad happened on the client-side: ' . $message;
  static $error_handler = NULL;
  if ( is_null($error_handler) ) {
    $error_handler = new CyCoErrorHandler();
  }
  $error_handler->reportError($message, FALSE);
  drupal_json_output(
      array('status' => TRUE)
  );
}

/**
 * Called from hook_form_alter() in cyco_core_custom.
 * 
 * Add display of available tokens.
 */
function _cyco_core_utilities_form_alter(&$form, $form_state, $form_id) {
  // $form_id ends in _node_form.
  $pos = strpos( $form_id, '_node_form');
  if ( $pos === FALSE ) {
    return;
  }
  $content_type = substr($form_id, 0, $pos);
  // Get a list of content types supporting tokens.
  $types = cyco_core_content_types_supporting_tokens();
  if (in_array($content_type, $types) ) {
    // Compute the weight of the token display form element.
    // What element should the display follow?
    $element_to_follow = 'field_body';
    // Pattern uses a different field.
    if ( $form_id == 'pattern_node_form' ) {
        $element_to_follow = 'field_situation';
    }
    $token_display_weight = NULL;
    if ( isset( $form[$element_to_follow] ) ) {
      if ( isset( $form[$element_to_follow]['#weight'] ) ) {
        $token_display_weight = $form[$element_to_follow]['#weight'] + 1;
      }
    }
    if ( !is_null($token_display_weight) ) {
      // Increase weights of elements following the token display.
      foreach ($form as $key => $value) {
        if (substr($key, 0, 6) == 'field_') {
          if (isset( $value['#weight'] )) {
            $weight = $form[$key]['#weight'];
            if ($weight >= $token_display_weight) {
              $form[$key]['#weight'] = $weight + 1;
            }
          }
        } // End substr
      } // End foreach
      // Insert the token display.
      $form['tokens'] = array(
        '#type' => 'fieldset',
        '#title' => t('Tokens'),
        '#description' => 
            t('Text like [current-user:field_last_name] are replaced with '
              . 'values like Smith or Jones when content is displayed. '
              . 'See the ' . l(t('CyberCourse wiki'), 'https://wiki.cybercour.se')
              . ' for more information.'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
        '#weight' => $token_display_weight,
      );
      $form['tokens']['list'] = array(
        '#theme' => 'token_tree',
        '#token_types' => array('node'),
        '#global_types' => TRUE,
        '#click_insert' => FALSE,
      );
    } //End $token_display_weight is not null.
  } //End supported type.
}

/**
 * Return array of names of node types that support tokens.
 * 
 * @return array Node type names
 */
function cyco_core_content_types_supporting_tokens() {
  //No exer submission - students can't use tokens.
  $types = array(
    'exercise',
    'course_page',
    'blueprint_page',
    'site_page',
    'rubric_item',
    'pattern',
    'class',
    'group',
    'group_announcement'
  );
  return $types;
}

/**
 * Get the fields supporting tokens for a content type.
 * 
 * @param string $content_type Content type, e.g., exercise.
 * @return array Field supporting tokens.
 */
function cyco_core_fields_supporting_tokens($content_type) {
  $fields = array();
  if (in_array($content_type, cyco_core_content_types_supporting_tokens())) {
    if ($content_type == 'pattern') {
      $fields = array('field_situation', 'field_actions', 'field_body',);
    }
    else {
      $fields = array('field_body');
    }
  }
  return $fields;
}

/**
 * Implements hook_tokens_alter.
 * 
 * Process tokens that CyCo defines, like user first name.
 */
function cyco_core_tokens_alter( &$replacements, $context) {
  global $user;
  foreach ($replacements as $key => $value) {
    // Key has a value like [[thing:thang]].
    $token = str_replace('[', '', $key);
    $token = str_replace(']', '', $token);
    switch ($key) {
      case 'current-user:field_first_name':
      case 'current-user:field-first-name':
        // If user is not logged in, or did not give first name...
        if ( 
               $user->uid == 0 
            || ! isset($user->field_first_name[LANGUAGE_NONE][0]) 
           ) {
          $replacements[$key] = 'Jane';
        }
        break;
      case 'current-user:field_last_name':
      case 'current-user:field-last-name':
        // If user is not logged in, or did not give last name...
        if ( 
               $user->uid == 0 
            || ! isset($user->field_last_name[LANGUAGE_NONE][0]) 
           ) {
          $replacements[$key] = 'Doe';
        }
        break;
      case 'current-user:name':
        // If user is not logged in...
        if ($user->uid == 0) {
          $replacements[$key] = 'genericUser';
        }
        break;
    };
  }
}

/**
 * Implements hook_form_alter().
 * 
 * Change order of fields, to put picture in the right place.
 * 
 * Check stuff in the user profile form.
 */
function cyco_core_form_user_profile_form_alter(&$form, $form_state) {
  $form['field_first_name']['#weight'] = $form['field_last_name']['#weight'];
  $form['#validate'][] = '_cyco_core_user_profile_form_validate';
}

/**
 * Validate the user profile form.
 * 
 * Warn the user that his/her instructor might want first and last names.
 */
function _cyco_core_user_profile_form_validate($form, &$form_state) {
  if (cyco_core_current_user_has_role('student')) {
    // Check first and last name.
    if ( ! $form_state['values']['field_first_name'][LANGUAGE_NONE][0]['value'] ) {
      drupal_set_message( t(
          'You didn\'t give your first name. Your instructor might want you to.'
      ) );
    }
    if ( ! $form_state['values']['field_last_name'][LANGUAGE_NONE][0]['value'] ) {
      drupal_set_message( t(
          'You didn\'t give your last name. Your instructor might want you to.'
      ) );
    }
  }
}

/**
 * Implements hook_user_view().
 */
function cyco_core_user_view($account, $view_mode, $langcode) {
  //Slimy hack to show user's time zone, as a reminder.
  $timezone = isset( $account->timezone ) 
      ? $account->timezone
      : 'Not set - PLEASE SET IT!';
  $markup = '<p><strong>' . t('Time zone:') . '</strong><br>' 
      . $timezone . '</p>';
  $account->content['timezone'] = array(
    '#weight' => -1, //$account->content['field_about']['#weight'] + 1,
//    '#title' => t('Time zone'), //Dinna work.
    '0' => array( '#markup' => $markup ),
  );
}

/**
 * Check whether the current user has a role, or one of a set of roles.
 * 
 * @global stdClass $user Current user.
 * 
 * @param int or stdClass $user User id or object.
 * @param string or array $roles Role(s) to check for.
 * @return boolean True if the user has at least one of the roles.
 */
function cyco_core_user_has_role($user, $roles) {
  // Load the user to check, depending on the type of the first argument.
  if (is_integer($user)) {
    // It's a uid.
    $user = user_load($user);
    if ( ! $user ) {
      $message = __FILE__ . ' (line ' . __LINE__ . ') ' . __FUNCTION__
          . ' bad uid: ' . $user;
      cyco_core_handle_error($message);
      return FALSE;
    }
  }
  elseif (is_object($user)) {
    if ( !isset($user->roles)) {
      $message = __FILE__ . ' (line ' . __LINE__ . ') ' . __FUNCTION__
          . ' bad user object: <pre>' . print_r($user, TRUE) . '</pre>';
      cyco_core_handle_error($message);
      return FALSE;
    }
  }
  else {
    $message = __FILE__ . ' (line ' . __LINE__ . ') ' . __FUNCTION__
        . ' bad thing passed: <pre>' . print_r($user, TRUE) . '</pre>';
    cyco_core_handle_error($message);
    return FALSE;
  }
  if (is_array($roles)) {
    $check = array_intersect($roles, array_values($user->roles));
    $result = empty($check) ? FALSE : TRUE;
  }
  else {
    $result = in_array($roles, $user->roles);
  }
  return $result;
}

/**
 * Check whether the current user has a role, or one of a set of roles.
 * 
 * @global stdClass $user Current user.
 * 
 * @param string or array $roles Role(s) to check for.
 * @return boolean True if the user has at least one of the roles.
 */
function cyco_core_current_user_has_role($roles) {
  global $user;
  $access = cyco_core_user_has_role($user, $roles);
  return $access;
}

/**
 * Format a timestamp in ISO 8601, using the user's timezone, or a default
 * if not set.
 * 
 * @param type $timestamp Timestamp to format.
 * @return string Date/time in 8601, using user's timezone.
 */
function cyco_core_timestamp_to_iso6801($timestamp) {
  $result = format_date($timestamp, 'custom', 'c', date_default_timezone());
  return $result;
}

/**
 * Convert date/time from UTC to user's time zone.
 * 
 * @param string $utc Date/time in UTC, e.g., 1995-04-27 01:55:55
 * @return string Date/time in user's time zone.
 */
function cyco_core_utc_to_user_time_zone($utc) {
  $utc .= ' +0:00';
  $dt = new DateTime('@' . strtotime($utc));  // will snap to UTC because of the 
  $dt->setTimeZone(new DateTimeZone(drupal_get_user_timezone()));
  $user_tz = $dt->format('Y-m-d H:i:s');
  return $user_tz;
}

/** Get now in format for date field.
 * 
 * @return array Formatted date/time.
 */
function cyco_core_get_now_utc() {
  $when = strtotime('now');
  $date = array(
    'value' => format_date($when, 'custom', 'Y-m-d H:i:s', 'UTC'),
    'timezone' => 'UTC',  
    'timezone_db' => 'UTC',
  );
  return $date;
}

/**
 * Find the next line break in a string, whether it's \r\n, or \n.
 * 
 * @param string $string String to search.
 * @param int $start Where to start searching.
 * 
 * @return array Result array. 
 *   [0] = position (-1 if not found).
 *   [1] = EOL length (0 if not found, 1 if \n, 2 if \r\n). 
 */
function cyco_core_find_next_line_break($string, $start) {
  $pos = stripos($string, "\n", $start);
  if ($pos === FALSE) {
    return array(-1, 0);
  }
  if ($pos == 0) {
    return array(0, 1);
  }
  if (substr($string, $pos - 1, 1) == "\r") {
    return array($pos - 1, 2);
  }
  return array($pos, 1);
}

/**
 * Find the highest weight in a set of fields. Used in hook_node_view().
 * 
 * @param type $content_fields
 * @param type $fields_to_check
 * @return int Highest weight.
 */
function cyco_core_highest_content_weight( 
    $content_fields, $fields_to_check ) {
  $weight = 0;
  foreach ($fields_to_check as $field_name) {
    if ( isset( $content_fields[$field_name] ) ) {
      if ( $content_fields[$field_name]['#weight'] > $weight ) {
        $weight = $content_fields[$field_name]['#weight'];
      }
    }
  }
  return $weight;
}

/**
 * Is a node of a type that can be in a book?
 * 
 * @staticvar array $types List of types.
 * 
 * @param string/stdClass $node Node (stdClass) or content type (string)
 * 
 * @return boolean. True of this content type is normally in a book.
 */
function cyco_core_is_book_content_type($node) {
  static $types = array('course_page', 'blueprint_page', 'learning_map');
  if (isset($node->type)) {
    $type_to_test = $node->type; 
  }
  else {
    $type_to_test = $node;
  }
  return in_array($type_to_test, $types);
} 

/**
 * Get the content types that can be roots of books.
 * 
 * @return array Names of content types.
 */
function cyco_core_get_book_root_types() {
  return array('course_page', 'blueprint_page', 'learning_map');
}

/**
 * Convert a Drupal URI to a URL usable on the Web.
 * 
 * @param string $uri Drupal URI
 * @return string Usable URL
 */
function cyco_core_uri2path($uri) {
  $absolute_url = file_create_url($uri);
  $url = parse_url($absolute_url);
  $usable_url = $url['path'];
  return $usable_url;
}

/**
 * Get role id given the role name.
 * See http://drupal.stackexchange.com/questions/50435/how-do-i-find-the-role-id-from-role-name
 * 
 * @param string $name Role name.
 * @return int The rid.
 */
function cyco_core_get_role_id_by_name($name) {
  $roles = user_roles();
  return array_search($name, $roles);
}

