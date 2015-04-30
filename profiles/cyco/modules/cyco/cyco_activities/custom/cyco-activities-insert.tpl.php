<?php
/** 
Template for displaying an activity inside a node
 */
?>
<fieldset class="cyco-activity-insert">
  <legend class="cyco-activity-insert-legend"><span><?php print t('Activity'); ?></span></legend>
  <p class="cyco-activity-insert-title">
    <?php print $title; ?>
  </p>
  <?php if ( $summary ) { ?>
    <div class="cyco-activity-insert-summary">
      <div class="summary-description">
        <?php print $summary; ?>
      </div>
    </div>
  <?php } ?>
  <?php if ( $keyword_links_rendered ) { ?>
    <p class="cyco-activity-insert-keywords-container">
      <span class="keywords-label"><?php print t('Keywords: '); ?></span>
      <?php print $keyword_links_rendered; ?>
    </p>
  <?php } ?>
  <?php if ( $more_link_destination ) { ?>
    <p class="cyco-activity-insert-more-link">
      <a href="<?php print $more_link_destination; ?>" 
        title="<?php print t('Activity details'); ?>"><?php print t('More...'); ?></a>
    </p>
  <?php } ?>
</fieldset>

