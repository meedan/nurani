(function ($) {

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

  /**
   * Nurani PassageBox class.
   */
  function PassageBox(element, bundleUI) {
    this.$wrapper = $(element);
    this.bundleUI = bundleUI;
    this.init();

    return this;
  }

  PassageBox.prototype.init = function () {
    this.bindOSISFields();
    this.bindAddButton();

    return this;
  };

  PassageBox.prototype.bindOSISFields = function () {
    this.$osisIDWork = $('.edit-osisIDWork', this.$wrapper);
    this.$osisID     = $('.edit-osisID', this.$wrapper);
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
          },
          onCancel: function () {
            console.log('onCancel');
            // TODO: Do something on cancel?
          }
        });

    passagePicker.pick();
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
                    height: 300,
                    width: 350,
                    modal: true,
                    buttons: {
                      Done: function() {
                        if (that.opts.onPicked) {
                          that.opts.onPicked($('#edit-osisIDWork', $form).val(), $('#edit-osisID', $form).val());
                        }
                        $(this).dialog('close');
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

  /**
   * Display the passage picker.
   */
  Picker.prototype.pick = function () {
    this.$dialog.dialog('open');

    return this;
  };

})(jQuery);