<?php

/**
 * @file
 * API documentation for SWIM field type.
 */

/**
 * Render a SWIM field using a specified format.
 * @param stdClass $entity Entity containing the field.
 * @param string $field_name Field name, e.g., field_body.
 * @param string $format Format: 
 *  default - main.
 *  summary - summary.
 *  summary-or-trimmed - summary if not MT, else trimmed main.
 * @param integer $trim_length Trim length.
 * @param string $lang Language.
 * @param integer $delta Delta, i.e., which value in a multivalued field.
 * @return string Rendered content.
 */
function swim_render_field( $entity, $field_name, $format = 'default', 
    $trim_length = 600, $lang = LANGUAGE_UNKNOWN, $delta = 0 ) {
}

/**
 * Translate SWIM content into HTML.
 * @param string $rest ReST
 * @return string HTML
 */
function swim_rest2html( $rest ) {
}

/**
 * Return info about CKEditor plugins to use.
 * For more than one, return array of (name, path) arrays.
 * The outer array will be flattened (I think!).
 * See pseudent module for an example.
 */
function hook_swim_load_ck_plugins() {
  return array(
    'name' => 'plugin_name',
    'path' => 'path to plugin',
  );
}

/**
 * Add own client-side stuff. JS, CSS, sttings.
 * See pseudent module for an example.
 * 
 * You might want to ensure that this runs only once per page, to avoid
 * strange Drupal array flatenning behavior. See example below.
 */
function hook_swim_add_client_stuff() {
  //Only run this once per page.
  static $already_added = FALSE;
  if ( $already_added ) {
    return;
  }
  $already_added = TRUE;
  /* More awesomeness ... */
}

/**
 * Parse $content (from CKEditor), and replace target tags
 * with ReST. Usually some regex. 
 * @param string $content Content to change.
 * See pseudent and authornote modules for examples.
 */
function hook_swim_ckhtml_2_directive_alter( &$content ) {
  
}

/**
 * Translate intermediate (betwixt) markup in $content (as inserted by
 * custom ReST directive) to its HTML equivalent. Sample betwixt markup:
 * 
 * [[[animal 666|||note]]]
 * 
 * See SWIM docs for more. Check pseudent and authornote modules for examples.
 * 
 * @param string $content The betwixt content.
 * @return string Content with betwixt markup replaced by HTML.
 */
function hook_swim_betwixt_markup_2_html_alter(&$content) {
}

/**
 * You also need to write some Python, like this:
 * 
 * class Authornote(Directive):
    """
    Render author notes.
    """
    has_content = True
    required_arguments = 1
    final_argument_whitespace = True
    node_class = nodes.decoration
    def run(self):
        text = '\n'.join(self.content)
        # Make a node with the content
        content_node = self.node_class(rawsource=text)
        # Parse the directive contents into the new node.
        self.state.nested_parse(
            self.content,
            self.content_offset,
            content_node
        )
        # Create a new node with the prefix marker text for
        # your Drupal hook code to find.
        prefix_text = '[[[authornote ' + self.arguments[0] + '|||\n'
        prefix_node = nodes.raw('', prefix_text, format='html')
        postfix_text = ']]]\n'
        postfix_node = nodes.raw('', postfix_text, format='html')
        # Return the nodes in sequence.
        return [prefix_node, content_node, postfix_node]
 */
