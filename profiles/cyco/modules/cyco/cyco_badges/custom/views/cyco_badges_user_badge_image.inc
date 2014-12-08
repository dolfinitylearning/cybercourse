<?php
/**
 * @file
 * Field handler to show image for current badge, depending on whether user
 * has earned it or not.
 */
class cyco_badges_user_badge_image extends views_handler_field {

  protected $current_users_badge_ids = array();
  
  function construct() {
    parent::construct();
    global $user;
    if ( $user->uid != 0 ) {
      $recorded_student_achievements = achievements_totals_user(0, $user->uid);
      foreach ( $recorded_student_achievements as $recorded_student_achievement ) {
        $this->current_users_badge_ids[] = $recorded_student_achievement->achievement_id;
      }
    }
  }
  
  function query() {
    // Do nothing -- to override the parent query.
  }  

  function option_definition() {
    $options = parent::option_definition();
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
  }
  
  function render($values) {
    $badge_nid = $values->nid;
    $badge_node = node_load($badge_nid);
    global $user;
    if ( $user->uid == 0 ) {
      //Anon user, show the earned badge image.
      $earned_badge = TRUE;
    }
    else {
      $achievement_machine_name 
          = $badge_node->field_internal_name[$badge_node->language][0]['value'];
      $earned_badge 
          = in_array($achievement_machine_name, $this->current_users_badge_ids);
    }
    $file_url = '';
    if ( $earned_badge ) {
      $file_url = file_create_url(
          $badge_node->field_unlocked_badge_image[$badge_node->language][0]['uri']
      );
    }
    else {
      $file_url = file_create_url(
          $badge_node->field_locked_badge_image[$badge_node->language][0]['uri']
      );
    }
    $alt = t('Badge');
    $result = '<img src="' . $file_url . '" alt="' . $alt . '">';
    return $result;
  }
}
