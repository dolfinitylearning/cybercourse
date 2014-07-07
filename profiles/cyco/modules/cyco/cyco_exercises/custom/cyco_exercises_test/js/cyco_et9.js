(function($) {
  Drupal.behaviors.ext9 = {
    attach: function(context, settings) {
      console.log("attach");
      $("a[data-target=popup]").click(function(event) {
        console.log("processing link");
        event.preventDefault();
        event.stopPropagation();
          windowObjectReference = window.open(
    "/node/add/exercise-submission",
    "DescriptiveWindowName",
    "resizable,scrollbars,status"
  );
        return false; //Cancel standard action.
      });

    }

  };
}(jQuery));
