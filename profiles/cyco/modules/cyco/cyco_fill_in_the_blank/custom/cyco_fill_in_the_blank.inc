<?php
/**
 * Implements hook_help().
 * @todo Write patterny help in hook_help.
 */
function cyco_fill_in_the_blank_help($path, $arg) {
  switch ($path) {
    case 'admin/help#cyco_fill_in_the_blank':
      return '<p>' . t('Helpy helpy help help, <a href="@jquery">jQuery</a>.', 
          array(
            '@jquery' => 'http://jquery.com',
          )) . '</p>';
  }
}

/**
 * Implements hook_swim_custom_tag_view_info().
 */
function cyco_fill_in_the_blank_swim_custom_tag_view_info() {
  return array(
    'tag' => 'fill-in-the-blank',
    'callback' => '_cyco_fill_in_the_blank_swim_callback',
  );
}

/**
 * Implement hook_theme().
 */
function cyco_fill_in_the_blank_theme() {
  $result = array(
    'fill_in_the_blank_inserted' => array(
      'template' => 'custom/cyco-fill-in-the-blank-insert',
      //Default variable values
      'variables' => array(
        'fill_in_the_blank_nid' => '',
        'response_type' => '',
        'title' => '(no title)',
        'body' => '(no body)',
        'hints' => '',
        'explanation' => '',
      ),
    ),
  );
  return $result;
}

/**
 * Implements hook_menu_local_tasks_alter
 */
function cyco_fill_in_the_blank_menu_local_tasks_alter(&$data, $router_item, $root_path) {
  switch ($root_path) {
    case 'fill-in-the-blanks':
      if ( cyco_core_current_user_has_role( array('author', 'administrator') ) ) {
        //Link to add fib.
        $item = menu_get_item('node/add/fill-in-the-blank');
        $item['title'] = t('Add fill-in-the-blank');
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
      if ( $node->type == 'fill_in_the_blank' ) {
          $item = menu_get_item('node/add/fill-in-the-blank');
          $item['title'] = t('Add fill-in-the-blank');
          $data['actions']['output'][] = array(
            '#theme' => 'menu_local_action',
            '#link' => $item,
          );
          $item = menu_get_item('fill-in-the-blanks');
          $item['title'] = t('List fill-in-the-blanks');
          $data['actions']['output'][] = array(
            '#theme' => 'menu_local_action',
            '#link' => $item,
          );
          break;
      }
  }
}

/**
 * Callback to generate HTML for the question.
 * @param string $fib_internal_name question internal name.
 * @param string $tag_content Inner tag content. Not used.
 */
function _cyco_fill_in_the_blank_swim_callback( $fib_internal_name, $tag_content ) {
  $fib_nid = cyco_core_nid_for_internal_name( $fib_internal_name );
  if ( is_null($fib_nid) ) {
    //Error already reported in function. 
    return '';
  }
  if ( $fib_nid == 0 ) {
    $message = t('Not found fill-in-the-blank internal name: @name', 
        array('@name' => $fib_internal_name));
    watchdog('cyco_fill_in_the_blank', $message);
    return '';
  }
  $fib_node = node_load($fib_nid);
  if ( ! $fib_node->status ) {
    $message = t('Tried to show unpublished fill-in-the-blank: @name (@nid)', 
        array('@name' => $fib_internal_name, '@nid' => $fib_nid)
        );
    watchdog('cyco_fill_in_the_blank', $message);
    return '';    
  }
  //Make sure that this is the right type of node.
  if (   $fib_node == FALSE 
      || !node_access('view', $fib_node) 
      || $fib_node->type != 'fill_in_the_blank') {
    $message = t('Invalid fill-in-the-blank id: @id', array('@id' => $fib_nid) );
    $message = __FILE__ . ' (line ' . __LINE__ . ') ' . __FUNCTION__ 
        . $message;
    cyco_core_handle_error( $message );
    return '<p>' . $message . '</p>';
  }
  $body = 
        isset( $fib_node->field_body[LANGUAGE_NONE][0]['value'] )
      ? swim_textile2html(
          $fib_node->field_body[LANGUAGE_NONE][0]['value'],
          TRUE //Flag as embedded call (swim_textile2html w/in swim_textile2html),
           //to avoid Certain Things.
        )
      : '';
  $hints = 
        isset( $fib_node->field_hints[LANGUAGE_NONE][0]['value'] )
      ? swim_textile2html( 
          $fib_node->field_hints[LANGUAGE_NONE][0]['value'],
          TRUE //Flag as embedded call (swim_textile2html w/in swim_textile2html),
               //to avoid Certain Things.
        )
      : '';
  $explanation = 
        isset( $fib_node->field_explanation[LANGUAGE_NONE][0]['value'] )
      ? swim_textile2html( 
          $fib_node->field_explanation[LANGUAGE_NONE][0]['value'],
          TRUE //Flag as embedded call (swim_textile2html w/in swim_textile2html),
               //to avoid Certain Things.
        )
      : '';
  $response_type = $fib_node->field_response_type[LANGUAGE_NONE][0]['value'];
  $result = theme('fill_in_the_blank_inserted', 
      array(
        'fill_in_the_blank_nid' => $fib_nid,
        'response_type' => $response_type,
        'title' => $fib_node->title,
        'body' => $body,
        'hints' => $hints,
        'explanation' => $explanation,
      )
  );
  //Add CSS
  $path = drupal_get_path('module', 'cyco_fill_in_the_blank')
      . '/custom/css/cyco_fib_ask_question.css';
  drupal_add_css($path);
  //Include JS.
  $path = drupal_get_path('module', 'cyco_fill_in_the_blank')
      . '/custom/js/cyco_fib_ask_question.js';
  drupal_add_js($path);
  //Add stuudent UID.
  global $user;
  //Send current user uid to client.
  drupal_add_js(
      array('cycoFib' => 
        array(
          'studentUid' => $user->uid,
        ),
      ),
      'setting'
  );
  return $result;
}

/**
 * Implements hook_form_FORM_alter().
 * 
 * Mess with the pattern node edit form.
 */
function cyco_fill_in_the_blank_form_fill_in_the_blank_node_form_alter( &$form, $form_state ) {
  //Supress author and book options for all users except admins.
  if ( ! cyco_core_current_user_has_role(array('administrator')) ) {
    $form['author']['#access'] = FALSE;
    $form['book']['#access'] = FALSE;
  }
  //Add validation of internal name.
  $form['#validate'][] = '_cyco_fill_in_the_blank_form_validate';
  //Include JS for editing.
  global $base_url;
  $path = $base_url . '/' . drupal_get_path('module', 'cyco_fill_in_the_blank')
      . '/custom/js/cyco_fib_edit_form.js';
  drupal_add_js($path);
}

function _cyco_fill_in_the_blank_form_validate($form, &$form_state) {
  //Check format of internal name.
  cyco_core_validate_internal_name_field($form_state);
}

/**
 * Implements hook_node_view().
 */
function cyco_fill_in_the_blank_node_view($node, $view_mode, $langcode) {
  if ( module_exists('cyco_events_log') && $view_mode == 'full') {
    if ( $node->type == 'fill_in_the_blank' ) {
      cyco_events_log_log_page_view();
    }
  }
}

/**
 * Implements hook_form_alter.
 */
function cyco_fill_in_the_blank_form_node_form_alter(&$form, $form_state) {
  // Alter some edit forms. Registier fill-in-the-blank tag for code that updates
  // references from embedded nodes to the nodes in which they are embedded.
  $types_exers_can_be_embedded = array('course_page', 'blueprint_page', 'page');
  if ( in_array($form['#node']->type, $types_exers_can_be_embedded) ) {
    swim_register_embedded_refs_tag($form, 'fill_in_the_blank', 'fill-in-the-blank');
  }
}

function cyco_fill_in_the_blank_views_pre_render(&$view) {
  if ( $view->name == 'fill_in_the_blanks' ) {
    $path = drupal_get_path('module', 'cyco_fill_in_the_blank')
      . '/custom/css/cyco_fib_view.css';
    drupal_add_css($path);

  }
}