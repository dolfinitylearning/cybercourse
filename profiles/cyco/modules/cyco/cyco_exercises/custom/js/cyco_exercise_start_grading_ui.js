/* 
Open the grading UI in a new window.
*/
(function ($) {
  Drupal.behaviors.openGradingUi = {
    attach: function() {
      //Open links in a popup window.
      $(".cybercourse-control-panel-grade-link").click(function(event) {
        event.preventDefault();
        event.stopPropagation();
        windowObjectReference = window.open(
                $(this).attr("href"),
                "Grading UI",
                "resizable,scrollbars,height=700,width=950"
                );
        //Tell the opening page the base path of Drupal.
        windowObjectReference.cybercourseBasePath = Drupal.settings.basePath;
        return false; //Cancel standard action.
      });
    } //End attach
  };
}(jQuery));



