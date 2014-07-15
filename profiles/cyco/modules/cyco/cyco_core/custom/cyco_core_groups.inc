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
  $user_group_gids = og_get_groups_by_user($user_to_check, $group_type);
  $user_groups = array();
  foreach ( $user_group_gids as $gid ) {
    $roles = og_get_user_roles($group_type, $gid);
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
          $item = menu_get_item('node/add/class-post');
          $item['title'] = t('Add class post');
          //Add class nid prepopulate group audience field.
          $item['localized_options']['query']['og_group_ref'] = $nid;
          $item['html'] = TRUE;
          $data['actions']['output'][] = array(
            '#theme' => 'menu_local_action',
            '#link' => $item,
          );
          break;
      }
          
  }
}
