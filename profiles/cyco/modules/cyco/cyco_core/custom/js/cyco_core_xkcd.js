/**
* @file
* Add XKCD comic to the page.
*/
"use strict";
(function ($) {
  Drupal.behaviors.xkcdComic = {
    attach: function() {
      $.ajax({
          url: "//dynamic.xkcd.com/api-0/jsonp/comic?callback=?",
//          url: "http://dynamic.xkcd.com/api-0/jsonp/comic?callback=?",
          dataType: "json",
          jsonpCallback: "xkcddata",
          success: function(data) {
            var container = $("<div>").attr({
              id: "xkcd-container"
            });
            var title = $("<p>")
              .attr({
                id: "xkcd-title"
              })
              .html("Latest <a href='http://xkcd.com' target='_blank'>"
                + "XKCD</a> comic.");
            $(container).append( title );
            var img = $("<img/>").attr({
              src: data.img,
              title: data.alt,
              alt: data.title
            });
            $(container).append( img );
            $(".cyco-control-panel").append( container );
          }
      });
    } //End attach
  };
}(jQuery));



