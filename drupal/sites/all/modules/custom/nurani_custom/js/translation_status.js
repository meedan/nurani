(function ($) {
// START jQuery

Drupal.behaviors.translationStatus = function(context) {
  $(".translation-status-placeholder", context)
  .not(".translation-status-processed")
  .addClass("translation-status-processed")
  .parents(".buildmode-full")
  .addClass("translation-status-placeholder");
}

// END jQuery
})(jQuery);

