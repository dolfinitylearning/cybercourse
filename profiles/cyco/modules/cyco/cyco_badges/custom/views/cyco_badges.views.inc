<?php
/**
 * @file
 * Adds display fields for Views.
 */

include_once realpath(dirname(__FILE__)) . '/cyco_badges_has_user_earned_badge.inc';
include_once realpath(dirname(__FILE__)) . '/cyco_badges_user_badge_image.inc';

/**
 * Implements hook_views_data().
 */
function cyco_badges_views_data_alter(&$data) {
  $data['cyco_badges']['table']['group'] = t('Cyco badges');
  $data['cyco_badges']['table']['join'] = array(
    // #global is a special flag which lets a table appear all the time.
    '#global' => array(),
  );
  $data['cyco_badges']['has_user_earned_badge'] = array(
    'title' => t('Has the current user earned the badge?'),
    'help' => t('Show whether the current user has earned the badge or not.'),
    'field' => array(
      'handler' => 'cyco_badges_handler_has_user_earned_badge',
    ),
  );
  $data['cyco_badges']['badge_image_for_current_user'] = array(
    'title' => t('Badge'),
    'help' => t('Show the badge image for the current user (locked or not).'),
    'field' => array(
      'handler' => 'cyco_badges_user_badge_image',
    ),
  );
}

