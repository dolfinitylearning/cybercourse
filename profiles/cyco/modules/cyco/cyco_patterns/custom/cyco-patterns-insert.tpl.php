<?php
/** 
Template for displaying a pattern inside a node
 */
?>
<fieldset class="cyco-pattern-insert">
  <legend class="cyco-pattern-insert-legend"><span><?php print t('Pattern'); ?></span></legend>
  <p class="cyco-pattern-insert-title">
    <?php print $title; ?>
  </p>
  <?php if ( $situation ) { ?>
    <div class="cyco-pattern-insert-situation">
      <div class="situation-label"><?php print t('Situation: '); ?></div>
      <div class="situation-description">
        <?php print $situation; ?>
      </div>
    </div>
  <?php } ?>
  <?php if ( $actions ) { ?>
    <div class="cyco-pattern-insert-actions">
      <div class="actions-label"><?php print t('Actions: '); ?></div>
      <div class="actions-description">
        <?php print $actions; ?>
      </div>
    </div>
  <?php } ?>
  <?php if ( $more_link_destination ) { ?>
    <p class="cyco-pattern-insert-more-link">
      <a href="<?php print $more_link_destination; ?>" 
        title="<?php print t('Pattern details'); ?>"><?php print t('More...'); ?></a>
    </p>
  <?php } ?>
</fieldset>

