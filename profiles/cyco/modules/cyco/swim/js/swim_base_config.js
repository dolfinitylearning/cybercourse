/**
 * @file
 * Base config file for SWIM's CKEditor instances. 
 * Plugins are added dynamically, as needed.
 */
"use strict";
(function ($) {
Drupal.behaviors.addMathJaxConfig = {
  attach: function (context, settings) {
//console.log('penguin');
//console.log(Drupal.settings.swim.mathjaxPath);
Drupal.swimCkConfig = {
  autoParagraph: false,
  fillEmptyBlocks: false,
  disableObjectResizing : true,
  basicEntities : true, //Entity encode <, >.
  forcePasteAsPlainText : false,
  mathJaxClass : 'math',
  mathJaxLib : Drupal.settings.swim.mathjaxPath,
//  mathJaxLib : 'https:\/\/c328740.ssl.cf1.rackcdn.com\/mathjax\/latest\/MathJax.js\?config\=TeX\-AMS\-MML\_HTMLorMML',
  //mathJaxLib : Drupal.settings.swim.base_url + '/profiles/cyco/libraries/mathjax/unpacked/MathJax.js\?config\=TeX\-AMS\-MML\_HTMLorMML',
  tabSpaces: 4,
  disableNativeSpellChecker : false,
  //What the Enter key does.
  enterMode : 2 , //CKEDITOR.ENTER_BR
  shiftEnterMode : 2, //CKEDITOR.ENTER_BR
  //Toolbar config
  toolbarGroups : [
    { name: 'clipboard',   groups: [ 'clipboard', 'undo' ] },
    { name: 'insert' },
    { name: 'tools' },
    { name: 'document',    groups: [ 'mode', 'document', 'doctools' ] },
    { name: 'about' }
  ],
  removePlugins : "scayt,elementspath,list,liststyle,tabletools,contextmenu,about,"
//    + "blockquote,indentlist,indentblock,pastefromword,pastetext,"
    + "blockquote,indentlist,indentblock,sourcearea,pastefromword,pastetext,"
    + "colorbutton,colordialog,flash,font,indent,forms.horizontalrule,"
    + "basicstyles",
  removeButtons : "Bold,Italic,Underline,Strike,Superscript,Subscript,"
    + "ShowBlocks,Save,NewPage,DocProps,Preview,Print,Templates,"
//    + "About",
    + "About,Source",
  allowedContent: true
    //@todo Figure out how to get pseudent rules into pseudents only.
    //Removing them from here makes the button vanish.
//  allowedContent:
//    'br;'
//    + 'img[!src];'
//    + 'div(!pseudent)[!data-pseudent-internal-name];'
//    + 'div(!pseudent-image-container);'
//    + 'div(!pseudent-content);'
//    + 'div(!pseudent-image-caption);'
};
  }
};

})(jQuery);
