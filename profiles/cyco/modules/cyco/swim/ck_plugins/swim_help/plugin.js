/**
 * @file Plugin for CKEditor, adding SWIM help button. The button opens
 * a window, with helpy content.
 */

(function($) {
  CKEDITOR.plugins.add('swim_help', {
    icons: 'swim_help',
    init: function(editor) {
      editor.addCommand('swimHelp', {
        exec: function() {
          //Check local cache.
          if ( cycoSwimHelp.help ) {
            //Already loaded, show it.
            cycoSwimHelp.showHelpPopup();
          }
          else {
            //Don't have help yet. Get it and show.
            $.when(
              cycoCoreServices.getCsrfToken()
            )
            .then(function() {
              $.when(
                cycoSwimHelp.getHelpFromServer()
              )
              .then(function() {
                cycoSwimHelp.showHelpPopup();
              });
            });
          }
        }
      });
      editor.ui.addButton( 'SwimHelp', {
          label: 'Help',
          title: 'SWIM help (tell your browser to allow popups)',
          command: 'swimHelp',
          state: CKEDITOR.TRISTATE_ENABLED,
          icon : this.path + 'icons/swim_help.png',
          toolbar: 'about'
      });
    }
  });

  var cycoSwimHelp = cycoSwimHelp || {};

  cycoSwimHelp.getHelpFromServer = function() {
    var webServiceUrl 
        = Drupal.settings.cycoCoreServices.baseUrl + Drupal.settings.basePath 
          + "swim/swim_help/swimHelp";
    var promise = $.ajax({
      type: "POST",
      contentType: "application/json; charset=utf-8",
      dataType: "json",
      url: webServiceUrl,
      beforeSend: function (request) {
        request.setRequestHeader("X-CSRF-Token", swimServices.csrfToken);
      }
    })
    .done(function(result) {
      cycoSwimHelp.help = result;
    })
    .fail(function(jqXHR, textStatus, errorThrown) {
      Drupal.behaviors.cycoErrorHandler.reportError(
        "Get help request failed in cycoSwimHelp.getHelpFromServer. " 
          + "textStatus: " + textStatus + ", errorThrown: " + errorThrown
      );
    });
    return promise;  
  };
  
  cycoSwimHelp.showHelpPopup = function() {
    var swimWindow=window.open(
      "",
      "SWIM Help",
      "width=700,height=500,resizable=yes,scrollbars=yes,"
        + "menubar=no,location=no"
    );
    swimWindow.document.write( cycoSwimHelp.help );
  };
  
} )(jQuery);
