<?php
/**
 * @file
 * Adds display fields for Views.
 */

include_once realpath(dirname(__FILE__)) . '/cyco_badges_has_user_earned_badge.inc';
include_once realpath(dirname(__FILE__)) . '/cyco_badges_user_badge_image.inc';

/**
 * Implements hook_views_data().
 */
function cyco_badges_views_data_alter(&$data) {
  $data['cyco_badges']['table']['group'] = t('Cyco badges');
  $data['cyco_badges']['table']['join'] = array(
    // #global is a special flag which lets a table appear all the time.
    '#global' => array(),
  );
  $data['cyco_badges']['has_user_earned_badge'] = array(
    'title' => t('Has the current user earned the badge?'),
    'help' => t('Show whether the current user has earned the badge or not.'),
    'field' => array(
      'handler' => 'cyco_badges_handler_has_user_earned_badge',
    ),
  );
  $data['cyco_badges']['badge_image_for_current_user'] = array(
    'title' => t('Badge'),
    'help' => t('Show the badge image for the current user (locked or not).'),
    'field' => array(
      'handler' => 'cyco_badges_user_badge_image',
    ),
  );
}

/**
 * Implementation of hook_views_default_views().
 * seehttps://api.drupal.org/api/views/views.api.php/function/hook_views_default_views/7
 **/
//function cyco_badges_views_default_views() {
//  $files = file_scan_directory(drupal_get_path('module', 'cyco_badges') 
//      . '/custom/views/imports', '/.*/');
//  foreach ($files as $filepath => $file) {
//    require $filepath;
//    if (isset($view)) {
//      $views[$view->name] = $view;
//    }
//  }
//  return $views;
//}    
//  
  
//  $files = file_scan_directory(drupal_get_path('module', 'cyco_badges') 
//      . '/custom/views/imports', '/.*/');
//  foreach (glob(dirname(__FILE__) . "/imports/*.inc") as $filename) {
//    include_once($filename);
//    $views[$view->name] = $view;
//  }
//  return $views;
//}

