/* 
 * @file
 * Library of services calls. Assumes some Drupal.settings are correct.
 */
"use strict";

var cycoCoreServices = cycoCoreServices || {};

(function($) {
  /**
   * Make the HTML for a wait throbber.
   * @param {string} idToUse Id to give the throbber. If omitted, throbber
   *   has no id.
   * @param {string} message Message to show. Defaults to Please wait...
   * @param {string} extraClasses Extra classes to give the throbber.
   * @returns {string} HTML for the throbber.
   */
  cycoCoreServices.makeWaitThrobber = function( idToUse, message, extraClasses ) {
    var throbberHtml = "<div";
    if ( idToUse ) {
      throbberHtml += " id='" + idToUse + "'";
    }
    if ( extraClasses ) {
      throbberHtml += " class='" + extraClasses + "'";
    }
    throbberHtml += ">";
    if ( message ) {
      throbberHtml += message;
    }
    else {
      throbberHtml += "Please wait...";
    }
    throbberHtml += ">"
      +   "<div class='ajax-progress ajax-progress-throbber'>"
      +     "<div class='throbber'>&nbsp;</div>"
      +   "</div>"
      + "</div>"
    return throbberHtml;
  };
  
} )(jQuery);
