(function($) {
  Drupal.behaviors.ext7 = {
    //Id of the selected rubric item.
    selectedItemNid: null,
    //Term ids the user has checked in the tree.
    checkedTermIds: new Array(),
    //Nids of the rubric items shown in the filtered list.
    filteredNids: new Array(),
    //CSS class attached to selected item.
    selectedItemClass: "rubric-select-selected-item",
    attach: function(context, settings) {
      this.hideAjaxThrobber();
      $("#rubric-select-ui").hide();
      $("#test").click(  
        Drupal.behaviors.ext7.startTest
      );
    },
    startTest: function(){
      Drupal.behaviors.ext7.showAjaxThrobber();
      $.when(
        Drupal.behaviors.ext7.getCsrfToken()
      )
      .then(function() {
        console.log("start test OK");
        
        //Grab and show vocab.
        $.when( 
          Drupal.behaviors.ext7.testTitle()
        )
        .then(function( result ) {
          console.log("Result: ", result);
          Drupal.behaviors.ext7.hideAjaxThrobber();
        })
        .fail(function() {
          alert("The title test died.");
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
          Drupal.behaviors.ext7.token = token;
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
    testTitle: function() {
      var nid = $("#nid").val();
      var title = $("#title").val();
      var webServiceUrl = Drupal.settings.basePath + "exercise/rubric_item/chkTtl";
      var dataToSend = {};
      dataToSend.nid = nid;
      dataToSend.title = title;
      dataToSend = JSON.stringify( dataToSend );
      var promise = $.ajax({
        type: "POST",
        contentType: "application/json; charset=utf-8",
        dataType: "json",
        data: dataToSend,
        url: webServiceUrl,
        beforeSend: function (request) {
          request.setRequestHeader("X-CSRF-Token", Drupal.behaviors.ext7.token);
        }
      })
        .done(function(result) {
          console.log("result: ", result);
        })
        .fail(function(jqXHR, textStatus, errorThrown) {
          alert('test title request failed! ' + errorThrown);
        });
      return promise;
    },

    showAjaxThrobber: function() {
      $("#rubric-select-loading-throbber").show();
    },
    hideAjaxThrobber: function() {
      $("#rubric-select-loading-throbber").hide();
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
