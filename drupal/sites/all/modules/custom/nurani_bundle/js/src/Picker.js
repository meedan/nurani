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
