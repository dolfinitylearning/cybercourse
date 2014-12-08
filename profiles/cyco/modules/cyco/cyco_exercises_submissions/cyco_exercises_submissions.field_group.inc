<?php
/**
 * @file
 * cyco_exercises_submissions.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function cyco_exercises_submissions_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_feedback_phrases|user|user|form';
  $field_group->group_name = 'group_feedback_phrases';
  $field_group->entity_type = 'user';
  $field_group->bundle = 'user';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Feedback phrases',
    'weight' => '5',
    'children' => array(
      0 => 'field_greetings',
      1 => 'field_overall_good',
      2 => 'field_overall_needs_work',
      3 => 'field_overall_poor',
      4 => 'field_signature',
      5 => 'field_good_cutoff',
      6 => 'field_needs_work_cutoff',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Feedback phrases',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-feedback-phrases field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_feedback_phrases|user|user|form'] = $field_group;

  return $export;
}
