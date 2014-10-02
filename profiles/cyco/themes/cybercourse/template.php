<?php
/**
 * @file
 * template.php
 */

/**
 * Turn links with 'List' in them into buttons. 
 * See cyco_exercises_menu_local_tasks_alter for an example of 
 * why this is needed.
 */
function cybercourse_bootstrap_colorize_text_alter(&$texts) {
  $texts['contains'][t('List')] = 'success';  
}

/**
 * Implements hook_theme_registry_alter().
 * 
 * Prevent the Bootstrap theme from running bootstrap_process_book_navigation.
 * It creates errors sometimes.
 */
function cybercourse_theme_registry_alter(&$registry) {
  $target_index = NULL;
  foreach ( $registry['book_navigation']['process functions'] as $index => $name ) {
    if ( $name == 'bootstrap_process_book_navigation' ) {
      $target_index = $index;
      break;
    }
  }
  if ( !is_null($target_index) ) {
    unset( $registry['book_navigation']['process functions'][ $target_index ] );
  }
}

