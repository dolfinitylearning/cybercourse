<?php
/**
 * Markdown parser for SWIM fields. 
 *
 * @author mathieso
 */
$parser_path = DRUPAL_ROOT . '/profiles/cyco/libraries/cebe/markdown';

require_once $parser_path . '/Parser.php';
require_once $parser_path . '/Markdown.php';
require_once $parser_path . '/block/TableTrait.php';
require_once $parser_path . '/MarkdownExtra.php';

class SwimMarkdown extends \cebe\markdown\MarkdownExtra {
  
  const START_CUSTOM_TAG = '@@cyco';
  //Version of START_CUSTOM_TAG that is escaped, ready for use in regex.
  const START_CUSTOM_TAG_REGEX_ESCAPED = '\@\@cyco';
  const END_CUSTOM_TAG = '/@@';
  const END_CUSTOM_TAG_REGEX_ESCAPED = '\/\@\@';
  
  public function __construct() {
    $this->html5 = true;
  }
  
  /**
   * Find the next end custom tag marker.
   * 
   * This does not allow for nested tags.
   * 
   * @param array $lines Lines in the content.
   * @param int $start_line Where to start looking.
   * @return int Line with the end tag, or NULL if not found.
   */
  public static function findEndCustomTag( $lines, $start_line ) { 
    $line_to_test = $start_line;
    while ( $line_to_test < sizeof($lines) ) {
      if (strstr($lines[$line_to_test], SwimMarkdown::END_CUSTOM_TAG) !== FALSE ) {
        return $line_to_test;
      }
      $line_to_test++;
    }
    return NULL;
  }
  
  protected function identifyLine($lines, $current) {
    if (
      substr($lines[$current], 0, strlen(SwimMarkdown::START_CUSTOM_TAG)) 
        == SwimMarkdown::START_CUSTOM_TAG) {
      //Found a custom tag.
      return 'customTag';
    }
    return parent::identifyLine($lines, $current);
  }

  protected function consumeCustomTag($lines, $current_line_number) {
    $current_line = $lines[$current_line_number];
    $matches = array();
    preg_match_all('/' . SwimMarkdown::START_CUSTOM_TAG_REGEX_ESCAPED . '\s+(\S+)?\s*(.*)$/im', $current_line, $matches);
    //$matches[0] is the entire custom tag with arguments.
    //$matches[1] is the custom tag.
    //$matches[2] is the arg string.

    if ( ! isset( $matches[1][0] ) ) {
      throw new Exception('SwimMarkdown: custom tag regex fail. current_line: '
          . $current_line);
    }
    //Prep arguments object.
    $args = new stdClass();
    $args->tag = $matches[1][0];
    $args->args = $matches[2][0];
    $args->content = $lines;
    $args->current_line = $current_line_number;
    //Trigger other modules' translators.
    drupal_alter( 'swim_markdown2html_' . $args->tag, $args );
    //Pass on results.
    $block = [
      'type' => 'customTag',
      'content' => array_slice(
          $lines, 
          $current_line_number, 
          $args->current_line - $current_line_number
      ),
      'replacement_content' => 
        isset( $args->replacement_content )
          ? $args->replacement_content
        : '',
    ];
    return [$block, $args->current_line];
  }
    
  protected function renderCustomTag($block) {
    return $block['replacement_content'];
  }
}