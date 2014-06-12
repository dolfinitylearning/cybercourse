/**
 * @file
 * Implement collapsing on book rearrange form.
 */

(function($) {
  "use strict";
  Drupal.behaviors.bookRearrangeCollapse = {
    attach: function(context, settings) {
      $("#book-outline").on("dblclick", ".tabledrag-handle", function(event){
        var $handle = $(event.target);
        //Find the container of the clicked icon.
        var $tr = $handle.closest("tr");
        //Is it collapsed?
        var isCollapsed = $tr.hasClass("collapsed");
        var followingSibs = $tr.nextAll("tr");
        //Compute indentation level of the clicked tr.
        var targetIndentLevel = $tr.children("td").first().children(".indentation").length;
        //Counter of trs that have been affected.
        var changedSibs = 0;
        //For each tr after the clicked tr...
        for ( var i = 0; i < followingSibs.length; i++ ) {
          var $sib = $(followingSibs.get(i));
          //Compute indent level.
          var sibIndentLevel = $sib.children("td").first()
              .children(".indentation").length;
          if ( sibIndentLevel > targetIndentLevel ) {
            //This tr belongs to the clicked tr.
            changedSibs++;
            if ( isCollapsed ) {
              $sib.show();
            }
            else {
              $sib.hide();
            }
          } //End indent level check.
          else {
            break;
          }
        } //End for.
        //Only change class if changes were actually made.
        if ( changedSibs > 0 ) {
          if ( isCollapsed ) {
            $tr.removeClass("collapsed");
          }
          else {
            $tr.addClass("collapsed");
          }
        }
      });
    } //End attach.
  };
}(jQuery));



