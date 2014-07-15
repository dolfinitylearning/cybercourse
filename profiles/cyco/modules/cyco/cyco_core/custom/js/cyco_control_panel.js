/* 
For control panel menus, show the title text after each link.
*/
"use strict";
(function ($) {
  Drupal.behaviors.cycoControlPanel = {
    attach: function() {
      //Only run if flag is set.
      if ( Drupal.settings.cycoControlPanel
           && Drupal.settings.cycoControlPanel.showMenuTitles ) {
        $(".cyco-control-panel ul.menu a").each( function(index, link) {
          //link is a menu <a>.
          var $link = $(link);
          //Only do it for links with a title attribute.
          if ( $link.attr("title") ) {
            //Add the title into the text of the link.
            var title = $link.attr("title");
            $link.html(
              $link.html() 
                + "<br><span class='cyco-cp-menu-title'>" + title + "</span>"
            );
          } //End if
        }); //End each
        }
    } //End attach
  };
}(jQuery));



