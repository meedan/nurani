(function ($) {

  // paulirish.com/2009/log-a-lightweight-wrapper-for-consolelog/
  var log = function f(){ log.history = log.history || []; log.history.push(arguments); if(this.console) { var args = arguments, newarr; args.callee = args.callee.caller; newarr = [].slice.call(args); if (typeof console.log === 'object') log.apply.call(console.log, console, newarr); else console.log.apply(console, newarr);}};

  /**
   * Drupal integration. Creates and binds new BundleUIs.
   */
  Drupal.behaviors.nuraniBundleUI = {
    bundleUIs: [],

    attach: function (context) {
      var that = this;

      $('#edit-field-bundle:not(.nurani-bundle-ui-processed)', context)
        .addClass('nurani-bundle-ui-processed')
        .each(function () {
          var bundleUI = new BundleUI(this);
          $(this).data('bundleUI', bundleUI);

          that.bundleUIs.push(bundleUI);
        });

      var i, bundleUI;
      for (var i = this.bundleUIs.length - 1; i >= 0 ; i--) {
        bundleUI = this.bundleUIs[i];

        if ($(context).index(bundleUI.$wrapper) !== -1) {
          bundleUI.initPassageBoxes();
        }
      }
    }

  };

  /**
   * Util library.
   */
  function Util() {
  }

  // Globally available Util
  var util = new Util();

  /**
   * Helper method, set informational messages which disappear after a set amount
   * of time.
   */
  Util.prototype.setMessage = function (prepend_to, message, type, hide_after) {
    type       = type || 'ok';
    hide_after = hide_after || 4000;

    classes = ['messages'];
    if (type) {
      classes.push(type);
    }

    var message = $('<div class="' + classes.join(' ') + '" style="display: none;">' + message + '</div>');
    prepend_to.prepend(message);
    message.slideDown();

    setTimeout(function () {
      message.slideUp(function () {
        $(this).remove();
      });
    }, hide_after);
  }

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

  /**
   * Nurani Passage Picker class.
   */
  function Picker(opts) {
    this.defaults = {
      osisIDWork: '',
      osisID:     '',
    };

    this.opts = $.extend(this.defaults, opts);
    this.init();

    return this;
  }

  Picker.prototype.init = function () {
    this.nuraniLibraryPickerUI = new NL.PickerUI({
      osisIDWork: this.opts.osisIDWork,
      osisID: this.opts.osisID
    });
    this.$dialog = this.createDialog(this.nuraniLibraryPickerUI.$element);

    return this;
  };

  Picker.prototype.createDialog = function ($element) {
    var that    = this,
        $window = $(window),
        $dialog = $element.dialog({
                    autoOpen: false,
                    width: $window.width() * 0.88,
                    height: $window.height() * 0.80,
                    modal: true,
                    buttons: {
                      Done: function() {
                        var data = that.nuraniLibraryPickerUI.getSelectionOSIS();

                        if (data) {
                          if (that.opts.onPicked) {
                            that.opts.onPicked(data);
                          }
                          $(this).dialog('close');
                        }
                        // NOTE: Error display is managed by PickerUI
                      },
                      Cancel: function() {
                        if (that.opts.onCancel) {
                          that.opts.onCancel();
                        }
                        $(this).dialog('close');
                      }
                    },
                    close: function() {
                      // TODO: Do things on close, like clear the state.
                    },
                    open: function () { that.nuraniLibraryPickerUI.didResize(); },
                    resize: function () { that.nuraniLibraryPickerUI.didResize(); }
                  });

    return $dialog;
  };

  /**
   * Display the passage picker.
   */
  Picker.prototype.pick = function () {
    this.$dialog.dialog('open');

    return this;
  };

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
        this.$wrapper.removeClass('hidden');
      } else {
        this.$wrapper.addClass('hidden');
      }

      if (animated) {
        this.$bib.slideDown();
      } else {
        this.$bib.show();
      }
    }
    else {
      this.$passageText.addClass('empty');
      this.$wrapper.removeClass('hidden');
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

    this.passageBoxStateDidChange(null, false);
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

    // The passage-box DIVs are created by Drupal and pre-existing in the HTML.
    // Loop through and bind a PassageBox object to each.
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

    this.cloneBundle.setVisibility(pickedKeys.length == 0, false, animated);
  };

  /**
   * Helper method, set informational messages which disappear after a set amount
   * of time.
   */
  BundleUI.prototype.setMessage = function (message, type, hideAfter) {
    util.setMessage($('> .inner', this.$passageBoxes), message, type, hideAfter)
  };

})(jQuery);