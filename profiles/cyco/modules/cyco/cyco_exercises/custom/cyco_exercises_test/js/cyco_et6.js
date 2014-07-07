(function($) {
  Drupal.behaviors.ext6 = {
    //Id of the selected rubric item.
    selectedItemNid: null,
    //Term ids the user has checked in the tree.
    checkedTermIds: new Array(),
    //Nids of the rubric items shown in the filtered list.
    filteredNids: new Array(),
    //CSS class attached to selected item.
    selectedItemClass: "rubric-select-selected-item",
    attach: function(context, settings) {
      $("#t6").html( 
          "<p><button type='button' id='run-test'>Run test</button></p>"
      );
      this.hideAjaxThrobber();
      $("#rubric-select-ui").hide();
      $("#run-test").click(  
        Drupal.behaviors.ext6.startTest
      );
    },
    startTest: function(){
      Drupal.behaviors.ext6.showAjaxThrobber();
      $.when(
        Drupal.behaviors.ext6.getCsrfToken()
      )
      .then(function() {
        console.log("start test OK");
        //Grab and show vocab.
        $.when( 
          Drupal.behaviors.ext6.fetchTerms(),
          Drupal.behaviors.ext6.fetchRubrics()
        )
        .then(function() {
                  console.log("loaded");
          //Grab and show vocab.
          Drupal.behaviors.ext6.prepareUi();
          Drupal.behaviors.ext6.hideAjaxThrobber();
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
          Drupal.behaviors.ext6.token = token;
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
          request.setRequestHeader("X-CSRF-Token", Drupal.behaviors.ext6.token);
        },
      })
        .done(function(result) {
          Drupal.behaviors.ext6.termsServerData = result;
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
          request.setRequestHeader("X-CSRF-Token", Drupal.behaviors.ext6.token);
        },
      })
        .done(function(result) {
          Drupal.behaviors.ext6.rubricsServerData = result;
          console.log(result);
        })
        .fail(function(jqXHR, textStatus, errorThrown) {
          alert('getJSON request failed! ' + errorThrown);
        });
      return promise;
    },
    prepareUi: function() {
      var treeNodes = new Array();
      $(Drupal.behaviors.ext6.termsServerData).each(function(index, term) {
        //Make a treeNode for the term.
        var treeNode = {
          title: term.title,
          key: term.tid,
          parentId: term.parent_tid,
          expanded: true
        };
        //Put a ref to the treeNode in the server data object.
        Drupal.behaviors.ext6.termsServerData[index].node = treeNode;
        //Add the tree node to treeNodes.
        if ( term.parent_tid == 0 ) {
          //No parent.
          treeNodes.push( treeNode );
        }
        else {
          //The new node is a child.
          //Get ref to the parent node.
          var parentNode = null;
          for (var i = 0; i < Drupal.behaviors.ext6.termsServerData.length; i++) {
            if ( Drupal.behaviors.ext6.termsServerData[i].tid == treeNode.parentId ) {
              parentNode = Drupal.behaviors.ext6.termsServerData[i].node;
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
      var nid;
      for (i = 0; i < Drupal.behaviors.ext6.rubricsServerData.length; i++) {
        nid = Drupal.behaviors.ext6.rubricsServerData[i].nid;
        fi.append("<li data-nid='" + nid + "'>" + Drupal.behaviors.ext6.rubricsServerData[i].title + "</li>");
        //Remember that this item is in the filtered list.
        this.filteredNids.push( nid );
      }
      $("#filtered-terms").click( this.rubricItemSelected );
      var tree = $("#term-tree").fancytree({
        source: treeNodes,
        icons: false,
        checkbox: true,
        selectMode: 2,
        select: this.termSelected,
        beforeActivate: function(event, treeData) {
          //Trigger selected instead.
          treeData.node.toggleSelected();
          return false;
        },
      });
      //Buttons states
      $("#rubric-select-edit").attr("disabled", "disabled");
      $("#rubric-select-link").attr("disabled", "disabled");
    },
    termSelected: function( event, treeData ) {
//      try {
        document.body.style.cursor = 'wait';
        var selNodes = treeData.tree.getSelectedNodes();
        //Shortcut to sav typing.
        var uiNamespace = Drupal.behaviors.ext6;
        //Replace existing array of checked term ids.
        uiNamespace.checkedTermIds = new Array();
        $(selNodes).each( function(index, node) {
          uiNamespace.checkedTermIds.push( node.key );
  //        console.log( node.key + " " + node.title );
        });
        console.log(uiNamespace.checkedTermIds);
        //Filter rubric items with those terms.
        uiNamespace.filteredNids = new Array();
        var itemCategories; //Categories (tids) for an item.
        var itemCategory; //A particular category, member of itemCategories.
        var itemMatched; //True if the item should be added to the filtered list.
        $(uiNamespace.rubricsServerData).each(function(index, rubricItem){
          console.log(rubricItem);
          if ( rubricItem.categories ) {
            //There are categories for the current item.
            itemMatched = false;
            itemCategories = rubricItem.categories;
            //Loop over categories of current item, and see if one is checked.
            for ( var i = 0; i < itemCategories.length; i++ ) {
              itemCategory = itemCategories[i];
              if ( uiNamespace.checkedTermIds.indexOf( itemCategory ) != -1 ) {
                //Found it. Add this item to the filtered list.
                itemMatched = true;
                break;
              }
            }
            if ( itemMatched ) {
              console.log("match");
              uiNamespace.filteredNids.push( rubricItem.nid );
            }
          } //End there are categories for current item.
        });
        //If an item has been selected, add it to the filtered items.
        if ( uiNamespace.selectedItemNid ) {
          var selectedItem = uiNamespace.selectedItemNid;
          //Check whether the item is already in the list.
          if ( uiNamespace.filteredNids.indexOf( selectedItem ) == -1 ) {
            uiNamespace.filteredNids.push( selectedItem );
          }
        } //End there is a selected item.
        //Update the filtered item list.
        var fi = $("#filtered-terms");
        $("#filtered-terms li").remove(); //Erase existing items.
        var nid;
        var rubricItem;
        var extraAttributes;
        //Loop over the nids.
        for (i = 0; i < uiNamespace.filteredNids.length; i++) {
          nid = uiNamespace.filteredNids[i];
          //Get the rubric item for this nid.
          rubricItem = Drupal.behaviors.ext6.findRubricItem( nid );
          //Is it the selected one?
          extraAttributes = ( nid == uiNamespace.selectedItemNid ) 
              ? " class='" + uiNamespace.selectedItemClass + "' " : "";
          fi.append("<li data-nid='" + nid + "' " + extraAttributes + " >" 
              + rubricItem.title + "</li>");
        } //End loop over this.filteredNids.
//      }
//      catch (e) {
//        var message = "Error! " + e.message 
//            + "\nFile: " + e.fileName + "\nLine: " + e.lineNumber
//            + "\n\nPlease take a screen shot, and send it to the CyCo people.";
//        console.log( message );
//        alert( message );
//      }
//      finally {
        document.body.style.cursor = 'default';
//      }
    },
    rubricItemSelected: function( event ) {
      var clickedItem = event.target;
      var clickedNid = parseInt( $(clickedItem).attr("data-nid") );
      //Remove existing highlight.
      $("." + Drupal.behaviors.ext6.selectedItemClass )
        .removeClass(Drupal.behaviors.ext6.selectedItemClass)
      //Save nid of selected item.
      Drupal.behaviors.ext6.selectedItemNid = clickedNid;
      //Add highlight class.
      $(clickedItem).addClass(Drupal.behaviors.ext6.selectedItemClass);
      //Enable buttons.
      $("#rubric-select-edit").removeAttr("disabled");
      $("#rubric-select-link").removeAttr("disabled");
    },
    /**
     * Find data from server for a rubric item with a gives nid. 
     * @param {integer} nidToFind
     * @returns The rubric item's data, or null if not found.
     */
    findRubricItem: function( nidToFind ) {
      var rubricItem;
      var nid;
      for (var i = 0; i < Drupal.behaviors.ext6.rubricsServerData.length; i++) {
        rubricItem = Drupal.behaviors.ext6.rubricsServerData[i];
        nid = rubricItem.nid;
        if ( nid == nidToFind ) {
          return rubricItem;
        }
      }
      return null;
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
