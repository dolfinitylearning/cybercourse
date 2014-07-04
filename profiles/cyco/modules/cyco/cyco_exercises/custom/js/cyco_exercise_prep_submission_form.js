/**
 * Prepare the exerise submisssion form.
 */

(function($) {
  var uiNamespace; //Convenient ref to a namespacey thing.
  Drupal.behaviors.cycoExerPrepSubmissionForm = {
    //Flag to detect unsaved changes on window onload.
    userChangedStuff: false,
    attach: function(context, settings) {
      uiNamespace = Drupal.behaviors.cycoExerPrepSubmissionForm;
      //When the window closes, tell the opener to refresh the links
      //for submission of the current exercise.
      window.onbeforeunload = function (event) {
        //Has the content in the editor changed?
        var editor = CKEDITOR.instances["edit-field-solution-und-0-main"];
        if ( editor.checkDirty() ) {
          uiNamespace.userChangedStuff = true;
        }
        if ( uiNamespace.userChangedStuff ) {
          //Ask user to confirm.
          event.returnValue = 
              "There are unsaved changes. Are you sure you want to close?";
        }
      };
      window.onunload = function () {
        var exerciseNid = Drupal.settings.cybercourse_exercise.exerciseNid;
        opener.Drupal.behaviors.cycoExerSubLinks.refreshLinksForExercise( exerciseNid );
      };
      //If user clicks anything in the attach section, record that as a change
      //to the submission. A bit of overkill, but simple.
      $("#edit-attachments-fieldset").click(function(e) {
        uiNamespace.userChangedStuff = true;
      });
      //If user clicks "Save", don't ask whether to abandon changes on unload.
      $("#edit-submit").click(function() {
        uiNamespace.userChangedStuff = false;
      });
      //Remove some things if they are present.
      //Preview changes button.
      $("#edit-preview-changes").remove();
      //View/edit tabs.
      $(".tabs-primary").remove();
    }
  };
}(jQuery));
