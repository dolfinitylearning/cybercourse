<?php
/**
 * @file
 * cyco_patterns.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function cyco_patterns_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'patterns';
  $view->description = 'Pattern list that anyone can see.';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Patterns public';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Patterns';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'field_actions' => 'field_actions',
    'delete_node' => 'delete_node',
    'edit_node' => 'edit_node',
    'field_pattern_categories' => 'field_pattern_categories',
    'field_situation' => 'field_situation',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_actions' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'delete_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_pattern_categories' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_situation' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = 'A pattern is a common way of doing things. Here are the patterns on this site.';
  $handler->display->display_options['header']['area']['format'] = 'plain_text';
  /* Field: Content: Pattern categories */
  $handler->display->display_options['fields']['field_pattern_categories']['id'] = 'field_pattern_categories';
  $handler->display->display_options['fields']['field_pattern_categories']['table'] = 'field_data_field_pattern_categories';
  $handler->display->display_options['fields']['field_pattern_categories']['field'] = 'field_pattern_categories';
  $handler->display->display_options['fields']['field_pattern_categories']['label'] = '';
  $handler->display->display_options['fields']['field_pattern_categories']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_pattern_categories']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_pattern_categories']['delta_offset'] = '0';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '[title]<br>
<div class="categories">[field_pattern_categories]</div>';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Situation */
  $handler->display->display_options['fields']['field_situation']['id'] = 'field_situation';
  $handler->display->display_options['fields']['field_situation']['table'] = 'field_data_field_situation';
  $handler->display->display_options['fields']['field_situation']['field'] = 'field_situation';
  $handler->display->display_options['fields']['field_situation']['click_sort_column'] = 'pure_rest';
  $handler->display->display_options['fields']['field_situation']['settings'] = array(
    'trim_length' => '600',
  );
  /* Field: Content: Actions */
  $handler->display->display_options['fields']['field_actions']['id'] = 'field_actions';
  $handler->display->display_options['fields']['field_actions']['table'] = 'field_data_field_actions';
  $handler->display->display_options['fields']['field_actions']['field'] = 'field_actions';
  $handler->display->display_options['fields']['field_actions']['click_sort_column'] = 'pure_rest';
  $handler->display->display_options['fields']['field_actions']['settings'] = array(
    'trim_length' => '600',
  );
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
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
    'pattern' => 'pattern',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'patterns-public';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Patterns';
  $handler->display->display_options['menu']['description'] = 'See all of the patterns used in the course';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'menu-tools';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['patterns'] = $view;

  $view = new view();
  $view->name = 'patterns_privilaged';
  $view->description = 'Pattern list that anyone can see.';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Patterns';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Patterns';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    3 => '3',
    4 => '4',
    5 => '5',
    6 => '6',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'field_actions' => 'field_actions',
    'delete_node' => 'delete_node',
    'edit_node' => 'edit_node',
    'field_pattern_categories' => 'field_pattern_categories',
    'field_situation' => 'field_situation',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_actions' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'delete_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_pattern_categories' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_situation' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = 'A pattern is a common way of doing things. Here are the patterns used in the course.';
  $handler->display->display_options['header']['area']['format'] = 'plain_text';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  /* Field: Content: Pattern categories */
  $handler->display->display_options['fields']['field_pattern_categories']['id'] = 'field_pattern_categories';
  $handler->display->display_options['fields']['field_pattern_categories']['table'] = 'field_data_field_pattern_categories';
  $handler->display->display_options['fields']['field_pattern_categories']['field'] = 'field_pattern_categories';
  $handler->display->display_options['fields']['field_pattern_categories']['label'] = '';
  $handler->display->display_options['fields']['field_pattern_categories']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_pattern_categories']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_pattern_categories']['delta_offset'] = '0';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '[title] ([nid])<br>
[field_pattern_categories]';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Situation */
  $handler->display->display_options['fields']['field_situation']['id'] = 'field_situation';
  $handler->display->display_options['fields']['field_situation']['table'] = 'field_data_field_situation';
  $handler->display->display_options['fields']['field_situation']['field'] = 'field_situation';
  $handler->display->display_options['fields']['field_situation']['type'] = 'swim_summary_or_trimmed_formatter';
  $handler->display->display_options['fields']['field_situation']['settings'] = array(
    'trim_length' => '600',
  );
  /* Field: Content: Actions */
  $handler->display->display_options['fields']['field_actions']['id'] = 'field_actions';
  $handler->display->display_options['fields']['field_actions']['table'] = 'field_data_field_actions';
  $handler->display->display_options['fields']['field_actions']['field'] = 'field_actions';
  $handler->display->display_options['fields']['field_actions']['type'] = 'swim_summary_or_trimmed_formatter';
  $handler->display->display_options['fields']['field_actions']['settings'] = array(
    'trim_length' => '600',
  );
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = '';
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['edit_node']['text'] = 'Edit';
  /* Field: Content: Delete link */
  $handler->display->display_options['fields']['delete_node']['id'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['delete_node']['field'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['label'] = '';
  $handler->display->display_options['fields']['delete_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['delete_node']['text'] = 'Delete';
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
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
    'pattern' => 'pattern',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'patterns';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'List patterns';
  $handler->display->display_options['menu']['description'] = 'See all of the patterns.';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'menu-control-panel-1';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['patterns_privilaged'] = $view;

  return $export;
}