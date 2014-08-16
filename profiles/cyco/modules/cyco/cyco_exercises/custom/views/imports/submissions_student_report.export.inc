<?php

$view = new view();
$view->name = 'submissions_student_report';
$view->description = 'Report for students on their submissions.';
$view->tag = 'default';
$view->base_table = 'node';
$view->human_name = 'Submissions (student report)';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Your submissions';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'role';
$handler->display->display_options['access']['role'] = array(
  9 => '9',
);
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '20';
$handler->display->display_options['style_plugin'] = 'table';
/* Header: Global: Unfiltered text */
$handler->display->display_options['header']['area_text_custom']['id'] = 'area_text_custom';
$handler->display->display_options['header']['area_text_custom']['table'] = 'views';
$handler->display->display_options['header']['area_text_custom']['field'] = 'area_text_custom';
$handler->display->display_options['header']['area_text_custom']['content'] = 'Here are your exercise submissions.';
/* No results behavior: Global: Unfiltered text */
$handler->display->display_options['empty']['area_text_custom']['id'] = 'area_text_custom';
$handler->display->display_options['empty']['area_text_custom']['table'] = 'views';
$handler->display->display_options['empty']['area_text_custom']['field'] = 'area_text_custom';
$handler->display->display_options['empty']['area_text_custom']['empty'] = TRUE;
$handler->display->display_options['empty']['area_text_custom']['content'] = 'Nothing found.';
/* Relationship: Entity Reference: Referenced Entity */
$handler->display->display_options['relationships']['field_exercise_target_id']['id'] = 'field_exercise_target_id';
$handler->display->display_options['relationships']['field_exercise_target_id']['table'] = 'field_data_field_exercise';
$handler->display->display_options['relationships']['field_exercise_target_id']['field'] = 'field_exercise_target_id';
/* Field: Cyco exercises: Completion badge */
$handler->display->display_options['fields']['completion_badge']['id'] = 'completion_badge';
$handler->display->display_options['fields']['completion_badge']['table'] = 'cyco_exercises';
$handler->display->display_options['fields']['completion_badge']['field'] = 'completion_badge';
$handler->display->display_options['fields']['completion_badge']['label'] = '';
$handler->display->display_options['fields']['completion_badge']['element_label_colon'] = FALSE;
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
$handler->display->display_options['arguments']['uid']['default_action'] = 'default';
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
$handler->display->display_options['path'] = 'submissions-student-report';
$handler->display->display_options['menu']['type'] = 'normal';
$handler->display->display_options['menu']['title'] = 'Your submissions';
$handler->display->display_options['menu']['name'] = 'menu-cp-students';
