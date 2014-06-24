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
      html += "<small>Children are added after existing children.  "
          + "Use \"Rearrange pages\" as needed.</small></form>"
      $("#cacpl-create-widget-location").append(html);
      $("#cacpl-create").click( function() {
        var selectedIndex = $("#cacpl-page-list").val();
        window.location = options[selectedIndex].link;
      });
    }
  };
}(jQuery));