<?php
// $Id$

/**
 * @file
 * Administration page callbacks for the booktopnav module.
 */

/**
 * Form builder. Configure when the navigation appears.
 *
 * @ingroup forms
 * @see system_settings_form().
 */
function book_top_navbar_admin_settings() {
  $form['#validate'][] = 'book_top_navbar_validate_admin_settings';
  $form['book_top_navbar_show_toc'] = array(
    '#type' => 'checkbox',
    '#title' => t('Top navigation bar includes tables of contents'),
    '#default_value' =>
        variable_get('book_top_navbar_show_toc', BOOK_TOP_NAVBAR_DEFAULT_SHOW_TOC),
    '#description' => t(
        'If this is off (recommended), tables of contents are '
        . 'omitted from the top navigation bar.'
    ),
  );
  $form['book_top_navbar_min_content_length'] = array(
    '#type' => 'textfield',
    '#title' => t('Minimum content length'),
    '#default_value' => 
        variable_get('book_top_navbar_min_content_length', 
            BOOK_TOP_NAVBAR_DEFAULT_MIN_CHARS),
    '#description' => t(
        'Content must be at least this many characters long before '
        . 'the navigation bar will appear. The character count '
        . 'includes HTML markup.'
    ),
  );
  $form['book_top_navbar_content_field_names'] = array(
    '#type' => 'textfield',
    '#title' => t('Content field names'),
    '#default_value' => 
        variable_get('book_top_navbar_content_field_names', 
            BOOK_TOP_NAVBAR_CONTENT_FIELD_NAMES),
    '#description' => t(
        'Possible names of field containing main content, separated by'
        . 'spaces. Checked left to right.'
    ),
  );
  return system_settings_form($form);
}

/**
 * Validate data in the admin form.
 */
function book_top_navbar_validate_admin_settings($form, &$form_state) {
  $min_length = trim($form_state['values']['book_top_navbar_min_content_length']);
  $min_length = check_plain($min_length);
  if ( $min_length == '' || !is_numeric($min_length) ) {
    form_set_error(
      'book_top_navbar_min_content_length',
      t('The minimum content length should be a number greater than or equal to zero.')
    );
    return;
  }
  //Explicitly cast to a number, so extra cruft characters go away.
  $min_length = (int)$min_length;
  if ( $min_length < 0 ) {
    form_set_error(
      'book_top_navbar_min_content_length',
      t('The minimum content length should be a number greater than or equal to zero.')
    );
    return;
  }
  //Put the decrufted integer back into $form_state.
  $form_state['values']['book_top_navbar_min_content_length'] = $min_length;
}
