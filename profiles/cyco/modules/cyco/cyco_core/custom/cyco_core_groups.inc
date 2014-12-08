<?php
/**
 * @file
 * Code about groups.
 */

function cyco_core_groups_render_basic_list() {
  $name = 'cybercourse_user_groups';
  $display_id = 'default'; //user_groups_for_cp';  
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
    foreach ( $user_group_gids as $group_gid ) {
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
  // Add a condition for an array, or a single value.
  if ( is_array( $gids ) ) {
    $query->condition('n.nid', $gids, 'IN');
  }
  else {
    $query->condition('n.nid', $gids);
  }
  $records = $query->execute();
  if ( is_array( $gids ) ) {
    // Array passed. Return array of nid/title pairs.
    $result = array();
    while ( $record = $records->fetchAssoc() ) {
      $result[ $record['nid'] ] = $record['title'];
    }
  }
  else {
    // Just one gid passed. Return its title.
    $record = $records->fetchAssoc();
    $result = $record['title'];
  }
  return $result;
}

/**
 * Get the members of group(s) given their id(s).
 * 
 * @param int or array $gids A group id, or an array of them.
 * @return array Entity ids (one gid), or array of arrays of member ids,
 *    keyed by group id.
 */
function cyco_core_groups_get_group_members( $gids ) {
  $query = db_select('og_membership', 'ogm')
      ->fields('ogm', array('gid', 'etid'));
  // Add a condition for an array, or a single value.
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
    // Attach list of class posts to the page.
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
  switch ($root_path) {
    case 'node/%':
      $path = $router_item['href'];
      list( $ignore, $nid ) = explode('/', $path);
      $node = node_load($nid);
      switch ($node->type) {
        case 'class':
          // Link to add class post.
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

/**
 * Implements hook_og_role_grant().
 */
function cyco_core_og_role_grant($entity_type, $gid, $uid, $og_rid) {
  _cyco_core_update_student_role($entity_type, $gid, $uid, 'grant', $og_rid);
}

/**
 * Implements hook_og_role_revoke().
 */
function cyco_core_og_role_revoke($entity_type, $gid, $uid, $og_rid) {
  _cyco_core_update_student_role($entity_type, $gid, $uid, 'revoke', $og_rid);
}

/**
 * Update account's student role depending on whether the account has the 
 * student role in a group. This code is called when there is a role change
 * in a group.
 * 
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
      // This change is for a class.
      // Get the OG role name that is being changed.
      $og_role_names = og_get_user_roles_name(array($og_rid));
      $og_role_name = current( $og_role_names );
      if ( $og_role_name == 'student' ) {
        // This change is for the student role in a class.
        $user_being_changed = user_load( $uid );
        // Get the classes in which this user has the student role.
        $gids_where_student = cyco_core_groups_get_groups_by_role(
            'class', 'student', $user_being_changed
        );
        // Adjust the group list depending on the current operation.
        // Don't need to do this, since the hook is called after the 
        // data is saved, but do it just in case. Computers are 
        // not trustworthy.
        if ( $current_op == 'grant' ) {
          // Add the new group to the list if it is not already there.
          if ( ! in_array($gid, $gids_where_student) ) {
            $gids_where_student[] = $gid;
          }
        }
        elseif ( $current_op == 'revoke' ) {
          // Remove the new group to the list if it is there.
          if ( in_array($gid, $gids_where_student) ) {
            unset( $gids_where_student[ $gid ] );
          }
        }
        else {
          $message = __FILE__ . ' (line ' . __LINE__ . ') ' . __FUNCTION__ 
              . ' Bad operation: ' . $current_op;
          cyco_core_handle_error( $message );
        }
        // Should this user be a student?
        $user_is_student = ( sizeof( $gids_where_student ) > 0 );
        if ( $user_is_student ) {
          // If the user is already an instructor or grader in the group being
          // affected, the user should not be a student as well.
          // Get the groups for which the current user is an instructor.
          $instructor_groups = cyco_core_groups_get_groups_by_role(
              'class', 'instructor', $user_being_changed
          ); 
          // Get the groups for which the current user is a grader.
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
        // Add/remove role from user.
        // This is the Drupal student role, not the OG role.
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

/**
 * Implements hook_form_alter.
 * 
 * When adding users, or editing memberships, check the Student role
 * by default.
 */
function _cyco_core_groups_form_alter(&$form, $form_state, $form_id) {
  if ( $form_id == 'og_ui_add_users' || $form_id == 'og_ui_edit_membership') {
    //When adding users to a class, select the student OG role
    //as the default.
    //Find the index of the student role, to pass to JS.
    $student_og_role_index = NULL;
    $og_role_names = $form['og_user']['roles']['#options'];
    foreach( $og_role_names as $index => $og_role_name ) {
      if ( $og_role_name == 'student' ) {
        $student_og_role_index = $index;
        break;
      }
    }
    if ( is_null($student_og_role_index) ) {
      drupal_set_message('Hmm, I could not find the student OG role. '
          . 'That\'s unexpected.', 'warning');
      return;
    }
    //Tell JS what the index of the student role is.
    $settings = array(
      'studentOgRoleIndex' => $student_og_role_index,
    );
    drupal_add_js(
        array('cycoGroupsSelectStudentRole' => $settings),
        'setting'
    );    
    drupal_add_js(
        drupal_get_path('module', 'cyco_core')
        . '/custom/js/cyco_core_groups_change_roles.js'
    );
  }
}

/**
 * Add a menu item that should appear in the group admin page.
 */
function cyco_core_og_ui_get_group_admin() {
  $items = array();
//return $items;
  // User listing pages.
  $items['approve_deny_membership_requests'] = array(
    'title' => 'Approve/deny student membership requests',
//    'title callback' => '_cyco_core_groups_approve_deny_title',
//    'title callback' => 'og_ui_menu_title_callback',
//    'title arguments' => array('Membership requests for group @group', 1, 2),
    'description' => 'Choose which group membership requests you will accept.',
    'href' => 'admin/approve-deny-membership-requests',
//    'page callback' => '_cyco_core_groups_approve_deny_membership_requests',
//    'page arguments' => array(1, 2),
//    'access callback' => TRUE,
//    'access callback' => 'og_ui_user_access_group',
//    'access arguments' => array('manage members', 1, 2),
//    'weight' => -12,
  );  

  return $items;
}

/**
 * Called from hook menu items.
 */
function _cyco_core_groups_add_menu_items(&$items) {
  $items['group/%/%/admin/approve-deny-membership-requests'] = array(
//    'title' => 'thing',
//    'title callback' => '_cyco_core_groups_approve_deny_title',
    'title callback' => 'og_ui_menu_title_callback',
    'title arguments' => array('Membership requests for group @group', 1, 2),
    'description' => 'Approve/deny group membership requests.',
    'page callback' => '_cyco_core_groups_approve_deny_membership_requests',
    'page arguments' => array(1, 2),
//    'access callback' => TRUE,
    'access callback' => 'og_ui_user_access_group',
    'access arguments' => array('manage members', 1, 2),
    'weight' => -12,
  );
}

//See og_ui_menu_title_callback.
function _cyco_core_groups_approve_deny_title($title, $entity_type, $etid) {
  $wrapper = entity_metadata_wrapper($entity_type, $etid);
  return str_replace('@group', $wrapper->label(), $title);
}

/**
 * Form builder; approve/deny request page.
 * Based on og_ui_admin_account in og_ui.admin.inc.
 */
function _cyco_core_groups_approve_deny_membership_requests($group_type, $gid) {
  //KRM - next right?
  //og_set_breadcrumb($group_type, $gid, array(l(t('Group'), "$group_type/$gid/group")));
  // $view = explode(':', variable_get)
//  list($view_name, $display) = explode(':', variable_get('og_ui_admin_people_view', 'og_members_admin:default'));
  // We can't use views_embed_view() as we have exposed filter, and we need to
  // make sure the path is overriden to the current URL.
  // @see http://drupal.org/node/525592#comment-1968604
  $view = views_get_view('group_approve_membership_requests');
//  $view = views_get_view($view_name, $display);
  $view->set_arguments(array($group_type, $gid));
  $view->override_url = $_GET['q'];
  return $view->preview();
}

/**
 * Implements hook_og_user_operations().
 */
//function cyco_core_og_user_operations($form = array(), $form_state = array()) {
//  drupal_set_message('dogs');
//  return;
//  $operations = array();
//  if (og_user_access($gid, 'update group') && !og_user_access($gid, 'administer group')) {
//    $operations = array(
//      'group_lead_grant' => array(
//        'label' => t('Grant group lead role to user'),
//        'callback' => 'group_leader_grant',
//      ),
//    );
//  }  
//  
//  return $operations;
//}

/**
 * Implements hook_action_info().
 */
function cyco_core_action_info() {
  //Define two actions - approve student membership, deny student membership.
  return array(
    '_cyco_core_approve_student_membership_action' => array(
      'type' => 'og_membership',
      'label' => t('Approve student membership'),
      'configurable' => FALSE,
    ),
    '_cyco_core_deny_student_membership_action' => array(
      'type' => 'og_membership',
      'label' => t('Deny student membership'),
      'configurable' => FALSE,
    ),
  );
}

/**
 * Called by VBO to approve student requests to join a group.
 * Changes state to active, and gives the student role.
 */
function _cyco_core_approve_student_membership_action($og_membership, $context) {
  // Don't process the group manager, if exists.
  $group = entity_load_single($og_membership->group_type, $og_membership->gid);
  if (!empty($group->uid) && $group->uid == $og_membership->etid && $og_membership->entity_type == 'user') {
    return;
  }
  //Make membership active from pending.
  $og_membership->state = OG_STATE_ACTIVE;
  $og_membership->save();
  //Give student OG role.
  $group_type = $og_membership->group_type;
  $gid = $og_membership->gid;
  $bundle = $group->type;
  //Load OG roles.
  $og_roles = og_roles($group_type, $bundle);
  $student_rid = array_keys($og_roles, 'student')[0];
  og_role_grant($group_type, $gid, $og_membership->etid, $student_rid);
}

/**
 * Called by VBO to delete a group membership request.
 */
function _cyco_core_deny_student_membership_action($og_membership, $context) {
  $group_type = $og_membership->group_type;
  $gid = $og_membership->gid;
  // Don't process the group manager, if exists.
  $group = entity_load_single($group_type, $gid);
  if (!empty($group->uid) && $group->uid == $og_membership->etid && $og_membership->entity_type == 'user') {
    return;
  }
  $og_membership->delete();
}

