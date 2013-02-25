/**
 * Drupal integration. Creates and binds new BundleUIs.
 */
Drupal.behaviors.nuraniBundleUI = {
  bundleUIs: [],

  attach: function (context) {
    var that = this,
        i, bundleUI;

    $('#edit-field-bundle:not(.nurani-bundle-ui-processed)', context)
      .addClass('nurani-bundle-ui-processed')
      .each(function () {
        bundleUI = new BundleUI(this);
        $(this).data('bundleUI', bundleUI);

        that.bundleUIs.push(bundleUI);
      });

    for (i = this.bundleUIs.length - 1; i >= 0 ; i--) {
      bundleUI = this.bundleUIs[i];

      if ($(context).index(bundleUI.$wrapper) !== -1) {
        bundleUI.initPassageBoxes();
      }
    }
  }

};
