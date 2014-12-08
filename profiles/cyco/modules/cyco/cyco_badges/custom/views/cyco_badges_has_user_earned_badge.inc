<?php
/**
 * @file
 * Field handler to show whether the current user has earned a badge.
 */
class cyco_badges_handler_has_user_earned_badge extends views_handler_field {

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
    global $user;
    if ( $user->uid == 0 ) {
      return 'If you were a student, you could earn this badge.';
    }
    $badge_nid = $values->nid;
    $badge = node_load($badge_nid);
    $achievement_machine_name 
        = $badge->field_internal_name[$badge->language][0]['value'];
    if (in_array($achievement_machine_name, $this->current_users_badge_ids) ) {
      $result = t('Yes');
    }
    else {
      $result = t('No');
    }
    return $result;
  }
}
