<?php

/**
 * Implements hook_menu_local_tasks_alter().
 * 
 * Change the title of the tab Achievements to Achievements and badges.
 */
function cyco_badges_menu_local_tasks_alter(&$data, $router_item, $root_path) {
  if (substr($root_path, 0, 6) == 'user/%' ) {
    $data['tabs'][0]['output'][1]['#link']['title'] = 'Badges';
  }
}

/**
 * Implement hook_menu_alter().
 * 
 * If there are no badges defined, suppress the Badges entry in the main menu.
 */
function cyco_badges_menu_alter( &$links ) {
  if ( isset($links['badges-public']) ) {
    $query = "SELECT COUNT(*) amount FROM {node} n ".
             "WHERE n.type = :type and n.status = 1";
    $result = db_query($query, array(':type' => 'badge'))->fetch();
    $num_entities = $result->amount;
    if ( $num_entities == 0 ) {
      $links['badges-public']['access callback'] = FALSE;
    }
  }
}

/**
 * Implements hook_module_implements_alter().
 * 
 * Change order of hook invocation, so this module's hooks run
 * after Views. Otherwise, hook_menu_alter won't work.
 */
function cyco_badges_module_implements_alter(&$implementations, $hook) {
  // When the implementations of hook_menu_alter are called, we need our module
  // to be called after views, so let's remove it from the implementations then
  // add it to the end.
  if ($hook == 'menu_alter') {
    if (isset($implementations['cyco_badges'])) {
      $group = $implementations['cyco_badges'];
      unset($implementations['cyco_badges']);
      $implementations['cyco_badges'] = $group;
    }
  }
}

function cyco_badges_achievements_info() {
  $achievements = array();
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'badge')
    ->propertyCondition('status', NODE_PUBLISHED);
  $result = $query->execute();
  if (isset($result['node'])) {
    $badge_nids = array_keys($result['node']);
    $badge_nodes = node_load_multiple($badge_nids);
    foreach ($badge_nodes as $nid => $node) {
      $badge_machine_name 
          = $node->field_badge_machine_name[$node->language][0]['value'];
      //Get the node's URL to use as the achievement id.
      $alias = drupal_get_path_alias('node/' . $nid);
      $alias_pieces = explode('/', $alias);
      $achievement = array(
        'title' => t($node->title),
        'description' => t($node->field_body[$node->language][0]['value']),
        'points' => 10,
        'images' => array(
          'unlocked'  => file_create_url(
              $node->field_unlocked_badge_image[$node->language][0]['uri']
          ),
          'locked'  => file_create_url(
              $node->field_locked_badge_image[$node->language][0]['uri']
          ),
          // 'secret' will use the defaults.
        ),
      );
      $achievements[$badge_machine_name] = $achievement;
    }
    return $achievements;
  }  
}

/**
 * Implements hook_feedback_given, called by the exercises module.
 * @param type $feedback_data
 */
function cyco_badges_feedback_given( $feedback_data ){
  $exercise_nid = $feedback_data['exercise_nid'];
  $complete = $feedback_data['complete'];
  $student_uid = $feedback_data['student_uid'];
  //Get badges and their exercises, for badges that 
  //have the exercise this feedback is for.
  $sql = 'select distinct
      fdfe.entity_id as badge_nid, 
      fdfe.field_exercises_target_id as exercise_nid
    from field_data_field_exercises as fdfe
    where 
      fdfe.entity_id in 
        (select distinct entity_id from field_data_field_exercises fdfe
          where 
            fdfe.bundle = \'badge\'
            and fdfe.field_exercises_target_id = :exer_nid)';
  $records = db_query($sql, array( ':exer_nid' => $exercise_nid ) );
  $badge_exercises = array();
  while ( $row = $records->fetchAssoc() ) {
    $badge_exercises[ $row['badge_nid'] ][] = $row['exercise_nid'];
  }
  //Get all complete exercises for this student.
  $sql = 'select 
    distinct fld_exercise.field_exercise_target_id as exercise_nid
  from field_revision_field_complete as fld_cmplt
    inner join node as n on fld_cmplt.entity_id = n.nid
	inner join field_data_field_exercise as fld_exercise on 
	  fld_exercise.entity_id = n.nid
  where 
	  n.type = \'exercise_submission\'
	  and n.uid = :uid
	  and fld_cmplt.field_complete_value = 1';
  $records = db_query($sql, array( ':uid' => $student_uid ) );
  $completed_exercise_nids = array();
  while ( $row = $records->fetchAssoc() ) {
    $completed_exercise_nids[] = $row['exercise_nid'];
  }
  //Adjust data for latest completion.
  if ( $complete ) {
    //Completed this exercise. Add that to the completion array
    //if not already there.
    if ( ! in_array($exercise_nid, $completed_exercise_nids) ) {
      $completed_exercise_nids[] = $exercise_nid;
    }
  }
  else {
    //This exercise not completed. Remove from destination array if there.
    if ( in_array($exercise_nid, $completed_exercise_nids) ) {
      $completed_exercise_nids = array_diff(
          $completed_exercise_nids, 
          array($exercise_nid)
      );
    }
  }
  //Array of actually completed badge nids.
  $actually_completed_badge_nids = array();
  foreach ( $badge_exercises as $badge_nid => $badge_exercise_nids ) {
    //Badge complete if $exercise_nids is subset of $completed_exercise_nids.
    $missing_exercises = array_diff(
        $badge_exercise_nids, //Exercises in this badge.
        $completed_exercise_nids //Exercises the user completed
    );
    if ( sizeof($missing_exercises) == 0 ) {
      //Did all of the exercises for the badge.
      $actually_completed_badge_nids[] = $badge_nid;
    }
  }
  //Get recorded completed badges for the student.
  $recorded_student_achievements = achievements_totals_user(0, $student_uid);
  //Add achievements that need to be added.
  foreach ( $actually_completed_badge_nids as $actual_badge_nid ) {
    if ( ! in_array($actual_badge_nid, $recorded_student_achievements) ) {
      //Award achievement.
      //Get the machine name for the badge.
      $badge_node = node_load( $actual_badge_nid );
      $badge_machine_name 
        = $badge_node->field_badge_machine_name[$badge_node->language][0]['value'];
      achievements_unlocked( $badge_machine_name, $student_uid );
    }
  }
  //Compute which achievements need to be removed.
  foreach ( $recorded_student_achievements as $recorded_badge_nid => $recorded_student_achievement) {
    if ( ! in_array($recorded_badge_nid, $actually_completed_badge_nids) ) {
      //Remove achievement.
      //Get the machine name for the badge.
      $badge_machine_name = $recorded_student_achievement->achievement_id;
      achievements_locked( $badge_machine_name, $student_uid );
    }
  }
}

/**
 * Implements hook_feedback_erased, called by the exercises module.
 * @param type $feedback_data
 */
function cyco_badges_feedback_erased( $feedback_data ) {
  //Set to not complete.
  $feedback_data['complete'] = 0;
  //Treat as new feedback given.
  cyco_badges_feedback_given($feedback_data);
}

/**
 * Implements hook_node_postdelete.
 * @param stdClass $node Node deleted.
 */
function cyco_badges_node_postdelete($node) {
  if ( $node->type == 'exercise_submission' ) {
    //Get feedback data to send to hook implementations.
    $feedback_data 
        = cyco_exercises_package_submission_node_feedback( $node );
    //Set to not complete.
    $feedback_data['complete'] = 0;
    //Treat as new feedback given.
    cyco_badges_feedback_given($feedback_data);
  }
  if ( $node->type == 'badge' ) {
    cyco_badges_clear_cache();
  }
}

/**
 * Implements hook_node_postsave().
 * 
 * Check if the menu cache needs to be rebuilt, so that the 
 * visibility of the Badges link in the tools menu is correct.
 */
function cyco_badges_node_postsave($node, $op) {
  if ( $node->type == 'badge' ) {
    _cyco_badges_clear_menu_cache( $node );
  }
}

/**
 * Rebuild the menu cache if the passed node is a badge node, and
 * there are either 0 or 1 badge nodes in existance. This ensures
 * that the Badge link in the tools menu is shown or hidden correctly.
 * @param type $node
 */
function _cyco_badges_clear_menu_cache( $node ) {
  if ( $node->type == 'badge' ) {
    $query = "SELECT COUNT(*) amount FROM {node} n ".
             "WHERE n.type = :type and n.status = 1";
    $result = db_query($query, array(':type' => 'badge'))->fetch();
    $num_entities = $result->amount;
    if ( $num_entities < 2 ) {
      menu_rebuild();
    }
  }
} 

/**
 * Implements hook_views_api().
 */
function cyco_badges_views_api_alter(&$vars) {
  if (isset($vars['cyco_badges'])) {
    $vars['cyco_badges']['path'] 
        = drupal_get_path('module', 'cyco_badges') . '/custom/views';
  }
}

/**
 * Clear badges (achievement) cache.
 */
function cyco_badges_clear_cache() {
  achievements_load(NULL, FALSE, TRUE);
}

/**
 * Implements hook_node_postsave().
 * 
 * Clear the achievements cache.
 */
function cyco_badges_node_postsave($node, $op) {
  if ( $node->type == 'badge' ) {
    cyco_badges_clear_cache();
  }
}

