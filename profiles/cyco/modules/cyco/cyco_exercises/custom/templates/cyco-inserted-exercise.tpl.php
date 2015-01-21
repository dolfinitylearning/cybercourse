<?php
/**
 * @file
 * cybercourse-inserted-exercise.tpl.php
 *
 * Template for an exercise inserted in another page.
 * 
 * Variables
 * - $exercise_nid: Nid of the exercise. Used by JS code.
 * - $title: The title of the exercise.
 * - $body: Exercise details.
 * - $labeled_links: array of data about link to show. Format of each entry:
 *    'version_label' => Which version. Usually MT.
 *    'status_message' => Whether submitted, has feedback, etc. Often MT.
 *    'link' => Rendered link.
 * - $too_bad_so_sad_message: Message telling user s/he can't do stuff.
 */
?>
<div class="cyco-inserted-exercise" data-nid="<?php print $exercise_nid; ?>">
  <div class="cyco-inserted-exercise-title">
    Exercise: <?php print $title; ?>
  </div>
  <div class="cyco-inserted-exercise-content">
    <?php print $body; ?>
  </div>
  <?php
  if ( isset($attached_file_links[0]) ) {
    ?>
  <fieldset class="cyco-inserted-exercise-attachments">
    <legend>Attachments</legend>
    <?php
    foreach( $attached_file_links as $link ) {
      print '<p>' . $link . '</p>';
    }
    ?>
  </fieldset>
    <?php
  }
  ?>
  <?php
  if ( $too_bad_so_sad_message ) {
    ?>
    <div class="cyco-inserted-exercise-too-bad">
      <?php print $too_bad_so_sad_message; ?>
    </div>
  <?php }
  else { ?>
  <div class="cyco-submission-links-container" 
       data-nid="<?php print $exercise_nid; ?>">
    <?php //This is completed by JavaScript. The class name cannot change. ?>
  </div>
  <?php } ?>
</div>
