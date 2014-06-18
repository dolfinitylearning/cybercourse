<?php
/**
 * @file
 * swim_services_definition.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function swim_services_definition_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "services" && $api == "services") {
    return array("version" => "3");
  }
}
