<?php
/**
 * @file
 * cyco_pseudents.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function cyco_pseudents_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_enable_revisions_page_node_pseudent_pose';
  $strongarm->value = 1;
  $export['diff_enable_revisions_page_node_pseudent_pose'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_show_preview_changes_node_pseudent_pose';
  $strongarm->value = 0;
  $export['diff_show_preview_changes_node_pseudent_pose'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_view_mode_preview_node_pseudent_pose';
  $strongarm->value = 'full';
  $export['diff_view_mode_preview_node_pseudent_pose'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__pseudent_pose';
  $strongarm->value = array(
    'view_modes' => array(
      'teaser' => array(
        'custom_settings' => TRUE,
      ),
      'full' => array(
        'custom_settings' => FALSE,
      ),
      'rss' => array(
        'custom_settings' => FALSE,
      ),
      'search_index' => array(
        'custom_settings' => FALSE,
      ),
      'search_result' => array(
        'custom_settings' => FALSE,
      ),
      'print' => array(
        'custom_settings' => FALSE,
      ),
      'diff_standard' => array(
        'custom_settings' => FALSE,
      ),
      'token' => array(
        'custom_settings' => FALSE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '0',
        ),
        'path' => array(
          'weight' => '7',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__pseudent_pose'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_pseudent_pose';
  $strongarm->value = array();
  $export['menu_options_pseudent_pose'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_pseudent_pose';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_pseudent_pose'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_pseudent_pose';
  $strongarm->value = array(
    0 => 'status',
    1 => 'revision',
  );
  $export['node_options_pseudent_pose'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_pseudent_pose';
  $strongarm->value = '0';
  $export['node_preview_pseudent_pose'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_pseudent_pose';
  $strongarm->value = 0;
  $export['node_submitted_pseudent_pose'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_pseudent_pose_pattern';
  $strongarm->value = 'pseudent-pose/[node:title]';
  $export['pathauto_node_pseudent_pose_pattern'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_taxonomy_term_pseudent_categories_pattern';
  $strongarm->value = '';
  $export['pathauto_taxonomy_term_pseudent_categories_pattern'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pseudents_poses_preview_data';
  $strongarm->value = array(
    'jeremy_big_smile' => array(
      'nid' => 308,
      'internal_name' => 'jeremy_big_smile',
      'title' => 'Jeremy big smile',
      'url' => '/sites/default/files/cycourse/library/pseudents/jeremy-big-smile.png',
      'caption' => 'Jeremy',
      'categories' => array(
        8 => 'Jeremy',
        13 => 'Positive',
        16 => 'Teagan\'s character',
      ),
    ),
    'jeremy_big_smile2' => array(
      'nid' => 311,
      'internal_name' => 'jeremy_big_smile2',
      'title' => 'Jeremy big smile 2',
      'url' => '/sites/default/files/cycourse/library/pseudents/jeremy-nervous-smile.png',
      'caption' => 'Jeremy',
      'categories' => array(
        8 => 'Jeremy',
        13 => 'Positive',
        16 => 'Teagan\'s character',
      ),
    ),
    'jeremy_blank' => array(
      'nid' => 307,
      'internal_name' => 'jeremy_blank',
      'title' => 'Jeremy blank',
      'url' => '/sites/default/files/cycourse/library/pseudents/jeremy-base.png',
      'caption' => 'Jeremy',
      'categories' => array(
        17 => 'Blank face',
        8 => 'Jeremy',
        16 => 'Teagan\'s character',
      ),
    ),
    'jeremy_explaining' => array(
      'nid' => 309,
      'internal_name' => 'jeremy_explaining',
      'title' => 'Jeremy explaining',
      'url' => '/sites/default/files/cycourse/library/pseudents/jeremy-explaining.png',
      'caption' => 'Jeremy',
      'categories' => array(
        8 => 'Jeremy',
        13 => 'Positive',
        16 => 'Teagan\'s character',
      ),
    ),
    'jeremy_irritated' => array(
      'nid' => 310,
      'internal_name' => 'jeremy_irritated',
      'title' => 'Jeremy irritated',
      'url' => '/sites/default/files/cycourse/library/pseudents/jeremy-irritated.png',
      'caption' => 'Jeremy',
      'categories' => array(
        8 => 'Jeremy',
        15 => 'Negative',
        16 => 'Teagan\'s character',
      ),
    ),
    'jeremy_smile' => array(
      'nid' => 312,
      'internal_name' => 'jeremy_smile',
      'title' => 'Jeremy smile',
      'url' => '/sites/default/files/cycourse/library/pseudents/jeremy-smile_0.png',
      'caption' => 'Jeremy',
      'categories' => array(
        8 => 'Jeremy',
        13 => 'Positive',
        16 => 'Teagan\'s character',
      ),
    ),
    'jeremy_surprised' => array(
      'nid' => 313,
      'internal_name' => 'jeremy_surprised',
      'title' => 'Jeremy surprised',
      'url' => '/sites/default/files/cycourse/library/pseudents/jeremy-surprised.png',
      'caption' => 'Jeremy',
      'categories' => array(
        8 => 'Jeremy',
        14 => 'Neutral',
        16 => 'Teagan\'s character',
      ),
    ),
    'jeremy_uh_oh' => array(
      'nid' => 314,
      'internal_name' => 'jeremy_uh_oh',
      'title' => 'Jeremy uh oh',
      'url' => '/sites/default/files/cycourse/library/pseudents/jeremy-uh-oh.png',
      'caption' => 'Jeremy',
      'categories' => array(
        8 => 'Jeremy',
        15 => 'Negative',
        16 => 'Teagan\'s character',
      ),
    ),
    'klaus_angry' => array(
      'nid' => 315,
      'internal_name' => 'klaus_angry',
      'title' => 'Klaus angry',
      'url' => '/sites/default/files/cycourse/library/pseudents/klaus-angry.png',
      'caption' => 'Klaus',
      'categories' => array(
        9 => 'Klaus',
        15 => 'Negative',
        16 => 'Teagan\'s character',
      ),
    ),
    'klaus_blank' => array(
      'nid' => 316,
      'internal_name' => 'klaus_blank',
      'title' => 'Klaus blank',
      'url' => '/sites/default/files/cycourse/library/pseudents/klaus-base.png',
      'caption' => 'Klaus',
      'categories' => array(
        17 => 'Blank face',
        9 => 'Klaus',
        14 => 'Neutral',
        16 => 'Teagan\'s character',
      ),
    ),
    'klaus_neutral' => array(
      'nid' => 317,
      'internal_name' => 'klaus_neutral',
      'title' => 'Klaus neutral',
      'url' => '/sites/default/files/cycourse/library/pseudents/klaus-neutral.png',
      'caption' => 'Klaus',
      'categories' => array(
        9 => 'Klaus',
        14 => 'Neutral',
        16 => 'Teagan\'s character',
      ),
    ),
    'klaus_sad' => array(
      'nid' => 318,
      'internal_name' => 'klaus_sad',
      'title' => 'Klaus sad',
      'url' => '/sites/default/files/cycourse/library/pseudents/klaus-sad.png',
      'caption' => 'Klaus',
      'categories' => array(
        9 => 'Klaus',
        15 => 'Negative',
        16 => 'Teagan\'s character',
      ),
    ),
    'klaus_scared' => array(
      'nid' => 319,
      'internal_name' => 'klaus_scared',
      'title' => 'Klaus scared',
      'url' => '/sites/default/files/cycourse/library/pseudents/klaus-scared.png',
      'caption' => 'Klaus',
      'categories' => array(
        9 => 'Klaus',
        15 => 'Negative',
        16 => 'Teagan\'s character',
      ),
    ),
    'klaus_small_smile' => array(
      'nid' => 320,
      'internal_name' => 'klaus_small_smile',
      'title' => 'Klaus small smile',
      'url' => '/sites/default/files/cycourse/library/pseudents/klaus-small-smile.png',
      'caption' => 'Klaus',
      'categories' => array(
        9 => 'Klaus',
        13 => 'Positive',
        16 => 'Teagan\'s character',
      ),
    ),
    'klaus_smile' => array(
      'nid' => 321,
      'internal_name' => 'klaus_smile',
      'title' => 'Klaus smile',
      'url' => '/sites/default/files/cycourse/library/pseudents/klaus-smile.png',
      'caption' => 'Klaus',
      'categories' => array(
        9 => 'Klaus',
        13 => 'Positive',
        16 => 'Teagan\'s character',
      ),
    ),
    'lily_big_smile' => array(
      'nid' => 323,
      'internal_name' => 'lily_big_smile',
      'title' => 'Lily big smile',
      'url' => '/sites/default/files/cycourse/library/pseudents/lily-big-smile.png',
      'caption' => 'Lily',
      'categories' => array(
        10 => 'Lily',
        13 => 'Positive',
        16 => 'Teagan\'s character',
      ),
    ),
    'lily_blank' => array(
      'nid' => 322,
      'internal_name' => 'lily_blank',
      'title' => 'Lily blank',
      'url' => '/sites/default/files/cycourse/library/pseudents/lily-base.png',
      'caption' => 'Lily',
      'categories' => array(
        17 => 'Blank face',
        10 => 'Lily',
        14 => 'Neutral',
        16 => 'Teagan\'s character',
      ),
    ),
    'lily_frowning' => array(
      'nid' => 324,
      'internal_name' => 'lily_frowning',
      'title' => 'Lily frowning',
      'url' => '/sites/default/files/cycourse/library/pseudents/lily-frowning.png',
      'caption' => 'Lily',
      'categories' => array(
        10 => 'Lily',
        15 => 'Negative',
        16 => 'Teagan\'s character',
      ),
    ),
    'lily_irritated' => array(
      'nid' => 325,
      'internal_name' => 'lily_irritated',
      'title' => 'Lily irritated',
      'url' => '/sites/default/files/cycourse/library/pseudents/lily-irritated.png',
      'caption' => 'Lily',
      'categories' => array(
        10 => 'Lily',
        15 => 'Negative',
        16 => 'Teagan\'s character',
      ),
    ),
    'lily_sad' => array(
      'nid' => 327,
      'internal_name' => 'lily_sad',
      'title' => 'Lily sad',
      'url' => '/sites/default/files/cycourse/library/pseudents/lily-sad.png',
      'caption' => 'Lily',
      'categories' => array(
        10 => 'Lily',
        15 => 'Negative',
        16 => 'Teagan\'s character',
      ),
    ),
    'lilly_smile1' => array(
      'nid' => 326,
      'internal_name' => 'lilly_smile1',
      'title' => 'Lily smile 1',
      'url' => '/sites/default/files/cycourse/library/pseudents/lily-neutral.png',
      'caption' => 'Lily',
      'categories' => array(
        10 => 'Lily',
        13 => 'Positive',
        16 => 'Teagan\'s character',
      ),
    ),
    'lily_smile2' => array(
      'nid' => 328,
      'internal_name' => 'lily_smile2',
      'title' => 'Lily smile 2',
      'url' => '/sites/default/files/cycourse/library/pseudents/lily-smile.png',
      'caption' => 'Lily',
      'categories' => array(
        10 => 'Lily',
        13 => 'Positive',
        16 => 'Teagan\'s character',
      ),
    ),
    'lily_yeesh' => array(
      'nid' => 329,
      'internal_name' => 'lily_yeesh',
      'title' => 'Lily yeesh',
      'url' => '/sites/default/files/cycourse/library/pseudents/lily-yeesh.png',
      'caption' => 'Lily',
      'categories' => array(
        10 => 'Lily',
        15 => 'Negative',
        16 => 'Teagan\'s character',
      ),
    ),
    'simon_angry' => array(
      'nid' => 330,
      'internal_name' => 'simon_angry',
      'title' => 'Simon angry',
      'url' => '/sites/default/files/cycourse/library/pseudents/simon-angry.png',
      'caption' => 'Simon',
      'categories' => array(
        15 => 'Negative',
        11 => 'Simon',
        16 => 'Teagan\'s character',
      ),
    ),
    'simon_big_smile' => array(
      'nid' => 332,
      'internal_name' => 'simon_big_smile',
      'title' => 'Simon big smile',
      'url' => '/sites/default/files/cycourse/library/pseudents/simon-big-smile.png',
      'caption' => 'Simon',
      'categories' => array(
        13 => 'Positive',
        11 => 'Simon',
        16 => 'Teagan\'s character',
      ),
    ),
    'simon_blank' => array(
      'nid' => 331,
      'internal_name' => 'simon_blank',
      'title' => 'Simon blank',
      'url' => '/sites/default/files/cycourse/library/pseudents/simon-base.png',
      'caption' => 'Simon',
      'categories' => array(
        17 => 'Blank face',
        14 => 'Neutral',
        11 => 'Simon',
        16 => 'Teagan\'s character',
      ),
    ),
    'simon_frown' => array(
      'nid' => 333,
      'internal_name' => 'simon_frown',
      'title' => 'Simon frown',
      'url' => '/sites/default/files/cycourse/library/pseudents/simon-frown.png',
      'caption' => 'Simon',
      'categories' => array(
        15 => 'Negative',
        11 => 'Simon',
        16 => 'Teagan\'s character',
      ),
    ),
    'simon_small_frown' => array(
      'nid' => 335,
      'internal_name' => 'simon_small_frown',
      'title' => 'Simon small frown',
      'url' => '/sites/default/files/cycourse/library/pseudents/simon-quizzical.png',
      'caption' => 'Simon',
      'categories' => array(
        15 => 'Negative',
        11 => 'Simon',
        16 => 'Teagan\'s character',
      ),
    ),
    'simon_smile' => array(
      'nid' => 336,
      'internal_name' => 'simon_smile',
      'title' => 'Simon smile',
      'url' => '/sites/default/files/cycourse/library/pseudents/simon-smile.png',
      'caption' => 'Simon',
      'categories' => array(
        13 => 'Positive',
        11 => 'Simon',
        16 => 'Teagan\'s character',
      ),
    ),
    'simon_thinking' => array(
      'nid' => 334,
      'internal_name' => 'simon_thinking',
      'title' => 'Simon thinking',
      'url' => '/sites/default/files/cycourse/library/pseudents/simon-neutral.png',
      'caption' => 'Simon',
      'categories' => array(
        14 => 'Neutral',
        11 => 'Simon',
        16 => 'Teagan\'s character',
      ),
    ),
    'tara_annoyed' => array(
      'nid' => 338,
      'internal_name' => 'tara_annoyed',
      'title' => 'Tara annoyed',
      'url' => '/sites/default/files/cycourse/library/pseudents/tara-annoyed.png',
      'caption' => 'Tara',
      'categories' => array(
        15 => 'Negative',
        12 => 'Tara',
        16 => 'Teagan\'s character',
      ),
    ),
    'tara_blank' => array(
      'nid' => 339,
      'internal_name' => 'tara_blank',
      'title' => 'Tara blank',
      'url' => '/sites/default/files/cycourse/library/pseudents/tara-base.png',
      'caption' => 'Tara',
      'categories' => array(
        17 => 'Blank face',
        14 => 'Neutral',
        12 => 'Tara',
        16 => 'Teagan\'s character',
      ),
    ),
    'tara_frown' => array(
      'nid' => 342,
      'internal_name' => 'tara_frown',
      'title' => 'Tara frown',
      'url' => '/sites/default/files/cycourse/library/pseudents/tara-sad.png',
      'caption' => 'Tara',
      'categories' => array(
        15 => 'Negative',
        12 => 'Tara',
        16 => 'Teagan\'s character',
      ),
    ),
    'tara_neutral' => array(
      'nid' => 341,
      'internal_name' => 'tara_neutral',
      'title' => 'Tara neutral',
      'url' => '/sites/default/files/cycourse/library/pseudents/tara-not-interested.png',
      'caption' => 'Tara',
      'categories' => array(
        14 => 'Neutral',
        12 => 'Tara',
        16 => 'Teagan\'s character',
      ),
    ),
    'tara_smile1' => array(
      'nid' => 340,
      'internal_name' => 'tara_smile1',
      'title' => 'Tara smile 1',
      'url' => '/sites/default/files/cycourse/library/pseudents/tara-confident.png',
      'caption' => 'Tara',
      'categories' => array(
        13 => 'Positive',
        12 => 'Tara',
        16 => 'Teagan\'s character',
      ),
    ),
    'tara_smile2' => array(
      'nid' => 343,
      'internal_name' => 'tara_smile2',
      'title' => 'Tara smile 2',
      'url' => '/sites/default/files/cycourse/library/pseudents/tara-smile.png',
      'caption' => 'Tara',
      'categories' => array(
        13 => 'Positive',
        12 => 'Tara',
        16 => 'Teagan\'s character',
      ),
    ),
    'tara_thinking' => array(
      'nid' => 344,
      'internal_name' => 'tara_thinking',
      'title' => 'Tara thinking',
      'url' => '/sites/default/files/cycourse/library/pseudents/tara-thinking.png',
      'caption' => 'Tara',
      'categories' => array(
        14 => 'Neutral',
        12 => 'Tara',
        16 => 'Teagan\'s character',
      ),
    ),
  );
  $export['pseudents_poses_preview_data'] = $strongarm;

  return $export;
}
