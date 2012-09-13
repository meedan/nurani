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
