$(document).ready( function() {
        
    $('#edit-i-understand').change( function() {
        if ($(this).is(':checked') == false) {
            $('#edit-enable').attr('disabled', 1);
        } else {
            $('#edit-enable').attr('disabled', 0);
        }
    });
});


