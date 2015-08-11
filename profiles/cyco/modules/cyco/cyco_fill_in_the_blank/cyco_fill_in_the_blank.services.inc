<?php
/**
 * @file
 * cyco_fill_in_the_blank.services.inc
 */

/**
 * Implements hook_default_services_endpoint().
 */
function cyco_fill_in_the_blank_default_services_endpoint() {
  $export = array();

  $endpoint = new stdClass();
  $endpoint->disabled = FALSE; /* Edit this to true to make a default endpoint disabled initially */
  $endpoint->api_version = 3;
  $endpoint->name = 'fill_in_the_blank';
  $endpoint->server = 'rest_server';
  $endpoint->path = 'fill_in_the_blank';
  $endpoint->authentication = array(
    'services' => 'services',
  );
  $endpoint->server_settings = array();
  $endpoint->resources = array(
    'fill_in_the_blank' => array(
      'actions' => array(
        'check' => array(
          'enabled' => '1',
        ),
      ),
    ),
  );
  $endpoint->debug = 0;
  $export['fill_in_the_blank'] = $endpoint;

  return $export;
}
