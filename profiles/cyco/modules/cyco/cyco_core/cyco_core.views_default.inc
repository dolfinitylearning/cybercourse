<?php
/**
 * @file
 * cyco_core.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function cyco_core_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'blueprints_and_keywords';
  $view->description = 'See all blueprint pages and their keywords';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Blueprints and keywords';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Blueprints and keywords';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'edit any blueprint_page content';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'field_blueprint_keywords' => 'field_blueprint_keywords',
    'field_workflow_tags' => 'field_workflow_tags',
    'changed' => 'changed',
    'status' => 'status',
  );
  $handler->display->display_options['style_options']['default'] = 'title';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_blueprint_keywords' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_workflow_tags' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'changed' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
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
  $handler->display->display_options['header']['area_text_custom']['content'] = 'Here are all the blueprint pages. You can sort the table by clicking on the column headings. Click on a keyword or tag to show items with that keyword or tag. ';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Blueprint keywords */
  $handler->display->display_options['fields']['field_blueprint_keywords']['id'] = 'field_blueprint_keywords';
  $handler->display->display_options['fields']['field_blueprint_keywords']['table'] = 'field_data_field_blueprint_keywords';
  $handler->display->display_options['fields']['field_blueprint_keywords']['field'] = 'field_blueprint_keywords';
  /* Field: Content: Workflow tags */
  $handler->display->display_options['fields']['field_workflow_tags']['id'] = 'field_workflow_tags';
  $handler->display->display_options['fields']['field_workflow_tags']['table'] = 'field_data_field_workflow_tags';
  $handler->display->display_options['fields']['field_workflow_tags']['field'] = 'field_workflow_tags';
  $handler->display->display_options['fields']['field_workflow_tags']['delta_offset'] = '0';
  /* Field: Content: Updated date */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['date_format'] = 'short';
  $handler->display->display_options['fields']['changed']['second_date_format'] = 'long';
  /* Field: Content: Published */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['order'] = 'DESC';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'blueprint_page' => 'blueprint_page',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'blueprints-and-keywords';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'List blueprint pages and keywords';
  $handler->display->display_options['menu']['description'] = 'See all blueprint pages (including unpublished), and their keywords';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'menu-cp-authors';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['blueprints_and_keywords'] = $view;

  return $export;
}
