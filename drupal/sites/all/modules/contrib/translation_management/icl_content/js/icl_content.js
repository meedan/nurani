function icl_content_lang_propagate(lang, speed) {
	var id = '#icl-content-translate-' + lang;    
	$('#icl-content').show('slow');
	$('#icl-content fieldset').hide();
        
        if ( $('#edit-minor-edit')) {
                if($('#edit-minor-edit').attr('checked')) {
                	$(id).hide(speed);
                } else {
                	$(id).show(speed);
                }
        }
        else {
        	$(id).show(speed);
        }
        
	if ($('#edit-icl-content-skip').val() == 'not') {
		$('#icl-content fieldset').hide();
	}
	if (lang.length == 0) {
                $('#edit-icl-content-skip').attr('disabled','disabled');
		$('#no_language_error').show('fast');
	} else {
                if($(id).html()!=null){
                    $('#edit-icl-content-skip').removeAttr('disabled');
                }else{
                    $('#edit-icl-content-skip').attr('disabled','disabled');
                }        
		$('#no_language_error').hide('fast');
	}
}

$(document).ready( function() {
	$('#edit-icl-content-skip').change( function() {
		if (this.value == 'not') {
			$('#icl-content fieldset').hide('slow');
		} else {
			icl_content_lang_propagate($('#edit-language').val(), 'slow');
		}
	});

	$('#edit-language').change( function() {
		icl_content_lang_propagate(this.value, '');
	});

	$('#edit-minor-edit').change( function() {
		if($('#edit-minor-edit').attr('checked')) {
                        $('#edit-icl-content-skip-wrapper').hide('slow');
			icl_content_lang_propagate($('#edit-language').val(), 'slow');
                } else {
                        $('#edit-icl-content-skip-wrapper').show('fast');
			icl_content_lang_propagate($('#edit-language').val(), 'fast');
                        
                }
	});

	icl_content_lang_propagate($('#edit-language').val(), '');
});