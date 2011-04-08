
function icl_get_form_id() {
  form_id = "";
  $("input[name=form_id]").each(function() {
    if ($(this).attr('id').indexOf('icl') >= 0) {
      form_id = $(this).val();
    }
  });
  return form_id;  
}

function icl_get_form_token() {
  form_token = "";
  $("input[name=form_token]").each(function() {
    if ($(this).attr('id').indexOf('icl') >= 0) {
      form_token = $(this).val();
    }
  });

  return form_token;  
}

$(document).ready(function(){
  // Render reminders
  
  form_token = icl_get_form_token();
  form_id = icl_get_form_id();
  
  jQuery.ajax({
    type: "POST",
    url: Drupal.settings.icl_reminders_message.ajax_url,
    data: {icl_translator_ajx_action:'reminders_get',
            form_id:form_id,
            form_token:form_token},
    cache: false,
    dataType: 'json',
    success: function(msg){
      if(!msg.error){
        $('#icl_reminders_wrapper').html(msg.message).fadeIn();
      }  
    }
  });
})

function iclRemindersInit() {
  $('.icl_reminders_link_dismiss').click(function() {

    form_token = icl_get_form_token();
    form_id = icl_get_form_id();
    
    var data = {icl_translator_ajx_action:'reminder_dismiss',
                  form_id:form_id,
                  form_token:form_token};
                  
    var hide = $(this).parent();
    jQuery.ajax({
        type: "POST",
        url: $(this).attr('href'),
        data: data,
        cache: false,
        dataType: 'json',
        success: function(msg){
            if(!msg.error){
              if (hide.parent().children('div').length < 2) {
                hide.parent().fadeOut();
              } else {              
                hide.fadeOut().remove();
              }
            }            
        }
    });
    return false;
  });
  
  $('#icl_reminders_show').click(function() {

    form_token = icl_get_form_token();
    form_id = icl_get_form_id();
    
    var data = {icl_translator_ajx_action:'reminders_show',
                  form_id:form_id,
                  form_token:form_token};
                  
    var thisV = $(this);
    jQuery.ajax({
        type:   "POST",
        url: $(this).attr('href'),
        data: data,
        cache: false,
        dataType: 'json',
        success: function(msg){
            if(!msg.error){                
              thisV.parent().children('div').toggle();
              if (thisV.parent().children('div').is(':visible')) {
                var txtV = Drupal.settings.icl_reminders_message.hide_txt;
                var hrefV = Drupal.settings.icl_reminders_message.hide_link;
              } else {
                var txtV = Drupal.settings.icl_reminders_message.show_txt;
                var hrefV = Drupal.settings.icl_reminders_message.show_link;
              }
            thisV.html(txtV).attr('href', hrefV);
            }            
        }
    });
    return false;
  });
}
