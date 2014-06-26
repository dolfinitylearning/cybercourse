<?php
/**
 * @file
 * cyco_core.features.node_export_features.inc
 */

/**
 * Implements hook_node_export_features_default().
 */
function cyco_core_node_export_features_default() {
  $node_export = array(
  'code_string' => 'array(
  (object) array(
      \'vid\' => \'65\',
      \'uid\' => \'1\',
      \'title\' => \'Welcome\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'1\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'9fc1479d-050c-4259-86b5-36b1f2670479\',
      \'nid\' => \'41\',
      \'type\' => \'page\',
      \'language\' => \'und\',
      \'created\' => \'1403793167\',
      \'changed\' => \'1403793167\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'546ff16e-718d-40b0-88c4-2a4c2f55b036\',
      \'revision_timestamp\' => \'1403793167\',
      \'revision_uid\' => \'1\',
      \'field_attachments\' => array(),
      \'field_body\' => array(
        \'und\' => array(
          array(
            \'value\' => "Welcome to the site.\\r\\n ",
            \'summary\' => \'Welcome to the site.\',
          ),
        ),
      ),
      \'field_images\' => array(),
      \'field_keywords\' => array(),
      \'field_show_table_of_contents\' => array(
        \'und\' => array(
          array(
            \'value\' => \'0\',
          ),
        ),
      ),
      \'field_workflow_tags\' => array(
        \'und\' => array(
          array(
            \'tid\' => \'5\',
          ),
        ),
      ),
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
          \'sioc:Item\',
          \'foaf:Document\',
        ),
        \'title\' => array(
          \'predicates\' => array(
            \'dc:title\',
          ),
        ),
        \'created\' => array(
          \'predicates\' => array(
            \'dc:date\',
            \'dc:created\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'changed\' => array(
          \'predicates\' => array(
            \'dc:modified\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'body\' => array(
          \'predicates\' => array(
            \'content:encoded\',
          ),
        ),
        \'uid\' => array(
          \'predicates\' => array(
            \'sioc:has_creator\',
          ),
          \'type\' => \'rel\',
        ),
        \'name\' => array(
          \'predicates\' => array(
            \'foaf:name\',
          ),
        ),
        \'comment_count\' => array(
          \'predicates\' => array(
            \'sioc:num_replies\',
          ),
          \'datatype\' => \'xsd:integer\',
        ),
        \'last_activity\' => array(
          \'predicates\' => array(
            \'sioc:last_activity_date\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
      ),
      \'cid\' => \'0\',
      \'last_comment_timestamp\' => \'1403793167\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'1\',
      \'comment_count\' => \'0\',
      \'name\' => \'admin\',
      \'picture\' => \'0\',
      \'data\' => \'a:1:{s:7:"contact";i:1;}\',
      \'path\' => array(
        \'pid\' => \'48\',
        \'source\' => \'node/41\',
        \'alias\' => \'welcome\',
        \'language\' => \'und\',
      ),
      \'menu\' => NULL,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'53\',
      \'uid\' => \'1\',
      \'title\' => \'Your course\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'2\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'1dacb43e-17cc-4dfa-b245-3726f4e72712\',
      \'nid\' => \'38\',
      \'type\' => \'course_page\',
      \'language\' => \'und\',
      \'created\' => \'1403703917\',
      \'changed\' => \'1403703917\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'7987900a-407a-46cd-a7d6-0d341fc4f1aa\',
      \'revision_timestamp\' => \'1403703917\',
      \'revision_uid\' => \'1\',
      \'field_attachments\' => array(),
      \'field_body\' => array(
        \'und\' => array(
          array(
            \'value\' => "This is the first page of your course.\\r\\n \\r\\n.. pseudent:: 3\\n\\n    Looks good so far.\\n\\n\\r\\n\\r\\nThanks, Betty.\\r\\n \\r\\n.. pseudent:: 2\\n\\n    What is this site called?\\n\\n\\r\\n\\r\\nIt\'s called [site:name].\\r\\n\\r\\n\\r\\n\\r\\n ",
            \'summary\' => \'\',
          ),
        ),
      ),
      \'field_images\' => array(),
      \'field_keywords\' => array(),
      \'field_show_table_of_contents\' => array(
        \'und\' => array(
          array(
            \'value\' => \'1\',
          ),
        ),
      ),
      \'field_workflow_tags\' => array(),
      \'field_short_title\' => array(),
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
          \'sioc:Item\',
          \'foaf:Document\',
        ),
        \'title\' => array(
          \'predicates\' => array(
            \'dc:title\',
          ),
        ),
        \'created\' => array(
          \'predicates\' => array(
            \'dc:date\',
            \'dc:created\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'changed\' => array(
          \'predicates\' => array(
            \'dc:modified\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'body\' => array(
          \'predicates\' => array(
            \'content:encoded\',
          ),
        ),
        \'uid\' => array(
          \'predicates\' => array(
            \'sioc:has_creator\',
          ),
          \'type\' => \'rel\',
        ),
        \'name\' => array(
          \'predicates\' => array(
            \'foaf:name\',
          ),
        ),
        \'comment_count\' => array(
          \'predicates\' => array(
            \'sioc:num_replies\',
          ),
          \'datatype\' => \'xsd:integer\',
        ),
        \'last_activity\' => array(
          \'predicates\' => array(
            \'sioc:last_activity_date\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
      ),
      \'book\' => array(
        \'mlid\' => \'590\',
        \'nid\' => \'38\',
        \'bid\' => \'38\',
        \'menu_name\' => \'book-toc-38\',
        \'plid\' => \'0\',
        \'link_path\' => \'node/38\',
        \'router_path\' => \'node/%\',
        \'link_title\' => \'Your course\',
        \'options\' => array(),
        \'module\' => \'book\',
        \'hidden\' => \'0\',
        \'external\' => \'0\',
        \'has_children\' => \'0\',
        \'expanded\' => \'0\',
        \'weight\' => \'0\',
        \'depth\' => \'1\',
        \'customized\' => \'0\',
        \'p1\' => \'590\',
        \'p2\' => \'0\',
        \'p3\' => \'0\',
        \'p4\' => \'0\',
        \'p5\' => \'0\',
        \'p6\' => \'0\',
        \'p7\' => \'0\',
        \'p8\' => \'0\',
        \'p9\' => \'0\',
        \'updated\' => \'0\',
        \'href\' => \'node/38\',
        \'title\' => \'Your course\',
      ),
      \'cid\' => \'0\',
      \'last_comment_timestamp\' => \'1403703917\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'1\',
      \'comment_count\' => \'0\',
      \'name\' => \'admin\',
      \'picture\' => \'0\',
      \'data\' => \'a:1:{s:7:"contact";i:1;}\',
      \'path\' => array(
        \'pid\' => \'42\',
        \'source\' => \'node/38\',
        \'alias\' => \'content/your-course\',
        \'language\' => \'und\',
      ),
      \'menu\' => NULL,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'68\',
      \'uid\' => \'1\',
      \'title\' => \'Your blueprint\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'2\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'d25ba800-c5de-47cb-a7e3-2b53f4567822\',
      \'nid\' => \'43\',
      \'type\' => \'blueprint_page\',
      \'language\' => \'und\',
      \'created\' => \'1403801175\',
      \'changed\' => \'1403801175\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'afae6f0c-ab0f-4fd7-b90f-4a2edc864c54\',
      \'revision_timestamp\' => \'1403801175\',
      \'revision_uid\' => \'1\',
      \'field_attachments\' => array(),
      \'field_blueprint_keywords\' => array(),
      \'field_body\' => array(
        \'und\' => array(
          array(
            \'value\' => \'A blueprint for your course.\',
            \'summary\' => \'A blueprint for your course.\',
          ),
        ),
      ),
      \'field_images\' => array(),
      \'field_show_table_of_contents\' => array(
        \'und\' => array(
          array(
            \'value\' => \'0\',
          ),
        ),
      ),
      \'field_workflow_tags\' => array(),
      \'field_short_title\' => array(),
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
          \'sioc:Item\',
          \'foaf:Document\',
        ),
        \'title\' => array(
          \'predicates\' => array(
            \'dc:title\',
          ),
        ),
        \'created\' => array(
          \'predicates\' => array(
            \'dc:date\',
            \'dc:created\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'changed\' => array(
          \'predicates\' => array(
            \'dc:modified\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'body\' => array(
          \'predicates\' => array(
            \'content:encoded\',
          ),
        ),
        \'uid\' => array(
          \'predicates\' => array(
            \'sioc:has_creator\',
          ),
          \'type\' => \'rel\',
        ),
        \'name\' => array(
          \'predicates\' => array(
            \'foaf:name\',
          ),
        ),
        \'comment_count\' => array(
          \'predicates\' => array(
            \'sioc:num_replies\',
          ),
          \'datatype\' => \'xsd:integer\',
        ),
        \'last_activity\' => array(
          \'predicates\' => array(
            \'sioc:last_activity_date\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
      ),
      \'book\' => array(
        \'mlid\' => \'604\',
        \'nid\' => \'43\',
        \'bid\' => \'43\',
        \'menu_name\' => \'book-toc-43\',
        \'plid\' => \'0\',
        \'link_path\' => \'node/43\',
        \'router_path\' => \'node/%\',
        \'link_title\' => \'Your blueprint\',
        \'options\' => array(),
        \'module\' => \'book\',
        \'hidden\' => \'0\',
        \'external\' => \'0\',
        \'has_children\' => \'0\',
        \'expanded\' => \'0\',
        \'weight\' => \'0\',
        \'depth\' => \'1\',
        \'customized\' => \'0\',
        \'p1\' => \'604\',
        \'p2\' => \'0\',
        \'p3\' => \'0\',
        \'p4\' => \'0\',
        \'p5\' => \'0\',
        \'p6\' => \'0\',
        \'p7\' => \'0\',
        \'p8\' => \'0\',
        \'p9\' => \'0\',
        \'updated\' => \'0\',
        \'href\' => \'node/43\',
        \'title\' => \'Your blueprint\',
      ),
      \'cid\' => \'0\',
      \'last_comment_timestamp\' => \'1403801175\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'1\',
      \'comment_count\' => \'0\',
      \'name\' => \'admin\',
      \'picture\' => \'0\',
      \'data\' => \'a:1:{s:7:"contact";i:1;}\',
      \'path\' => array(
        \'pid\' => \'50\',
        \'source\' => \'node/43\',
        \'alias\' => \'blueprint/your-blueprint\',
        \'language\' => \'und\',
      ),
      \'menu\' => NULL,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'64\',
      \'uid\' => \'1\',
      \'title\' => \'About\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'1\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'9eae6016-57a3-4b4c-b929-388a4c5c225d\',
      \'nid\' => \'40\',
      \'type\' => \'page\',
      \'language\' => \'und\',
      \'created\' => \'1403792886\',
      \'changed\' => \'1403793124\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'e1faa190-d982-4cdf-ba11-31a73cc85eb2\',
      \'revision_timestamp\' => \'1403793124\',
      \'revision_uid\' => \'1\',
      \'field_attachments\' => array(),
      \'field_body\' => array(
        \'und\' => array(
          array(
            \'value\' => \'About this site.\',
            \'summary\' => \'About this site.\',
          ),
        ),
      ),
      \'field_images\' => array(),
      \'field_keywords\' => array(),
      \'field_show_table_of_contents\' => array(
        \'und\' => array(
          array(
            \'value\' => \'0\',
          ),
        ),
      ),
      \'field_workflow_tags\' => array(
        \'und\' => array(
          array(
            \'tid\' => \'5\',
          ),
        ),
      ),
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
          \'sioc:Item\',
          \'foaf:Document\',
        ),
        \'title\' => array(
          \'predicates\' => array(
            \'dc:title\',
          ),
        ),
        \'created\' => array(
          \'predicates\' => array(
            \'dc:date\',
            \'dc:created\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'changed\' => array(
          \'predicates\' => array(
            \'dc:modified\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'body\' => array(
          \'predicates\' => array(
            \'content:encoded\',
          ),
        ),
        \'uid\' => array(
          \'predicates\' => array(
            \'sioc:has_creator\',
          ),
          \'type\' => \'rel\',
        ),
        \'name\' => array(
          \'predicates\' => array(
            \'foaf:name\',
          ),
        ),
        \'comment_count\' => array(
          \'predicates\' => array(
            \'sioc:num_replies\',
          ),
          \'datatype\' => \'xsd:integer\',
        ),
        \'last_activity\' => array(
          \'predicates\' => array(
            \'sioc:last_activity_date\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
      ),
      \'cid\' => \'0\',
      \'last_comment_timestamp\' => \'1403792886\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'1\',
      \'comment_count\' => \'0\',
      \'name\' => \'admin\',
      \'picture\' => \'0\',
      \'data\' => \'a:1:{s:7:"contact";i:1;}\',
      \'path\' => array(
        \'pid\' => \'46\',
        \'source\' => \'node/40\',
        \'alias\' => \'about\',
        \'language\' => \'und\',
      ),
      \'menu\' => array(
        \'link_title\' => \'About\',
        \'mlid\' => 0,
        \'plid\' => \'0\',
        \'menu_name\' => \'main-menu\',
        \'weight\' => \'0\',
        \'options\' => array(),
        \'module\' => \'menu\',
        \'expanded\' => \'0\',
        \'hidden\' => \'0\',
        \'has_children\' => \'0\',
        \'customized\' => 0,
        \'parent_depth_limit\' => 8,
        \'description\' => \'\',
        \'enabled\' => 1,
      ),
      \'node_export_drupal_version\' => \'7\',
    ),
)',
);
  return $node_export;
}
