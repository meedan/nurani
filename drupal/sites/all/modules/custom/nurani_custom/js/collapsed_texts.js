(function ($) {

// TODO: Replace this with Drupal.behaviors
$(document).ready(function(){  
  $(".text_more a").click(function() {
    $link = $(this);
    $link.parents(".node-type-text").find(".field-body").each(function() {
      $text = $(this);
      if ($text.hasClass("text-expand")) {
        $text.removeClass("text-expand");
        $link.text(Drupal.t("more"));
      }
      else {
        $text.addClass("text-expand");
        $link.text(Drupal.t("less"));
      }
    });
    return false;
  }); 
});


})(jQuery);
