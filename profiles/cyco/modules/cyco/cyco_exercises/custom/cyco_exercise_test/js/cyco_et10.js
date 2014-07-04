(function($) {
  Drupal.behaviors.ext10 = {
    attach: function(context, settings) {
      this.hideAjaxThrobber();
      $("#test").click(  
        Drupal.behaviors.ext10.startTest
      );
    },
    startTest: function(){
      Drupal.behaviors.ext10.showAjaxThrobber();
      $.when(
        Drupal.behaviors.ext10.getCsrfToken()
      )
      .then(function() {
        console.log("start test OK");
        $.when( 
          Drupal.behaviors.ext10.testFetch()
        )
        .then(function( result ) {
          console.log("Result: ", result);
          Drupal.behaviors.ext10.hideAjaxThrobber();
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
          Drupal.behaviors.ext10.token = token;
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
      var studentUid = $("#student").val();
      var exerNid = $("#exercise").val();
      var webServiceUrl = Drupal.settings.basePath 
              + "exercise/submission/getSubmissionMetaStudentExer";
      var dataToSend = {};
      dataToSend.student = studentUid;
      dataToSend.exercise = exerNid;
      dataToSend = JSON.stringify( dataToSend );
      var promise = $.ajax({
        type: "POST",
        contentType: "application/json; charset=utf-8",
        dataType: "json",
        data: dataToSend,
        url: webServiceUrl,
        beforeSend: function (request) {
          request.setRequestHeader("X-CSRF-Token", Drupal.behaviors.ext10.token);
        }
      })
        .done(function(result) {
          console.log("result: ", result);
          window.result = result;
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
    eraseArray: function(A) {
      //Remove array from memory. This is the fastest way, according
      //to http://stackoverflow.com/questions/1232040/how-to-empty-an-array-in-javascript
      while(A.length > 0) {
          A.pop();
      }      
    }
  };
}(jQuery));
