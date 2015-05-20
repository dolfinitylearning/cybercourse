      
"use strict";
(function ($) {

$(document).ready(function(){
  $("#quicktest .cyco-test-button2").click(function(){
    console.log('begin');
    $.when(
      cycoCoreServices.getCsrfToken()
    )
    .then(function() {
      $.when(
        cycoCoreServices.getShouldLogOtherEvent( "other" )
      )
      .then(function() {
        if ( cycoCoreServices.shouldLogOtherEvent ) {
          $.when( function(){
            var params = {
              goose: 'thing',
              gander: 'that'
            };
            return cycoCoreServices.sendEventToServer('other', 'aligator', params);
            }
          )
          .then(function(){
            console.log('event logged');
          })
          .fail(function(jqXHR, textStatus, errorThrown) {
            alert("ARGH! " + errorThrown );
          });
        }
         console.log("Result: " + cycoCoreServices.shouldLogOtherEvent);
      })
      .fail(function(jqXHR, textStatus, errorThrown) {
        alert("EVIL! " + errorThrown );
      });

    console.log('end');
  })
  });
});

}(jQuery));
