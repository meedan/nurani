$(document).ready( function() {
        $('.icl_add_link').click(on_add_edit_click);
        $('.icl_edit_link').click(on_add_edit_click);
        $('.icl_save').click(on_save_click);
        $('.icl_cancel').click(on_cancel_click);
        $('.icl_delete').click(on_delete_click);
});


function on_add_edit_click() {
        $('.icl_edit').each(function() {
                $(this).hide();
        });
        id = $(this).attr('id');
        edit_id = id.replace('add_edit', 'edit');
        $('#' + edit_id).show();
        $('.icl_add_link').each(function() {
                if (id == $(this).attr('id')) {
                        $(this).hide();
                } else {
                        $(this).show();
                }
        });
        $('.icl_edit_link').each(function() {
                if (id == $(this).attr('id')) {
                        $(this).hide();
                } else {
                        $(this).show();
                }
        });
};

function on_save_click() {
        
        id = $(this).attr('id');
        text_id = id.replace('save', 'text');

        $(this).after($('#icl_throbber'));
        $('#icl_throbber').show();        
        jQuery.ajax({
                type: "POST",
                url: Drupal.settings.ican_ajax.ican_image_replace_url,
                data: "icl_image_cmd=icl_save&icl_id=" + id + "&icl_file_name=" + $("#" + text_id).val(),
                async: false,
                success: function(msg){
                        if (msg.split('|')[0] == '1') {
                                // change 'add' to 'edit'
                                add_id = id.replace('save', 'add_edit');
                                //$("#" + add_id).text(Drupal.settings.ican_ajax.ican_edit_text);
                                $("#" + add_id).removeClass('icl_add_link');
                                $("#" + add_id).addClass('icl_edit_link');
                                // show delete button
                                delete_id = id.replace('save', 'delete');
                                $('#' + delete_id).show();
                                $('#icl_changes_message').show();
                                $('#icl_changes_message_2').show();
                        }
                        $('#icl_throbber').hide();        
                }
        });

        $('.icl_edit').each(function() {
                $(this).hide();
        });
        $('.icl_add_link').each(function() {
                $(this).show();
        });
        $('.icl_edit_link').each(function() {
                $(this).show();
        });
};

function on_cancel_click() {

        $('.icl_edit').each(function() {
                $(this).hide();
        });
        $('.icl_add_link').each(function() {
                $(this).show();
        });
        $('.icl_edit_link').each(function() {
                $(this).show();
        });
};

function on_delete_click() {
        
        id = $(this).attr('id');

        $(this).after($('#icl_throbber'));
        $('#icl_throbber').show();        
        jQuery.ajax({
                type: "POST",
                url: Drupal.settings.ican_ajax.ican_image_replace_url,
                data: "icl_image_cmd=icl_delete&icl_id=" + id,
                async: false,
                success: function(msg){
                        if (msg.split('|')[0] == '1') {
                                add_id = id.replace('delete', 'add_edit');
                                //$("#" + add_id).text(Drupal.settings.ican_ajax.ican_add_text);
                                $("#" + add_id).removeClass('icl_edit_link');
                                $("#" + add_id).addClass('icl_add_link');
                                $("#" + id).hide();
                                $('#icl_changes_message').show();
                                $('#icl_changes_message_2').show();
                        }
                        $('#icl_throbber').hide();        
                }
        });

        $('.icl_edit').each(function() {
                $(this).hide();
        });
        $('.icl_add_link').each(function() {
                $(this).show();
        });
        $('.icl_edit_link').each(function() {
                $(this).show();
        });
};