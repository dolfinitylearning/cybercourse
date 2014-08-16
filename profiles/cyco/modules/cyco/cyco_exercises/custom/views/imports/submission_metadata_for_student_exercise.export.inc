<?php

$view = new view();
$view->name = 'submission_metadata_for_student_exercise';
$view->description = 'Return metadata about submissions for a student/exercise combination.';
$view->tag = 'Services';
$view->base_table = 'node';
$view->human_name = 'Submission metadata for student/exercise';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['style_plugin'] = 'default';
$handler->display->display_options['row_plugin'] = 'fields';
/* Relationship: Content: Author */
$handler->display->display_options['relationships']['uid']['id'] = 'uid';
$handler->display->display_options['relationships']['uid']['table'] = 'node';
$handler->display->display_options['relationships']['uid']['field'] = 'uid';
$handler->display->display_options['relationships']['uid']['required'] = TRUE;
/* Relationship: Entity Reference: Referenced Entity */
$handler->display->display_options['relationships']['field_exercise_target_id']['id'] = 'field_exercise_target_id';
$handler->display->display_options['relationships']['field_exercise_target_id']['table'] = 'field_data_field_exercise';
$handler->display->display_options['relationships']['field_exercise_target_id']['field'] = 'field_exercise_target_id';
$handler->display->display_options['relationships']['field_exercise_target_id']['required'] = TRUE;
/* Field: Content: Nid */
$handler->display->display_options['fields']['nid']['id'] = 'nid';
$handler->display->display_options['fields']['nid']['table'] = 'node';
$handler->display->display_options['fields']['nid']['field'] = 'nid';
$handler->display->display_options['fields']['nid']['label'] = 'submission_nid';
$handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
/* Field: Content: Version */
$handler->display->display_options['fields']['field_version']['id'] = 'field_version';
$handler->display->display_options['fields']['field_version']['table'] = 'field_data_field_version';
$handler->display->display_options['fields']['field_version']['field'] = 'field_version';
$handler->display->display_options['fields']['field_version']['label'] = 'version';
$handler->display->display_options['fields']['field_version']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['field_version']['type'] = 'number_unformatted';
$handler->display->display_options['fields']['field_version']['settings'] = array(
  'skip_safe' => 0,
  'skip_empty_values' => 0,
);
/* Field: Content: Post date */
$handler->display->display_options['fields']['created']['id'] = 'created';
$handler->display->display_options['fields']['created']['table'] = 'node';
$handler->display->display_options['fields']['created']['field'] = 'created';
$handler->display->display_options['fields']['created']['label'] = 'when created';
$handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['created']['date_format'] = 'custom';
$handler->display->display_options['fields']['created']['custom_date_format'] = 'c';
$handler->display->display_options['fields']['created']['second_date_format'] = 'long';
/* Field: Content: When submitted */
$handler->display->display_options['fields']['field_when_submitted']['id'] = 'field_when_submitted';
$handler->display->display_options['fields']['field_when_submitted']['table'] = 'field_data_field_when_submitted';
$handler->display->display_options['fields']['field_when_submitted']['field'] = 'field_when_submitted';
$handler->display->display_options['fields']['field_when_submitted']['label'] = 'when_submitted';
$handler->display->display_options['fields']['field_when_submitted']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['field_when_submitted']['type'] = 'services';
$handler->display->display_options['fields']['field_when_submitted']['settings'] = array(
  'skip_safe' => 0,
  'skip_empty_values' => 0,
);
/* Field: Content: When feedback given */
$handler->display->display_options['fields']['field_when_feedback_given']['id'] = 'field_when_feedback_given';
$handler->display->display_options['fields']['field_when_feedback_given']['table'] = 'field_data_field_when_feedback_given';
$handler->display->display_options['fields']['field_when_feedback_given']['field'] = 'field_when_feedback_given';
$handler->display->display_options['fields']['field_when_feedback_given']['label'] = 'when_feedback_given';
$handler->display->display_options['fields']['field_when_feedback_given']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['field_when_feedback_given']['settings'] = array(
  'skip_safe' => 0,
  'skip_empty_values' => 0,
);
/* Field: Content: Complete */
$handler->display->display_options['fields']['field_complete']['id'] = 'field_complete';
$handler->display->display_options['fields']['field_complete']['table'] = 'field_data_field_complete';
$handler->display->display_options['fields']['field_complete']['field'] = 'field_complete';
$handler->display->display_options['fields']['field_complete']['label'] = 'complete';
$handler->display->display_options['fields']['field_complete']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['field_complete']['type'] = 'list_key';
$handler->display->display_options['fields']['field_complete']['settings'] = array(
  'skip_safe' => 0,
  'skip_empty_values' => 0,
);
/* Sort criterion: Content: Post date */
$handler->display->display_options['sorts']['created']['id'] = 'created';
$handler->display->display_options['sorts']['created']['table'] = 'node';
$handler->display->display_options['sorts']['created']['field'] = 'created';
/* Contextual filter: User: Uid */
$handler->display->display_options['arguments']['uid']['id'] = 'uid';
$handler->display->display_options['arguments']['uid']['table'] = 'users';
$handler->display->display_options['arguments']['uid']['field'] = 'uid';
$handler->display->display_options['arguments']['uid']['relationship'] = 'uid';
$handler->display->display_options['arguments']['uid']['default_action'] = 'access denied';
$handler->display->display_options['arguments']['uid']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
/* Contextual filter: Content: Nid */
$handler->display->display_options['arguments']['nid']['id'] = 'nid';
$handler->display->display_options['arguments']['nid']['table'] = 'node';
$handler->display->display_options['arguments']['nid']['field'] = 'nid';
$handler->display->display_options['arguments']['nid']['relationship'] = 'field_exercise_target_id';
$handler->display->display_options['arguments']['nid']['default_action'] = 'access denied';
$handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
/* Filter criterion: Content: Published */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'node';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['value'] = '1';
$handler->display->display_options['filters']['status']['group'] = 1;
$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
/* Filter criterion: Content: Type */
$handler->display->display_options['filters']['type']['id'] = 'type';
$handler->display->display_options['filters']['type']['table'] = 'node';
$handler->display->display_options['filters']['type']['field'] = 'type';
$handler->display->display_options['filters']['type']['value'] = array(
  'exercise_submission' => 'exercise_submission',
);


