/**
 * @file
 * View/controller for the pane that shows the student's submission.
 */

var app = app || {};

app.resetSubmissionPane = function( submissionNid ) {
  var submission = app.submissionsToGrade[submissionNid];
  var version = submission.version;
  if ( version > 1 ) {
    $("#submission-version")
      .html( "Version " + version )
      .show();
  }
  else {
    $("#submission-version").hide();
  }
  $("#submission-pane .pane-content").html( submission.renderedSolution );
}

