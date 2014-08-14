<?php
/**
 * @file
 * Field handler to show submission completion badge.
 */
class cyco_exercises_handler_completion_badge extends views_handler_field {

  function query() {
    // Do nothing -- to override the parent query.
  }  

  function option_definition() {
    $options = parent::option_definition();
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
  }
  
  function render($values) {
    $node = $values->_field_data['nid']['entity'];
    $result = '';
    if ($node->field_complete[ $node->language ][0]['value'] == 1) {
      $image_path = drupal_get_path('module', 'cyco_exercises') 
          . '/custom/images/completion-badge.png';
      $result = '<img alt="' . t('Complete') . '" '
          . 'title="' . t('Complete') . '" '
          . 'src="' . $image_path . '">';
    }
    return $result;
  }
}
