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
BundleUI.prototype.passageBoxStateDidChange = function (passageBox) {
  var i, len = this.passageBoxes.length, picked = [];

  for (i = 0; i < len; i++) {
    picked.push(this.passageBoxes[i].picked);
  }

  this.cloneBundle.setVisibility(picked.indexOf(true) === -1);
};

/**
 * Helper method, set informational messages which disappear after a set amount
 * of time.
 */
BundleUI.prototype.setMessage = function (message, type, hideAfter) {
  type      = type || 'ok';
  hideAfter = hideAfter || 3000;

  classes = ['messages'];
  if (type) {
    classes.push(type);
  }

  var message = $('<div class="' + classes.join(' ') + '" style="display: none;">' + message + '</div>');
  this.$wrapper.prepend(message);
  message.slideDown();

  setTimeout(function () {
    message.slideUp(function () {
      $(this).remove();
    });
  }, hideAfter);
};
