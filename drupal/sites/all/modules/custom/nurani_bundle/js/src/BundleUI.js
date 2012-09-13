/**
 * Main controller object for the bundle UI.
 */
function BundleUI(element) {
  this.$wrapper = $(element);
  this.init();

  return this;
}

BundleUI.prototype.init = function () {
  this.cloneBundle  = undefined;
  this.passageBoxes = [];

  this.initCloneBundleForm();
  this.initPassageBoxes();
};

BundleUI.prototype.initCloneBundleForm = function () {
  var $cloneBundle = $('.clone-bundle:not(.nurani-bundle-ui-processed):first', this.$wrapper)
                       .addClass('nurani-bundle-ui-processed');

  this.cloneBundle = new CloneBundle($cloneBundle[0], this);
};

BundleUI.prototype.initPassageBoxes = function () {
  var that = this;

  $('.passage-box:not(.nurani-bundle-ui-processed)', this.$wrapper)
    .addClass('nurani-bundle-ui-processed')
    .each(function () {
      var passageBox = new PassageBox(this, that);
      $(this).data('passageBox', passageBox);
      that.passageBoxes.push(passageBox);
    });

  return this;
};
