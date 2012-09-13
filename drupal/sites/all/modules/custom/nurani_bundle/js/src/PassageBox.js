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
