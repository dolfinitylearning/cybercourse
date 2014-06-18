<?php

/**
 * @file
 * Template used by SWIM to show content only, with no headers, etc.
 * It loads a small stylesheet in this directory. The body tag has an 
 * id of content-only. This makes it easy to add your own styling.
 *
 * Available variables:
 * - $stylesheets: Array of stylesheet URLs.
 * - $title: Page title.
 * - $content: The main content of the current page.
 */
?><!DOCTYPE html>
<html>
  <head>
    <title>
      <?php print $title; ?>
    </title>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <?php
    if ( isset( $stylesheets ) ) {
      foreach( $stylesheets as $stylesheet ) {
        print '<link rel="stylesheet" href="' . $stylesheet . "\">\n";
      }
    }
    if ( isset( $javascript_files ) ) {
      foreach( $javascript_files as $file ) {
        print '<script src="' . $file . "\"></script>\n";
      }
    }
    ?>
  </head>
  <body id="content-only">
    <?php print $content; ?>
  </body>
</html>
