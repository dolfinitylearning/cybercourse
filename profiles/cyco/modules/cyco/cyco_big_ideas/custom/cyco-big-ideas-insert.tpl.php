<?php
/** 
Template for displaying a big idea inside a node
 */
?>
<fieldset class="cyco-big-idea-insert">
  <legend class="cyco-big-idea-insert-legend"><span><?php print t('Big Idea'); ?></span></legend>
  <p class="cyco-big-idea-insert-title">
    <?php print $title; ?>
  </p>
  <?php if ( $summary ) { ?>
    <div class="cyco-big-idea-insert-summary">
      <div class="summary-description">
        <?php print $summary; ?>
      </div>
    </div>
  <?php } ?>
  <?php if ( $keyword_links_rendered ) { ?>
    <p class="cyco-big-idea-insert-keywords-container">
      <span class="keywords-label"><?php print t('Keywords: '); ?></span>
      <?php print $keyword_links_rendered; ?>
    </p>
  <?php } ?>
  <?php if ( $more_link_destination ) { ?>
    <p class="cyco-big-idea-insert-more-link">
      <a href="<?php print $more_link_destination; ?>" 
        title="<?php print t('Big Idea details'); ?>"><?php print t('More...'); ?></a>
    </p>
  <?php } ?>
</fieldset>

