<?php
//KRM: Not working. See: https://drupal.org/node/1157794
/**
 * @file
 * Default theme implementation for field collection items.
 *
 * Available variables:
 * - $content: An array of comment items. Use render($content) to print them all, or
 *   print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $title: The (sanitized) field collection item label.
 * - $url: Direct url of the current entity if specified.
 * - $page: Flag for the full page state.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. By default the following classes are available, where
 *   the parts enclosed by {} are replaced by the appropriate values:
 *   - entity-field-collection-item
 *   - field-collection-item-{field_name}
 *
 * Other variables:
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 *
 * @see template_preprocess()
 * @see template_preprocess_entity()
 * @see template_process()
 */
?>
<div class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <div class="content"<?php print $content_attributes; ?>>
    <?php 
      $item = $content['field_attainment_level_name']['#object'];
      $entity = $item->field_attainment_level_name;
      $name = $entity[LANGUAGE_NONE][0]['safe_value'];
      print '<h1>' . $name . '</h1>';
      $entity = $item->field_attainment_level_score;
      $score = $entity[LANGUAGE_NONE][0]['value'];
      print '<h1>' . $score . '</h1>';
//      print '<pre>'.print_r($entity,TRUE).'</pre>';
//      foreach ( $entity->field_attainment_levels[LANGUAGE_NONE] as $level ) {
//        $path = taxonomy_term_uri($term['taxonomy_term']);
//        $term_url = $path['path'];
//        $term_name = $term['taxonomy_term']->name;
//        print '<p>' . l( $term_name, $term_url ) . '</p>';
//      }
    ?>
    <?php print '<pre>'.print_r($content,TRUE).'</pre>'; ?>
    <?php
      print render($content);
    ?>
  </div>
</div>
