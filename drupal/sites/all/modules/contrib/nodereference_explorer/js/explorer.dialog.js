
/**
 * @file explorer.dialog.js
 * This file builds and opens the built-in in document dialog.
 * It holds several events as well element masking to prevent
 * id collisions with the underlying form.
 */

Drupal.nodereference_explorer.dialog = Drupal.nodereference_explorer.dialog || {};

/**
 * Open the dialog with the specified options
 * @param dialog
 *   rendered html representation of dialog
 * @param options
 *   dialog options, e. g. height
 * @param value
 *   initial selection value
 */
Drupal.nodereference_explorer.dialog.open = function(dialog, options, value) {
  
  if (!options['dialogClass']) //add default dialog class specified in the dialog template if no CSS scope has been specified
    options['dialogClass'] = $(dialog).attr('class');
	
  $.extend(options, 
	{
	  modal: true,
	  autoOpen: true,
	  close: function(event) { //when dialog closes, destroy it and unmask node form	  
	    $(this).dialog('destroy');
	    $(this).empty();
	    Drupal.nodereference_explorer.dialog.unmask();
  	  },
  	  open: function(event) { //when the dialog opens get the selection value and mask the node form
  		Drupal.nodereference_explorer.dialog.mask();
  		$(this).prepend($('<input id="edit-selection" type="hidden" />').val(value)); 
  		Drupal.attachBehaviors(this);
  	  }
    }
  );
  
  //In jQuery UI 1.6 the scrollbar size has to be synchronized with the dialog container and button pane manually.
  //Therefore we have to assign listeners which react on dialog resize. In jQuery UI 1.7 this has been fixed.
  if (parseFloat($.ui['version']) < 1.7) {
    $.extend(options, 
	  {
	    focus:       function() {Drupal.nodereference_explorer.dialog.resetDialogContentSize(this, options.height);},
  	    resize:      function() {Drupal.nodereference_explorer.dialog.resetDialogContentSize(this, options.height);},
  	    resizeStart: function() {Drupal.nodereference_explorer.dialog.resetDialogContentSize(this, options.height);},
  	    resizeStop:  function() {Drupal.nodereference_explorer.dialog.resetDialogContentSize(this, options.height);}
	  }
    );
  }
  
  $(dialog).dialog(options); 
  //Fix for Chrome/Safari, where those browser sets width to 0
  $('.nodereference-explorer-dialog').css('width', 'auto');
};

/**
 * Adds the action buttons to the dialog's button pane
 * @param actions
 *   info for dialog buttons
 * @param settings
 *   action configuration, e. g. target widget and type
 */
Drupal.nodereference_explorer.dialog.addButtonPane = function(actions, settings) {
  var buttons = {};
  
  //confirmation button
  if (actions.ok)
  	ok = actions.ok;
  
  buttons[ok] = function() {
    var value = $('#edit-selection', this).val();
    var widget = '#' + settings['widget'];
    var type = settings['field_type'];
    if (value != $(widget).val()) //if different from old value, save it
	  Drupal.nodereference_explorer.actions.setValue(widget, type, value);
    $(this).dialog('close');
  };
  
  //cancel button
  if (actions.cancel)
  	cancel = actions.cancel;
  
  buttons[cancel] = function() {
    $(this).dialog('close');
  };
	
  return buttons;
};

/**
 * Sets the dialog content to its correct size when using a button pane
 * In jQuery UI 1.6 scrollbars are hidden behind the button pane. This fix
 * actually shortens the height of the actual content by the height of the
 * button pane
 * @param
 *   dialog content
 * @param
 *   options for dialog
 */
Drupal.nodereference_explorer.dialog.resetDialogContentSize = function(dialog, defaultHeight) {
  var container = $(dialog).parent(); //overall container
  var titlebar = $(dialog).siblings('.ui-dialog-titlebar'); //title
  var buttonpane = $(dialog).parent().siblings('.ui-dialog-buttonpane'); //button panel
	
  if (container.height() > 1) { //when container height is already known (all resize and focus events)
    $container_height = container.height();
    $buttonpane_height = buttonpane.height();
  }
  else { //when container height is not yet known (opening the dialog)
    $container_height = defaultHeight;
    $buttonpane_height = buttonpane.height()/2;
  }
  $(dialog).height($container_height - titlebar.outerHeight() - $buttonpane_height);
};

/**
 * Masking of node form widgets
 * Helper function for fixing the collision between the filter form 
 * and the node form.
 */
Drupal.nodereference_explorer.dialog.mask = function () {
  //mask node's title field
  $('#edit-title-wrapper').attr('id', 'edit-title-wrapper-masked'); 
  $('#edit-title').attr('id', 'edit-title-masked');
};

/**
 * Unmasking of node form widgets
 * Helper function for fixing the collision between the filter form
 * and the node form
 */
Drupal.nodereference_explorer.dialog.unmask = function () {
  //unmask node's title field
  $('#edit-title-wrapper-masked').attr('id', 'edit-title-wrapper');
  $('#edit-title-masked').attr('id', 'edit-title');
};