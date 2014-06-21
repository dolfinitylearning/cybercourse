<?php
/**
 * @file
 * CyberCourse centralized error handler.
 */

/**
 * Contribute to hook_init.
 */
function _cyco_core_error_init() {
  //Add client-side error handling.
  drupal_add_js( 
      drupal_get_path('module', 'cyco_core') . '/custom/js/cyco_core_error_handler.js'
  );
}


/**
 * Add a menu item. 
 * @param type $items
 */
function _cyco_core_error_add_menu_items( &$items ){
  //Client-side error handler callback.
  $items['cyco_handle_client_error'] = array(
    'page callback' => 'cyco_core_client_error',
    'access callback' => TRUE,
    'type' => MENU_CALLBACK,
  );
}

/**
 * Handle an error.
 * @staticvar CycoErrorHandler $error_handler Error handling class.
 * @param string $explanation Why? Oh, god, WHY?
 */
function cyco_core_handle_error( $explanation = 'Something bad.' ) {
  static $error_handler = NULL;
  if ( is_null($error_handler) ) {
    $error_handler = new CycoErrorHandler();
  }
  $error_handler->reportError( $explanation );
}

/**
 * Handle a services error. Message has to go back to client, as well 
 * as being recorded on server.
 * @staticvar CycoErrorHandler $error_handler Error handling class.
 * @param string $explanation Why? Oh, god, WHY?
 */
function cyco_core_handle_services_error( $explanation = 'Something bad.' ) {
  static $error_handler = NULL;
  if ( is_null($error_handler) ) {
    $error_handler = new CycoErrorHandler();
  }
  $error_handler->servicesError( $explanation );
}

/**
 * Implements hook_js_alter().
 */
function cyco_core_js_alter(&$javascript) {
  //Make sure that JS error handling code is included.
  global $base_url;
  $path = drupal_get_path('module', 'cyco_core') 
        . '/custom/js/cyco_core_error_handler.js';
  $javascript[$path] = array(
    'data' => $base_url. '/' . $path,
    'scope' => 'header',
    'group' => 'JS_LIBRARY',
    'every_page' => TRUE,
    'type' => 'file',
    'cache' => TRUE,
    'weight' => 0,
    'preprocess' => 1,
    'defer' => 0,
  );
}

/**
 * Error handler for CyberCourse.
 *
 * @author mathieso
 */
class CycoErrorHandler {
  //Template to put error message in.
  private $template = 
      "**ERROR**<br><br>Please <a href=\"https://cybercour.se/report-error\" 
        target=\"_blank\">report</a> the error";
  public function __construct() {
    //Nothing to do.
  }

  /**
   * Create an error message.
   * @param string $explanation What happened.
   * @return string Error message.
   */
  private function makeMessage( $explanation = 'Something bad.' ) {
    //Insert into template.
    $message = str_replace($this->template, '**ERROR**', $explanation);
    return $message;
  }

  /**
   * Report a services error.
   * @param string $explanation Why? Oh, god, WHY?
   */
  public function servicesError( $explanation = 'Something bad.' ) {
    $message = $this->makeMessage($explanation);
    //Log to DB.
    watchdog('CyberCourse', $message);
    //Return to client.
    if (function_exists( 'services_error' ) ) {
      services_error( $message );
    }
    else {
      $explanation = 'ServicesError: Error reporting following error '
          . 'because services_error does not exist: ' . $explanation;
      $this->reportError( $explanation );
    }
  }
  
  /**
   * Report an error.
   * @param string $explanation Why? Oh, god, WHY?
   * @param boolean $setMessage Whether to call drupal_set_message. Want to 
   *   suppress it when processing client-side errors, otherwise the message
   *   message will show on the wrong page (the next one, not the 
   *   one with the error). 
   */
  public function reportError( $explanation = 'Something bad.', $setMessage = TRUE ) {
    $message = $this->makeMessage($explanation);
    //Log to DB.
    watchdog('CyberCourse', $message);
    if ( $setMessage ) {
      //Show user.
      drupal_set_message( $message, 'warning' );
    }
  }
  
}
