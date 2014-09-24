<?php
/**
 * @file
 * Admin for toggle sidebar module.
 */

/**
 * Form for settings for toggle sidebar module.
 */
function _tsb_settings_form() {
  $form['tsb_intro'] = array(
    '#markup' => 
        t('The toggle sidebar module needs to know about '
          . 'your theme for it to work correctly. You need to identify '
          . 'elements on your page. For example, it needs to know '
          . 'how to find the sidebar so that it knows what to collapse.'
        )
        . '<br><br>'
        . t('The defaults are set for the default CyberCourse theme. If you '
            . 'use it, you won\'t need to change anything.')
  );
  $form['tsb_sidebar_selector'] = array(
    '#type' => 'textfield',
    '#title' => t('Sidebar selector'),
    '#description' => t('jQuery selector for the sidebar to be collapsed '
        . 'E.g.: .region-sidebar-second'),
    '#default_value' => variable_get('tsb_sidebar_selector', 
        TSB_DEFAULT_SIDEBAR_SELECTOR),
  );
  $form['tsb_main_region_selector'] = array(
    '#type' => 'textfield',
    '#title' => t('Main region selector'),
    '#description' => t('jQuery selector for the main region to be'
        . 'expanded when the sidebar is collapsed. '
        . 'E.g.: .region-content'),
    '#default_value' => variable_get('tsb_main_region_selector', 
        TSB_DEFAULT_MAIN_REGION_SELECTOR),
  );
  $form['tsb_main_region_class_when_collapsed'] = array(
    '#type' => 'textfield',
    '#title' => t('Collapsed class for main region'),
    '#description' => t('Class to give the main region when the sidebar '
        . 'is collapsed. E.g.: col-sm-12'),
    '#default_value' => variable_get('tsb_main_region_class_when_collapsed', 
        TSB_DEFAULT_MAIN_REGION_CLASS_COLLPASED),
  );
  $form['tsb_main_region_class_when_expanded'] = array(
    '#type' => 'textfield',
    '#title' => t('Expanded class for main region'),
    '#description' => t('Class to give the main region when the sidebar '
        . 'is expanded. E.g.: col-sm-9'),
    '#default_value' => variable_get('tsb_main_region_class_when_expanded', 
        TSB_DEFAULT_MAIN_REGION_CLASS_EXPANDED),
  );
  $form['tsb_icon_position'] = array(
    '#type' => 'radios',
    '#title' => t('Icon position'),
    '#description' => t('Should the collapse icon that users click on be on '
        . 'the left or right of the main region?'),
    '#options' => array(
      'left' => 'Left',
      'right' => 'Right',
    ),
    '#default_value' => variable_get('tsb_icon_position', 
        TSB_DEFAULT_ICON_POSITION),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
  );
  $form['#validate'][] = '_tsb_validate_settings';
  $form['#submit'][] = '_tsb_save_settings';
  return $form;
}

/**
 * Validate the admin settings form.
 */
function _tsb_validate_settings( $form, &$form_state ) {
  _tsb_check_selector($form_state, 'tsb_sidebar_selector');
  _tsb_check_selector($form_state, 'tsb_main_region_selector');
  _tsb_check_class_name($form_state, 'tsb_main_region_class_when_collapsed');
  _tsb_check_class_name($form_state, 'tsb_main_region_class_when_expanded');
}

/**
 * Check that a selector is OK. Show an error if there is no selector, or a
 * warning if the selector does not begin with a . or a #.
 * @param array $form_state Form values.
 * @param string $field_name Field to check.
 */
function _tsb_check_selector( $form_state, $field_name ) {
  if ( !_tsb_form_value_exists($form_state, $field_name) ) {
    form_set_error(
        $field_name, 
        t('Please give a selector. E.g.: .primary-sidebar')
    );
  }
  else {
    $ok = FALSE;
    $first_char = substr(trim($form_state['values'][$field_name]), 0, 1);
    if ( $first_char ) {
      $ok = ( $first_char == '.') || ( $first_char == '#');
    }
    if ( ! $ok ) {
      drupal_set_message( 
          t('Selectors usually start with . (for a CSS class) or '
              . '# (for an element id). Please check that your selectors '
              . 'are correct. If you don\'t know, you might ask a question '
              . 'on the CyberCourse wiki.' ), 
          'warning'
      );
    }
  }
}

/**
 * Check whether a field has a value in $form_state.
 * @param array $form_state Form data.
 * @param string $field_name Field to check.
 * @return boolean True if it has a value, else false.
 */
function _tsb_form_value_exists( $form_state, $field_name ) {
  if ( ! isset( $form_state['values'][$field_name] ) ) {
    return FALSE;
  }
  if ( ! trim($form_state['values'][$field_name]) ) {
    return FALSE;
  }
  return TRUE;
}

/**
 * Validate a class name.
 * 
 * If it is MT, give a warning. If it starts with ., give an error.
 * 
 * @param array $form_state Form values.
 * @param string $field_name Field name.
 */
function _tsb_check_class_name( $form_state, $field_name ) {
  if ( ! _tsb_form_value_exists($form_state, $field_name) ) {
    drupal_set_message(
        t('You\'ve skipped a class name. Please make sure this is correct. '
            . 'If you don\'t know, you might ask a question '
            . 'on the CyberCourse wiki.' ),
        'warning'
    );
  }
  else {
    $first_char = substr(trim($form_state['values'][$field_name]), 0, 1);
    if ( $first_char ) {
      if ( $first_char == '.' ) {
        form_set_error(
            $field_name,
            t('Please give a class, not a class selector. '
                . 'E.g., tiger, not .tiger' )
        );
      }
    }
  }
}

/**
 * Settings form submit function. 
 * Save the form values.
 */
function _tsb_save_settings( $form, $form_state ) {
  variable_set(
      'tsb_sidebar_selector', 
      trim($form_state['values']['tsb_sidebar_selector'])
  );
  variable_set(
      'tsb_main_region_selector', 
      trim($form_state['values']['tsb_main_region_selector'])
  );
  variable_set(
      'tsb_main_region_class_when_expanded', 
      trim($form_state['values']['tsb_main_region_class_when_expanded'])
  );
  variable_set(
      'tsb_main_region_class_when_collapsed', 
      trim($form_state['values']['tsb_main_region_class_when_collapsed'])
  );
  variable_set(
      'tsb_icon_position', 
      trim($form_state['values']['tsb_icon_position'])
  );
  drupal_set_message('Settings saved.');
}
