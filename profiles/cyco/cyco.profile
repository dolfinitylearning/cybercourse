<?php
/**
 * @file
 * Enables modules and site configuration for a standard site installation.
 */

/**
 * Implements hook_form_FORM_ID_alter() for install_configure_form().
 *
 * Allows the profile to alter the site configuration form.
 */
function cyco_form_install_configure_form_alter(&$form, $form_state) {
  // Pre-populate the site name.
  $form['site_information']['site_name']['#default_value'] 
      = 'CyberCourse instance';
}


function cyco_install_tasks() {
  $task = array();
  $task['finalize'] = array(
    'display_name' => st('Finalizing the awesome'),
    'display' => TRUE,
    'type' => 'normal',
    'function' => '_cyco_finalize_install',
  );
  return $task;
}


function _cyco_finalize_install() {
  //Clean URLs
  _cyco_clean_urls();
  //Give user 1 the administrator role.
  _cyco_make_user_1_admin_author();
  //Add some taxonomy terms.
  _cyco_add_workflow_terms();
  //Add starting content. Basic pages, course pages, blueprint pages.
  _cyco_add_content();
  //Add page to main menu.
  _cyco_add_pages_main_menu();
  //Add terms to content.
  _cyco_add_terms_to_content();
  //Put course and blueprint blocks in sidebar.
  _cyco_place_blocks();
  
  
  //Set the front page.
  _cyco_set_frontpage();
  return '<p>' . st('Awesomeness achieved.') . '</p>';
}




/**
 * Give user 1 the administrator role.
 */
function _cyco_make_user_1_admin_author() {
//See https://api.drupal.org/api/drupal/modules!user!user.module/function/user_multiple_role_edit/7
  $admin_role = user_role_load_by_name( 'administrator' );
  $author_role = user_role_load_by_name( 'author' );
  if ( $admin_role ) {
    user_multiple_role_edit(array(1), 'add_role', $admin_role->rid);
  }
  if ( $author_role ) {
    user_multiple_role_edit(array(1), 'add_role', $author_role->rid);
  }
}


function _cyco_add_workflow_terms() {
  //See http://www.phase2technology.com/blog/taxonomy-terms-in-code/
  _cyco_taxonomy_terms_save_terms(
      array('Create content', 'Review'),
      'workflow_tags'
  );
}

function _cyco_add_terms_to_content() {
  //Add the Create content term to some nodes.
  $tid = _cyco_get_tid_from_term_name('workflow_tags', 'create-content');
  _cyco_add_term2no_cyco_add_term2node(
      'Welcome', 'page', 'field_workflow_tags', $tid
  );
  _cyco_add_term2no_cyco_add_term2node(
      'About', 'page', 'field_workflow_tags', $tid
  );
  
  
}

function _cyco_taxonomy_terms_save_terms($terms, $vocab_name){
  $vocab = taxonomy_vocabulary_machine_name_load($vocab_name);
  if ($vocab == false) {
    drupal_set_message('Error while attempting to install vocabulary ' . $vocab_name, 'error');
  }
  else {
    foreach($terms as $weight => $term){
      $data = new stdClass();
      $data->name = $term;
      $data->vid = $vocab->vid;
      $data->weight = $weight;
      taxonomy_term_save($data);
    }
  }
}

/**
 * Add a term from a vocab to a node.
 */
function _cyco_add_term2node( $node_title, $node_type, $field, $tid ) {
  $node = _cyco_node_load_by_title($node_title, $node_type);
  $node->$field[$node->language][0]['tid'] = $tid;
  node_save($node);
}

/**
 * Get the term id of a term in a vocab.
 * See http://drupal.stackexchange.com/questions/76319/how-to-set-a-taxonomy-term-programatically-for-a-node
 * @param string $vocabulary Vocab name.
 * @param string $term_name The term.
 */
function _cyco_get_tid_from_term_name($vocabulary, $term_name) {
  $arr_terms = taxonomy_get_term_by_name($term_name, $vocabulary);
  if (!empty($arr_terms)) {
    $arr_terms = array_values($arr_terms);
    $tid = $arr_terms[0]->tid;
  }
   else {
    $vobj = taxonomy_vocabulary_machine_name_load($vocabulary);
    $term = new stdClass();
    $term->name = $term_name;
    $term->vid = $vobj->vid;
    taxonomy_term_save($term);
    $tid = $term->tid;
  }
  return $tid;
}

/**
 * Load a node given its title.
 * See http://dropbucket.org/node/698
 * @param string $title Title to find.
 * @param string $node_type Type of node.
 */
function _cyco_node_load_by_title($title, $node_type) {
  $query = new EntityFieldQuery();
  $entities = $query->entityCondition('entity_type', 'node')
    ->propertyCondition('type', $node_type)
    ->propertyCondition('title', $title)
    ->propertyCondition('status', 1)
    ->range(0,1)
    ->execute();
  if(!empty($entities)) {
    return node_load(array_shift(array_keys($entities['node'])));
  }
  else {
    return NULL;
  }
}

/**
 * Set clean URLs.
 * @todo Clean URLs like this may not work.
 */
function _cyco_clean_urls() {
  variable_set('clean_url', 1);  
}

/**
 * Add content, using imports from export_node module.
 */
function _cyco_add_content() {
  //Basic pages.
  _cyco_import_nodes('basic_pages.export');
  //Course pages.
  _cyco_import_nodes('course_pages.export');
  //Blueprint pages.
  _cyco_import_nodes('blueprint_pages.export');
}

/**
 * Import nodes.
 * @param string $filename Name of file with data to import.
 * @return array Import messages.
 */
function _cyco_import_nodes( $filename ) {
  $file_name 
      = drupal_get_path('module', 'cyco_core') . '/exports/' . $filename;
  $data = file_get_contents($file_name);
  $messages = node_export_import($data);
  return $messages;
}

/**
 * Put course pages and blueprints into books.
 */
function _cyco_make_books() {
  $children = array(
    'Topic 1',
    'Topic 2',
  );
  _cyco_make_book('course_page', 'Your course', $children);
  $children = array(
    'Outcomes',
    'Context',
  );
  _cyco_make_book('blueprint_page', 'Your blueprint', $children);
}

function _cyco_make_book( $content_type, $root_title, $children_titles ) {
  //Make the root a book root.
  $root_node = _cyco_node_load_by_title($root_title, $content_type);
  $root_node->book = array('bid' =>'new', 'plid' => 0 );
  node_save($root_node);
  $root_nid = $root_node->nid;
  //Get the root's mlid.
  $sql = 'SELECT mlid FROM menu_links WHERE link_path = :path';
  $root_mlid = db_query($sql, array(':path' => 'node/' . $root_nid))
      ->fetchField();
  //Load the children.
  $children = array();
  foreach ( $children_titles as $child_title ) {
    $child_node = _cyco_node_load_by_title($child_title, $content_type);
    $child_nid = $child_node->nid;
    $child_mlid  = db_query($sql, array(':path' => 'node/' . $child_nid))
      ->fetchField();
    $children[] = array(
      'nid' => $child_nid,
      'node' => $child_node,
      'mlid' => $child_mlid,
    );
  } //End foreach.
  //Add each child into the book.
  foreach( $children as $child ) {
    db_update('menu_links')
      ->fields(array(
        'plid' => $root_mlid,
      ))
      ->condition('mlid', $child['mlid'])
      ->execute();
    db_insert('book')
      ->fields(array(
        'mlid' => $child['mlid'],
        'nid' => $child['nid'],
        'bid' => $root_nid,
      ))
      ->execute();
  } //End foreach.
}

/**
 * Put a block in a region
 * https://www.drupal.org/node/796500#comment-4514446
 */
function _cyco_activate_block($module, $block, $region, $theme, $pages, $visibility) {
  drupal_set_message("Activating block $module:$block\n");
  db_merge('block')
  ->key(array('theme' => $theme, 'delta' => $block, 'module' => $module))
  ->fields(array(
    'region' => ($region == BLOCK_REGION_NONE ? '' : $region),
    'pages' => trim($pages),
    'status' => (int) ($region != BLOCK_REGION_NONE),
    'visibility' => $visibility,
  ))
  ->execute();
}

function _cyco_place_blocks() {
  $blueprint_node 
      = _cyco_node_load_by_title('Your blueprint', 'blueprint_page');
  $blueprint_block_id = 'cbb_' . $blueprint_node->nid;
  _cyco_activate_block('cyco_book_blocks', $blueprint_block_id, 'sidebar_first', 
      'cybercourse', '', 1);
  $course_node 
      = _cyco_node_load_by_title('Your course', 'course_page');
  $course_block_id = 'cbb_' . $course_node->nid;
  _cyco_activate_block('cyco_book_blocks', $course_block_id, 'sidebar_first', 
      'cybercourse', '', 1);
}

/**
 * Set the frontpage of the site to the Welcome page.
 */
function _cyco_set_frontpage() {
  $welcome = _cyco_node_load_by_title('Welcome', 'page');
  $welcome_nid = $welcome->nid;
  variable_get('site_frontpage', 'node/' . $welcome_nid);
}


function _cyco_add_pages_main_menu() {
  _cyco_add_menu_item('Welcome', 'page', 'main-menu', 0);
  _cyco_add_menu_item('About', 'page', 'main-menu', 1);
}

/**
 * Create a menu item.
 * @param string $node_title Node title.
 * @param string $node_type Node content type.
 * @param string $menu Menu machine name, e.g., main-menu.
 * @param int $weight Menu item weight.
 */
function _cyco_add_menu_item($node_title, $node_type, $menu, $weight) {
  $node = _cyco_node_load_by_title($node_title, $node_type);
  $item = array(
    'link_path' => 'node/' . $node->nid,
    'link_title' => $node->title,
    'menu_name' => $menu, // Menu machine name, for example: main-menu
    'weight' => $weight,
    'language' => $node->language,
    'plid' => 0, // Parent menu item, 0 if menu item is on top level
    'module' => 'menu',
  );
  menu_link_save($item);
}