<?php
/**
 * @file
 * Adds display fields for Views.
 */

/**
 * Implements hook_views_data().
 */
function cyco_exercises_views_data_alter(&$data) {
  $data['cyco_exercises']['table']['group'] = t('Cyco exercises');
  $data['cyco_exercises']['table']['join'] = array(
    // #global is a special flag which let's a table appear all the time.
    '#global' => array(),
  );
  $data['cyco_exercises']['submission_status'] = array(
    'title' => t('Submission status'),
    'help' => t('Status of submission: Unsubmitted, Waiting for feedback...'),
    'field' => array(
      'handler' => 'cyco_exercises_handler_submission_status',
    ),
  );
  $data['cyco_exercises']['completion_badge'] = array(
    'title' => t('Completion badge'),
    'help' => t('Show completion badge, if submission complete.'),
    'field' => array(
      'handler' => 'cyco_exercises_handler_completion_badge',
    ),
  );
}

/**
 * Implementation of hook_views_default_views().
 * seehttps://api.drupal.org/api/views/views.api.php/function/hook_views_default_views/7
 **/
function cyco_exercises_views_default_views() {
  $files = file_scan_directory(drupal_get_path('module', 'cyco_exercises') 
      . '/custom/views/imports', '/.*/');
  foreach ($files as $filepath => $file) {
    require $filepath;
    if (isset($view)) {
      $views[$view->name] = $view;
    }
  }
  return $views;
}  

