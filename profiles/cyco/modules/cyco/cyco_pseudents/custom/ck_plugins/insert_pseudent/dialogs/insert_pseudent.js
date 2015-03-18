/**
 * @file
 * Manage a dialog that lets the user choose a pseudent. The HTML for
 * the image display is a set of floated divs (let's call it a cell).
 * 
 * Each cell is a pseudent. Each cell has an id of pseudent-cell-INTERNAL_NAME.
 * 
 * Each cell also has an attribute data-pseudent-internal-name with the same name.
 */

(function($) {
  //Make the dialog scroll correctly. See
  // http://theholyjava.wordpress.com/2011/03/31/ckeditor-scroll-dialogs-with-page/
  //Written for CK 3, dinna work w/ 4, but mayhap there's a clue.
  CKEDITOR.on('dialogDefinition', function(e) {
    var dialogName = e.data.name;
    var dialogDefinition = e.data.definition;
    dialogDefinition.dialog.parts.dialog.setStyles(
        {
            position : 'absolute'
        });
  });
  CKEDITOR.dialog.add('insert_pseudent', function(editor) {
    //Drupal.settings.pseudents.currentSelection = '';
    return {
//      allowedContent: 
//                'img[*]{*}(*);'
//              + 'br;'
//              + 'div(!pseudent)[!data-pseudent-internal-name];'
//              + 'div(!pseudent-image-container);'
//              + 'div(!pseudent-image);'
//              + 'div(!pseudent-image-caption); '
//              + 'div(!pseudent-content);',
      title: 'Add a pseudent',
      width: $(window).width() * 0.75,
      height: $(window).height() * 0.75,
      resizable: CKEDITOR.DIALOG_RESIZE_BOTH,
      contents: [
        {
          id: 'info',
          elements: [
            {
              //List of pseudent categories.
              id: 'pseudentCategories',
              type: 'select',
              label: "Select a category",
              items: makeSelectList(Drupal.settings.pseudents.catTerms),
              setup: function( widget ) {
                if ( ! widget.data.pseudentCategory ) {
                  //No category - it's a new insertion.
                  //Use category from last time, if there is one.
                  if ( Drupal.settings.pseudents.lastCategory ) {
                    widget.data.pseudentCategory 
                        = Drupal.settings.pseudents.lastCategory;
                  }
                  else {
                    //Nothing there - use All.
                    widget.data.pseudentCategory = 0;
                  }
                }
                this.setValue( widget.data.pseudentCategory );
              },
              commit: function( widget ) {
                widget.setData( "pseudentCategory", this.getValue() );
                //Store the category for next time user clicks psuedent button
                //on this page.
                Drupal.settings.pseudents.lastCategory = this.getValue();
              },
              validate: function(evt) {
                if ( $(".pseudent-cell.selected").length == 0 ) {
                  alert("Please select a pseudent pose, or Cancel.");
                  return false;
                }
              },
              onChange: function() {
                //The selected category has changed, 
                //so show only cells in that category.
                //Hide everything.
                $(".pseudent-cell").hide();
                var selectedCategory = this.getValue();
                  //Add spaces around the selected category.
                  //This avoids, e.g., 7 being a false positive for 171.
                  var selectedCategoryString = " " + selectedCategory + " ";
                  $(".pseudent-cell").each(
                    function(index, element) {
                      //Does this element have any categories?
                      var $element = $(element);
                      if ( selectedCategory == 0 ) {
                        //"All" was selected.
                        $element.show();
                      }
                      else {
                        if ($element.attr("data-pseudent-categories")) {
                          //Does this element have the selected category?
                          if ($element.attr("data-pseudent-categories")
                                  .indexOf(selectedCategoryString) != -1) {
                            $element.show();
                          }
                        }
                      }
                    } //End function run on each element.
                  ); //End each.
              }
            },
            {
              //The cells shown for selecting a pseudent.
              id: 'pseudentCells',
              type: 'html',
              html: makeChoosePseudentHtml(
                Drupal.settings.pseudents.posePreviews
              ),
              setup: function( widget ) {
                //Show the selected cell, if there is one.
                if ( widget.data.pseudentInternalName ) {
                  $("#pseudent-cell-" + widget.data.pseudentInternalName)
                          .addClass('selected');
                }
                else {
                  //Nothing chosen - show everything in the selected
                  //category.
                  
                }
                this.setupClickEvents( widget );
              },
              onHide: function( x ) {
                $(".pseudent-cell").unbind('click');
              },
              commit: function( widget ) {
                widget.setData( "pseudentInternalName", this.selectedPseudentInternalName );
              },
              setupClickEvents: function( widget ) {
                $(".pseudent-cell")
                    .click(function(event) {
                      //Clicked on a pose.
                      var target = event.target;
                      //Remove prior selection.
                      $(".pseudent-cell.selected").removeClass('selected');
                      //Save new selection.
                      var cell = $(target).closest("div.pseudent-cell");
                          //Could have clicked on any element in the cell.
                      cell.addClass('selected');
                      var pseudentInternalName
                              = cell.attr("data-pseudent-internal-name");
                      widget.setData( "pseudentInternalName", pseudentInternalName );
                      //Stop other processing.
                      return false;
                    })
                    .dblclick(function(event) {
                      //Click on the target image.
                      event.target.click();
                      //Click on the OK button.
                      var dlg = CKEDITOR.dialog.getCurrent();
                      //Test hides an error. Works, don't know why.
                      if ( dlg ) {
                        var okBtn = dlg.getButton('ok');
                        okBtn.click();
                      }
                      //Stop other processing.
                      return false;
                    });
              } //End setupClickEvents.
            } //End HTML element definition.
          ] //End dialog tab UI elements definition.
        } //End dialog tab contents definition.
      ] //End dialog tab list (only one).
    }; //End return object definition.
  });

  function makeChoosePseudentHtml(pseudents) {
    var html = '<div id="pseudent-grid-container">';
    $.each(pseudents, function(index, pseudent) {
      html +=
              '<div class="pseudent-cell" id="pseudent-cell-' + pseudent.internal_name
              + '" data-pseudent-internal-name="' + pseudent.internal_name + '" ';
      //Add student category term ids, as string of ids separated by 
      //spaces, with spaces at the beginning and end.
      if (Object.keys(pseudent.categories).length > 0) {
        var indexList = "";
        $.each(pseudent.categories, function(termId, term) {
          indexList += " " + termId;
        });
        indexList += " ";
        html += ' data-pseudent-categories="' + indexList + '" ';
      }
      //Every pose is hidden until the user selects a category.
      html += ' style="display:none;">'
              + '<div class="pseudent-preview-title">' + pseudent.title + '</div>'
              + '<img src="' + pseudent.url + '" alt="' + pseudent.caption + '">'
              + '</div>';
    }); //End each.
    html += '</div>';
    return html;
  }

  /**
   * Generate array of items for <select> in the format CK wants it.
   * @param {Array} termDefs Term definitions.
   * @returns {Array} Select list.
   */
  function makeSelectList(termDefs) {
    var selectItems = new Array();
    jQuery.each(termDefs, function(index, termDef) {
      selectItems.push([termDef.term, termDef.tid]);
    });
    //Sort them.
    selectItems.sort();
    //Add "All" category.
    selectItems.unshift(["All", 0]);
    return selectItems;
  }

}(jQuery));
