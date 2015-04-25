/**
 * @file
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
    Drupal.behaviors.cycoErrorHandler.reportError(
      "Fail in app.getCsrfToken."  
        + " textStatus: " + textStatus + ", errorThrown: " + errorThrown
    );
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
    Drupal.behaviors.cycoErrorHandler.reportError(
      "Fail in app.getSubmissionsFromServer."  
        + " textStatus: " + textStatus + ", errorThrown: " + errorThrown
    );
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
  submission.version = submissionRecord.submission_version;
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
        Drupal.behaviors.cycoErrorHandler.reportError(
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
      Drupal.behaviors.cycoErrorHandler.reportError(
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
        Drupal.behaviors.cycoErrorHandler.reportError(
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
//      if ( result.models ) {
//        //Extract it from the server data.
//        app.loadModelSolutionsFromExercise( exerciseNid, result.models );
//      }
    })
    .fail(function(jqXHR, textStatus, errorThrown) {
      Drupal.behaviors.cycoErrorHandler.reportError(
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
//app.loadModelSolutionsFromExercise = function( exerciseNid, dataFromServer ) {
//  dataFromServer.forEach(function (record) {
//    var model = new app.ModelSolution();
//    model.modelSolutionNid = record.model_nid;
//    model.exerciseNid = exerciseNid;
//    //Add ref to model in exercise object.
//    app.allExercises[ exerciseNid ].modelSolutions.push( model.modelSolutionNid );
//    model.renderedSolution = '(MT)';
//    if ( record.rendered ) {
//      model.renderedSolution = record.rendered;
//    }
//    if ( record.notes ) {
//      model.notes = record.notes;
//    }
//    if ( record.attachments ) {
//      model.renderedSolution += app.makeLinksForAttachments(record.attachments);
//    }
//    app.allModelSolutions[ model.modelSolutionNid ] = model;
//  });
//};

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
    Drupal.behaviors.cycoErrorHandler.reportError(
      "Fail in app.getRubricItems. ids: " + rubricItemIds.join(",")  
        + " textStatus: " + textStatus + ", errorThrown: " + errorThrown
    );
  });
  return promise;
};

/**
 * Save new rubric item comments to the server.
 */
app.saveNewRubricItemComments = function() {
  var newComments = app.packageNewCommentData();
  //Any new comments to save?
  if ( newComments === null ) {
    return;
  }
  var webServiceUrl = app.basePath + "exercise/rubric_item/saveNewItemComments";
  var dataToSend = JSON.stringify( newComments );
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
    //Update the rubric items' models.
    app.updateRubricItemDataModels( newComments );
  })
  .fail(function(jqXHR, textStatus, errorThrown) {
    Drupal.behaviors.cycoErrorHandler.reportError(
      "Fail in app.feedbackPane.saveFeedback."  
        + " textStatus: " + textStatus + ", errorThrown: " + errorThrown
    );
  })
  .always(function() {
    app.feedbackPane.hideSendingThrobber();
  });  

};

/**
 * Create the data structure to send to the server, with new comments.
 * @returns {stdClass} Data to send to server, null for none.
 */
app.packageNewCommentData = function() {
  var newComments = new Array();
  //Loop through each rubric item.
  app.allRubricItems.forEach(function ( rubricItem ) {
    //Grad new comments this rubric item.
    var newCommentsOneRubric = new Array();
    //There should always be a blank item. Hence the 1.
    var newCommentOneRating;
    if ( rubricItem.goodNewComments.length > 1 ) {
      newCommentOneRating = app.getNewComments( 
        rubricItem.goodNewComments, "good"
      );
      newCommentsOneRubric = newCommentsOneRubric.concat( newCommentOneRating );
    }
    if ( rubricItem.needsWorkNewComments.length > 1 ) {
      newCommentOneRating = app.getNewComments( 
        rubricItem.needsWorkNewComments, "needs_work"
      );
      newCommentsOneRubric = newCommentsOneRubric.concat( newCommentOneRating );
    }
    if ( rubricItem.poorNewComments.length > 1 ) {
      newCommentOneRating = app.getNewComments( 
        rubricItem.poorNewComments, "poor"
      );
      newCommentsOneRubric = newCommentsOneRubric.concat( newCommentOneRating );
    }
    //Any new comments for this rubric?
    if ( newCommentsOneRubric.length > 0 ) {
      newComments[ rubricItem.nid ] = newCommentsOneRubric;
    }
  });
  if ( newComments.length === 0 ) {
    return null;
  }
  //Make sparse array into an object, with no MT spaces.
  var newCommentsObj = new Object();
  newComments.forEach( function(elem, index){
    if ( elem ) {
      newCommentsObj[index] = elem;
    }
  });
  return newCommentsObj;
};

/**
 * Return new comments for one comment array (good, needsWork, bad) for one 
 * rubric item.
 * @param {Array} newComments Comments.
 * @param {string} rating Rating
 * @returns {Array} New comments.
 */
app.getNewComments = function( newComments, rating ) {
  var result = new Array();
  newComments.forEach(function( newComment ){
    if ( newComment.saveFlag && newComment.comment ) {
      var record = {
        "comment": newComment.comment,
        "rating": rating
      };
      result.push( record );
    }
  });
  return result;
};

/**
 * Update the rubric items' models.
 * @param {Object} newComments Data on new comments.
 * Structure:
 * Object {16: Array[1], 19: Array[1]}
 *   16: Array[1]
 *     0: Object
 *       comment: "Poor comment smell"
 *       rating: "poor"
 *   19: Array[1]
 *     0: Object
 *       comment: "Good comment sleek"
 *       rating: "good"
 */
app.updateRubricItemDataModels = function( newComments ) {
  //Erase all the new comments data. It has been repackaged in newComments.
  app.allRubricItems.forEach(function( rubricItem ){
    rubricItem.goodNewComments = new Array();
    rubricItem.goodNewComments.push( new app.NewRubricComment() ); //Blank comment.
    rubricItem.needsWorkNewComments = new Array();
    rubricItem.needsWorkNewComments.push( new app.NewRubricComment() ); //Blank comment.
    rubricItem.poorNewComments = new Array();
    rubricItem.poorNewComments.push( new app.NewRubricComment() ); //Blank comment.
  });
  //Add the new comments.
  $.each(newComments,function(rubricItemNid, itemNewComments){
    //itemNewComments is all new comments for one rubric item.
    $.each(itemNewComments, function(index, commentData){
      var comment = commentData.comment;
      var rating = commentData.rating;
      if ( rating === "good" ) {
        app.allRubricItems[ rubricItemNid ].good.push( comment );
      }
      else if ( rating === "needs_work" ) {
        app.allRubricItems[ rubricItemNid ].needsWork.push( comment );
      }
      else if ( rating === "poor" ) {
        app.allRubricItems[ rubricItemNid ].poor.push( comment );
      }
      else {
        Drupal.behaviors.cycoErrorHandler.reportError(
          "Fail in app.updateRubricItemDataModels. Bad rating: "  
            + rating
        );
        return;
      }
    });
  });
};
