
/**
 * The preview displays depend on the selected view. The list is updated
 * when the referenced view is changed. This action applies to the settings form.
 * @param
 *   DOM context
 */
Drupal.behaviors.NodereferenceExplorerSettings = function (context) {
	  
  $('#edit-advanced-view', context).change(function(event) {
    var advanced_view = this;
	$id = $(advanced_view).attr('id');
	var settings = Drupal.settings.nodereference_explorer[$id]; //get the settings
	var path = settings['path'];
	var view_name = $(this).val();
	var widget = settings['widget'];
	
    $.getJSON(path, {view: view_name}, function(data, textStatus) {
      $('#' + widget).children().remove();
      var displays = data.data;
      for (var id in displays) {
        var option = '<option value="' +id +'">' + displays[id] +'</option>';
        $('#' + widget).append(option);
      }
      var value = settings['value'];
      $('#' + widget).val(value);
    });
  });
  if ($('#edit-advanced-view:not(.nodereference-explorer-processed)', context))
    $('#edit-advanced-view', context).change().addClass('nodereference-explorer-processed'); 
 
};