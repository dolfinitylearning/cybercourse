<?php

/**
 * Implements hook_views_data()
 */
function cyco_exercises_views_data_alter( &$data ) {
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
 * Implementation of hook_views_handlers().
 */
//function cyco_exercises_views_handlers() {
//  $r=6;
//  return array(
//    'info' => array(
//      'path' => drupal_get_path('module', 'cyco_exercises') . '/custom/views',
//    ),
//    'handlers' => array(
//      'cyco_exercises_handler_submission_status' => array(
//        'parent' => 'views_handler_field',
//      ),
//    ),
//  );
//}

  