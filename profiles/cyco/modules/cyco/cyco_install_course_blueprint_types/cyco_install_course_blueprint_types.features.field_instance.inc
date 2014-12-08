<?php
/**
 * @file
 * cyco_install_course_blueprint_types.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function cyco_install_course_blueprint_types_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-blueprint_page-field_attachments'
  $field_instances['node-blueprint_page-field_attachments'] = array(
    'bundle' => 'blueprint_page',
    'deleted' => 0,
    'description' => 'Files attached to this page.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'file',
        'settings' => array(),
        'type' => 'file_default',
        'weight' => 4,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 3,
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
      'weight' => 7,
    ),
  );

  // Exported field_instance: 'node-blueprint_page-field_blueprint_keywords'
  $field_instances['node-blueprint_page-field_blueprint_keywords'] = array(
    'bundle' => 'blueprint_page',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Keywords relevant to course design. Shown in the blueprint only.',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'inline',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_blueprint_keywords',
    'label' => 'Blueprint keywords',
    'required' => 0,
    'settings' => array(
      'exclude_cv' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'taxonomy',
      'settings' => array(
        'autocomplete_path' => 'taxonomy/autocomplete',
        'size' => 60,
      ),
      'type' => 'taxonomy_autocomplete',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'node-blueprint_page-field_body'
  $field_instances['node-blueprint_page-field_body'] = array(
    'bundle' => 'blueprint_page',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'swim',
        'settings' => array(),
        'type' => 'swim_default_formatter',
        'weight' => 3,
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
    'field_name' => 'field_body',
    'label' => 'Body',
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
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'node-blueprint_page-field_images'
  $field_instances['node-blueprint_page-field_images'] = array(
    'bundle' => 'blueprint_page',
    'deleted' => 0,
    'description' => 'Images for this page.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 5,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 4,
      ),
    ),
    'entity_type' => 'node',
    'exclude_cv' => 0,
    'field_name' => 'field_images',
    'label' => 'Images',
    'required' => 0,
    'settings' => array(
      'alt_field' => 1,
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
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'node-blueprint_page-field_short_title'
  $field_instances['node-blueprint_page-field_short_title'] = array(
    'bundle' => 'blueprint_page',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Title used in tree menus. If blank, the full title will be used.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 6,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_short_title',
    'label' => 'Short title',
    'required' => 0,
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

  // Exported field_instance: 'node-blueprint_page-field_show_table_of_contents'
  $field_instances['node-blueprint_page-field_show_table_of_contents'] = array(
    'bundle' => 'blueprint_page',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => 'Do you want to show a table of contents on this page?',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 6,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_show_table_of_contents',
    'label' => 'Show table of contents',
    'required' => 0,
    'settings' => array(
      'exclude_cv' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 0,
      ),
      'type' => 'options_onoff',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'node-blueprint_page-field_workflow_tags'
  $field_instances['node-blueprint_page-field_workflow_tags'] = array(
    'bundle' => 'blueprint_page',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Tasks for this page.',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 5,
      ),
    ),
    'entity_type' => 'node',
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
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'node-course_page-field_attachments'
  $field_instances['node-course_page-field_attachments'] = array(
    'bundle' => 'course_page',
    'deleted' => 0,
    'description' => 'Files for this page.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'file',
        'settings' => array(),
        'type' => 'file_default',
        'weight' => 3,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 6,
      ),
    ),
    'entity_type' => 'node',
    'exclude_cv' => 0,
    'field_name' => 'field_attachments',
    'label' => 'Attachments',
    'required' => 0,
    'settings' => array(
      'description_field' => 0,
      'exclude_cv' => FALSE,
      'file_directory' => 'cycourse/bucket',
      'file_extensions' => '',
      'max_filesize' => '20mb',
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
      'weight' => 7,
    ),
  );

  // Exported field_instance: 'node-course_page-field_body'
  $field_instances['node-course_page-field_body'] = array(
    'bundle' => 'course_page',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'swim',
        'settings' => array(),
        'type' => 'swim_default_formatter',
        'weight' => 2,
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
    'field_name' => 'field_body',
    'label' => 'Body',
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
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'node-course_page-field_exercises'
  $field_instances['node-course_page-field_exercises'] = array(
    'bundle' => 'course_page',
    'default_value' => NULL,
    'default_value_function' => '',
    'deleted' => 0,
    'description' => 'Exercises this page includes. Internal use only.',
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
      'type' => 'options_select',
      'weight' => 8,
    ),
  );

  // Exported field_instance: 'node-course_page-field_images'
  $field_instances['node-course_page-field_images'] = array(
    'bundle' => 'course_page',
    'deleted' => 0,
    'description' => 'Images for your page.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 4,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 5,
      ),
    ),
    'entity_type' => 'node',
    'exclude_cv' => 0,
    'field_name' => 'field_images',
    'label' => 'Images',
    'required' => 0,
    'settings' => array(
      'alt_field' => 1,
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
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'node-course_page-field_keywords'
  $field_instances['node-course_page-field_keywords'] = array(
    'bundle' => 'course_page',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Keywords describing this page.',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_keywords',
    'label' => 'Keywords',
    'required' => 0,
    'settings' => array(
      'exclude_cv' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'taxonomy',
      'settings' => array(
        'autocomplete_path' => 'taxonomy/autocomplete',
        'size' => 60,
      ),
      'type' => 'taxonomy_autocomplete',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'node-course_page-field_short_title'
  $field_instances['node-course_page-field_short_title'] = array(
    'bundle' => 'course_page',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Title used in tree menus. If blank, the full title will be used.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 6,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_short_title',
    'label' => 'Short title',
    'required' => 0,
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

  // Exported field_instance: 'node-course_page-field_show_table_of_contents'
  $field_instances['node-course_page-field_show_table_of_contents'] = array(
    'bundle' => 'course_page',
    'default_value' => array(
      0 => array(
        'value' => 1,
      ),
    ),
    'deleted' => 0,
    'description' => 'Do you want to show a table of contents on this page?',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 5,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 4,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_show_table_of_contents',
    'label' => 'Show table of contents',
    'required' => 0,
    'settings' => array(
      'exclude_cv' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 0,
      ),
      'type' => 'options_onoff',
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'node-course_page-field_workflow_tags'
  $field_instances['node-course_page-field_workflow_tags'] = array(
    'bundle' => 'course_page',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'What work needs to be done on this page?',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 3,
      ),
    ),
    'entity_type' => 'node',
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
  t('Attachments');
  t('Blueprint keywords');
  t('Body');
  t('Do you want to show a table of contents on this page?');
  t('Exercises');
  t('Exercises this page includes. Internal use only.');
  t('Files attached to this page.');
  t('Files for this page.');
  t('Images');
  t('Images for this page.');
  t('Images for your page.');
  t('Keywords');
  t('Keywords describing this page.');
  t('Keywords relevant to course design. Shown in the blueprint only.');
  t('Short title');
  t('Show table of contents');
  t('Tasks for this page.');
  t('Title used in tree menus. If blank, the full title will be used.');
  t('What work needs to be done on this page?');
  t('Workflow tags');

  return $field_instances;
}
