<?php

/**
 * Implements hook_css_alter()
 */
function nurani_css_alter(&$css) {
  if (isset($css['misc/ui/jquery.ui.theme.css'])) {
    $css['misc/ui/jquery.ui.theme.css']['data'] = drupal_get_path('theme', 'seven') . '/jquery.ui.theme.css';
  }

  // Remove style.css if style-rtl.css is included.
  global $language;
  if ($language->direction == LANGUAGE_RTL) {
    unset($css[drupal_get_path('theme', 'nurani') . '/css/core.css']);
  }
}

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
}

/**
 * Implements hook_preprocess_textarea()
 *
 * Removes resize drag handle from all text areas. Modern browsers implement
 * this natively these days.
 */
function nurani_preprocess_textarea(&$vars) {
  $vars['element']['#resizable'] = FALSE;
}
