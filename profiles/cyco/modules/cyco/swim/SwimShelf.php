<?php

/*
 * Let plugins shelve content that SWIM will insert in the right spot
 * after Textile processing.
 * 
 * Use case: don't want Textile to process HTML.
 */

/**
 * Selve content, restore after Textile processing.
 *
 * @author mathieso
 */
class SwimShelf {
  const MARKER = 'swim_shelf';
  const MARKER_REGEX = 'swim\_shelf';
    //Version of marker to use in regex.
  
  //Where things are stored.
  protected $shelf = array();
  
  private static $_instance = null;
  
  /**
   * Protected constructor to prevent creating a new instance of the
   * *Singleton* via the `new` operator from outside of this class.
   */
  protected function __construct() {
  }
  
  // A method to get our singleton instance
  public static function getInstance() {
    if (!(self::$_instance instanceof SwimShelf)) {
      self::$_instance = new SwimShelf();
    }
    return self::$_instance;
  }

  /**
   * Shelf content, for later restoration.
   * @param type $content Content to shelve.
   * @return string Marker that caller should insert in its output stream.
   */
  public function shelve( $content ) {
    $shelf_index = sizeof($this->shelf);
    $this->shelf[ $shelf_index ] = $content;
    $shelf_marker = 
          '<notextile>' 
        .   SwimShelf::MARKER . ' ' . $shelf_index 
        . '</notetextile>';
    return $shelf_marker;
  }
  
  /**
   * Restore shelved content.
   * @param type $content Content with shelf markers.
   * @return string Content with markers replaced by shelf contents.
   */
  public function restore( $content ) {
    $regex = '/' . SwimShelf::MARKER_REGEX . '\s(\d+)?/';
    $content = preg_replace_callback($regex, 
        function($matches) {
          $shelf_index = $matches[1];
          return $this->shelf[ $shelf_index ];
        }, 
        $content); //End preg_replace_callback call.
    return $content;
  }
}
