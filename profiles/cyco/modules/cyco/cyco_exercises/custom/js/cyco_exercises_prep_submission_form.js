/**
 * @file
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
    //Flag to show whether in the process of saving to the server.
    saving: false,
    attach: function(context, settings) {
      uiNamespace = Drupal.behaviors.cycoExerPrepSubmissionForm;
      //Grab the solution content for later comparison.
      uiNamespace.initialSolutionText 
          = $("#" + uiNamespace.solutionWidgetId).val();
      window.onbeforeunload = function (event) {
        if ( uiNamespace.saving ) {
          //Show AJAX throbber.
          console.log("dog");
          $("#edit-actions").after(
             "<div class='ajax-progress ajax-progress-throbber'>"
            +  "Saving..."
            +  "<div class='throbber'>&nbsp;</div>"
            + "</div>"
          );
        }
        else {
          //Flag to show whether the close should be confirmed with the user.
          //Cases:
          //1. There is new text in the text field.
          //2. A file has been selected but not uploaded.
          //3. There is no text and no file selected or uploaded.
          var confirmClose = false;
          var confirmMessage = "";
          //Has the content in the editor changed?
          var currentContent = $("#" + uiNamespace.solutionWidgetId).val();
          if ( currentContent != uiNamespace.initialSolutionText ) {
            //Ask user to confirm.
            confirmClose = true;
            confirmMessage += "You've changed your solution. ";
          }
          //Have there been changes in the files?
          if ( uiNamespace.userChangedFiles ) {
            //Ask user to confirm.
            confirmClose = true;
            confirmMessage += "You've changed the files. ";
          }
//          //Is there a file that has been selected but not uploaded?
//          if ( uiNamespace.selectedFileNotUploaded() ) {
//            confirmClose = true;
//            confirmMessage += "You've selected a file, but not uploaded it. ";
//          }          
          if ( confirmClose ) {
            event.returnValue = confirmMessage
              + "Are you sure you want to close?";
          }
        }
      };
      //When the window closes, tell the opener to refresh the links
      //for submission of the current exercise.
      window.onunload = function () {
        var exerciseNid = Drupal.settings.cyco_exercises.exerciseNid;
        opener.Drupal.behaviors.cycoExerSubLinks.refreshLinksForExercise( exerciseNid );
      };
      //Save draft button clicked.
      $("#cyco_save_draft").click(function() {
        $("input[name=save_draft_clicked").val("yes");
        $("#edit-submit").click();
      });
      //Save and submit button clicked - tell code that the user is saving.
      $("#edit-submit").click(function(evt) {
          //Is there a file that has been selected but not uploaded?
          if ( uiNamespace.selectedFileNotUploaded() ) {
            if ( ! confirm("You've selected a file, but not uploaded it. "
                + "Are you sure you want to close?") ) {
              evt.preventDefault();
              return;
            }
          }
          uiNamespace.saving = true;
      });
      //Cancel button clicked.
      $("#cyco_cancel").click(function() {
        window.close();
      });
      //User did something to a file.
      $("button[value=Remove]").click(function() {
        uiNamespace.fileOpDone();
      });
      $("button[value=Upload]").click(function() {
        uiNamespace.fileOpDone();
      });
      $("div.file-widget.form-managed-file .form-type-textfield input")
        .change(function() {
        uiNamespace.fileOpDone();
      });
      //If user clicks "Choose file" in the attach section, record that 
      //as a file op that dirties the submission data. 
      $("input.form-control.form-file").click(function(e) {
        uiNamespace.fileOpDone();
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
//    showHideReminder: function() {
//      //Show/hide reminder depending on state of feedback checkbox.
//      if ( $("#edit-submit-solution").attr("checked") ) {
//        $(".cyco_reminder").hide("fast");
//      }
//      else {
//        $(".cyco_reminder").show("fast");
//      }
//    },
    /**
     * A file operation was performed.
     */
    fileOpDone: function() {
      uiNamespace.userChangedFiles = true;
    },
//    selectedFileNotUploaded: function() {
//      //Is there a file that has been selected but not uploaded?
//      uiNamespace.filesSelectedNotUploaded = false;
//      $("input:file").each(function( index ) {
//        if ( $(this).val() != "" ) {
//          uiNamespace.filesSelectedNotUploaded = true;
//        }
//      });
//      return uiNamespace.filesSelectedNotUploaded;
//    }
    
  };
}(jQuery));
