  
function select_default(n) {
  google.language.translate(n.html(), "", languages[0].code, function(result) {
    if (!result.error) {
      n.html(result.translation + source_language_message);
    } else {
      n.html(failed_translation_message);
    }
  });
}
          
$(document).ready(function(){
    
  $(".comment .content").each(function (i) {
    if($(this).find(".comment_sent").length == 0) {
      // duplicate the comment
      var temp = $(this).clone().insertAfter(this);
      temp.html('<div class="icanlocalize_orig_comment">' + temp.html() + '</div>');
        
      // show translation below.
      select_default($(this));
    }
  });
});
