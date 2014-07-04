/**
 * View/controller for the pane that shows the student's submission.
 */

var app = app || {};

app.initSubmissionPane = function( submissionNid ) {
  $("#submission-pane .pane-content").html( 
      app.submissionsToGrade[submissionNid].renderedSolution
  );
}

