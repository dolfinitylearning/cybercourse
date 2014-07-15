/* 
* Handle client-side errors. 
* 
* Show the user an error message. Send the message to the server for 
* processing. The user can click a button to clear the message.
*/
"use strict";
(function ($) {
  var nameSpaceyThing; //Convenience reference.
  Drupal.behaviors.cycoErrorHandler = {
    attach: function() {
      nameSpaceyThing = this;
    }, //End attach
    reportError: function( message ) {
      //Show a "Please wait" display.
      nameSpaceyThing.showAjaxWaitDisplay( message );
      $.when(
        //Send the error report to the server.
        nameSpaceyThing.sendErrorToServer( message )
      )
      .then(function() {
        //Let the user hide the "Please wait" display.
        nameSpaceyThing.activateCloseButton();
      })
      .fail(function(jqXHR, textStatus, errorThrown) {
        //Error while reporting an error.
        alert( nameSpaceyThing.showMetaError( errorThrown ) );
      });
    }, //End reportError
    sendErrorToServer: function( message ) {
      var callbackUrl = Drupal.settings.basePath + "cyco_handle_client_error";
      var promise = $.ajax({
        type: "GET",
        contentType: "application/json; charset=utf-8",
        dataType: "json", 
        url: callbackUrl,
        data: { "message": message } //,
      })
      .done(function(response) {
        return;
      })
      .fail(function(jqXHR, textStatus, errorThrown) {
        //Error while reporting an error.
        alert( nameSpaceyThing.showMetaError( errorThrown ) );
      });
      return promise;
    },
    /**
     * Show the ajax waity thing. It includes the error message.
     * @param {string} message About the Bad Thing.
     */
    showAjaxWaitDisplay: function( message ) {
      //Ensure there is a message.
      if ( ! message ) {
        message = "(Hey, boo! It's a stealth error.)";
      }
      //Add the message container, if needed.
      if ( $("#cyco-client-error-container").length == 0 ) {
        //Display to show the user that an error is being reported.
        //The styles are inline to reduce dependencies on other code.
        var ajaxWaitDisplay = $("<h2 id='cyco-client-error-container' "
            + "style='background-color:yellow;font-size:1.2em;color:black;padding:10px;border:thick red;'>"
            + "Recording a client-side error: <span id='cyco-client-error'></span>"
            + "<div class='ajax-progress ajax-progress-throbber'>"
            +   "<div class='throbber'>&nbsp;</div>"
            + "</div>"
            + "<p>"
            +   "<button id='cyco-client-error-button' type='button'>"
            +     "Please wait..."
            +   "</button>"
            + "</p>");
        $("body").append( ajaxWaitDisplay );
        //Add event to let the user hide the display when ready.
        $("#cyco-client-error-button").click(function() {
          nameSpaceyThing.hideAjaxWaitDisplay()
        });
      }
      //Insert the error message.
      $("#cyco-client-error").html( message );
      //Init the close button.
      $("#cyco-client-error-button")
        .attr("disabled", "disabled")
        .text("Please wait...")
        .find(".ajax-progress-throbber").show();
      //Center the message container on the screen, and show it.
      //See http://stackoverflow.com/questions/15090439/how-to-position-a-div-element-at-the-center-of-the-actual-screen-jquery
      var $container = $("#cyco-client-error-container");
      $container.css("position", "fixed")
        .css("top", ($(window).height() / 2) - ($container.outerHeight() / 2))
        .css("left", ($(window).width() / 2) - ($container.outerWidth() / 2))
        .show("fast");
    },
    /**
     * Let the user use the button that closes the message.
     */
    activateCloseButton: function() {
      $("#cyco-client-error-button")
        .removeAttr("disabled")
        .text("Continue");
      $("#cyco-client-error-container .ajax-progress-throbber").hide();
    },
    hideAjaxWaitDisplay: function() {
     $("#cyco-client-error-container").hide();
    },
    /**
     * Show an error while reporting an error.
     * @param {string} message Original error message.
     */
    showMetaError: function( message ) {
      if ( ! message ) {
        message = "(I don't even know that! Man, this sucks. For real, baby.)";
      }
      message = "There was an error reporting an error. Ain't that ironic? "
          + "You should tell someone, boo. Maybe send a screenshot. "
          + "\n\nHere's the original error: " + message;
      alert( message );
    }
  };
}(jQuery));