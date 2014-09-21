<?php
/**
 * @file
 * Process callback for hook_filter. Finds [[[cycopattern (node_id)]]]
 * and passes match data onto function that will do the insertion.
 */

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
function cyco_patterns_node_view($node, $view_mode, $langcode) {
  if ( $node->type == 'pattern' && $view_mode == 'full' ) {
    if ( user_access('edit any pattern content') ) {
      drupal_set_title( $node->title . ' (' . $node->nid . ')' );
    }
  }
}

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
  }
}

/**
 * Callback to generate HTML for the pattern.
 * @param int $pattern_nid Pattern node nid.
 * @param string $tag_content Inner tag content. Not used.
 */
function _cyco_patterns_swim_callback( $pattern_nid, $tag_content ) {
  $pattern_node = node_load($pattern_nid);
  //Make sure that this is the right type of node.
  if (   $pattern_node == FALSE 
      || !node_access('view', $pattern_node) 
      || !$pattern_node->status
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
          $pattern_node->field_situation[LANGUAGE_NONE][0]['value']
        )
      : '';
  $actions = 
      isset( 
        $pattern_node->field_actions[LANGUAGE_NONE][0]['value'] 
      )
      ? swim_textile2html( 
          $pattern_node->field_actions[LANGUAGE_NONE][0]['value']
        )
      : '';
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
  $result = theme('pattern_inserted', 
      array(
        'title' => $pattern_node->title,
        'category_links' => $pattern_category_links,
        'category_links_rendered' => $pattern_category_links_rendered,
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
