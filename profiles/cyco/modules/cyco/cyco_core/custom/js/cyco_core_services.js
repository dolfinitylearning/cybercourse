/* 
 * @file
 * Library of services calls. Assumes some Drupal.settings are correct.
 */
"use strict";

var cycoCoreServices = cycoCoreServices || {};

(function($) {
  /*
  * Get the CSRF token.
  * @returns {unresolved} Promise.
  */
  cycoCoreServices.getCsrfToken = function(){
   if ( cycoCoreServices.csrfToken ) {
     //Already have it.
     return;
   }
   //Connect and get token.
   var webServiceUrl 
     = Drupal.settings.cycoCoreServices.baseUrl + Drupal.settings.basePath 
       + "services/session/token";
   var promise = $.ajax({ 
       type: "GET",
       url: webServiceUrl,
       dataType: "text"
      })
     .done(function(token){
       cycoCoreServices.csrfToken = token;
     })
     .fail(function(jqXHR, textStatus, errorThrown) {
        Drupal.behaviors.cycoErrorHandler.reportError(
          "Token request failed in cycoErrorHandler.getCsrfToken. " 
            + "textStatus: " + textStatus + ", errorThrown: " + errorThrown
        );
     });
   return promise;
  };
  
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
