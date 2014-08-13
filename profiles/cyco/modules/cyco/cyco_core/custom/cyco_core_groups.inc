<?php
/**
 * @file
 * Code about groups.
 */

function cyco_core_groups_render_basic_list() {
//  $html = views_embed_view('cyco_core_user_groups', 'user_groups_for_cp');
  $name = 'cybercourse_user_groups';
  $display_id = 'user_groups_for_cp';  
  $view = views_get_view($name);
  if (!$view || !$view->access($display_id)) {
    return '<p>Not found or access denied</p>';
  }
  $view_content = $view->preview($display_id);
  return $view_content;
}

/**
 * Get the groups a user has a role in.
 * @global stdClass $user The current user.
 * @param string $group_type Type of group, e.g., class.
 * @param stdClass $user_to_check User to check. Defaults to current user.
 * @return array Group ids.
 */
function cyco_core_groups_get_groups_for_user( 
    $group_type, $user_to_check = NULL ) {
  if ( is_null($user_to_check) ) {
    global $user;
    $user_to_check = $user;
  }
  //Find groups the user is in.
  $user_group_gids = og_get_groups_by_user($user_to_check, $group_type);
  return $user_group_gids;
}

/**
 * Get the groups of a given type that a user has a given role in.
 * @global stdClass $user The current user.
 * @param string $group_type Type of group, e.g., class.
 * @param string $role_name Role name, e.g., grader.
 * @param stdClass $user_to_check User to check. Defaults to current user.
 * @return array Group ids.
 */
function cyco_core_groups_get_groups_by_role( 
    $group_type, $role_name, $user_to_check = NULL ) {
  if ( is_null($user_to_check) ) {
    global $user;
    $user_to_check = $user;
  }
  //Find groups the user is in.
  //Returns null if there are none.
  $user_group_gids = og_get_groups_by_user($user_to_check, 'node');
  //Which of the groups are classes?
  $user_classes_gids = array();
  if ( ! is_null($user_group_gids) ) {
    foreach( $user_group_gids as $group_gid ) {
      $group_node = node_load( $group_gid );
      if ( $group_node->type == $group_type ) {
        $user_classes_gids[] = $group_gid;
      }
    }
  }
  //Now check the roles.
  $user_groups = array();
  foreach ( $user_classes_gids as $gid ) {
    $roles = og_get_user_roles('node', $gid, $user_to_check->uid);
    if ( in_array($role_name, $roles) ) {
      $user_groups[] = $gid;
    }
  }
  return $user_groups;
}


/**
 * Get all users of a group.
 * See http://codekarate.com/blog/drupal-7-getting-all-members-organic-group
 */
function cyco_core_groups_get_group_users($gid) {
  $query = db_select('users', 'u');
  $query
    ->condition('u.uid', 0, '<>')
    ->condition('u.status', 1, '=')
    ->fields('u', array('uid', 'name'))
    ->join('og_membership', 'ogm', "ogm.gid = :gid AND u.uid = ogm.etid AND ogm.entity_type = 'user'", array(':gid' => $gid));
  return $query->execute();
}

/**
 * Get the names of group(s) given their id(s).
 * @param int or array $gids A group id, or an array of them.
 * @return string or array One group name, or an array of names,
 *    keyed by group id.
 */
function cyco_core_groups_get_group_names( $gids ) {
  $query = db_select('node', 'n')
      ->fields('n', array('nid', 'title'));
  //Add a condition for an array, or a single value.
  if ( is_array( $gids ) ) {
    $query->condition('n.nid', $gids, 'IN');
  }
  else {
    $query->condition('n.nid', $gids);
  }
  $records = $query->execute();
  if ( is_array( $gids ) ) {
    //Array passed. Return array of nid/title pairs.
    $result = array();
    while ( $record = $records->fetchAssoc() ) {
      $result[ $record['nid'] ] = $record['title'];
    }
  }
  else {
    //Just one gid passed. Return its title.
    $record = $records->fetchAssoc();
    $result = $record['title'];
  }
  return $result;
}

/**
 * Get the members of group(s) given their id(s).
 * @param int or array $gids A group id, or an array of them.
 * @return array Entity ids (one gid), or array of arrays of member ids,
 *    keyed by group id.
 */
function cyco_core_groups_get_group_members( $gids ) {
  $query = db_select('og_membership', 'ogm')
      ->fields('ogm', array('gid', 'etid'));
  //Add a condition for an array, or a single value.
  if ( is_array( $gids ) ) {
    $query->condition('ogm.gid', $gids, 'IN');
  }
  else {
    $query->condition('ogm.gid', $gids);
  }
  $records = $query->execute();
  if ( is_array( $gids ) ) {
    //Array passed. Return array of arrays.
    $result = array();
    while ( $record = $records->fetchAssoc() ) {
      $gid = $record['gid'];
      $etid = $record['etid'];
      if ( ! isset( $result[ $gid ] ) ) {
        $result[ $gid ] = array();
      }
      $result[ $gid ][] = $etid;
    }
  }
  else {
    //Just one gid passed. Return its members.
    $result = array();
    while ( $record = $records->fetchAssoc() ) {
      $etid = $record['etid'];
      $result[] = $etid;
    }
  }
  return $result;
}

/**
 * Implements hook_node_view().
 */
function cyco_core_node_view($node, $view_mode, $langcode) {
  if ( $node->type == 'class' && $view_mode == 'full' ) {
    //Attach list of class posts to the page.
    $name = 'class_nodes_for_class';
    $display_id = 'default';  
    $view = views_get_view($name);
    if ( $view ) {
      $view->set_arguments(array( $node->nid ));
      if (!$view || !$view->access($display_id)) {
        return '<p>Not found or access denied</p>';
      }
      $view_content = $view->preview($display_id);
      $node->content['field_body'][0]['#markup'] .= $view_content;     
    }
  }
    
}

/**
 * Implements hook_menu_local_tasks_alter
 */
function cyco_core_menu_local_tasks_alter(&$data, $router_item, $root_path) {
  switch($root_path){
    case 'node/%':
      $path = $router_item['href'];
      list( $ignore, $nid ) = explode('/', $path);
      $node = node_load($nid);
      switch( $node->type ) {
        case 'class':
          //Link to add class post.
          if (cyco_core_current_user_has_role( array('instructor', 'administrator') ) ) {
            $item = menu_get_item('node/add/class-post');
            $item['title'] = t('Add class post');
            //Add class nid prepopulate group audience field.
            $item['localized_options']['query']['og_group_ref'] = $nid;
            $item['html'] = TRUE;
            $data['actions']['output'][] = array(
              '#theme' => 'menu_local_action',
              '#link' => $item,
            );
          }
          break;
      }
          
  }
}

function cyco_core_og_role_grant($entity_type, $gid, $uid, $og_rid) {
  _cyco_core_update_student_role($entity_type, $gid, $uid, 'grant', $og_rid);
}

function cyco_core_og_role_revoke($entity_type, $gid, $uid, $og_rid) {
  _cyco_core_update_student_role($entity_type, $gid, $uid, 'revoke', $og_rid);
}
//
//function cyco_core_og_membership_delete(OgMembership $og_membership) {
//  $r=6;
//}
//
//function cyco_core_og_membership_insert(OgMembership $og_membership) {
//  $r=6;
//}
//
//function cyco_core_og_membership_update(OgMembership $og_membership) {
//  $r=6;
//}
//


/**
 * Update account's student role depending on whether the account has the 
 * student role in a group. This code is called when there is a role change
 * in a group.
 * @param string $entity_type Class is the only one we care about.
 * $param int $gid Group id.
 * @param int $uid The user.
 * @param string $current_op Operation, grant or revoke.
 * @param int $og_rid The OG role that is affected.
 */
function _cyco_core_update_student_role( $entity_type, $gid, $uid, $current_op, $og_rid ) {
  if ( $entity_type == 'node' ) {
    $node = node_load( $gid );
    if ( $node->type == 'class' ) {
      //This change is for a class.
      //Get the OG role name that is being changed.
      $og_role_names = og_get_user_roles_name(array($og_rid));
      $og_role_name = current( $og_role_names );
      if ( $og_role_name == 'student' ) {
        //This change is for the student role in a class.
        $user_being_changed = user_load( $uid );
        //Get the classes in which this user has the student role.
        $gids_where_student = cyco_core_groups_get_groups_by_role(
            'class', 'student', $user_being_changed
        );
        //Adjust the group list depending on the current operation.
        //Don't need to do this, since the hook is called after the 
        //data is saved, but do it just in case. Computers are 
        //not trustworthy.
        if ( $current_op == 'grant' ) {
          //Add the new group to the list if it is not already there.
          if ( ! in_array($gid, $gids_where_student) ) {
            $gids_where_student[] = $gid;
          }
        }
        else if ( $current_op == 'revoke' ) {
          //Remove the new group to the list if it is there.
          if ( in_array($gid, $gids_where_student) ) {
            unset( $gids_where_student[ $gid ] );
          }
        }
        else {
          $message = __FILE__ . ' (line ' . __LINE__ . ') ' . __FUNCTION__ 
              . ' Bad operation: ' . $current_op;
          cyco_core_handle_error( $message );
        }
        //Should this user be a student?
        $user_is_student = ( sizeof( $gids_where_student ) > 0 );
        if ( $user_is_student ) {
          //If the user is already an instructor or grader in the group being
          //affected, the user should not be a student as well.
          //Get the groups for which the current user is an instructor.
          $instructor_groups = cyco_core_groups_get_groups_by_role(
              'class', 'instructor', $user_being_changed
          ); 
          //Get the groups for which the current user is a grader.
          $grader_groups = cyco_core_groups_get_groups_by_role( 
              'class', 'grader', $user_being_changed
          ); 
          if ( in_array($gid, $instructor_groups) || in_array($gid, $grader_groups) ) {
            $user_is_student = FALSE;
            drupal_set_message( 
              'Warning! Someone should not be a student in a class if '
                . 's/he is already an instructor or grader in the same class. '
                . 'Please check the roles for the class.'
            );
          }
        }
        //Add/remove role from user.
        //This is the Drupal student role, not the OG role.
        $drupal_rid = cyco_core_get_role_id_by_name( 'student' );
        if ( $user_is_student ) {
          $user_being_changed->roles[ $drupal_rid ] = 'student';
        }
        else {
          unset( $user_being_changed->roles[ $drupal_rid ] );
        }
        user_save($user_being_changed, array('roles' => $user_being_changed->roles));
      } // End if OG role name is student.
    } // End if node type == class
  } // End if entity type == node
}