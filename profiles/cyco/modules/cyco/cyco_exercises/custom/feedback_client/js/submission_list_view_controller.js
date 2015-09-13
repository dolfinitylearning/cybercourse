/**
 * @file
 * Manage the list of submissions to grade.
 */
var app = app || {};

//Create a namespacey object for this pane.
app.submissionListPane = {};

/**
 * Initialize the submission list display in the outer north pane.
 * Display data and setup events.
 */
app.initSubmissionList = function() {
  //Prep data for the template.
  var dataForTemplate = { submissionMeta: new Array() };
  //Compute order in which to show the records.
  var orderedSubmissionKeys = new Array();
  for ( var key in app.submissionsToGrade) {
    orderedSubmissionKeys[ app.submissionsToGrade[ key ].recordOrder ]
      = key;
  }
  for ( key in orderedSubmissionKeys) {
    var submission = app.submissionsToGrade[ orderedSubmissionKeys[ key ] ];
    var templateRecord = new Object();
    templateRecord.submissionNid = submission.submissionNid;
    templateRecord.timeAgo = app.capitaliseFirstLetter( 
        submission.whenSubmitted
    );
    templateRecord.exerciseName 
        = app.allExercises[ submission.exerciseNid ].title;
    var version = submission.version;
    if ( version > 1 ) {
      templateRecord.exerciseName += " (ver " + version + ")";
    }
    templateRecord.studentName 
        = app.allStudents[ submission.studentUid ].name;
    //Get groups student is in.
    templateRecord.groups = new Array();
    var studentGroupIds = app.allStudents[ submission.studentUid ].groups;
    for ( var groupsIndex in studentGroupIds ) {
      var groupId = studentGroupIds[ groupsIndex ];
      var groupTitle = app.allGroups[ groupId ].title;
      templateRecord.groups.push( { title: groupTitle } );
    }
    dataForTemplate.submissionMeta.push( templateRecord );
  }
  var html = app.compiledTemplates.submissionListTemplate( dataForTemplate );
  //Show all.
  $("#submission-list-pane .pane-content").html( html );
  //Convert times into time ago format.
//  $(".cybercourse_timeago").timeago();

  //Set up event.
  $("#submission-list-pane table tr").click(function(event){
    event.stopPropagation();
    event.preventDefault();
    var submissionId = Number($(this).attr("data-submission-nid"));
    app.submissionListItemClicked( submissionId );
//    console.log(submissionId);
    return false;
  });
}

/**
 * Use clicked on an item in the submission list pane.
 * @param {int} submissionNid Id of the submission list item click on.
 */
app.submissionListItemClicked = function( submissionNid ) {
  $("#submission-list-pane table tr").removeClass("current-submission");
  $("#submission-list-pane table tr[data-submission-nid=" + submissionNid + "]")
      .addClass("current-submission");
  //Grab the submission clicked on.
  var submissionItem = app.submissionsToGrade[ submissionNid ];
  var exerciseNid = submissionItem.exerciseNid;
  var studentUid = submissionItem.studentUid;
  //Remember current state.
  app.currentState.submissionNid = submissionNid;
  app.currentState.exerciseNid = exerciseNid;
  app.currentState.studentUid = studentUid;
  //Tell user to wait.
  app.showPrepForSubmissionGradingWait( submissionNid );
  $.when(
    //Load all of the required data from the server.
    app.loadSubmissionFromServer( submissionNid ),
    app.loadExerciseFromServer( exerciseNid )
  )
  .then(function(){
    //Show all the data in the UI.
    app.resetSubmissionPane( submissionNid );
    app.resetExercisePane( exerciseNid );
    app.resetExerciseNotesPane( app.allExercises[ exerciseNid ].notes );
    app.feedbackPane.resetFeedbackPaneForSubmission();
    //Load rubric items that haven't been loaded yet.
    var missingRubricItems = app.findMissingItems(
        app.allExercises[ exerciseNid ].rubricItems
    );
    $.when(
      app.loadRubricItemsFromServer( missingRubricItems )
    )
    .then(function(){
      app.rubricPane.resetRubricPaneForSubmission(),
      app.hidePrepForSubmissionGradingWait( submissionNid );
    });
  });
};

app.showPrepForSubmissionGradingWait = function( submissionNid ) {
  if ( $("#cybercourse-submittion-list-wait-container").length == 0 ) {
    var $waitIndicator = $(
          "<div id='cybercourse-submittion-list-wait-container'>"
        +   "Please wait..."
        +   "<div class='ajax-progress ajax-progress-throbber'>"
        +     "<div class='throbber'>&nbsp;</div>"
        +   "</div>"
        + "</div>");
    $("body").append( $waitIndicator );
  };
  $waitIndicator = $("#cybercourse-submittion-list-wait-container");
  //Position it.
  $("td.cyco-submission-list-wait[data-submission-nid=" + submissionNid + "]")
      .append( $waitIndicator )
      .show();
};

app.hidePrepForSubmissionGradingWait = function( submissionNid ) {
  $("td.cyco-submission-list-wait[data-submission-nid=" + submissionNid + "]")
      .hide();  
};

/**
 * Clear the UI, ready to grade a new submission. 
 * @param {type} submissionNid If set, show this submission has been graded.
 */
app.submissionListPane.resetUi = function( submissionNid ) {
  //Line through the submission listing.
  $("tr[data-submission-nid=" + submissionNid + "]")
      .addClass("submission-graded");
  
  //Clear current state.
  
};
