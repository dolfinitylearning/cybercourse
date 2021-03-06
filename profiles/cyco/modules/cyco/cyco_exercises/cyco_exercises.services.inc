<?php
/**
 * @file
 * cyco_exercises.services.inc
 */

/**
 * Implements hook_default_services_endpoint().
 */
function cyco_exercises_default_services_endpoint() {
  $export = array();

  $endpoint = new stdClass();
  $endpoint->disabled = FALSE; /* Edit this to true to make a default endpoint disabled initially */
  $endpoint->api_version = 3;
  $endpoint->name = 'exercise';
  $endpoint->server = 'rest_server';
  $endpoint->path = 'exercise';
  $endpoint->authentication = array(
    'services' => 'services',
  );
  $endpoint->server_settings = array();
  $endpoint->resources = array(
    'definition' => array(
      'operations' => array(
        'index' => array(
          'enabled' => '1',
        ),
      ),
    ),
    'exercise' => array(
      'operations' => array(
        'retrieve' => array(
          'enabled' => '1',
        ),
      ),
    ),
    'feedback' => array(
      'actions' => array(
        'getGraderSubmissionsNeedingFeedback' => array(
          'enabled' => '1',
        ),
        'getSubmissionRendered' => array(
          'enabled' => '1',
        ),
        'getExerciseRendered' => array(
          'enabled' => '1',
        ),
        'getRubricItems' => array(
          'enabled' => '1',
        ),
        'makeFeedbackMessage' => array(
          'enabled' => '1',
        ),
        'saveFeedback' => array(
          'enabled' => '1',
        ),
      ),
    ),
    'rubric_item' => array(
      'operations' => array(
        'retrieve' => array(
          'enabled' => '1',
        ),
        'create' => array(
          'enabled' => '1',
        ),
        'update' => array(
          'enabled' => '1',
        ),
        'delete' => array(
          'enabled' => '1',
        ),
        'index' => array(
          'enabled' => '1',
        ),
      ),
      'actions' => array(
        'getTitlesCategories' => array(
          'enabled' => '1',
        ),
        'chkTtl' => array(
          'enabled' => '1',
        ),
        'saveNewItemComments' => array(
          'enabled' => '1',
        ),
      ),
    ),
    'rubric_item_categories' => array(
      'actions' => array(
        'getTree' => array(
          'enabled' => '1',
        ),
      ),
    ),
    'submission' => array(
      'actions' => array(
        'getSubmissionMetaStudentExer' => array(
          'enabled' => '1',
        ),
      ),
    ),
  );
  $endpoint->debug = 0;
  $export['exercise'] = $endpoint;

  return $export;
}
