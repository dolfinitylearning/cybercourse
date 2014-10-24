<?php

/**
 * Feedback has been given for a submission.
 * @param $feedback_data  Array of feedback data.
 * Elements:
 *  submission_nid
 *  student_uid
 *  exercise_nid
 *  rubric_ratings
 *    JSON array. Sample item:
 *     {"rubric_item_nid":"206","comment":"Funny!","comment_rating":"good"}
 *  complete (1/0)
 *  message
 */
function hook_feedback_given( $feedback_data ) {
  
}

/**
 * Feedback for a submission was erased.
 * @param $feedback_data  Array of feedback data.
 * Elements:
 *  submission_nid
 *  student_uid
 *  exercise_nid
 *  rubric_ratings
 *    JSON array. Sample item:
 *     {"rubric_item_nid":"206","comment":"Funny!","comment_rating":"good"}
 *  complete (1/0)
 *  message
 */
function hook_feedback_erased( $feedback_data ) {
  
}


function things_you_can_call() {
  //Erase the feedback data from a submission.
  cyco_exercises_erase_feedback( $submission_nid );
  //How much grading? If no uid, for current user. Returns bunches o' stuff.
  cyco_exercises_get_number_submissions_to_grade($grader_uid = NULL);
  
}
