/* 
 * Slimy hack to kill extra <brs>s added by CKEditor before pseudent divs.
 */
"use strict";
(function ($) {
  CKEDITOR.on("instanceReady", function(evnt) {
    $(evnt.editor.document.$.body).find(".pseudent").each(function(index, element) {
      if (
                this.parentElement.previousSibling.nodeName == "BR"
             && this.parentElement.previousSibling.previousSibling.nodeName == "BR"
         ) {
           this.parentElement.previousSibling.remove();
         }
    });
  });
}(jQuery));
