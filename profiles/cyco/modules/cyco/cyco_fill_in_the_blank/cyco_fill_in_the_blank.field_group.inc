<?php
/**
 * @file
 * cyco_fill_in_the_blank.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function cyco_fill_in_the_blank_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_correct_number|node|fill_in_the_blank|form';
  $field_group->group_name = 'group_correct_number';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'fill_in_the_blank';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Correct number',
    'weight' => '5',
    'children' => array(
      0 => 'field_lowest',
      1 => 'field_highest',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-correct-number field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_correct_number|node|fill_in_the_blank|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_correct_text|node|fill_in_the_blank|form';
  $field_group->group_name = 'group_correct_text';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'fill_in_the_blank';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Correct text',
    'weight' => '6',
    'children' => array(
      0 => 'field_case_sensitive',
      1 => 'field_correct_text_answers',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-correct-text field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_correct_text|node|fill_in_the_blank|form'] = $field_group;

  return $export;
}
