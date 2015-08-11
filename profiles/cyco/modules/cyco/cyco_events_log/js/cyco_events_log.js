/* 
 * @file
 * Library of services calls. Assumes some Drupal.settings are correct.
 */
"use strict";

var cycoEventsLog = cycoEventsLog || {};

(function($) {
  
  $(document).ready(function(){
    window.onunload = function() {
      if ( Drupal.settings.cycoLogEvents.logEvents == "yes" ) {
        if ( Drupal.settings.cycoLogEvents.eventType 
             && Drupal.settings.cycoLogEvents.eventType == "leave_page" ) {
          var dataToSend = {};
          dataToSend.path = Drupal.settings.cycoLogEvents.path;
          $.when(
            cycoEventsLog.sendEventToServer( "logPageLeaveEvent", dataToSend )
          )
          .then(function() {
            //Nothing to do.
          })
          .fail(function() {
            alert("cycoEventsLog.logPageLeaveEvent died.");
          });
          
        }
      }
    };
  });
  
  /**
   * Log an Other event.
   * @param string bundle Usually "other".
   * @param string activityType E.g., simulation run
   * @param string summary Summary of the event.
   * @param object params Object with event parameters.
   */
  cycoEventsLog.logOtherEvent = function( activityType, summary, params ) {
    if ( Drupal.settings.cycoLogEvents.logEvents == 'yes' ) {
      var dataToSend = {};
      dataToSend.bundle = 'other';
      dataToSend.activityType = activityType;
      dataToSend.summary = summary;
      dataToSend.params = JSON.stringify( params );
      $.when(
        cycoEventsLog.sendEventToServer( "logOtherEvent", dataToSend )
      )
      .then(function() {
        //Nothing to do.
      })
      .fail(function() {
        alert("cycoEventsLog.logOtherEvent died.");
      });
    }
  };
  
  /**
   * Send event log data to server.
   */
  cycoEventsLog.sendEventToServer = function( controller, dataToSend ) {
    var webServiceUrl = Drupal.settings.basePath 
            + "event_logging/event_logging/" + controller;
    var promise = $.ajax({
      type: "POST",
      contentType: "application/json; charset=utf-8",
      dataType: "json", 
      data: JSON.stringify(dataToSend),
      url: webServiceUrl,
      beforeSend: function (request) {
        request.setRequestHeader("X-CSRF-Token", 
          Drupal.settings.cycoCoreServices.csrfToken); //cycoCoreServices.csrfToken);
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
