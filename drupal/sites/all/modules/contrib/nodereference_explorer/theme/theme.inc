<?php
/**
 * @file
 * theme.inc
 * Template preprocess function for preparing necessary template variables and doing
 * theme related tasks.
 */

/**
 * Prepare the dialog template variables and add css,
 * as well as javascript and javascript settings
 * @param $vars template variables
 */
function template_preprocess_nodereference_explorer_dialog(&$vars) {
	
  //initialize template array variables	avoiding "not valid argument" error
  if (!$vars['filters'] || empty($vars['filters']))
	$vars['filters'] = array();
	
  if (!$vars['tabs'] || empty($vars['tabs']))
    $vars['tabs'] = array();
    
  if (!$vars['displays'] || empty($vars['displays']))
    $vars['displays'] = array();
}

/**
 * Theme the core widget
 * @param $element widget
 * @return rendered representation of autocomplete
 */
function theme_nodereference_explorer($element) {

  //embrace widget with a wrapper
  $output = '<div class="nodereference-explorer">';

  //call plugin specific theming function
  $output .= $element['#plugin']->theme_nodereference_explorer($element);

  $output .= '</div>';
  return $output;
}

/**
 * Theme an action button.
 * @param $element
 *  button
 */
function theme_nodereference_explorer_button($element) {
  //Currently it's just a thin wrapper around the theme_button()
  //function which only returns a button of type submit. The themed
  //representation is just adapted to achieve an input html tag
  //of the type button.
  $button = theme('button', $element);
  return str_ireplace('type="submit"', 'type="button"', $button);
}

/**
 * Template for selectable row fields. This is used by grid,
 * list and unformatted view plugins.
 * @param $vars template variables
 */
function template_preprocess_nodereference_explorer_view_row_fields_selectable(&$vars) {
  template_preprocess_views_view_fields($vars);

  if ($vars['view']->display_handler->options['row_plugin'] == 'fields_selectable') {

    //if no node id/title is excluded from display, get it from the view result.
    $nid =   isset($vars['fields']['nid']) ? $vars['fields']['nid']->raw : $vars['row']->nid;
    $title = isset($vars['fields']['title']) ? $vars['fields']['title']->raw : $vars['row']->node_title;

    //when nid is included it will be attached as inline html for selection (field selectable)
    if (!isset($vars['fields']['nid'])) {
      $vars['fields']['nid']->raw = $nid;
      $vars['fields']['nid']->inline = true;
      $vars['fields']['nid']->inline_html = 'span';
      $vars['fields']['nid']->element_type = 'span';
      $vars['fields']['nid']->class = 'nid';
    }
    $element = array(
      '#type' => 'radio',
      '#id' => form_clean_id('selectable'),
      '#name' => 'nodereference-explorer-dialog',
      '#return_value' => "$title [nid:$nid]",
    );
    $vars['fields']['nid']->content .= drupal_render($element);
  }
}