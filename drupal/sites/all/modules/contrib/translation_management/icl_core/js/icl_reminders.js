
function icl_tb_init(domChunk) {
    // copied from thickbox.js
    // add code so we can detect closure of popup

    jQuery(domChunk).unbind('click');
    
    jQuery(domChunk).click(function(){
    var t = this.title || this.name || "ICanLocalize Reminder";
    var a = this.href || this.alt;
    var g = this.rel || false;
    tb_show(t,a,g);
    
    do_message_refresh = true;
    jQuery('#TB_window').bind('unload', function(){
        
        if (a.indexOf('no_refresh=1') == -1) {
            url = location.href;
            if (url.indexOf('translate/search') == -1){
                
                url = url.replace(/[&?]icl_refresh_langs=1/g, '');
                url = url.replace(/&show_config=1/g, '');
                url = url.replace(/#.*/,'');
                if(-1 == url.indexOf('?')){
                    url_glue='?';
                }else{
                    url_glue='&';
                }
                
                location.href = url + url_glue + "icl_refresh_langs=1"
            }
        }        
        });
    
    this.blur();
    return false;
    });
}


function icl_tb_set_size(domChunk) {
    if (typeof(tb_getPageSize) != 'undefined') {

        var pagesize = tb_getPageSize();
        jQuery(domChunk).each(function() {
            var url = jQuery(this).attr('href');
            url += '&width=' + (pagesize[0] - 150);
            url += '&height=' + (pagesize[1] - 150);
            url += '&tb_avail=1'; // indicate that thickbox is available.
            jQuery(this).attr('href', url);
        });
    }
}

function dismiss_message(message_id) {
    do_message_refresh = false;
    jQuery('#icl_reminder_list').html('Refreshing messages  ' + '<div class="icl_throbber"></div>');
    tb_remove();

    
    jQuery.ajax({
        type: "POST",
        url: Drupal.settings.ican_fetch.ican_delete_reminder_url,
        data: "icl_ajx_action=icl_delete_message&message_id=" + message_id,
        async: false,
        success: function(msg){
        }
    }); 
    
    show_messages();
}

function icl_show_hide_reminders() {
    jqthis = jQuery(this);
    if(jQuery('#icl_reminder_list').css('display')=='none'){
        jQuery('#icl_reminder_list').fadeIn();
        jQuery.ajax({
            type: "POST",
            url: Drupal.settings.ican_fetch.ican_show_reminders_url,
            data: "icl_ajx_action=icl_show_reminders&state=show",
            async: true,
            success: function(msg){
            }
        }); 
    } else {
        jQuery('#icl_reminder_list').fadeOut();
        jQuery.ajax({
            type: "POST",
            url: Drupal.settings.ican_fetch.ican_show_reminders_url,
            data: "icl_ajx_action=icl_show_reminders&state=hide",
            async: true,
            success: function(msg){
            }
        }); 
        
    }
    jqthis.children().toggle();    
}