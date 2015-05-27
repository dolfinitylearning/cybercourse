/* 
 * @file
 * Library of services calls. Assumes some Drupal.settings are correct.
 */
"use strict";

var cycoEventsLog = cycoEventsLog || {};

(function($) {
  /**
   * Log an event.
   * @param string bundle Usually "other".
   * @param string activityType E.g., simulation run
   * @param string summary Summary of the event.
   * @param object params Object with event parameters.
   */
  cycoEventsLog.logEvent = function( bundle, activityType, summary, params ) {
    $.when(
      cycoEventsLog.getShouldLogOtherEvent( activityType )
    )
    .then(function() {
      if ( cycoEventsLog.shouldLogOtherEvent == "yes" ) {
        $.when(
          cycoEventsLog.sendEventToServer( bundle, activityType, summary, params )
        )
        .then(function() {
          //Nothing to do.
        })
        .fail(function() {
          alert("cycoEventsLog.logEvent died.");
        });
      }
    });
  };
  
  /**
   * Ask the server whether an Other event should be logged.
   * @param string activityType Type of activity to log.
   * @returns boolean Whether to log event.
   */
  cycoEventsLog.getShouldLogOtherEvent = function( activityType ) {
//    console.log('start fetchEventLogFlag');
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
//      console.log('done fetchEventLogFlag');
      cycoEventsLog.shouldLogOtherEvent = result[0];
    })
    .fail(function(jqXHR, textStatus, errorThrown) {
      alert('getJSON request in fetchEventLogFlag failed! ' + errorThrown);
    });
//    console.log('end fetchEventLogFlag');
    return promise;
  };

  /**
   * Send event log data to server.
   */
  cycoEventsLog.sendEventToServer = function(bundle, activityType, summary, params) {
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
