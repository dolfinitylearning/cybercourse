/**
 * Manage a dialog that lets the user choose a pseudent. The HTML for
 * the image display is generated on the server. It's a table. 
 * The id of the table is pseudent-choose-table.
 * 
 * Each cell
 * is a pseudent. Each cell has an id of pseudent-cell-nid, where nid is
 * the nid of a pseudent entity.
 * 
 * Each cell also has an attribute data-pseudent-nid with the same nid.
 */

(function ($) {
  CKEDITOR.dialog.add( 'pseudentDialog', function ( editor ) {
      Drupal.settings.pseudents.currentSelection = '';
      var theDialog = this;
      return {
          onShow:function( evt ) {
//            console.log('show fired');
            //Move to a place it can expand.
            this.move( 10, 10 );
          },
          ok: function( evt ) {
            //console.log('ok fired');
          },
          cancel: function() {
          },
          title: 'Add a pseudent',
          minWidth: 400,
          minHeight: 200,
          contents: [
              {
                //****** Need a tab?
                id: 'tab-pseudents',
                label: 'Pseudents',
                elements: [
                  {
                    //List of pseudent categories.
                    id: 'pseudentCategories',
                    validate: function( evt ) {
                      //Ref to the dialog this is in.
                      var dialog = this.getDialog();
                      if ( ! dialog.pseudentId ) {
                        alert("Please select a pseudent pose.");
                        return false;
                      }
                    },
                    type: 'select',
                    label: "Select a category",
                    items: makeSelectList( Drupal.settings.pseudents.catTerms ),
                    onChange: function( api ) {
                        // this is CKEDITOR.ui.dialog.select.
                        //Hide everything.
                        $("#pseudent-choose-table td.pseudent-preview").hide();
                        var selectedCategory = this.getValue();
                        //Anything selected?
                        if ( selectedCategory ) {
                          //Add spaces around the selected category.
                          //This avoids, e.g., 7 being a false positive for 171.
                          var selectedCategoryString = " " + selectedCategory + " ";
                          $("#pseudent-choose-table td.pseudent-preview").each(
                            function(index, element) {
                              //Does this element have any categories?
                              var $element = $(element);
                              if ( $element.attr("data-pseudent-categories") ) {
                                //Does this element have the selected category?
                                if ( $element.attr("data-pseudent-categories")
                                      .indexOf(selectedCategoryString) != -1 ) {
                                  $element.show();
                                }
                              }
                            } //End function run on each element.
                          ); //End each.
                        }
                    }
                  },
                  {
                    id: 'pseudentId',
                    type: 'html',
                    html: makeChoosePseudentHtml(Drupal.settings.pseudents.posePreviews),
                    setup: function( widget ) {
                      //Ref to the dialog this is in.
                      var dialog = this.getDialog();
                      //Clear all selection classes.
                      jQuery("table#pseudent-choose-table td")
                              .removeClass("selected");
                      //Find the selected item, if there is one.
                      dialog.pseudentId = "";
                      dialog.initialPseudentId = "";
                      if ( jQuery(widget.element.$).find(".pseudent-image") ) {
                        if ( jQuery(widget.element.$).find(".pseudent-image").attr("data-pseudent-id") ) {
                          dialog.pseudentId = jQuery(widget.element.$).find(".pseudent-image").attr("data-pseudent-id");
                          dialog.initialPseudentId = dialog.pseudentId;
                        }
                      }
                      //Show current item as selected, if there is a current item.
                      //  The pseudentId is part of the DOM id of the table cell
                      //  containing data about a pseudent.
                      if ( dialog.pseudentId ) {
                        jQuery('#pseudent-cell-' + dialog.pseudentId)
                          .addClass('selected');
                      }
                      //Add click events to the cells.
                      if ( ! jQuery("table#pseudent-choose-table td")
                             .hasClass("processed") ) {
                        jQuery("table#pseudent-choose-table td")
  //                        .addClass("processed")
                          .click(function(event) {
                            //Clicked on a pose.
                            var target = event.target;
                            //Remove prior selection.
                            if ( dialog.pseudentId ) {
                              var cellId = 'pseudent-cell-' + dialog.pseudentId;
                              jQuery('#' + cellId).removeClass('selected');
                            }
                            //Save new selection.
                            var cell = jQuery(target).closest("td");
                            var psendentId 
                                = parseInt( cell.attr("data-pseudent-nid") );
                            dialog.pseudentId = psendentId;
                            cell.addClass('selected');
                          })
                          .dblclick(function(event) {
                            //Click on the target image.
                            event.target.click();
                            //Click on the OK button.
                            var dlg = CKEDITOR.dialog.getCurrent();
                            var okBtn = dlg.getButton('ok');
                            okBtn.click();
                          });
                      }
                    },
                    commit: function( widget ) {
                      //Ref to the dialog this is in.
                      var dialog = this.getDialog();
                      widget.updateImage( dialog.pseudentId );
                    }
                  }
                ]

              }
          ]
        }
      });

  function makeChoosePseudentHtml ( pseudents ) {
    var NUM_COLUMNS = 5;
    var html = '<div id="pseudent-grid-container"><table id="pseudent-choose-table">';
    var col = 1;
    jQuery.each( pseudents, function( index, pseudent ) {
      if ( col == 1 ) {
        html += '<tr>';
      }
      html += 
         '<td class="pseudent-preview" id="pseudent-cell-' + pseudent.nid 
       +   '" data-pseudent-nid="' + pseudent.nid + '" ';
       //Add student category term ids, as string of ids separated by 
       //spaces, with spaces at the beginning and end.
       if ( Object.keys( pseudent.categories ).length > 0 ) {
         var indexList = "";
         $.each( pseudent.categories, function(termId, term){
           indexList += " " + termId;
         } );
         indexList += " ";
         html += ' data-pseudent-categories="' + indexList + '" ';
       }
       //Every pose is hidden until the user selects a category.
       html += ' style="display:none;">'
       +  '<span class="pseudent-preview-title">' + pseudent.title + '</span><br>'
       +  '<img src="' + pseudent.url + '" alt="' + pseudent.caption + '">'
       + '</td>';
      if ( col < NUM_COLUMNS ) {
        col++;
      }
      else {
        html += '</tr>';
        col = 1;
      }
    }); //End each.
    if ( col != 1 ) {
      html += '</tr>';
    }
    html += '</html></div>';
    return html;
  }
  
  /**
   * Generate array ot items for <select> in the format CK wants it.
   * @param {Array} termDefs Term definitions.
   * @returns {Array} Select list.
   */
  function makeSelectList( termDefs ) {
    var selectItems = new Array();
    $.each( termDefs, function(index, termDef) {
      selectItems.push( [ termDef.term, termDef.tid ] )
    });
    //Sort them.
    selectItems.sort();
    return selectItems;
  }
}(jQuery));
