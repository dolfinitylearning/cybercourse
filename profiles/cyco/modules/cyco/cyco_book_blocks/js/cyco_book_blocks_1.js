(function($) {


  $(document).ready(function() {
    
    /**
     * Move all items under the first level to the top level. 
     */
    $("ul.cyco-book-tree-menu").each(function(index, ulTopLevel){
      var firstLi = $(ulTopLevel).find("li:first");
      var liForChapters = $(firstLi).find("ul:first > li");
      $(liForChapters).each(function(i, item){
        $(ulTopLevel).append(item);
        $(item).removeClass("closed-branch").addClass("opened-branch").show();
      });
      $(firstLi).remove();
    });
    
    $('.cyco-book-tree-menu > ul').attr('role', 'cycoBookBlock').find('ul').attr('role', 'group');
    $('.cyco-book-tree-menu').find('li:has(ul)').addClass('parent_li').attr('role', 'treeitem')
        .find(' > span').attr('title', 'Collapse this branch').on('click',
           function(e) { 
             var $this = $(e.currentTarget);
             $this.bookBlockMenuClicked( $this ); 
             e.stopPropagation();
           } );
    
    //Animation to show. None to start with.
    //$.bccMenuAnimation = '';
    
    $.fn.bookBlockMenuClicked = function( $this ) {
      if ( ! $this ) {
        $this = $(this);
      }
      var children = $this.parent('li.parent_li').find(' > ul > li');
      if ( children.hasClass('opened-branch') ) {
        children.removeClass('opened-branch').addClass('closed-branch');
        children.hide();// $.bccMenuAnimation );
        $this.attr('title', 'Expand this branch');
      }
      else {
        children.removeClass('closed-branch').addClass('opened-branch');
        children.show();// $.bccMenuAnimation );
        $this.attr('title', 'Collapse this branch');
      }
    };
    
    //Find the menu item that is the link to the current page.
    var currentPagePath = 
//          Drupal.settings.cyco_book_blocks.base_url
//        + Drupal.settings.basePath
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
          foundParent = ( active.hasClass("menuTop") || active.hasClass("parent_li"));
        }
        if ( active.hasClass("menuTop") ) {
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
      //Animations from now on.
      $.bccMenuAnimation = ''; //'fast';
    }
  });

}(jQuery));
