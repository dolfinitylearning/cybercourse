/**
 * @file
 * Implement client-side of the tweaks.
 */

"use strict";
(function ($) {

/**
 * Collapse the summary area. Change collapsing link text to show whether there
 * is summary content.
 */
var nameSpaceRef; //Convenience.
Drupal.behaviors.cycoNodeEditTweaks = {
  attach: function (context, settings) {
    //Show we do anything?
    if ( ! Drupal.settings.cycoNodeEditTweaks
         || ! Drupal.settings.cycoNodeEditTweaks.enabled ) {
      return false;
    }
    nameSpaceRef = this;
    $(window).load(this.start);
  },
  start: function(){
    $(".swim-summary-wrapper").each(function() {
      //Sometimes this runs more than once, so do this only if the
      //summary is MT.
      if ( $(this).parent().find(".collapse-summary-indicator").length == 0 ) {
        //Remember the summary content widget.
        var summaryWidget = nameSpaceRef.findCKSummaryWidget();
        if ( ! summaryWidget ) {
          return;
        }
        //Compute text to show.
        var indicatorText 
            = nameSpaceRef.computeStatusMessage( summaryWidget );
        var indicatorHtml = "<span class='collapse-summary-indicator'>" 
            + indicatorText + "</span>";
        //Get the label embedded in a lower level in the
        //wrapper, and make it a label for the wrapper.
        var $label = $($(this).find("label").get(0));
        $label
            .attr("for", "swim-summary-wrapper")
            .attr("class", "swim-summary-wrapper-label")
            .attr("title", "Click to expand/collapse");
        $(this).prepend($label);
        //Append indicator to label.
        $label.append(indicatorHtml);
        //Append triangle to left of label, for clicking.
        $label.html( "<span class='arrow-thing'>&#x25b6;</span> " + $label.html() );
        //Remember what to collapse.
        var whatToCollapse = $label.next();
        //Remember content indicator.
        var contentIndicator = $label.find(".collapse-summary-indicator");
        //Remember arrow thing.
        var arrowThing = $label.find(".arrow-thing");
        whatToCollapse.hide();
        
        //Find the summary container.
        var summContainer = $("#edit-field-body .swim-summary-wrapper");
        //The body.
        var bodyContainer = $(summContainer).next();
        $(bodyContainer).find("label").after( summContainer );
        
        //Flag to show whether collapsed.
        var collapsed = true;
        $label.click(function(event){
          if( collapsed ) {
            collapsed = false;
            //Indicator only shows when collapsed.
            $(contentIndicator).hide();
            //Change the arrow direction.
            $(arrowThing).html( "&#x25bc;" );
            $(whatToCollapse).show("fast");
          }
          else {
            collapsed = true;
            $(contentIndicator).html( 
                nameSpaceRef.computeStatusMessage( summaryWidget ) 
            ).show();
            $(arrowThing).html( "&#x25b6;" );
            $(whatToCollapse).hide("fast");
          }
        });
      }
    });
  },
  computeStatusMessage: function( widgetToCheck ) {
    return ( widgetToCheck.getData() == "" )
        ? "Summary is empty" 
        : "Summary has content";
  },
  findCKSummaryWidget: function() {
    for ( var instanceName in CKEDITOR.instances ) {
      if ( instanceName.indexOf("summary") !== -1 ) {
        //This is it.
        return CKEDITOR.instances[instanceName];
      }
    } //End for.
      console.log("Didn't find summary instance.");
  }
};

})(jQuery);