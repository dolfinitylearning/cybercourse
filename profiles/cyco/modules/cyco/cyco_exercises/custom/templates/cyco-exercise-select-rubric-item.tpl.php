<?php
/* 
* Template for HTML for UI for selecting rubric item for exercise.
 * 
 * Be careful when changing this. Changing the DOM hierarcy can break the 
 * JS. Adding classes is probably fine.
*/

/**
 * The interface for existing items.
 * 
 * Part 1. The container for all the existing items.
 * 
 */
?>
<div id='rubric-select-current-items-ui' class="form-item form-group" style="display:none">
  <label id='rubric-select-current-items-ui-title' for="rubric-select-ui">
    Rubric items
  </label>
<?php /* Collection of existing item templates goes here. See part 2. */ ?>
  <div id="rubric-select-link-item-container" class="form-item form-group">
    <button id="rubric-select-link-item" type="button"
            title="Link to a rubric item">Add rubric item link</button>
  </div>
</div>

<?php
/**
 * The interface for existing items.
 * 
 * Part 2. Template for one existing item.
 * 
 */
?>
  <div class="rubric-select-current-item-container" data-nid="" style="display:none">
    <span class="rubric-select-current-item-title"></span>
    <button class="rubric-select-current-item-unlink" type="button"
            title="Unlink this item from the exercise">Unlink</button>
    <button class="rubric-select-current-item-edit" type="button"
            title="View/edit this rubric item">Edit</button>
  </div>

<?php
/*
* The rubric item selection interface.
*/
?>
<div id='rubric-select-loading-throbber' style="display:none">
  Loading linked rubric items...
  <div class='ajax-progress ajax-progress-throbber'>
    <div class='throbber'>&nbsp;</div>
  </div>
</div>
<div id='rubric-select-ui' class="form-item form-group" style="display:none">
  <label id='rubric-select-ui-title' for="rubric-select-ui">
      Select a rubric item to link
  </label>
  <div id="rubric-select-ui-widget-container">
    <div id='rubric-select-ui-row1'>
      <div id='term-tree-container'>
        <div id='term-tree-label'>Filter rubric items</div>
        <div id='term-tree'></div>
      </div>
      <div id='filtered-terms-container'>
        <div id='filtered-terms-label'>Choose one item</div>
        <ul id='filtered-terms'></ul>
      </div>
    </div>
    <div id='rubric-select-ui-row2'>
      <div id='term-tree-ui-mt-cell'>
        &nbsp;
      </div>
      <div id='rubric-select-buttons-container'>
        <button id='rubric-select-create' type='button' 
            title="Create a new rubric item">Create</button>
        <button id='rubric-select-edit' type='button'
            title="View/edit the selected rubric item">Edit</button>
        <button id='rubric-select-link' type='button'
            title="Link the exercise to this item">Link</button>
        <button id='rubric-select-cancel' type='button'
            title="Forget it">Cancel</button>
      </div>
    </div>
  </div>
</div>

<?php
/*
* The rubric item creation interface.
*/
?>
<div id='rubric-create-loading-throbber' style="display:none">
  Loading rubric item...
  <div class='ajax-progress ajax-progress-throbber'>
    <div class='throbber'>&nbsp;</div>
  </div>
</div>
<div id="rubric-create-ui" class="rubric-create-ui-table" style="display:none">
<?php //Start outer UI table. 2 rows x 2 cells. Row 1 has most of the UI.
      //Row 2 has the buttons. ?>
  <div class="rubric-create-ui-row"><?php //Start row 1 of outer UI table.?>
    <div class="rubric-create-ui-cell">
    <?php //Start cell for title, categories, and notes. ?>
      <div class="rubric-create-ui-table">
      <?php //Start table, row 1 w/ title, row 2 w/ categories, row 3 w/ notes. ?>
        <div class="rubric-create-ui-row"><?php //One row for title label and field. ?>
          <div id="rubric-create-title-container" 
               class="form-item form-group rubric-create-ui-cell"><?php //Start cell. ?>
            <label id='rubric-create-title-label' for="rubric-create-title-container">
              Rubric item title
            </label>
            <div>
              <input id="rubric-create-title" class="form-item form-group" type="text" maxlength="200">
            </div>
          </div><?php //End cell.?>
        </div><?php //End row for title widgets.?>
        <div class="rubric-create-ui-row"><?php //Start row for category widgets. ?>
          <div id="rubric-create-categories-container" 
               class="form-item form-group rubric-create-ui-cell"><?php //Start cell. ?>
            <label id='rubric-create-categories-title' 
                   for="rubric-create-categories-container">
              Categories
            </label>
            <div id="rubric-create-categories" class="form-item form-group"><?php //Tree here. ?></div>
          </div><?php //End cell.?>
        </div><?php //End row for category widgets. ?>
        <div class="rubric-create-ui-row"><?php //Start row for notes widgets. ?>
          <div id="rubric-create-notes-container" 
               class="form-item form-group rubric-create-ui-cell"><?php //Start cell. ?>
            <label id='rubric-create-notes-title' for="rubric-create-notes-container">
              Notes
            </label>
            <textarea id="rubric-create-notes" class="form-item form-group"></textarea>
          </div><?php //End cell.?>
        </div><?php //End row for notes widgets. ?>
      </div><?php //End table with title, categories, and notes fields. ?>
    </div><?php //End row 1, cell 1 of outer table. Titles, categories, and notes. ?>
    <div id="rubric-create-phrases-container" class="rubric-create-ui-cell">
    <?php //Start row 1, cell 2 of outer table. Has all phrase widgets. ?>
      <label id='rubric-create-phrases-title' 
             for="rubric-create-phrases-container">
        Feedback phrases
      </label>
      <div class="rubric-create-ui-table"><?php //Start table for phrases.
        //Three rows of one column each. ?>
        <div class="rubric-create-ui-row"><?php //Start row good phrases. ?>
          <div id="rubric-create-phrases-good-container" 
               class="rubric-create-ui-cell rubric-create-phrases-container"><?php //Start cell good phrases. ?>
            <label id='rubric-create-phrases-good-label' 
                   for="rubric-create-phrases-good-container">
              Good
            </label>
            <div id="rubric-create-phrases-good-list"
                 class="rubric-create-ui-table">
                   <?php //Good phrases here, each one a CSS row, with 2 cells. ?>
            </div>
            <div>
              <button class="rubric-create-add-phrase" type="button" title="Add a phrase">+</button>              
            </div>
          </div><?php //End cell good phrases. ?>
        </div><?php //End row good phrases. ?>
        <div class="rubric-create-ui-row"><?php //Start row needs-work phrases. ?>
          <div id="rubric-create-phrases-needs-work-container" 
               class="rubric-create-ui-cell rubric-create-phrases-container"><?php //Start cell needs-work phrases. ?>
            <label id='rubric-create-phrases-needs-work-label' 
                   for="rubric-create-phrases-needs-work-container">
              Needs work
            </label>
            <div id="rubric-create-phrases-needs-work-list"
                 class="rubric-create-ui-table">
                   <?php //Needs-work phrases here, each one a CSS row, with 2 cells. ?>
            </div>
            <div>
              <button class="rubric-create-add-phrase" type="button" title="Add a phrase">+</button>              
            </div>
          </div><?php //End cell needs-work phrases. ?>
        </div><?php //End row needs-work phrases. ?>
        <div class="rubric-create-ui-row"><?php //Start row poor phrases. ?>
          <div id="rubric-create-phrases-poor-container" 
               class="rubric-create-ui-cell rubric-create-phrases-container"><?php //Start cell poor phrases. ?>
            <label id='rubric-create-phrases-poor-label' 
                   for="rubric-create-phrases-poor-container">
              Poor
            </label>
            <div id="rubric-create-phrases-poor-list"
                 class="rubric-create-ui-table">
                   <?php //Poor phrases here, each one a CSS row, with 2 cells. ?>
            </div>
            <div>
              <button class="rubric-create-add-phrase" type="button" title="Add a phrase">+</button>              
            </div>
          </div><?php //End cell poor phrases. ?>
        </div><?php //End row poor phrases. ?>
      </div><?php //End table for phrases. ?>
    </div><?php //End rubric-create-phrases-container, cell of outer table. ?>
  </div><?php //End row 1 of outer UI table.?>
  <div class="rubric-create-ui-row form-item form-group"><?php //Start row 2 outer - for buttons. ?>
    <div id="rubric-create-extra-actions" 
         class="rubric-create-ui-cell"><?php //Start cell for extra buttons. ?>
      <button id='rubric-create-extra' type='button' 
          title="Forget it">Extra</button>
    </div><?php //End cell for extra buttons. ?>
    <div id="rubric-create-finish-buttons" 
         class="rubric-create-ui-cell"><?php //Start cell for finish buttons. ?>
      <div id='rubric-create-saving-throbber' style="display:none">
        That ol' time server action...
        <div class='ajax-progress ajax-progress-throbber'>
          <div class='throbber'>&nbsp;</div>
        </div>
      </div>
      
      <button id='rubric-create-save' type='button' 
          title="Save rubric item">Save</button>
      <button id='rubric-create-cancel' type='button' 
          title="Forget it">Cancel</button>
    </div><?php //End cell for finish buttons. ?>
  </div><?php //End row for buttons. ?>
</div><?php //End outer UI table. ?>

<?php
/*
 * Template for one existing phrase.
 */
?>
<div class="rubric-create-phrase-container rubric-create-ui-row"
     style="display:none"><?php //Start row. ?>
  <div class="rubric-create-ui-cell"><?php //Start cell ?>
    <input type="text">
  </div><?php //End cell ?>
  <div class="rubric-create-ui-cell"><?php //Start cell ?>
    <button type="button" title="Remove">X</button>
  </div><?php //End cell ?>
</div><?php //End row ?>

