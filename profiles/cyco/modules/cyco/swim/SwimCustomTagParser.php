<?php
/**
 * Description of SwimCustomTagParser
 *
 * @author mathieso
 */

//Set these to big, else regex will send back MT string when the
//content gets too big. 
ini_set('pcre.backtrack_limit', 10000000);
ini_set('pcre.recursion_limit', 10000000);

class SwimCustomTagParser {

  const START_CUSTOM_TAG = '@@cyco';
  //Version of START_CUSTOM_TAG that is escaped, ready for use in regex.
  const START_CUSTOM_TAG_REGEX_ESCAPED = '\@\@cyco';
  const END_CUSTOM_TAG = '/@@cyco';
  const END_CUSTOM_TAG_REGEX_ESCAPED = '\/\@\@cyco';  
  
  protected $custom_tag_definitions = array();
  protected $current_tag_def;
  protected $current_regex;
  
  /**
   * Declare a custom tag.
   * @param string $tag Custom tag, e.g., pseudent.
   * @param string $callback_name Name of the callback function.
   */
  public function declareCustomTag($tag, $callback_name) {
    $this->custom_tag_definitions[] = array(
      'tag' => $tag, 
      'callback' => $callback_name,
    );
  }
  
  public function parse($text) {
    //Call registered custom tag hooks.
    foreach($this->custom_tag_definitions as $def) {
      //Remember tag def being processed.
      $this->current_tag_def = $def;
      //Create the regex to look for.
      $this->current_regex = '/^' . SwimCustomTagParser::START_CUSTOM_TAG_REGEX_ESCAPED 
          . '\s+' . $def['tag'] . '\s+(.*?)\s*\n'
          . '(.*?)'
          . SwimCustomTagParser::END_CUSTOM_TAG_REGEX_ESCAPED . '\s*' . $def['tag'] 
          . '\s*?(\1)+\s*?\n?'
          . '/ism';
      //BAD THING. The regex won't pick up tags with no params. It works in 
      //testing at https://www.myregextester.com/index.php, though.
      $text = preg_replace_callback($this->current_regex, 
          function($matches) {
            //Call the custom tag callback registered earlier.
            $tag_param = $matches[1];
            //Check for collapsed flag and message.
            $collapse_title = '';
            preg_replace_callback('/collapse\s+(.*)/i', 
                function($collapse_match) use ($collapse_title) {
                  $collapse_title = $collapse_match[1];
                  return '';
                }, 
                $tag_param
            );
            $tag_content = $matches[2];
            //Any matches in the inner tag content?
            $matches = preg_match($this->current_regex, $tag_content);
            if ( $matches ) {
              $parser = new SwimCustomTagParser();
              $out = $parser->parse($tag_content);
              $tag_content = $out;
            }
            $result = call_user_func(
                $this->current_tag_def['callback'],
                $tag_param,
                $tag_content
            );
            if ( $collapse_title ) {
              //Wrap in collapse div.
              $result = '<div data-collapse>'
                  . '<p>' . $collapse_title . '</p>'
                  . $result 
              . '</div>';
            }
            return $result;
          }, 
          $text); //End preg_replace_callback call.
    }
    return $text;
  }
}
