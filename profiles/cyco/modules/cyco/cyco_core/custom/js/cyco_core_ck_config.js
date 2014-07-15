/**
 * @file
 * Base config file for SWIM's CKEditor instances. 
 * Plugins are added dynamically, as needed.
 */
CKEDITOR.editorConfig = {
//  autoParagraph: false,
//  fillEmptyBlocks: false,
//  disableObjectResizing : true,
//  basicEntities : false, //Entity encode <, >.
  basicEntities : true, //Entity encode <, >.
  forcePasteAsPlainText : false,
  mathJaxClass : 'math',
  mathJaxLib : 'https:\/\/c328740.ssl.cf1.rackcdn.com\/mathjax\/latest\/MathJax.js\?config\=TeX\-AMS\-MML\_HTMLorMML',
  tabSpaces: 4,
  disableNativeSpellChecker : false,
  //What the Enter key does.
  enterMode : 2 , //CKEDITOR.ENTER_BR
  shiftEnterMode : 2, //CKEDITOR.ENTER_BR
  //Let images be inserted.
  allowedContent : true,
  //Toolbar config
//  toolbarGroups : [
//    { name: 'clipboard',   groups: [ 'clipboard', 'undo' ] },
//    { name: 'insert' },
//    { name: 'tools' },
//    { name: 'document',    groups: [ 'mode', 'document', 'doctools' ] },
//    { name: 'about' }
//  ],
  removePlugins : "scayt,elementspath,contextmenu,about,"
    + "flash,font,forms"
};
