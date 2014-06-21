<?php
/**
 * @file
 * cyco_core.services.inc
 */

/**
 * Implements hook_default_services_endpoint().
 */
function cyco_core_default_services_endpoint() {
  $export = array();

  $endpoint = new stdClass();
  $endpoint->disabled = FALSE; /* Edit this to true to make a default endpoint disabled initially */
  $endpoint->api_version = 3;
  $endpoint->name = 'swim';
  $endpoint->server = 'rest_server';
  $endpoint->path = 'swim';
  $endpoint->authentication = array(
    'services' => 'services',
  );
  $endpoint->server_settings = array();
  $endpoint->resources = array(
    'peek' => array(
      'actions' => array(
        'peek' => array(
          'enabled' => '1',
        ),
      ),
    ),
    'swim_help' => array(
      'actions' => array(
        'swimHelp' => array(
          'enabled' => '1',
        ),
      ),
    ),
  );
  $endpoint->debug = 0;
  $export['swim'] = $endpoint;

  return $export;
}
