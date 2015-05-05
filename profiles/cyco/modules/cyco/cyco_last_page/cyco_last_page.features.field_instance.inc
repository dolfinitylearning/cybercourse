<?php
/**
 * @file
 * cyco_last_page.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function cyco_last_page_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'user-user-field_last_course_page_seen'
  $field_instances['user-user-field_last_course_page_seen'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Last course page the user saw.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 14,
      ),
    ),
    'entity_type' => 'user',
    'exclude_cv' => 0,
    'field_name' => 'field_last_course_page_seen',
    'label' => 'Last course page seen',
    'required' => 0,
    'settings' => array(
      'exclude_cv' => FALSE,
      'text_processing' => 0,
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 15,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Last course page seen');
  t('Last course page the user saw.');

  return $field_instances;
}
