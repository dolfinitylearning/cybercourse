(function($) {
  Drupal.behaviors.ext2 = {
    attach: function(context, settings) {
      $("#t2").html(
  "<button type='button' id='run-test'>Run test</button>"
+ "<p id='output'>Output here</p>"
+ "<p id='activity'>Processing...</p>"
      );
      $("#activity").hide();
      $("#run-test").click(  
        Drupal.behaviors.ext2.runTest
      );
    },
    runTest: function(){
      $.when( 
        Drupal.behaviors.ext2.getCsrfToken() 
      )
      .then( 
        //Grab and show vocab.
        Drupal.behaviors.ext2.fetchTerms
      )
      .fail(function() {
        alert("The gerbils died.");
      });
    },
    /**
     * Get a CSRF token.
     * @returns {unresolved} Promise.
     */
    getCsrfToken: function(){
      //Connect and get user details.
      var webServiceUrl = Drupal.settings.basePath + "services/session/token";
      $("#activity").show();
      var promise = $.ajax({ 
          type: "GET",
          url: webServiceUrl,
          dataType: "text"
      })
        .done(function(token){
          //Create Drupal.settings.ext1 if dinna exist.
          Drupal.settings.ext1 = Drupal.settings.ext1 || {};
          Drupal.settings.ext1.token = token;
        })
        .fail(function(jqXHR, textStatus, errorThrown) {
          console.log('Token request failed! ' + textStatus + errorThrown); 
        })
        .always(function() {
          $("#activity").hide();
        }); 
      return promise;
    },
    fetchTerms: function() {
      $("#output").text("Waiting...");
      var webServiceUrl = Drupal.settings.basePath + "exercise/rubric_item_categories/getTree";
      $.ajax({
        type: "POST",
        contentType: "application/json; charset=utf-8",
        dataType: "json", url: webServiceUrl,
        beforeSend: function (request) {
          request.setRequestHeader("X-CSRF-Token", Drupal.settings.ext1.token);
        },
      })
        .done(function(data) {
          $("#output").text("Done");
          console.log(data);
        })
        .fail(function(jqXHR, textStatus, errorThrown) {
          alert('getJSON request failed! ' + errorThrown);
        });
    }
  };
}(jQuery));
