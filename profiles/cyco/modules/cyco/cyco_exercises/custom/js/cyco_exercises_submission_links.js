/* 
 * Create submission links for an inserted exercise. 
 */
(function($) {
  var uiNamespace; //Convenient ref to a namespacey thing.
  /**
   * Theme function to make a submission link.
   * @param {string} url The URL.
   * @param {string} linkText Text the user sees.
   * @param {string} titleText Title attribute text.
   * @returns {string} The link, an <a> tag.
   */
  Drupal.theme.prototype.submissionLink = function(url, linkText, titleText) {
    var link = "<a href='" + url + "' title='" + titleText + "' "
        + " class='exercise-work-on-it-link' data-target='popup'>"
        + linkText + "</a>";
    return link;    
  }
  /**
   * Theme function for a labeled link.
   * @param {string} versionLabel The version, usually MT.
   * @param {string} statusMessage Status of the submission.
   * @param {string} link The link, an <a> tag.
   * @returns {string} HTML for the labeled link.
   */
  Drupal.theme.prototype.linkLabel = function(versionLabel, statusMessage, link){
    var html = 
          "<div class='cyco-inserted-exercise-link-container'>";
    if ( versionLabel ) {
      html += "<div class='cyco-inserted-exercise-link-version'>"
        +       versionLabel
        +     "</div>"

    }
    if ( statusMessage ) {
      html += "<div class='cyco-inserted-exercise-link-status'>"
        +       statusMessage 
        +     "</div>";
    }
    html += "<div class='cyco-inserted-exercise-link-link'>"
        +       link 
        +   "</div>"
        + "</div>";
    return html;
  },
  Drupal.behaviors.cycoExerSubLinks = {
    attach: function(context, settings) {
      uiNamespace = Drupal.behaviors.cycoExerSubLinks;
      //Where submission data from the server is kept.
      uiNamespace.submissionData = new Array();
      //References to throbbers, indexed by exercise nid.
      uiNamespace.throbbbers = new Array();
      //Find the inserted exercises.
      $("div[data-nid].cyco-inserted-exercise").each( function(index, element) {
        //Get uid of current user.
        var studentUid = Drupal.settings.cybercourse_exercise.uid;
        //Get exercise nid of this exercise.
        var exerciseNid = $(element).attr("data-nid");
        //Append a throbber.
        var throbber = uiNamespace.makeThrobber( element );
        //Keep a reference to the throbber, in case of a refresh by a popup window.
        uiNamespace.throbbbers[exerciseNid] = throbber;
        throbber.show();
        $.when(
          uiNamespace.getCsrfToken()
        )
        .then(function() {
          //Grab vocab terms and rubric items from server.
          $.when( 
            uiNamespace.fetchSubmissionMetaData( studentUid, exerciseNid )
          )
          .then(function() {
            //Prep the UI.
            uiNamespace.prepareUi( studentUid, exerciseNid );
            throbber.hide();
          })
          .fail(function() {
            alert("The voles died.");
          });
        })
        .fail(function() {
          alert("The gerbils died.");
        });
      });
    },
    refreshLinksForExercise: function( exerciseNid ) {
      var throbber = uiNamespace.throbbbers[exerciseNid];
      throbber.show();
      //Get uid of current user.
      var studentUid = Drupal.settings.cybercourse_exercise.uid;
      //Load submission data for the exercise.
      $.when( 
        uiNamespace.fetchSubmissionMetaData( studentUid, exerciseNid )
      )
      .then(function() {
        //Update the the UI.
        uiNamespace.prepareUi( studentUid, exerciseNid );
        throbber.hide();
      })
      .fail(function() {
        alert("The submission interface refresh failed.");
      });
    },
    /**
     * Append a throbber to an element.
     * @param {DOM element} parentElement Where to attach throbber.
     * @returns {$} Rrf to the attached throbber.
     */
    makeThrobber: function( parentElement ) {
      var throbber = $(
  "<div style='display:none'>"
+   "Loading..."
+   "<div class='ajax-progress ajax-progress-throbber'>"
+     "<div class='throbber'>&nbsp;</div>"
+   "</div>"
+ "</div>"
      );
      $(parentElement).append( throbber );
      return throbber;
    },
    /**
     * Get a CSRF token.
     * @returns {unresolved} Promise.
     */
    getCsrfToken: function(){
      //Connect and get user details.
      var webServiceUrl = Drupal.settings.basePath + "services/session/token";
      var promise = $.ajax({ 
          type: "GET",
          url: webServiceUrl,
          dataType: "text"
      })
        .done(function(token){
          uiNamespace.token = token;
        })
        .fail(function(jqXHR, textStatus, errorThrown) {
          console.log('Token request failed! ' + textStatus + errorThrown); 
        })
        .always(function() {
//          $("#activity").hide();
        }); 
      return promise;
    },
    /**
     * Ask the server for metadata about this user's submissions 
     * for this exercise.
     * @param {int} uid Uid of current user.
     * @param {int} exercise_nid Nid of current exercise.
     */
    fetchSubmissionMetaData: function( studentUid, exerciseNid ) {
      var webServiceUrl = Drupal.settings.basePath 
              + "exercise/submission/getSubmissionMetaStudentExer";
      var dataToSend = {};
      dataToSend.student = studentUid;
      dataToSend.exercise = exerciseNid;
      dataToSend = JSON.stringify( dataToSend );
      var promise = $.ajax({
        type: "POST",
        contentType: "application/json; charset=utf-8",
        dataType: "json",
        url: webServiceUrl,
        data: dataToSend,
        beforeSend: function (request) {
          request.setRequestHeader("X-CSRF-Token", uiNamespace.token);
        }
      })
        .done(function(result) {
          uiNamespace.submissionData[ exerciseNid ] = result;
        })
        .fail(function(jqXHR, textStatus, errorThrown) {
          alert('fetchSubmissionMetaData request failed! ' + errorThrown);
        });
      return promise;
    },
    /**
     * Set up the links to the submission form.
     * @param {int} studentUid Student uid.
     * @param {int} exerciseNid Exercuse nid.
     */
    prepareUi: function( studentUid, exerciseNid ) {
      //Compute links to add.
      var linkLabels = uiNamespace.makeLinkLabels( studentUid, exerciseNid );
      //Find where to add them.
      var $linkLocation = $("div[data-nid=" + exerciseNid + "] .cyco-inserted-exercise-links-container");
      //MT it - this could be a refresh call from a popup.
      $linkLocation.html('');
      $.each(linkLabels, function(index, linkLabel) {
        var renderedLink = Drupal.theme(
          "linkLabel", //Theme function.
          linkLabel.versionLabel,
          linkLabel.statusMessage,
          linkLabel.link
        );
        $linkLocation.append( renderedLink );
      });
      //Open links in a popup window.
      $("a[data-target=popup]").click(function(event) {
        event.preventDefault();
        event.stopPropagation();
        windowObjectReference = window.open(
                $(this).attr("href"),
                "Exercise: " + exerciseNid,
                "resizable,scrollbars,height=600,width=600"
                );
        return false; //Cancel standard action.
      });
      //Update 
    },
    /**
     * Constructor for a link label: a link with a pair of labels
     * describing the link to the user.
     * @param {string} versionLabel Version of submission.
     * @param {string} statusMessage State of the submission.
     * @param {string} link Link to submission in a new window.
     */
    LinkLabel: function (versionLabel, statusMessage, link) {
      this.versionLabel = versionLabel;
      this.statusMessage = statusMessage;
      this.link = link;
    },
    /**
     * Make a set of link labels for this exercise for this user.
     * @returns {Array} LinkLabels.
     */
    makeLinkLabels : function( studentUid, exerciseNid ) {
      //The labels to return;
      var linkLabels = new Array();
      //One link label.
      var linkLabel;
      //One link.
      var link;
      var numSubmissions = uiNamespace.submissionData[exerciseNid].length;
      if ( numSubmissions == 0 ) {
        //There are no submissions.
        //Make a link to create the first submission.
        link = uiNamespace.makeSubmissionLink(
            "add", "Work on it", "Work on the exercise", exerciseNid, "");
        linkLabel = new uiNamespace.LinkLabel("", "", link);
        linkLabels.push( linkLabel );
      }
      else {
        //There is at least one submission.
        $.each( uiNamespace.submissionData[exerciseNid], function(submissionIndex, submission) {
          var submissionId = submission.nid;
          //Version label only shows if there is more than one submission.
          var versionLabel = "";
          if ( numSubmissions > 1 ) {
            versionLabel = "Version " + submission.version;
          }
          //Set up the status label and the link.
          var statusMessage = "";
          var link = "";
          if ( ! submission.whenSubmitted ) {
            //Has not been submitted yet.
            statusMessage = "Not submitted for feedback.";
            link = uiNamespace.makeSubmissionLink(
                "edit", "Work on it", "Work on the exercise", submissionId, ""
            );
            //Save the link.
            linkLabel = new uiNamespace.LinkLabel(versionLabel, statusMessage, link);
            linkLabels.push( linkLabel );
          }
          else {
            //It has been submitted.
            //Is there feedback?
            if ( ! submission.whenFeedbackGiven ) {
              //Submitted, but no feedback. User can still work on it.
              statusMessage = "Submitted, but no feedback yet.";
              link = uiNamespace.makeSubmissionLink(
                  "edit", "Work on it", "Work on the exercise", submissionId, ""
              );
              //Save the link.
              linkLabel = new uiNamespace.LinkLabel(versionLabel, statusMessage, link);
              linkLabels.push( linkLabel );
            }
            else {
              //Submitted and there is feedback. User can only review it.
              statusMessage = "Feedback is available.";
              link = uiNamespace.makeSubmissionLink(
                  "review", "Review", "Look at the feedback", submissionId, ""
              );
              //Save the link.
              linkLabel = new uiNamespace.LinkLabel(versionLabel, statusMessage, link);
              linkLabels.push( linkLabel );
              //After the last one, add a link that lets the user create a new
              //version for the submission.
              var processingLastOne = ( (submissionIndex + 1) == numSubmissions );
              if ( processingLastOne ) {
                //Make a link to create a new version.
                versionLabel = "";
                statusMessage = "";
                var urlExtras = "&version = " + (numSubmissions + 1);
                link = uiNamespace.makeSubmissionLink(
                    "add", "Create new version", 
                    "Make a new version of the submission", 
                    exerciseNid, urlExtras
                );
                //Save the link.
                linkLabel = new uiNamespace.LinkLabel(versionLabel, statusMessage, link);
                linkLabels.push( linkLabel );
              }
            }
          } // end whenSubmitted
        }); //End each loop.
      }// End there are submissions.
      return linkLabels;
    },
    /**
     * Create a link to open a submission window.
     * @param {string} operation What the user is doing - add, edit, or review.
     * @param {string} linkText Text the user sees.
     * @param {string} titleText Link title.
     * @param {int} exerciseNid Exercise nid.
     * @param {string} urlExtras Stuff to append to URL.
     * @returns {string} The link.
     */
    makeSubmissionLink: function ( 
            operation, linkText, titleText, exerciseNid, urlExtras ) {
      var url = Drupal.settings.basePath;
      var link;
      if ( operation == "add" ) {
        url += "node/add/exercise-submission";
      }
      else if ( operation == "edit" ) {
        url += "node/" + exerciseNid + "/edit";
      }
      else if ( operation == "review" ) {
        //View the node.
        url += "node/" + exerciseNid;
      }
      else {
        alert("Bad operation: " + operation);
        return;
      }
      //Add the operation type.
      url += '?op=' + operation;
      //Add exercise id.
      url += '&field_exercise=' + exerciseNid;
      //Add destination after submission that will close the window.
      url += '&destination=cybercourse-exercise-close-popup';
      //Add extras.
      url += urlExtras;
      link = Drupal.theme("submissionLink", url, linkText, titleText);
      return link;
    }
  };
}(jQuery));



