

 (function ($) {
$(document).ready(function(){
	/**
	 * Character Counter for inputs and text areas showing characters left.
	 */
	$('.form-textarea').each(function(){
	    //maximum limit of characters allowed.
	    var maxlimit = 850;
	    // get current number of characters
	    var length = $(this).val().length;
	    if(length >= maxlimit) {
			$(this).val($(this).val().substring(0, maxlimit));
			length = maxlimit;
		}
	    // update count on page load
	    $(this).parent().find('.counter').html( (maxlimit - length) + ' characters left');
	    // bind on key up event
	    $(this).keyup(function(){
		// get new length of characters
		var new_length = $(this).val().length;
		if(new_length >= maxlimit) {
				$(this).val($(this).val().substring(0, maxlimit));
				//update the new length
				new_length = maxlimit;
			}
		// update count
		$(this).parent().find('.counter').html( (maxlimit - new_length) + ' characters left');
	    });
	});

});
})(jQuery);