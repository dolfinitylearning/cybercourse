/**
 *  Base config file for CKEditor instances. 
 */
Drupal.swimCkConfig = {
  	disableObjectResizing : true,
  basicEntities : true, //Entity encode <, >.
  forcePasteAsPlainText : true,
  mathJaxClass : 'math',
  mathJaxLib : 'https:\/\/c328740.ssl.cf1.rackcdn.com\/mathjax\/latest\/MathJax.js\?config\=TeX\-AMS\-MML\_HTMLorMML',
//  enableTabKeyTools: false,
  tabSpaces: 4,
  disableNativeSpellChecker : false,
  //What the Enter key does.
  enterMode : 2 , //CKEDITOR.ENTER_BR
  shiftEnterMode : 2, //CKEDITOR.ENTER_BR
  //Let images be inserted.
  allowedContent : true,
  // The minimum editor width, in pixels, when resizing it with the resize handle.
//  resize_minWidth : 400,
  //Toolbar config
  toolbarGroups : [
    { name: 'clipboard',   groups: [ 'clipboard', 'undo' ] },
//      { name: 'editing',     groups: [ 'find', 'selection', 'spellchecker' ] },
//      { name: 'links' },
      { name: 'insert' },
//      { name: 'forms' },
    { name: 'tools' },
    { name: 'document',    groups: [ 'mode', 'document', 'doctools' ] },////
//    { name: 'others' },
//    '/',
//    { name: 'basicstyles', groups: [ 'cleanup' ] },
//      { name: 'paragraph',   groups: [ 'list', 'indent', 'blocks', 'align' ] },
//      { name: 'styles' },
//      { name: 'colors' },
    { name: 'about' }
  ],
  removeButtons : "Bold,Italic,Underline,Strike,Superscript,Subscript" +
          ",ShowBlocks,Save,NewPage,DocProps,Preview,Print,Templates," +
          ",About",
  //These should not be there anyway, given the limited CK instance
  //that is used.
  removePlugins : "scayt,elementspath,list,liststyle,tabletools,contextmenu,about,"
    + "blockquote,indentlist,indentblock,"
    + "colorbutton,colordialog,flash,font,indent,forms.horizontalrule"
};
