"use strict";
/**
 * @file
 * Suppress the kid page list in the book top nav bar.
 */
(function ($) {
  Drupal.behaviors.bookTopNavbar = {
    attach: function (context, settings) {
      //If settings exist...
      if ( Drupal.settings.bookTopBNavbar ) {
        //If suppressing kids...
        if ( Drupal.settings.bookTopBNavbar.supressKids ) {
          var topNavbar = $(".book-navigation .menu").get(0);
          $(topNavbar).remove();
        }
      }
    }
  };
}(jQuery));