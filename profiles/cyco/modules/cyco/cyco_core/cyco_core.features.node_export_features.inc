<?php
/**
 * @file
 * cyco_core.features.node_export_features.inc
 */

/**
 * Implements hook_node_export_features_default().
 */
function cyco_core_node_export_features_default() {
//KRM
return;
  $node_export = array(
  'code_string' => 'array(
  (object) array(
      \'vid\' => \'13\',
      \'uid\' => \'0\',
      \'title\' => \'Welcome\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'1\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'bcc60946-265e-4384-bea9-7d71df262e14\',
      \'nid\' => \'1\',
      \'type\' => \'page\',
      \'language\' => \'und\',
      \'created\' => \'1403874607\',
      \'changed\' => \'1403894892\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'546ff16e-718d-40b0-88c4-2a4c2f55b036\',
      \'revision_timestamp\' => \'1403894892\',
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
      \'field_workflow_tags\' => array(),
      \'field_show_table_of_contents\' => array(
        \'und\' => array(
          array(
            \'value\' => \'0\',
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
      \'last_comment_timestamp\' => \'1403874607\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'0\',
      \'comment_count\' => \'0\',
      \'name\' => \'\',
      \'picture\' => \'0\',
      \'data\' => NULL,
      \'path\' => array(
        \'pid\' => \'1\',
        \'source\' => \'node/1\',
        \'alias\' => \'content/welcome\',
        \'language\' => \'und\',
      ),
      \'menu\' => array(
        \'link_title\' => \'Home\',
        \'mlid\' => 0,
        \'plid\' => \'0\',
        \'menu_name\' => \'main-menu\',
        \'weight\' => \'-50\',
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
  (object) array(
      \'vid\' => \'21\',
      \'uid\' => \'0\',
      \'title\' => \'Your course\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'2\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'a9627c71-dc1e-4770-8ef8-d021661441d2\',
      \'nid\' => \'2\',
      \'type\' => \'course_page\',
      \'language\' => \'und\',
      \'created\' => \'1403874607\',
      \'changed\' => \'1403898592\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'7987900a-407a-46cd-a7d6-0d341fc4f1aa\',
      \'revision_timestamp\' => \'1403898592\',
      \'revision_uid\' => \'1\',
      \'field_attachments\' => array(),
      \'field_body\' => array(
        \'und\' => array(
          array(
            \'value\' => "This is the first page of your course.\\r\\n\\r\\n.. pseudent:: 6\\r\\n\\r\\n This is not here.\\r\\n\\r\\nNeither is this.",
            \'summary\' => \'\',
          ),
        ),
      ),
      \'field_images\' => array(),
      \'field_keywords\' => array(),
      \'field_short_title\' => array(),
      \'field_workflow_tags\' => array(),
      \'field_show_table_of_contents\' => array(
        \'und\' => array(
          array(
            \'value\' => \'0\',
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
      \'book\' => array(
        \'mlid\' => \'396\',
        \'nid\' => \'2\',
        \'bid\' => \'2\',
        \'menu_name\' => \'book-toc-2\',
        \'plid\' => \'0\',
        \'link_path\' => \'node/2\',
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
        \'p1\' => \'396\',
        \'p2\' => \'0\',
        \'p3\' => \'0\',
        \'p4\' => \'0\',
        \'p5\' => \'0\',
        \'p6\' => \'0\',
        \'p7\' => \'0\',
        \'p8\' => \'0\',
        \'p9\' => \'0\',
        \'updated\' => \'0\',
        \'href\' => \'node/2\',
        \'title\' => \'Your course\',
      ),
      \'cid\' => \'0\',
      \'last_comment_timestamp\' => \'1403874607\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'0\',
      \'comment_count\' => \'0\',
      \'name\' => \'\',
      \'picture\' => \'0\',
      \'data\' => NULL,
      \'path\' => array(
        \'pid\' => \'2\',
        \'source\' => \'node/2\',
        \'alias\' => \'content/your-course\',
        \'language\' => \'und\',
      ),
      \'menu\' => NULL,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'9\',
      \'uid\' => \'0\',
      \'title\' => \'Your blueprint\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'2\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'fe6c00e0-1d97-4ab8-b58e-f35312e63daf\',
      \'nid\' => \'3\',
      \'type\' => \'blueprint_page\',
      \'language\' => \'und\',
      \'created\' => \'1403874607\',
      \'changed\' => \'1403887793\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'afae6f0c-ab0f-4fd7-b90f-4a2edc864c54\',
      \'revision_timestamp\' => \'1403887793\',
      \'revision_uid\' => \'1\',
      \'field_attachments\' => array(),
      \'field_blueprint_keywords\' => array(),
      \'field_body\' => array(
        \'und\' => array(
          array(
            \'value\' => "A blueprint for your course.\\r\\n ",
            \'summary\' => \'A blueprint for your course.\',
          ),
        ),
      ),
      \'field_images\' => array(),
      \'field_short_title\' => array(),
      \'field_workflow_tags\' => array(),
      \'field_show_table_of_contents\' => array(
        \'und\' => array(
          array(
            \'value\' => \'0\',
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
      \'book\' => array(
        \'mlid\' => \'397\',
        \'nid\' => \'3\',
        \'bid\' => \'3\',
        \'menu_name\' => \'book-toc-3\',
        \'plid\' => \'0\',
        \'link_path\' => \'node/3\',
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
        \'p1\' => \'397\',
        \'p2\' => \'0\',
        \'p3\' => \'0\',
        \'p4\' => \'0\',
        \'p5\' => \'0\',
        \'p6\' => \'0\',
        \'p7\' => \'0\',
        \'p8\' => \'0\',
        \'p9\' => \'0\',
        \'updated\' => \'0\',
        \'href\' => \'node/3\',
        \'title\' => \'Your blueprint\',
      ),
      \'cid\' => \'0\',
      \'last_comment_timestamp\' => \'1403874607\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'0\',
      \'comment_count\' => \'0\',
      \'name\' => \'\',
      \'picture\' => \'0\',
      \'data\' => NULL,
      \'path\' => array(
        \'pid\' => \'3\',
        \'source\' => \'node/3\',
        \'alias\' => \'content/your-blueprint\',
        \'language\' => \'und\',
      ),
      \'menu\' => NULL,
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'6\',
      \'uid\' => \'0\',
      \'title\' => \'About\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'1\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'73380895-4e3b-47b7-b4f1-96392e70a0f7\',
      \'nid\' => \'4\',
      \'type\' => \'page\',
      \'language\' => \'und\',
      \'created\' => \'1403874607\',
      \'changed\' => \'1403882514\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'e1faa190-d982-4cdf-ba11-31a73cc85eb2\',
      \'revision_timestamp\' => \'1403882514\',
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
      \'field_workflow_tags\' => array(),
      \'field_show_table_of_contents\' => array(
        \'und\' => array(
          array(
            \'value\' => \'0\',
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
      \'last_comment_timestamp\' => \'1403874607\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'0\',
      \'comment_count\' => \'0\',
      \'name\' => \'\',
      \'picture\' => \'0\',
      \'data\' => NULL,
      \'path\' => array(
        \'pid\' => \'4\',
        \'source\' => \'node/4\',
        \'alias\' => \'content/about\',
        \'language\' => \'und\',
      ),
      \'menu\' => array(
        \'link_title\' => \'About\',
        \'mlid\' => 0,
        \'plid\' => \'0\',
        \'menu_name\' => \'main-menu\',
        \'weight\' => \'-49\',
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
