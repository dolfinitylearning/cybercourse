/**
 * @file
 * View/controller for the pane that shows the model solution.
 */

var app = app || {};

/**
 * Set up the model solution pane.
 * @param {array} modelSolutions Array of model solution nids (indexes into
 * the model solutions array). 
 */
app.resetModelSolutionPane = function( modelSolutions ) {
  var $paneContents = $("#model-solution-pane .pane-content");
  $paneContents.html("");
  if ( ! modelSolutions || modelSolutions.length === 0 ) {
    //There are no model solution.s
    $paneContents.html("<p class='cybercourse-grading-no-model'>No model solutions given.</p>");
  }
  else {
    var numModels = modelSolutions.length;
    var message = ( numModels === 1 )
      ? "There is one model solution."
      : "There are " + numModels + " model solutions.";
    var messageWrapped = 
        "<p class='cybercourse-grading-num-models'>" + message + "</p>";
    $paneContents.append( messageWrapped );
    var modelCounter = 0;
    modelSolutions.forEach(function(modelSolutionNid){
      var modelSolution = app.allModelSolutions[ modelSolutionNid ];
      modelCounter ++;
      if ( numModels > 1 ) {
        $paneContents.append(
            "<p class='cybercourse-grading-model-number'>Model" 
            + modelCounter + "</p>"
        );
      }
      if ( modelSolution.renderedSolution ) {
        $paneContents.append( modelSolution.renderedSolution );
      }
      if ( modelSolution.notes ) {
        $paneContents.append(
                "<div class='cybercourse-grading-notes-container'>"
              +   "<p class='cybercourse-grading-notes-title'>Notes</p>"
              +   "<p class='cybercourse-grading-notes'>" + modelSolution.notes + "</p>"
              + "</div>"
          );
      }
    }); //End foreach.
  } //End there are model solutions.
};
