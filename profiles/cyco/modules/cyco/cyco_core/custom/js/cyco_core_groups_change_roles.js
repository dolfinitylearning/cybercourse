/**
 * @file
When adding users to a class, select the student role.
*/
"use strict";
(function ($) {
  Drupal.behaviors.cycoGroupsSelectStudentRole = {
    attach: function() {
      return;
      //Get the index of the student role sent by server, if it exists.
      if ( 
              Drupal.settings.cycoGroupsSelectStudentRole
           && Drupal.settings.cycoGroupsSelectStudentRole.studentOgRoleIndex
         ) {
        var studentOgRoleIndex = 
             Drupal.settings.cycoGroupsSelectStudentRole.studentOgRoleIndex;
         //Get ref to student checkbox.
        var studentRoleCheckbox = $("#edit-roles #edit-roles-" + studentOgRoleIndex);
        if ( studentRoleCheckbox.length > 0 ) {
          $(studentRoleCheckbox).prop( "checked", true );
          //Add some helpy help.
          $("#edit-roles").before(
            "<p>What role(s) do you want the user(s) to have in "
            + "your group? \"Student\" is the most common.</p>"
          );
        }
      }
    } //End attach
  };
}(jQuery));



