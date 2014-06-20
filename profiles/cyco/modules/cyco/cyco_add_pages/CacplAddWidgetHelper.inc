<?php
/**
 * Collects data about things user can add - kids and siblings.
 *
 * @author mathieso
 */
class CacplAddWidgetHelper {
  
  //Array of descriptions of things that can be added,
  //and links to them.
  protected $add_info = array();
  
  public function appendAddData( $description, $link ) {
    if ( ! $description ) {
      throw new Exception('CacplAddWidgetHelper: appendAddData: no description');
    }
    if ( ! $link ) {
      throw new Exception('CacplAddWidgetHelper: appendAddData: no link');
    }
    $this->add_info[] = array(
      'description' => $description,
      'link' => $link,
    );
  }
  
  public function getAddData() {
    return $this->add_info;
  }
  
}

