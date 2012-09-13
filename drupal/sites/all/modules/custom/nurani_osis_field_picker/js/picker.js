(function ($) {

/**
 * Drupal integration. Creates a new Picker instance for each osis_field.
 */
Drupal.behaviors.nuraniOsisFieldPicker = {
  attach: function (context) {

    $('.osis-field-input-group:not(.nurani-osis-field-picker-processed)', context)
      .addClass('nurani-osis-field-picker-processed')
      .each(function () {
        var picker = new Picker(this);
      });

  }
};



/**
 * Nurani Passage Picker class.
 */
function Picker(element) {
  this.$wrapper = $(element);
  this.init();

  return this;
}

Picker.prototype.init = function () {
  this.$pickButton = this.createPickButton();
  this.$wrapper.append(this.$pickButton);

  this.$dialog = this.createDialog();

  return this;
};

Picker.prototype.createPickButton = function () {
  var that    = this,
      $button = $('<input type="submit" name="pick" class="form-submit pick-button" value="' + Drupal.t('Select passage') + '" />');

  $button.click(function (e) {
    that.pick();
    e.stopPropagation();
    return false;
  });

  return $button;
};

Picker.prototype.createDialog = function () {
  var that    = this,
      $dialog = $('.nurani-osis-field-picker-dialog:first', this.$wrapper).dialog({
                  autoOpen: false,
                  height: 300,
                  width: 350,
                  modal: true,
                  buttons: {
                    Done: function() {
                      $(this).dialog('close');
                    },
                    Cancel: function() {
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
