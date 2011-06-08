
/**
 * @file explorer.actions.js 
 * Actions, e. g. buttons, are assigned to core widget. The most important
 * is the action which open the dialog. Each action has settings which are
 * already there from a former request, e. g. loading of node form.
 */

Drupal.nodereference_explorer.actions = Drupal.nodereference_explorer.actions || {};

/**
 * Attaches actions to the core widget, e. g. buttons
 * @param
 *   DOM context
 */
Drupal.behaviors.NodereferenceExplorerActions = function(context) {
  //open the dialog
  $('.nodereference-explorer-action-open-dialog:not(.nodereference-explorer-processed)', context)
    .click(Drupal.nodereference_explorer.actions.browse).addClass('nodereference-explorer-processed');
  //removes the value
  $('.nodereference-explorer-action-remove-value:not(.nodereference-explorer-processed)', context)
    .click(Drupal.nodereference_explorer.actions.remove).addClass('nodereference-explorer-processed'); 
};

/**
 * Action for opening the dialog
 */
Drupal.nodereference_explorer.actions.browse = function() {
  var action = this;
  
  Drupal.nodereference_explorer.actions.startProgress(action); //progress feedback
  
  $id = $(action).attr('id');
  
  var settings = Drupal.nodereference_explorer.getSettings($id); //get the settings
  
  $.getJSON(settings['dialog'], function(data, textStatus) {
    Drupal.nodereference_explorer.addCSS(data.css); //add css files
    //add js files
	var inlines = Drupal.nodereference_explorer.addJS(data.js); 
	Drupal.nodereference_explorer.addInlineJS(inlines);

	var options = data.js.setting.dialog; //dialog options
	var value = $('#' + settings['widget']).val();
	if (settings['dialog_api'] == 'modalframe') {
	  options.onSubmit = Drupal.nodereference_explorer.modalframe.addOnSubmit(settings);
	  Drupal.nodereference_explorer.modalframe.open(settings['modalframe'], options, value);
	}
	else { //built-in default behaviour
	  options.buttons = Drupal.nodereference_explorer.dialog.addButtonPane(data.js.setting.actions, settings);
	  Drupal.nodereference_explorer.dialog.open(data.data, options, value); //open the dialog
	}
	//when dialog is opened, remove progress
	Drupal.nodereference_explorer.actions.endProgress(action);
  });
  return false; // This will not submit the form.
};

/**
 * Action for removing selected values and the preview
 */
Drupal.nodereference_explorer.actions.remove = function() {
  var action = this;
  
  Drupal.nodereference_explorer.actions.startProgress(action); //progress feedback
	  
  $id = $(this).attr('id');
  var settings = Drupal.nodereference_explorer.getSettings($id); //get the settings
  var widget = '#' + settings['widget']; //get the parent widget where the selected value will be saved to
  var type = settings['field_type'];
  Drupal.nodereference_explorer.actions.removeValue(widget, type);
  Drupal.nodereference_explorer.actions.endProgress(action);
  return false; // This will not submit the form.
};

/**
 * "Saves" the selected value to the parent widget
 * @param widget
 *   widget where the value is saved to
 * @param type
 *   type of target widget, e. g. nodereference. Determins the output format
 * @param value
 *   Actual value to be stored
 */
Drupal.nodereference_explorer.actions.setValue = function(widget, type, value) {
  eval('nodereference_explorer_plugin_content_' +type+ '_setValue(widget, value);');
};

/**
 * Clears the select item value. Like setValue() this is type specific
 * @param widget
 *   widget where the value is saved to
 * @param type
 *   type of target widget, e. g. nodereference. Determins the output format
 */
Drupal.nodereference_explorer.actions.removeValue = function(widget, type) {
  eval('nodereference_explorer_plugin_content_' +type+ '_removeValue(widget);');
};

/**
 * Add a progress throbber, simulating progress
 * @param
 *   widget element
 */
Drupal.nodereference_explorer.actions.startProgress = function(element) {
  $(element).after('<span class="views-throbbing">&nbsp</span>');
  if ($('input', element)) //if the action element is an input disable it, preventing multiple clicking
	$(element).attr('disabled', 'disabled');
};

/**
 * Stop progress when action done
 * @param
 *   widget element
 */
Drupal.nodereference_explorer.actions.endProgress = function(element) {
  $(element).next().remove();
  if ($('input', element))  //enable button again
    $(element).removeAttr("disabled");
};
