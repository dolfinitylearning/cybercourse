<?php

$view = new view();
$view->name = 'submissions_instructor_report_one_student';
$view->description = 'Report for instructors on submissions.';
$view->tag = 'default';
$view->base_table = 'node';
$view->human_name = 'Submissions (instructor report)';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Exercise submissions';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'role';
$handler->display->display_options['access']['role'] = array(
  3 => '3',
  5 => '5',
  6 => '6',
);
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '20';
$handler->display->display_options['style_plugin'] = 'table';
/* Relationship: Entity Reference: Referenced Entity */
$handler->display->display_options['relationships']['field_exercise_target_id']['id'] = 'field_exercise_target_id';
$handler->display->display_options['relationships']['field_exercise_target_id']['table'] = 'field_data_field_exercise';
$handler->display->display_options['relationships']['field_exercise_target_id']['field'] = 'field_exercise_target_id';
/* Relationship: Content: Author */
$handler->display->display_options['relationships']['uid']['id'] = 'uid';
$handler->display->display_options['relationships']['uid']['table'] = 'node';
$handler->display->display_options['relationships']['uid']['field'] = 'uid';
/* Field: User: First name */
$handler->display->display_options['fields']['field_first_name']['id'] = 'field_first_name';
$handler->display->display_options['fields']['field_first_name']['table'] = 'field_data_field_first_name';
$handler->display->display_options['fields']['field_first_name']['field'] = 'field_first_name';
$handler->display->display_options['fields']['field_first_name']['relationship'] = 'uid';
$handler->display->display_options['fields']['field_first_name']['element_label_colon'] = FALSE;
/* Field: User: Last name */
$handler->display->display_options['fields']['field_last_name']['id'] = 'field_last_name';
$handler->display->display_options['fields']['field_last_name']['table'] = 'field_data_field_last_name';
$handler->display->display_options['fields']['field_last_name']['field'] = 'field_last_name';
$handler->display->display_options['fields']['field_last_name']['relationship'] = 'uid';
$handler->display->display_options['fields']['field_last_name']['element_label_colon'] = FALSE;
/* Field: User: Name */
$handler->display->display_options['fields']['name']['id'] = 'name';
$handler->display->display_options['fields']['name']['table'] = 'users';
$handler->display->display_options['fields']['name']['field'] = 'name';
$handler->display->display_options['fields']['name']['relationship'] = 'uid';
$handler->display->display_options['fields']['name']['label'] = 'User name';
/* Field: Content: Version */
$handler->display->display_options['fields']['field_version']['id'] = 'field_version';
$handler->display->display_options['fields']['field_version']['table'] = 'field_data_field_version';
$handler->display->display_options['fields']['field_version']['field'] = 'field_version';
$handler->display->display_options['fields']['field_version']['label'] = '';
$handler->display->display_options['fields']['field_version']['exclude'] = TRUE;
$handler->display->display_options['fields']['field_version']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['field_version']['settings'] = array(
  'thousand_separator' => ' ',
  'prefix_suffix' => 1,
);
/* Field: Content: Title */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['relationship'] = 'field_exercise_target_id';
$handler->display->display_options['fields']['title']['label'] = 'Exercise';
$handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['title']['alter']['text'] = '[title] (ver. [field_version])';
$handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
$handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
/* Field: Content: When submitted */
$handler->display->display_options['fields']['field_when_submitted']['id'] = 'field_when_submitted';
$handler->display->display_options['fields']['field_when_submitted']['table'] = 'field_data_field_when_submitted';
$handler->display->display_options['fields']['field_when_submitted']['field'] = 'field_when_submitted';
$handler->display->display_options['fields']['field_when_submitted']['label'] = 'Submitted';
$handler->display->display_options['fields']['field_when_submitted']['settings'] = array(
  'format_type' => 'short_date_only',
  'fromto' => 'both',
  'multiple_number' => '',
  'multiple_from' => '',
  'multiple_to' => '',
);
/* Field: Cyco exercises: Submission status */
$handler->display->display_options['fields']['submission_status']['id'] = 'submission_status';
$handler->display->display_options['fields']['submission_status']['table'] = 'cyco_exercises';
$handler->display->display_options['fields']['submission_status']['field'] = 'submission_status';
$handler->display->display_options['fields']['submission_status']['label'] = 'Status';
$handler->display->display_options['fields']['submission_status']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['submission_status']['hide_alter_empty'] = FALSE;
/* Sort criterion: Content: Post date */
$handler->display->display_options['sorts']['created']['id'] = 'created';
$handler->display->display_options['sorts']['created']['table'] = 'node';
$handler->display->display_options['sorts']['created']['field'] = 'created';
$handler->display->display_options['sorts']['created']['order'] = 'DESC';
/* Contextual filter: Content: Author uid */
$handler->display->display_options['arguments']['uid']['id'] = 'uid';
$handler->display->display_options['arguments']['uid']['table'] = 'node';
$handler->display->display_options['arguments']['uid']['field'] = 'uid';
$handler->display->display_options['arguments']['uid']['default_argument_type'] = 'current_user';
$handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
/* Filter criterion: Content: Published */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'node';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['value'] = 1;
$handler->display->display_options['filters']['status']['group'] = 1;
$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
/* Filter criterion: Content: Type */
$handler->display->display_options['filters']['type']['id'] = 'type';
$handler->display->display_options['filters']['type']['table'] = 'node';
$handler->display->display_options['filters']['type']['field'] = 'type';
$handler->display->display_options['filters']['type']['value'] = array(
  'exercise_submission' => 'exercise_submission',
);

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'submissions';
$handler->display->display_options['menu']['title'] = 'Your submissions';
$handler->display->display_options['menu']['weight'] = '0';
$handler->display->display_options['menu']['name'] = 'menu-cp-students';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;

