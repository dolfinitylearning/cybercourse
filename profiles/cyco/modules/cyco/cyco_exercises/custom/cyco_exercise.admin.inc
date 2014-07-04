<?php
/**
 * Admin function for cybercourse_exercise.
 */

/**
 * Define admin form for exercises.
 */
function cybercourse_exercise_settings_form($form, &$form_state) {
  //Select list of enabled themes, plus Default at the top.
  $theme_details = list_themes();
  $theme_select_options = array( 'default' => 'Use default theme' );
  foreach( $theme_details as $machine_name => $theme ) {
    if ( $theme->status == 1 ) {
      $theme_select_options[$machine_name] = $theme->info['name'];
    }
  }
  $form['exercise_theme'] = array(
    '#type' => 'select',
    '#options' => $theme_select_options,
    '#title' => t('Exercise theme'),
    '#description' => t('What theme should be used for the exercise submission '
        . 'interface? Choose "Default theme" to always use the same theme as '
        . 'the rest of the site.'),
    '#default_value' => variable_get('cybercourse_exercise_submission_theme', 'default'),
  );
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  return $form;  
}

/**
 * Process exercise config submission.
 */
function cybercourse_exercise_settings_form_submit($form, &$form_state) {
  variable_set('cybercourse_exercise_submission_theme',
    $form_state['values']['exercise_theme']);
  drupal_set_message( t('Settings have been saved.') );
}

