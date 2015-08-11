/* 
 * Fill-in-the-blank process answer.
 */

/**
 * @file
 * Manage the rubric creation UI.
 */
(function($) {
  "use strict";
  Drupal.behaviors.cycoFibCheckAnswer = {
    /**
     * What is checked? text, number, or none.
     */
    resultOfCheck: "",
    attach: function(context, settings) {
      $(document).ready(function(){
        $(".cyco-fib-response-container button").click(function(event){
          var $fibFieldSet = $($(event.target).closest("fieldset"));
          Drupal.behaviors.cycoFibCheckAnswer.checkAnswer($fibFieldSet);
        });
        $(".cyco-fib-response-container input").keypress(function(event){
          if ( event.which == 13 ) {
            event.preventDefault();
            var $fibFieldSet = $($(event.target).closest("fieldset"));
            Drupal.behaviors.cycoFibCheckAnswer.checkAnswer($fibFieldSet);
          }
        });
      });
    },
    /**
     * Check the user's answer.
     * @param {jQuery ref to a DOM element} $fibFieldSet The fib element, a fieldset.
     */
    checkAnswer: function( $fibFieldSet ) {
      var answerControl, answer, fibType, fibNid, resultObject, returnFibId;
      //Hide responses.
      $fibFieldSet.find(".cyco-fib-correct").hide();
      $fibFieldSet.find(".cyco-fib-hint-container").hide();
      $fibFieldSet.find("cyco-fib-error-container.").hide();      
      //Get the answer.
      answerControl = $fibFieldSet.find("input");
      answer = answerControl.val();
      answer = answer.trim();
      //Stop if MT.
      if ( answer == "" ) {
        alert("Sorry, please type an answer.");
        $(answerControl).focus().select();
        return;
      }
      //Check answer type: number or text.
      fibType = $fibFieldSet.attr("data-response-type");
      if ( isNaN(answer) && fibType == "number" ){
        alert("Sorry, expecting a number.");
        $(answerControl).focus().select();
        return;
      }
      //Send answer to server.
      fibNid = $fibFieldSet.attr("data-nid");
      this.showAjaxThrobber( $fibFieldSet );
      $.when( 
        Drupal.behaviors.cycoFibCheckAnswer.sendAnswerToServer(
            fibNid, answer )
      )
      .then(function() {
        var $fibFieldSet;
        resultObject = Drupal.behaviors.cycoFibCheckAnswer.resultOfCheck;
        returnFibId = resultObject.fibNid;
        $fibFieldSet = $( $(".cyco-fib[data-nid=" + returnFibId + "]"));
        Drupal.behaviors.cycoFibCheckAnswer.hideAjaxThrobber( $fibFieldSet );
        answerControl = $fibFieldSet.find("input");
        if ( resultObject.result == "right" ) {
          $fibFieldSet.find(".cyco-fib-correct").show("medium");
        }
        else if ( resultObject.result == "wrong" ) {
          $fibFieldSet.find(".cyco-fib-hint-container").show("medium");
          $(answerControl).focus().select();
      }
        else if ( resultObject.result == "error" ) {
          $fibFieldSet.find(".cyco-fib-error-message")
                  .text( resultObject.message );
          $fibFieldSet.find(".cyco-fib-error-container").show("medium");
          $(answerControl).focus().select();
        }
      });           
    },
    /*
     * Call the server to check the answer.
     * @param int fibNid Item nid.
     * @param string answer User answer.
     */
    sendAnswerToServer: function ( fibNid, answer ) {
      var webServiceUrl = Drupal.settings.basePath 
              + "fill_in_the_blank/fill_in_the_blank/check";
      var dataToSend = {};
      dataToSend.fib_nid = fibNid;
      dataToSend.student_uid = Drupal.settings.cycoFib.studentUid;
      dataToSend.answer = answer;
      dataToSend = JSON.stringify( dataToSend );
      var promise = $.ajax({
        type: "POST",
        contentType: "application/json; charset=utf-8",
        dataType: "json", 
        data: dataToSend,
        url: webServiceUrl,
        beforeSend: function (request) {
          request.setRequestHeader("X-CSRF-Token", 
            Drupal.settings.cycoCoreServices.csrfToken);
        }
      })
        .done(function(result) {
          //Store result of check.
          Drupal.behaviors.cycoFibCheckAnswer.resultOfCheck = result;
        })
        .fail(function(jqXHR, textStatus, errorThrown) {
          Drupal.behaviors.cycoErrorHandler.reportError(
            "Fail in checkAnswer in "
              + "Drupal.behaviors.cycoFibCheckAnswer. " 
              + "textStatus: " + textStatus + ", errorThrown: " + errorThrown
          );
        });
      return promise;
    },
    showAjaxThrobber: function( $fibFieldSet ) {
      $fibFieldSet.find(".cyco-fib-ajax-throbber").show("fast");
    },
    hideAjaxThrobber: function( $fibFieldSet ) {
      $fibFieldSet.find(".cyco-fib-ajax-throbber").hide("fast");
    }
    
  };
}(jQuery));


