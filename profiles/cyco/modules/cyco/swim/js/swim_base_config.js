/**
 * @file
 * Base config file for SWIM's CKEditor instances. 
 * Plugins are added dynamically, as needed.
 */
"use strict";
Drupal.swimCkConfig = {
  autoParagraph: false,
  fillEmptyBlocks: false,
  disableObjectResizing : true,
//  basicEntities : false, //Entity encode <, >.
  basicEntities : true, //Entity encode <, >.
  forcePasteAsPlainText : false,
  mathJaxClass : 'math',
  //mathJaxLib : 'https:\/\/c328740.ssl.cf1.rackcdn.com\/mathjax\/latest\/MathJax.js\?config\=TeX\-AMS\-MML\_HTMLorMML',
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
    + "blockquote,indentlist,indentblock,sourcearea,pastefromword,pastetext,"
    + "colorbutton,colordialog,flash,font,indent,forms.horizontalrule,"
    + "basicstyles",
  removeButtons : "Bold,Italic,Underline,Strike,Superscript,Subscript,"
    + "ShowBlocks,Save,NewPage,DocProps,Preview,Print,Templates,"
    + "About,Source",
    //@todo Figure out how to get pseudent rules into pseudents only.
    //Removing them from here makes the button vanish.
  allowedContent:
    'br;'
    + 'img[!src];'
    + 'div(!pseudent)[!data-pseudent-id];'
    + 'div(!pseudent-image-container);'
    + 'div(!pseudent-content);'
    + 'div(!pseudent-image-caption);'
};
