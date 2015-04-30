<?php
/**
 * @file
 * cyco_patterns.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function cyco_patterns_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-pattern-field_actions'
  $field_instances['node-pattern-field_actions'] = array(
    'bundle' => 'pattern',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'What to do when the situation occurs.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'swim',
        'settings' => array(),
        'type' => 'swim_default_formatter',
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
    'field_name' => 'field_actions',
    'label' => 'Actions',
    'required' => 0,
    'settings' => array(
      'exclude_cv' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'swim',
      'settings' => array(),
      'type' => 'swim_widget',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'node-pattern-field_attachments'
  $field_instances['node-pattern-field_attachments'] = array(
    'bundle' => 'pattern',
    'deleted' => 0,
    'description' => 'Attached files.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'file',
        'settings' => array(),
        'type' => 'file_default',
        'weight' => 6,
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
    'field_name' => 'field_attachments',
    'label' => 'Attachments',
    'required' => 0,
    'settings' => array(
      'description_field' => 1,
      'exclude_cv' => FALSE,
      'file_directory' => 'cycourse/bucket',
      'file_extensions' => '',
      'max_filesize' => '20Mb',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'file',
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
        'progress_indicator' => 'throbber',
      ),
      'type' => 'file_generic',
      'weight' => 8,
    ),
  );

  // Exported field_instance: 'node-pattern-field_explanation'
  $field_instances['node-pattern-field_explanation'] = array(
    'bundle' => 'pattern',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Why the pattern makes sense.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'swim',
        'settings' => array(),
        'type' => 'swim_default_formatter',
        'weight' => 5,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_explanation',
    'label' => 'Explanation',
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
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'node-pattern-field_images'
  $field_instances['node-pattern-field_images'] = array(
    'bundle' => 'pattern',
    'deleted' => 0,
    'description' => 'Images for your content.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 7,
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
    'field_name' => 'field_images',
    'label' => 'Images',
    'required' => 0,
    'settings' => array(
      'alt_field' => 0,
      'default_image' => 0,
      'exclude_cv' => FALSE,
      'file_directory' => 'cycourse/bucket',
      'file_extensions' => 'png gif jpg jpeg svg',
      'max_filesize' => '5Mb',
      'max_resolution' => '1200x1200',
      'min_resolution' => '',
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
        'insert' => 1,
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
      'weight' => 7,
    ),
  );

  // Exported field_instance: 'node-pattern-field_internal_name'
  $field_instances['node-pattern-field_internal_name'] = array(
    'bundle' => 'pattern',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The internal name of the pattern. Lowercase letters, digits, and underscores only, e.g., post_tested_loop1. Use the internal name to insert the pattern in content.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
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
    'label' => 'Internal name',
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

  // Exported field_instance: 'node-pattern-field_keywords'
  $field_instances['node-pattern-field_keywords'] = array(
    'bundle' => 'pattern',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Keywords describing the pattern.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
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
    'field_name' => 'field_keywords',
    'label' => 'Keywords',
    'required' => 0,
    'settings' => array(
      'exclude_cv' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'taxonomy',
      'settings' => array(
        'autocomplete_path' => 'taxonomy/autocomplete',
        'size' => 60,
      ),
      'type' => 'taxonomy_autocomplete',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'node-pattern-field_situation'
  $field_instances['node-pattern-field_situation'] = array(
    'bundle' => 'pattern',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'What is observed.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'swim',
        'settings' => array(),
        'type' => 'swim_default_formatter',
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
    'field_name' => 'field_situation',
    'label' => 'Situation',
    'required' => 0,
    'settings' => array(
      'exclude_cv' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'swim',
      'settings' => array(),
      'type' => 'swim_widget',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'node-pattern-field_workflow_tags'
  $field_instances['node-pattern-field_workflow_tags'] = array(
    'bundle' => 'pattern',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'What work needs to be done on this pattern?',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
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
    'field_name' => 'field_workflow_tags',
    'label' => 'Workflow tags',
    'required' => 0,
    'settings' => array(
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

  // Translatables
  // Included for use with string extractors like potx.
  t('Actions');
  t('Attached files.');
  t('Attachments');
  t('Explanation');
  t('Images');
  t('Images for your content.');
  t('Internal name');
  t('Keywords');
  t('Keywords describing the pattern.');
  t('Situation');
  t('The internal name of the pattern. Lowercase letters, digits, and underscores only, e.g., post_tested_loop1. Use the internal name to insert the pattern in content.');
  t('What is observed.');
  t('What to do when the situation occurs.');
  t('What work needs to be done on this pattern?');
  t('Why the pattern makes sense.');
  t('Workflow tags');

  return $field_instances;
}
