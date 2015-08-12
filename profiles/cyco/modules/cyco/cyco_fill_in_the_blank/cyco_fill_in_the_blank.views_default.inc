<?php
/**
 * @file
 * cyco_fill_in_the_blank.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function cyco_fill_in_the_blank_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'fill_in_the_blanks';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Fill-in-the-blanks';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Fill-in-the-blanks';
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
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'field_internal_name' => 'field_internal_name',
    'field_keywords' => 'field_keywords',
    'field_response_type' => 'field_response_type',
    'field_lowest' => 'field_lowest',
    'field_highest' => 'field_highest',
    'field_case_sensitive' => 'field_case_sensitive',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Internal name */
  $handler->display->display_options['fields']['field_internal_name']['id'] = 'field_internal_name';
  $handler->display->display_options['fields']['field_internal_name']['table'] = 'field_data_field_internal_name';
  $handler->display->display_options['fields']['field_internal_name']['field'] = 'field_internal_name';
  /* Field: Content: Keywords */
  $handler->display->display_options['fields']['field_keywords']['id'] = 'field_keywords';
  $handler->display->display_options['fields']['field_keywords']['table'] = 'field_data_field_keywords';
  $handler->display->display_options['fields']['field_keywords']['field'] = 'field_keywords';
  $handler->display->display_options['fields']['field_keywords']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['field_keywords']['delta_offset'] = '0';
  /* Field: Content: Body */
  $handler->display->display_options['fields']['field_body']['id'] = 'field_body';
  $handler->display->display_options['fields']['field_body']['table'] = 'field_data_field_body';
  $handler->display->display_options['fields']['field_body']['field'] = 'field_body';
  /* Field: Content: Response type */
  $handler->display->display_options['fields']['field_response_type']['id'] = 'field_response_type';
  $handler->display->display_options['fields']['field_response_type']['table'] = 'field_data_field_response_type';
  $handler->display->display_options['fields']['field_response_type']['field'] = 'field_response_type';
  $handler->display->display_options['fields']['field_response_type']['element_wrapper_type'] = 'div';
  /* Field: Content: Lowest */
  $handler->display->display_options['fields']['field_lowest']['id'] = 'field_lowest';
  $handler->display->display_options['fields']['field_lowest']['table'] = 'field_data_field_lowest';
  $handler->display->display_options['fields']['field_lowest']['field'] = 'field_lowest';
  $handler->display->display_options['fields']['field_lowest']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['field_lowest']['settings'] = array(
    'thousand_separator' => ',',
    'decimal_separator' => '.',
    'scale' => '2',
    'prefix_suffix' => 1,
  );
  /* Field: Content: Highest */
  $handler->display->display_options['fields']['field_highest']['id'] = 'field_highest';
  $handler->display->display_options['fields']['field_highest']['table'] = 'field_data_field_highest';
  $handler->display->display_options['fields']['field_highest']['field'] = 'field_highest';
  $handler->display->display_options['fields']['field_highest']['settings'] = array(
    'thousand_separator' => ' ',
    'decimal_separator' => '.',
    'scale' => '2',
    'prefix_suffix' => 1,
  );
  /* Field: Content: Correct answers */
  $handler->display->display_options['fields']['field_correct_text_answers']['id'] = 'field_correct_text_answers';
  $handler->display->display_options['fields']['field_correct_text_answers']['table'] = 'field_data_field_correct_text_answers';
  $handler->display->display_options['fields']['field_correct_text_answers']['field'] = 'field_correct_text_answers';
  $handler->display->display_options['fields']['field_correct_text_answers']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_correct_text_answers']['multi_type'] = 'ul';
  /* Field: Content: Case-sensitive */
  $handler->display->display_options['fields']['field_case_sensitive']['id'] = 'field_case_sensitive';
  $handler->display->display_options['fields']['field_case_sensitive']['table'] = 'field_data_field_case_sensitive';
  $handler->display->display_options['fields']['field_case_sensitive']['field'] = 'field_case_sensitive';
  /* Field: Content: Explanation */
  $handler->display->display_options['fields']['field_explanation']['id'] = 'field_explanation';
  $handler->display->display_options['fields']['field_explanation']['table'] = 'field_data_field_explanation';
  $handler->display->display_options['fields']['field_explanation']['field'] = 'field_explanation';
  /* Field: Content: Hints */
  $handler->display->display_options['fields']['field_hints']['id'] = 'field_hints';
  $handler->display->display_options['fields']['field_hints']['table'] = 'field_data_field_hints';
  $handler->display->display_options['fields']['field_hints']['field'] = 'field_hints';
  /* Field: Content: Notes */
  $handler->display->display_options['fields']['field_notes']['id'] = 'field_notes';
  $handler->display->display_options['fields']['field_notes']['table'] = 'field_data_field_notes';
  $handler->display->display_options['fields']['field_notes']['field'] = 'field_notes';
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['order'] = 'DESC';
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
    'fill_in_the_blank' => 'fill_in_the_blank',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'fill-in-the-blanks';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'List fill-in-the-blanks';
  $handler->display->display_options['menu']['name'] = 'menu-cp-actions';
  $export['fill_in_the_blanks'] = $view;

  return $export;
}
