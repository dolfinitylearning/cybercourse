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

/**
 * Add an install task.
 * @return array Definition
 */
function cyco_install_tasks() {
  $task = array();
  $task['finalize'] = array(
    'display_name' => st('Finalize the awesome'),
    'display' => TRUE,
    'type' => 'normal',
    'function' => '_cyco_finalize_install',
  );
  return $task;
}

/*
 * Finish up the installation.
 */
function _cyco_finalize_install() {
  // Clean URLs
  _cyco_clean_urls();
  // Give user 1 the administrator role.
  _cyco_make_user_1_admin_author();
  // Define services.
  _cyco_define_services();
  // Add some taxonomy terms.
  _cyco_add_workflow_terms();
  // Add starting content. Basic pages, course pages, blueprint pages.
  _cyco_add_content();
  // Add terms to content.
  _cyco_add_terms_to_content();
  // Link pages into books.
  _cyco_make_books();
//  //Add pages to the main menu.
//  _cyco_add_links_main_menu();
  // Create pages for ToU, credits, and copyright. Why not just import them?
  // Because I can't figure out Mysterious Menu Misplacement. They won't go
  // in the footer menu. (Oh, just figured it out. Maybe. Leave this here
  // anyway.)
  _cyco_create_footer_linked_pages();
  // Add pages to the footer.
  _cyco_add_links_footer_menu();
  //Remove the title from the footer block.
  _cyco_remove_footer_title();
  // Add links to control panel menu. I can't make features do it, 
  // except for cp-author.
  _cyco_add_links_cp_menus();
  // Put course and blueprint blocks in sidebar, footer menu 
  // in (gasp!) the footer.
  _cyco_place_blocks();
  // Add class to some blocks.
  _cyco_add_classes2blocks();
  // Set the front page.
  _cyco_set_frontpage();
  
  // Secondary links source - none.
  variable_set('menu_secondary_links_source', '');
  // Tell extlink to open external targets in a new window.
  variable_set('extlink_target', '_blank');
  // Theme stuff
  _cyco_theme_stuff();
  // Turn off some modules.
  _cyco_disable_modules();
  node_access_rebuild();
  cache_clear_all();
  //Remove all blocks from submission theme, except for content.
  _cyco_remove_submission_blocks();
  // Add control panel link to user menu.
  _cyco_add_cp_link();
  cache_clear_all();
}

/**
 * Give user 1 the administrator role.
 * See https://api.drupal.org/api/drupal/modules!user!user.module/function/user_multiple_role_edit/7
 */
function _cyco_make_user_1_admin_author() {
  $admin_role = user_role_load_by_name( 'administrator' );
  $author_role = user_role_load_by_name( 'author' );
  if ( $admin_role ) {
    user_multiple_role_edit(array(1), 'add_role', $admin_role->rid);
  }
  if ( $author_role ) {
    user_multiple_role_edit(array(1), 'add_role', $author_role->rid);
  }
}

/**
 * Define services, using an export.
 */
function _cyco_define_services() {
  $path = drupal_get_path('module', 'cyco_core') . '/custom/exports/' 
      . 'services.export'; 
  require_once $path;
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
  $tid = _cyco_get_tid_from_term_name('workflow_tags', 'Create content');
  _cyco_add_term2node(
      'Welcome', 'page', 'field_workflow_tags', $tid
  );
  _cyco_add_term2node(
      'About', 'page', 'field_workflow_tags', $tid
  );
  _cyco_add_term2node(
      'Copyright, you, 20xx', 'page', 'field_workflow_tags', $tid
  );
  _cyco_add_term2node(
      'Terms of use', 'page', 'field_workflow_tags', $tid
  );
  _cyco_add_term2node(
      'Credits', 'page', 'field_workflow_tags', $tid
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
  if ( ! is_null($node) ) {
    $node->{$field}[$node->language][0]['tid'] = $tid;
    node_save($node);
  }
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
    $nodes = $entities['node'];
    $nids = array_keys($nodes);
    $nid = $nids[0];
    $node = node_load($nid);
    return $node;
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
  _cyco_import_nodes(
      drupal_get_path('module', 'cyco_core') . '/custom/exports/' 
      . 'basic_pages.export'
  );
  //Course pages.
  _cyco_import_nodes(
      drupal_get_path('module', 'cyco_core') . '/custom/exports/' 
      . 'course_pages.export'
  );
  //Blueprint pages.
  _cyco_import_nodes(
      drupal_get_path('module', 'cyco_core') . '/custom/exports/' 
      . 'blueprint_pages.export'
  );
  //Pseudents.
  _cyco_import_nodes(
      drupal_get_path('module', 'cyco_pseudents') . '/custom/exports/' 
      . 'pseudents.export'
  );
  //Patterns.
  _cyco_import_nodes(
      drupal_get_path('module', 'cyco_patterns') . '/custom/exports/' 
      . 'patterns.export'
  );  
}

/**
 * Import nodes.
 * @param string $filename Name of file with data to import.
 * @return array Import messages.
 */
function _cyco_import_nodes( $filename ) {
  $data = file_get_contents($filename);
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

/**
 * Make content into a book.
 * @param string $content_type Content type.
 * @param string $root_title Title of the book's root node.
 * @param array $children_titles Titles of the child pages of the root.
 */
function _cyco_make_book( $content_type, $root_title, $children_titles ) {
  //Make the root a book root.
  $root_node = _cyco_node_load_by_title($root_title, $content_type);
  $root_node->book = array('bid' =>'new', 'plid' => 0 );
  node_save($root_node);
  $root_nid = $root_node->nid;
  //Get the root's mlid and menu_name.
  $sql = 'SELECT mlid, menu_name FROM menu_links WHERE link_path = :path';
  $row = (object)db_query($sql, array(':path' => 'node/' . $root_nid))->fetchAssoc();
  $root_mlid  = $row->mlid;
  $root_menu_name = $row->menu_name;
  //Load the children.
  $children = array();
  foreach ( $children_titles as $child_title ) {
    $child_node = _cyco_node_load_by_title($child_title, $content_type);
    $children[] = $child_node;
  } //End foreach.
  //Add each child into the book.
  foreach( $children as $child ) {
    //Add a new menu item.
    $item = array(
      'link_path' => 'node/' . $child->nid,
      'link_title' => $child->title,
      'menu_name' => $root_menu_name,
      'weight' => 0,
      'language' => $child->language,
      'plid' => $root_mlid,
      'module' => 'menu',
    );
    $child_mlid = menu_link_save($item);
    //Add child to the book.
    if ( $child_mlid !== FALSE ) {
      db_insert('book')
        ->fields(array(
          'mlid' => $child_mlid,
          'nid' => $child->nid,
          'bid' => $root_nid,
        ))
        ->execute();
    }
  } //End foreach.
}

/**
 * Put a block in a region
 * https://www.drupal.org/node/796500#comment-4514446
 * @param string $module Module creating the block.
 * @param string $block Block machine name.
 * @param string $region Region machine name.
 * @param string $theme Theme this block setting applies to.
 * @param string $pages Pages with special visibility.
 * @param int $visibility 1 if show in $pages, 0 if not.
 * @param int $weight Block weight in region.
 * @param string $title The title of the block. Optional.
 * 
 */
function _cyco_activate_block($module, $block, $region, $theme, 
    $pages, $visibility, $weight, $title=FALSE) {
//  drupal_set_message("Activating block $module:$block\n");
  $fields = array(
      'region' => ($region == BLOCK_REGION_NONE ? '' : $region),
      'pages' => trim($pages),
      'status' => (int) ($region != BLOCK_REGION_NONE),
      'visibility' => $visibility,
      'weight' => $weight,
  );
  if ( $title !== FALSE ) {
    $fields['title'] = $title;
  }
  db_merge('block')
    ->key(array('theme' => $theme, 'delta' => $block, 'module' => $module))
    ->fields( $fields )
  ->execute();
}

/**
 * Place blocks in regions.
 */
function _cyco_place_blocks() {
  _cyco_activate_block('system', 'user-menu', 'sidebar_first',
      'cybercourse', '', 0, -1, '<none>');
  _cyco_activate_block('menu', 'menu-footer', 'footer',
      'cybercourse', '', 0, 0, '<none>');
  $course_node 
      = _cyco_node_load_by_title('Your course', 'course_page');
  //Cache the menu tree for this block.
  $rendered = _cbb_get_book_tree( $course_node->nid );
  $course_block_id = 'cbb_' . $course_node->nid;
  _cyco_activate_block('cyco_book_blocks', $course_block_id, 'sidebar_first', 
      'cybercourse', '', 0, 0);
  $blueprint_node 
      = _cyco_node_load_by_title('Your blueprint', 'blueprint_page');
  $rendered = _cbb_get_book_tree( $blueprint_node->nid );
  $blueprint_block_id = 'cbb_' . $blueprint_node->nid;
  _cyco_activate_block('cyco_book_blocks', $blueprint_block_id, 'sidebar_first', 
      'cybercourse', '', 0, 1);
  _cyco_activate_block('menu', 'menu-tools', 'sidebar_first',
      'cybercourse', '', 0, 2);
  _cyco_activate_block('user', 'login', 'sidebar_first',
      'cybercourse', '', 0, 4);
  _cyco_activate_block('search', 'form', 'sidebar_first',
      'cybercourse', '', 0, 5);
  //Position the footer.
  $footer_menu_machine_name = _cyco_find_menu_machine_name('Footer');
  _cyco_activate_block('menu', $footer_menu_machine_name, 'footer',
      'cybercourse', '', 0, 1);
}

/**
 * Set up block visibility rules.
 */
function _cyco_set_block_visibility() {
  //Roles.
  $role_names = array(
    'administrator',
    'author',
    'instructor',
    'reviewer',
    'grader',
  );
  $blueprint_node 
      = _cyco_node_load_by_title('Your blueprint', 'blueprint_page');
  $blueprint_block_id = 'cbb_' . $blueprint_node->nid;
  _cyco_restrict_block2roles( 
      $blueprint_block_id, 'cyco_book_blocks', $role_names
  );
}

/**
 * Set block visibility for roles.
 * @param string $block_id Id of block.
 * @param string $module Module name.
 * @param array $role_names Names of roles.
 */
function _cyco_restrict_block2roles( $block_id, $module, $role_names ) {
  $roles = user_roles();
  foreach( $role_names as $role_name ) {
    $rid = array_search($role_name, $roles);
    if ( $rid !== FALSE ) {
      db_insert('block_role')
        ->fields(array(
          'module' => $module,
          'delta' => $block_id,
          'rid' => $rid,
        ))
        ->execute();
    }
  }
}

/**
 * Set the frontpage of the site to the Welcome page.
 */
function _cyco_set_frontpage() {
  $welcome = _cyco_node_load_by_title('Welcome', 'page');
  $welcome_nid = $welcome->nid;
  variable_set('site_frontpage', 'node/' . $welcome_nid);
}

/**
 * Add links to the main menu.
 */
function _cyco_add_links_main_menu() {
  _cyco_add_menu_item('Welcome', 'page', 'main-menu', 0);
  _cyco_add_menu_item('About', 'page', 'main-menu', 1);
  _cyco_add_menu_item('Help', 'page', 'main-menu', 2);
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

/**
 * Add classes to blocks.
 */
function _cyco_add_classes2blocks() {
  //Footer menu block.
  $footer_menu_machine_name = _cyco_find_menu_machine_name('Footer');
  _cyco_add_classes2block('menu', $footer_menu_machine_name, 'well well-sm');
  //Tools menu block.
  _cyco_add_classes2block('menu', 'menu-tools', 'well well-sm');
  //User menu block.
  _cyco_add_classes2block('system', 'user-menu', 'well well-sm');
  //Login block
  _cyco_add_classes2block('user', 'login', 'well well-sm');
  //Course block.
  $course_node 
      = _cyco_node_load_by_title('Your course', 'course_page');
  $course_block_id = 'cbb_' . $course_node->nid;
  _cyco_add_classes2block('cyco_book_blocks', $course_block_id, 'well well-sm');
  //Blueprint block.
  $blueprint_node 
      = _cyco_node_load_by_title('Your blueprint', 'blueprint_page');
  $blueprint_block_id = 'cbb_' . $blueprint_node->nid;
  _cyco_add_classes2block('cyco_book_blocks', $blueprint_block_id, 'well well-sm');
}

/**
 * Add classes to a block.
 * @param string $module Name of the module defining the block.
 * @param string $block Name of the block.
 * @param string $classes Classes, no ., space separated.
 */
function _cyco_add_classes2block( $module, $block, $classes ) {
  db_update('block')
    ->fields(array('css_class' => $classes))
    ->condition('module', $module)
    ->condition('delta', $block)
    ->execute();
}

/**
 * Turn off some modules.
 */
function _cyco_disable_modules() {
  $modules = array(
    'node_export',
    'features_orphans',
  );
  module_disable( $modules );
}

function _cyco_theme_stuff() {
  theme_disable(array('bartik'));
  theme_enable(array('seven', 'cybercourse_submission'));
  //Settings for CyberCourse  theme.
  $var_name = 'theme_cybercourse_settings';
  $settings = variable_get($var_name, array());
  $settings['bootstrap_bootswatch'] = 'cerulean';
  variable_set($var_name, $settings);
  //Settings for CyberCourse submission theme.
  $var_name = 'theme_cybercourse_submission_settings';
  $settings = variable_get($var_name, array());
  $settings['bootstrap_breadcrumb'] = 0;
  $settings['bootstrap_breadcrumb_home'] = 0;
  variable_set($var_name, $settings);

}


function _cyco_add_links_cp_menus() {
  //Links in instructor menu.
  $items = array();
  $menu_name = 'menu-cp-instructors';
  $language = LANGUAGE_NONE;
  $module = 'menu';
  $plid = 0;
  $items[] = array(
    'link_path' => 'courses-and-keywords',
    'link_title' => 'Courses and keywords',
    'weight' => 0,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $plid,
    'module' => $module,
  );
  $items[] = array(
    'link_path' => 'blueprints-and-keywords',
    'link_title' => 'Blueprints and keywords',
    'weight' => 1,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $plid,
    'module' => $module,
  );
  $items[] = array(
    'link_path' => 'pseudent-poses',
    'link_title' => 'Pseudent poses',
    'weight' => 2,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $plid,
    'module' => $module,
  );
  $items[] = array(
    'link_path' => 'patterns',
    'link_title' => 'Patterns',
    'weight' => 3,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $plid,
    'module' => $module,
  );
  $items[] = array(
    'link_path' => 'admin/people',
    'link_title' => 'Users',
    'weight' => 4,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $plid,
    'module' => $module,
  );

  $mlids = array();
  foreach ( $items as $item ) {
    $mlids[ $item['link_path'] ] = menu_link_save($item);
  }

  $items = array();
  $items[] = array(
    'link_path' => 'admin/people',
    'link_title' => 'List users',
    'weight' => 0,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $mlids[ 'admin/people' ],
    'module' => $module,
  );
  $items[] = array(
    'link_path' => 'admin/people/create',
    'link_title' => 'Add user',
    'weight' => 1,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $mlids[ 'admin/people' ],
    'module' => $module,
  );
  
  $menu_name = 'menu-cp-graders';
  $items[] = array(
    'link_path' => 'courses-and-keywords',
    'link_title' => 'Courses and keywords',
    'weight' => 0,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $plid,
    'module' => $module,
  );
  $items[] = array(
    'link_path' => 'blueprints-and-keywords',
    'link_title' => 'Blueprints and keywords',
    'weight' => 1,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $plid,
    'module' => $module,
  );
  $items[] = array(
    'link_path' => 'pseudent-poses',
    'link_title' => 'Pseudent poses',
    'weight' => 2,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $plid,
    'module' => $module,
  );
  $items[] = array(
    'link_path' => 'patterns',
    'link_title' => 'Patterns',
    'weight' => 3,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $plid,
    'module' => $module,
  );
  
  $menu_name = 'menu-cp-reviewers';
  $items[] = array(
    'link_path' => 'courses-and-keywords',
    'link_title' => 'Courses and keywords',
    'weight' => 0,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $plid,
    'module' => $module,
  );
  $items[] = array(
    'link_path' => 'blueprints-and-keywords',
    'link_title' => 'Blueprints and keywords',
    'weight' => 1,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $plid,
    'module' => $module,
  );
  $items[] = array(
    'link_path' => 'pseudent-poses',
    'link_title' => 'Pseudent poses',
    'weight' => 2,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $plid,
    'module' => $module,
  );
  $items[] = array(
    'link_path' => 'patterns',
    'link_title' => 'Patterns',
    'weight' => 3,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $plid,
    'module' => $module,
  );
  foreach ( $items as $item ) {
    menu_link_save($item);
  }
}

function _cyco_add_cp_link() {
  $item = array(
    'menu_name' => 'user-menu',
    'link_path' => 'user/control-panel',
    'router_path' => 'user/control-panel',
    'link_title' => 'Control panel',
    'options' => array(
      'attributes' => array(
        'title' => 'CyberCourse control panel.',
      ),
      'identifier' => 'user-menu_control-panel:user/control-panel',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,    
    'language' => 'und',
  );
  menu_link_save($item);
}

/**
 * Create pages with links in the footer.
 */
function _cyco_create_footer_linked_pages() {
  $summary = 'Copyright.';
  $body = 'Your copyright details.';
  _cyco_create_page('page', 1, 'Copyright, you, 20xx', $summary, $body);
  $summary = 'Web site terms of use.';
  $body = "Terms of use go here. E.g.,\n\nDon't rely on anything on "
      . "this site, including this sentence.\n";
  _cyco_create_page('page', 1, 'Terms of use', $summary, $body);
  $summary = 'Thanks!';
  $body = 'Credit other people here.';
  _cyco_create_page('page', 1, 'Credits', $summary, $body);
  
}

/**
 * Add links to the footer menu.
 */
function _cyco_add_links_footer_menu() {
  //Find the machine name of the footer menu.
  $footer_menu_machine_name = _cyco_find_menu_machine_name('Footer');
  if ( is_null($footer_menu_machine_name) ) {
    drupal_set_message('Could not find footer menu.');
    return;
  }
  _cyco_add_menu_item('Copyright, you, 20xx', 'page', $footer_menu_machine_name, 0);
  _cyco_add_menu_item('Credits', 'page', $footer_menu_machine_name, 1);
  _cyco_add_menu_item('Terms of use', 'page', $footer_menu_machine_name, 2);
}

/**
 * Find the machine name of the footer menu.
 * @param string $menu_title Human title of the menu.
 * @return string Menu machine name.
 */
function _cyco_find_menu_machine_name($menu_title) {
  $machine_name = NULL;
  $menu_defs = menu_load_all();
  foreach ( $menu_defs as $menu_def ) {
    if ( $menu_def['title'] == $menu_title ) {
      $machine_name = $menu_def['menu_name'];
    }
  }
  return $machine_name;
}

/**
 * Create a page.
 * @param string $type
 * @param int $uid
 * @param string $title
 * @param string $summary
 * @param string $body
 */
function _cyco_create_page( $type, $uid, $title, $summary, $body) {
  $values = array(
    'type' => $type,
    'uid' => $uid,
    'status' => 1,
    'comment' => 1,
    'promote' => 0,
  );
  $entity = entity_create('node', $values);
  $ewrapper = entity_metadata_wrapper('node', $entity);
  $ewrapper->title->set($title);
  $ewrapper->body->set(array('value' => $body));
  $ewrapper->body->summary->set($summary);
  $ewrapper->save();
}

/**
 * Remove the title from the footer block.
 */
function _cyco_remove_footer_title() {
  $block_machine_name = _cyco_find_menu_machine_name('Footer');
  _cyco_remove_title_from_block('menu', $block_machine_name, 'cybercourse');
}

/**
 * Remove title from a block.
 * @param string $module Name of the module defining the block.
 * @param string $block Name of the block.
 * @param string $theme Name of the theme.
 */
function _cyco_remove_title_from_block( $module, $block, $theme ) {
  db_update('block')
    ->fields(array('title' => '<none>'))
    ->condition('module', $module)
    ->condition('delta', $block)
    ->condition('theme', $theme)
    ->execute();
}

/**
 * Remove all blocks from the submission theme, except for 
 * content in the main area.
 */
function _cyco_remove_submission_blocks() {
  //There isn't an entry for content.
  db_update('block')
    ->fields(array(
      'status' => 0,
      'region' => -1,
    ))
    ->condition('theme', 'cybercourse_submission')
    ->condition('delta', 'main', '!=')
    ->execute();
}
