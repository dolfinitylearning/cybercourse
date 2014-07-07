(function($) {
  Drupal.behaviors.ext5 = {
    attach: function(context, settings) {
      //Make sure Drupal.settings.ext5 exists.
      Drupal.settings.ext5 = Drupal.settings.ext5 || {};
      $("#t5").html( 
          "<p><button type='button' id='run-test'>Run test</button></p>"
        + this.uiTemplate() 
      );
      this.hideAjaxThrobber();
      $("#rubric-select-ui").hide();
      $("#run-test").click(  
        Drupal.behaviors.ext5.startTest
      );
    },
    uiTemplate: function() {
      //HTML for the UI.
      //The throbber code is copied from Drupal's misc/ajax.js.
      var htmlTemplate = "\
<div id='rubric-select-loading-throbber'> \
  Loading... \
  <div class='ajax-progress ajax-progress-throbber'> \
    <div class='throbber'>&nbsp;</div> \
  </div> \
</div> \
  <label id='rubric-select-ui-title'> \
    Select a rubric item to link \
  </label> \
<div id='rubric-select-ui'> \
  <div id='rubric-select-ui-row1'> \
    <div id='term-tree-container'> \
      <div id='term-tree-label'>Filter rubric items</div> \
      <div id='term-tree'/> \
    </div> \
    <div id='filtered-terms-container'> \
      <div id='filtered-terms-label'>Choose one item</div> \
      <ul id='filtered-terms'/> \
    </div> \
  </div> \
  <div id='rubric-select-ui-row2'> \
    <div id='term-tree-ui-mt-cell'> \
      &nbsp; \
    </div> \
    <div id='rubric-select-buttons-container'>\
      <button id='rubric-select-create' type='button'>Create</button> \
      <button id='rubric-select-edit' type='button'>Edit</button> \
      <button id='rubric-select-link' type='button'>Link</button> \
      <button id='rubric-select-cancel' type='button'>Cancel</button> \
    </div> \
  </div> \
</div> \
";
      return htmlTemplate;
    },
    startTest: function(){
      Drupal.behaviors.ext5.showAjaxThrobber();
      $.when(
        Drupal.behaviors.ext5.getCsrfToken()
      )
      .then(function() {
        console.log("start test OK");
        //Grab and show vocab.
        $.when( 
          Drupal.behaviors.ext5.fetchTerms(),
          Drupal.behaviors.ext5.fetchRubrics()
        )
        .then(function() {
                  console.log("loaded");
          //Grab and show vocab.
          Drupal.behaviors.ext5.prepareUi();
          Drupal.behaviors.ext5.hideAjaxThrobber();
          $("#rubric-select-ui").show();
        })
        .fail(function() {
          alert("The voles died.");
        });
      })
      .fail(function() {
        alert("The gerbils died.");
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
          Drupal.settings.ext5.token = token;
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
          request.setRequestHeader("X-CSRF-Token", Drupal.settings.ext5.token);
        },
      })
        .done(function(result) {
          Drupal.settings.ext5.termsServerData = result;
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
          request.setRequestHeader("X-CSRF-Token", Drupal.settings.ext5.token);
        },
      })
        .done(function(result) {
          Drupal.settings.ext5.rubricsServerData = result;
          console.log(result);
        })
        .fail(function(jqXHR, textStatus, errorThrown) {
          alert('getJSON request failed! ' + errorThrown);
        });
      return promise;
    },
    prepareUi: function() {
      var treeNodes = new Array();
      $(Drupal.settings.ext5.termsServerData).each(function(index, term) {
        //Make a treeNode for the term.
        var treeNode = {
          title: term.title,
          key: term.tid,
          parentId: term.parent_tid,
          expanded: true
        };
        //Put a ref to the treeNode in the server data object.
        Drupal.settings.ext5.termsServerData[index].node = treeNode;
        //Add the tree node to treeNodes.
        if ( term.parent_tid == 0 ) {
          //No parent.
          treeNodes.push( treeNode );
        }
        else {
          //The new node is a child.
          //Get ref to the parent node.
          var parentNode = null;
          for (var i = 0; i < Drupal.settings.ext5.termsServerData.length; i++) {
            if ( Drupal.settings.ext5.termsServerData[i].tid == treeNode.parentId ) {
              parentNode = Drupal.settings.ext5.termsServerData[i].node;
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
      for (i = 0; i < Drupal.settings.ext5.rubricsServerData.length; i++) {
        fi.append("<li>" + Drupal.settings.ext5.rubricsServerData[i].title + "</li>");
      }
      //Clear the server data terms array. This is the fastest way, according
      //to http://stackoverflow.com/questions/1232040/how-to-empty-an-array-in-javascript
      var A = Drupal.settings.ext5.termsServerData;
      while(A.length > 0) {
          A.pop();
      }
      var tree = $("#term-tree").fancytree({
        source: treeNodes,
        icons: false,
        checkbox: true,
        selectMode: 2
      });
    },
    showAjaxThrobber: function() {
      $("#rubric-select-loading-throbber").show();
    },
    hideAjaxThrobber: function() {
      $("#rubric-select-loading-throbber").hide();
    }
  };
}(jQuery));
