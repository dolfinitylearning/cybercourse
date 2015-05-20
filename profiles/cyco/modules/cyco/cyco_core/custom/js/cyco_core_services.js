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
  
  cycoCoreServices.logEvent = function( bundle, activityType, summary, params ) {
    $.when(
      cycoCoreServices.getShouldLogOtherEvent( activityType )
    )
    .then(function() {
      if ( cycoCoreServices.shouldLogOtherEvent == "yes" ) {
        $.when(
          cycoCoreServices.sendEventToServer( bundle, activityType, summary, params )
        )
        .then(function() {
          //Nothing to do.
        })
        .fail(function() {
          alert("cycoCoreServices.logEvent died.");
        });
      }
    });
  };
  
  /**
   * Ask the server where an Other event should be logged.
   * @param string activityType Type of activity to log.
   * @returns boolean Whether to log event.
   */
  cycoCoreServices.getShouldLogOtherEvent = function( activityType ) {
    console.log('start fetchEventLogFlag');
    var webServiceUrl = 
            Drupal.settings.basePath + "event_logging/event_logging/shouldLogEvents";
    var promise = $.ajax({
      type: "POST",
      contentType: "application/json; charset=utf-8",
      dataType: "json", 
      data: activityType,
      url: webServiceUrl,
      beforeSend: function (request) {
        request.setRequestHeader("X-CSRF-Token", cycoCoreServices.csrfToken);
      }
    })
    .done(function(result) {
      console.log('done fetchEventLogFlag');
      cycoCoreServices.shouldLogOtherEvent = result[0];
    })
    .fail(function(jqXHR, textStatus, errorThrown) {
      alert('getJSON request in fetchEventLogFlag failed! ' + errorThrown);
    });
    console.log('end fetchEventLogFlag');
    return promise;
  };

  /**
   * Send event log data to server.
   */
  cycoCoreServices.sendEventToServer = function(bundle, activityType, summary, params) {
    var webServiceUrl = Drupal.settings.basePath + "event_logging/event_logging/logEvent";
    var dataToSend = {};
    dataToSend.bundle = bundle;
    dataToSend.activityType = activityType;
    dataToSend.summary = summary;
    dataToSend.params = JSON.stringify( params );
    var promise = $.ajax({
      type: "POST",
      contentType: "application/json; charset=utf-8",
      dataType: "json", 
      data: JSON.stringify(dataToSend),
      url: webServiceUrl,
      beforeSend: function (request) {
        request.setRequestHeader("X-CSRF-Token", cycoCoreServices.csrfToken);
      }
    })
    .done(function(result) {
      //Nothing to do.
    })
    .fail(function(jqXHR, textStatus, errorThrown) {
      alert('getJSON request in sendEventToServer failed! ' + errorThrown);
    });
    return promise;
  };

} )(jQuery);
