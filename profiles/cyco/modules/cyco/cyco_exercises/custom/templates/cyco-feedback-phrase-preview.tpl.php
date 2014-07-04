<?php
/**
 * @file
 * cybercourse-feedback-phrase-preview.tpl.php
 *
 * Template for previewing feedback phrases.
 * 
 * Variables
 * - $phrases_groups: Groups of phrases.
 * - $phrase_groups[]['group_title']: The title of the group.
 * - $phrase_groups[]['phrases']: array of phrases in the group.
 */
?>
<div class="cyco-feedback-phrases-preview-container">
  <p>Here are the feedback phrases, with sample student names inserted as needed.</p>
  <?php foreach( $phrases_groups as $phrase_group ) { ?>
  <div>
    <p>
      <?php print $phrase_group['group_title']; ?>:
    </p>
    <ul>
      <?php 
      foreach ($phrase_group['phrases'] as $key => $phrase) { 
        ?>
      <li>
        <?php 
        print token_replace( $phrase ); 
        ?>
      </li>
      <?php } ?>
    </ul>
  </div>
  <?php } ?>
</div>
