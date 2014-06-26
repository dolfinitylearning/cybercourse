<?php
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
      return '<p>' . t('Helpy help help, <a href="@jquery">jQuery</a>.', 
          array(
            '@jquery' => 'http://jquery.com',
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
//function cyco_pseudents_ckeditor_plugin() {
//  return array(
//    'pseudent' => array(
//      // Plugin name.
//      'name' => 'pseudent',
//      // Plugin description - it will be displayed in the plugins management section of the profile settings.
//      'desc' => t('Cyco: Insert a pseudent into content.'),
//      // The full path to the CKEditor plugin directory, trailing slash included.
//      'path' => drupal_get_path('module', 'cyco_pseudents') . '/custom/ck_plugins/',
//    )
//  );
//}

function cyco_pseudents_swim_load_ck_plugins() {
  global $base_url;
  $result = array(
    'name' => 'insert_pseudent',
    'path' => $base_url . '/' . drupal_get_path('module', 'cyco_pseudents') 
        . '/custom/ck_plugins/insert_pseudent/',
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
//    'use pseudents in content' => array(
//      'title' => t('Use pseudents in content'),
//      'description' => t('Insert pseudent token in content.')
//    ),
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
      $renderable_array = field_view_field(
          'node', $node, 'field_notes', 'swim_summary_or_trimmed_formatter'
      );
      $notes = drupal_render( $renderable_array );
      //Caption is not a required field.
      if ( isset($node->field_caption[LANGUAGE_NONE][0]['safe_value']) ) {
        $caption = $node->field_caption[LANGUAGE_NONE][0]['safe_value'];
      }
      else {
        $caption = $node->title;
      }
      $categories = array();
      if ( isset($node->field_pseudent_categories[LANGUAGE_NONE]) ) {
        foreach( $node->field_pseudent_categories[LANGUAGE_NONE] as $term ) {
          $categories[ $term['tid'] ] = $term_names[ $term['tid'] ];
        }
      }
      $usable_url = cyco_core_uri2path(
          $node->field_image[LANGUAGE_NONE][0]['uri']
      );
      $pseudents[$nid] = array(
        'nid' => $nid,
        'title' => $title,
        'url' => $usable_url,
        'caption' => $caption,
        'categories' => $categories,
      );
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

function cyco_pseudents_form_alter(&$form, &$form_state, $form_id) {
  // @todo Instead of checking form_id, check for a field
  //having the SWIM format? Cache the results of the check 
  //so don't run check again on this page call.
  //Not sure if this is the right approach.
  if ( strpos($form_id, 'node_form') !== FALSE ) {
    _cyco_pseudents_load_client_side_stuff();
  }
  if ( $form_id == 'pseudent_pose_node_form' ) {
    $form['pseudent_pose_link'] = array(
        '#type' => 'markup',
        '#markup' => _cyco_pseudents_make_link2list(),
        '#weight' => ( $form['field_notes']['#weight'] + 1 ),
    );    
  }
}

/**
 * Make a link back to the pseudent list page.
 */
function _cyco_pseudents_make_link2list() {
  return 
        '<div class="pseudents-back-link">'
      .   l(
            '<< Back to pseudents list', 
            'pseudent-poses'
          )
      . '</div>';  
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
 * Implements hook_swim_ckhtml2rest_alter().
 * @param string $content Content to change.
 */
function cyco_pseudents_swim_ckhtml2rest_alter( &$content ) {
  $regex = 
      '/\<div class\=\"pseudent\".*?data\-pseudent\-id\=\"(.*?)\"*.\>\s*'
      .  '\<div class\=\"pseudent\-image\-container\"\>\s*'
      .    '\<img.*?\>\s*'
      .    '\<div class\=\"pseudent-image-caption\"\>.*?\<\/div\>\s*'
      .  '\<\/div\>\s*'
      .  '\<div class=\"pseudent\-content\"\>(.*?)\<\/div\>\s*'
      . '\<\/div\>/is';
    //? for lazy eval.
    //s option to include new lines in whitespace matches.
  $content
    = preg_replace_callback($regex, '_cyco_pseudents_make_directive_replacements', $content);
}

function _cyco_pseudents_make_directive_replacements($matches) {
  $nid = $matches[1];
  $content = $matches[2];
  //Add four spaces after every new line in the content, because indentation
  //is significant in ReST.
  $content = str_replace("\n", "\n    ", $content);
  $replacement = 
      '.. pseudent:: ' . $nid . "\n\n"
    . ' ' . $content . "\n\n";
  return $replacement;
}

/**
 * Replace .. pseudent:: directives with betwixt tag, used later to 
 * add HTML tags CK uses. Note: betwixt tags can't have spaces that the user
 * didna' type.
 * @param string $content Da goods, ReSTy.
 */
function cyco_pseudents_swim_rest2betwixt_alter( &$content ) {
  $rest_tags = array();
  $pattern = '/\.\.\s+pseudent\:\:\s+(\d+).*\r?\n/i';
  preg_replace_callback(
      $pattern, 
      function ($matches) use (&$rest_tags) {
        //Got one.
        $rest_tags[] = array(
          'tag' => $matches[0],
          'nid' => $matches[1],
        );
      },
      $content
  );
  if ( sizeof($rest_tags) == 0 ) {
    //Didna' find nuthin', lass.
    return;
  }
  //Count of ReST tags found so far.
  $rest_tag_count = 0;
  foreach ( $rest_tags as $rest_tag ) {
    //Find position of the rest directive tag.
    $rest_tag_start = stripos($content, $rest_tag['tag']);
    //Remove the directive from the content.
    $content = substr($content, 0, $rest_tag_start) 
        . substr( $content, $rest_tag_start + strlen($rest_tag['tag']) );
    //Find the next line that isn't indented.
    $search_start = $rest_tag_start;
    $done = false;
    while( ! $done ) {
      list( $break_pos, $break_length) 
          = cyco_core_find_next_line_break($content, $search_start);
      if ( $break_pos == -1 ) {
        //Not found. Formula goes to the end of the content.
        $rest_tag_end = strlen( $content ) - 1;
        $done = TRUE;
      }
      else if ( ($break_pos + $break_length) >= strlen($content) )  {
        //Line break is at the end of string.
        $rest_tag_end = strlen( $content ) - 1;
        $done = TRUE;
      }
      else {
        $next_char = substr($content, $break_pos + $break_length, 1);
        if ( ! ctype_space($next_char) ) {
          //Line starts with non-whitespace, so not indented. It's the end.
          $rest_tag_end = $break_pos + $break_length - 1;
          $done = TRUE;
        }
      }
      $search_start = $break_pos + $break_length;
    }
    //$rest_tag_end points to char after the whitespace that ended
    //the content. We don't want that. Work backwards until hit a
    //non-whitespace char. That's the real end of the content.
    $content_end = $rest_tag_end;
    while ( ctype_space( substr($content, $content_end, 1 ) ) ) {
      $content_end --;
    }
    //Do the same for the start tag.
    $content_start = $rest_tag_start;
    while ( ctype_space( substr($content, $content_start, 1 ) ) ) {
      $content_start ++;
    }
    //Grab the ReST tag's content.
    $rest_tag_content 
        = substr($content, 
                 $content_start, 
                 $content_end - $content_start + 1
          );
    //Construct the betwixt.
    $replacement = '[[[cycopseudent:' . $rest_tag['nid'] . '|||'
        . $rest_tag_content . ']]]' . PHP_EOL;
        //Add the EOL because one was eaten by the regex.
    //Replace directive in content with betwixt. Using $rest_tag_start/end
    //in the replacement, so that the whitespace that separated the pseudent
    //content from the other ReST tags is replaced, too. 
    $content = substr($content, 0, $rest_tag_start) 
        . $replacement . substr($content, $rest_tag_end + 1);
    $rest_tag_count++;
  } //End foreach.
}

/*
 * Implements hook_swim_betwixt2ckhtml_alter().
 * 
 * This doesn't set the pseudent category - that information is not stored
 * in the DB.
 */
function cyco_pseudents_swim_betwixt2ckhtml_alter( &$content ) {
  $template = <<<EOT
<div class="pseudent" data-pseudent-id="**NID**">
  <div class="pseudent-image-container">
    <img class="pseudent-image" src="**IMAGE_PATH**" />
    <div class="pseudent-image-caption">**CAPTION**</div>
  </div>
  <div class="pseudent-content">**CONTENT**</div>
</div>
EOT;
  //Replace temp directives tags with HTML.
  $pattern = '/\[\[\[cycopseudent\:(\d+)\|\|\|(.*?)\]\]\]/is';
  $content = preg_replace_callback(
      $pattern, 
      function ($match) use ($template) {
        $pseudent_nid = $match[1];
        $content = $match[2];
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
        $replacement = str_replace('**NID**', $pseudent_nid, $template);
        $replacement = str_replace('**CAPTION**', $caption, $replacement);
        $replacement = str_replace('**CONTENT**', $content, $replacement);
        $replacement = str_replace('**IMAGE_PATH**', $usable_url, $replacement);
        return $replacement;
      },
      $content
  );

}


/**
 * Implements hook_restructuredtext_to_html_alter.
 * 
 * Translate intermediate (betwixt) markup in $content (as inserted by
 * custom ReST directive) to its HTML equivalent. Sample betwixt markup:
 * 
 * [[[animal 666|||note]]]
 * 
 */
function cyco_pseudents_swim_betwixt2html_alter(&$content) {
  $regex = 
      '/\[\[\[cycopseudent\:(\d*?)\|\|\|(.*?)\]\]\]/is';
  //? is for lazy match.
      //s option so it can contain new line chars.
  $content
    = preg_replace_callback($regex, '_cyco_pseudents_make_view_replacements', $content);
}

function _cyco_pseudents_make_view_replacements($matches) {
  $pseudent_nid = $matches[1];
  $content = $matches[2];
  //Load pseudent data.
  $node = node_load($pseudent_nid);
  if ( !$node ) {
    $message = '_cyco_pseudents_make_view_replacements: bad nid: ' . $pseudent_nid;
    watchdog('pseudents', $message);
    throw new Exception($message);
  }
  $caption = '';
  if (sizeof( $node->field_caption ) > 0 ) {
    $caption = $node->field_caption[LANGUAGE_NONE][0]['value'];
  }
  else {
    $caption = $node->title;
  }
  $usable_url = cyco_core_uri2path(
     $node->field_image[LANGUAGE_NONE][0]['uri']
  );
  $html =   '<div class="pseudent">'
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
 * Implements hook_node_view().
 */
function cyco_pseudents_node_view($node, $view_mode, $langcode) {
  global $base_url;
  if ( $node->type == 'pseudent_pose' ){
    //Add links - "Add another" and "Back to list."
    if ( $view_mode == 'full' ) {
          $weight = cyco_core_highest_content_weight( 
              $node->content, 
              array( 
                'field_caption',
                'field_image',
                'field_notes',
                'field_pseudent_categories',
                'field_workflow_tags',
              ) 
          );
          $node->content['pseudent_pose_add_link'] = array(
              '#markup' =>
                  '<div class="pseudents-back-link">'
                .   l(
                      'Add another pseudent pose', 
                      $base_url . '/node/add/pseudent-pose'
                    )
                . '</div>', 
              '#weight' => ( $weight + 1 ),
          );
          $node->content['pseudent_pose_link'] = array(
              '#markup' => _cyco_pseudents_make_link2list(),
              '#weight' => ( $weight + 2 ),
          );
    }
  }
}