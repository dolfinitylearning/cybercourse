<?php

/**
 * Implements hook_features_export_options().
 */
function menu_item_visibility_features_export_options() {
  $options = array();
  $query = db_select("menu_links_visibility_role", 'vr');
  $query->join('menu_links','ml','ml.mlid = vr.mlid');
  $result = $query->fields('ml', array('menu_name', 'link_title') )
    ->fields('vr', array('mlid'))
    ->execute();
  foreach ($result as $row) {
    $link = menu_link_load($row->mlid);
    $identifier = menu_links_features_identifier($link);
    $options[$identifier] = "{$row->menu_name}: {$row->link_title}";
  }
  return $options;
}




/**
 * Implements hook_features_export().
 */
function menu_item_visibility_features_export($data, &$export, $module_name = '') {
  $export['dependencies']['menu_item_visibility'] = 'menu_item_visibility';

  foreach ($data as $identifier) {
    $export['features']['menu_item_visibility'][$identifier] = $identifier;
  }
  return array();
}

/**
 * Implements hook_features_export_render().
 */
function menu_item_visibility_features_export_render($module_name, $data) {
  $items = array();

  foreach ($data as $identifier) {
    if ($link = features_menu_link_load($identifier)) {
      $values = array();
      $results = db_query("SELECT rid FROM {menu_links_visibility_role} WHERE mlid = :mlid", array(':mlid' => $link['mlid']) );
      foreach ($results as $row) {
        $values[] = $row;
      }
      $items[$identifier] = $values;
    }
  }
  $code = "  \$items = " . features_var_export($items, '  ') . ";\n";
  $code .= '  return $items;';
  return array('menu_item_visibility_export_fields' => $code);
}


/**
 * Implements hook_features_revert().
 */
function menu_item_visibility_features_revert($module) {
  $table = 'menu_links_visibility_role';
  $defaults = features_get_default('menu_item_visibility', $module);

  // Revert.
  foreach ($defaults as $identifier => $object) {
    _menu_item_visibility_save_field($object, $identifier);
  }
}

/**
 * Implements hook_features_rebuild().
 */
function menu_item_visibility_features_rebuild($module) {
  menu_item_visibility_features_revert($module);
}

function _menu_item_visibility_save_field($arr, $identifier) {
  if ($link = features_menu_link_load($identifier)) {

    foreach ($arr as $field_data) {
      $field_data['mlid'] = $link['mlid'];
      if (!isset($field_data['rid'])) {
        $field_data['rid'] = '';
      }
      else {
        $field_data = (object)$field_data;
        if (!db_query("SELECT * FROM {menu_links_visibility_role} WHERE mlid = :mlid and rid = :rid", array(':mlid' => $field_data->mlid, ':rid' => $field_data->rid))->fetchObject() )  {
          drupal_write_record('menu_links_visibility_role', $field_data);
        }
        else {
          drupal_write_record('menu_links_visibility_role', $field_data, array('mlid','rid'));
        }

      }
    }

  }
}
