/**
 * Prepare the exerise submisssion form.
 */
"use strict";

(function($) {
  var uiNamespace; //Convenient ref to a namespacey thing.
  Drupal.behaviors.cycoExerPrepSubmissionForm = {
    //Flag to detect whether user changed the files.
    userChangedFiles: false,
    initialSolutionText: '',
    solutionWidgetId: "edit-field-solution-und-0-value",
    attach: function(context, settings) {
      uiNamespace = Drupal.behaviors.cycoExerPrepSubmissionForm;
      //Grab the solution content for later comparison.
      uiNamespace.initialSolutionText 
          = $("#" + uiNamespace.solutionWidgetId).val();
      //Set up the submission reminder.
      uiNamespace.showHideReminder();
      $("#edit-submit-solution").click(
        uiNamespace.showHideReminder
      );
      window.onbeforeunload = function (event) {
        //Has the content in the editor changed?
        var currentContent = $("#" + uiNamespace.solutionWidgetId).val();
        if ( currentContent != uiNamespace.initialSolutionText
             || uiNamespace.userChangedFiles ) {
          //Ask user to confirm.
          event.returnValue = 
              "There are unsaved changes. Are you sure you want to close?";
        }
      };
      //When the window closes, tell the opener to refresh the links
      //for submission of the current exercise.
      window.onunload = function () {
        var exerciseNid = Drupal.settings.cyco_exercises.exerciseNid;
        opener.Drupal.behaviors.cycoExerSubLinks.refreshLinksForExercise( exerciseNid );
      };
      //If user clicks "Choose file" in the attach section, record that 
      //as a change to the submission. 
      $("input.form-control.form-file").click(function(e) {
        uiNamespace.userChangedFiles = true;
      });
      //If user clicks "Save", don't ask whether to abandon changes on unload.
      $("#edit-submit-solution").change(function() {
        uiNamespace.userChangedFiles = false;
        var currentContent = $("#" + uiNamespace.solutionWidgetId).val();
        uiNamespace.initialSolutionText = currentContent;
      });
      //Remove some things if they are present.
      //Preview changes button.
      $("#edit-preview-changes").remove();
      //View/edit tabs.
      $(".tabs-primary").remove();
      $(".tabs--primary").remove();
    },
    showHideReminder: function() {
      //Show/hide reminder depending on state of feedback checkbox.
      if ( $("#edit-submit-solution").attr("checked") ) {
        $(".cyco_reminder").hide("fast");
      }
      else {
        $(".cyco_reminder").show("fast");
      }
    }
  };
}(jQuery));
