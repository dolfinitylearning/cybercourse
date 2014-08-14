/**
 * @file
 * Base config file for SWIM's CKEditor instances. 
 * Plugins are added dynamically, as needed.
 */
CKEDITOR.editorConfig = {
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
  removePlugins : "scayt,elementspath,contextmenu,about,"
    + "flash,font,forms"
};
