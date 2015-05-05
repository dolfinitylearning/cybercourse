<?php
/**
 * @file
 * Show the last course page a user looked at. 
 */

function cyco_last_page_node_view($node, $view_mode, $langcode) {
  global $user;
  //Is the user looking at a course page?
  if ( $user->uid != 0 && $node->type == 'course_page' && $view_mode == 'full') {
    //Store nid as the last course page seen.
    $uid = $user->uid;
    $user_all_data = entity_load('user', array($uid) );
    $user_all_data = $user_all_data[ $uid ];
    $user_all_data->field_last_course_page_seen = 
        array( 
          LANGUAGE_NONE => array(
            0 => array(
              'value' =>$node->nid,
            )
          ) 
        );
    entity_save('user', $user_all_data);
  }
  //Front page? Show the last page seen.
  if ( drupal_is_front_page() ) {
    //Skip anon users.
    $uid = $user->uid;
    if ( $uid != 0 ) {
      $user_all_data = entity_load( 'user', array($uid) );
      $user_all_data = $user_all_data[ $uid ];
      //Is there a last page stored?
      if ( isset($user_all_data->field_last_course_page_seen[LANGUAGE_NONE][0]['value']) ) {
        //Get nid.
        $nid = $user_all_data->field_last_course_page_seen[LANGUAGE_NONE][0]['value'];
        $node = node_load($nid);
        if ( $node->status == 1 ) {
          drupal_set_message(
              t('The last course page you looked at was ')
              . l($node->title, base_path() . 'node/' . $nid) 
              . '.'
          );
        }
      }
    }
  }
}


/**
 * Implements hook_help().
 */
function cyco_last_page_help($path, $arg) {
  switch ($path) {
    case 'admin/help#last_page':
      $output = '';
      $output .= '<h3>' . t('About') . '</h3>';
      $output .= '<p>' . t(
          'Shows the user the last course page s/he looked at. '
        . 'Shows on the home page. '
        . 'Useful to pick up where s/he left off. '
      ) . '</p>';
      return $output;
  }
}
