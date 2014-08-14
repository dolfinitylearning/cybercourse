/**
 * @file
 * View/controller for the pane that shows the rubric items.
 */

var app = app || {};

//Create a namespacey object for this pane.
app.rubricPane = {};
//Timeout for updating current comment from new comment text area. Milliseconds.
app.rubricPane.newCommentTimeoutDelay = 1000;

//Flag for whether click events are simulated during
//reset. If so, don't want to animate screen changes. 
app.rubricPane.simClickDuringReset = true;

/**
 * Initialize the rubric pane. Call this only once.
 */
app.rubricPane.initRubricPane = function() {
  //When the user clicks the Complete checkbox...
  $(".cyco-exercise-complete").change(function(event){
    //Set both checkboxes to the same value.
    var newState = $(this).prop("checked");
    $(".cyco-exercise-complete").prop("checked", newState);
    //Change the complete indicator in feedback pane.
    app.feedbackPane.updateStatusComplete( newState );
    //Update data model.
    app.submissionsToGrade[ app.currentState.submissionNid ].complete = newState;
    //Set dirty flag.
    if ( ! app.rubricPane.simClickDuringReset ) {
      app.submissionsToGrade[ app.currentState.submissionNid ].dirty = true;
    }
  });
  //When user clicks a generate feedback button...
  $(".generate-feedback-button").click(function() {
    $.when(
      app.rubricPane.createFeedbackMessage()
    )
    .then(function() {
      app.feedbackPane.resetFeedbackPaneForSubmission();
    });
  });
};

/**
 * Resert the rubric pane for the current submission.
 */
app.rubricPane.resetRubricPaneForSubmission = function() {
  var exerciseNid = app.currentState.exerciseNid;
  var submissionNid = app.currentState.submissionNid;
  //Get the exercise's rubric list.
  var rubricNids = app.allExercises[ exerciseNid ].rubricItems;
  //Clear existing content.
  $("#rubric-pane .pane-content").children().off().remove();
  //Render each rubric item.
  rubricNids.forEach( function( rubricNid ) {
    app.rubricPane.renderRubricItem( rubricNid );
  });
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
  //Keypress in new comment.
  $("#rubric-pane .pane-content")
    .on("keypress", ".cybercourse-rubric-item-new-comment-container textarea",
      function( event ){
        app.rubricPane.newCommentContentChange( event );
    }
  );
  //Paste into new comment.
  $("#rubric-pane .pane-content")
    .on("paste", ".cybercourse-rubric-item-new-comment-container textarea",
      function( event ){
        app.rubricPane.newCommentContentChange( event );
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
    //If this is a real user-generated event...
    if ( ! app.rubricPane.simClickDuringReset ) {
      //Ignore event if feedback already sent.
      if ( app.submissionsToGrade[ app.currentState.submissionNid ].feedbackSent ) {
        return;
      }
    }
    var newCommentText = $( event.target ).text();
    //Show that this is the Chosen One.
    app.rubricPane.showChosen( event.target );
    var rubricItemContainer = $( event.target )
        .closest(".cybercourse-rubric-item-container");
    rubricItemContainer
        .find(".cybercourse-rubric-item-chosen-text")
        .text( newCommentText );
    app.rubricPane.toggleRubricItemDisplayState( rubricItemContainer );
    //Update data model.
    var rubricItemNid = 
        $(event.target)
        .closest('div.cybercourse-rubric-item-container')
        .attr("data-rubric-item-nid");
    var rubricItemRating = 
        $(event.target)
        .closest("div.cybercourse-rubric-item-comment-set")
        .attr("data-comment-set")
    app.rubricPane.updateRubricItemSelectionDataModel( 
        rubricItemNid, newCommentText, rubricItemRating
    );
    //Show number of ungraded rubric items.
    app.rubricPane.updateUngradedRubricCount();
    //Set dirty flag.
    if ( ! app.rubricPane.simClickDuringReset ) {
      app.submissionsToGrade[ app.currentState.submissionNid ].dirty = true;
    }
  });
  //When the user clicks to collapse button...
  $(".display-state").on("click", function(event) {
    var rubricItemContainer 
        = $( event.target ).closest(".cybercourse-rubric-item-container").first();
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
                      .closest(".cybercourse-rubric-item-container").first();
              $(rubricItemContainer)
                .find(".cybercourse-rubric-item-chosen-text").text( newCommentText );
              app.rubricPane.showChosen( event.target );
            }
          }
        }
    );
  //User clicks pin...
  $(".pane-content").on("click", ".cyco-rubric-item-new-comment-remember", 
    function(event) {
      var pin = $(event.target);
      if ( pin.hasClass("cyco-save-off") ) {
        pin
          .removeClass("cyco-save-off")
          .addClass("cyco-save-on");
      }
      else {
        pin
          .removeClass("cyco-save-on")
          .addClass("cyco-save-off");
      }
      //Update the data model.
      var rubricItemNid = pin
              .closest("[data-rubric-item-nid]")
              .attr("data-rubric-item-nid");
      var rubricItemRating = 
          pin
          .closest("div.cybercourse-rubric-item-comment-set")
          .attr("data-comment-set");
      var newCommentIndex = 
          pin
          .closest("[data-new-comment-index]")
          .attr("data-new-comment-index");
      var pinOn = pin.hasClass("cyco-save-on");
      if ( rubricItemRating == "good" ) {
        app.allRubricItems[ rubricItemNid ]
          .goodNewComments[ newCommentIndex ].saveFlag
          = pinOn;
      }
      else if ( rubricItemRating == "needs_work" ) {
        app.allRubricItems[ rubricItemNid ]
          .needsWorkNewComments[ newCommentIndex ].saveFlag
          = pinOn;
      }
      else if ( rubricItemRating == "poor" ) {
        app.allRubricItems[ rubricItemNid ]
          .poorNewComments[ newCommentIndex ].saveFlag
          = pinOn;
      }
      else {
        Drupal.behaviors.cycoErrorHandler.reportError(
          "Fail in app.rubricPane.click on pin! Bad rubricItemRating: "  
            + rubricItemRating
        );
        return;
      }
    }
  );
  //Get the current selections, if they exist.
  //This would happen when grader is looking back at a graded submission.
  var currentRubricSelections = app.submissionsToGrade[ submissionNid ].rubricItemSelections;
  //If there are already item selections in the data model, reflect 
  //them in the GUI.
  app.rubricPane.simClickDuringReset = true;
  rubricNids.forEach( function( rubricNid ){
    if ( currentRubricSelections[ rubricNid ] ) {
      var currentRubricComment = currentRubricSelections[ rubricNid ].comment;
      //Find the comment and click on it.
      //Search the predefined elements first.
      var rubricItemContainer 
          = $("div.cybercourse-rubric-item-container[data-rubric-item-nid="
            + rubricNid + "]");
      var commentElements = $(rubricItemContainer).find(".cybercourse-rubric-item-comment");
      var targetCommentElement = null;
      $.each( commentElements, function( index, element ) {
        if ( $(element).html() ==  currentRubricComment ) {
          targetCommentElement = element;
        }
      });
     //Found something yet?
      if ( targetCommentElement === null) {
        //Could be that one of the new comments was the Chosen One.
        var newCommentElements = $(rubricItemContainer)
                .find("textarea.cybercourse-rubric-item-new-comment-text");
        $.each( newCommentElements, function( index, element ) {
          if ( $(element).val() == currentRubricComment ) {
            targetCommentElement 
                = $(element).closest(".cybercourse-rubric-item-new-comment-container");
          }
        });
      }
      //Found the Chosen One?
      if ( targetCommentElement !== null) {
        //Click it.
        $(targetCommentElement).click();
      }
    }
  });
  //Show number of ungraded rubric items.
  app.rubricPane.updateUngradedRubricCount();
  //Set the disabled state of widgets if f/b already send.
  app.rubricPane.updateWidgetsDisabled();
  //Events from the user now, so allow animations.
  app.rubricPane.simClickDuringReset = false;
  //Show everything - hidden when UI loads.
  $("#rubric-pane > div").show();
};

/**
 * Update the disabled state of the widgets.
 */
app.rubricPane.updateWidgetsDisabled = function() {
  var feedbackSent 
    = app.submissionsToGrade[ app.currentState.submissionNid ].feedbackSent;
  $("#rubric-pane *").prop("disabled", feedbackSent);
};


/**
 * A textarea for a new comment has changed. Keypress or paste.
 * When the user types into a new comment field:
 *  1. Add a new new comment field, if needed.
 *  2. Make what the user typed the current comment, after a short delay.
 *  3. Update the data model.
 * @param {Event} event What happened.
 */
app.rubricPane.newCommentContentChange = function(event) {
  //Add a new comment field if needed.
  app.rubricPane.addNewCommentField( event.target );
  //Reset timer.
  var timerIndex = $(event.target)
          .closest("[data-timer-index]")
          .attr("data-timer-index");
  window.clearTimeout( app.rubricPane.newCommentTimers[ timerIndex ] );
  app.rubricPane.newCommentTimers[ timerIndex ] 
      = window.setTimeout(
        app.rubricPane.setChosenFromNewComment,
        app.rubricPane.newCommentTimeoutDelay,
        timerIndex );
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
              .closest(".cybercourse-rubric-item-container").first();
      $(rubricItemContainer)
        .find(".cybercourse-rubric-item-chosen-text").text( newCommentText );
      app.rubricPane.showChosen( 
          $(textarea).closest(".cybercourse-rubric-item-new-comment-container")
      );
    }
  }
};

/**
 * Store rubric item selection data into the data model for the current
 * submission.
 * @param {int} rubricItemNid
 * @param {string} comment
 * @param {string} commentRating
 */
app.rubricPane.updateRubricItemSelectionDataModel = function( 
        rubricItemNid, comment, commentRating
    ){
  var rubricItemSelection = new app.RubricItemSelection();
  rubricItemSelection.rubricItemNid = rubricItemNid;
  rubricItemSelection.comment = comment;
  rubricItemSelection.commentRating = commentRating;
  app.submissionsToGrade[ app.currentState.submissionNid ]
          .rubricItemSelections[ rubricItemNid ] = rubricItemSelection;
};

/**
 * Render a rubric item.
 * @param {int} rubricNid Rubric to render.
 *    Null if none.
 */
app.rubricPane.renderRubricItem = function( rubricNid ) {
  var rubricItem = app.allRubricItems[ rubricNid ];
  //Convert data format into that used by the tempate.
  var templateData = { 
    title: rubricItem.title,
    rubricItemNid: rubricNid
  };
  templateData.commentsGroups = new Array();
  //Good comments.
  var commentsGroup = app.rubricPane.formatCommentsGroup( 
      "Good", 
      rubricItem.good,
      rubricItem.goodNewComments
  );
  templateData.commentsGroups.push( commentsGroup );
  //Needs work comments.
  commentsGroup = app.rubricPane.formatCommentsGroup( 
      "Needs work", 
      rubricItem.needsWork,
      rubricItem.needsWorkNewComments
  );
  templateData.commentsGroups.push( commentsGroup );
  //Poor comments.
  commentsGroup = app.rubricPane.formatCommentsGroup( 
      "Poor", 
      rubricItem.poor,
      rubricItem.poorNewComments
  );
  templateData.commentsGroups.push( commentsGroup );
  //Render the template.
  var result = app.compiledTemplates.rubricItemTemplate( templateData );
  $("#rubric-pane .pane-content").append( result );
};

/**
 * Format data from good/needs work/poor comments into template format.
 * @param {string} groupName The name of the group, e.g., good.
 * @param {Array} commentsList Comments in the group.
 * @param {Array} newCommentsList New comments (entered by user).
 * @returns {object} Data in template format.
 */
app.rubricPane.formatCommentsGroup = function( 
        groupName, commentsList, newCommentsList ) {
  //Compute an id for an HTML 5 data- property.
  var groupDataId = groupName.toLowerCase();
  groupDataId = groupDataId.replace( " ", "_" );
  var commentsGroup = { 
    set: groupName,
    setId: groupDataId
  };
  commentsGroup.comments = new Array();
  commentsList.forEach( function( comment ) {
    commentsGroup.comments.push( {
      "comment": comment
    } );
  });
  var index = 0;
  commentsGroup.newComments = new Array();
  newCommentsList.forEach( function( object ){
    commentsGroup.newComments.push( {
      "comment": object.comment,
      "saveFlag": object.saveFlag,
      "commentIndex": index 
    });
    index++;
  });
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
      = $(newCommentContainer).closest( ".cybercourse-rubric-item-container" );
  $(rubricItemContainer)
      .find(".cybercourse-rubric-item-chosen-text").text( newCommentText );
  //Highlight the container as the Chosen One.
  app.rubricPane.showChosen( newCommentContainer );
  //Update rubric item data model.
  var $textarea = $($(newCommentContainer).find("textarea"));
  var rubricItemNid = 
      $textarea
      .closest('div.cybercourse-rubric-item-container')
      .attr("data-rubric-item-nid");
  var rubricItemRating = 
      $textarea
      .closest("div.cybercourse-rubric-item-comment-set")
      .attr("data-comment-set")
  //Which of the new items is it?
  var newItemIndex = 
      $textarea
      .closest("[data-new-comment-index]")
      .attr("data-new-comment-index");
  if ( rubricItemRating == "good" ) {
    app.allRubricItems[ rubricItemNid ].goodNewComments[ newItemIndex ].comment 
        = newCommentText;
  }
  else if ( rubricItemRating == "needs_work" ) {
    app.allRubricItems[ rubricItemNid ].needsWorkNewComments[ newItemIndex ].comment 
        = newCommentText;
  }
  else if ( rubricItemRating == "poor" ) {
    app.allRubricItems[ rubricItemNid ].poorNewComments[ newItemIndex ].comment 
        = newCommentText;
  }
  else {
    Drupal.behaviors.cycoErrorHandler.reportError(
      "Fail in app.rubricPane.setChosenFromNewComment. Bad rubricItemRating: "  
        + rubricItemRating
    );
    return;
  }
  //Update submission rubric item selection.
  app.rubricPane.updateRubricItemSelectionDataModel( 
      rubricItemNid, newCommentText, rubricItemRating
  );
  //Show number of ungraded rubric items.
  app.rubricPane.updateUngradedRubricCount();
  //Set dirty flag.
  if ( ! app.rubricPane.simClickDuringReset ) {
    app.submissionsToGrade[ app.currentState.submissionNid ].dirty = true;
  }
};

/**
 * Toggle the collapsed/expanded state of a rubric item.
 * @param {DOM element} rubricItemContainer The container to alter.
 */
app.rubricPane.toggleRubricItemDisplayState = function( rubricItemContainer ) {
  var animationSpeed = app.rubricPane.simClickDuringReset ? 10: "fast";
    //0 makes show() do nothing.
  if ( $( rubricItemContainer )
         .find(".cybercourse-rubric-item-details :visible").length > 0 ) {
    //Visible - hide it.
    $( rubricItemContainer )
            .find(".cybercourse-rubric-item-details").hide(animationSpeed);
    //Change the arrow.
    $( rubricItemContainer ).find(".display-state").text("▾");
  }
  else {
    //Hidden - show it.
    $( rubricItemContainer ).
            find(".cybercourse-rubric-item-details").show(animationSpeed);
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
    //Compute the new comment index of the new comment.
    //Added to the HTML as an attr, so later code can
    //tell which new comment is being messed with.
    var rubricItemNid = $(widget)
            .closest("[data-rubric-item-nid]")
            .attr("data-rubric-item-nid");
    var rubricItemRating = 
        $(widget)
        .closest("div.cybercourse-rubric-item-comment-set")
        .attr("data-comment-set");
    var newCommentIndex;
    if ( rubricItemRating == "good" ) {
      newCommentIndex = app.allRubricItems[ rubricItemNid ].goodNewComments.length;
    }
    else if ( rubricItemRating == "needs_work" ) {
      newCommentIndex = app.allRubricItems[ rubricItemNid ].needsWorkNewComments.length;
    }
    else if ( rubricItemRating == "poor" ) {
      newCommentIndex = app.allRubricItems[ rubricItemNid ].poorNewComments.length;
    }
    else {
      Drupal.behaviors.cycoErrorHandler.reportError(
        "Fail in app.rubricPane.addNewCommentField! Bad rubricItemRating: "  
          + rubricItemRating
      );
      return;
    }
    var html = app.compiledTemplates.newCommentTemplate( {
      "comment": "",
      "saveFlag": false,
      "commentIndex": newCommentIndex 
    } );
    //Need to trim, or $() will fail.
    var $html = $( html.trim() );
    //Add a timeout element for it.
    var newIndex = app.rubricPane.newCommentTimers.length;
    app.rubricPane.newCommentTimers[ newIndex ] = "";
    $html.attr("data-timer-index", newIndex);
    //Append.
    $( widget ).parents(".cybercourse-rubric-item-comment-set").append( $html );
    //Add flag to show processing done.
    $( widget ).parents(".cybercourse-rubric-item-new-comment-container")
        .attr("new-done", "yes");
    //Update the rubic item data model.
    var newCommentData = new app.NewRubricComment();
    newCommentData.saveFlag = false;
    if ( rubricItemRating == "good" ) {
      app.allRubricItems[ rubricItemNid ].goodNewComments.push( newCommentData );
    }
    else if ( rubricItemRating == "needs_work" ) {
      app.allRubricItems[ rubricItemNid ].needsWorkNewComments.push( newCommentData );
    }
    else if ( rubricItemRating == "poor" ) {
      app.allRubricItems[ rubricItemNid ].poorNewComments.push( newCommentData );
    }
    else {
      Drupal.behaviors.cycoErrorHandler.reportError(
        "Fail in app.rubricPane.addNewCommentField. Bad rubricItemRating: "  
          + rubricItemRating
      );
    }
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
      .closest(".cybercourse-rubric-item-container")
      .find(".cybercourse-rubric-item-chosen-indicator")
      .removeClass("cybercourse-rubric-item-chosen-indicator");
  //Same for new comment containers.
  $chosenOne
      .closest(".cybercourse-rubric-item-container")
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
  //Remind user to remember new comments.
  app.rubricPane.rememberNewCommentsReminder();
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
    //Tell feedback pane to show it.
    app.feedbackPane.showFeedback( message );
    //Update the data model.
    app.submissionsToGrade[ app.currentState.submissionNid ].feedback = message;
    //Set dirty flag.
    if ( ! app.rubricPane.simClickDuringReset ) {
      app.submissionsToGrade[ app.currentState.submissionNid ].dirty = true;
    }
  })
  .fail(function(jqXHR, textStatus, errorThrown) {
    Drupal.behaviors.cycoErrorHandler.reportError(
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
            .closest(".cybercourse-rubric-item-comment-set")
            .attr("data-comment-set");
    var rubric_item = {};
    rubric_item.rubric_item_nid = $(rubricItemDom).attr("data-rubric-item-nid");
    rubric_item.comment = chosenCommentHtml;
    rubric_item.comment_rating = chosenCommentRating;
    if ( rubric_item.comment 
         && rubric_item.comment.trim() != "(Nothing chosen)" ) {
      //The string is set in index.html, in a Mustache template. 
      //Should make it a variable somehow. 
      result.push( rubric_item );
    }
  });
  return result;
};

/**
 * Show the number of rubrics ungraded.
 */
app.rubricPane.updateUngradedRubricCount = function() {
  //Get number rubrics for this exercise.
  var totalRubrics = app.countElements( 
    app.allExercises[ app.currentState.exerciseNid ].rubricItems
  );
  //Get number rubrics graded.
  var gradedRubrics = app.countElements( 
    app.submissionsToGrade[ app.currentState.submissionNid ].rubricItemSelections
  );  
  //Update message.
  var ungraded = totalRubrics - gradedRubrics;
  if ( ungraded == 0 ) {
    $("#ungraded-rubric-count")
      .text("All rubrics graded")
      .addClass("cyco-all-graded")
      .removeClass("cyco-ungraded");
  }
  else {
    $("#ungraded-rubric-count")
      .text("Rubrics ungraded: " + ungraded )
      .addClass("cyco-ungraded")
      .removeClass("cyco-all-graded");
  }
  //Update status in feedback pane.
  app.feedbackPane.updateStatusUngradedRubrics( ungraded );
};

/**
 * Remind the user to click the pin for new comments that
 * s/he wants to save with their rubrics.
 */
app.rubricPane.rememberNewCommentsReminder = function() {
  //Find all the reminder elements.
  var allReminders = $(".cyco-remember-reminder");
  //Keep the reminders for new comments that have a textarea with content.
  var remindersWithText = new Array();
  $(allReminders).each( function(index, reminderElement ){
    var textarea = $(reminderElement)
      .closest(".cybercourse-rubric-item-new-comment-container")
      .find("textarea");
    if ( $(textarea).val().trim() ) {
      remindersWithText.push( reminderElement );
    }
  });
  //Keep the reminders where the comment is not already pinned.
  var remindersWithTextNotPinned = new Array();
  remindersWithText.forEach( function( reminderElement ){
    var pin = $(reminderElement)
      .closest(".cybercourse-rubric-item-new-comment-container")
      .find(".cyco-rubric-item-new-comment-remember");
    if ( $(pin).hasClass("cyco-save-off") ) {
      remindersWithTextNotPinned.push( reminderElement );
    }
  });
  //Start flashing.
  remindersWithTextNotPinned.forEach( function( reminderElement ){
    $( reminderElement ).fadeIn("slow", 
      function() {
        $( reminderElement ).fadeOut("slow");
    });
  });
};
