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
        foreach ( $node->field_pseudent_categories[LANGUAGE_NONE] as $term ) {
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
//function cyco_pseudents_swim_ckhtml2rest_alter( &$content ) {
//  $regex = 
//      '/\<div class\=\"pseudent\".*?data\-pseudent\-id\=\"(.*?)\"*.\>\s*'
//      .  '\<div class\=\"pseudent\-image\-container\"\>\s*'
//      .    '\<img.*?\>\s*'
//      .    '\<div class\=\"pseudent-image-caption\"\>.*?\<\/div\>\s*'
//      .  '\<\/div\>\s*'
//      .  '\<div class=\"pseudent\-content\"\>(.*?)\<\/div\>\s*'
//      . '\<\/div\>/is';
//    //? for lazy eval.
//    //s option to include new lines in whitespace matches.
//  //NB: does not include last \n.
//  $content
//    = preg_replace_callback($regex, '_cyco_pseudents_make_directive_replacements', $content);
//}
//
//function _cyco_pseudents_make_directive_replacements($matches) {
//  $nid = $matches[1];
//  $content = $matches[2];
//  //Add four spaces after every new line in the content, because indentation
//  //is significant in ReST.
//  $content = str_replace("\n", "\n    ", $content);
//  $replacement = 
//      '.. pseudent:: ' . $nid . "\n\n"
//    . '  ' . $content; // . "\n";
//  return $replacement;
//}

/**
 * Replace .. pseudent:: directives with betwixt tag, used later to 
 * add HTML tags CK uses. Note: betwixt tags can't have spaces that the user
 * didna' type.
 * @param string $content Da goods, ReSTy.
 */
//function cyco_pseudents_swim_rest2betwixt_alter( &$content ) {
//  $directives = _cyco_pseudents_find_pseudent_elements( $content );
//  foreach ($directives as $directive) {
//    //Get relevant data about the ReST pseudent directive.
//    $pseudent_nid = $directive['pseudent_nid'];
//    //Where the .. starts.
//    $directive_start_pos = $directive['directive_start_pos'];
//    //The end of the directive's content.
//    $pseudent_content_end_pos = $directive['pseudent_content_end_pos'];
//    //The content itself.
//    $pseudent_content = $directive['pseudent_content'];
//    //Make the tag.
//    $betwixt = '[[[cycopseudent:' . $pseudent_nid . '|||'
//        . $pseudent_content . "]]]";
//    //Replace the ReST with the betwixt.
//    $left = substr($content, 0, $directive_start_pos );
//    $right = substr( $content, $pseudent_content_end_pos + 1);
//    if ( $directive['eof_encountered'] ) {
//      $right .= "\n"; //Slimy patch.
//      $left .= "\n"; //Slimy patch.
//    }
//    $content = $left . $betwixt . $right;
//  }
//}

/*
 * Implements hook_swim_betwixt2ckhtml_alter().
 * 
 * This doesn't set the pseudent category - that information is not stored
 * in the DB.
 */
//function cyco_pseudents_swim_betwixt2ckhtml_alter( &$content ) {
//  $template = <<<EOT
//<div class="pseudent" data-pseudent-id="**NID**">
//  <div class="pseudent-image-container">
//    <img class="pseudent-image" src="**IMAGE_PATH**">
//    <div class="pseudent-image-caption">**CAPTION**</div>
//  </div>
//  <div class="pseudent-content">**CONTENT**</div>
//</div>
//EOT;
  //Replace temp directives tags with HTML.
  //<br> is a slimy hack to preserve blank lines.
//  $pattern = '/\<br\>\s*\[\[\[cycopseudent\:(\d+)\|\|\|(.*?)\]\]\]/is';
//  $content = preg_replace_callback(
//      $pattern, 
//      function ($match) use ($template) {
//        $pseudent_nid = $match[1];
//        $content = $match[2];
//        $pseudent_node = node_load($pseudent_nid);
//        if ( isset( $pseudent_node->field_caption[LANGUAGE_NONE][0]['value'] ) ) {
//          $caption = $pseudent_node->field_caption[LANGUAGE_NONE][0]['value'];
//        }
//        else {
//          $caption = $pseudent_node->title;
//        }
//        //Get the path to the pseudent's image file.
//        $usable_url = cyco_core_uri2path(
//            $pseudent_node->field_image[LANGUAGE_NONE][0]['uri']
//        );
//        $replacement = str_replace('**NID**', $pseudent_nid, $template);
//        $replacement = str_replace('**CAPTION**', $caption, $replacement);
//        $replacement = str_replace('**CONTENT**', $content, $replacement);
//        $replacement = str_replace('**IMAGE_PATH**', $usable_url, $replacement);
//        return $replacement;
//      },
//      $content
//  );
//
//}


/**
 * Implements hook_restructuredtext_to_html_alter.
 * 
 * Translate intermediate (betwixt) markup in $content (as inserted by
 * custom ReST directive) to its HTML equivalent. Sample betwixt markup:
 * 
 * [[[animal 666|||note]]]
 * 
 */
//function cyco_pseudents_swim_betwixt2html_alter(&$content) {
//  $regex = 
//      '/\[\[\[cycopseudent\:(\d*?)\|\|\|(.*?)\]\]\]/is';
//  //? is for lazy match.
//      //s option so it can contain new line chars.
//  $content
//    = preg_replace_callback($regex, '_cyco_pseudents_make_view_replacements', $content);
//}
//
//function _cyco_pseudents_make_view_replacements_old($matches) {
//  $pseudent_nid = $matches[1];
//  $content = $matches[2];
//  //Load pseudent data.
//  $node = node_load($pseudent_nid);
//  if ( !$node ) {
//    $message = '_cyco_pseudents_make_view_replacements: bad nid: ' . $pseudent_nid;
//    watchdog('pseudents', $message);
//    throw new Exception($message);
//  }
//  $caption = '';
//  if ( isset( $node->field_caption[LANGUAGE_NONE][0]['value'] ) ) {
//    $caption = $node->field_caption[LANGUAGE_NONE][0]['value'];
//  }
//  else {
//    $caption = $node->title;
//  }
//  $usable_url = cyco_core_uri2path(
//     $node->field_image[LANGUAGE_NONE][0]['uri']
//  );
//  $html =   '<div class="pseudent">'
//          .   '<div class="pseudent-image-container">'
//          .     '<img class="pseudent-image" '
//          .         'src="' . $usable_url . '" '
//          .         'alt="' . $caption . '" >'
//          .     '<div class="pseudent-image-caption">' 
//          .       $caption
//          .     '</div>'
//          .   '</div>'
//          .   '<div class="pseudent-content">' . $content . '</div>'
//          . '</div>';
//  return $html;
//}

/**
 * Implements hook_node_view().
 */
function cyco_pseudents_node_view($node, $view_mode, $langcode) {
  global $base_url;
  if ( $node->type == 'pseudent_pose' ) {
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
//          $node->content['pseudent_pose_link'] = array(
//              '#markup' => _cyco_pseudents_make_link2list(),
//              '#weight' => ( $weight + 2 ),
//          );
    }
  }
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
 * Find pseudent directives and return info about them.
 * @param type $content Content containing the directives.
 * @return array Info about the directives.
 */
//function _cyco_pseudents_find_pseudent_elements( $content ) {
//  //Get rid of CRs.
//  $content = str_replace("\r", '', $content);
//  //Make sure the last two chars are \ns.
//  //Otherwise, EOS processing gets too messy. Yuck.
//  if ( substr($content, -1, 2) != "\n\n") {
//    $content .= "\n\n";
//  }
//  
//  //Find the directive commands. "Directive command" is the first line
//  //of the directive (.. pseudent:: 666).
//  //Match includes \n.
//  $matches = array();
//  preg_match_all(
//      '/\.\.\s*pseudent\:\:\s*(\d+)\s*?\n/i',
//      $content,
//      $matches
//  );
//
//  /**
//   * For each match, skip the blank line(s) that follow it, then find
//   * the next non-blank line with the same or lesser indent. 
//   * Everything betixt those
//   * two points is what the pseudent says.
//   */
//  //Results of processing. One element for each match found.
//  $results = array();
//  for ( $match_number = 0; $match_number < sizeof( $matches[0] ); $match_number++) {
//    //Match[0] is the complete matched text.
//    $match = $matches[0][$match_number];
//    //Mathces[1] is the pseudent number.
//    $pseudent_nid = $matches[1][$match_number];
//    //Where does the match start in $content?
//    $match_start = strpos($content, $match);
//    //Remember this is as the start of the directive
//    $directive_start = $match_start;
//    $directive_end = $directive_start + strlen($match) - 1;
//    //Compute indentation of the .. pseudent thing.
//    //Start with the first . and work left.
//    $directive_indentation = 0;
//    $char = substr($content, $match_start - $directive_indentation - 1, 1);
//    while ( $char == ' ' ) {
//      $directive_indentation ++;
//      $char = substr($content, $match_start - $directive_indentation - 1, 1);
//    }
//
//    //Find the beginning of the next line.
//    $next_line_start = $match_start + strlen($match);
//    //Skip blank lines after the directive command. 
//    //"Blank" means just a \n, or whitesspace and a \n.
//    $num_blank_lines = 0;
//    list( $line, $line_length, $end_char_pos, $indent_level, $is_blank, $EOS) 
//        = _cyco_pseudents_get_line($content, $next_line_start);
//    while ( $is_blank && ! $EOS ) {
//      $num_blank_lines ++;
//      $next_line_start += $line_length;
//      list( $line, $line_length, $end_char_pos, $indent_level, $is_blank, $EOS) 
//          = _cyco_pseudents_get_line($content, $next_line_start);
//    }
//    //Must have at least one blank line.
//    if ( $num_blank_lines == 0 && ! $EOS ) {
//      //Add a blank line.
//      $content = substr($content, 0, $next_line_start) 
//          . "\n" 
//          . substr($content, $next_line_start);
//  //****??????***************************************^^^    
//      //Move past the /n at the end of the line ($end_char_post points to it),
//      //And then skip the new \n.
//      $next_line_start = $end_char_pos + 2;
//    }
//    //Start looking for pseudent content.
//    $pseudent_content_start = NULL; 
//    $pseudent_content_end  = NULL;
//    $pseudent_content = NULL;
//    //If EOS at this point, there is no pseudent content. Just the
//    //Directive command.
//    if ( ! $EOS ) {
//      //Loop, looking for non-blank line that has less indentation than
//      //the directive.
//      //$next_line_start points to the start of a non-blank line.
//      list( $line, $line_length, $end_char_pos, $indent_level, $is_blank, $EOS) 
//          = _cyco_pseudents_get_line($content, $next_line_start);
//      //If the indent level of this line is more than the indent level
//      //of the directive command, the line belongs to the pseudent content.
//      //Otherwise, the content does not belong to the pseudent directive,
//      //and there is no more processing to do.
//      if ( $indent_level > $directive_indentation ) {
//        //$next_line_start is the beginning of a non-blank line.
//        $pseudent_content_start = $next_line_start;
//        do {
//          //Find the next blank.
//          do {
//            $next_line_start += $line_length;
//            //This could be the end of the student content, but can't be sure. 
//            $candidate_content_end = $next_line_start - 1;
//            list( $line, $line_length, $end_char_pos, $indent_level, $is_blank, $EOS) 
//              = _cyco_pseudents_get_line($content, $next_line_start);
//          } while ( ! $is_blank && ! $EOS );
//          if ( $EOS ) {
//            //Done.
//            $pseudent_content_end = strlen($content) - 1;
//          }
//          else {
//            //Found a blank line.
//            //Skip the blanks to the next non-blank, and check its indentation.
//            do {
//              $next_line_start += $line_length;
//              list( $line, $line_length, $end_char_pos, $indent_level, $is_blank, $EOS) 
//                = _cyco_pseudents_get_line($content, $next_line_start);
//            } while ( $is_blank && ! $EOS );
//            if ( $EOS ) {
//              //Done.
//              $pseudent_content_end = strlen($content) - 1;
//            }
//            else {
//              //Check the indentation level.
//              if ( $indent_level <= $directive_indentation ) {
//                //This is the beginning of the next element.
//                $pseudent_content_end = $candidate_content_end;
//              }
//            }// ! EOS
//          }// ! EOS
//          //The non-blank line is part of the pseudent contemt.
//        } while ( is_null( $pseudent_content_end ) );
//        //Grab the peusent content.
//        $pseudent_content_with_indent = substr( 
//            $content, 
//            $pseudent_content_start,  
//            $pseudent_content_end - $pseudent_content_start
//        );
//        //Remember whether EOS was found during this processing.
//        $found_EOS = $EOS;
//        //Unindent the pseudent content.
//        //Find the indentation of the first line of the pseudent content.
//        list( $line, $line_length, $end_char_pos, $indent_level, $is_blank, $EOS) 
//          = _cyco_pseudents_get_line($pseudent_content_with_indent, 0);
//        $pseudent_content_indentation = $indent_level;
//        //Some of this may be indentation of the directive command, if the
//        //latter was indented.
//        if ( $directive_indentation > 0 ) {
//          $pseudent_content_indentation -= $directive_indentation;
//        }
//        //Loop through pseudent content, removing $pseudent_content_indentation
//        // chars from the beginning.
//        $pseudent_content = '';
//        $start_pos = 0;
//        do {
//          list( $line, $line_length, $end_char_pos, $indent_level, $is_blank, $EOS) 
//            = _cyco_pseudents_get_line($pseudent_content_with_indent, $start_pos);
//          if ( $line ) {
//            $line = substr( $line, $pseudent_content_indentation );
//            $pseudent_content .= $line;
//            $start_pos += $line_length;
//          }
//        } while ( ! $EOS );
//
//      } // End processing one match.
//    }
//    $results[] = array( 
//      'pseudent_nid' => $pseudent_nid,
//      'directive_command' => $match,
//      'directive_start_pos' => $directive_start,
//      'directive_command_end_pos' => $directive_end,
//      'pseudent_content_start_pos' => $pseudent_content_start,
//      'pseudent_content_end_pos' => $pseudent_content_end,
//      'pseudent_content' => $pseudent_content,
//      'directive_indentation' => $directive_indentation,
//      'eof_encountered' => $found_EOS,
//    );
//  } //End for loop over matches.
//  return $results;
//}

/**
 * Find the line in $content that starts at $start_pos.
 * Return much info about it.
 * @param string $content Content to search.
 * @param int $start_pos Where to start (char pos).
 * @return array Info about the line.
 */
//function _cyco_pseudents_get_line( $content, $start_pos ) {
//  //Flag for MT string = \n, or whitespace and \n.
//  $is_blank = TRUE;
//  //Flag for whether the end of the string was encountered.
//  $EOS = FALSE;
//  //Is $start_pos beyond the end of the string?
//  if ( $start_pos >= strlen($content) ) {
//    $line = NULL;
//    $length = NULL;
//    $eol_pos = NULL;
//    $indentation = NULL;
//    $is_blank = NULL;
//    $EOS = TRUE;
//    return array( $line, $length, $eol_pos, $indentation, $is_blank, $EOS );
//  }
//  //Find end of line.
//  $eol_pos = $start_pos;
//  $char = substr($content, $eol_pos, 1);
//  if ( $char != "\n" && $char != ' ') {
//    $is_blank = FALSE;
//  }
//  while ( $char != "\n" && ($eol_pos + 1) < strlen($content) ) {
//    $eol_pos ++;
//    $char = substr($content, $eol_pos, 1);
//    if ( $char != "\n" && $char != ' ') {
//      $is_blank = FALSE;
//    }
//  }
//  //$eol_pos points to \n, or the end of the string.
//  $line = substr( $content, $start_pos, $eol_pos - $start_pos + 1);
//  if ( ($eol_pos + 1) >= strlen($content) ) {
//    $EOS = TRUE;
//  }
//  //Compute indentation level.
//  $indentation = 0;
//  $content_start_pos = $start_pos;
//  $char = substr( $content, $content_start_pos, 1);
//  if ( $char != "\n" && $char != ' ') {
//    $is_blank = FALSE;
//  }
//  while ( $char == ' ' && ($content_start_pos + 1) < strlen($content) ) {
//    $content_start_pos ++;
//    $char = substr( $content, $content_start_pos, 1);
//    if ( $char != "\n" && $char != ' ') {
//      $is_blank = FALSE;
//    }
//    $indentation ++;
//  }
//  if ( ($content_start_pos + 1) >= strlen($content) ) {
//    $EOS = TRUE;
//  }
//  return array( $line, strlen( $line ), $eol_pos, $indentation, $is_blank, $EOS );
//}

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
 * Implements hook_swim_tag_process_alter().
 * 
 */
//function cyco_pseudents_swim_tag_process_alter(  ) {
//}

/**
 * Implements hook_swim_markdown2html_TAG_alter().
 * @param stdClass $args Untranslated markdown.
 */
//function cyco_pseudents_swim_markdown2html_pseudent_alter( &$args ) {
//  $template = <<<EOT
//<div class="pseudent" data-pseudent-id="**NID**">
//  <div class="pseudent-image-container">
//    <img class="pseudent-image" src="**IMAGE_PATH**">
//    <div class="pseudent-image-caption">**CAPTION**</div>
//  </div>
//  <div class="pseudent-content">**CONTENT**</div>
//</div>
//EOT;
//  //Find the end of the tag.
//  $end_line = SwimMarkdown::findEndCustomTag(
//      $args->content, 
//      $args->current_line + 1
//  );
//  if ( is_null($end_line) ) {
//    $message = __FILE__ . ' (line ' . __LINE__ . ') ' . __FUNCTION__ 
//        . ' id not find end tag.';
//    cyco_core_handle_error( $message );
//    return;
//  }
//  //Parse the content in the pseudent tag.
//  $pseudent_markdown = array_slice(
//      $args->content,
//      $args->current_line + 1,
//      $end_line - $args->current_line - 1
//  );
//  $parser = new SwimMarkdown();
//  $content = $parser->parse( implode("\n", $pseudent_markdown) );
//  //Load pseudent attributes.
//  $pseudent_nid = intval($args->args);
//  $pseudent_node = node_load($pseudent_nid);
//  if ( isset( $pseudent_node->field_caption[LANGUAGE_NONE][0]['value'] ) ) {
//    $caption = $pseudent_node->field_caption[LANGUAGE_NONE][0]['value'];
//  }
//  else {
//    $caption = $pseudent_node->title;
//  }
//  //Get the path to the pseudent's image file.
//  $usable_url = cyco_core_uri2path(
//      $pseudent_node->field_image[LANGUAGE_NONE][0]['uri']
//  );
//  //Use template.
//  $replacement = str_replace('**NID**', $pseudent_nid, $template);
//  $replacement = str_replace('**CAPTION**', $caption, $replacement);
//  $replacement = str_replace('**CONTENT**', $content, $replacement);
//  $replacement = str_replace('**IMAGE_PATH**', $usable_url, $replacement);
//  //Return to sen-der.
//  $args->replacement_content = $replacement;
//  $args->current_line = $end_line + 1;
//}

/**
 * Implements hook_swim_ckhtml2rest_alter().
 * @param string $content Content to change.
 */
//function cyco_pseudents_swim_ckhtml2markdown_alter( &$content ) {
//  $regex = 
//      '/\<div class\=\"pseudent\".*?data\-pseudent\-id\=\"(.*?)\"*.\>\s*'
//      .  '\<div class\=\"pseudent\-image\-container\"\>\s*'
//      .    '\<img.*?\>\s*'
//      .    '\<div class\=\"pseudent-image-caption\"\>.*?\<\/div\>\s*'
//      .  '\<\/div\>\s*'
//      .  '\<div class=\"pseudent\-content\"\>(.*?)\<\/div\>\s*'
//      . '\<\/div\>/is';
//    //? for lazy eval.
//    //s option to include new lines in whitespace matches.
//  //NB: does not include last \n.
//  $content
//    = preg_replace_callback($regex, '_cyco_pseudents_make_markdown_replacements', $content);
//}

//function _cyco_pseudents_make_markdown_replacements($matches) {
//  $nid = $matches[1];
//  $content = $matches[2];
//  $replacement = 
//      SwimMarkdown::START_CUSTOM_TAG . ' pseudent ' . $nid . "\n"
//      . $content . "\n"
//      . SwimMarkdown::END_CUSTOM_TAG;
//  return $replacement;
//}

/**
 * Implements hook_swim_markdown2ckhtml.
 * 
 * Translate intermediate (betwixt) markup in $content (as inserted by
 * custom ReST directive) to its HTML equivalent. Sample betwixt markup:
 * 
 * [[[animal 666|||note]]]
 * 
 */
//function cyco_pseudents_swim_markdown2ckhtml_alter(&$content) {
//  $regex = 
//      '/' . SwimMarkdown::START_CUSTOM_TAG_REGEX_ESCAPED 
//      . '\s+pseudent\s+(\d+)?\s*\n(.*)' 
//      . SwimMarkdown::END_CUSTOM_TAG_REGEX_ESCAPED . '\s*\n/is';
//  //? is for lazy match.
//  //s option so it can contain new line chars.
//  $content
//    = preg_replace_callback($regex, '_cyco_pseudents_make_view_replacements', $content);
//}

//function _cyco_pseudents_make_view_replacements($matches) {
//  $pseudent_nid = $matches[1];
//  $content = $matches[2];
//  //Load pseudent data.
//  $node = node_load($pseudent_nid);
//  if ( !$node ) {
//    $message = __FILE__ . ' (line ' . __LINE__ . ') ' . __FUNCTION__ 
//        . ' bad nid: ' . $pseudent_nid;
//    cyco_core_handle_error( $message );
//    return;
//  }
//  $caption = '';
//  if ( isset( $node->field_caption[LANGUAGE_NONE][0]['value'] ) ) {
//    $caption = $node->field_caption[LANGUAGE_NONE][0]['value'];
//  }
//  else {
//    $caption = $node->title;
//  }
//  $usable_url = cyco_core_uri2path(
//     $node->field_image[LANGUAGE_NONE][0]['uri']
//  );
//  $html =   '<div class="pseudent" data-pseudent-id="' . $pseudent_nid . '" >'
//          .   '<div class="pseudent-image-container">'
//          .     '<img class="pseudent-image" '
//          .         'src="' . $usable_url . '" '
//          .         'alt="' . $caption . '" >'
//          .     '<div class="pseudent-image-caption">' 
//          .       $caption
//          .     '</div>'
//          .   '</div>'
//          .   '<div class="pseudent-content">' . $content . '</div>'
//          . '</div>';
//  return $html;
//}

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
function _cyco_pseudents_swim_view_callback( $pseudent_nid, $tag_content ) {
  $template = <<<EOT
<div class="pseudent" data-pseudent-id="**NID**">
  <div class="pseudent-image-container">
    <img class="pseudent-image" src="**IMAGE_PATH**"" alt="**CAPTION**">
    <div class="pseudent-image-caption">**CAPTION**</div>
  </div>
  <div class="pseudent-content">**CONTENT**</div>
</div>
EOT;
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
  //Use template.
  $replacement = str_replace('**NID**', $pseudent_nid, $template);
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
  return array(
    'tag' => 'pseudent',
    'callback' => '_cyco_pseudents_swim_edit_callback',
  );
}

/**
 * Implements hook_swim_textile2ckhtml.
 */
function _cyco_pseudents_swim_edit_callback( $pseudent_nid, $content ) {
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
  $html =   '<div class="pseudent" data-pseudent-id="' . $pseudent_nid . '" >'
          .   '<div class="pseudent-image-container">'
          .     '<img class="pseudent-image" '
          .         'src="' . $usable_url . '" '
          .         'alt="' . $caption . '" >'
          .     '<div class="pseudent-image-caption">' 
          .       $caption
          .     '</div>'
          .   '</div>'
          .   '<div class="pseudent-content">' . $content . '</div>'
          . "</div>\n";
  return $html;
}

/**
 * Implements hook_swim_ckhtml2textile_alter().
 * @param string $content Content to change.
 */
function cyco_pseudents_swim_ckhtml2textile_alter( &$content ) {
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
  //NB: does not include last \n.
  $content
    = preg_replace_callback($regex, '_cyco_pseudents_make_textile_replacements', $content);
}



function _cyco_pseudents_make_textile_replacements($matches) {
  $nid = $matches[1];
  $content = $matches[2];
  $replacement = 
    SwimCustomTagParser::START_CUSTOM_TAG . ' pseudent ' . $nid . "\n"
      . $content . "\n"
      . SwimCustomTagParser::END_CUSTOM_TAG . ' pseudent ' . $nid;
  return $replacement;
}