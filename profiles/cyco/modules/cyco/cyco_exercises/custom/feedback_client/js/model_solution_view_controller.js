/**
 * View/controller for the pane that shows the model solution.
 */

var app = app || {};

app.initModelSolutionPane = function( modelSolutionNid ) {
  var $paneContents = $("#model-solution-pane .pane-content");
  $paneContents.html("");
  if ( ! modelSolutionNid ) {
    //There is no model solution.
    $paneContents.html("<p class='cybercourse-grading-no-model'>No model solution given.</p>");
  }
  else {
    var modelSolution = app.allModelSolutions[ modelSolutionNid ];
    if ( modelSolution.renderedSolution ) {
      $paneContents.html( modelSolution.renderedSolution );
    }
    if ( modelSolution.notes ) {
      $("#exercise-pane ")
        .append(
              "<div class='cybercourse-grading-notes-container'>"
            +   "<p class='cybercourse-grading-notes-title'>Notes</p>"
            +   "<p class='cybercourse-grading-notes'>" + modelSolution.notes + "</p>"
            + "</div>"
        );
    }
    
  }
};


