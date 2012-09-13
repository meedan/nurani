(function ($) {

/**
 * Drupal integration. Creates a new BundleUI instance for each passage box.
 */
Drupal.behaviors.nuraniBundleUI = {
  attach: function (context) {

    $('.passage-box:not(.nurani-bundle-ui-processed)', context)
      .addClass('nurani-bundle-ui-processed')
      .each(function () {
        // Create a new BundleUI instance for this passage box and attach
        // a reference to the instance on the passage-box DOM element for later
        // retrieval.
        var bundleUI = new BundleUI(this);
        $(this).data('bundleUI', bundleUI);
      });

  }
};



/**
 * Nurani BundleUI class.
 */
function BundleUI(element) {
  this.$wrapper = $(element);
  this.init();

  return this;
}

BundleUI.prototype.init = function () {
  return this;
};


})(jQuery);
