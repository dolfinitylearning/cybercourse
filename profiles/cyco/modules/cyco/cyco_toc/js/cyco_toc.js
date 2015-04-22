/**
 * @file
 * Show a table of contents.
 */
(function ($) {
  Drupal.behaviors.cycoToc = {
    attach: function (context, settings) {
      var headingTagList 
          = $('.swim h1, .swim h2, .swim h3, .swim h4');
      if ( headingTagList.size() > 0 ) {
        var html = '<div id="cyco_toc">'
                    + '<p id="cyco_toc_label">Contents</p>';
        var elementCount = 0;
        headingTagList.each(function(index) {
          var elementHeading = $(this).text();
          var elementTag = this.tagName.toLowerCase();
          //Use existing id if the element has one, or create a new one.
          var idToUse;
          if ( $(this).attr('id') ) {
            idToUse = $(this).attr('id');
          } 
          else {
            idToUse = 'cyco_toc' + elementCount;
            elementCount ++;
            $(this).attr('id', idToUse);
          }
          html += '<p class="cyco_toc_' + elementTag + '"><a href="#' 
                  + idToUse + '">' + elementHeading + '</a></p>';
        }); // end each
        html += '</div>';
        //Only add the ToC to the first instance of a body.
        //Prevents extras from appearing when exercises are inserted.
        $('.field-name-field-body').before(html);
      } // end if
    }
  };
}(jQuery));



