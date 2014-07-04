<?php
/**
 * @file
 * cyco-feedback-message.tpl.php
 *
 * Template for feedback message from grader.
 * This is ReST, not HTML.
 * 
 * Variables
 * - $greeting: Greeting, e.g., G'day,
 * - $overall: Overall evaluation.
 * - $comments: Grader comments.
 * - $signature
 */
?>
<?php if ( $greeting ) {
  print $greeting . "\n"; 
} ?>

<?php if ( $overall ) {
  print $overall . "\n";
}  ?>

<?php 
foreach ($comments as $comment) { ?>
* <?php print $comment . "\n"; ?>
<?php } ?>

<?php if ( $signature )  {
  print $signature; 
}
?>

