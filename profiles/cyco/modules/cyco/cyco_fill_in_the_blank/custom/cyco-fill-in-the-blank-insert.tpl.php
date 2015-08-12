<?php
/** 
Template for displaying a fill-in-the-blank quesion inside a node
 */
  ?>
<fieldset class="cyco-fib" 
          data-nid="<?php print $fill_in_the_blank_nid; ?>"
          data-response-type="<?php print $response_type; ?>">
  <legend class="cyco-fib-legend"><span><?php 
    print t('Fill in the blank'); ?></span></legend>
  <p class="cyco-fib-title">
    <?php print $title; ?>
  </p>
  <div class="cyco-fib-body">
    <?php print $body; ?>
  </div>
  <div class="cyco-fib-response-container">
    <?php print t('Your answer') . ':'; ?> 
    <input class="cyco-fib-response" type="text" size="20">
    <button type="button" class="cyco-fib-check-button">
        <?php print t('Check'); ?></button>
    <span class="cyco-fib-ajax-throbber" style="display: none;">
      &nbsp;&nbsp;&nbsp;</span>
  </div>
  <div class="cyco-fib-correct" style="display: none;">
    You got it!
    <div class="cyco-fib-explanation">
      <?php print $explanation; ?>
    </div>  </div>  
  <div class="cyco-fib-hint-container" style="display: none;">
    Sorry, that's not it.
    <div class="cyco-fib-hint">
      <?php print $hints; ?>
    </div>
  </div>
  <div class="cyco-fib-error-container" style="display: none;">
    Something bad happened. Please take a screen shot and send it to someone.
    <div class="cyco-fib-error-message"></div>
  </div>

</fieldset>

