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
  this.bindSelect();
  this.bindSubmitButton();

  return this;
};

CloneBundle.prototype.bindSelect = function () {
  this.$select = $('.form-select', this.$wrapper);
};

CloneBundle.prototype.bindSubmitButton = function () {
  var that = this;

  $('.form-submit.clone-bundle-action', this.$wrapper).click(function () {
    if (that.$select.val()) {
      that.cloneBundle(that.$select.val());
    }
    return false;
  });

  return this;
};

CloneBundle.prototype.cloneBundle = function (bundle_nid) {
  var that = this;
  // TODO: Initiate spinner and lock UI.

  $.getJSON(Drupal.settings.basePath + 'nurani_bundle/clone_bundle/' + bundle_nid + '/und', function (data) {
    // TODO: Remove spinner and unlock UI.
    that.bundleUI.loadState(data, true);
  });
};

CloneBundle.prototype.setVisibility = function (visibility, set_message, animated) {
  if (visibility) {
    if (animated) {
      this.$wrapper.slideDown('slow');
    } else {
      this.$wrapper.show();
    }
  } else {
    if (set_message) {
      this.bundleUI.setMessage(Drupal.t('Existing bundle selected. Remove all passages to use a different bundle as a template.'));
    }
    if (animated) {
      this.$wrapper.slideUp('slow');
    } else {
      this.$wrapper.hide();
    }
  }
};
