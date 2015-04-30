<?php

/**
 * Implements hook_help().
 * @todo Write help in hook_help.
 */
function cyco_activities_help($path, $arg) {
  switch ($path) {
    case 'admin/help#cyco_activities':
      return '<p>' . t('Helpy helpy help help, <a href="@jquery">jQuery</a>.', 
          array(
            '@jquery' => 'http://jquery.com',
          )) . '</p>';
  }
}

/**
 * Implements hook_swim_custom_tag_view_info().
 */
function cyco_activities_swim_custom_tag_view_info() {
  return array(
    'tag' => 'activity',
    'callback' => '_cyco_activities_swim_callback',
  );
}

/**
 * Implement hook_theme().
 */
function cyco_activities_theme() {
  $result = array(
    'activity_inserted' => array(
      'template' => 'custom/cyco-activities-insert',
      //Default variable values
      'variables' => array(
        'title' => '(no title)',
        'summary' => '(no summary)',
        'more_link_destination' => '',
        'activity_node' => '',
      ),
    ),
  );
  return $result;
}

/**
 * Implements hook_menu_local_tasks_alter.
 * 
 * Add local menu buttons to activity list and for creating activity.
 * Convenience for authors.
 */
function cyco_activities_menu_local_tasks_alter(&$data, $router_item, $root_path) {
  switch ($root_path) {
    case 'activities':
      if ( cyco_core_current_user_has_role( array('author', 'administrator') ) ) {
        //Link to add activity.
        $item = menu_get_item('node/add/activity');
        $item['title'] = t('Add activity');
        $data['actions']['output'][] = array(
          '#theme' => 'menu_local_action',
          '#link' => $item,
        );
      }
      break;
    case 'node/%':
      $path = $router_item['href'];
      list( $ignore, $nid ) = explode('/', $path);
      $node = node_load($nid);
      switch ( $node->type ) {
        case 'activity':
          if ( cyco_core_current_user_has_role( 
                array('author', 'administrator', 'grader', 'reviewer') 
              ) ) {
            //List activity.
            $item = menu_get_item('activities');
            $item['title'] = t('List activities');
            $data['actions']['output'][] = array(
              '#theme' => 'menu_local_action',
              '#link' => $item,
            );
          }
          if ( cyco_core_current_user_has_role( array('author', 'administrator') ) ) {
            //Link to add activity.
            $item = menu_get_item('node/add/activity');
            $item['title'] = t('Add activity');
            $data['actions']['output'][] = array(
              '#theme' => 'menu_local_action',
              '#link' => $item,
            );
          }
          break;
      }
      break;
    }
}

/**
 * Callback to generate HTML for the activity.
 * @param string $activity_internal_name Activity internal name.
 * @param string $tag_content Inner tag content. Not used.
 */
function _cyco_activities_swim_callback( $activity_internal_name, $tag_content ) {
  $activity_nid = cyco_core_nid_for_internal_name( $activity_internal_name );
  if ( is_null($activity_nid) ) {
    //Error already reported in function. 
    return '';
  }
  //Exit if not found.
  if ( $activity_nid == 0 ) {
    $message = t('Not found activity internal name: @name', 
        array('@name' => $activity_internal_name));
    watchdog('cyco_activity', $message);
    return '';
  }
  $activity_node = node_load($activity_nid);
  if ( ! $activity_node->status ) {
    $message = t('Tried to show unpublished activity: @name (@nid)', 
        array('@name' => $activity_internal_name, '@nid' => $activity_nid)
        );
    watchdog('cyco_activity', $message);
    return '';    
  }
  //Make sure that this is the right type of node.
  if (   $activity_node == FALSE 
      || !node_access('view', $activity_node) 
      || $activity_node->type != 'activity') {
    $message = t('Invalid activity id: @id', array('@id' => $activity_nid) );
    $message = __FILE__ . ' (line ' . __LINE__ . ') ' . __FUNCTION__ 
        . $message;
    cyco_core_handle_error( $message );
    return '<p>' . $message . '</p>';
  }
  $summary = 
      isset( 
        $activity_node->field_body[LANGUAGE_NONE][0]['summary']
      ) 
      ? swim_textile2html(
          $activity_node->field_body[LANGUAGE_NONE][0]['summary'],
          TRUE //Flag as embedded call (swim_textile2html w/in swim_textile2html),
           //to avoid Certain Things.
        )
      : '';
  //Make activity category links.
  $activity_keyword_links = array();
  $activity_keyword_links_rendered = '';
  if ( sizeof( $activity_node->field_keywords ) > 0 ) {
    $done_first = FALSE;
    foreach ($activity_node->field_keywords[LANGUAGE_NONE] as $item) {
      $tid = $item['tid'];
      $term = taxonomy_term_load($tid);
      $term_name = $term->name;
      $activity_keyword_links[] = array('tid' => $tid, 'term' => $term_name);
      $path_to_term = drupal_lookup_path('alias', 'taxonomy/term/' . $tid);
      $link_html = l($term_name, $path_to_term );
      if ( $done_first ) {
        $activity_keyword_links_rendered .= ', ';
      }
      $done_first = TRUE;
      $activity_keyword_links_rendered .= $link_html;
    }
  }
  $result = theme('activity_inserted', 
      array(
        'title' => $activity_node->title,
        'keyword_links' => $activity_keyword_links,
        'keyword_links_rendered' => $activity_keyword_links_rendered,
        'summary' => $summary,
        'more_link_destination' => '/node/' . $activity_nid,
        'activity_node' => $activity_node,
      )
  );
  return $result;
}

/**
 * Implements hook_form_FORM_alter().
 * 
 * Mess with the activity node edit form.
 */
function cyco_activities_form_activity_node_form_alter( &$form, $form_state ) {
  //Supress author and book options for all users except admins.
  if ( ! cyco_core_current_user_has_role(array('administrator')) ) {
    $form['author']['#access'] = FALSE;
    $form['book']['#access'] = FALSE;
  }
  //Add validation of internal name.
  $form['#validate'][] = '_cyco_activity_form_validate';
}

function _cyco_activity_form_validate($form, &$form_state) {
  //Check format of internal name.
  cyco_core_validate_internal_name_field($form_state);
}

/**
 * Return CSS file to show pseudent in peek.
 */
function cyco_activities_swim_peek_load_css() {
  global $base_url;
  $result = array(
    $base_url . base_path() . drupal_get_path('module', 'cyco_activities') 
      . '/custom/css/cyco_activities.css',
  );
  return $result;
}

