<?php
/**
 * @file
 * Admin for SWIM.
 */

/**
 * Form for basic SWIM settings.
 */
function _swim_settings_form() {
  _swim_add_editor_client_pieces( FALSE ); //Do not include plugins.
  $form['swim_help_message'] = array(
    '#type' => 'textarea',
    '#title' => t( 'SWIM help message' ),
    '#description' => t(
        'Message to show when user clicks the help button in the SWIM '
        . 'editor. If empty, the help button will not be shown.'
    ),
    //Remove grippie.
    '#resizable' => FALSE,
    '#default_value' => swim_textile2ckhtml(
        variable_get('swim_help_message', '') 
    ),
    '#attributes' => array(
      'class' => array('swim-editor swim-editor-main text-full'),
    ),
    '#value_callback' => '_swim_field_widget_value',
    '#required' => FALSE,
  );
  $form['swim_default_height'] = array(
    '#type' => 'textfield',
    '#title' => t('Default editor height'),
    '#description' => t(
        'Default height of the editor, in lines of text (e.g., 15). Note: CyCo '
        . 'will approximate this value the best it can.'
    ),
    '#size' => 6,
    '#maxlength' => 5,
    '#default_value' => variable_get('swim_default_height', 
        SWIM_DEFAULT_HEIGHT),
  );
  $form['swim_default_summary_height'] = array(
    '#type' => 'textfield',
    '#title' => t('Default editor height for summary fields'),
    '#description' => t(
        'Default height for summary fields, in lines of text (e.g., 5). '
        . 'Note: CyCo will approximate this value the best it can.'
    ),
    '#size' => 6,
    '#maxlength' => 5,
    '#default_value' => variable_get('swim_default_summary_height', 
        SWIM_DEFAULT_SUMMARY_HEIGHT),
  );
  $form['swim_base_injector_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Base injector path'),
    '#description' => t(
        'Path to directory of stuff to be injected, from site root. '
        . 'E.g., /sites/default/files/inject'
    ),
    '#default_value' => variable_get('swim_injector_path', 
        SWIM_DEFAULT_INJECTOR_PATH),
  );  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
  );
  $form['#validate'][] = '_swim_validate_settings';
  $form['#submit'][] = '_swim_save_settings';
  return $form;
}

function _swim_validate_settings( $form, &$form_state ) {
  _swim_check_settings_height_field($form_state, 'swim_default_height', 
      SWIM_DEFAULT_HEIGHT);
  _swim_check_settings_height_field($form_state, 'swim_default_summary_height', 
      SWIM_DEFAULT_SUMMARY_HEIGHT);  
  _swim_check_settings_injector_path_field($form_state);
}

/**
 * Check value of a line height form field on the settings form.
 * @param array $form_state Usual Drupaly thing.
 * @param string $field_name Name of the field to check.
 * @param integer $default Default for MT field.
 */
function _swim_check_settings_height_field( &$form_state, $field_name, $default ) {
  $form_state['values'][$field_name] 
    = trim($form_state['values'][$field_name]);
  if ( ! $form_state['values'][$field_name] ) {
    $form_state['values'][$field_name] = $default;
  }
  else if ( is_nan( $form_state['values'][$field_name] ) ) {
    form_set_error( $field_name, 'Sorry, must be a number.' );
  }
  else if ( $form_state['values'][$field_name] < 2 ) {
    form_set_error( $field_name, 'Sorry, must be at least 2.' );
  }
}

/**
 * Check the base injector path.
 * @param type $form_state Data entered into form.
 */
function _swim_check_settings_injector_path_field(&$form_state) {
  $path = $form_state['values']['swim_base_injector_path'];
  //Make sure first character is /.
  if ( substr($path, 0, 1) != '/' ) {
    $path = '/' . $path;
    $form_state['values']['swim_base_injector_path'] = $path;
  }
  if ( ! is_dir(DRUPAL_ROOT . $path) ) {
    form_set_error('swim_base_injector_path', 
        'Sorry, enter a valid path to an existing directory.');
  }
}

/**
 * Settings form submit function. 
 * Save the message (Markdown), and a rendered version of it.
 */
function _swim_save_settings( $form, $form_state ) {
  //Markdown help message.
  $message = $form_state['values']['swim_help_message'];
  variable_set('swim_help_message', $message);
  $rendered_message = swim_textile2html( $message );
  variable_set('swim_help_message_rendered', $rendered_message);
  //Editor height.
  $editor_height = $form_state['values']['swim_default_height'];
  variable_set( 'swim_default_height', $editor_height );
  //Editor summary height.
  $editor_summary_height = $form_state['values']['swim_default_summary_height'];
  variable_set( 'swim_default_summary_height', $editor_summary_height );
  //Base injector path.
  $path = $form_state['values']['swim_base_injector_path'];
  variable_set( 'swim_base_injector_path', $path );
  drupal_set_message('Settings saved.');
}
