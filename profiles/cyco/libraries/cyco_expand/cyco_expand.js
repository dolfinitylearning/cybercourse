/* 
 * Expand/collapse marked content.
 * 
 * Version: 1.0
 * 
 * Use:
 * 
 * <div data-cyco-expand>
 * <TAG>Title</TAG>
 * Content
 * </div>
 * 
 */

"use strict";
(function ($) {
  $(document).ready(function(){
    //Find data-cyco-expand.
    $("[data-cyco-expand]").each(function(index, element){
      var $this = $(this);
      //Erase all of the MT paras.
      //A weirdness of Textile is that it adds blank paras when there
      //is HTML included.
      $this.children('p').each(function(pIndex, pElement){
        var $p = $(pElement);
        if ( $p.html() == "" ) {
          $p.remove();
        }
      });
      //First child is the title.
      var titleElement = $this.children().get(0);
      if ( titleElement ) {
        var $titleElement = $(titleElement);
        //Add a class.
        $titleElement.addClass("cyco-expand-title");
        //Wrap siblings in a div.
        $titleElement.siblings().wrapAll("<div class='cyco-expand-content' />");
        //Add a collapse thing before the title.
        $titleElement.prepend("<span class='cyco-expand-toggle'>+</span>")
      }
    });
    $(".cyco-expand-title").click(function() {
      $(this).siblings().slideToggle();
      if ( $(this).children(".cyco-expand-toggle").text() == "+") {
        $(this).children(".cyco-expand-toggle").text("-");
      }
      else {
        $(this).children(".cyco-expand-toggle").text("+");
      }
    });
  });
}(jQuery));
