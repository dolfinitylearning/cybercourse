<?php
/**
 * @file
 * cyco-exercises-model-solutions.tpl.php
 *
 * Template for showing model solutions for an exercise.
 * 
 * Variables
 * - $models: The models.
 * - $phrase_groups[]['nid']: Solution node id.
 * - $phrase_groups[]['title']: Solution title.
 */
?>
<div id="cyco-exercises-model-solutions-container" class="form-item form-group">
  <label>Model solutions</label>
  <p>Here are the model solutions for this exercise.</p>
  <?php 
  if ( sizeof( $models ) == 0 ) { ?>
    <p>(There are no model solutions.)</p>
  <?php }
  else {
    foreach( $models as $nid => $title ) { ?>
      <p class="cyco-exercises-model-solutions-link">
        <?php 
        $result = l( $title, 'node/' . $nid, 
            array(
              'attributes' => array(
                'target' => '_blank',
              ),
            )
        );
        print $result;
        ?>
      </p>
    <?php } //End foreach.
  } //End there are models. ?>
  <p class="cyco-exercises-model-solutions-add"><?php
    $result = theme('menu_local_action', 
      array( 'element' => 
        array('#link' => 
          array(
            'title' => 'Add model solution',
            'href' => 
              'node/add/model-exercise-solution?field_exercise_solved=' . $exer_nid,
            'localized_options' => array(
              'attributes' => array(
                'target' => '_blank',
              ),
            )
          )
        )
      )
    );
    //theme() does strange things.
    $result = urldecode( $result );
    print $result;
  ?></p>
</div>
