<?php
/**
 * @file
 * Enables modules and site configuration for a standard site installation.
 */

/**
 * Implements hook_form_FORM_ID_alter() for install_configure_form().
 *
 * Allows the profile to alter the site configuration form.
 */
function cyco_form_install_configure_form_alter(&$form, $form_state) {
  // Pre-populate the site name.
  $form['site_information']['site_name']['#default_value'] 
      = 'CyberCourse instance';
}
