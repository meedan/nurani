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
   * Corebox util library.
   */
  function Util() {
  }

  // Globally available CB.Util
  var util = new Util();

  /**
   * Helper method, set informational messages which disappear after a set amount
   * of time.
   */
  Util.prototype.setMessage = function (prepend_to, message, type, hide_after) {
    type       = type || 'ok';
    hide_after = hide_after || 3000;

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
    var i, len = this.passageBoxes.length, picked = [];

    animated = typeof animated === 'undefined' ? true : animated;

    for (i = 0; i < len; i++) {
      picked.push(this.passageBoxes[i].picked);
    }

    this.cloneBundle.setVisibility(picked.indexOf(true) === -1, false, animated);
  };

  /**
   * Helper method, set informational messages which disappear after a set amount
   * of time.
   */
  BundleUI.prototype.setMessage = function (message, type, hideAfter) {
    util.setMessage($('> .inner', this.$passageBoxes), message, type, hideAfter)
  };

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
    this.bindAddButton();

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
    this.$osisIDWork         = $('.edit-osisIDWork', this.$wrapper);
    this.$osisID             = $('.edit-osisID', this.$wrapper);
    this.$moderatorsThoughts = $('.edit-moderator_s_thoughts', this.$wrapper);
    this.$visible            = $('.edit-visible', this.$wrapper);
  };

  PassageBox.prototype.bindRemoveButton = function () {
    var that = this;

    $('.form-submit.remove-passage-action', this.$wrapper).click(function () {
      that.loadState({}); // Load empty state
      return false;
    });

    return this;
  };

  PassageBox.prototype.bindAddButton = function () {
    var that = this;

    $('.form-submit.pick-passage-action', this.$wrapper).click(function () {
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
          onPicked: function (work_name, osisID) {
            that.$osisIDWork.val(work_name);
            that.$osisID.val(osisID);
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
      this.$passageWidget.html('<span>' + this.$osisIDWork.val() + '</span>:<span>' + this.$osisID.val() + '</span>');
      this.$moderatorsThoughts.removeAttr('disabled');
      this.$visible.removeAttr('disabled');

      if (animated) {
        this.$bib.slideDown();
      } else {
        this.$bib.show();
      }
    }
    else {
      this.$passageText.addClass('empty');
      this.$moderatorsThoughts.attr('disabled', 'disabled');
      this.$visible.attr('disabled', 'disabled');

      if (animated) {
        this.$bib.slideUp();
      } else {
        this.$bib.hide();
      }
    }
  };

  /**
   * Replaces the state of a passage box with that in "data".
   */
  PassageBox.prototype.loadState = function (data) {
    this.$osisIDWork.val(data.osisIDWork || '');
    this.$osisID.val(data.osisID || '');
    this.$moderatorsThoughts.val(data.moderator_s_thoughts || '');

    if (data.visible && data.visible === '1') {
      this.$visible.attr('checked', 'checked');
    } else {
      this.$visible.removeAttr('checked');
    }

    this.updatedPicked();
    this.render();
    this.bundleUI.passageBoxStateDidChange(this);
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
    this.$dialog = this.createDialog();

    return this;
  };

  Picker.prototype.createDialog = function () {
    var $form = $('<div>'
                +   '<div class="form-item form-type-textfield form-item-osisIDWork">'
                +     '<label for="edit-osisIDWork">Work name <span class="form-required" title="This field is required.">*</span></label>'
                +     '<input type="text" id="edit-osisIDWork" name="osisIDWork" value="' + this.opts.osisIDWork + '" size="16" maxlength="32" class="form-text required">'
                +   '</div>'
                +   '<div class="form-item form-type-textfield form-item-osisID">'
                +     '<label for="edit-osisID">Osis ID <span class="form-required" title="This field is required.">*</span></label>'
                +     '<input type="text" id="edit-osisID" name="osisID" value="' + this.opts.osisID + '" size="16" maxlength="64" class="form-text required">'
                +   '</div>'
                + '</div>');

    var that    = this,
        $dialog = $form.dialog({
                    autoOpen: false,
                    width: 800,
                    modal: true,
                    buttons: {
                      Done: function() {
                        var osisIDWork = $('#edit-osisIDWork', $form).val(),
                            osisID     = $('#edit-osisID', $form).val()

                        that.pickIfValid(osisIDWork, osisID);
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
                    }
                  });

    return $dialog;
  };

  Picker.prototype.pickIfValid = function (osisIDWork, osisID) {
    var that = this;

    $.getJSON(Drupal.settings.basePath + 'nurani_bundle/validate_passage/' + osisIDWork + '/' + osisID, function (data) {
      if (data === true) {
        if (that.opts.onPicked) {
          that.opts.onPicked(osisIDWork, osisID);
        }
        that.$dialog.dialog('close');
      }
      else {
        for (var key in data.errors) {
          if (data.errors.hasOwnProperty(key)) {
            util.setMessage(that.$dialog, data.errors[key], 'error');
          }
        }
      }
    });
  };

  /**
   * Display the passage picker.
   */
  Picker.prototype.pick = function () {
    this.$dialog.dialog('open');

    return this;
  };

})(jQuery);