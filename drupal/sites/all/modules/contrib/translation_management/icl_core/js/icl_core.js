function on_lang_from(n, lang) {
        if (n.attr('checked'))
        {
                $("#dest_languages_" + lang).show();
                
        }
        else
        {
                $("#dest_languages_" + lang).hide();
        }
}


function on_account_button() {
        if($("#edit-icl-core-password-wrapper").is(":hidden"))
        {
                $("#edit-icl-core-password-wrapper").show();
                $("#edit-icl-core-button").attr("value", "I need to create an account at ICanLocalize");
                $("#edit-icl-core-first-name-wrapper").hide();
                $("#edit-icl-core-last-name-wrapper").hide();
                $("#edit-icl-core-do-create").attr("value", "0");
                $("#icl_core_account_message").hide();
        }
        else
        {
                $("#edit-icl-core-password-wrapper").hide();
                $("#edit-icl-core-button").attr("value", "I already have an account at ICanLocalize");
                $("#edit-icl-core-first-name-wrapper").show();
                $("#edit-icl-core-last-name-wrapper").show();
                $("#edit-icl-core-do-create").attr("value", "1");
                $("#icl_core_account_message").show();
        }
}

function on_translator_select() {
        if($('#edit-icl-core-translator-selection-private-translators').attr('checked')) {
                $('#icl_core_private_translator_message').show();
                $('div').filter(function (index) {
                        var id = $(this).attr('id');
                        if (id.match("-own-"))
                        {
                                var lang_id = id.replace("-own-", "-").replace("-wrapper", "");
                                if ($('#' + lang_id).attr('checked')) {
                                        $(this).show('slow');
                                } else {
                                        $(this).hide();
                                }
                                
                        }
                        
                })
        } else {
                $('#icl_core_private_translator_message').hide();
                $('div').filter(function (index) {
                        var id = $(this).attr('id');
                        if (id.match("-own-"))
                        {
                                $(this).hide();
                        }
                        
                })
        }
        
}

$(document).ready( function() {
        $("#edit-icl-core-password-wrapper").hide();
        on_translator_select();
        icl_tb_init('.icl_thickbox');
        icl_tb_set_size('.icl_thickbox');
        
});