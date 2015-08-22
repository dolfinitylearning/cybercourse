<?php
/**
 * @file
 * Implements the way kewl pseudent thing.
 */

require_once drupal_get_path('module', 'swim') . '/SwimCustomTagParser.php';

/**
 * Flag showing whether the poses preview data (used with CKEditor) is dirty.
 */
define('POSES_PREVIW_DIRTY_FLAG_VAR', 'pseudents_poses_preview_dirty');
/**
 * Poses preview data used with CKEditor.
 */
define('POSES_PREVIEW_DATA_VAR', 'pseudents_poses_preview_data');

/**
 * Implements hook_help().
 */
function cyco_pseudents_help($path, $arg) {
  switch ($path) {
      // Help for another path in the block module
    case 'admin/help#cyco_pseudents':
      return '<p>' . t('See the <a href="@">wiki</a> for help with pseudents.', 
          array(
            '@jquery' => 'https://wiki.cybercour.se',
          )) . '</p>';
  }
}

function cyco_pseudents_menu() {
  $items = array();
  $items['admin/config/cyco/cyco-pseudents'] = array(
    'title' => 'Pseudents',
    'description' => 'Pseudents configuration',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('_cyco_pseudents_admin_form'),
    'access arguments' => array('administer pseudents'),
  );
  return $items;
}

function _cyco_pseudents_admin_form($form, &$form_state) {
  $form['clear_cache'] = array(
    '#type' => 'submit',
    '#value' => t('Clear pseudent cache'),
    '#submit' => array('cyco_pseudents_flush_cache'),
  );  
  return $form;
}

function cyco_pseudents_flush_cache() {
  _cyco_pseudents_generate_ck_pseudent_table();
  drupal_set_message( t('Pseudent cache cleared.') );
  drupal_goto('admin/config/cyco/cyco-pseudents');
}

/**
 * Register the CKEditor plugin.
 */
function cyco_pseudents_swim_load_ck_plugins() {
  //Only add plugin if the user is allowed to create course page
  //content.
  if ( user_access( 'create course_page content' ) ) {
    global $base_url;
    $result = array(
      'name' => 'insert_pseudent',
      'path' => $base_url . '/' . drupal_get_path('module', 'cyco_pseudents') 
          . '/custom/ck_plugins/insert_pseudent/',
    );
    return $result;
  }
}

/**
 * Return CSS file to show pseudent in peek.
 */
function cyco_pseudents_swim_peek_load_css() {
  global $base_url;
  $result = array(
    $base_url . base_path() . drupal_get_path('module', 'cyco_pseudents') 
      . '/custom/css/cyco_pseudents.css',
  );
  return $result;
}

/**
 * Implementation of hook_perm().
 */
function cyco_pseudents_permission() {
  return array(
    'administer pseudents' => array(
      'title' => t('Administer pseudents'),
      'description' => t('Create, delete, and update pseudents.')
    ),
  );
}


function cyco_pseudents_get_editor_previews() {
  $pseudents_preview_dirty = variable_get(POSES_PREVIW_DIRTY_FLAG_VAR, TRUE);
  if ( $pseudents_preview_dirty ) {
    _cyco_pseudents_generate_ck_pseudent_table();
  }
  return variable_get(POSES_PREVIEW_DATA_VAR, 'none');
}

/**
 * Generate HTML for a table of pseudent poses to use in a CKEditor dialog.
 * The result is cached. 
 */
function _cyco_pseudents_generate_ck_pseudent_table() {
  //Fetch pseudent pose data.
  $query = new EntityFieldQuery;
  $query
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'pseudent_pose')
    ->propertyCondition('status', 1)
    ->propertyOrderBy('title');
  $query_result = $query->execute();
  //Create the pseudent HTML.
  $pseudents = array();
  if ( isset($query_result['node']) ) {
    //Get term names.
    $term_names = _cyco_pseudents_load_category_terms();
    foreach ( $query_result['node'] as $nid => $value ) {
      $node = node_load($nid);
      $title = $node->title;
      //Caption is not a required field.
      if ( isset($node->field_caption[LANGUAGE_NONE][0]['safe_value']) ) {
        $caption = $node->field_caption[LANGUAGE_NONE][0]['safe_value'];
      }
      else {
        $caption = $node->title;
      }
      $categories = array();
      if ( isset($node->field_pseudent_categories[LANGUAGE_NONE]) ) {
        foreach ( $node->field_pseudent_categories[LANGUAGE_NONE] as $term ) {
          $categories[ $term['tid'] ] = $term_names[ $term['tid'] ];
        }
      }
      $usable_url = NULL;
      if ( isset( $node->field_image[LANGUAGE_NONE][0]['uri'] ) ) {
        $usable_url = cyco_core_uri2path(
            $node->field_image[LANGUAGE_NONE][0]['uri']
        );
      }
      $internal_name = $node->field_internal_name[LANGUAGE_NONE][0]['value'];
      if ( !is_null($usable_url) ) {
        $pseudents[$internal_name] = array(
          'nid' => $nid,
          'internal_name' => $internal_name,
          'title' => $title,
          'url' => $usable_url,
          'caption' => $caption,
          'categories' => $categories,
        );
      }
    } // end for
  }
  if ( $pseudents == '' ) {
    variable_set(POSES_PREVIEW_DATA_VAR, 'none');
  }
  else {
    variable_set( POSES_PREVIEW_DATA_VAR, $pseudents );
  }
  variable_set(POSES_PREVIW_DIRTY_FLAG_VAR, FALSE);
}

/** 
 * Find the names of all the terms in the pseudent_categories vocab.
 * 
 * @return array Term names, indexed by term id
 */
function _cyco_pseudents_load_category_terms() {
  $name = 'pseudent_categories';
  $myvoc = taxonomy_vocabulary_machine_name_load($name);
  $tree = taxonomy_get_tree($myvoc->vid);
  $term_names = array();
  foreach ($tree as $term) {
   $term_names[ $term->tid ] = $term->name;
  }
  return $term_names;
}

/*
 * Set 'cache is dirty' flag when poses change.
 */
function cyco_pseudents_node_update( $node ) {
  _cyco_pseudents_set_dirty_flag( $node );
}

function cyco_pseudents_node_delete( $node ) {
  _cyco_pseudents_set_dirty_flag( $node );
}

function cyco_pseudents_node_insert( $node ) {
  _cyco_pseudents_set_dirty_flag( $node );
}

function _cyco_pseudents_set_dirty_flag( $node ) {
  if ( $node->type == 'pseudent_pose' ) {
    //Mark pseudent pose preview data used in editor as dirty.
    variable_set(POSES_PREVIW_DIRTY_FLAG_VAR, TRUE);
  }  
}

/** 
 * Implements hook_form_alter().
 */
function cyco_pseudents_form_alter(&$form, &$form_state, $form_id) {
  // @todo Instead of checking form_id, check for a field
  //having the SWIM format? Cache the results of the check 
  //so don't run check again on this page call.
  //Not sure if this is the right approach.
  if ( strpos($form_id, 'node_form') !== FALSE ) {
    _cyco_pseudents_load_client_side_stuff();
  }
  if ( $form_id == 'pseudent_pose_node_form' ) {
    //Add validation of internal name.
    $form['#validate'][] = '_cyco_pseudents_form_validate';    
  }
}

function _cyco_pseudents_form_validate($form, &$form_state) {
  //Check format of internal name.
  cyco_core_validate_internal_name_field($form_state);
}

/**
 * Add client-side stuff the pseudent code needs.
 */
function _cyco_pseudents_load_client_side_stuff() {
  //Only run this once per page.
  static $already_added = FALSE;
  if ( $already_added ) {
    return;
  }
  $already_added = TRUE;
  drupal_add_css( drupal_get_path('module', 'cyco_pseudents') 
      . '/custom/css/cyco_pseudents.css' );
  global $base_url;
  $css_path = $base_url . '/' . drupal_get_path('module', 'cyco_pseudents') 
      . '/custom/css/';
  $settings = array(
    'posePreviews' => cyco_pseudents_get_editor_previews(),
    'poseStylesheet' => $css_path . 'cyco_pseudents.css',
    'poseStylesheetEdit' => $css_path . 'cyco_pseudents_edit.css',
  );
  drupal_add_js(
      array('pseudents' => $settings),
      'setting'
  );
  //Add slimy hack to remove extra <br> afore pseudents.
  $module_path = drupal_get_path('module', 'cyco_pseudents');
  drupal_add_js( $module_path . '/custom/js/extra_br_slimy_hack.js');
}

/**
 * Implement hook_swim_add_client_stuff().
 * 
 * SWIM calls this to let modules load their own client-side stuff.
 */
function cyco_pseudents_swim_add_client_stuff() {
  _cyco_pseudents_load_client_side_stuff();
}

/**
 * Implements hook_ckeditor_plugin().
 * @return array Definitions.
 */
function cyco_pseudents_ckeditor_plugin() {
  $definition = 
    array(
      'pseudents' => array(
        // Plugin name.
        'name' => 'Pseudents',
        // Plugin description.
        'desc' => t('Add a pseudent.'),
        // The full path to the CKEditor plugin directory, trailing slash included.
        'path' => drupal_get_path('module', 'cyco_pseudents') 
                  . '/custom/ck_plugins/insert_pseudent/',
         )
    );
  return $definition;
}

/**
 * Implements hook_menu_local_tasks_alter
 */
function cyco_pseudents_menu_local_tasks_alter(&$data, $router_item, $root_path) {
  switch ($root_path) {
    case 'pseudent-poses':
      if ( cyco_core_current_user_has_role( array('author', 'administrator') ) ) {
        //Link to add pseudent.
        $item = menu_get_item('node/add/pseudent-pose');
        $item['title'] = t('Add pseudent pose');
        $data['actions']['output'][] = array(
          '#theme' => 'menu_local_action',
          '#link' => $item,
        );
      }
      break;
    case 'node/%':
      if ( isset($router_item['map'][1]->type) 
          && $router_item['map'][1]->type == 'pseudent_pose' ) {
        if ( cyco_core_current_user_has_role( array('author', 'administrator') ) ) {
          //Link to pseudent list.
          $item = menu_get_item('pseudent-poses');
          $item['title'] = t('List pseudent poses');
          $data['actions']['output'][] = array(
            '#theme' => 'menu_local_action',
            '#link' => $item,
          );
          //Link to add pseudent.
          $item = menu_get_item('node/add/pseudent-pose');
          $item['title'] = t('Add pseudent pose');
          $data['actions']['output'][] = array(
            '#theme' => 'menu_local_action',
            '#link' => $item,
          );
          }
      }
      break;
  }//End switch
}

/**
 * Implements hook_swim_tag_info().
 * 
 * Defines a custom tag for adding pseudents.
 * 
 * @return string Name of the tag.
 */
function cyco_pseudents_swim_tag_info() {
  return 'pseudent';
}

/**
 * Implements hook_swim_custom_tag_view_info().
 */
function cyco_pseudents_swim_custom_tag_view_info() {
  return array(
    'tag' => 'pseudent',
    'callback' => '_cyco_pseudents_swim_view_callback',
  );
}

/**
 * Callback to generate HTML for the pseudent custom tag.
 * @param int $pseudent_nid Exercise node nid.
 * @param string $tag_content Inner tag content. Not used.
 */
function _cyco_pseudents_swim_view_callback( $pseudent_internal_name, $tag_content ) {
  $template = 
'<div class="pseudent" data-pseudent-internal-name="**INTERNAL_NAME**">
  <div class="pseudent-image-container">
    <img class="pseudent-image" src="**IMAGE_PATH**"" alt="**CAPTION**">
    <div class="pseudent-image-caption">**CAPTION**</div>
  </div>
  <div class="pseudent-content">**CONTENT**</div>
</div>';
  $pseudent_nid = cyco_core_nid_for_internal_name( $pseudent_internal_name );
  if ( is_null($pseudent_nid) ) {
    //Error already reported in function. 
    return '';
  }
  if ( $pseudent_nid == 0 ) {
    $message = t('Not found pseudent internal name: @name', 
        array('@name' => $pseudent_internal_name));
    watchdog('cyco_pseudent', $message);
    return '';
  }
  $pseudent_node = node_load($pseudent_nid);
  if ( isset( $pseudent_node->field_caption[LANGUAGE_NONE][0]['value'] ) ) {
    $caption = $pseudent_node->field_caption[LANGUAGE_NONE][0]['value'];
  }
  else {
    $caption = $pseudent_node->title;
  }
  //Get the path to the pseudent's image file.
  $usable_url = cyco_core_uri2path(
      $pseudent_node->field_image[LANGUAGE_NONE][0]['uri']
  );
  $internal_name = $pseudent_node->field_internal_name[LANGUAGE_NONE][0]['value'];
  //Use template.
  $replacement = str_replace('**INTERNAL_NAME**', $internal_name, $template);
  $replacement = str_replace('**CAPTION**', $caption, $replacement);
  $replacement = str_replace('**CONTENT**', $tag_content, $replacement);
  $replacement = str_replace('**IMAGE_PATH**', $usable_url, $replacement);
  //Return to sen-der.
  return $replacement;
}

/**
 * Implements hook_swim_custom_tag_edit_info().
 */
function cyco_pseudents_swim_custom_tag_edit_info() {
  $definition = array(
    'tag' => 'pseudent',
    'callback' => '_cyco_pseudents_swim_edit_callback',
  );
  return $definition;
}

/**
 * Implements hook_swim_textile2ckhtml.
 */
function _cyco_pseudents_swim_edit_callback( $pseudent_internal_name, $content ) {
  $pseudent_nid = cyco_core_nid_for_internal_name( $pseudent_internal_name );
  if ( is_null($pseudent_nid) ) {
    //Error already reported in function. 
    return '';
  }
  //Exit if not found.
  if ( $pseudent_nid == 0 ) {
    $message = t('Not found pseudent internal name: @name', 
        array('@name' => $pseudent_internal_name));
    watchdog('cyco_pseudents', $message);
    return '';
  }
  //Load pseudent data.
  $node = node_load($pseudent_nid);
  if ( !$node ) {
    $message = __FILE__ . ' (line ' . __LINE__ . ') ' . __FUNCTION__ 
        . ' bad nid: ' . $pseudent_nid;
    cyco_core_handle_error( $message );
    return;
  }
  $caption = '';
  if ( isset( $node->field_caption[LANGUAGE_NONE][0]['value'] ) ) {
    $caption = $node->field_caption[LANGUAGE_NONE][0]['value'];
  }
  else {
    $caption = $node->title;
  }
  $usable_url = cyco_core_uri2path(
     $node->field_image[LANGUAGE_NONE][0]['uri']
  );
  //brs add spacing to reduce problems with not being able to
  //put cursor before/after pseudent block.
  $html =   '<div class="pseudent" data-pseudent-internal-name="' 
          .       $pseudent_internal_name . '" >'
          .   '<div class="pseudent-image-container">'
          .     '<img class="pseudent-image" '
          .         'src="' . $usable_url . '" '
          .         'alt="' . $caption . '" >'
          .     '<div class="pseudent-image-caption">' 
          .       $caption
          .     '</div>'
          .   '</div>'
          .   '<div class="pseudent-content">' . $content . '</div>'
          . '</div>';
  return $html;
}

/**
 * Implements hook_swim_ckhtml2textile_alter().
 * @param string $content Content to change.
 */
function cyco_pseudents_swim_ckhtml2textile_alter( &$content ) {
  $regex = 
      '/\<div class\=\"pseudent\".*?data\-pseudent\-internal\-name\=\"(.*?)\"*.\>\s*'
      .  '\<div class\=\"pseudent\-image\-container\"\>\s*'
      .    '\<img.*?\>\s*'
      .    '\<div class\=\"pseudent-image-caption\"\>.*?\<\/div\>\s*'
      .  '\<\/div\>\s*'
      .  '\<div class=\"pseudent\-content\"\>(.*?)\<\/div\>\s*'
      . '\<\/div\>/is';
    //? for lazy eval.
    //s option to include new lines in whitespace matches.
  //NB: does not include last \n.
  $content
    = preg_replace_callback($regex, '_cyco_pseudents_make_textile_replacements', $content);
}

function _cyco_pseudents_make_textile_replacements($matches) {
  $internal_name = $matches[1];
  $content = $matches[2];
  //May have extra <p></p> wrapped around content.
  $content = trim($content);
//  if ( substr($content, 0, 3) == '<p>' && substr($content, -4, 4) == '</p>' ) {
//    $content = substr($content, 3, strlen($content) - 7 );
//  }
  $replacement = 
    SwimCustomTagParser::START_CUSTOM_TAG . ' pseudent ' . $internal_name . "\n"
      . $content . "\n"
      . SwimCustomTagParser::END_CUSTOM_TAG . ' pseudent ' . $internal_name;
  return $replacement;
}