

(function ($) {

// TODO: Replace with Drupal.behaviors
$(document).ready(function(){  

//$(".form-textarea").textareaCounter();   

	 $('.form-textarea').each(function(){
	    //maximum limit of characters allowed.
	    var maxlimit = 240;
	    // get current number of characters
	    //var length = $(this).val().length;
	    var length = $(this).val().split(/\b[\s,\.-:;]*/).length;
	    if(length >= maxlimit) {
			$(this).val($(this).val().substring(0, maxlimit));
			length = maxlimit;
		}
	    // update count on page load
	    $(this).parent().find('.counter').html( (maxlimit - length) + ' characters left');
	    // bind on key up event
	    $(this).keyup(function(){
		// get new length of characters
		//var new_length = $(this).val().length;
		var new_length = $(this).val().split(/\b[\s,\.-:;]*/).length;
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
