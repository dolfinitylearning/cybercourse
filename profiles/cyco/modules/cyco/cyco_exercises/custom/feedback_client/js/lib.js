/* 
 * Library of shared code for feedback_client.
 */

/**
 * Create HTML with links to attachments.
 * @param {Array} attachmentData Data about attachments. Array, each element
 *     an object with filename and url. 
 * @param {string} titleToUse Title for the section. Defaults to Attachments.
 * @returns {String} HTML.
 */
app.makeLinksForAttachments = function( attachmentData, titleToUse ) {
  //Title defaults to Attachment.
  if ( ! titleToUse ) {
    titleToUse = "Attachments";
  }
  var linksHtml = "";
  linksHtml += "<div class='cybercourse-grading-attachments-container'>"
    + "<p class='cybercourse-grading-attachments-title'>" + titleToUse + "</p>";
  for( var index in attachmentData ) {
    var filename = attachmentData[ index ].filename;
    var url = attachmentData[ index ].url;
    //Make a link.
    var link = "<a href='" + url + "' data-target='popup' title='Open'>" 
        + filename + "</a>";
    linksHtml += "<p class='cybercourse-grading-attachments-link'>"
        + link + "</p>";
  } //End for.
  linksHtml += "</div>";
  return linksHtml;
}

/**
 * Open attachment links in new window.
 */
app.setupAttachmentLinks = function() {
  $(".pane-content").on("click", "a[data-target=popup]", function(event) {
    event.preventDefault();
    event.stopPropagation();
    var filename = $(this).text();
    windowObjectReference = window.open(
            $(this).attr("href"),
            "Attachment " + filename,
            "resizable,scrollbars,height=400,width=400"
            );
    windowObjectReference.document.title = "DOG";
    return false; //Cancel standard action.
  });
}
