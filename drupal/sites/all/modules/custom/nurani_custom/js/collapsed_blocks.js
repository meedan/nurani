(function ($) {

// TODO: Replace with Drupal.behaviors
$(document).ready(function(){  

  $("#block-views-nuranis-block_1 h3").click(function() {
    $("#block-views-nuranis-block_1 .content").toggle(function() {
      $("#block-views-nuranis-block_1 h3").toggleClass("collapsed");
    });   
  });   

$("#block-views-new_glossary_terms-block_1 h3").click(function() {
    $("#block-views-new_glossary_terms-block_1 .content").toggle(function() {
      $("#block-views-new_glossary_terms-block_1 h3").toggleClass("expand");
    });   
  });   

$("#block-views-new_texts-block_1 h3").click(function() {
    $("#block-views-new_texts-block_1 .content").toggle(function() {
      $("#block-views-new_texts-block_1 h3").toggleClass("expand");
    });   
  });   

});

})(jQuery);
