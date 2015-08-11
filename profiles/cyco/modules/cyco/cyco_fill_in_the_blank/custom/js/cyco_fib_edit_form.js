/* 
 * Fill-in-the-blank edit form
 */

/**
 * @file
 * Manage the rubric creation UI.
 */
(function($) {
  "use strict";
  Drupal.behaviors.cycoFillInTheBlankEdit = {
    /**
     * What is checked? text, number, or none.
     */
    itemChecked: "none",
    attach: function(context, settings) {
      $(document).ready(function(){
        Drupal.behaviors.cycoFillInTheBlankEdit.setInputContolsState();
         $("#edit-field-response-type-und input[type='radio']").change(function(){
           Drupal.behaviors.cycoFillInTheBlankEdit.setInputContolsState();
         });
      });
    },
    /**
     * Check what is checked.
     */
    checkChecked: function() {
      var checkedControl 
         = $("#edit-field-response-type-und input[type='radio']:checked");
      if ( checkedControl.length == 0 ) {
        this.itemChecked = "none";
      }
      else {
        this.itemChecked = checkedControl.val();
      }
    },
    /**
     * Set the state of the input controls, depending on the response type.
     */
    setInputContolsState: function() {
      this.checkChecked();
      switch ( this.itemChecked ) {
        case "none":
          this.setNumberControlsEnabled( false );
          this.setTextControlsEnabled( false );
          break;
        case "number":
          this.setNumberControlsEnabled( true );
          this.setTextControlsEnabled( false );
          break;
        case "text":
          this.setNumberControlsEnabled( false );
          this.setTextControlsEnabled( true );
          break;
      }
    },
    /**
     * Set the number controls to enabled or not.
     * @param {Boolean} state True to enable, else false.
     */
    setNumberControlsEnabled: function( state ) {
      var lowest, highest;
      lowest = $("#edit-field-lowest input");
      highest = $("#edit-field-highest input");
      if ( state ) {
        lowest.removeAttr("disabled");
        highest.removeAttr("disabled");
      }
      else {
        lowest.attr("disabled", "disabled");
        highest.attr("disabled", "disabled");
      }
    },
    /**
     * Set the text controls to enabled or not.
     * @param {Boolean} state True to enable, else false.
     */
    setTextControlsEnabled: function( state ) {
      var correct, caseSensitive;
      correct = $("#edit-field-correct-text-answers input");
      caseSensitive = $("#edit-field-case-sensitive input");
      if ( state ) {
        correct.removeAttr("disabled");
        caseSensitive.removeAttr("disabled");
      }
      else {
        correct.attr("disabled", "disabled");
        caseSensitive.attr("disabled", "disabled");
      }
    }
  };
}(jQuery));


