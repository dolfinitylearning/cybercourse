<?php

/**
 * Field handler to show submission status.
 */
class cyco_exercises_handler_submission_status extends views_handler_field {

  function query() {
    // do nothing -- to override the parent query.
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
    $status = cyco_exercises_compute_submission_status($node);
    return $status;
  }
}
