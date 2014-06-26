<?php
/*
 * @file
 * Implements the CyCo table of contents module.
 */

/**
 * Implements hook_help().
 * @todo Write ToCy help in hook_help.
 */
function cyco_toc_help($path, $arg) {
  switch ($path) {
    case 'admin/help#cyco_toc':
      return '<p>' . t('Helpy helpy help help, <a href="@jquery">jQuery</a>.', 
          array(
            '@jquery' => 'http://jquery.com',
          )) . '</p>';
  }
}

/**
 * Implement hook_node_view_alter().
 * Add toc handling to pages that need it.
 */
function cyco_toc_node_view_alter(&$build) {
  if ( isset($build['#node']->field_show_table_of_contents[LANGUAGE_NONE][0]['value']) ) {
    if ( $build['#node']->field_show_table_of_contents[LANGUAGE_NONE][0]['value'] == 1 ) {
      drupal_add_js(drupal_get_path('module', 'cyco_toc') 
          . '/custom/js/cyco_toc.js', 'file');
//      drupal_add_css(drupal_get_path('module', 'cyco_toc') 
//          . '/custom/js/cyco_toc.css', 'file');
    }
  }
}