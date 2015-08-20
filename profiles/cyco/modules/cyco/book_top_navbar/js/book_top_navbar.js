"use strict";
/**
 * @file
 * Suppress the kid page list in the book top nav bar.
 */
(function ($) {
  Drupal.behaviors.bookTopNavbar = {
    attach: function (context, settings) {
      //If settings exist...
      if ( Drupal.settings.bookTopNavbar ) {
        //If suppressing kids...
        if ( Drupal.settings.bookTopNavbar.supressKids ) {
          var topNavbar = $("#book-top-navbar-top-navbar .book-navigation .menu");
          $(topNavbar).remove();
        }
      }
    }
  };
}(jQuery));