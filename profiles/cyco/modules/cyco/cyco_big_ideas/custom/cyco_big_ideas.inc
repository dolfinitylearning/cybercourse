<?php

/**
 * Implements hook_help().
 * @todo Write big_ideay help in hook_help.
 */
function cyco_big_ideas_help($path, $arg) {
  switch ($path) {
    case 'admin/help#cyco_big_ideas':
      return '<p>' . t('Helpy helpy help help, <a href="@jquery">jQuery</a>.', 
          array(
            '@jquery' => 'http://jquery.com',
          )) . '</p>';
  }
}

/**
 * Implements hook_swim_custom_tag_view_info().
 */
function cyco_big_ideas_swim_custom_tag_view_info() {
  return array(
    'tag' => 'big-idea',
    'callback' => '_cyco_big_ideas_swim_callback',
  );
}

/**
 * Implement hook_theme().
 */
function cyco_big_ideas_theme() {
  $result = array(
    'big_idea_inserted' => array(
      'template' => 'custom/cyco-big-ideas-insert',
      //Default variable values
      'variables' => array(
        'title' => '(no title)',
        'summary' => '(no summary)',
        'more_link_destination' => '',
        'big_idea_node' => '',
      ),
    ),
  );
  return $result;
}

/**
 * Implements hook_menu_local_tasks_alter.
 * 
 * Add local menu buttons to Big Idea list and for creating Big Ideas.
 * Convenience for authors.
 */
function cyco_big_ideas_menu_local_tasks_alter(&$data, $router_item, $root_path) {
  switch ($root_path) {
    case 'big-ideas':
      if ( cyco_core_current_user_has_role( array('author', 'administrator') ) ) {
        //Link to add big_idea.
        $item = menu_get_item('node/add/big-idea');
        $item['title'] = t('Add big idea');
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
        case 'big_idea':
          if ( cyco_core_current_user_has_role( 
                array('author', 'administrator', 'grader', 'reviewer') 
              ) ) {
            //List Big Ideas.
            $item = menu_get_item('big-ideas');
            $item['title'] = t('List Big Ideas');
            $data['actions']['output'][] = array(
              '#theme' => 'menu_local_action',
              '#link' => $item,
            );
          }
          if ( cyco_core_current_user_has_role( array('author', 'administrator') ) ) {
            //Link to add Big Idea.
            $item = menu_get_item('node/add/big-idea');
            $item['title'] = t('Add Big Idea');
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
 * Callback to generate HTML for the big idea.
 * @param string $big_idea_internal_name Big idea internal name.
 * @param string $tag_content Inner tag content. Not used.
 */
function _cyco_big_ideas_swim_callback( $big_idea_internal_name, $tag_content ) {
  $big_idea_nid = cyco_core_nid_for_internal_name( $big_idea_internal_name );
  if ( is_null($big_idea_nid) ) {
    //Error already reported in function. 
    return '';
  }
  //Exit if not found.
  if ( $big_idea_nid == 0 ) {
    if ( variable_get('cyco_core_log_notices', FALSE) ) {
      $message = t('Not found big idea internal name: @name', 
          array('@name' => $big_idea_internal_name));
      watchdog('cyco_big_idea', $message);
    }
    return '';
  }
  $big_idea_node = node_load($big_idea_nid);
  if ( ! $big_idea_node->status ) {
    if ( variable_get('cyco_core_log_notices', FALSE) ) {
      $message = t('Tried to show unpublished big idea: @name (@nid)', 
          array('@name' => $big_idea_internal_name, '@nid' => $big_idea_nid)
          );
      watchdog('cyco_big_idea', $message);
    }
    return '';    
  }
  //Make sure that this is the right type of node.
  if (   $big_idea_node == FALSE 
      || !node_access('view', $big_idea_node) 
      || $big_idea_node->type != 'big_idea') {
    $message = t('Invalid big_idea id: @id', array('@id' => $big_idea_nid) );
    $message = __FILE__ . ' (line ' . __LINE__ . ') ' . __FUNCTION__ 
        . $message;
    cyco_core_handle_error( $message );
    return '<p>' . $message . '</p>';
  }
  $summary = 
      isset( 
        $big_idea_node->field_body[LANGUAGE_NONE][0]['summary']
      ) 
      ? swim_textile2html(
          $big_idea_node->field_body[LANGUAGE_NONE][0]['summary'],
          TRUE //Flag as embedded call (swim_textile2html w/in swim_textile2html),
           //to avoid Certain Things.
        )
      : '';
  //Make big_idea category links.
  $big_idea_keyword_links = array();
  $big_idea_keyword_links_rendered = '';
  if ( sizeof( $big_idea_node->field_keywords ) > 0 ) {
    $done_first = FALSE;
    foreach ($big_idea_node->field_keywords[LANGUAGE_NONE] as $item) {
      $tid = $item['tid'];
      $term = taxonomy_term_load($tid);
      $term_name = $term->name;
      $big_idea_keyword_links[] = array('tid' => $tid, 'term' => $term_name);
      $path_to_term = drupal_lookup_path('alias', 'taxonomy/term/' . $tid);
      $link_html = l($term_name, $path_to_term );
      if ( $done_first ) {
        $big_idea_keyword_links_rendered .= ', ';
      }
      $done_first = TRUE;
      $big_idea_keyword_links_rendered .= $link_html;
    }
  }
  $result = theme('big_idea_inserted', 
      array(
        'title' => $big_idea_node->title,
        'keyword_links' => $big_idea_keyword_links,
        'keyword_links_rendered' => $big_idea_keyword_links_rendered,
        'summary' => $summary,
        'more_link_destination' => '/node/' . $big_idea_nid,
        'big_idea_node' => $big_idea_node,
      )
  );
  return $result;
}

/**
 * Implements hook_form_FORM_alter().
 * 
 * Mess with the big idea node edit form.
 */
function cyco_big_ideas_form_big_idea_node_form_alter( &$form, $form_state ) {
  //Supress author and book options for all users except admins.
  if ( ! cyco_core_current_user_has_role(array('administrator')) ) {
    $form['author']['#access'] = FALSE;
    $form['book']['#access'] = FALSE;
  }
  //Add validation of internal name.
  $form['#validate'][] = '_cyco_big_idea_form_validate';
}

function _cyco_big_idea_form_validate($form, &$form_state) {
  //Check format of internal name.
  cyco_core_validate_internal_name_field($form_state);
}

/**
 * Return CSS file to show pseudent in peek.
 */
function cyco_big_ideas_swim_peek_load_css() {
  global $base_url;
  $result = array(
    $base_url . base_path() . drupal_get_path('module', 'cyco_big_ideas') 
      . '/custom/css/cyco_big_ideas.css',
  );
  return $result;
}

/**
 * Implements hook_node_view().
 */
function cyco_big_ideas_node_view($node, $view_mode, $langcode) {
  if ( module_exists('cyco_events_log') 
      && _cyco_events_log_should_log_events() 
      && $view_mode == 'full') {
    if ( $node->type == 'big_idea' ) {
      cyco_events_log_log_node_view($node, $view_mode, $langcode);
    }
  }
}

/**
 * Alter edit forms for nodes a big idea can be embedded in. 
 * Register the big idea node type and tag, so SWIM will
 * update refs to where a BI is embedded when it saves 
 * the BI node.
 */
function cyco_big_ideas_form_node_form_alter(&$form, $form_state) {
  $types_exers_can_be_embedded = array('course_page', 'blueprint_page', 'page');
  if ( in_array($form['#node']->type, $types_exers_can_be_embedded) ) {
    swim_register_embedded_refs_tag($form, 'big_idea', 'big-idea');
  }
}
