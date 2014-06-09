<?php
/* 
 * Obscures peek preview dialog until server replies. 
 */
?>
<style>
  .peek-obscurer {
    font-size: 200%;
    margin: 0;
    padding: 0;
    background-color: white;
    position: absolute;
    width: 100%;
    height: 100%;
    top: 0;
    left: 0;
  }
  .peek-obscurer img {
    float: left;
    margin-right: 1em;
  }
</style>
<p class="peek-obscurer">
  Working... <img src="<?php 
    print $obscurer_throbber_path;
  ?>throbber.png" alt="Working">
</p>


