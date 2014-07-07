(function($) {
  Drupal.behaviors.ext1 = {
    attach: function(context, settings) {
      $("#t1").html(
  "<button type='button' id='run-test'>Run test</button>"
+ "<p id='output'>Output here</p>"
+ "<p id='activity'>Processing...</p>"
      );
      $("#activity").hide();
      $("#run-test").click(  
        Drupal.behaviors.ext1.runTest
      );
    },
    runTest: function(){
      $.when( Drupal.behaviors.ext1.getCsrfToken() ).done( function() {
        if ( Drupal.settings.ext1.token ) {
          //Grab and show vocab.
          Drupal.behaviors.ext1.fetchTerms();
        }
        else {
          alert("Problem fetching token.");
        }
      });
    },
    getCsrfToken: function(){
      //Connect and get user details.
      var deferred = $.Deferred();
      var webServiceUrl = Drupal.settings.basePath + "services/session/token";
      $("#activity").show();
      $.ajax({
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
          alert('Token request failed! ' + textStatus + errorThrown); 
        })
        .always(function() {
          $("#activity").hide();
          deferred.resolve();
        }); 
      return deferred.promise();
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
          $("#output").text(data.type);
          console.log(data);
        })
        .fail(function(jqXHR, textStatus, errorThrown) {
          alert('getJSON request failed! ' + errorThrown);
        });
    }
  };
}(jQuery));
