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

  this.bindContainers();
  this.initCloneBundleForm();
  this.initPassageBoxes();
};

BundleUI.prototype.bindContainers = function () {
  this.$passageBoxes = $('.passage-boxes', this.$wrapper);
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

/**
 * Replaces the current state with that that in "data".
 */
BundleUI.prototype.loadState = function (data, set_message) {
  var i, len = this.passageBoxes.length;

  this.cloneBundle.setVisibility(data.length == 0, set_message);

  for (i = 0; i < len; i++) {
    this.passageBoxes[i].loadState(data[i] || {})
  }

  if (data.length > this.passageBoxes.length) {
    log('Error, attempting to load more data than is possible with ' + this.passageBoxes.length + ' passage boxes.');
  }
};

/**
 * Passage boxes call this method to inform the rest of the application that
 * their state changed.
 */
BundleUI.prototype.passageBoxStateDidChange = function (passageBox, animated) {
  var i, len = this.passageBoxes.length, pickedKeys = [], visibleKeys = [], state;

  animated = typeof animated === 'undefined' ? true : animated;

  for (i = 0; i < len; i++) {
    state = this.passageBoxes[i].getState();

    if (this.passageBoxes[i].picked === true) {
      pickedKeys.push(i);
    }
    if (state.visible) {
      visibleKeys.push(i);
    }
  }

  // If there are picked passages but none are visible then ensure the first
  // passage is marked visible.
  if (visibleKeys.length == 0 && pickedKeys.length > 0) {
    state = this.passageBoxes[pickedKeys[0]].getState();
    state.visible = true;
    this.passageBoxes[pickedKeys[0]].loadState(state, true);
  }

  this.cloneBundle.setVisibility(pickedKeys.length > 0, false, animated);
};

/**
 * Helper method, set informational messages which disappear after a set amount
 * of time.
 */
BundleUI.prototype.setMessage = function (message, type, hideAfter) {
  util.setMessage($('> .inner', this.$passageBoxes), message, type, hideAfter)
};
