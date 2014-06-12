<?php

/**
 * @file
 * Administration settings for the reStructuredText module.
 */

/**
 * General configuration form.
 */
function _restructuredtext_admin_settings($form, $form_state) {
  $form['restructuredtext_docutils_css_path'] = array(
    '#type' => 'textfield',
    '#title' => t('DocUtils CSS path'),
    '#description' => t(
        'The path to the CSS files html4css1.css and math.css, supplied '
        . 'by docutils. E.g., /usr/lib/python27/Lib/site-packages/'
        . 'docutils/writers/html4css1. If not specified (the most common '
        . 'case), files from docutils version 0.11 will be used.'
     ),
    '#default_value' => variable_get('restructuredtext_docutils_css_path', ''),
    '#required' => FALSE,
  );
  return system_settings_form($form);
}

