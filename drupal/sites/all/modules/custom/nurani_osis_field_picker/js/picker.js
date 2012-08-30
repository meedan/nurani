(function ($) {

/**
 * Drupal integration. Creates a new Picker instance for each osis_field.
 */
Drupal.behaviors.nuraniOsisFieldPicker = {
  attach: function (context) {

    $('.osis-field-input-group:not(.nurani-osis-field-picker-processed)')
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
  this.$field = $(element);
  this.init();

  return this;
}

Picker.prototype.init = function () {
  this.$pickButton = this.createPickButton();
  this.$field.append(this.$pickButton);

  return this;
};

Picker.prototype.createPickButton = function () {
  var that = this,
      btn  = $('<input type="submit" name="pick" class="form-submit pick-button" value="' + Drupal.t('Select passage') + '" />');

  btn.click(function (e) {
    that.pick();
    e.stopPropagation();
    return false;
  });

  return btn;
}

/**
 * Display the passage picker.
 */
Picker.prototype.pick = function () {
  alert('Display the passage picker.');

  return this;
};

})(jQuery);
