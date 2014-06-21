/* 
 * @file
 * Library of services calls. Assumes some Drupal.settings are correct.
 */

var swimServices = swimServices || {};

(function($) {
  /*
  * Get the CSRF token.
  * @returns {unresolved} Promise.
  */
  swimServices.getCsrfToken = function(){
   //Connect and get token.
   var webServiceUrl 
     = Drupal.settings.swimServices.baseUrl + Drupal.settings.basePath 
       + "services/session/token";
   var promise = $.ajax({ 
       type: "GET",
       url: webServiceUrl,
       dataType: "text"
      })
     .done(function(token){
       swimServices.csrfToken = token;
     })
     .fail(function(jqXHR, textStatus, errorThrown) {
        Drupal.behaviors.cycoErrorHandler.reportError(
          "Token request failed in swimServices.getCsrfToken. " 
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
  swimServices.makeWaitThrobber = function( idToUse, message, extraClasses ) {
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
