<?php
/**
 * Implements hook_help().
 * @todo Write patterny help in hook_help.
 */
function cyco_patterns_help($path, $arg) {
  switch ($path) {
    case 'admin/help#cyco_patterns':
      return '<p>' . t('Helpy helpy help help, <a href="@jquery">jQuery</a>.', 
          array(
            '@jquery' => 'http://jquery.com',
          )) . '</p>';
  }
}

/**
 * Implements hook_swim_custom_tag_view_info().
 */
function cyco_patterns_swim_custom_tag_view_info() {
  return array(
    'tag' => 'pattern',
    'callback' => '_cyco_patterns_swim_callback',
  );
}

/**
 * Implement hook_theme().
 */
function cyco_patterns_theme() {
  $result = array(
    'pattern_inserted' => array(
      'template' => 'custom/cyco-patterns-insert',
      //Default variable values
      'variables' => array(
        'title' => '(no title)',
        'situation' => '(no situation)',
        'actions' => '(no actions)',
        'more_link_destination' => '',
        'pattern_node' => '',
      ),
    ),
  );
  return $result;
}

/**
 * Implements hook_node_view().
 * 
 * If the user can edit course pages, then add the id of the pattern
 * to the end of the title. 
 */
//function cyco_patterns_node_view($node, $view_mode, $langcode) {
//  if ( $node->type == 'pattern' && $view_mode == 'full' ) {
//    if ( user_access('edit any pattern content') ) {
//      drupal_set_title( $node->title . ' (' . $node->nid . ')' );
//    }
//  }
//}

/**
 * Implements hook_menu_local_tasks_alter
 */
function cyco_patterns_menu_local_tasks_alter(&$data, $router_item, $root_path) {
  switch ($root_path) {
    case 'patterns':
      if ( cyco_core_current_user_has_role( array('author', 'administrator') ) ) {
        //Link to add pattern.
        $item = menu_get_item('node/add/pattern');
        $item['title'] = t('Add pattern');
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
      if ( $node->type == 'pattern' ) {
          // Link to add rubric item.
          $item = menu_get_item('node/add/pattern');
          $item['title'] = t('Add pattern');
          $data['actions']['output'][] = array(
            '#theme' => 'menu_local_action',
            '#link' => $item,
          );
          //Link to list rubric items.
          $item = menu_get_item('patterns');
          $item['title'] = t('List patterns');
          $data['actions']['output'][] = array(
            '#theme' => 'menu_local_action',
            '#link' => $item,
          );
          break;
      }
  }
}

/**
 * Callback to generate HTML for the pattern.
 * @param string $pattern_internal_name Pattern internal name.
 * @param string $tag_content Inner tag content. Not used.
 */
function _cyco_patterns_swim_callback( $pattern_internal_name, $tag_content ) {
  $pattern_nid = cyco_core_nid_for_internal_name( $pattern_internal_name );
  if ( is_null($pattern_nid) ) {
    //Error already reported in function. 
    return '';
  }
//  $sql = 'select entity_id from {field_data_field_internal_name} '
//      . 'where entity_type=\'node\' and bundle=\'pattern\' '
//      . 'and field_internal_name_value=\'' 
//      . check_plain($pattern_internal_name) . '\'';
//  $query_result = db_query($sql);
//  $nids = array();
//  foreach( $query_result as $row ) {
//    $nids[] = $row->entity_id;
//  }
//  $num_nids_returned = sizeof($nids);
//  if ( $num_nids_returned > 1 ) {
//    //This should never happen.
//    $message = __FILE__ . ' (line ' . __LINE__ . ') ' . __FUNCTION__ 
//        . ' Duplicates for internal name ' . $pattern_internal_name . '.';
//    cyco_core_handle_error( $message );
//    form_set_error(
//        'field_internal_name', 
//        t('Internal error: ' . $message . "\n\nPlease tell someone.")
//    );
//    return '';
//  }
  //Exit if not found.
  if ( $pattern_nid == 0 ) {
    $message = t('Not found pattern internal name: @name', 
        array('@name' => $pattern_internal_name));
    watchdog('cyco_pattern', $message);
    return '';
  }
  $pattern_node = node_load($pattern_nid);
  if ( ! $pattern_node->status ) {
    $message = t('Tried to show unpublished pattern: @name (@nid)', 
        array('@name' => $pattern_internal_name, '@nid' => $pattern_nid)
        );
    watchdog('cyco_pattern', $message);
    return '';    
  }
  //Make sure that this is the right type of node.
  if (   $pattern_node == FALSE 
      || !node_access('view', $pattern_node) 
      || $pattern_node->type != 'pattern') {
    $message = t('Invalid pattern id: @id', array('@id' => $pattern_nid) );
    $message = __FILE__ . ' (line ' . __LINE__ . ') ' . __FUNCTION__ 
        . $message;
    cyco_core_handle_error( $message );
    return '<p>' . $message . '</p>';
  }
  $situation = 
      isset( 
        $pattern_node->field_situation[LANGUAGE_NONE][0]['value']
      ) 
      ? swim_textile2html(
          $pattern_node->field_situation[LANGUAGE_NONE][0]['value'],
          TRUE //Flag as embedded call (swim_textile2html w/in swim_textile2html),
           //to avoid Certain Things.

        )
      : '';
  $actions = 
      isset( 
        $pattern_node->field_actions[LANGUAGE_NONE][0]['value'] 
      )
      ? swim_textile2html( 
          $pattern_node->field_actions[LANGUAGE_NONE][0]['value'],
          TRUE //Flag as embedded call (swim_textile2html w/in swim_textile2html),
               //to avoid Certain Things.
        )
      : '';
/*
  //Make pattern category links.
  $pattern_category_links = array();
  $pattern_category_links_rendered = '';
  if ( sizeof( $pattern_node->field_pattern_categories ) > 0 ) {
    $done_first = FALSE;
    foreach ($pattern_node->field_pattern_categories[LANGUAGE_NONE] as $item) {
      $tid = $item['tid'];
      $term = taxonomy_term_load($tid);
      $term_name = $term->name;
      $pattern_category_links[] = array('tid' => $tid, 'term' => $term_name);
      $path_to_term = drupal_lookup_path('alias', 'taxonomy/term/' . $tid);
      $link_html = l($term_name, $path_to_term );
      if ( $done_first ) {
        $pattern_category_links_rendered .= ', ';
      }
      $done_first = TRUE;
      $pattern_category_links_rendered .= $link_html;
    }
  }
 */
  $result = theme('pattern_inserted', 
      array(
        'title' => $pattern_node->title,
//        'category_links' => $pattern_category_links,
//        'category_links_rendered' => $pattern_category_links_rendered,
        'situation' => $situation,
        'actions' => $actions,
        'more_link_destination' => '/node/' . $pattern_nid,
        'pattern_node' => $pattern_node,
      )
  );
  return $result;
}

/**
 * Implements hook_form_FORM_alter().
 * 
 * Mess with the pattern node edit form.
 */
function cyco_patterns_form_pattern_node_form_alter( &$form, $form_state ) {
  //Supress author and book options for all users except admins.
  if ( ! cyco_core_current_user_has_role(array('administrator')) ) {
    $form['author']['#access'] = FALSE;
    $form['book']['#access'] = FALSE;
  }
  //Add validation of internal name.
  $form['#validate'][] = '_cyco_pattern_form_validate';
}

function _cyco_pattern_form_validate($form, &$form_state) {
  //Check format of internal name.
  cyco_core_validate_internal_name_field($form_state);
}

/**
 * Return CSS file to show pseudent in peek.
 */
function cyco_patterns_swim_peek_load_css() {
  global $base_url;
  $result = array(
    $base_url . base_path() . drupal_get_path('module', 'cyco_patterns') 
      . '/custom/css/cyco_patterns.css',
  );
  return $result;
}

/**
 * Implements hook_node_view().
 */
function cyco_patterns_node_view($node, $view_mode, $langcode) {
  if ( module_exists('cyco_events_log') && $view_mode == 'full') {
    if ( $node->type == 'pattern' ) {
      cyco_events_log_log_node_view($node, $view_mode, $langcode);
    }
  }
}

/**
 * Alter some edit forms. Registier pattern tag for code that updates
 * references from embedded nodes to the nodes in which they are embedded.
 */
function cyco_patterns_form_node_form_alter(&$form, $form_state) {
  $types_exers_can_be_embedded = array('course_page', 'blueprint_page', 'page');
  if ( in_array($form['#node']->type, $types_exers_can_be_embedded) ) {
    swim_register_embedded_refs_tag($form, 'pattern', 'pattern');
  }    
}
