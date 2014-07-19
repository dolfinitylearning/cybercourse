/**
 *  Functions to exchange data with the server.
 */

var app = app || {};

/*
* Get the CSRF token.
* @returns {unresolved} Promise.
*/
app.getCsrfToken = function(){
// console.log("Getting token");
 //Connect and get user details.
  var webServiceUrl = app.basePath + "services/session/token";
  var promise = $.ajax({ 
     type: "GET",
     url: webServiceUrl,
     dataType: "text"
  })
  .done(function(token){
    app.csrfToken = token;
  })
  .fail(function(jqXHR, textStatus, errorThrown) {
    console.log('Token request failed! ' + textStatus + errorThrown); 
  });
 return promise;
};

app.getSubmissionsFromServer = function() {
  var webServiceUrl = app.basePath 
          + "exercise/feedback/getGraderSubmissionsNeedingFeedback";
  var promise = $.ajax({
    type: "POST",
    contentType: "application/json; charset=utf-8",
    dataType: "json",
    url: webServiceUrl,
    beforeSend: function (request) {
      request.setRequestHeader("X-CSRF-Token", app.csrfToken);
    }
  })
  .done(function(result) {
    //Move data into the data model.
    var submissionRecords = result.submissions;
    $.each( submissionRecords, function( index, submissionRecord ){
      app.createSubmissionFromServerRecord( index, submissionRecord );
    });
    var groupRecords = result.groups;
    $.each( groupRecords, function( gid, title ){
      //Create group object.
      var group = new app.Group();
      //Fill it from server data.
      group.groupId = gid;
      group.title = title;
      //Add to data model.
      app.allGroups[ gid ] = group;
    });
    //Store group memberships in student records.
    //Have an array of arrays of group ids, keyed by uid.
    var memberships = result.memberships;
    $.each( memberships, function( uid, groups ){
      app.allStudents[ uid ].groups = groups;
    });
  })
  .fail(function(jqXHR, textStatus, errorThrown) {
    alert('test fetch request failed! ' + errorThrown);
  });
  return promise;
};

/**
 * Store data about submission into local data structure.
 * @param {type} recordOrder Order in which the record was delivered from the 
 * server. Use the same order when displaying the data.
 * @param {type} submissionRecord Submission record.
 */
app.createSubmissionFromServerRecord = function( recordOrder, submissionRecord ) {
  //Create submission object.
  var submission = new app.Submission();
  submission.recordOrder = recordOrder;
  submission.submissionNid = submissionRecord.submission_nid;
  submission.exerciseNid = submissionRecord.exercise_nid;
  submission.studentUid = submissionRecord.submitter_uid;
  submission.whenSubmitted = submissionRecord.when_submitted;
  app.submissionsToGrade[ submission.submissionNid ] = submission;
  //Add student object if not present.
  if ( ! app.allStudents[ submissionRecord.submitter_uid ] ) {
    var student = new app.Student();
    student.studentUid = submissionRecord.submitter_uid;
    student.name = submissionRecord.display_name;
    app.allStudents[submissionRecord.submitter_uid] = student;
  }
  //Add exercise object if not present.
  if ( ! app.allExercises[ submissionRecord.exercise_nid ] ) {
    var exercise = new app.Exercise();
    exercise.exerciseNid = submissionRecord.exercise_nid;
    exercise.title = submissionRecord.exercise_title;
    app.allExercises[ submissionRecord.exercise_nid ] = exercise;
  }
};


app.loadSubmissionFromServer = function( submissionNid ) {
  //Check if it is loaded already.
  if ( app.submissionsToGrade[ submissionNid ].renderedSolution ) {
    //Already got it. Nowt to do
    return true;
  }
  else {
    //Load from server.
    var webServiceUrl = app.basePath + "exercise/feedback/getSubmissionRendered";
    var dataToSend = {};
    dataToSend.sub_nid = submissionNid;
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
    .done(function(result){
      if ( result.status != "ok" ) {
        var message = result.message;
        Drupal.behaviors.cybercourseErrorHandler.reportError(
          "Fail in app.loadSubmissionFromServer. subNid: "  
            + submissionNid + " message: " + message
        );
        return false;
      }
      var renderedSubmission = result.rendered;
      //Are there attached files?
      if ( result.attachments ) {
        var attachmentsHtml = app.makeLinksForAttachments( result.attachments );
        renderedSubmission += attachmentsHtml;
      }
      app.submissionsToGrade[ submissionNid ].renderedSolution = renderedSubmission;
      //return renderedSubmission;
    })
    .fail(function(jqXHR, textStatus, errorThrown) {
      Drupal.behaviors.cybercourseErrorHandler.reportError(
        "Fail in app.loadSubmissionFromServer. subNid: "  
          + submissionNid
          + " textStatus: " + textStatus + ", errorThrown: " + errorThrown
      );
    });
    return promise;
  }
};


app.loadExerciseFromServer = function( exerciseNid ) {
  //Check if it is loaded already.
  if ( app.allExercises[ exerciseNid ].renderedExercise ) {
    //Already got it. Nowt to do.
    return true;
  }
  else {
    //Load from server.
    var webServiceUrl = app.basePath + "exercise/feedback/getExerciseRendered";
    var dataToSend = {};
    dataToSend.exer_nid = exerciseNid;
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
    .done(function(result){
      if ( result.status != "ok" ) {
        var message = result.message;
        Drupal.behaviors.cybercourseErrorHandler.reportError(
          "Fail in app.loadExerciseFromServer. exerNid: "  
            + exerciseNid + " message: " + message
        );
        return false;
      }
      var renderedExercise = result.rendered;
      //Are there attached files?
      if ( result.attachments ) {
        var attachmentsHtml = app.makeLinksForAttachments( result.attachments );
        renderedExercise += attachmentsHtml;
      }
      //Are there hidden attached files?
      if ( result.hidden_attachments ) {
        var hiddenAttachmentsHtml = app.makeLinksForAttachments( 
            result.hidden_attachments,
            "Hidden attachments"
        );
        renderedExercise += hiddenAttachmentsHtml;
      }
      //Store rendered in data object.
      app.allExercises[ exerciseNid ].renderedExercise = renderedExercise;
      //Rubric items.
      if ( result.rubric_items ) {
        for( var key in result.rubric_items ) {
          app.allExercises[ exerciseNid ].rubricItems.push( result.rubric_items[ key ] );
        }
      }
      //Load any missing rubric definitions from the server.
      app.loadRubricItemsFromServer( app.allExercises[ exerciseNid ].rubricItems );
      //Is there a model solution?
      if ( result.models ) {
        //Extract it from the server data.
        app.loadModelSolutionsFromExercise( exerciseNid, result.models );
      }
    })
    .fail(function(jqXHR, textStatus, errorThrown) {
      Drupal.behaviors.cybercourseErrorHandler.reportError(
        "Fail in app.loadExerciseFromServer. exerNid: "  
          + exerciseNid
          + " textStatus: " + textStatus + ", errorThrown: " + errorThrown
      );
    });
    return promise;
  }
};

/**
 * Extract model solution data from the exercise data from the server.
 * @param {int} exerciseNid Exercise this is a model for.
 * @param {Array} dataFromServer Model solution data from server.
 */
app.loadModelSolutionsFromExercise = function( exerciseNid, dataFromServer ) {
  dataFromServer.forEach(function (record) {
    var model = new app.ModelSolution();
    model.modelSolutionNid = record.model_nid;
    model.exerciseNid = exerciseNid;
    //Add ref to model in exercise object.
    app.allExercises[ exerciseNid ].modelSolutions.push( model.modelSolutionNid );
    model.renderedSolution = '(MT)';
    if ( record.rendered ) {
      model.renderedSolution = record.rendered;
    }
    if ( record.notes ) {
      model.notes = record.notes;
    }
    if ( record.attachments ) {
      model.renderedSolution += app.makeLinksForAttachments(record.attachments);
    }
    app.allModelSolutions[ model.modelSolutionNid ] = model;
  });
};

/**
 * Find out which rubric items have not been loaded yet.
 * @param {Array} rubricItemList Rubric item nids to check.
 * @returns {Array} Rubric item nids that have not been loaded yet.
 */
app.findMissingItems = function( rubricItemList ) {
  var missingItems = new Array();
  for( var index in rubricItemList ) {
    var rubricItemIdToCheck = rubricItemList[ index ];
    if ( ! app.allRubricItems[ rubricItemIdToCheck ] ) {
      missingItems.push( rubricItemIdToCheck );
    }
  }
  return missingItems;
}

/**
 * Load any missing rubric item definitions from the server.
 * @param {Array} rubricItemIds Item ids.
 */
app.loadRubricItemsFromServer = function( rubricItemIds ) {
  if ( rubricItemIds.length == 0 ) {
    //Nothing to do.
    return true;
  }
  //Send request to server.
  var webServiceUrl = app.basePath + "exercise/feedback/getRubricItems";
  var promise = $.ajax({
    type: "POST",
    contentType: "application/json; charset=utf-8",
    dataType: "json",
    data: JSON.stringify( rubricItemIds ),
    url: webServiceUrl,
    beforeSend: function (request) {
      request.setRequestHeader("X-CSRF-Token", app.csrfToken);
    }
  })
  .done(function(result){
    for( var itemId in result ) {
      var serverData = result[ itemId ];
      var rubricItem = new app.RubricItem();
      rubricItem.nid = serverData.nid;
      rubricItem.title = serverData.title;

      if ( serverData.good ) {
        rubricItem.good = Array();
        for( var needsWorkId in serverData.good ) {
          rubricItem.good.push( serverData.good[ needsWorkId ] );
        }
      }
      //Create a blank new comment object.
      rubricItem.goodNewComments.push( new app.NewRubricComment() );
      
      if ( serverData.needs_work ) {
        rubricItem.needsWork = Array();
        for( var needsWorkId in serverData.needs_work ) {
          rubricItem.needsWork.push( serverData.needs_work[ needsWorkId ] );
        }
      }
      rubricItem.needsWorkNewComments.push( new app.NewRubricComment() );

      if ( serverData.poor ) {
        rubricItem.poor = Array();
        for( var poorId in serverData.poor ) {
          rubricItem.poor.push( serverData.poor[ poorId ] );
        }
      }
      rubricItem.poorNewComments.push( new app.NewRubricComment() );

      if ( serverData.notes ) {
        rubricItem.notes = serverData.notes;
      }
      //Put in data store.
      app.allRubricItems[ rubricItem.nid ] = rubricItem;
    }
  })
  .fail(function(jqXHR, textStatus, errorThrown) {
    Drupal.behaviors.cybercourseErrorHandler.reportError(
      "Fail in app.getRubricItems. ids: " + rubricItemIds.join(",")  
        + " textStatus: " + textStatus + ", errorThrown: " + errorThrown
    );
  });
  return promise;
};
