<?php
/**
 * @file
 * Field handler to show a link to erase submission feedback.
 */
class cyco_exercises_erase_submission_feedback_link extends views_handler_field {

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
    $result = '';
    //Should we make a link?
    if ( sizeof( $values->field_field_when_feedback_given ) > 0 ) {
      //Yes, make a link.
      $url = 'confirm-erase-feedback/' . $values->nid;
      $result = l( 
          t('Erase feedback'),
          $url,
          array(
            'attributes' => array(
              'title' => t('Erase the feedback, but leave the submission.'),
            ),
          )
      );
    }
    return $result;
  }
}
