/**
 * @file nodereference_explorer_plugin_content_link.js
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
nodereference_explorer_plugin_content_link_setValue = function(widget, value) {
  
  $(widget).val(value).blur(); //trigger change event for depending actions  
  //apply regular expression to split string, e. g. Photo gallery: HDIM 2009 [nid: 4444]
  var matches = value.match(/^(?:\s*|(.*) )?\[\s*nid\s*:\s*(\d+)\s*\]$/);
  var title = matches[1];
  var nid = matches[2];
  $(widget+'-url').val('node/' +nid);
  $(widget+'-title').val(title);
}

/**
 * Removes the value from the parent widget and clears the preview
 * @param widget
 *   parent widget
 */
nodereference_explorer_plugin_content_link_removeValue = function(widget) {
  $(widget).val('').blur();
  $(widget+'-url').val('');
  $(widget+'-title').val('');
}