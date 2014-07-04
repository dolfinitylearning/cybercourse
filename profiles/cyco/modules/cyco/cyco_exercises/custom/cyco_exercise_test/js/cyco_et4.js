(function($) {
  Drupal.behaviors.ext4 = {
    attach: function(context, settings) {
      //Make sure Drupal.settings.ext4 exists.
      Drupal.settings.ext4 = Drupal.settings.ext4 || {};
      $("#t4").html(
  "<button type='button' id='run-test'>Run test</button>"
+ "<div id='output'>"
+ "<div id='term-tree'/>"
+ "<div id='filtered-terms-container'><ul id='filtered-terms'/></div>"
+ "</div>"
+ "<p id='activity'>Processing...</p>"
      );
      $("#activity").hide();
      $("#run-test").click(  
        Drupal.behaviors.ext4.startTest
      );
    },
    startTest: function(){
      $.when(
        Drupal.behaviors.ext4.getCsrfToken()
      )
      .then(function() {
        console.log("start test OK");
        //Grab and show vocab.
        Drupal.behaviors.ext4.loadTree();
      })
      .fail(function() {
        alert("The gerbils died.");
      });
    },
    loadTree: function() {
      $.when( 
        Drupal.behaviors.ext4.fetchTerms(),
        Drupal.behaviors.ext4.fetchRubrics()
      )
      .then(function() {
                console.log("loaded");
        //Grab and show vocab.
        Drupal.behaviors.ext4.showUi();
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
          Drupal.settings.ext4.token = token;
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
      var webServiceUrl = Drupal.settings.basePath + "exercise/rubric_item_categories/getTree";
      var promise = $.ajax({
        type: "POST",
        contentType: "application/json; charset=utf-8",
        dataType: "json", url: webServiceUrl,
        beforeSend: function (request) {
          request.setRequestHeader("X-CSRF-Token", Drupal.settings.ext4.token);
        },
      })
        .done(function(result) {
          Drupal.settings.ext4.termsServerData = result;
          console.log(result);
        })
        .fail(function(jqXHR, textStatus, errorThrown) {
          alert('getJSON request failed! ' + errorThrown);
        });
      return promise;
    },
    fetchRubrics: function() {
      console.log("Fetching rubrics");
      var webServiceUrl = Drupal.settings.basePath + "exercise/rubric_item/getTitlesCategories"
      var promise = $.ajax({
        type: "POST",
        contentType: "application/json; charset=utf-8",
        dataType: "json", 
        url: webServiceUrl,
        beforeSend: function (request) {
          request.setRequestHeader("X-CSRF-Token", Drupal.settings.ext4.token);
        },
      })
        .done(function(result) {
          Drupal.settings.ext4.rubricsServerData = result;
          console.log(result);
        })
        .fail(function(jqXHR, textStatus, errorThrown) {
          alert('getJSON request failed! ' + errorThrown);
        });
      return promise;
    },
    showUi: function() {
      var treeNodes = new Array();
      $(Drupal.settings.ext4.termsServerData).each(function(index, term) {
        //Make a treeNode for the term.
        var treeNode = {
          title: term.title,
          key: term.tid,
          parentId: term.parent_tid,
          expanded: true
        };
        //Put a ref to the treeNode in the server data object.
        Drupal.settings.ext4.termsServerData[index].node = treeNode;
        //Add the tree node to treeNodes.
        if ( term.parent_tid == 0 ) {
          //No parent.
          treeNodes.push( treeNode );
        }
        else {
          //The new node is a child.
          //Get ref to the parent node.
          var parentNode = null;
          for (var i = 0; i < Drupal.settings.ext4.termsServerData.length; i++) {
            if ( Drupal.settings.ext4.termsServerData[i].tid == treeNode.parentId ) {
              parentNode = Drupal.settings.ext4.termsServerData[i].node;
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
      //Add terms to list
      var fi = $("#filtered-terms");
      for (i = 0; i < Drupal.settings.ext4.rubricsServerData.length; i++) {
        fi.append("<li>" + Drupal.settings.ext4.rubricsServerData[i].title + "</li>");
      }
      //Clear the server data terms array. This is the fastest way, according
      //to http://stackoverflow.com/questions/1232040/how-to-empty-an-array-in-javascript
      var A = Drupal.settings.ext4.termsServerData;
      while(A.length > 0) {
          A.pop();
      }
      var tree = $("#term-tree").fancytree({
        source: treeNodes,
        icons: false,
        checkbox: true,
        selectMode: 2
      });
      $("#output").show();
    }
  };
}(jQuery));
