<?php
/**
 * @file
 * cyco_badges.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function cyco_badges_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-badge-field_body'
  $field_instances['node-badge-field_body'] = array(
    'bundle' => 'badge',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Description of the badge.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'swim',
        'settings' => array(),
        'type' => 'swim_default_formatter',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'module' => 'swim',
        'settings' => array(
          'trim_length' => 600,
        ),
        'type' => 'swim_summary_or_trimmed_formatter',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'exclude_cv' => 0,
    'field_name' => 'field_body',
    'label' => 'Description',
    'required' => 0,
    'settings' => array(
      'exclude_cv' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'swim',
      'settings' => array(),
      'type' => 'swim_with_summary_widget',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'node-badge-field_exercises'
  $field_instances['node-badge-field_exercises'] = array(
    'bundle' => 'badge',
    'default_value' => NULL,
    'default_value_function' => '',
    'deleted' => 0,
    'description' => 'Exercises students must complete to earn this badge.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => 1,
        ),
        'type' => 'entityreference_label',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'exclude_cv' => 0,
    'field_name' => 'field_exercises',
    'label' => 'Exercises',
    'required' => 0,
    'settings' => array(
      'behaviors' => array(
        'prepopulate' => array(
          'status' => 0,
        ),
      ),
      'exclude_cv' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'node-badge-field_internal_name'
  $field_instances['node-badge-field_internal_name'] = array(
    'bundle' => 'badge',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The machine name of the badge. Lowercase letters, digits, and underscores only, e.g., javascript_level_1. The machine name identifies the badge to outside services, e.g., OpenBadge.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 4,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'exclude_cv' => 0,
    'field_name' => 'field_internal_name',
    'label' => 'Machine name',
    'required' => 1,
    'settings' => array(
      'exclude_cv' => FALSE,
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'node-badge-field_locked_badge_image'
  $field_instances['node-badge-field_locked_badge_image'] = array(
    'bundle' => 'badge',
    'deleted' => 0,
    'description' => 'Image shown when a student has not earned the badge. Must be png, minimum 90x90, maximum file size 256Kb. ',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => '',
        ),
        'type' => 'image',
        'weight' => 3,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'exclude_cv' => 0,
    'field_name' => 'field_locked_badge_image',
    'label' => 'Locked image',
    'required' => 1,
    'settings' => array(
      'alt_field' => 1,
      'default_image' => 38,
      'exclude_cv' => FALSE,
      'file_directory' => 'cycourse/library/badges',
      'file_extensions' => 'png',
      'max_filesize' => '256kb',
      'max_resolution' => '',
      'min_resolution' => '90x90',
      'title_field' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'image',
      'settings' => array(
        'filefield_sources' => array(
          'filefield_sources' => array(
            'attach' => 0,
            'clipboard' => 0,
            'imce' => 'imce',
            'reference' => 0,
            'remote' => 0,
            'upload' => 'upload',
          ),
          'source_attach' => array(
            'absolute' => 0,
            'attach_mode' => 'move',
            'path' => 'file_attach',
          ),
          'source_imce' => array(
            'imce_mode' => 1,
          ),
          'source_reference' => array(
            'autocomplete' => 0,
          ),
        ),
        'insert' => 0,
        'insert_absolute' => 0,
        'insert_class' => '',
        'insert_default' => 'auto',
        'insert_styles' => array(
          'auto' => 'auto',
          'icon_link' => 0,
          'image' => 0,
          'image_large' => 0,
          'image_medium' => 0,
          'image_thumbnail' => 0,
          'link' => 0,
        ),
        'insert_width' => '',
        'preview_image_style' => 'thumbnail',
        'progress_indicator' => 'throbber',
      ),
      'type' => 'image_image',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'node-badge-field_unlocked_badge_image'
  $field_instances['node-badge-field_unlocked_badge_image'] = array(
    'bundle' => 'badge',
    'deleted' => 0,
    'description' => 'Image shown when a student has earned the badge. Must be png, minimum 90x90, maximum file size 256Kb. ',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => '',
        ),
        'type' => 'image',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'exclude_cv' => 0,
    'field_name' => 'field_unlocked_badge_image',
    'label' => 'Unlocked image',
    'required' => 1,
    'settings' => array(
      'alt_field' => 1,
      'default_image' => 37,
      'exclude_cv' => FALSE,
      'file_directory' => 'cycourse/library/badges',
      'file_extensions' => 'png',
      'max_filesize' => '256kb',
      'max_resolution' => '',
      'min_resolution' => '90x90',
      'title_field' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'image',
      'settings' => array(
        'filefield_sources' => array(
          'filefield_sources' => array(
            'attach' => 0,
            'clipboard' => 0,
            'imce' => 'imce',
            'reference' => 0,
            'remote' => 0,
            'upload' => 'upload',
          ),
          'source_attach' => array(
            'absolute' => 0,
            'attach_mode' => 'move',
            'path' => 'file_attach',
          ),
          'source_imce' => array(
            'imce_mode' => 1,
          ),
          'source_reference' => array(
            'autocomplete' => 0,
          ),
        ),
        'insert' => 0,
        'insert_absolute' => 0,
        'insert_class' => '',
        'insert_default' => 'auto',
        'insert_styles' => array(
          'auto' => 'auto',
          'icon_link' => 0,
          'image' => 0,
          'image_large' => 0,
          'image_medium' => 0,
          'image_thumbnail' => 0,
          'link' => 0,
        ),
        'insert_width' => '',
        'preview_image_style' => 'thumbnail',
        'progress_indicator' => 'throbber',
      ),
      'type' => 'image_image',
      'weight' => 4,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Description');
  t('Description of the badge.');
  t('Exercises');
  t('Exercises students must complete to earn this badge.');
  t('Image shown when a student has earned the badge. Must be png, minimum 90x90, maximum file size 256Kb. ');
  t('Image shown when a student has not earned the badge. Must be png, minimum 90x90, maximum file size 256Kb. ');
  t('Locked image');
  t('Machine name');
  t('The machine name of the badge. Lowercase letters, digits, and underscores only, e.g., javascript_level_1. The machine name identifies the badge to outside services, e.g., OpenBadge.');
  t('Unlocked image');

  return $field_instances;
}
