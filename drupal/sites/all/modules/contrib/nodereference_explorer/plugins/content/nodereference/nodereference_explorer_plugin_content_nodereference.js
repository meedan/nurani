/**
 * @file nodereference_explorer_plugin_content_nodereference.js
 * Each Nodereference Explorer plugin has a client side implemenentation. It is about the saving
 * the selected value from the dialog to the underlying widget.
 */

/**
 * Save the value to the parent widget
 * @param widget
 *   parent widget
 * @param
 *   value to be saved, format: NODE_TITLE [nid: NID], e. g. Page [nid: 234]
 */
nodereference_explorer_plugin_content_nodereference_setValue = function(widget, value) {
  $(widget).val(value).blur(); //trigger change event for depending actions
}

/**
 * Removes the value from the parent widget and clears the preview
 * @param widget
 *   parent widget
 */
nodereference_explorer_plugin_content_nodereference_removeValue = function(widget) {
  $(widget).val('').blur();
}
  