<?php
/**
 * @file
 * cyco_exercises_submissions.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function cyco_exercises_submissions_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-exercise_submission-field_complete'
  $field_instances['node-exercise_submission-field_complete'] = array(
    'bundle' => 'exercise_submission',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => 'Has the student completed this exercise?',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 8,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_complete',
    'label' => 'Complete',
    'required' => 1,
    'settings' => array(
      'exclude_cv' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 10,
    ),
  );

  // Exported field_instance: 'node-exercise_submission-field_conversation'
  $field_instances['node-exercise_submission-field_conversation'] = array(
    'bundle' => 'exercise_submission',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Conversation about this feedback.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 9,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_conversation',
    'label' => 'Conversation',
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
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 11,
    ),
  );

  // Exported field_instance: 'node-exercise_submission-field_exercise'
  $field_instances['node-exercise_submission-field_exercise'] = array(
    'bundle' => 'exercise_submission',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Exercise this is a submission for.',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
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
    'field_name' => 'field_exercise',
    'label' => 'Exercise',
    'required' => 1,
    'settings' => array(
      'exclude_cv' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'node-exercise_submission-field_feedback'
  $field_instances['node-exercise_submission-field_feedback'] = array(
    'bundle' => 'exercise_submission',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Feedback from grader.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'swim',
        'settings' => array(),
        'type' => 'swim_default_formatter',
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
    'field_name' => 'field_feedback',
    'label' => 'Feedback',
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
      'weight' => 8,
    ),
  );

  // Exported field_instance: 'node-exercise_submission-field_feedback_source'
  $field_instances['node-exercise_submission-field_feedback_source'] = array(
    'bundle' => 'exercise_submission',
    'default_value' => NULL,
    'default_value_function' => '',
    'deleted' => 0,
    'description' => 'Who gave the feedback?',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
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
    'field_name' => 'field_feedback_source',
    'label' => 'Feedback source',
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
      'weight' => 7,
    ),
  );

  // Exported field_instance: 'node-exercise_submission-field_rubric_item_ratings'
  $field_instances['node-exercise_submission-field_rubric_item_ratings'] = array(
    'bundle' => 'exercise_submission',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Ratings on rubric items. ',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 10,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'exclude_cv' => 1,
    'field_name' => 'field_rubric_item_ratings',
    'label' => 'Rubric item ratings',
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
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 9,
    ),
  );

  // Exported field_instance: 'node-exercise_submission-field_solution'
  $field_instances['node-exercise_submission-field_solution'] = array(
    'bundle' => 'exercise_submission',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
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
    'field_name' => 'field_solution',
    'label' => 'Your solution',
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
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'node-exercise_submission-field_submitted_files'
  $field_instances['node-exercise_submission-field_submitted_files'] = array(
    'bundle' => 'exercise_submission',
    'deleted' => 0,
    'description' => 'Files attached to the submission.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'file',
        'settings' => array(),
        'type' => 'file_default',
        'weight' => 11,
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
    'field_name' => 'field_submitted_files',
    'label' => 'Submitted files',
    'required' => 0,
    'settings' => array(
      'description_field' => 1,
      'exclude_cv' => FALSE,
      'file_directory' => 'student_uploads',
      'file_extensions' => 'txt',
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
            'imce' => 0,
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
            'imce_mode' => 0,
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
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'node-exercise_submission-field_version'
  $field_instances['node-exercise_submission-field_version'] = array(
    'bundle' => 'exercise_submission',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Which version is this? First submission is version 1. If resubmitted, that is version 2. Etc.',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_integer',
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
    'field_name' => 'field_version',
    'label' => 'Version',
    'required' => 1,
    'settings' => array(
      'exclude_cv' => FALSE,
      'max' => '',
      'min' => 1,
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'node-exercise_submission-field_when_feedback_given'
  $field_instances['node-exercise_submission-field_when_feedback_given'] = array(
    'bundle' => 'exercise_submission',
    'deleted' => 0,
    'description' => 'When was the feedback recorded?',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'date',
        'settings' => array(
          'format_type' => 'long',
          'fromto' => 'both',
          'multiple_from' => '',
          'multiple_number' => '',
          'multiple_to' => '',
        ),
        'type' => 'date_default',
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
    'field_name' => 'field_when_feedback_given',
    'label' => 'When feedback given',
    'required' => 0,
    'settings' => array(
      'default_value' => 'blank',
      'default_value2' => 'same',
      'default_value_code' => '',
      'default_value_code2' => '',
      'exclude_cv' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'date',
      'settings' => array(
        'increment' => 1,
        'input_format' => 'M j Y - g:i:sa',
        'input_format_custom' => '',
        'label_position' => 'above',
        'text_parts' => array(),
        'year_range' => '-3:+3',
      ),
      'type' => 'date_popup',
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'node-exercise_submission-field_when_submitted'
  $field_instances['node-exercise_submission-field_when_submitted'] = array(
    'bundle' => 'exercise_submission',
    'deleted' => 0,
    'description' => 'When was the solution submitted for feedback?',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'date',
        'settings' => array(
          'format_type' => 'long',
          'fromto' => 'both',
          'multiple_from' => '',
          'multiple_number' => '',
          'multiple_to' => '',
        ),
        'type' => 'date_default',
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
    'field_name' => 'field_when_submitted',
    'label' => 'When submitted',
    'required' => 0,
    'settings' => array(
      'default_value' => 'blank',
      'default_value2' => 'same',
      'default_value_code' => '',
      'default_value_code2' => '',
      'exclude_cv' => FALSE,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'date',
      'settings' => array(
        'increment' => 1,
        'input_format' => 'M j Y - g:i:sa',
        'input_format_custom' => '',
        'label_position' => 'above',
        'text_parts' => array(),
        'year_range' => '-3:+3',
      ),
      'type' => 'date_popup',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'user-user-field_good_cutoff'
  $field_instances['user-user-field_good_cutoff'] = array(
    'bundle' => 'user',
    'default_value' => array(
      0 => array(
        'value' => 80,
      ),
    ),
    'deleted' => 0,
    'description' => 'Lowest rating for "good" messages, as percentage. Tokens substituted.<br><br>The score is computed as [number of "good"s x 2 + number of "needs work"s] / [number of rubric items x 2].<br><br>See the CyberCourse wiki for more information.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_integer',
        'weight' => 12,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_good_cutoff',
    'label' => '"Good" cutoff',
    'required' => 0,
    'settings' => array(
      'exclude_cv' => FALSE,
      'max' => 90,
      'min' => 10,
      'prefix' => '',
      'suffix' => '%',
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 10,
    ),
  );

  // Exported field_instance: 'user-user-field_greetings'
  $field_instances['user-user-field_greetings'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Opening line, or salutation. You can add [feedback:student_first_name] and [feedback:student_last_name]; they\'ll be replaced by the appropriate values. Enter as many greetings as you like. E.g., "Hi [feedback:student_first_name]:" and "Yo, [feedback:student_first_name]!". (See the Token section below for a full list.)',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 5,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_greetings',
    'label' => 'Greetings',
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
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'user-user-field_needs_work_cutoff'
  $field_instances['user-user-field_needs_work_cutoff'] = array(
    'bundle' => 'user',
    'default_value' => array(
      0 => array(
        'value' => 40,
      ),
    ),
    'deleted' => 0,
    'description' => 'Lowest rating for "needs work" messages, as percentage. Score computed as [number of "good"s x 2 + number of "needs work"s] / [number of rubric items x 2]. ',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_integer',
        'weight' => 13,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_needs_work_cutoff',
    'label' => '"Needs work" cutoff',
    'required' => 0,
    'settings' => array(
      'exclude_cv' => FALSE,
      'max' => 90,
      'min' => 10,
      'prefix' => '',
      'suffix' => '%',
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 11,
    ),
  );

  // Exported field_instance: 'user-user-field_overall_good'
  $field_instances['user-user-field_overall_good'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Phrases that tell a student s/he did well on an exercise. Enter as many as you like. E.g. "Good job, [feedback:student_first_name]!", "[feedback:student_first_name], I like it!", "Nice work.". (See the Token section below for a full list of tokens.)',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 6,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_overall_good',
    'label' => 'Overall: good',
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
      'weight' => 7,
    ),
  );

  // Exported field_instance: 'user-user-field_overall_needs_work'
  $field_instances['user-user-field_overall_needs_work'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Phrases that tell a student his/her submission needs work. Enter as many as you like. E.g., "Not too bad, [feedback:student_first_name], but there are some issues.", "There are things you should fix, [feedback:student_first_name].", "It\'s OK, but needs fixing." (See the Token section below for a full list of tokens.)',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 7,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_overall_needs_work',
    'label' => 'Overall: needs work',
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
      'weight' => 8,
    ),
  );

  // Exported field_instance: 'user-user-field_overall_poor'
  $field_instances['user-user-field_overall_poor'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Phrases that tell a student s/he did poorly on an exercise. Enter as many as you like. E.g., "You can do better, [feedback:student_first_name].", "[feedback:student_first_name], you need to improve.", "Not that good. Come in for some help." (See the Token section below for a full list of tokens.)',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 8,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_overall_poor',
    'label' => 'Overall: poor',
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
      'weight' => 9,
    ),
  );

  // Exported field_instance: 'user-user-field_signature'
  $field_instances['user-user-field_signature'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Endings to feedback messages. Enter as many as you like. E.g., "Ann", "Your helper, Ann", "Best wishes, Ann".  (See the Token section below for a full list of tokens.)',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 11,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_signature',
    'label' => 'Signature',
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
      'weight' => 12,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('"Good" cutoff');
  t('"Needs work" cutoff');
  t('Complete');
  t('Conversation');
  t('Conversation about this feedback.');
  t('Endings to feedback messages. Enter as many as you like. E.g., "Ann", "Your helper, Ann", "Best wishes, Ann".  (See the Token section below for a full list of tokens.)');
  t('Exercise');
  t('Exercise this is a submission for.');
  t('Feedback');
  t('Feedback from grader.');
  t('Feedback source');
  t('Files attached to the submission.');
  t('Greetings');
  t('Has the student completed this exercise?');
  t('Lowest rating for "good" messages, as percentage. Tokens substituted.<br><br>The score is computed as [number of "good"s x 2 + number of "needs work"s] / [number of rubric items x 2].<br><br>See the CyberCourse wiki for more information.');
  t('Lowest rating for "needs work" messages, as percentage. Score computed as [number of "good"s x 2 + number of "needs work"s] / [number of rubric items x 2]. ');
  t('Opening line, or salutation. You can add [feedback:student_first_name] and [feedback:student_last_name]; they\'ll be replaced by the appropriate values. Enter as many greetings as you like. E.g., "Hi [feedback:student_first_name]:" and "Yo, [feedback:student_first_name]!". (See the Token section below for a full list.)');
  t('Overall: good');
  t('Overall: needs work');
  t('Overall: poor');
  t('Phrases that tell a student his/her submission needs work. Enter as many as you like. E.g., "Not too bad, [feedback:student_first_name], but there are some issues.", "There are things you should fix, [feedback:student_first_name].", "It\'s OK, but needs fixing." (See the Token section below for a full list of tokens.)');
  t('Phrases that tell a student s/he did poorly on an exercise. Enter as many as you like. E.g., "You can do better, [feedback:student_first_name].", "[feedback:student_first_name], you need to improve.", "Not that good. Come in for some help." (See the Token section below for a full list of tokens.)');
  t('Phrases that tell a student s/he did well on an exercise. Enter as many as you like. E.g. "Good job, [feedback:student_first_name]!", "[feedback:student_first_name], I like it!", "Nice work.". (See the Token section below for a full list of tokens.)');
  t('Ratings on rubric items. ');
  t('Rubric item ratings');
  t('Signature');
  t('Submitted files');
  t('Version');
  t('When feedback given');
  t('When submitted');
  t('When was the feedback recorded?');
  t('When was the solution submitted for feedback?');
  t('Which version is this? First submission is version 1. If resubmitted, that is version 2. Etc.');
  t('Who gave the feedback?');
  t('Your solution');

  return $field_instances;
}
