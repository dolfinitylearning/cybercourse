<?php
/**
 * @file
 * Enables modules and site configuration for a standard site installation.
 */
require_once 'cyco_install_debug.php';
CycoInstallDebug::getInstance()->debug = TRUE;

//File with list of extra modules to install.
define('MODULE_LIST_FILE_NAME', 'more_modules.ini');

/**
 * Implements hook_form_FORM_ID_alter() for install_configure_form().
 *
 * Allows the profile to alter the site configuration form.
 */
function cyco_form_install_configure_form_alter(&$form, $form_state) {
  // Pre-populate the site name.
  $form['site_information']['site_name']['#default_value'] 
      = 'Your CyberCourse instance';
}

/**
 * Implements hook_install_tasks_alter()
 */
function cyco_install_tasks_alter( &$tasks, $install_state ) {
CycoInstallDebug::getInstance()->output('Start cyco_install_tasks_alter');
  //Add new installation tasks before the site configure form in shown.
  //See https://www.drupal.org/node/1022020 for task list.  
  //Grab tasks to be moved to the end.
  $t = get_t();
  $install_import_locales_remaining = $tasks['install_import_locales_remaining'];
  unset( $tasks['install_import_locales_remaining'] );
  $install_finished = $tasks['install_finished'];
  unset( $tasks['install_finished'] );
  //Define new batch task. Adding bunch o' modules.
  $tasks['_cyco_install_more_modules'] = array(
    'display_name' => $t('Installing more modules'),
    'display' => TRUE,
    'type' => 'batch',
    'run' => INSTALL_TASK_RUN_IF_NOT_COMPLETED,
  );  
  //Custom configuration.
  $tasks['_cyco_finalize_install'] = array(
    'display_name' => $t('Making it awesome'),
    'display' => TRUE,
    'type' => 'batch',
    'run' => INSTALL_TASK_RUN_IF_NOT_COMPLETED,
  );  
  //Restore tasks removed earlier.
  $tasks['install_import_locales_remaining'] = $install_import_locales_remaining;
  $tasks['install_finished'] = $install_finished;
CycoInstallDebug::getInstance()->output('End cyco_install_tasks_alter');
}

/**
 * Define a batch job to install modules listed in a file.
 * @return array Job definition.
 */
function _cyco_install_more_modules() {
CycoInstallDebug::getInstance()->output('Start _cyco_install_more_modules');
  $t = get_t();
  //Read the list of modules to install.
  $filepath = dirname(__FILE__) . '/' . MODULE_LIST_FILE_NAME;
  $modules = parse_ini_file( $filepath );
  $modules = $modules['dependencies']; 
  //Define a batch job.
  $operations = array();
  foreach ($modules as $module) {
    $operations[] = array(
      '_cyco_install_one_module',
      array( $module ),
    );
  }
  $batch_def = array(
    'operations' => $operations,
    'title' => $t('Installing modules that put the fun in functional'),
    'init_message' => $t('Initializing'),
    'error_message' => $t('Error'),
    'progress_message' => $t('Processed @current out of @total.'),
    'finished' => '_cyco_install_finished_task',
  );
CycoInstallDebug::getInstance()->output(
    'End _cyco_install_more_modules.'// Job: <pre>'
//    . print_r($batch_def, TRUE) . '</pre>'
 );
  return $batch_def;  
}

/**
 * Install a module as one step in a batch job.
 * @param type $module_name
 * @param type $context
 */
function _cyco_install_one_module($module_name, &$context) {
CycoInstallDebug::getInstance()->output(
    'Start _cyco_install_one_module. Module: ' . $module_name);
  $t = get_t();
  module_enable(array($module_name), FALSE);
  $context['message'] = $t('Installing %module.', array('%module' => $module_name));
CycoInstallDebug::getInstance()->output('End _cyco_install_one_module');
}

/**
 * Done with a Cyco installation task.
 * @param type $success
 * @param type $results
 * @param type $operations
 */
function _cyco_install_finished_task($success, $results, $operations) {
CycoInstallDebug::getInstance()->output('In _cyco_install_finished_task');
}

/*
 * Finish up the installation.
 */
function _cyco_finalize_install() {
CycoInstallDebug::getInstance()->output('Start _cyco_finalize_install');
   $t = get_t();
  //Define a batch job. Breaks the final tasks into several steps,
  //to avoid timeout issues.
  $operations = array();
  //Second para is needed even if it isn't needed.
  $operations[] = array( '_cyco_finalize_install_step1', array('dog') );
  $operations[] = array( '_cyco_finalize_install_step2', array('dog')  );
  $operations[] = array( '_cyco_finalize_install_step3', array('dog') );
  $operations[] = array( '_cyco_finalize_install_step4', array('dog') );
  $operations[] = array( '_cyco_finalize_install_step4_2', array('dog') );
  $operations[] = array( '_cyco_finalize_install_step4_2a', array('dog') );
  $operations[] = array( '_cyco_finalize_install_step4_3', array('dog') );
  $operations[] = array( '_cyco_finalize_install_step4_4', array('dog') );
  $operations[] = array( '_cyco_finalize_install_step4_5', array('dog') );
  $operations[] = array( '_cyco_finalize_install_step4_6', array('dog') );
  $operations[] = array( '_cyco_finalize_install_step4_7', array('dog') );
  $operations[] = array( '_cyco_finalize_install_step5', array('dog') );
  $batch_def = array(
    'operations' => $operations,
    'title' => $t('Adding some awesome stuff'),
    'init_message' => $t('Initializing'),
    'error_message' => $t('Error'),
    'progress_message' => $t('Processed @current out of @total.'),
    'finished' => '_cyco_install_finished_task',
  );
CycoInstallDebug::getInstance()->output(
    'End _cyco_finalize_install.' // Job: <pre>'
//    . print_r($batch_def, TRUE) . '</pre>'
 );
  return $batch_def;
}

function _cyco_finalize_install_step1($dog, &$context) {
CycoInstallDebug::getInstance()->output('Start _cyco_finalize_install_step1');
  $t = get_t();
  // Clean URLs
  //_cyco_clean_urls();
  // Give user 1 the administrator role.
  _cyco_make_user_1_admin_author();
  // Define services.
//  _cyco_define_services();
  // Add some taxonomy terms.
  _cyco_add_workflow_terms();
  // Add starting content. Basic pages, course pages, blueprint pages...
  _cyco_add_content();
  // Add workflow terms to content.
  _cyco_add_workflow_terms_to_content();
  //Add links to the main menu.
  _cyco_add_links_main_menu();
  $context['message'] = $t('Just added some awesome stuff.');
CycoInstallDebug::getInstance()->output('End _cyco_finalize_install_step1');
}

function _cyco_finalize_install_step2($dog, &$context) {
CycoInstallDebug::getInstance()->output('Start _cyco_finalize_install_step2');
  $t = get_t();
  // Link pages into books.
  _cyco_make_books();
  // Create pages for ToU, credits, and copyright. Why not just import them?
  // Because I can't figure out Mysterious Menu Misplacement. They won't go
  // in the footer menu. (Oh, just figured it out. Maybe. Leave this here
  // anyway.)
  _cyco_create_footer_linked_pages();
  // Add pages to the footer.
  _cyco_add_links_footer_menu();
  //Remove the title from the footer block.
  _cyco_remove_footer_title();
  $context['message'] = $t('Mixed in some awesome sauce.');
CycoInstallDebug::getInstance()->output('End _cyco_finalize_install_step2');
}
  
function _cyco_finalize_install_step3($dog, &$context) {
CycoInstallDebug::getInstance()->output('Start _cyco_finalize_install_step3');
  $t = get_t();
  //Turn on modules.
  _cyco_enable_modules();
  // Put course and blueprint blocks in sidebar, footer menu 
  // in (gasp!) the footer.
  _cyco_place_blocks();
  // Add class to some blocks.
  _cyco_add_classes2blocks();
  
  // Secondary links source - none.
  variable_set('menu_secondary_links_source', '');
  // Tell extlink to open external targets in a new window.
  variable_set('extlink_target', '_blank');
  // Theme stuff
  _cyco_theme_stuff();
  // Turn off some modules.
  _cyco_disable_modules();
  // Set the front page.
//  CycoInstallDebug::getInstance()->output('Before set frontpage call');
  _cyco_set_frontpage();
//  CycoInstallDebug::getInstance()->output('After frontpage call');
//  $doom_dog = variable_get('site_frontpage', '(Not found)');
//  CycoInstallDebug::getInstance()->output('Frontpage: ' . $doom_dog);
  $context['message'] = $t('Mmm... smells awesome!');
CycoInstallDebug::getInstance()->output('End _cyco_finalize_install_step3');
}

function _cyco_finalize_install_step4($dog, &$context) {
CycoInstallDebug::getInstance()->output('Starting _cyco_finalize_install_step4');
  $t = get_t();
  // Add links to control panel menu. I can't make features do it right.
  _cyco_add_links_cp_menu1();
  $context['message'] = $t('Linking up more awesome.');  
CycoInstallDebug::getInstance()->output('Ending _cyco_finalize_install_step4');
}

function _cyco_finalize_install_step4_2($dog, &$context) {
CycoInstallDebug::getInstance()->output('Starting _cyco_finalize_install_step4_2');
  $t = get_t();
  // Add links to control panel menu. I can't make features do it right.
  _cyco_add_links_cp_menu2();
  $context['message'] = $t('Linking up Return of Awesome.');  
CycoInstallDebug::getInstance()->output('Ending _cyco_finalize_install_step4_2');
}

function _cyco_finalize_install_step4_2a($dog, &$context) {
CycoInstallDebug::getInstance()->output('Starting _cyco_finalize_install_step4_2a');
  $t = get_t();
  // Add links to control panel menu. I can't make features do it right.
  _cyco_add_links_cp_menu2a();
  $context['message'] = $t('Linking up Awesome\'s Revenge.');  
CycoInstallDebug::getInstance()->output('Ending _cyco_finalize_install_step4_2a');
}

function _cyco_finalize_install_step4_3($dog, &$context) {
CycoInstallDebug::getInstance()->output('Starting _cyco_finalize_install_step4_3');
  $t = get_t();
  // Add links to control panel menu. I can't make features do it right.
  _cyco_add_links_cp_menu3();
  $context['message'] = $t('Linking up Awesome Rides Again.');  
CycoInstallDebug::getInstance()->output('Ending _cyco_finalize_install_step4_3');
}

function _cyco_finalize_install_step4_4($dog, &$context) {
CycoInstallDebug::getInstance()->output('Starting _cyco_finalize_install_step4_4');
  $t = get_t();
  // Add links to control panel menu. I can't make features do it right.
  _cyco_add_links_cp_menu4();
  $context['message'] = $t('Linking up Awesome: This Time, It\'s Personal');  
CycoInstallDebug::getInstance()->output('Ending _cyco_finalize_install_step4_4');
}

function _cyco_finalize_install_step4_5($dog, &$context) {
CycoInstallDebug::getInstance()->output('Starting _cyco_finalize_install_step4_5');
  $t = get_t();
  // Add links to control panel menu. I can't make features do it right.
  _cyco_add_links_cp_menu5();
  $context['message'] = $t('Linking up Revenge of Awesome.');  
CycoInstallDebug::getInstance()->output('Ending _cyco_finalize_install_step4_5');
}

function _cyco_finalize_install_step4_6($dog, &$context) {
CycoInstallDebug::getInstance()->output('Starting _cyco_finalize_install_step4_6');
  $t = get_t();
  // Add links to control panel menu. I can't make features do it right.
  _cyco_add_links_cp_menu6();
  $context['message'] = $t('Linking up Awesome: The Next Generation.');  
CycoInstallDebug::getInstance()->output('Ending _cyco_finalize_install_step4_6');
}

function _cyco_finalize_install_step4_7($dog, &$context) {
CycoInstallDebug::getInstance()->output('Starting _cyco_finalize_install_step4_7');
  $t = get_t();
  // Add links to control panel menu. I can't make features do it right.
  _cyco_add_links_cp_menu7();
  $context['message'] = $t('Linking up Deep Space Awesome.');  
CycoInstallDebug::getInstance()->output('Ending _cyco_finalize_install_step4_7');
}

function _cyco_finalize_install_step5($dog, &$context) {
CycoInstallDebug::getInstance()->output('Start _cyco_finalize_install_step5');
  $t = get_t();
  node_access_rebuild();
//  cache_clear_all();
  //Remove all blocks from submission theme, except for content.
  _cyco_remove_submission_blocks();
  cache_clear_all();
  $context['message'] = $t('You won\'t believe how awesome Cyco is.');
CycoInstallDebug::getInstance()->output('End _cyco_finalize_install_step5');
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
 * Return rid of a role, given its name.
 * @param string $role_name Role name
 * @return int rid
 */
function _cyco_get_role_id_from_name( $role_name ) {
  $role = user_role_load_by_name( $role_name );
  return $role->rid;
}

/**
 * Show block to certain roles.
 * @param string $module Name of the module creating the block.
 * @param string $delta Block id (delta).
 * @param array $roles_see_block Array of rids who can see the block.
 */
function _cyco_set_block_role_visibility( $module, $delta, $roles_see_block ) {
CycoInstallDebug::getInstance()->output('Start _cyco_set_block_role_visibility');
  //Copied from block_admin_configure_submit().
  $query = db_insert('block_role')->fields(array('rid', 'module', 'delta'));
  foreach ($roles_see_block as $rid) {
    $query->values(array(
      'rid' => $rid,
      'module' => $module,
      'delta' => $delta,
    ));
  }
  $query->execute();  
CycoInstallDebug::getInstance()->output('End _cyco_set_block_role_visibility');
}

/**
 * Define services, using an export.
 */
//function _cyco_define_services() {
//  $path = drupal_get_path('module', 'cyco_core') . '/custom/exports/' 
//      . 'services.export'; 
//  require_once $path;
//}
//
function _cyco_add_workflow_terms() {
CycoInstallDebug::getInstance()->output('Start _cyco_add_workflow_terms');
  //See http://www.phase2technology.com/blog/taxonomy-terms-in-code/
  _cyco_taxonomy_terms_save_terms(
      array('Create content', 'Review'),
      'workflow_tags'
  );
CycoInstallDebug::getInstance()->output('End _cyco_add_workflow_terms');
}

function _cyco_add_workflow_terms_to_content() {
CycoInstallDebug::getInstance()->output('Start _cyco_add_workflow_terms_to_content');
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
CycoInstallDebug::getInstance()->output('End _cyco_add_workflow_terms_to_content');
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
CycoInstallDebug::getInstance()->output('Start _cyco_add_content');
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
//  //Pseudents.
//  _cyco_import_nodes(
//      drupal_get_path('module', 'cyco_pseudents') . '/custom/exports/' 
//      . 'pseudents.export'
//  );
//  //Patterns.
//  _cyco_import_nodes(
//      drupal_get_path('module', 'cyco_patterns') . '/custom/exports/' 
//      . 'patterns.export'
//  );  
CycoInstallDebug::getInstance()->output('Start _cyco_add_content');
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
CycoInstallDebug::getInstance()->output('Start _cyco_make_books');
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
CycoInstallDebug::getInstance()->output('End _cyco_make_books');
}

/**
 * Make content into a book.
 * @param string $content_type Content type.
 * @param string $root_title Title of the book's root node.
 * @param array $children_titles Titles of the child pages of the root.
 */
function _cyco_make_book( $content_type, $root_title, $children_titles ) {
CycoInstallDebug::getInstance()->output('Start _cyco_make_book '
    . 'root title: ' . $root_title);
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
CycoInstallDebug::getInstance()->output('End _cyco_make_book');
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
CycoInstallDebug::getInstance()->output('Start _cyco_activate_block. Block:' . $block);
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
CycoInstallDebug::getInstance()->output('End _cyco_activate_block');
}

/**
 * Place blocks in regions.
 */
function _cyco_place_blocks() {
CycoInstallDebug::getInstance()->output('Start _cyco_place_blocks');
  _cyco_activate_block('system', 'user-menu', 'sidebar_second',
      'cybercourse', '', 0, -1, '<none>');
  _cyco_activate_block('menu', 'menu-footer', 'footer',
      'cybercourse', '', 0, 0, '<none>');
  $course_node 
      = _cyco_node_load_by_title('Your course', 'course_page');
  //Cache the menu tree for this block.
  $rendered = _cbb_get_book_tree( $course_node->nid );
  $course_block_id = 'cbb_' . $course_node->nid;
  _cyco_activate_block('cyco_book_blocks', $course_block_id, 'sidebar_second', 
      'cybercourse', '', 0, 0);
  $blueprint_node 
      = _cyco_node_load_by_title('Your blueprint', 'blueprint_page');
  $rendered = _cbb_get_book_tree( $blueprint_node->nid );
  $blueprint_block_id = 'cbb_' . $blueprint_node->nid;
  _cyco_activate_block('cyco_book_blocks', $blueprint_block_id, 'sidebar_second', 
      'cybercourse', '', 0, 1);
  //The blueprint block is only visible to some roles.
  $roles_see_block = array(
    _cyco_get_role_id_from_name('administrator'),
    _cyco_get_role_id_from_name('author'),
    _cyco_get_role_id_from_name('reviewer'),
    _cyco_get_role_id_from_name('instructor'),
    _cyco_get_role_id_from_name('grader'),
  );
  _cyco_set_block_role_visibility( 'cyco_book_blocks', $blueprint_block_id, 
      $roles_see_block );
  //Set up some other blocks.
  _cyco_activate_block('menu', 'menu-tools', 'sidebar_second',
      'cybercourse', '', 0, 2);
  _cyco_activate_block('user', 'login', 'sidebar_second',
      'cybercourse', '', 0, 4);
  _cyco_activate_block('search', 'form', 'sidebar_second',
      'cybercourse', '', 0, 5);
  //Position the footer.
  $footer_menu_machine_name = _cyco_find_menu_machine_name('Footer');
  _cyco_activate_block('menu', $footer_menu_machine_name, 'footer',
      'cybercourse', '', 0, 1);
CycoInstallDebug::getInstance()->output('End _cyco_place_blocks');
}

/**
 * Set up block visibility rules.
 */
function _cyco_set_block_visibility() {
CycoInstallDebug::getInstance()->output('Start _cyco_set_block_visibility');
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
CycoInstallDebug::getInstance()->output('End _cyco_set_block_visibility');
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
  CycoInstallDebug::getInstance()->output('Start set frontpage');
  $welcome = _cyco_node_load_by_title('Welcome', 'page');
  $welcome_nid = $welcome->nid;
//  CycoInstallDebug::getInstance()->output('$welcome_nid: ' . $welcome_nid);
  variable_set('site_frontpage', 'node/' . $welcome_nid);
  CycoInstallDebug::getInstance()->output('End set frontpage');
}

/**
 * Add links to the main menu.
 */
function _cyco_add_links_main_menu() {
CycoInstallDebug::getInstance()->output('Start _cyco_add_links_main_menu');
  _cyco_add_menu_item('Welcome', 'page', 'main-menu', 0);
  _cyco_add_menu_item('About', 'page', 'main-menu', 1);
  _cyco_add_menu_item('Help', 'page', 'main-menu', 2);
CycoInstallDebug::getInstance()->output('End _cyco_add_links_main_menu');
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
CycoInstallDebug::getInstance()->output('Start _cyco_add_classes2blocks');
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
CycoInstallDebug::getInstance()->output('End _cyco_add_classes2blocks');
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

/**
 * Turn on Cyco modules. Don't know why this is needed.
 * If it isn't here, some Cyco modules are not 
 * enabled.
 */
function _cyco_enable_modules() {
CycoInstallDebug::getInstance()->output('Start _cyco_enable_modules');
  $modules = array(
    'cyco_core',
    'cyco_install_course_blueprint_types',
    'cyco_install_groups',
    'cyco_exercises',
    'cyco_exercises_services',
    'cyco_exercises_views',
    'cyco_badges',
    'cyco_pseudents',
    'cyco_patterns',
    'cyco_toggle_sidebar',
    'book_rearrange_collapse',
    'book_top_navbar',
    'cyco_add_pages',
    'cyco_book_blocks',
    'cyco_toc',
    'cyco_node_edit_tweaks',
    'cyco_book_mods',
    'cyco_collapse_summary',
  );
  module_enable($modules, TRUE);
CycoInstallDebug::getInstance()->output('End _cyco_enable_modules');
}

/**
 * Theme settings for two themes: cybercourse, and 
 * cybercourse_submission.
 */
function _cyco_theme_stuff() {
  //Enable/disable themes.
  theme_enable(
      array(
        //seven is the admin theme.
        'seven', 
        //cybercourse is theme for most things.
        'cybercourse', 
        //cybercourse_submission is the theme for popups 
        //students use to submit their work.
        'cybercourse_submission',
      )
  );
  theme_disable(array('bartik'));
  //Set the default theme.
  variable_set('theme_default', 'cybercourse');  
  //Settings for the CyberCourse theme.
  _cyco_cybercourse_theme_settings();
  //Settings for the CyberCourse submission theme.
  _cyco_cybercourse_submission_theme_settings();
  //Set the admin theme.
  db_update('system')
    ->fields(array('status' => 1))
    ->condition('type', 'theme')
    ->condition('name', 'seven')
    ->execute();
  variable_set('admin_theme', 'seven');
  variable_set('node_admin_theme', '1');
}

/**
 * Define settings for the CyberCourse theme.
 */
function _cyco_cybercourse_theme_settings() {
  $var_name = 'theme_cybercourse_settings';
  $settings = variable_get($var_name, array());
  $settings['bootstrap_bootswatch'] = 'cerulean';
  //Turn off tooltips.
  $settings['bootstrap_tooltip_enabled'] = 0;
  //Set the logo.
  $theme_path = drupal_get_path('theme', 'cybercourse');
  $settings['logo_path'] = $theme_path . '/images/logo_white_fg.png';
  //Set the shortcut icon.
  $settings['favicon_path'] = $theme_path . '/images/logo_blue_fg.png';
  variable_set($var_name, $settings);
}

/**
 * Define settings for the CyberCourse submission theme.
 * This is the theme for popups students use to submit their work.
 */
function _cyco_cybercourse_submission_theme_settings() {
  $var_name = 'theme_cybercourse_submission_settings';
  $settings = variable_get($var_name, array());
  $settings['bootstrap_bootswatch'] = 'cerulean';
  $settings['bootstrap_breadcrumb'] = 0;
  $settings['bootstrap_breadcrumb_home'] = 0;
  //Set the logo.
  $theme_path = drupal_get_path('theme', 'cybercourse_submission');
  $settings['logo_path'] = $theme_path . '/images/logo_white_fg.png';
  //Set the shortcut icon.
  $settings['favicon_path'] = $theme_path . '/images/logo_blue_fg.png';
  variable_set($var_name, $settings);
}

function _cyco_add_links_cp_menu1() {
CycoInstallDebug::getInstance()->output('Starting _cyco_add_links_cp_menu1');
  $items = array();
  $menu_name = 'menu-cp-actions';
  $language = LANGUAGE_NONE;
  $module = 'cyco_core';
  
  //Create top level items.
  $plid = 0;
  $items[] = array(
    'link_path' => 'courses-and-keywords',
    'link_title' => 'Courses and keywords',
    'weight' => 0,
    'menu_name' => $menu_name,
    'expanded' => TRUE,
    'language' => $language,
    'plid' => $plid,
    'module' => $module,
    'options' => array(
      'attributes' => array(
        'title' => 'Manage course pages and keywords.',
      ),
    ),
  );
  $items[] = array(
    'link_path' => 'blueprints-and-keywords',
    'link_title' => 'Blueprints and keywords',
    'weight' => 10,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $plid,
    'module' => $module,
    'options' => array(
      'attributes' => array(
        'title' => 'A blueprint is a design for a course.',
      ),
    ),
  );
  $items[] = array(
    'link_path' => 'exercises',
    'link_title' => 'Exercises and rubrics',
    'weight' => 20,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $plid,
    'module' => $module,
    'options' => array(
      'attributes' => array(
        'title' => 'Exercises are tasks that students do. Graders use '
        . 'rubrics to grade students\' work.',
      ),
    ),
  );
  $items[] = array(
    'link_path' => 'pseudent-poses',
    'link_title' => 'Pseudent poses',
    'weight' => 30,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $plid,
    'module' => $module,
    'options' => array(
      'attributes' => array(
        'title' => 'Pseudents take courses along with real students.',
      ),
    ),
  );
  $items[] = array(
    'link_path' => 'patterns',
    'link_title' => 'Patterns',
    'weight' => 40,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $plid,
    'module' => $module,
    'options' => array(
      'attributes' => array(
        'title' => 'Patterns are common ways of doing things.',
      ),
    ),
  );
  $items[] = array(
    'link_path' => 'basic-pages',
    'link_title' => 'Basic pages',
    'weight' => 50,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $plid,
    'module' => $module,
    'options' => array(
      'attributes' => array(
        'title' => 'Pages that are not part of a course or blueprint, like'
        . 'the home page.',
      ),
    ),
  );
  $items[] = array(
    'link_path' => 'workflow-tagged',
    'link_title' => 'Content that needs work',
    'weight' => 60,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $plid,
    'module' => $module,
    'options' => array(
      'attributes' => array(
        'title' => 'See content that has workflow tags attached.',
      ),
    ),
  );
  $items[] = array(
    'link_path' => 'classes',
    'link_title' => 'Classes',
    'weight' => 70,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $plid,
    'module' => $module,
    'options' => array(
      'attributes' => array(
        'title' => 'Classes are groups of students taking a course, with '
        . 'an instructor.',
      ),
    ),
  );
  $items[] = array(
    'link_path' => 'admin/people',
    'link_title' => 'Users',
    'weight' => 80,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $plid,
    'module' => $module,
    'options' => array(
      'attributes' => array(
        'title' => 'Manage user accounts.',
      ),
    ),
  );
  $items[] = array(
    'link_path' => 'admin/content',
    'link_title' => 'Other',
    'weight' => 90,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $plid,
    'module' => $module,
    'options' => array(
      'attributes' => array(
        'title' => 'Change site appearance, backup the site, ...',
      ),
    ),
  );
  global $_cyco_install_cp_top_level_mlids;
  $_cyco_install_cp_top_level_mlids = array();
  foreach ( $items as $item ) {
    $_cyco_install_cp_top_level_mlids[ $item['link_path'] ] = menu_link_save($item);
  }
CycoInstallDebug::getInstance()->output('End _cyco_add_links_cp_menu1');
  return $_cyco_install_cp_top_level_mlids;
}

//  CycoInstallDebug::getInstance()->output('CP menu items - top-level.');
//  CycoInstallDebug::getInstance()->output(
//      '<pre>$items: '.print_r($items, TRUE).'</pre>'
//  );
//  CycoInstallDebug::getInstance()->output(
//      '<pre>$top_level_mlids: '.print_r($_cyco_install_cp_top_level_mlids, TRUE).'</pre>'
//  );
function _cyco_add_links_cp_menu2() {
CycoInstallDebug::getInstance()->output('Starting _cyco_add_links_cp_menu2');
  global $_cyco_install_cp_top_level_mlids;
  $menu_name = 'menu-cp-actions';
  $language = LANGUAGE_NONE;
  $module = 'cyco_core';
  //Courses and keywords submenu
  $items = array();
  $items[] = array(
    'link_path' => 'courses-and-keywords',
    'link_title' => 'List course pages and keywords',
    'weight' => 0,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $_cyco_install_cp_top_level_mlids[ 'courses-and-keywords' ],
    'module' => $module,
  );
  $items[] = array(
    'link_path' => 'node/add/course-page?book_op=newbook',
    'link_title' => 'Create a new course',
    'weight' => 10,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $_cyco_install_cp_top_level_mlids[ 'courses-and-keywords' ],
    'module' => $module,
  );
  $items[] = array(
    'link_path' => 'admin/structure/taxonomy/keywords',
    'link_title' => 'Manage keywords',
    'weight' => 20,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $_cyco_install_cp_top_level_mlids[ 'courses-and-keywords' ],
    'module' => $module,
  );
  foreach ( $items as $item ) {
    menu_link_save($item);
  }
CycoInstallDebug::getInstance()->output('End _cyco_add_links_cp_menu2');
}
  
//  CycoInstallDebug::getInstance()->output('CP menu items - Courses and keywords submenu.');
//  CycoInstallDebug::getInstance()->output(
//      '<pre>$items: '.print_r($items, TRUE).'</pre>'
//  );

  function _cyco_add_links_cp_menu2a() {
CycoInstallDebug::getInstance()->output('Starting _cyco_add_links_cp_menu2a');
  global $_cyco_install_cp_top_level_mlids;
  $menu_name = 'menu-cp-actions';
  $language = LANGUAGE_NONE;
  $module = 'cyco_core';

  //Blueprints and keywords submenu
  $items = array();
  $items[] = array(
    'link_path' => 'blueprints-and-keywords',
    'link_title' => 'List blueprints pages and keywords',
    'weight' => 0,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $_cyco_install_cp_top_level_mlids[ 'blueprints-and-keywords' ],
    'module' => $module,
  );
  $items[] = array(
    'link_path' => 'node/add/blueprint-page?book_op=newbook',
    'link_title' => 'Create a new blueprint',
    'weight' => 10,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $_cyco_install_cp_top_level_mlids[ 'blueprints-and-keywords' ],
    'module' => $module,
  );
  $items[] = array(
    'link_path' => 'admin/structure/taxonomy/blueprint_keywords',
    'link_title' => 'Manage blueprint keywords',
    'weight' => 20,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $_cyco_install_cp_top_level_mlids[ 'blueprints-and-keywords' ],
    'module' => $module,
  );
  foreach ( $items as $item ) {
    menu_link_save($item);
  }
CycoInstallDebug::getInstance()->output('End _cyco_add_links_cp_menu2a');
}

function _cyco_add_links_cp_menu3() {
CycoInstallDebug::getInstance()->output('Starting _cyco_add_links_cp_menu3');
  global $_cyco_install_cp_top_level_mlids;
  $menu_name = 'menu-cp-actions';
  $language = LANGUAGE_NONE;
  $module = 'cyco_core';

  //Exercises and rubics submenu
  $items = array();
  $items[] = array(
    'link_path' => 'exercises',
    'link_title' => 'List exercises',
    'weight' => 0,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $_cyco_install_cp_top_level_mlids[ 'exercises' ],
    'module' => $module,
  );
  $items[] = array(
    'link_path' => 'node/add/exercise',
    'link_title' => 'Add new exercise',
    'weight' => 10,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $_cyco_install_cp_top_level_mlids[ 'exercises' ],
    'module' => $module,
  );
  $items[] = array(
    'link_path' => 'admin/structure/taxonomy/keywords',
    'link_title' => 'Manage exercise keywords',
    'weight' => 20,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $_cyco_install_cp_top_level_mlids[ 'exercises' ],
    'module' => $module,
  );
  $items[] = array(
    'link_path' => 'rubric-items',
    'link_title' => 'List rubric items',
    'weight' => 30,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $_cyco_install_cp_top_level_mlids[ 'exercises' ],
    'module' => $module,
  );
  $items[] = array(
    'link_path' => 'node/add/rubric-item',
    'link_title' => 'Add new rubric item',
    'weight' => 40,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $_cyco_install_cp_top_level_mlids[ 'exercises' ],
    'module' => $module,
  );
  $items[] = array(
    'link_path' => 'admin/structure/taxonomy/rubric_item_categories',
    'link_title' => 'Manage rubric item categories',
    'weight' => 50,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $_cyco_install_cp_top_level_mlids[ 'exercises' ],
    'module' => $module,
  );
  $items[] = array(
    'link_path' => 'list-model-solutions',
    'link_title' => 'List model solutions',
    'weight' => 60,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $_cyco_install_cp_top_level_mlids[ 'exercises' ],
    'module' => $module,
  );
  $items[] = array(
    'link_path' => 'node/add/model-exercise-solution',
    'link_title' => 'Add model solution',
    'weight' => 70,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $_cyco_install_cp_top_level_mlids[ 'exercises' ],
    'module' => $module,
  );
  foreach ( $items as $item ) {
    menu_link_save($item);
  }
CycoInstallDebug::getInstance()->output('End _cyco_add_links_cp_menu3');
}

function _cyco_add_links_cp_menu4() {
CycoInstallDebug::getInstance()->output('Starting _cyco_add_links_cp_menu4');
  global $_cyco_install_cp_top_level_mlids;
  $menu_name = 'menu-cp-actions';
  $language = LANGUAGE_NONE;
  $module = 'cyco_core';
  //Pseudent poses submenu
  $items = array();
  $items[] = array(
    'link_path' => 'pseudent-poses',
    'link_title' => 'List pseudent poses',
    'weight' => 0,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $_cyco_install_cp_top_level_mlids[ 'pseudent-poses' ],
    'module' => $module,
  );
  $items[] = array(
    'link_path' => 'node/add/pseudent-pose',
    'link_title' => 'Add a new pseudent pose.',
    'weight' => 10,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $_cyco_install_cp_top_level_mlids[ 'pseudent-poses' ],
    'module' => $module,
  );
  $items[] = array(
    'link_path' => 'admin/structure/taxonomy/pseudent_categories',
    'link_title' => 'Manage pseudent categories',
    'weight' => 20,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $_cyco_install_cp_top_level_mlids[ 'pseudent-poses' ],
    'module' => $module,
  );
  foreach ( $items as $item ) {
    menu_link_save($item);
  }
  
  //Patterns submenu
  $items = array();
  $items[] = array(
    'link_path' => 'patterns',
    'link_title' => 'List patterns',
    'weight' => 0,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $_cyco_install_cp_top_level_mlids[ 'patterns' ],
    'module' => $module,
  );
  $items[] = array(
    'link_path' => 'node/add/pattern',
    'link_title' => 'Add a pattern',
    'weight' => 10,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $_cyco_install_cp_top_level_mlids[ 'patterns' ],
    'module' => $module,
  );
  $items[] = array(
    'link_path' => 'admin/structure/taxonomy/pattern_categories',
    'link_title' => 'Manage pattern categories',
    'weight' => 20,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $_cyco_install_cp_top_level_mlids[ 'patterns' ],
    'module' => $module,
  );
  foreach ( $items as $item ) {
    menu_link_save($item);
  }
CycoInstallDebug::getInstance()->output('Starting _cyco_add_links_cp_menu4');
}

function _cyco_add_links_cp_menu5() {
CycoInstallDebug::getInstance()->output('Starting _cyco_add_links_cp_menu5');
  global $_cyco_install_cp_top_level_mlids;
  $menu_name = 'menu-cp-actions';
  $language = LANGUAGE_NONE;
  $module = 'cyco_core';
  //Basic pages submenu
  $items = array();
  $items[] = array(
    'link_path' => 'node/add/page',
    'link_title' => 'Add basic page',
    'weight' => 0,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $_cyco_install_cp_top_level_mlids[ 'basic-pages' ],
    'module' => $module,
  );
  $items[] = array(
    'link_path' => 'basic-pages',
    'link_title' => 'List basic pages',
    'weight' => 10,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $_cyco_install_cp_top_level_mlids[ 'basic-pages' ],
    'module' => $module,
  );
  foreach ( $items as $item ) {
    menu_link_save($item);
  }

  //Workflow tags submenu
  $items = array();
  $items[] = array(
    'link_path' => 'workflow-tagged',
    'link_title' => 'Workflow tagged',
    'weight' => 0,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $_cyco_install_cp_top_level_mlids[ 'workflow-tagged' ],
    'module' => $module,
  );
  $items[] = array(
    'link_path' => 'admin/structure/taxonomy/workflow_tags',
    'link_title' => 'Manage workflow tags',
    'weight' => 10,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $_cyco_install_cp_top_level_mlids[ 'workflow-tagged' ],
    'module' => $module,
  );
  foreach ( $items as $item ) {
    menu_link_save($item);
  }
CycoInstallDebug::getInstance()->output('End _cyco_add_links_cp_menu5');
}

function _cyco_add_links_cp_menu6() {
CycoInstallDebug::getInstance()->output('Starting _cyco_add_links_cp_menu6');
  $menu_name = 'menu-cp-actions';
  $language = LANGUAGE_NONE;
  $module = 'cyco_core';
  global $_cyco_install_cp_top_level_mlids;
  //Classes submenu
  $items = array();
  $items[] = array(
    'link_path' => 'classes',
    'link_title' => 'List classes',
    'weight' => 0,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $_cyco_install_cp_top_level_mlids[ 'classes' ],
    'module' => $module,
  );
  $items[] = array(
    'link_path' => 'node/add/class',
    'link_title' => 'Add class',
    'weight' => 10,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $_cyco_install_cp_top_level_mlids[ 'classes' ],
    'module' => $module,
  );
  foreach ( $items as $item ) {
    menu_link_save($item);
  }

  //Users submenu
  $items = array();
  $items[] = array(
    'link_path' => 'admin/people',
    'link_title' => 'List users',
    'weight' => 0,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $_cyco_install_cp_top_level_mlids[ 'admin/people' ],
    'module' => $module,
  );
  $items[] = array(
    'link_path' => 'admin/people/create',
    'link_title' => 'Add user',
    'weight' => 10,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $_cyco_install_cp_top_level_mlids[ 'admin/people' ],
    'module' => $module,
  );
  foreach ( $items as $item ) {
    menu_link_save($item);
  }
CycoInstallDebug::getInstance()->output('End _cyco_add_links_cp_menu6');
}

function _cyco_add_links_cp_menu7() {
CycoInstallDebug::getInstance()->output('Starting _cyco_add_links_cp_menu7');
  global $_cyco_install_cp_top_level_mlids;
  $menu_name = 'menu-cp-actions';
  $language = LANGUAGE_NONE;
  $module = 'cyco_core';
//Other submenu
  $items = array();
  $items[] = array(
    'link_path' => 'admin/content',
    'link_title' => 'All content',
    'weight' => 0,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $_cyco_install_cp_top_level_mlids[ 'admin/content' ],
    'module' => $module,
  );
  $items[] = array(
    'link_path' => 'admin/structure/token-custom',
    'link_title' => 'Custom tokens',
    'weight' => 10,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $_cyco_install_cp_top_level_mlids[ 'admin/content' ],
    'module' => $module,
  );
  $items[] = array(
    'link_path' => 'admin/config/system/backup_migrate',
    'link_title' => 'Backup',
    'weight' => 20,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $_cyco_install_cp_top_level_mlids[ 'admin/content' ],
    'module' => $module,
  );
  $items[] = array(
    'link_path' => 'admin/structure/block',
    'link_title' => 'Blocks',
    'weight' => 30,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $_cyco_install_cp_top_level_mlids[ 'admin/content' ],
    'module' => $module,
  );
  $items[] = array(
    'link_path' => 'admin/appearance',
    'link_title' => 'Appearance',
    'weight' => 40,
    'expanded' => TRUE,
    'menu_name' => $menu_name,
    'language' => $language,
    'plid' => $_cyco_install_cp_top_level_mlids[ 'admin/content' ],
    'module' => $module,
  );
  foreach ( $items as $item ) {
    menu_link_save($item);
  }
CycoInstallDebug::getInstance()->output('End _cyco_add_links_cp_menu7');

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
CycoInstallDebug::getInstance()->output('Starting _cyco_add_links_footer_menu');
  //Find the machine name of the footer menu.
  $footer_menu_machine_name = _cyco_find_menu_machine_name('Footer');
  if ( is_null($footer_menu_machine_name) ) {
    drupal_set_message('Could not find footer menu.');
    return;
  }
CycoInstallDebug::getInstance()->output('Middle _cyco_add_links_footer_menu');
  _cyco_add_menu_item('Copyright, you, 20xx', 'page', $footer_menu_machine_name, 0);
  _cyco_add_menu_item('Credits', 'page', $footer_menu_machine_name, 1);
  _cyco_add_menu_item('Terms of use', 'page', $footer_menu_machine_name, 2);
CycoInstallDebug::getInstance()->output('Ending _cyco_add_links_footer_menu');
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
