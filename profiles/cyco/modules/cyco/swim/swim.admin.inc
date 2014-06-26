<?php
/**
 * @file
 * Admin for SWIM.
 */

/**
 * Form for basic SWIM settings.
 */
function _swim_settings_form() {
  _swim_add_client_pieces( FALSE ); //Do not include plugins.
  $form['swim_help_message'] = array(
    '#type' => 'textarea',
    '#title' => t( 'SWIM help message' ),
    '#description' => t(
        'Message to show when user clicks the ReST help button in the SWIM '
        . 'editor. If empty, the help button will not be shown.'
    ),
    //Remove grippie.
    '#resizable' => FALSE,
    '#default_value' => swim_rest2ckhtml(
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
 * Settings form submit function. 
 * Save the message (ReST), and a rendered version of it.
 */
function _swim_save_settings( $form, $form_state ) {
  //ReST help message.
  $message = $form_state['values']['swim_help_message'];
  variable_set('swim_help_message', $message);
  $rendered_message = swim_rest2html( $message );
  variable_set('swim_help_message_rendered', $rendered_message);
  //Editor height.
  $editor_height = $form_state['values']['swim_default_height'];
  variable_set( 'swim_default_height', $editor_height );
  //Editor summary height.
  $editor_summary_height = $form_state['values']['swim_default_summary_height'];
  variable_set( 'swim_default_summary_height', $editor_summary_height );
  drupal_set_message('Settings saved.');
}
