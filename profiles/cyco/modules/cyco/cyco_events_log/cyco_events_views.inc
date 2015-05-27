<?php

function cyco_events_log_views_default_views() {
  $view = new view();
  $view->name = 'events';
  $view->description = 'Show events that have been logged.';
  $view->tag = 'default';
  $view->base_table = 'eck_cyco_event';
  $view->human_name = 'Events';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Events';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'id' => 'id',
    'field_activity_params' => 'field_activity_params',
    'field_activity_type' => 'field_activity_type',
    'uid' => 'uid',
    'field_class' => 'field_class',
    'field_class_activity_type' => 'field_class_activity_type',
    'created' => 'created',
    'type' => 'type',
    'delete_link' => 'delete_link',
    'edit_link' => 'edit_link',
    'view_link' => 'view_link',
    'field_node' => 'field_node',
    'field_submission_activity_type' => 'field_submission_activity_type',
    'field_submission_files' => 'field_submission_files',
    'field_submission' => 'field_submission',
    'field_submission_text' => 'field_submission_text',
    'field_summary' => 'field_summary',
    'field_exercise' => 'field_exercise',
    'field_version' => 'field_version',
  );
  $handler->display->display_options['style_options']['default'] = 'created';
  $handler->display->display_options['style_options']['info'] = array(
    'id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_activity_params' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_activity_type' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'uid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_class' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_class_activity_type' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'type' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'delete_link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'view_link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_node' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_submission_activity_type' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_submission_files' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_submission' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_submission_text' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_summary' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_exercise' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_version' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: Cyco event: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'eck_cyco_event';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: Cyco event: Created */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'eck_cyco_event';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'When';
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'long';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'User';
  /* Field: Cyco event: cyco_event type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'eck_cyco_event';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['label'] = 'Event type';
  /* Field: Cyco event: Author */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'eck_cyco_event';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['label'] = 'User id';
  $handler->display->display_options['fields']['uid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['uid']['separator'] = '';
  /* Field: Cyco event: Id */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'eck_cyco_event';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['exclude'] = TRUE;
  /* Field: Cyco event: Activity params */
  $handler->display->display_options['fields']['field_activity_params']['id'] = 'field_activity_params';
  $handler->display->display_options['fields']['field_activity_params']['table'] = 'field_data_field_activity_params';
  $handler->display->display_options['fields']['field_activity_params']['field'] = 'field_activity_params';
  $handler->display->display_options['fields']['field_activity_params']['exclude'] = TRUE;
  /* Field: Cyco event: Activity type */
  $handler->display->display_options['fields']['field_activity_type']['id'] = 'field_activity_type';
  $handler->display->display_options['fields']['field_activity_type']['table'] = 'field_data_field_activity_type';
  $handler->display->display_options['fields']['field_activity_type']['field'] = 'field_activity_type';
  $handler->display->display_options['fields']['field_activity_type']['exclude'] = TRUE;
  /* Field: Cyco event: Class */
  $handler->display->display_options['fields']['field_class']['id'] = 'field_class';
  $handler->display->display_options['fields']['field_class']['table'] = 'field_data_field_class';
  $handler->display->display_options['fields']['field_class']['field'] = 'field_class';
  $handler->display->display_options['fields']['field_class']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_class']['settings'] = array(
    'link' => 0,
  );
  /* Field: Cyco event: Class activity type */
  $handler->display->display_options['fields']['field_class_activity_type']['id'] = 'field_class_activity_type';
  $handler->display->display_options['fields']['field_class_activity_type']['table'] = 'field_data_field_class_activity_type';
  $handler->display->display_options['fields']['field_class_activity_type']['field'] = 'field_class_activity_type';
  $handler->display->display_options['fields']['field_class_activity_type']['exclude'] = TRUE;
  /* Field: Cyco event: Node */
  $handler->display->display_options['fields']['field_node']['id'] = 'field_node';
  $handler->display->display_options['fields']['field_node']['table'] = 'field_data_field_node';
  $handler->display->display_options['fields']['field_node']['field'] = 'field_node';
  $handler->display->display_options['fields']['field_node']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_node']['settings'] = array(
    'link' => 0,
  );
  /* Field: Cyco event: Submission activity type */
  $handler->display->display_options['fields']['field_submission_activity_type']['id'] = 'field_submission_activity_type';
  $handler->display->display_options['fields']['field_submission_activity_type']['table'] = 'field_data_field_submission_activity_type';
  $handler->display->display_options['fields']['field_submission_activity_type']['field'] = 'field_submission_activity_type';
  $handler->display->display_options['fields']['field_submission_activity_type']['exclude'] = TRUE;
  /* Field: Cyco event: Submission files */
  $handler->display->display_options['fields']['field_submission_files']['id'] = 'field_submission_files';
  $handler->display->display_options['fields']['field_submission_files']['table'] = 'field_data_field_submission_files';
  $handler->display->display_options['fields']['field_submission_files']['field'] = 'field_submission_files';
  $handler->display->display_options['fields']['field_submission_files']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_submission_files']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_submission_files']['delta_offset'] = '0';
  /* Field: Cyco event: Submission node */
  $handler->display->display_options['fields']['field_submission']['id'] = 'field_submission';
  $handler->display->display_options['fields']['field_submission']['table'] = 'field_data_field_submission';
  $handler->display->display_options['fields']['field_submission']['field'] = 'field_submission';
  $handler->display->display_options['fields']['field_submission']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_submission']['settings'] = array(
    'link' => 0,
  );
  /* Field: Cyco event: Submission text */
  $handler->display->display_options['fields']['field_submission_text']['id'] = 'field_submission_text';
  $handler->display->display_options['fields']['field_submission_text']['table'] = 'field_data_field_submission_text';
  $handler->display->display_options['fields']['field_submission_text']['field'] = 'field_submission_text';
  $handler->display->display_options['fields']['field_submission_text']['exclude'] = TRUE;
  /* Field: Field: Exercise */
  $handler->display->display_options['fields']['field_exercise']['id'] = 'field_exercise';
  $handler->display->display_options['fields']['field_exercise']['table'] = 'field_data_field_exercise';
  $handler->display->display_options['fields']['field_exercise']['field'] = 'field_exercise';
  $handler->display->display_options['fields']['field_exercise']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_exercise']['settings'] = array(
    'link' => 0,
  );
  /* Field: Field: Version */
  $handler->display->display_options['fields']['field_version']['id'] = 'field_version';
  $handler->display->display_options['fields']['field_version']['table'] = 'field_data_field_version';
  $handler->display->display_options['fields']['field_version']['field'] = 'field_version';
  $handler->display->display_options['fields']['field_version']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_version']['settings'] = array(
    'thousand_separator' => '',
    'prefix_suffix' => 1,
  );
  /* Field: Cyco event: Summary */
  $handler->display->display_options['fields']['field_summary']['id'] = 'field_summary';
  $handler->display->display_options['fields']['field_summary']['table'] = 'field_data_field_summary';
  $handler->display->display_options['fields']['field_summary']['field'] = 'field_summary';
  /* Field: Cyco event: Edit link */
  $handler->display->display_options['fields']['edit_link']['id'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['table'] = 'eck_cyco_event';
  $handler->display->display_options['fields']['edit_link']['field'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['label'] = 'Edit';
  /* Field: Cyco event: Delete link */
  $handler->display->display_options['fields']['delete_link']['id'] = 'delete_link';
  $handler->display->display_options['fields']['delete_link']['table'] = 'eck_cyco_event';
  $handler->display->display_options['fields']['delete_link']['field'] = 'delete_link';
  $handler->display->display_options['fields']['delete_link']['label'] = 'Delete';
  /* Field: Cyco event: Link */
  $handler->display->display_options['fields']['view_link']['id'] = 'view_link';
  $handler->display->display_options['fields']['view_link']['table'] = 'eck_cyco_event';
  $handler->display->display_options['fields']['view_link']['field'] = 'view_link';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'events';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Events';
  $handler->display->display_options['menu']['name'] = 'menu-cp-actions';

  $views[$view->name] = $view;

  return $views;
}


