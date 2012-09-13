/**
 * Nurani CloneBundle form.
 */
function CloneBundle(element, bundleUI) {
  this.$wrapper = $(element);
  this.bundleUI = bundleUI;
  this.init();

  return this;
}

CloneBundle.prototype.init = function () {
  this.bindSubmitButton();

  return this;
};

CloneBundle.prototype.bindSubmitButton = function () {
  var that = this;

  $('.form-submit.clone-bundle-action', this.$wrapper).click(function () {
    that.cloneBundle(this);
    return false;
  });

  return this;
};

CloneBundle.prototype.cloneBundle = function (button) {
  console.log('TODO: Clone the bundle..');
};
