/**
 * @file Plugin for peeking at SWIM content.
 * Used to be called preview, but there is already a preview plugin. 
 */

(function($) {
  CKEDITOR.plugins.add( 'peek', {
      icons: 'peek',
      init: function( editor ) {
        //Check peek permission.
        if ( Drupal.settings.swim.can_peek != "yes" ) {
          return;
        }
        editor.addCommand( 'peek', {
          exec: function( editor ) {
            Drupal.behaviors.swim.peekButtonClicked( editor );
          }
        });
        editor.ui.addButton( 'Peek', {
            label: 'Peek: see what readers see',
            command: 'peek',
            state: CKEDITOR.TRISTATE_DISABLED,
            icon: this.path + 'icons/peek.png',
            toolbar: 'tools,1'
        });
      }
  });
} )(jQuery);
