<?php
/**
 * @file
 * page.vars.php
 */

/**
 * Implements hook_preprocess_page().
 *
 * @see page.tpl.php
 */
function cybercourse_preprocess_page(&$variables) {
  //Find container class in navbar.
  $key = array_search('container', $variables['navbar_classes_array']);
  if ( $key !== FALSE ) {
    //Replace it with fluid.
    $variables['navbar_classes_array'][$key] = 'container-fluid';
  }
}

/**
 * Implements hook_process_page().
 *
 * @see page.tpl.php
 */
function cybercourse_process_page(&$variables) {
  $variables['navbar_classes'] = implode(' ', $variables['navbar_classes_array']);
}
