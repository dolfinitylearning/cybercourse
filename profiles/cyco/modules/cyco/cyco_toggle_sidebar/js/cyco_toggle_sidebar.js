"use strict";
/**
 * Collapse/expand the sidebar.
 */
(function($) {
  var uiNameSpace; //For namespacing.
  Drupal.behaviors.toggleSidebar = {
    setup: function() {
      this.cookieName = "cyco_toggle_sidebar";
      //Cookie expires in 3 days, and is site-wide.
      //  Three days, because humans may have forgotten what they did
      //  by then.
      this.cookieOptions = { expires: 3, path: '/' };
      //Selector identifying the region to collapse.
      this.regionSelector = 
          Drupal.settings.toggleSidebar.tsbSidebarSelector;
      //Selector identifying the main region.
      this.mainRegionSelector =
          Drupal.settings.toggleSidebar.tsbMainRegionSelector;
      //The class the main region has when the sidebar is expanded
      this.mainRegionClassWhenSidebarCollapsed =
          Drupal.settings.toggleSidebar.tsbMainRegionClassWhenCollapsed;
              //"col-sm-12",
      //The class the main region has when the sidebar is collapse.
      this.mainRegionClassWhenSidebarExpanded =
          Drupal.settings.toggleSidebar.tsbMainRegionClassWhenExpanded;
              //"col-sm-9",
      //Code to show the widget.
      this.widgetCode = "<span "
                + "id='toggle-sidebar' "
                + "title='Show/hide the sidebar'>"
                + "</span>";
      //CSS Id for the widget.
      this.widgetSelector = "#toggle-sidebar";
    },
    attach: function(context, settings) {
      uiNameSpace = this;
      this.setup();
      //Only make one of them. CTools modals can cause multiples. 
      if ( $("#toggle-sidebar").length > 0 ) {
        return;
      }
      var sideRegion = $(uiNameSpace.regionSelector);
      var sideRegionContainer = sideRegion.parent();
      //Find the main content region.
      var mainRegion = $(uiNameSpace.mainRegionSelector);
      //Add the widget as the first child of the region.
      mainRegion.prepend(uiNameSpace.widgetCode);
      var widget = $(uiNameSpace.widgetSelector);
      //Position the widget left or right.
      if ( uiNameSpace.tsbIconPosition == "left" ) {
        widget
          .css("float", "left")
          .css("margin-left", -($(widget).width()) );
      }
      else {
        widget
          .css("float", "right")
          .css("margin-right", -($(widget).width()) );
      }
      //Set up the event.
      var toggleSidebar = this;
      //If cookie says it is hidden, hide it.
      if ( $.cookie(this.cookieName) ) {
        if ( $.cookie(this.cookieName) == "hidden") {
          this.hideSidebar(
            sideRegion, sideRegionContainer, 
            mainRegion, widget 
          );
          widget.addClass("collapsed");
        }
        else {
          widget.addClass("expanded");
        }
      }
      else {
        //100% cookie free. Add the expanded class to the widget, so the 
        //background shows, like the hero it is.
        widget.addClass("expanded");
      }
      widget.click(function() {
        var isHidden = (sideRegion.css("display") == "none");
        if (isHidden) {
          toggleSidebar.showSidebar(
            sideRegion, sideRegionContainer, 
            mainRegion, widget, "fast"
          );
          //Set cookie.
          $.cookie(
              toggleSidebar.cookieName, 
              "shown", 
              toggleSidebar.cookieOptions
          );
        }
        else {
          toggleSidebar.hideSidebar(
            sideRegion, sideRegionContainer, 
            mainRegion, widget, "fast"
          );
          //Set cookie.
          $.cookie(
              toggleSidebar.cookieName, 
              "hidden", 
              toggleSidebar.cookieOptions
          );
        }
      });
    }, //End atttach
    hideSidebar: function(
        sideRegion, sideRegionContainer, 
        mainRegion, widget, animationSpeed
      ) {
        widget.removeClass("expanded");
        widget.addClass("collapsed");
        sideRegion.hide(animationSpeed);
        if ( mainRegion ) {
          if ( uiNameSpace.mainRegionClassWhenSidebarExpanded ) {
            mainRegion.removeClass(
                uiNameSpace.mainRegionClassWhenSidebarExpanded
            );
          }
          if ( uiNameSpace.mainRegionClassWhenSidebarCollapsed ) {
            mainRegion.addClass(
                uiNameSpace.mainRegionClassWhenSidebarCollapsed
            );
          }
        }
    },
    showSidebar: function(
        sideRegion, sideRegionContainer, 
        mainRegion, widget, animationSpeed
      ) {
      widget.removeClass("collapsed");
      widget.addClass("expanded");
      if ( mainRegion ) {
        if ( uiNameSpace.mainRegionClassWhenSidebarCollapsed ) {
          mainRegion.removeClass(
              uiNameSpace.mainRegionClassWhenSidebarCollapsed
          );
        }
        if ( uiNameSpace.mainRegionClassWhenSidebarExpanded ) {
          mainRegion.addClass(
              uiNameSpace.mainRegionClassWhenSidebarExpanded
          );
        }
      }
      sideRegion.show(animationSpeed);
    }
  };
}(jQuery));
