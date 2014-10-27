<?php

/*
 * Class to help debug installations.
 */

class CycoInstallDebug {
  public $debug = FALSE;
  public $path;

  public static function getInstance() {
    static $instance = null;
    if (null === $instance) {
      $instance = new CycoInstallDebug();
    }
    return $instance;
  }

  protected function __construct() {
    $this->path = dirname(__FILE__) . '/install_log.html';
  }

  public function output($message) {
    if ( $this->debug ) {
      $caller_info = '';
      $trace = debug_backtrace();
      $caller = $trace[1];
      $caller_info .= "Called by {$caller['function']}";
      if (isset($caller['line'])) {
        $caller_info .= " at line {$caller['line']}";
      }
      if (isset($caller['file'])) {
        $caller_info .= " in file {$caller['file']}";
      }
      file_put_contents(
          $this->path, 
          $caller_info . "<br>\n" . $message . "<br>\n<br>\n", 
          FILE_APPEND
      );
    }
  }

}
