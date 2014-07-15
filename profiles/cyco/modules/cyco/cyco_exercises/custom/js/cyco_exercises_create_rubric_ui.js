(function($) {
  "use strict";
  var uiNamespace; //Convenient ref to a namespacey thing.
  Drupal.behaviors.cycoCreateRubricUi = {
    //**** Data describing a rubric item.
    RubricItem: function() {
      this.nid = 0;
      this.title = "";
      this.termsChecked = new Array();
      this.notes = new Array();
      this.phrasesGood = new Array();
      this.phrasesNeedsWork = new Array();
      this.phrasesPoor = new Array();
    },
    //**** Data about the UI's state.
    //The user has changed something. Used during save and cancel.
    changed: false,
    //HTML template for a phrase.
    phraseTemplate: "",
    //The categories tree.
    tree: null,
    //Text to show in a phrase field that is MT.
    mtPhraseText: "Type new phrase",
    //Flag - warn the user that item title is already in use.
    warnDuplicateTitle: false,
    attach: function(context, settings) {
      //Nothing to do
    },
    //Does not use attach. startMeUp is called by the select interface 
    //one it has done its work.
    startMeUp: function() {
      uiNamespace = Drupal.behaviors.cycoCreateRubricUi;
      uiNamespace.createUi();
    },
    /**
     * Prepare the UI.
     */
    createUi: function() {
      uiNamespace.hideSaveThrobber();
      //Hide the templates for the interfaces that Drupal added to the page.
      $("#rubric-create-ui").hide();
      $(".rubric-create-phrase-container").hide();
      //Grab the template for phrases.
      uiNamespace.phraseTemplate = 
          $(".rubric-create-phrase-container").remove();
      //Get the tree node data from the link items UI.
      var treeNodes = Drupal.behaviors.cycoSelectRubricUi.treeNodes;
      //Set up the categories tree.
      uiNamespace.createTreeDisplay( treeNodes );
      //Set up the buttons.
      uiNamespace.setupAddItemUiButtons();
      //Set up keypress processing for phrases and other things.
      uiNamespace.setupKeypress();
      //Set up the dialog.
      $("#rubric-create-ui").dialog({
          modal: true,
          autoOpen: false,
          title: "Rubric item",
          resizable: true,
          width: 700
      });
    },
    /*
     * Create the term tree display from the data structure.
     * @param Array treeNodes Data structure, tree of terms.
     */
    createTreeDisplay: function( treeNodes ) {
      //Create the tree display object.
      uiNamespace.tree = $("#rubric-create-categories").fancytree({
        source: treeNodes,
        icons: false,
        checkbox: true,
        selectMode: 2,
        beforeActivate: function(event, treeData) {
          //Trigger selected instead.
          treeData.node.toggleSelected();
          return false;
        },
        select: function(event, treeData) {
          uiNamespace.dataHasChanged( true );
        }
      });
    },
    /*
     * Track data changed state.
     * @param boolean changed Whether the data has changed.
     */
    dataHasChanged: function( changed ) {
      uiNamespace.changed = changed;
      //Is Save button available?
      if ( changed ) {
        $("#rubric-create-save").removeAttr("disabled");
      }
      else {
        $("#rubric-create-save").attr("disabled", "disabled");
      }
    },
    /*
     * Set up the buttons in the bottom right of the add item UI.
     */
    setupAddItemUiButtons: function() {
      //Handler for the save button.
      $("#rubric-create-save").click(function() {
        uiNamespace.saveItem();
      });
      //Handler for the cancel button.
      $("#rubric-create-cancel").click(function() {
        //Confirm that user wants to lose changes.
        if ( uiNamespace.changed ) {
          if ( ! confirm("Do you want to lose your changes?") ) {
            return;
          }
        }
        //Hide the create item UI.
        $("#rubric-create-ui").dialog("close");
      });
      //Click on a button for a phrase.
      $("#rubric-create-phrases-container").click(function(event) {
        //Was a button clicked on?
        var $target = $(event.target);
        if ( $target.prop("tagName") == "BUTTON" ) {
          //User clicked on a button.
          var caption = $target.text();
          if ( caption == "X" ) {
            //User clicked on remove button.
            //Find container - depends on a specific DOM relationship.
            var container = $target.parent().parent();
            if ( ! container.hasClass("rubric-create-phrase-container") ) {
              alert("Evil detected!");
              return;
            }
            container.remove();
            //Track that data has changed.
            uiNamespace.dataHasChanged( true );
          }// End X clicked.
          else if ( caption == "+" ) {
            //User clicked on add phrase button.
            //Create a new container.
            var newPhraseContainer = uiNamespace.createPhraseContainer("");
            //Add it to the DOM.
            $target.parent().prev().append(newPhraseContainer);
            newPhraseContainer.show("fast");
            //Flag to show changes made.
            uiNamespace.changed = true;
          }// End + clicked.
        }
      });
    },
    /*
     * Set up processing of keypresses in phrase fields.
     */
    setupKeypress: function() {
      $("#rubric-create-phrases-container").keypress( function(event) {
        uiNamespace.changedPhrase(event);
      });
      $("#rubric-create-title").keypress( function(event) {
        uiNamespace.changedPhrase(event);
      });
      $("#rubric-create-notes").keypress( function(event) {
        uiNamespace.changedPhrase(event);
      });
    },
    /*
     * Set up processing of paste in phrase fields.
     */
    setupPhrasePaste: function() {
      $("#rubric-create-phrases-container").on("paste", function(event) {
        uiNamespace.changedPhrase(event);
      });
    },
    changedPhrase: function(event) {
        //Was an input field involved?
        var $target = $(event.target);
        if ( $target.prop("tagName") == "INPUT" ) {
          //Remember that the data has changed
          uiNamespace.dataHasChanged(true);
        }
    },
    //Save the item.
    saveItem: function() {
      //Validate the title.
      var title = $("#rubric-create-title").val().trim();
      if ( title.length === 0 ) {
        alert("Sorry, you must give the rubric a title.");
        $("#rubric-create-title").focus();
        return false;
      }
      //Make sure the title is not already in use.
      uiNamespace.showSaveThrobber();
      $.when( 
        uiNamespace.checkTitle( 
          uiNamespace.item.nid ? uiNamespace.item.nid : 0, //0 for new item.
          title
        )
      )
      .then(function() {
        if ( uiNamespace.warnDuplicateTitle ) {
          var message = "There is already a rubric item with that title.\n\n"
            + "Are you sure you want to create a new item with the same title?";
          if ( ! confirm( message ) ) {
            return false;
          }
        }
        //Package widget contents into object to send.
        uiNamespace.item = uiNamespace.packageWidgetDataIntoItemObject();
        //Save to server.
        $.when(
          uiNamespace.sendItemToServer( uiNamespace.item )
        )
        .then(function() {
          //Tell selection client to update itself.
          Drupal.behaviors.cycoSelectRubricUi.returnFromAddItemUi( uiNamespace.item );
          //Hide the create/edit item UI.
          $("#rubric-create-ui").dialog("close");
        })
        .fail(function() {
          Drupal.behaviors.cycoErrorHandler.reportError(
            "Save failed in saveItem in "
              + "cyco_exercises_create_rubric_ui.js. " 
              + "textStatus: " + textStatus + ", errorThrown: " + errorThrown
          );
        })
        .always(function(){
          uiNamespace.hideSaveThrobber();
        });
      })//End then().
      .fail(function() {
        Drupal.behaviors.cycoErrorHandler.reportError(
          "Fetch item data failed in saveItem in "
            + "cyco_exercises_create_rubric_ui. " 
            + "textStatus: " + textStatus + ", errorThrown: " + errorThrown
        );
      });
    },
    /*
     * Show the display for creating/editing/viewing rubric items.
     * @param int itemNid The nid of the item to edit. 0 to create new one.
     */
    showCreateItemUi: function( itemNid ) {
      //Show user has made no changes yet.
      uiNamespace.dataHasChanged( false );
      if ( itemNid == 0 ) {
        uiNamespace.item = new uiNamespace.RubricItem();
        uiNamespace.item.nid = 0;
        uiNamespace.clearUi();
        uiNamespace.displayUi();
      }
      else {
        //Grab vocab terms and rubric items from server.
        uiNamespace.showSaveThrobber();
        $.when( 
          uiNamespace.fetchItemData( itemNid )
        )
        .then(function() {
          //Load the fetched data into UI.
          uiNamespace.fillUiWidgets();
          uiNamespace.hideSaveThrobber();
          //Show the UI.
          uiNamespace.displayUi();
        })
        .fail(function() {
          Drupal.behaviors.cycoErrorHandler.reportError(
            "Fetch item data failed in showCreateItemUi in "
              + "cyco_exercises_create_rubric_ui. " 
              + "textStatus: " + textStatus + ", errorThrown: " + errorThrown
          );
        })
        .always(function() {
          uiNamespace.hideSaveThrobber();
        });
      }
    },
    /**
     * Empty the UI's widgets in preparation for a new item.
     */
    clearUi: function() {
      //Create an MT item.
      uiNamespace.item = new uiNamespace.RubricItem();
      //Clear the item title widget.
      $("#rubric-create-title").val("");
      //Clear the checked values from the category tree.
      var selNodes = uiNamespace.tree.fancytree("getTree").getSelectedNodes();
      $(selNodes).each( function(index, node) {
        node.setSelected(false);
      });
      //Clear the notes widget.
      $("#rubric-create-notes").val("");
      //Set up new phrase widgets.
      uiNamespace.mtPhraseContainer( $("#rubric-create-phrases-good-list") );
      uiNamespace.mtPhraseContainer( $("#rubric-create-phrases-needs-work-list") );
      uiNamespace.mtPhraseContainer( $("#rubric-create-phrases-poor-list") );
      
    },
    mtPhraseContainer: function( container ) {
      container.empty();
      //Create a new container.
      var newPhraseContainer = uiNamespace.createPhraseContainer("");
      //Add it to the DOM.
      container.append(newPhraseContainer);
      newPhraseContainer.show("fast");
    },
    /*
     * Create a new phrase container.
     * @param string phrase Phrase for container, MT for new phrase.
     * @returns Phrase container.
     */
    createPhraseContainer: function( phrase ) {
      //Clone the phrase template.
      var phraseContainer = $(uiNamespace.phraseTemplate).clone();
      //Insert phrase text, if any.
      if ( phrase ) {
        phraseContainer.find("input").val( phrase );
      }
      return phraseContainer;
    },
    /*
     * Fetch item data from the server.
     */
    fetchItemData: function( itemNid ) {
      var webServiceUrl = Drupal.settings.basePath 
              + "exercise/rubric_item/" + itemNid;
      var promise = $.ajax({
        type: "GET",
        contentType: "application/json; charset=utf-8",
        dataType: "json", 
        url: webServiceUrl,
        beforeSend: function (request) {
          request.setRequestHeader("X-CSRF-Token", 
            Drupal.behaviors.cycoSelectRubricUi.token);
        }
      })
        .done(function(result) {
          uiNamespace.item = result;
        })
        .fail(function(jqXHR, textStatus, errorThrown) {
          Drupal.behaviors.cycoErrorHandler.reportError(
            "Fetch item data failed in fetchItemData in "
              + "cyco_exercises_create_rubric_ui. " 
              + "textStatus: " + textStatus + ", errorThrown: " + errorThrown
          );
        });
      return promise;
    },
    /*
     * Load the UI's widgets in preparation for editing.
     */
    fillUiWidgets: function() {
      //Title widget.
      $("#rubric-create-title").val( uiNamespace.item.title );
      //Term tree widget.
      var i, tid, treeNode;
      var fancyTree = uiNamespace.tree.fancytree("getTree");
      for ( i = 0; i < uiNamespace.item.termsChecked.length; i++ ) {
        tid = parseInt( uiNamespace.item.termsChecked[i] );
        treeNode = fancyTree.getNodeByKey( tid );
        treeNode.setSelected();
      }
      //Notes widget.
      $("#rubric-create-notes").val( uiNamespace.item.notes );
      //Phrases.
      var phrase, phraseContainer;
      //Good phrases.
      $("#rubric-create-phrases-good-list").empty();
      for ( i = 0; i < uiNamespace.item.phrasesGood.length; i++ ) {
        phrase = uiNamespace.item.phrasesGood[i];
        phraseContainer = uiNamespace.createPhraseContainer( phrase );
        $("#rubric-create-phrases-good-list").append( phraseContainer );
        phraseContainer.show();
      }
      //Needs work phrases.
      $("#rubric-create-phrases-needs-work-list").empty();
      for ( i = 0; i < uiNamespace.item.phrasesNeedsWork.length; i++ ) {
        phrase = uiNamespace.item.phrasesNeedsWork[i];
        phraseContainer = uiNamespace.createPhraseContainer( phrase );
        $("#rubric-create-phrases-needs-work-list").append( phraseContainer );
        phraseContainer.show();
      }
      //Poor phrases.
      $("#rubric-create-phrases-poor-list").empty();
      for ( i = 0; i < uiNamespace.item.phrasesPoor.length; i++ ) {
        phrase = uiNamespace.item.phrasesPoor[i];
        phraseContainer = uiNamespace.createPhraseContainer( phrase );
        $("#rubric-create-phrases-poor-list").append( phraseContainer );
        phraseContainer.show();
      }
    },
    /*
     * Show the UI
     */
    displayUi: function() {
      $("#rubric-create-ui").dialog("open");
    },
    /*
     * Call the server to check whether the title is already being
     * used by an item.
     * @param int nid Item nid.
     * @param string title Item title.
     */
    checkTitle: function ( nid, title ) {
      var webServiceUrl = Drupal.settings.basePath 
              + "exercise/rubric_item/chkTtl";
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
          request.setRequestHeader("X-CSRF-Token", 
            Drupal.behaviors.cycoSelectRubricUi.token);
        }
      })
        .done(function(result) {
          //Store warning flag
          uiNamespace.warnDuplicateTitle = result.warn;
        })
        .fail(function(jqXHR, textStatus, errorThrown) {
          Drupal.behaviors.cycoErrorHandler.reportError(
            "Fail in checkTitle in "
              + "cyco_exercises_create_rubric_ui. " 
              + "textStatus: " + textStatus + ", errorThrown: " + errorThrown
          );
        });
      return promise;
    },
    /*
     * Package the widget data into a RubricItem object. 
     * @returns {undefined}
     */
    packageWidgetDataIntoItemObject: function() {
      var item = new uiNamespace.RubricItem();
      item.nid = uiNamespace.item.nid;
      item.title = $("#rubric-create-title").val();
      item.termsChecked = uiNamespace.findCheckedTerms();
      item.notes = $("#rubric-create-notes").val();
      item.phrasesGood = uiNamespace.getPhrases("good");
      item.phrasesNeedsWork = uiNamespace.getPhrases("needs-work");
      item.phrasesPoor = uiNamespace.getPhrases("poor");
      return item;
    },
    /*
     * Get all the phrases of a type from widgets.
     * @param string phraseType Phrase type good, needs_work, poor.
     * @returns Array Phrases of that type.
     */
    getPhrases: function( phraseType ) {
      var phrases = new Array();
      var containerId = "rubric-create-phrases-" + phraseType + "-container";
      var phrase;
      $("#" + containerId + " input").each( function(index, element) {
        phrase = $(element).val();
        if ( phrase ) {
          phrases.push( phrase );
        }
      });
      return phrases;
    },
    /*
     * Return a list of tids (term ids) of terms the user has checked. 
     */
    findCheckedTerms: function() {
      var selNodes = uiNamespace.tree.fancytree("getTree").getSelectedNodes();
      var terms = new Array();
      $(selNodes).each( function(index, node) {
        terms.push( node.key );
//        console.log( node.key + " " + node.title );
      });
      return terms;
    },
    /*
     * Save rubric item to server. Update or create, depending on nid.
     */
    sendItemToServer: function( item ) {
      var webServiceUrl = Drupal.settings.basePath 
              + "exercise/rubric_item";
      var httpType;
      if ( item.nid == 0 ) {
        //Create.
        httpType = "POST";
      }
      else {
        //Update.
        webServiceUrl += "/" + item.nid;
        httpType = "PUT";
      }
      var promise = $.ajax({
        type: httpType,
        contentType: "application/json; charset=utf-8",
        dataType: "json",
        data: JSON.stringify( item ),
        url: webServiceUrl,
        beforeSend: function (request) {
          request.setRequestHeader("X-CSRF-Token", 
            Drupal.behaviors.cycoSelectRubricUi.token);
        }
      })
      .done(function(result) {
        //Save item nid - new for item creation.
        if ( result.operation == "create" ) {
          uiNamespace.item.nid = result.nid;
        }
      })
      .fail(function(jqXHR, textStatus, errorThrown) {
        Drupal.behaviors.cycoErrorHandler.reportError(
          "Fail in sendItemToServer in "
            + "cyco_exercises_create_rubric_ui. " 
            + "textStatus: " + textStatus + ", errorThrown: " + errorThrown
        );
      });
      return promise;
    },
    showSaveThrobber: function() {
      $("#rubric-create-saving-throbber").show("fast");
    },
    hideSaveThrobber: function() {
      $("#rubric-create-saving-throbber").hide("fast");
    }
  };
}(jQuery));
