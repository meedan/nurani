
var icl_intval = "";

function iclAjaxAutoSave(form, time) {
  icl_inval = setInterval(function () {
        iclAjaxSubmit(form);
    }, time);
}

function iclAjaxSubmit(form) {
    $(form).ajaxSubmit({
      //target:, 
      //url:,
      type: "POST",
      data: ({icl_ajax:1, save_translation:Drupal.settings[form].submit}),
			//forceSync: true,
      success: function() { 
        //
      }
    });
}

                	