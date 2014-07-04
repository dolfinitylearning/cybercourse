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
 */
?>
<div class="cyco-inserted-exercise" data-nid="<?php print $exercise_nid; ?>">
  <div class="cyco-inserted-exercise-title">
    Exercise: <?php print $title; ?>
  </div>
  <div class="cyco-inserted-exercise-content">
    <?php print $body; ?>
  </div>
  <div class="cyco-inserted-exercise-links-container">
    <?php //This is complete by JavaScript. The class name cannot change. ?>
  </div>
</div>
