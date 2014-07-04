/**
 * View/controller for the pane that shows the feedback message.
 */

var app = app || {};

//Create a namespacey object for this pane.
app.feedbackPane = {};

/**
 * Initialize the feedback pane after Make Message button in rubric
 * pane clicked.
 */
app.feedbackPane.initFeedbackPane = function( complete ) {
  //Set completed indicator.
  app.feedbackPane.setCompleteMessage( complete );  
  //Set up send event.
  $("#send-feedback-button").click( app.feedbackPane.sendFeedback );
  //Show the UI.
  $("#feedback-pane .pane-content").show();
};

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