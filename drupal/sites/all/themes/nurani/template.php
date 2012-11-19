<?php

/**
 * Implements hook_preprocess_node().
 */
function nurani_preprocess_node(&$vars) {
  // Hide the node links ("Add comment", "Printer friendly version", "Print PDF")
  // on the comment and bundle pages.
  if (in_array($vars['type'], array('discussion', 'bundle'))) {
    $vars['content']['links']['#access'] = FALSE;
  }
}

/**
 * Implements hook_preprocess_page().
 *
 * Runs AFTER bowerbird_preprocess_page().
 */
function nurani_preprocess_page(&$vars) {
  // Add spin.js (see: http://fgnass.github.com/spin.js/)
  drupal_add_js(drupal_get_path('theme', 'bowerbird') . '/js/spin.min.js');
  // Add global spin.js settings for this theme
  drupal_add_js(array(
    'spin' => array(
      'lines' => 7, // The number of lines to draw
      'length' => 0, // The length of each line
      'width' => 20, // The line thickness
      'radius' => 0, // The radius of the inner circle
      'corners' => 1, // Corner roundness (0..1)
      'rotate' => 0, // The rotation offset
      'color' => '#fff', // #rgb or #rrggbb
      'speed' => 0.7, // Rounds per second
      'trail' => 56, // Afterglow percentage
      'shadow' => false, // Whether to render a shadow
      'hwaccel' => false, // Whether to use hardware acceleration
      'className' => 'spinner', // The CSS class to assign to the spinner
      'zIndex' => 2e9, // The z-index (defaults to 2000000000)
      'top' => 'auto', // Top position relative to parent in px
      'left' => 'auto' // Left position relative to parent in px
    ),
  ), 'setting');
}
