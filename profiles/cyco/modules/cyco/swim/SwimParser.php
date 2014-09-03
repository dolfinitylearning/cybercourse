<?php
/**
 * Description of SwimParser
 *
 * @author mathieso
 */

$path = '../../../libraries/php-textile/src/Netcarver/Textile/';

require_once $path . 'Parser.php';
require_once $path . 'DataBag.php';
require_once $path . 'Tag.php';

class SwimParser extends \Netcarver\Textile\Parser {
  
  const START_CUSTOM_TAG = '@@cyco';
  //Version of START_CUSTOM_TAG that is escaped, ready for use in regex.
  const START_CUSTOM_TAG_REGEX_ESCAPED = '\@\@cyco';
  const END_CUSTOM_TAG = '/@@';
  const END_CUSTOM_TAG_REGEX_ESCAPED = '\/\@\@';

  //Array of custom tag definitions.
  protected $custom_tag_definitions = array();
  
  //Tag definition being processed.
  protected $current_tag_def;


  /**
   * Constructor. 
   */
  public function __construct() {
    parent::__construct();
    $this
      //Set document output type to HTML 5.
      ->setDocumentType('html5')
      //Ignore line breaks in text.
      ->setLineWrap(FALSE);
    //Call hooks to register custom tags.
    //Expect elements of the form: 
    //  array( 
    //    'tag' => string, 
    //    'callback' => string (function name)
    //  )
    $this->custom_tag_definitions = module_invoke_all('swim_register_custom_tag');
  }
  
  public function parse($text) {
    //Call registered custom tag hooks.
    foreach($this->custom_tag_definitions as $def) {
      //Remember tag def being processed.
      $this->current_tag_def = $def;
      //Create the regex to look for.
      $regex = '/' . SwimParser::START_CUSTOM_TAG_REGEX_ESCAPED . '\s+' 
          . $def['tag'] . '\s+(.*)?\n(.*)?' 
          . SwimParser::END_CUSTOM_TAG_REGEX_ESCAPED 
          . '(\s*)?' . $def['tag'] . '(.*)?\n/is';
      preg_replace_callback('', 'triggerCustomTagCallback', $text);
    }
    parent::parse($text);
  }
  
  protected function triggerCustomTagCallback($matches){
    //Call the custom tag callback registered earlier.
    call_user_func($this->current_tag_def['callback'], $matches);
  }
  
}
