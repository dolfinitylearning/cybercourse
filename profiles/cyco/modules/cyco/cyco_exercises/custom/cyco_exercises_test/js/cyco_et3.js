(function($) {
  Drupal.behaviors.ext3 = {
    attach: function(context, settings) {
      //Make sure Drupal.settings.ext3 exists.
      Drupal.settings.ext3 = Drupal.settings.ext3 || {};
      $("#t3").html(
  "<button type='button' id='run-test'>Run test</button>"
+ "<p id='output'>Output here</p>"
+ "<p id='activity'>Processing...</p>"
      );
      $("#activity").hide();
      $("#run-test").click(  
        Drupal.behaviors.ext3.startTest
      );
    },
    startTest: function(){
      $.when(
        Drupal.behaviors.ext3.getCsrfToken()
      )
      .then(function() {
        console.log("start test OK");
        //Grab and show vocab.
        Drupal.behaviors.ext3.loadTree();
      })
      .fail(function() {
        alert("The gerbils died.");
      });
    },
    loadTree: function() {
      $.when( 
        Drupal.behaviors.ext3.fetchTerms()
      )
      .then(function() {
                console.log("loaded");
        //Grab and show vocab.
        Drupal.behaviors.ext3.showTree();
      })
      .fail(function() {
        alert("The voles died.");
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
          Drupal.settings.ext3.token = token;
                console.log("Token: " + token);
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
      console.log("Fetching terms");
      $("#output").text("Waiting...");
      var webServiceUrl = Drupal.settings.basePath + "exercise/rubric_item_categories/getTree";
      var promise = $.ajax({
        type: "POST",
        contentType: "application/json; charset=utf-8",
        dataType: "json", url: webServiceUrl,
        beforeSend: function (request) {
          request.setRequestHeader("X-CSRF-Token", Drupal.settings.ext3.token);
        },
      })
        .done(function(result) {
          Drupal.settings.ext3.termsServerData = result;
          console.log(result);
        })
        .fail(function(jqXHR, textStatus, errorThrown) {
          alert('getJSON request failed! ' + errorThrown);
        });
      return promise;
    },
    showTree: function() {
      var treeNodes = new Array();
      $(Drupal.settings.ext3.termsServerData).each(function(index, term) {
        //Make a treeNode for the term.
        var treeNode = {
          title: term.title,
          key: term.tid,
          parentId: term.parent_tid
        };
        //Put a ref to the treeNode in the server data object.
        Drupal.settings.ext3.termsServerData[index].node = treeNode;
        //Add the tree node to treeNodes.
        if ( term.parent_tid == 0 ) {
          //No parent.
          treeNodes.push( treeNode );
        }
        else {
          //The new node is a child.
          //Get ref to the parent node.
          var parentNode = null;
          for (var i = 0; i < Drupal.settings.ext3.termsServerData.length; i++) {
            if ( Drupal.settings.ext3.termsServerData[i].tid == treeNode.parentId ) {
              parentNode = Drupal.settings.ext3.termsServerData[i].node;
              break;
            }
          }
          if ( parentNode === null ) {
            alert('blagh!');
            return;
          }
          //Make sure the parent node has a children property.
          parentNode.children = parentNode.children || new Array();
          //Add the new node to the parent's children collection.
          parentNode.children.push( treeNode );
        }
      }); //End each
      //Clear the server data array. This is the fastest way, according
      //to http://stackoverflow.com/questions/1232040/how-to-empty-an-array-in-javascript
      var A = Drupal.settings.ext3.termsServerData;
      while(A.length > 0) {
          A.pop();
      }      
      var tree = $("#output").fancytree({
        source: treeNodes,
        icons: false,
        checkbox: true,
        selectMode: 2
      });
    }
  };
}(jQuery));
