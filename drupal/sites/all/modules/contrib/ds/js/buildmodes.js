
/**
 * Toggle all buildmodes at once.
 */
Drupal.behaviors.ds_buildmodes = function(context) {

	$('.block-all').bind('click', function() {
    var excluder = this;
    $(excluder).parents('tr').find('.checkbox-instance').not('.block-all').each(function() {
      if(excluder.checked) {
        $(this).attr('disabled', 'disabled');
      }
      else {
        $(this).attr('disabled', '');
      }
    });
  });
}