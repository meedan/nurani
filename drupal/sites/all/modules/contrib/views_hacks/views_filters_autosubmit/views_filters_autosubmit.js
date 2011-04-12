(function ($) {
// START jQuery

Drupal.vfas = Drupal.vfas || {};

Drupal.behaviors.vfas = function(context) {
  $.each(Drupal.settings.vfas, function(form_id, settings) {
    $('form#'+form_id+':not(.vfas-processed)', context).each(function() {
      var self = this;
      var exceptions;
      if (settings.exceptions) {
        exceptions = ':not('+settings.exceptions+')';
      }    
      else {
        exceptions = '';
      }
      $(self).addClass('vfas-processed');
      $('input:submit.form-submit', self).hide();
      $('div.views-exposed-widget input:not(:checkbox,:radio)'+exceptions, self).change(function() {
        $(self).submit();
      });
      $('div.views-exposed-widget input:checkbox'+exceptions+', div.views-exposed-widget input:radio'+exceptions, self).click(function() {
        $(self).submit();
      });
      $('div.views-exposed-widget select'+exceptions, self).change(function() {
        $(self).submit();
      });
    });
  });
}

// END jQuery
})(jQuery);

