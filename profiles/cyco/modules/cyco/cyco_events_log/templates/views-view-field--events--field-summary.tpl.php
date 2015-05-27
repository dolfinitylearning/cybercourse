<?php

/**
 * @file
 * This template is used to print a single field in a view.
 *
 * It is not actually used in default Views, as this is registered as a theme
 * function which has better performance. For single overrides, the template is
 * perfectly okay.
 *
 * Variables available:
 * - $view: The view object
 * - $field: The field handler object that can process the input
 * - $row: The raw SQL result that can be used
 * - $output: The processed output that will normally be used.
 *
 * When fetching output from the $row, this construct should be used:
 * $data = $row->{$field->field_alias}
 *
 * The above will guarantee that you'll always get the correct data,
 * regardless of any changes in the aliasing that might happen if
 * the view is modified.
 */
?>
<?php 
if ( $row->eck_cyco_event_type == 'exercise_submission' ) {
  $version_display = '(Unknown)';
  if ( isset($row->field_field_version[0]['rendered']['#markup']) ) {
    $version_display = $row->field_field_version[0]['rendered']['#markup'];
  }
  $submission_text_display = '(None)';
  if ( isset($row->field_field_submission[0]['rendered']['#markup']) ) {
    $submission_text_display 
        = $row->field_field_submission[0]['rendered']['#markup'];
  }
  $summary_display = '(Unknown)';
  if ( isset($row->field_field_summary[0]['rendered']['#markup']) ) {
    $summary_display = $row->field_field_summary[0]['rendered']['#markup'];
  }
  $files_display = '(None)';
  if ( isset( $row->field_field_submission_files[0] ) ) {
    $files_display = '';
    foreach( $row->field_field_submission_files as $file_info ) {
      $filename = $file_info['raw']['filename'];
      $url = $file_info['rendered']['#markup'];
      $files_display .= '<a href="' . $url . '" target=_blank>' 
          . $filename . '</a><br>';
    }
  }
  $output 
      = $summary_display . '<br>' . t('Version') . ': ' . $version_display . '<br>'
        . t('Submission text') . ':<br>' 
        . '<div class="cyco-event-report-submission-text">' 
        .   $submission_text_display 
        . '</div>'
        . t('Submission files') . ':<br>' 
        . '<div class="cyco-event-report-submission-text">' 
        .   $files_display 
        . '</div>';
} // End exercise submission.
if ( $row->eck_cyco_event_type == 'other' ) {
  $r=6;
}

print $output; 
?>
