
/**
 * @file explorer.preview.js
 * The preview of a node (if enabled) is rendered next to the core widget.
 * It's retrieved via JSON because a server-side approach breaks other
 * CCK fields.
 */

Drupal.nodereference_explorer.preview = Drupal.nodereference_explorer.preview || {};

/**
 * Preview behavior. Each preview wrapper loads the preview if the core widget changes
 * @param
 *   DOM context
 */
Drupal.behaviors.NodereferenceExplorerPreview = function(context) {
  $('.nodereference-explorer-preview:not(.nodereference-explorer-processed)', context)
    .each(function (index, domElement) {
      var preview = domElement;
      
      //get the settings
      $id = $(preview).attr('id');
      var settings = Drupal.nodereference_explorer.getSettings($id); 
      var path = settings['preview'];
      var widget = '#' + settings['widget'];
      
      //attach change action to core widget, triggered when dialog returns a value
      //when loading an editing node with nodereference fields
      //  when loading a selection from a autocomplete view selection
      $(widget).blur(function(event) {
    	var val = $(this).val(); //current value
    	if (val != '') {//placeholder while preview loads
    	  $(preview).text(Drupal.t('Preview loading, please wait...'));
          Drupal.nodereference_explorer.preview.getPreview(preview, path, val);
    	}
    	else { //clear preview if no widget value
    	  $(preview).text('');
    	}
      });
      $(widget).blur();
    })
    .addClass('nodereference-explorer-processed');
};

/**
 * Load the preview via JSON
 * @parm preview
 *   wrapper area
 * @parm path
 *   url returning preview
 * @param value
 *   Node information determing which view item will be rendered
 */
Drupal.nodereference_explorer.preview.getPreview = function (preview, path, value) {
  $view_dom_id = $(preview).attr('id');
  $.getJSON(path, { val: value, view_dom_id: $view_dom_id }, function(data, textStatus) {
    if (data.data) { //insert the preview into the wrapper
      $(preview).html(data.data);
      // Allow other modules to add functionality to the returned DOM object, 
      // e.g. when preview returns an image with rel='lightbox'.
       Drupal.attachBehaviors(preview);
      //the behaviors hide the node form's title, therefore force it to show up
      Drupal.nodereference_explorer.preview.showTitle();
    }
    else { //clear preview, if no result
      $(preview).text('');
    }
  });
};

/**
 * Fix for id collisions between node form and view filter form.
 * Just make sure that the node form's title is displayed. Otherwise
 * no saving of newly created nodes is possible.
 */
Drupal.nodereference_explorer.preview.showTitle = function () {
  $('#edit-title-wrapper').show();
  $('#edit-title').show();	
};