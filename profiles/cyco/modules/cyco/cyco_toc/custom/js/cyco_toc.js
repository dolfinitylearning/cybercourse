(function ($) {
  Drupal.behaviors.cycoToc = {
    attach: function (context, settings) {
      var headingTagList 
          = $('.document h1, .document h2, .document h3, .document h4');
      if ( headingTagList.size() > 0 ) {
        var html = '<div id="cyco_toc">'
                    + '<p id="cyco_toc_label">Contents</p>';
        var elementCount = 0;
        headingTagList.each(function(index) {
          var elementHeading = $(this).text();
          var elementTag = this.tagName.toLowerCase();
          $(this).attr('id', 'cyco_toc' + elementCount);
          html += '<p class="cyco_toc_' + elementTag + '"><a href="#cyco_toc' 
                  + elementCount + '">' + elementHeading + '</a></p>';
          elementCount ++;
        }); // end each
        html += '</div>';
        //Only add the ToC to the first instance of a body.
        //Prevents extras from appearing when exercises are inserted.
        $('#page-title').after(html);
      } // end if
    }
  };
}(jQuery));



