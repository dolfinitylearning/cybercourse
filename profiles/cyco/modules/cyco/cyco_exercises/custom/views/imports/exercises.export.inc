<?php

/* 
 * Exercises view. Import manually, since Features has trouble with it.
 */

$view = new view();
$view->name = 'exercises';
$view->description = 'List of all exercises';
$view->tag = 'default';
$view->base_table = 'node';
$view->human_name = 'Exercises';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Exercises';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'role';
$handler->display->display_options['access']['role'] = array(
  3 => '3',
  4 => '4',
  5 => '5',
  6 => '6',
  7 => '7',
);
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['query']['options']['disable_sql_rewrite'] = TRUE;
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '20';
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['grouping'] = array(
  0 => array(
    'field' => 'title',
    'rendered' => 0,
    'rendered_strip' => 0,
  ),
);
$handler->display->display_options['style_options']['columns'] = array(
  'nid' => 'nid',
  'body' => 'body',
  'edit_node_1' => 'edit_node_1',
  'title' => 'title',
  'title_1' => 'title_1',
  'field_rubric_item_weight' => 'field_rubric_item_weight',
  'field_categories' => 'field_categories',
  'edit_node' => 'edit_node',
);
$handler->display->display_options['style_options']['default'] = '-1';
$handler->display->display_options['style_options']['info'] = array(
  'nid' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'body' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'edit_node_1' => array(
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'title' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'title_1' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'field_rubric_item_weight' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => 'views-align-center',
    'separator' => '',
    'empty_column' => 0,
  ),
  'field_categories' => array(
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'edit_node' => array(
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
);
$handler->display->display_options['style_options']['sticky'] = TRUE;
/* Header: Global: Unfiltered text */
$handler->display->display_options['header']['area_text_custom']['id'] = 'area_text_custom';
$handler->display->display_options['header']['area_text_custom']['table'] = 'views';
$handler->display->display_options['header']['area_text_custom']['field'] = 'area_text_custom';
$handler->display->display_options['header']['area_text_custom']['empty'] = TRUE;
$handler->display->display_options['header']['area_text_custom']['content'] = '<p>Here are the exercises.</p>

';
/* Relationship: Entity Reference: Referenced Entity */
$handler->display->display_options['relationships']['field_rubric_items_target_id']['id'] = 'field_rubric_items_target_id';
$handler->display->display_options['relationships']['field_rubric_items_target_id']['table'] = 'field_data_field_rubric_items';
$handler->display->display_options['relationships']['field_rubric_items_target_id']['field'] = 'field_rubric_items_target_id';
/* Relationship: Entity Reference: Referencing entity */
$handler->display->display_options['relationships']['reverse_field_exercises_node']['id'] = 'reverse_field_exercises_node';
$handler->display->display_options['relationships']['reverse_field_exercises_node']['table'] = 'node';
$handler->display->display_options['relationships']['reverse_field_exercises_node']['field'] = 'reverse_field_exercises_node';
/* Field: Content: Nid */
$handler->display->display_options['fields']['nid']['id'] = 'nid';
$handler->display->display_options['fields']['nid']['table'] = 'node';
$handler->display->display_options['fields']['nid']['field'] = 'nid';
$handler->display->display_options['fields']['nid']['label'] = '';
$handler->display->display_options['fields']['nid']['exclude'] = TRUE;
$handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
/* Field: Content: Body */
$handler->display->display_options['fields']['field_body']['id'] = 'field_body';
$handler->display->display_options['fields']['field_body']['table'] = 'field_data_field_body';
$handler->display->display_options['fields']['field_body']['field'] = 'field_body';
$handler->display->display_options['fields']['field_body']['label'] = '';
$handler->display->display_options['fields']['field_body']['exclude'] = TRUE;
$handler->display->display_options['fields']['field_body']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['field_body']['type'] = 'swim_summary_or_trimmed_formatter';
$handler->display->display_options['fields']['field_body']['settings'] = array(
  'trim_length' => '600',
);
/* Field: Content: Keywords */
$handler->display->display_options['fields']['field_keywords']['id'] = 'field_keywords';
$handler->display->display_options['fields']['field_keywords']['table'] = 'field_data_field_keywords';
$handler->display->display_options['fields']['field_keywords']['field'] = 'field_keywords';
$handler->display->display_options['fields']['field_keywords']['exclude'] = TRUE;
$handler->display->display_options['fields']['field_keywords']['delta_offset'] = '0';
/* Field: Content: Workflow tags */
$handler->display->display_options['fields']['field_workflow_tags']['id'] = 'field_workflow_tags';
$handler->display->display_options['fields']['field_workflow_tags']['table'] = 'field_data_field_workflow_tags';
$handler->display->display_options['fields']['field_workflow_tags']['field'] = 'field_workflow_tags';
$handler->display->display_options['fields']['field_workflow_tags']['exclude'] = TRUE;
$handler->display->display_options['fields']['field_workflow_tags']['delta_offset'] = '0';
/* Field: Content: Published */
$handler->display->display_options['fields']['status']['id'] = 'status';
$handler->display->display_options['fields']['status']['table'] = 'node';
$handler->display->display_options['fields']['status']['field'] = 'status';
$handler->display->display_options['fields']['status']['label'] = '';
$handler->display->display_options['fields']['status']['exclude'] = TRUE;
$handler->display->display_options['fields']['status']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['status']['type'] = 'published-notpublished';
$handler->display->display_options['fields']['status']['not'] = 0;
/* Field: Content: Title */
$handler->display->display_options['fields']['title_2']['id'] = 'title_2';
$handler->display->display_options['fields']['title_2']['table'] = 'node';
$handler->display->display_options['fields']['title_2']['field'] = 'title';
$handler->display->display_options['fields']['title_2']['relationship'] = 'reverse_field_exercises_node';
$handler->display->display_options['fields']['title_2']['label'] = '';
$handler->display->display_options['fields']['title_2']['exclude'] = TRUE;
$handler->display->display_options['fields']['title_2']['element_label_colon'] = FALSE;
/* Field: Content: Title */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['label'] = '';
$handler->display->display_options['fields']['title']['exclude'] = TRUE;
$handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['title']['alter']['text'] = '<p class="exercise-view-exercise-title"><a href="/node/[nid]?destination=admin/structure/views/nojs/preview/exercises/default">[title]</a> ([nid])</p>

<div class="exercise-view-body">[field_body]</div>

<div class="exercise-view-course-pages">Used in pages: [title_2]</div>

<p class="exercise-view-terms">Workflow tags: [field_workflow_tags] &nbsp;&nbsp;&nbsp;Keywords: [field_keywords]</p>

<p class="exercise-view-status">Status: [status]</p>

<p class="exercise-view-rubric-label">Rubrics:</p>';
$handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
$handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
$handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['title']['hide_alter_empty'] = FALSE;
/* Field: Content: Title */
$handler->display->display_options['fields']['title_1']['id'] = 'title_1';
$handler->display->display_options['fields']['title_1']['table'] = 'node';
$handler->display->display_options['fields']['title_1']['field'] = 'title';
$handler->display->display_options['fields']['title_1']['relationship'] = 'field_rubric_items_target_id';
$handler->display->display_options['fields']['title_1']['label'] = '';
$handler->display->display_options['fields']['title_1']['element_label_colon'] = FALSE;
/* Sort criterion: Content: Title */
$handler->display->display_options['sorts']['title']['id'] = 'title';
$handler->display->display_options['sorts']['title']['table'] = 'node';
$handler->display->display_options['sorts']['title']['field'] = 'title';
/* Filter criterion: Content: Type */
$handler->display->display_options['filters']['type']['id'] = 'type';
$handler->display->display_options['filters']['type']['table'] = 'node';
$handler->display->display_options['filters']['type']['field'] = 'type';
$handler->display->display_options['filters']['type']['value'] = array(
  'exercise' => 'exercise',
);

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'exercises';
$handler->display->display_options['menu']['type'] = 'normal';
$handler->display->display_options['menu']['title'] = 'List exercises';
$handler->display->display_options['menu']['description'] = 'See all the exercises';
$handler->display->display_options['menu']['weight'] = '0';
$handler->display->display_options['menu']['name'] = 'menu-cp-authors';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;


