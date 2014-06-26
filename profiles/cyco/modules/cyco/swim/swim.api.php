<?php

/**
 * @file
 * API documentation for SWIM field type.
 * 
 * swim_rest2html() is a function you can call to translate ReST into HTML.
 * It will invoke the appropriate hooks.
 * 
 * The hooks are functions you should implement in your SWIM component. 
 * See cyco_pseudents for an example. 
 */

/**
 * Translate SWIM content into HTML.
 * @param string $rest ReST
 * @return string HTML
 */
function swim_rest2html( $rest ) {
}

/**
 * Translate ReST to betwixt tags.
 * @param string $content Coontent to translate.
 */
function hook_swim_rest2betwixt_alter( &$content ) {
  
}

/**
 * Return info about CKEditor plugins to use.
 * For more than one, return array of (name, path) arrays.
 * The outer array will be flattened (I think!).
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
 * Parse $content (HTML from CKEditor), and replace target tags
 * with ReST. Usually some regex. 
 * @param string $content Content to change.
 */
function hook_swim_ckhtml2rest_alter( &$content ) {
  
}

/**
 * From betwixt tags to HTML ready for editing on CKEditor.
 * @param string $content Content to translate.
 */
function hook_swim_betwixt2ckhtml_alter( &$content ) {
  
}
/**
 * Translate intermediate (betwixt) markup in $content (as inserted by
 * custom ReST directive) to its HTML equivalent. Sample betwixt markup:
 * 
 * [[[animal:666|||note]]]
 * 
 * There should be no spaces in the betwixt tags, except those typed by the
 * user. E.g., this is OK:
 * 
 * [[[animal:666|||Note: dogs are the best animals.]]]
 * 
 * Check the cyco_pseudents module for an example.
 * 
 * @param string $content The betwixt content.
 * @return string Content with betwixt markup replaced by HTML.
 */
function hook_swim_betwixt2html_alter(&$content) {
}

/**
 * Does the user have access to the peek function?
 * @return boolean True if the user is allowed to peek.
 */
function hook_swim_peek_access() {
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
