(function ($) {
  Drupal.behaviors.cacpl = {
    attach: function (context, settings) {
      //Build a select control
      var options = Drupal.settings.cacpl;
      var html = 
          "<form class='form-inline'><select id='cacpl-page-list' class=''>";
      for ( var i in options ) {
        html += "<option value='" + i + "'>" + options[i].description + "</option>";
      }
      html += "</select> <button id='cacpl-create' type='button' "
          + "class='btn'>Create</button><br>";
      html += "<small>Note: siblings might not add themselves in the right spot. "
          + "(You know how unreliable <em>your</em> sibs can be.) "
          + "Use the Rearrange pages link, if you need to fix mistakes.</small></form>"
      $("#cacpl-create-widget-location").append(html);
      $("#cacpl-create").click( function() {
        var selectedIndex = $("#cacpl-page-list").val();
        window.location = options[selectedIndex].link;
      });
    }
  };
}(jQuery));