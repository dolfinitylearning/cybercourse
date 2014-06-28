(function($) {


  $(document).ready(function() {
    //If no settings set, exit. Will happen when there are no
    //book blocks to show.
    if ( ! Drupal.settings.cyco_book_blocks ) {
      return;
    }
    /**
     * Move all items under the first level to the top level. 
     */
    $("ul.cyco-book-tree-menu").each(function(index, ulTopLevel){
      var firstLi = $(ulTopLevel).find("li:first");
      var liForChapters = $(firstLi).find("ul:first > li");
      $(liForChapters).each(function(i, item){
        $(ulTopLevel).append(item);
        $(item).removeClass("open-branch").addClass("close-branch").show();
      });
      $(firstLi).remove();
    });
    var parentyThings = $('.cyco-book-tree-menu').find('li:has(ul)');
    parentyThings.addClass('parent_li');
    parentyThings.find(' > span').attr('title', 'Expand this branch');
    $('.cyco-book-tree-menu')
        .on('click', 'li:has(ul) > span', function(e) { 
          var $this = $(e.currentTarget);
          $this.bookBlockMenuClicked( $this ); 
          e.stopPropagation();
        } );
    
    $.fn.bookBlockMenuClicked = function( $this ) {
      if ( ! $this ) {
        $this = $(this);
      }
      var children = $this.parent('li.parent_li').find(' > ul > li');
      if ( $this.hasClass('open-branch') ) {
        $this.removeClass('open-branch').addClass('close-branch');
        children.show('fast');// $.bccMenuAnimation );
        $this.attr('title', 'Collapse this branch');
      }
      else {
        $this.removeClass('close-branch').addClass('open-branch');
        children.hide('fast');// $.bccMenuAnimation );
        $this.attr('title', 'Expand this branch');
      }

    };
    
    //Find the menu item that is the link to the current page.
    var currentPagePath = 
         Drupal.settings.cyco_book_blocks.current_path;
    var active = $(".cyco-book-tree-menu li a[href$='" + currentPagePath + "']");
    if ( active.length > 0 ) {
      active = active.closest("li");
      active.addClass("currentPage");
      var reachedMenuTop = false;
      var foundParent = false;
      while ( ! reachedMenuTop ) {
        foundParent = false;
        while ( ! foundParent ) {
          active = active.parent();
          foundParent = ( active.hasClass("menu-top") || active.hasClass("parent_li"));
        }
        if ( active.hasClass("menu-top") ) {
          reachedMenuTop = true;
        }
        else {
          active = active.children("span");
          active.addClass("active-path");
          active = active.closest("li.parent_li");
        }
      }
      //Expand all the menu items on the active path.
      $(".cyco-book-tree-menu .active-path").each(function(){
        $(this).bookBlockMenuClicked();
      });
    }
  });

}(jQuery));
