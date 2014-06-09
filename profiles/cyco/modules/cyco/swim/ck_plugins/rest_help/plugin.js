/**
 * @file Plugin for CKEditor, adding ReST help button.
 */

CKEDITOR.plugins.add('rest_help', {
  icons: 'rest_help',
  init: function(editor) {
    var restWindow; //For closure below.
    editor.addCommand('restHelp', {
      exec: function() {
          //Open the help window.
          var url = Drupal.settings.basePath 
                  + Drupal.settings.restHelp.helpUrl
                  + Drupal.settings.restHelp.plainFlag;
          restWindow=window.open(
            url,
            Drupal.settings.restHelp.windowTitle,
            'width=500 height=400, resizable=yes,scrollbars=yes ,menubar=no'
          );
          restWindow.focus();
      }
    });
    editor.ui.addButton( 'RestHelp', {
        label: 'Help',
        command: 'restHelp',
        state: CKEDITOR.TRISTATE_ENABLED,
        icon : this.path + 'icons/rest_help.png',
        toolbar: 'about'
    });
  }
});


