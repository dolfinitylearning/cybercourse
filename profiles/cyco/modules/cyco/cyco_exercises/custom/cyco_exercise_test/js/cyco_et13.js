(function($) {
  Drupal.behaviors.ext13 = {
    attach: function(context, settings) {
      this.hideAjaxThrobber();
      $("#test").click(  
        Drupal.behaviors.ext13.startTest
      );
    },
    startTest: function(){
      Drupal.behaviors.ext13.showAjaxThrobber();
      $.when(
        Drupal.behaviors.ext13.getCsrfToken()
      )
      .then(function() {
        console.log("start test OK");
        $.when( 
          Drupal.behaviors.ext13.testFetch()
        )
        .then(function( result ) {
          console.log("Result: ", result);
          $("#solution").html( result.rendered);
          Drupal.behaviors.ext13.hideAjaxThrobber();
        })
        .fail(function() {
          alert("The fetch test died.");
        });
      })
      .fail(function() {
        alert("The CSRF died.");
      });
    },
    /**
     * Get a CSRF token.
     * @returns {unresolved} Promise.
     */
    getCsrfToken: function(){
      console.log("Getting token");
      //Connect and get user details.
      var webServiceUrl = Drupal.settings.basePath + "services/session/token";
      $("#activity").show();
      var promise = $.ajax({ 
          type: "GET",
          url: webServiceUrl,
          dataType: "text"
      })
        .done(function(token){
          Drupal.behaviors.ext13.token = token;
          return token;
        })
        .fail(function(jqXHR, textStatus, errorThrown) {
          console.log('Token request failed! ' + textStatus + errorThrown); 
        })
        .always(function() {
          $("#activity").hide();
        }); 
      return promise;
    },
    testFetch: function() {
      var webServiceUrl = Drupal.settings.basePath 
              + "exercise/submission/getSubmissionRendered";
      var dataToSend = {};
      dataToSend.sub_nid = $("#subNid").val();
      dataToSend = JSON.stringify( dataToSend );
      var promise = $.ajax({
        type: "POST",
        contentType: "application/json; charset=utf-8",
        dataType: "json",
        data: dataToSend,
        url: webServiceUrl,
        beforeSend: function (request) {
          request.setRequestHeader("X-CSRF-Token", Drupal.behaviors.ext13.token);
        }
      })
        .done(function(result) {
          console.log("result: ", result);
        })
        .fail(function(jqXHR, textStatus, errorThrown) {
          alert('test fetch request failed! ' + errorThrown);
        });
      return promise;
    },
    showAjaxThrobber: function() {
      $("#loading").show();
    },
    hideAjaxThrobber: function() {
      $("#loading").hide();
    },
  };
}(jQuery));
