/* 
 * @file
 * Guess the user's time zone.
 */
"use strict";
(function($) {
  var uiNamespace; //Convenient ref to a namespacey thing.
  Drupal.behaviors.cycoTimeZoneGuess = {
    attach: function(context, settings) {
      var message = Drupal.t("Time zone guess: ")
        + jstz.determine().name();
      $("#set-time-zone").parent().append("<p><br>" + message + "</p>");
    }
  };
}(jQuery));
