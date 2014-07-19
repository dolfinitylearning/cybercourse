/**
 * View/controller for the pane that shows the feedback message.
 */

var app = app || {};

//Create a namespacey object for this pane.
app.feedbackPane = {};

/**
 * Initialize the feedback pane, using state data from submission with
 * id of submissionNid.
 */
app.feedbackPane.initFeedbackPane = function( submissionNid ) {
  //Show existing feedback if it exists.
  if ( app.submissionsToGrade[ submissionNid ].feedback ) {
    app.feedbackPane.showFeedback( app.submissionsToGrade[ submissionNid ].feedback )
  }
  else {
    app.feedbackPane.mtFeedbackArea();
  }
  //Set completed indicator.
  app.feedbackPane.setCompleteMessage( 
      app.submissionsToGrade[ submissionNid ].complete
  );
  //Set feedback sent indicator.
  app.feedbackPane.setFeedbackSentMessage( 
      app.submissionsToGrade[ submissionNid ].feedbackSent
  );
  //Set up send event.
  $("#send-feedback-button").click( app.feedbackPane.sendFeedback );
  //Show the UI.
//  $("#feedback-pane .pane-content").show();
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
  $.when(
    app.feedbackPane.saveFeedbackToServer()
  )
  .then(function(){
    //Show UI ready for next submission.
    app.submissionListPane.resetUi( app.currentState.submissionNid );
  });
};

/**
 * Save feedback to the server.
 */
app.feedbackPane.saveFeedbackToServer = function() {
  app.feedbackPane.showSendingThrobber();
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
    //Update the feedback sent message.
    app.setFeedbackSentMessage( true );
  })
  .fail(function(jqXHR, textStatus, errorThrown) {
    Drupal.behaviors.cybercourseErrorHandler.reportError(
      "Fail in app.feedbackPane.saveFeedback."  
        + " textStatus: " + textStatus + ", errorThrown: " + errorThrown
    );
  })
  .always(function() {
    app.feedbackPane.hideSendingThrobber();
  });
  return promise;
};

app.feedbackPane.setCompleteMessage = function( complete ) {
  if ( complete ) {
    $("#feedback-pane #exercise-complete")
      .text( "Complete" )
      .removeClass( "cyco-exer-not-complete" )
      .addClass( "cyco-exer-complete" );
  }
  else {
    $("#feedback-pane #exercise-complete")
      .text( "Not complete" )
      .removeClass( "cyco-exer-complete" )
      .addClass( "cyco-exer-not-complete" );
  }
};

app.feedbackPane.setFeedbackSentMessage = function( sent ) {
  if ( sent ) {
    $("#feedback-pane #feedback-sent")
      .text( "Feedback sent" )
      .removeClass( "cyco-exer-feedback-not-sent" )
      .addClass( "cyco-exer-feedback-sent" );
  }
  else {
    $("#feedback-pane #feedback-sent")
      .text( "Feedback not sent" )
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