<?php

/* 
 * Utility functions
 */

/**
 * Check whether the current user has a role, or one of a set of roles.
 * @global stdClass $user Current user.
 * @param string or array $roles Role(s) to check for.
 * @return boolean True if the user has at least one of the roles.
 */
function cyco_base_user_has_role($user, $roles) {
  //Load the user to check, depending on the type of the first argument.
  if ( is_integer($user) ) {
    //It's a uid.
    $user = user_load($user);
    if ( ! $user ) {
      $message = __FILE__ . ' (line ' . __LINE__ . ') ' . __FUNCTION__ 
          . ' bad uid: ' . $user;
      cyco_base_handle_error( $message );
      return FALSE;
    }
  }
  else if ( is_object($user) ) {
    if ( ! isset( $user->roles) ) {
      $message = __FILE__ . ' (line ' . __LINE__ . ') ' . __FUNCTION__ 
          . ' bad user object: <pre>' . print_r($user, TRUE) . '</pre>';
      cyco_base_handle_error( $message );
      return FALSE;
    }
  }
  else {
    $message = __FILE__ . ' (line ' . __LINE__ . ') ' . __FUNCTION__ 
        . ' bad thing passed: <pre>' . print_r($user, TRUE) . '</pre>';
    cyco_base_handle_error( $message );
    return FALSE;
  }
  if ( is_array($roles) ) {
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
 * @global stdClass $user Current user.
 * @param string or array $roles Role(s) to check for.
 * @return boolean True if the user has at least one of the roles.
 */
function cyco_base_current_user_has_role($roles) {
  global $user;
  return cyco_base_user_has_role($user, $roles);
}

/**
 * Format a timestamp in ISO 8601, using the user's timezone, or a default
 * if not set.
 * @param type $timestamp Timestamp to format.
 * @return string Date/time in 8601, using user's timezone.
 */
function cyco_base_timestamp_to_iso6801( $timestamp ) {
  $result = format_date($timestamp, 'custom', 'c', date_default_timezone());
  return $result;
}

/**
 * Format date/time as needed by Date/Time field.
 * @param date $when Date/time to format. Defaults to now.
 * @return array Formatted date/time.
 */
function cyco_base_format_time( $when = NULL ) {
  //This is clunky.
  if ( is_null( $when ) ) {
    $when = date_now('UTC');
  }
  //Make an array with the rep used by the date api for form field 
  //in $form_state.
  $temp = array();
  //Date is almost OK. Replace space between date and time with a T.
  $temp['value'] = str_replace(' ', 'T', $when->date);
  $temp['value2'] = $temp['value'];
  $temp['show_todate'] = 0;
  $temp['timezone'] = $when->timezone;
  //Compute timezone offset.
  $phpNow = new DateTime( $temp['value'], new DateTimeZone($when->timezone) );
  $offset = $phpNow->getOffset();
  $temp['offset'] = $offset;
  $temp['offset2'] = $offset;
  return $temp;
}