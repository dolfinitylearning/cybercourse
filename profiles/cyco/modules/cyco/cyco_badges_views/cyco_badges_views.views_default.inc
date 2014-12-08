<?php
/**
 * @file
 * cyco_badges_views.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function cyco_badges_views_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'badges';
  $view->description = 'Badge list for authors, used to admin badges.';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Badges';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Badge types';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'field_body' => 'field_body',
    'title_1' => 'title_1',
    'edit_node' => 'edit_node',
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
    'field_body' => array(
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
    'edit_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Header: Global: Unfiltered text */
  $handler->display->display_options['header']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['header']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['header']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['header']['area_text_custom']['content'] = '<p>Here are badges that students can earn. Each badge is a group of exercises. When students complete all of the exercises, they earn the badge.</p>

<p>Students can send their badges into their <a href="http://openbadges.org/">OpenBadge</a> backpack. Other people can verify that they have earned the badges.</p>';
  /* No results behavior: Global: Unfiltered text */
  $handler->display->display_options['empty']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['empty']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['empty'] = TRUE;
  $handler->display->display_options['empty']['area_text_custom']['content'] = 'Sorry, no badge types have been defined.';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Internal name */
  $handler->display->display_options['fields']['field_internal_name']['id'] = 'field_internal_name';
  $handler->display->display_options['fields']['field_internal_name']['table'] = 'field_data_field_internal_name';
  $handler->display->display_options['fields']['field_internal_name']['field'] = 'field_internal_name';
  $handler->display->display_options['fields']['field_internal_name']['label'] = '';
  $handler->display->display_options['fields']['field_internal_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_internal_name']['element_label_colon'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['field_body']['id'] = 'field_body';
  $handler->display->display_options['fields']['field_body']['table'] = 'field_data_field_body';
  $handler->display->display_options['fields']['field_body']['field'] = 'field_body';
  $handler->display->display_options['fields']['field_body']['label'] = 'Badge';
  $handler->display->display_options['fields']['field_body']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_body']['alter']['text'] = '<strong>[title]</strong><br>
<br>
[field_internal_name]<br>
<br>
[field_body]';
  $handler->display->display_options['fields']['field_body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_body']['type'] = 'swim_summary_or_trimmed_formatter';
  $handler->display->display_options['fields']['field_body']['settings'] = array(
    'trim_length' => '200',
  );
  /* Field: Content: Exercises */
  $handler->display->display_options['fields']['field_exercises']['id'] = 'field_exercises';
  $handler->display->display_options['fields']['field_exercises']['table'] = 'field_data_field_exercises';
  $handler->display->display_options['fields']['field_exercises']['field'] = 'field_exercises';
  $handler->display->display_options['fields']['field_exercises']['settings'] = array(
    'link' => 1,
  );
  $handler->display->display_options['fields']['field_exercises']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_exercises']['separator'] = '<br>';
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = '';
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['edit_node']['text'] = 'Edit';
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
    'badge' => 'badge',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'badges';
  $handler->display->display_options['menu']['title'] = 'List badges';
  $handler->display->display_options['menu']['description'] = 'Show the badges students can earn.';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'menu-cp-actions';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['badges'] = $view;

  $view = new view();
  $view->name = 'badges_public';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Badges (public)';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Badges';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = TRUE;
  /* Header: Global: Unfiltered text */
  $handler->display->display_options['header']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['header']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['header']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['header']['area_text_custom']['content'] = '<p>Students earn badges when they master certain skills. For instance, a student who completes 20 JavaScript programming exercises might earn the Basic JavaScript Proficiency badge.</p>

<p>CyberCourse uses Mozilla\'s <a href="http://openbadges.org/" target="_blank">Open Badges</a> system. Students can add Cyco badges to their Mozilla badge <a href="http://backpack.openbadges.org/" target="_blank">Backpack</a>. Employers, universities, and others can verify that students have earned the badges they claim.</p>';
  /* Field: Cyco badges: Badge */
  $handler->display->display_options['fields']['badge_image_for_current_user']['id'] = 'badge_image_for_current_user';
  $handler->display->display_options['fields']['badge_image_for_current_user']['table'] = 'cyco_badges';
  $handler->display->display_options['fields']['badge_image_for_current_user']['field'] = 'badge_image_for_current_user';
  $handler->display->display_options['fields']['badge_image_for_current_user']['label'] = '';
  $handler->display->display_options['fields']['badge_image_for_current_user']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['field_body']['id'] = 'field_body';
  $handler->display->display_options['fields']['field_body']['table'] = 'field_data_field_body';
  $handler->display->display_options['fields']['field_body']['field'] = 'field_body';
  $handler->display->display_options['fields']['field_body']['label'] = '';
  $handler->display->display_options['fields']['field_body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_body']['type'] = 'swim_summary_or_trimmed_formatter';
  $handler->display->display_options['fields']['field_body']['settings'] = array(
    'trim_length' => '400',
  );
  /* Field: Cyco badges: Has the current user earned the badge? */
  $handler->display->display_options['fields']['has_user_earned_badge']['id'] = 'has_user_earned_badge';
  $handler->display->display_options['fields']['has_user_earned_badge']['table'] = 'cyco_badges';
  $handler->display->display_options['fields']['has_user_earned_badge']['field'] = 'has_user_earned_badge';
  $handler->display->display_options['fields']['has_user_earned_badge']['label'] = 'Earned?';
  $handler->display->display_options['fields']['has_user_earned_badge']['element_label_colon'] = FALSE;
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
    'badge' => 'badge',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'badges-public';
  $handler->display->display_options['menu']['title'] = 'Badges';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'menu-tools';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['badges_public'] = $view;

  return $export;
}
