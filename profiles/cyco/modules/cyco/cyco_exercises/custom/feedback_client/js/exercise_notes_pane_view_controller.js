/**
 * @file
 * View/controller for the pane that shows exercise notes.
 */

var app = app || {};

/**
 * Set up the pane.
 * TODO: render from Textile to HTML?
 */
app.resetExerciseNotesPane = function( notes ) {
  var $paneContents = $("#exercise-notes-pane .pane-content");
  notes ? $paneContents.html(notes) : $paneContents.html("");
};
