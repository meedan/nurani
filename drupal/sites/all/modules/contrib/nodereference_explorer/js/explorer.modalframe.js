
/**
 * @file
 * explorer.modalframe.js
 * This script contains an action button for a nodereference_explorer widget
 * to use the Modal Frames API module to open the popup views.
 */

Drupal.nodereference_explorer.modalframe = Drupal.nodereference_explorer.modalframe || {};

/**
 * Open a modalframe dialog
 */
Drupal.nodereference_explorer.modalframe.open = function(path, options, value) { 
  $.extend(options, {
    // TODO these options need to be (1) specific to modalframe dialog instances
    // and (2) presented in the settings form or translated from the options
    // there. autoFit is necessary to prevent the dialog from changing size all
    // the time.
    url: path +'/'+ Drupal.encodeURIComponent(value),
    autoFit: false
  });
  //console.log(path+'/'+ Drupal.encodeURIComponent(value));
  Drupal.modalFrame.open(options);
};
/**
 * Saves the selected value to the parent widget
 * @param
 *   widget settings
 */
Drupal.nodereference_explorer.modalframe.addOnSubmit = function(settings) {
  return function (args) {
    if (args) {
      var widget = '#' + settings['widget'];
      var type = settings['field_type'];
      Drupal.nodereference_explorer.actions.setValue(widget, type, args.selection);
    }
  };
};
