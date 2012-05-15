var check_count = 0;

$(document).ready( function() {
        
        var form = $('#locale-translate-seek-form');
        var string_ids = new Array();
        var string_status = new Array();
        
        if (form.length > 0) {
                
                // find the table headers.
                
                $('table thead tr th').each(
                                            
                        function() {
                                if ($(this).html() == Drupal.settings.text_group) {
                                        // this starts with the "Text group"
                                        var clone = $(this).clone();
                                        clone.html('');
                                        
                                        // Add a check box to the first column.
                                        
                                        var check_box = $('#edit-icl-check').clone();
                                        check_box.show();
                                        check_box.attr('checked', '');
                                        check_box.attr('id', 'icl_check_all' + check_count);
                                        
                                        clone.append(check_box);
                                        $(this).before(clone);
        
                                        $('#icl_check_all' + check_count).change( function() {
                                                checked = $(this).attr('checked');
                                                $('.icl_lid_class').each(function() {
                                                        if(checked) {
                                                                $(this).attr('checked', 'checked');
                                                        } else {
                                                                $(this).attr('checked', '');
                                                        }
                                                });
                                                
                                                for (i = 0; i < check_count; i++) {
                                                        if (checked != $('#icl_check_all' + i).attr('checked')) {
                                                                if(checked) {
                                                                        $('#icl_check_all' + i).attr('checked', 'checked');
                                                                } else {
                                                                        $('#icl_check_all' + i).attr('checked', '');
                                                                }
                                                                
                                                        }
                                                }
                                                
                                        });
                                        
                                        check_count++;
                                        
                                        // find the table
                                        var table = $(this).parent().parent().parent();
                                        
                                        form.prepend(table);
                                        
                                        var table_rows = table.find('tr');
                                        table_rows.each(function() {
                                                
                                                // for each row add a check box to the first column.
                                                
                                                first_td = $(this).find('td:first');
                                                if (first_td) {
                                                        last_td = $(this).find('td:last a');
                                                        href = last_td.attr('href');
                                                        if (typeof(href) != 'undefined') {
                                                                href = href.split('/');
                                                                source_id = href[href.length - 1];
                                                                clone = first_td.clone();
                                                                clone.html('');
                                                                var check_box = $('#edit-icl-check').clone();
                                                                check_box.show();
                                                                check_box.attr('id', 'icl_lid[' + source_id + ']');
                                                                check_box.attr('name', 'icl_lid[' + source_id + ']');
                                                                check_box.attr('class', 'icl_lid_class');
                                                                check_box.attr('checked', '');
                                                                clone.append(check_box);
                                                                first_td.before(clone);
                                                                
                                                                string_ids.push(source_id);
                                                                string_status[source_id] = last_td.parent().prev().prev();
                                                        }
                                                }
                                                });
                                        
                                }
                        }
                        );
                
                if (check_count == 0) {
                        $('#dashboard-actions').hide();
                }
        }
        
        if (typeof(icl_tb_init) != 'undefined') {
                icl_tb_init('.icl_thickbox');
                icl_tb_set_size('.icl_thickbox');
        }
        
        if (check_count > 0) {
                
                // get the icl status of the strings.
                jQuery.ajax({
                type: "POST",
                url: Drupal.settings.ican_url.ican_string_status_url,
                data: "icl_ajx_action=icl_string_status&string_ids=" + string_ids.toString() + "&ican_string_token=" + Drupal.settings.ican_url.ican_string_token,
                async: true,
                success: function(msg){
                        data = msg.split('|');
                        for (i in data) {
                                if (data[i].length > 0) {
                                        string = data[i].split(',');
                                        existing = string_status[string[0]].html();
                                        if (existing.indexOf('Translation') < 0) {
                                                existing += '<br /><b>Translation</b>';
                                        }
                                        existing += '<br />(' + string[1] + ') ';
                                        string_status[string[0]].html(existing);
                                }
                        }
                        
                        
                        
                        
                }
            }); 
        }
        
        // NOW check for l10client.
        
        l10n_client = $('#l10n-client-form');
        if (l10n_client.length) {

                // check the id of the "Clear" button
                edit_clear_id = '#edit-clear';
                if ($(edit_clear_id).length == 0) {
                        edit_clear_id = '#l10n-client-edit-clear';
                }
                
                // allow a bit more room for our controls.
                $('#l10n-client-form .form-textarea').css('height', '5em');
                
                span = $(document.createElement('span'))
                span.attr('id', 'icl-link-to-queue');
                span.html('<br />' + Drupal.settings.queued_message + '<a href="' + Drupal.settings.ican_url.ican_string_que_url + '">' + Drupal.settings.send_link + '</a>');
                $(edit_clear_id).after(span);
                span.hide();
                
                clone = $('#l10n-client-form ' + edit_clear_id).clone();
                clone.attr('id', 'icl-send-translation');
                clone.attr('value', Drupal.settings.send_button);
                
                $(edit_clear_id).after(clone);

                // add span for checking status display
                span = $(document.createElement('span'))
                span.html(Drupal.settings.checking_status);
                span.attr('id', 'icl_checking_status');
                $(edit_clear_id).after(span);
                span.hide()

                // add span for displaying status
                span = $(document.createElement('span'))
                span.html('');
                span.attr('id', 'icl_status');
                $(edit_clear_id).after(span);
                span.hide()
                
                
                span = $(document.createElement('span'))
                span.html('<b>Translate: </b>');
                $(edit_clear_id).after(span);

                $(edit_clear_id).after($(document.createElement('br')));
                $(edit_clear_id).after($(document.createElement('br')));
                
                $('#l10n-client #icl-send-translation').click(function() {
                        // send for translation.
                        jQuery.ajax({
                        type: "POST",
                        url: Drupal.settings.ican_url.ican_string_send_url,
                        data: "string=" + $('#l10n-client-string-editor .source-text').text() + "&ican_string_token=" + Drupal.settings.ican_url.ican_string_token,
                        async: true,
                        success: function(msg){
                                data = msg.split('|');
                                if (data[0] == '1') {
                                        
                                } else {
                                        // show the error.
                                        alert(data[1]);
                                }
                                icl_check_string_status_for_index(li_index);
                        }
                        });
                });

                icl_show_queued_link_if_required();
        }
        
        $('#l10n-client-string-select li').click(icl_check_string_status);
        
});

var li_index = -1;

function icl_check_string_status() {
        li_index = $('#l10n-client-string-select li').index(this);
        
        icl_check_string_status_for_index(li_index);
}

function icl_check_string_status_for_index(index) {
        $('#l10n-client #icl-send-translation').hide();
        $('#l10n-client #icl_status').hide();
        $('#l10n-client #icl_checking_status').show();

        var text = Drupal.l10nClient.getString(index, 'source');
        jQuery.ajax({
        type: "POST",
        url: Drupal.settings.ican_url.ican_string_status_url,
        data: "icl_ajx_action=icl_single_string_status&source=" + text + "&ican_string_token=" + Drupal.settings.ican_url.ican_string_token,
        async: true,
        success: function(msg){
                if (msg == "") {
                        // this is not managed by icanlocalize.
                        $('#l10n-client #icl_checking_status').hide();
                        $('#l10n-client #icl_status').hide();
                        $('#l10n-client #icl-send-translation').show();
                } else {
                        data = msg.split('|');
                        $('#l10n-client #icl_checking_status').hide();
                        $('#l10n-client #icl_status').html(data[1]);
                        $('#l10n-client #icl_status').show();
                }
        }
        
        });
        
        icl_show_queued_link_if_required();

}

function icl_show_queued_link_if_required() {
        jQuery.ajax({
        type: "POST",
        url: Drupal.settings.ican_url.ican_string_status_url,
        data: "icl_ajx_action=icl_any_queued_strings" + "&ican_string_token=" + Drupal.settings.ican_url.ican_string_token,
        async: true,
        success: function(msg){
                if (msg == "1") {
                        $('#l10n-client #icl-link-to-queue').show();
                }
        }
        
        }); 
        
}