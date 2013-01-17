/**
 * Nurani PassageBox class.
 */
function PassageBox(element, bundleUI) {
  this.$wrapper = $(element);
  this.bundleUI = bundleUI;
  this.picked   = false;
  this.init();

  return this;
}

PassageBox.prototype.init = function () {
  this.bindContainers();
  this.bindFields();
  this.bindRemoveButton();
  this.bindAddEditButton();

  // Set up initial display state
  this.updatedPicked();
  this.render(false);
  this.bundleUI.passageBoxStateDidChange(this, false);

  return this;
};

PassageBox.prototype.bindContainers = function () {
  this.$passageText   = $('.passage-text', this.$wrapper);
  this.$passageWidget = $('.passage-widget', this.$passageText);
  this.$bib           = $('.bib', this.$wrapper);
}

PassageBox.prototype.bindFields = function () {
  var that = this;

  this.$osisIDWork         = $('.edit-osisIDWork', this.$wrapper);
  this.$osisID             = $('.edit-osisID', this.$wrapper);
  this.$moderatorsThoughts = $('.edit-moderator_s_thoughts', this.$wrapper);
  this.$visible            = $('.edit-visible', this.$wrapper)
                               .change(function () { that.render(false); });
};

PassageBox.prototype.bindRemoveButton = function () {
  var that = this;

  $('.form-submit.remove-passage-action', this.$wrapper).click(function () {
    that.loadState({}); // Load empty state
    return false;
  });

  return this;
};

PassageBox.prototype.bindAddEditButton = function () {
  var that = this;

  $('.pick-passage-action,.edit-passage-action', this.$wrapper).click(function () {
    that.pickPassage(this);
    return false;
  });

  return this;
};

PassageBox.prototype.pickPassage = function (button) {
  var that = this,
      passagePicker = new Picker({
        // Default values
        osisIDWork: that.$osisIDWork.val(),
        osisID:     that.$osisID.val(),
        // Callbacks
        onPicked: function (data) {
          that.$osisIDWork.val(data.osisIDWork);
          that.$osisID.val(data.osisID);
          that.updatedPicked();
          that.render();

          that.bundleUI.passageBoxStateDidChange(that);
        },
        onCancel: function () {
          // TODO: Do something on cancel?
        }
      });

  passagePicker.pick();
};

PassageBox.prototype.updatedPicked = function () {
  this.picked = !!(this.$osisIDWork.val() && this.$osisID.val());
}

/**
 * Retrieves passage text and update other aspects of the display.
 */
PassageBox.prototype.render = function (animated) {
  animated = typeof animated === 'undefined' ? true : animated;

  if (this.picked) {
    this.$passageText.removeClass('empty');
    this.updatePassageWidget();
    this.$moderatorsThoughts.removeAttr('disabled');
    this.$visible.removeAttr('disabled');

    if (this.$visible[0].checked) {
      this.$passageText.removeClass('hidden');
    } else {
      this.$passageText.addClass('hidden');
    }

    if (animated) {
      this.$bib.slideDown();
    } else {
      this.$bib.show();
    }
  }
  else {
    this.$passageText.addClass('empty');
    this.$passageText.removeClass('visible');
    this.$moderatorsThoughts.attr('disabled', 'disabled');
    this.$visible.attr('disabled', 'disabled');

    if (animated) {
      this.$bib.slideUp();
    } else {
      this.$bib.hide();
    }
  }
};

PassageBox.prototype.updatePassageWidget = function () {
  var that = this,
      url = PassageWidget.oEmbedURL(this.$osisIDWork.val(), this.$osisID.val(), null, 'jsonp', '?');

  $.ajax({
    url: url,
    dataType: 'jsonp',
    success: function (data) {
      that.$passageWidget.html(data.html);
    }
  });
};

/**
 * Replaces the state of a passage box with that in "data".
 */
PassageBox.prototype.loadState = function (data, quiet) {
  quiet = quiet || false;

  this.$osisIDWork.val(data.osisIDWork || '');
  this.$osisID.val(data.osisID || '');
  this.$moderatorsThoughts.val(data.moderator_s_thoughts || '');

  if (data.visible) {
    this.$visible.attr('checked', 'checked');
  } else {
    this.$visible.removeAttr('checked');
  }

  this.updatedPicked();
  this.render();

  if (!quiet) {
    this.bundleUI.passageBoxStateDidChange(this);
  }
};

PassageBox.prototype.getState = function (visible) {
  return {
    osisIDWork: this.$osisIDWork.val(),
    osisID: this.$osisID.val(),
    moderator_s_thoughts: this.$moderatorsThoughts.val(),
    visible: this.$visible.attr('checked')
  };
}