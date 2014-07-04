/**
 * View/controller for the pane that shows the rubric items.
 */

var app = app || {};

//Create a namespacey object for this pane.
app.rubricPane = {};
//Timeout for updating current comment from new comment text area. Milliseconds.
app.rubricPane.newCommentTimeoutDelay = 1000;

/**
 * Initialize the rubric pane for a given exercise.
 * @param {int} exerciseNid The exercise.
 */
app.initRubricPane = function( exerciseNid ) {
  var submissionNid = app.currentState.submissionNid;
  //Get the exercise's rubric list.
  var rubricNids = app.allExercises[ exerciseNid ].rubricItems;
  //Get the current selections, if they exist.
  //This would happen when grader is looking back at a graded submission.
  var currentRubricSelections = app.submissionsToGrade[ submissionNid ].rubricItemSelections;
//  var currentRubricSelections = null;
//  if ( app.submissionsToGrade[ submissionNid ].rubricItemSelections ) {
//    currentRubricSelections 
//      = app.submissionsToGrade[ submissionNid ].rubricItemSelections;
//  }
  //Clear existing content.
  $("#rubric-pane .pane-content").children().remove();
  //Render each rubric item.
  for( var key in rubricNids ) {
    var rubricNid = rubricNids[ key ];
    var currentRubricSelection = null;
    if ( currentRubricSelections[ rubricNid ] ) {
      currentRubricSelection = currentRubricSelections[ rubricNid ];
    }
    app.renderRubricItem( rubricNid, currentRubricSelection );
  }
  //Give each new comment container a timer index, used to track 
  //individual event timers for each container. The timers update
  //the chosen comment from the textarea a user is typing in.
  var newCommentContainers 
      = $("#rubric-pane .pane-content .cybercourse-rubric-item-new-comment-container");
  var numNewCommentContainers = newCommentContainers.length;
  newCommentContainers.each( function(index, element) {
    $(element).attr("data-timer-index", index);
  });
  app.rubricPane.newCommentTimers = new Array( numNewCommentContainers );
  //Set up events.
  //When the user types into a new comment field:
  //  1. Add a new new comment field, if needed.
  //  2. Make what the user typed the current comment, after a short delay.
  $("#rubric-pane .pane-content")
    .on("keypress", ".cybercourse-rubric-item-new-comment-container textarea",
      function( event ){
      //Add a new comment field if needed.
      app.rubricPane.addNewCommentField( event.target );
      //Reset timer.
      var timerIndex = $(event.target).parent().attr("data-timer-index");
      window.clearTimeout( app.rubricPane.newCommentTimers[ timerIndex ] );
      app.rubricPane.newCommentTimers[ timerIndex ] 
          = window.setTimeout(
            app.rubricPane.setChosenFromNewComment,
            app.rubricPane.newCommentTimeoutDelay,
            timerIndex );
    }
  );
  /**
   * If click new comment textarea, make it the Chosen One if there is
   * stuff in it.
   */
  $("#rubric-pane .pane-content")
    .on("focus", ".cybercourse-rubric-item-new-comment-container textarea",
      function( event ){
        var textarea = $ ( event.target );
        app.rubricPane.choosePopulatedTextarea(textarea);        
      }
  );  
  //When user clicks a comment, show it as the Chosen One, collapse
  //rubric item display.
  $(".pane-content").on("click", ".cybercourse-rubric-item-comment", function(event) {
    var newCommentText = $( event.target ).text();
    //Show that this is the Chosen One.
    app.rubricPane.showChosen( event.target );
    var rubricItemContainer = $( event.target )
        .parents(".cybercourse-rubric-item-container");
    rubricItemContainer
        .find(".cybercourse-rubric-item-chosen-text")
        .text( newCommentText );
    app.rubricPane.toggleRubricItemDisplayState( rubricItemContainer );
  });
  //When the user clicks to collapse button...
  $(".display-state").click(function(event) {
    var rubricItemContainer 
        = $( event.target ).parents(".cybercourse-rubric-item-container").first();
    app.rubricPane.toggleRubricItemDisplayState( rubricItemContainer );
  });
  //When the user clicks a new comment container...
  $(".pane-content")
    .on("click", ".cybercourse-rubric-item-new-comment-container", 
        function(event) {
          var textarea = $( event.target )
              .find(".cybercourse-rubric-item-new-comment-text");
          app.rubricPane.choosePopulatedTextarea( textarea );
          return;
          var $textarea = $($( event.target )
              .find(".cybercourse-rubric-item-new-comment-text"));
          //Is there anything in the container's textarea?
          var newCommentText = $textarea.val();
          if ( newCommentText ) {
            newCommentText = newCommentText.trim();
            if ( newCommentText.length > 0 ) {
              //There is something in the container's text widget. Chose it.
              var rubricItemContainer 
                  = $( event.target )
                      .parents(".cybercourse-rubric-item-container").first();
              $(rubricItemContainer)
                .find(".cybercourse-rubric-item-chosen-text").text( newCommentText );
              app.rubricPane.showChosen( event.target );
            }
          }
        }
    );
  //When the user clicks the Complete checkbox...
  $(".cyco-exercise-complete").change(function(event){
    //Set both checkboxes to the same value.
    var newState = $(this).prop("checked");
    $(".cyco-exercise-complete").prop("checked", newState);
    //Change the complete indicator in feedback pane.
    app.feedbackPane.setCompleteMessage( newState );
  });
  //When user clicks a generate feedback button...
  $(".generate-feedback-button").click(function() {
    $.when(
      app.rubricPane.createFeedbackMessage()
    )
    .then(function() {
      var complete = $(".cyco-exercise-complete").prop("checked");
      app.feedbackPane.initFeedbackPane( complete );
    });
  });
  //Show everything - hidden when UI loads.
  $("#rubric-pane div").show();
};

/**
 * Check whether a new comment can be chosen. Only if its textarea has content.
 * @param {type} textarea
 */
app.rubricPane.choosePopulatedTextarea = function(textarea) {
  //Is there anything in the container's textarea?
  var newCommentText = textarea.val();
  if ( newCommentText ) {
    newCommentText = newCommentText.trim();
    if ( newCommentText.length > 0 ) {
      //There is something in the container's text widget. Choose it.
      var rubricItemContainer 
          = $( textarea )
              .parents(".cybercourse-rubric-item-container").first();
      $(rubricItemContainer)
        .find(".cybercourse-rubric-item-chosen-text").text( newCommentText );
      app.rubricPane.showChosen( $(textarea).parent() );
    }
  }
};

/**
 * Render a rubric item.
 * @param {int} rubricNid Rubric to render.
 * @param {type} currentSelections Current selections, if any.
 */
app.renderRubricItem = function( rubricNid, currentSelections ) {
  var rubricItem = app.allRubricItems[ rubricNid ];
  //Convert data format into that used by the tempate.
  var templateData = { 
    title: rubricItem.title,
    rubricItemNid: rubricNid
  };
  templateData.commentsGroups = new Array();
  //Good comments.
  var commentsGroup = app.formatCommentsGroup( "Good", rubricItem.good );
  templateData.commentsGroups.push( commentsGroup );
  //Needs work comments.
  commentsGroup = app.formatCommentsGroup( "Needs work", rubricItem.needsWork );
  templateData.commentsGroups.push( commentsGroup );
  //Poor comments.
  commentsGroup = app.formatCommentsGroup( "Poor", rubricItem.poor );
  templateData.commentsGroups.push( commentsGroup );
  //Render the template.
  var result = app.compiledTemplates.rubricItemTemplate( templateData );
  $("#rubric-pane .pane-content").append( result );
};

/**
 * Format data from good/needs work/poor comments into template format.
 * @param {string} groupName The name of the group, e.g., good.
 * @param {Array} commentsList Comments in the group.
 * @returns {object} Data in template format.
 */
app.formatCommentsGroup = function( groupName, commentsList ) {
  //Compute an id for an HTML 5 data- property.
  var groupDataId = groupName.toLowerCase();
  groupDataId = groupDataId.replace( " ", "_" );
  var commentsGroup = { 
    set: groupName,
    setId: groupDataId
  };
  commentsGroup.comments = new Array();
  for( var index in commentsList ) {
    var comment = commentsList[ index ];
    commentsGroup.comments.push( { "comment": comment } );
  }
  return commentsGroup;
};

/**
 * Set chosen comment from new comment.
 * @param {type} timerIndex Unique index attached to new comment container.
 *     Shows which comment to copy.
 */
app.rubricPane.setChosenFromNewComment = function( timerIndex ) {
  var newCommentContainer = $("[data-timer-index=" + timerIndex + "]");
  var newCommentText 
      = $(newCommentContainer).find("textarea").val();
  var rubricItemContainer 
      = $(newCommentContainer).parents( ".cybercourse-rubric-item-container" );
  $(rubricItemContainer)
      .find(".cybercourse-rubric-item-chosen-text").text( newCommentText );
  //Highlight the container as the Chosen One.
  app.rubricPane.showChosen( newCommentContainer );
};

/**
 * Toggle the collapsed/expanded state of a rubric item.
 * @param {DOM element} rubricItemContainer The container to alter.
 */
app.rubricPane.toggleRubricItemDisplayState = function( rubricItemContainer ) {
  if ( $( rubricItemContainer )
         .find(".cybercourse-rubric-item-details :visible").length > 0 ) {
    //Visible - hide it.
    $( rubricItemContainer ).find(".cybercourse-rubric-item-details").hide("fast");
    //Change the arrow.
    $( rubricItemContainer ).find(".display-state").text("▾");
  }
  else {
    //Hidden - show it.
    $( rubricItemContainer ).find(".cybercourse-rubric-item-details").show("fast");
    //Change the arrow.
    $( rubricItemContainer ).find(".display-state").text("▴");
  }
};

/**
 * User typed/hit checkbox in new comment area. Add a blank new comment
 * area if needed.
 * @param {DOM element} widget Widget user clicked on.
 */
app.rubricPane.addNewCommentField = function( widget ) {
  //Check a data flag that shows whether a new comment event has been
  //processed for this widget.
  if ( $(widget)
        .parents(".cybercourse-rubric-item-new-comment-container[new-done=yes]")
        .length == 0
     ) {
    //Not added a new comment container yet.
    //Create the new HTML.
    var html = app.compiledTemplates.newCommentTemplate( {} );
    //Need to trim, or $() will fail.
    var $html = $( html.trim() );
//    var $html = $($("#newCommentContainerTemplate").html());
    //Add a timeout element for it.
    var newIndex = app.rubricPane.newCommentTimers.length;
    app.rubricPane.newCommentTimers[ newIndex ] = "";
    $html.attr("data-timer-index", newIndex);
    //Append.
    $( widget ).parents(".cybercourse-rubric-item-comment-set").append( $html );
    //Add flag to show processing done.
    $( widget ).parents(".cybercourse-rubric-item-new-comment-container")
        .attr("new-done", "yes");
  }
};

/**
 * Show that a comment has been chosen.
 * @param {type} chosenOne The comment.
 */
app.rubricPane.showChosen = function( chosenOne ) {
  var $chosenOne = $(chosenOne);
  //Skip if the chosenOne already has a chosen indicator.
  if ( $chosenOne.hasClass( "cybercourse-rubric-item-chosen-indicator" ) ) {
    return;
  }
  //Remove indicator from comments.
  $chosenOne
      .parents(".cybercourse-rubric-item-container")
      .find(".cybercourse-rubric-item-chosen-indicator")
      .removeClass("cybercourse-rubric-item-chosen-indicator");
  //Same for new comment containers.
  $chosenOne
      .parents(".cybercourse-rubric-item-container")
      .find(".cybercourse-rubric-item-new-comment-container")
      .removeClass("cybercourse-rubric-item-chosen-indicator");
  //Add the class to the Chosen One.
  $chosenOne.addClass("cybercourse-rubric-item-chosen-indicator");
};

/**
 * Create a feedback message to send to the student.
 */
app.rubricPane.createFeedbackMessage = function() {
  app.feedbackPane.showGeneratingThrobber();
  var webServiceUrl = app.basePath + "exercise/feedback/makeFeedbackMessage";
  var dataToSend = {};
  dataToSend.submission_nid = app.currentState.submissionNid;
  dataToSend.student_uid = app.currentState.studentUid;
  dataToSend.exercise_nid = app.currentState.exerciseNid;
  dataToSend.model_solution_nid = app.currentState.modelSolutionNid;
  dataToSend.rubric_ratings = app.rubricPane.packageRubicRatings();
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
    $("#cyco-feedback-editor").val( message );
    $("#feedback-pane .pane-content").fadeIn('fast');
  })
  .fail(function(jqXHR, textStatus, errorThrown) {
    Drupal.behaviors.cybercourseErrorHandler.reportError(
      "Fail in app.rubricPane.createFeedbackMessage."  
        + " textStatus: " + textStatus + ", errorThrown: " + errorThrown
    );
  })
  .always(function() {
    app.feedbackPane.hideGeneratingThrobber();
  });
  return promise;
};

/**
 * Package users's selections ready to send to server.
 * @returns object Selections.
 */
app.rubricPane.packageRubicRatings = function() {
  var result = new Array();
  $("#rubric-pane .cybercourse-rubric-item-container").each(function(index, rubricItemDom){
    var $chosenCommentDom 
        = $($(rubricItemDom).find(".cybercourse-rubric-item-chosen-indicator"));
    var chosenCommentHtml;
    //Comment could be in a textarea (for a new comment) or not (existing comment).
    if ( $chosenCommentDom.hasClass("cybercourse-rubric-item-new-comment-container") ) {
      chosenCommentHtml = $chosenCommentDom.find("textarea").val();
    }
    else {
      chosenCommentHtml = $chosenCommentDom.html();
    }
    var chosenCommentRating 
        = $chosenCommentDom
            .parents(".cybercourse-rubric-item-comment-set")
            .attr("data-comment-set");
    var rubric_item = {};
    rubric_item.rubric_item_nid = $(rubricItemDom).attr("data-rubric-item-nid");
    rubric_item.comment = chosenCommentHtml;
    rubric_item.comment_rating = chosenCommentRating;
    result.push( rubric_item );
  });
  return result;
};
