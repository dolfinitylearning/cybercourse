/**
 * @file
 * View/controller for the pane that shows the feedback message.
 */

var app = app || {};

//Create a namespacey object for this pane.
app.feedbackPane = {};

/**
 * Initialize the pane. Just do this once.
 */
app.feedbackPane.initFeedbackPane = function() {
  //Set up send event.
  $("#send-feedback-button").click( app.feedbackPane.sendFeedback );
};

/**
 * Reset the feedback pane, using state data from submission with
 * id of submissionNid.
 */
app.feedbackPane.resetFeedbackPaneForSubmission = function() {
  var submissionNid = app.currentState.submissionNid;
  //Show existing feedback if it exists.
  if ( app.submissionsToGrade[ submissionNid ].feedback ) {
    app.feedbackPane.showFeedback( app.submissionsToGrade[ submissionNid ].feedback )
  }
  else {
    app.feedbackPane.mtFeedbackArea();
  }
  //Set completed indicator.
  app.feedbackPane.updateStatusComplete( 
      app.submissionsToGrade[ submissionNid ].complete
  );
  //Set feedback sent indicator.
  app.feedbackPane.updateStatusFeedbackSent( 
      app.submissionsToGrade[ submissionNid ].feedbackSent
  );
  //Set the disabled state of widgets if f/b already sent.
  app.feedbackPane.updateWidgetsDisabled();
  //Show the UI.
  if ( ! $("#feedback-pane .pane-content").is(':visible') ) {
    $("#feedback-pane .pane-content").fadeIn('fast');
  }};

/**
 * Show feedback.
 * @param {string} feedback
 */
app.feedbackPane.showFeedback = function( feedback ) {
  $("#cyco-feedback-editor").val( feedback );

};

/**
 * Clear the feedback area of any text.
 */
app.feedbackPane.mtFeedbackArea = function() {
  $("#cyco-feedback-editor").val( "" );
};

/**
 * Function other controllers can call.
 */
app.feedbackPane.hideFeedbackArea = function() {
  $("#feedback-pane .pane-content").hide();  
}

/**
 * Send the current feedback.
 */
app.feedbackPane.sendFeedback = function() {
  if ( ! $("#cyco-feedback-editor").val().trim() ) {
    alert("Nothing to send.");
    return;
  }
  //Send feedback data to server.
  app.feedbackPane.showSendingThrobber();
  $.when(
    app.feedbackPane.saveFeedbackToServer()
  )
  .then(function(){
    //Reset the rubric pane, to show new comments added by the user.
    app.rubricPane.resetRubricPaneForSubmission();
    //Show UI ready for next submission.
    app.submissionListPane.resetUi( app.currentState.submissionNid );
  })
  .always(function() {
    app.feedbackPane.hideSendingThrobber();
  });
};

/**
 * Save feedback to the server, and new rubric item comments.
 */
app.feedbackPane.saveFeedbackToServer = function() {
  //Prepare feedback data for server.
  var dataToSend = {};
  var webServiceUrl = app.basePath + "exercise/feedback/saveFeedback";
  dataToSend.submission_nid = app.currentState.submissionNid;
  dataToSend.student_uid = app.currentState.studentUid;
  dataToSend.exercise_nid = app.currentState.exerciseNid;
  dataToSend.model_solution_nid = app.currentState.modelSolutionNid;
  dataToSend.rubric_ratings = app.rubricPane.packageRubicRatings();
  dataToSend.complete = $(".cyco-exercise-complete").prop("checked");
  dataToSend.message = $("#cyco-feedback-editor").val().trim();
  dataToSend = JSON.stringify( dataToSend );
  var promise = $.ajax({
    type: "POST",
    contentType: "application/json; charset=utf-8",
    dataType: "json",
    data: dataToSend,
    url: webServiceUrl,
    beforeSend: function (request) {
      request.setRequestHeader("X-CSRF-Token", app.csrfToken);
    }
  })
  .done(function(message){
    //Update the data model.
    app.submissionsToGrade[ app.currentState.submissionNid ].feedbackSent = true;
    //Record that the submission data is not dirty.
    app.submissionsToGrade[ app.currentState.submissionNid ].dirty = false;
    //Update the feedback sent message.
    app.feedbackPane.updateStatusFeedbackSent( true );
    //Set the disabled state of the Send button.
    app.feedbackPane.updateWidgetsDisabled();
    //Send data on new rubric item comments, if there are any.
    app.saveNewRubricItemComments();
  })
  .fail(function(jqXHR, textStatus, errorThrown) {
    Drupal.behaviors.cycoErrorHandler.reportError(
      "Fail in app.feedbackPane.saveFeedback."  
        + " textStatus: " + textStatus + ", errorThrown: " + errorThrown
    );
  });
  return promise;
};

app.feedbackPane.updateStatusComplete = function( complete ) {
  if ( complete ) {
    $("#feedback-pane #status-exercise-complete")
      .text( "Complete" )
      .removeClass( "cyco-exer-not-complete" )
      .addClass( "cyco-exer-complete" );
  }
  else {
    $("#feedback-pane #status-exercise-complete")
      .text( "Not complete" )
      .removeClass( "cyco-exer-complete" )
      .addClass( "cyco-exer-not-complete" );
  }
};

app.feedbackPane.updateStatusFeedbackSent = function( sent ) {
  if ( sent ) {
    $("#feedback-pane #status-feedback-sent")
      .text( "Fb sent" )
      .removeClass( "cyco-exer-feedback-not-sent" )
      .addClass( "cyco-exer-feedback-sent" );
  }
  else {
    $("#feedback-pane #status-feedback-sent")
      .text( "Fb not sent" )
      .removeClass( "cyco-exer-feedback-sent" )
      .addClass( "cyco-exer-feedback-not-sent" );
  }
};

/**
 * Show throbber for generating feedback.
 */
app.feedbackPane.showGeneratingThrobber = function() {
  if ( $("#cyco-exer-feedback-generate-throbber").length == 0 ) {
    app.feedbackPane.makeGeneratingThrobber();
  }
  $("#feedback-pane .pane-content").hide();
  $("#cyco-exer-feedback-generate-throbber").show();
};

/**
 * Hide throbber for generating feedback.
 */
app.feedbackPane.hideGeneratingThrobber = function() {
  $("#cyco-exer-feedback-generate-throbber").hide();
  $("#feedback-pane .pane-content").show();
};

/**
 * Make a throbber to show when generating feedback.
 */
app.feedbackPane.makeGeneratingThrobber = function() {
  var html = app.compiledTemplates.throbber({
    message: "Please wait...",
    id: "cyco-exer-feedback-generate-throbber"
  });
  $("#feedback-pane header").after( html );
};

/**
 * Show throbber when sending feedback.
 */
app.feedbackPane.showSendingThrobber = function() {
  if ( $("#cyco-exer-feedback-send-throbber").length == 0 ) {
    app.feedbackPane.makeSendingThrobber();
  }
  $("#cyco-exer-feedback-send-throbber").show();
};

/**
 * Hide "sending feedback" throbber.
 */
app.feedbackPane.hideSendingThrobber = function() {
  $("#cyco-exer-feedback-send-throbber").hide();
};

/**
 * Make a throbber to show when sending feedback.
 */
app.feedbackPane.makeSendingThrobber = function() {
  var html = app.compiledTemplates.throbber({
    message: "Please wait...",
    id: "cyco-exer-feedback-send-throbber"
  });
  $("#send-feedback-button").after( html );
};

/**
 * Update status indicator: ungraded rubrics.
 */
app.feedbackPane.updateStatusUngradedRubrics = function( numRubrics ) {
  $("#status-ungraded-subrics").text("Ungraded: " + numRubrics);
  if ( numRubrics === 0 ) {
    $("#status-ungraded-subrics")
      .addClass("cyco-status-all-graded")
      .removeClass("cyco-status-ungraded");
  }
  else {
    $("#status-ungraded-subrics")
      .addClass("cyco-status-ungraded")
      .removeClass("cyco-status-all-graded");
  }
};

/**
 * Update the disabled state of the widgets.
 */
app.feedbackPane.updateWidgetsDisabled = function() {
  var feedbackSent 
    = app.submissionsToGrade[ app.currentState.submissionNid ].feedbackSent;
  $("#feedback-pane *").prop("disabled", feedbackSent);
};
