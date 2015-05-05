<?php
/**
 * @file
 * Tweak the node edit form.
 */

function cyco_last_page_node_view($node, $view_mode, $langcode) {
  global $user;
  //Is the user looking at a course page?
  if ( $user->uid != 0 && $node->type == 'course_page') {
    //Store as the last course page seen.
    $uid = $user->uid;
    $user_all_data = entity_load('user', array($uid) );
    $user_all_data = $user_all_data[ $uid ];
    $user_all_data->field_last_course_page_seen = 
        array( 
          LANGUAGE_NONE => array(
            0 => array(
              'value' =>current_path()
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
        //Get nonaliased URL.
        $url = $user_all_data->field_last_course_page_seen[LANGUAGE_NONE][0]['value'];
        $url_pieces = explode('/', $url);
        if ( isset($url_pieces[1]) && is_numeric($url_pieces[1])) {
          $nid = $url_pieces[1];
          $node = node_load($nid);
          drupal_set_message(
              t('The last course page you looked at was ')
              . l($node->title, base_path() . $url) 
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
