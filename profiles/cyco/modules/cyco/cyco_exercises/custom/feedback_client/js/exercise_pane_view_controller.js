/**
 * @file
 * View/controller for the pane that shows the exercise solution.
 */

var app = app || {};

app.resetExercisePane = function( exerciseNid ) {
  var exercise = app.allExercises[ exerciseNid ];
  var $paneContents = $("#exercise-pane .pane-content");
  $paneContents.html("");
  if ( ! exercise.renderedExercise ) {
    //There is no exercise content.
    $paneContents.html(
        "<p class='cybercourse-grading-no-exercise'>No exercise content.</p>"
    );
  }
  else {
    $paneContents.html( exercise.renderedExercise );
  }
  if ( exercise.notes ) {
      $paneContents.append(
            "<div class='cybercourse-grading-notes-container'>"
          +   "<p class='cybercourse-grading-notes-title'>Notes</p>"
          +   "<p class='cybercourse-grading-notes'>" + exercise.notes + "</p>"
          + "</div>"
      );
  }
};