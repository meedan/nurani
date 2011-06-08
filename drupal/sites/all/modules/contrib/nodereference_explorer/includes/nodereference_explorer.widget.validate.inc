<?php
/**
 * @file
 * nodereference_explorer.widget.validate.inc
 * Validation of widget settings
 */

/**
 * Check if the css file specified is correct.
 * @param $widget cck widget
 * @param $theme setting key
 */
function nodereference_explorer_widget_validate_theme_file($widget, $theme) {
  $theme_file = $widget[$theme];
  if (stripos($theme_file, '.css') == 0)
    form_set_error($theme, 'A theme file must be a valid css file (.css)!');

  if ($theme_file[0] == '/')
    form_set_error($theme, 'A theme file must no start with a slash ("/")!');
}

/**
 * Check if a textfield is an integer number
 * @param $widget cck widget
 * @param $prop settings property key
 * @param $label Label of the field for error output
 * @param $mandatory specify if the validation is mandatory
 */

function nodereference_explorer_widget_validate_textfield_number($widget, $prop, $label, $mandatory = FALSE) {
  if ($mandatory) {
    nodereference_explorer_widget_validate_integer($widget, $prop, $label);
  }
  else { //validate if set
    if (isset($widget[$prop]) && $widget[$prop] != '') {
      nodereference_explorer_widget_validate_integer($widget, $prop, $label);
    }
  }
}

/**
 * Check if a textfield is an integer number. Subfunction
 * of nodereference_explorer_widget_validate_textfield_number().
 * @param $widget cck widget
 * @param $prop settings property key
 * @param $label Label of the field for error output
 */
function nodereference_explorer_widget_validate_integer($widget, $prop, $label) {
  if (!is_numeric($widget[$prop]) || intval($widget[$prop]) != $widget[$prop] || $widget[$prop] <= 0) {
    form_set_error($prop, '\"$label\"' . t(" must be a positive integer."));
  }
}