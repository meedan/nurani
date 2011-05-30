(function ($) {
// START jQuery

Drupal.vbo = Drupal.vbo || {};

Drupal.vbo.selectionModes = {
  all: 1,
  allPages: 2,
  none: 3
}

Drupal.vbo.fixSelectors = function() {
  var table = this;
  var form = $(table).parents('form');

  $('select.views-bulk-operations-selector', form).change(function() {
    if (this.options[this.selectedIndex].value == Drupal.vbo.selectionModes.all || this.options[this.selectedIndex].value == Drupal.vbo.selectionModes.allPages) {
      var selection = {};
      $('input:checkbox.vbo-select', table).each(function() {
        this.checked = true;
        $(this).parents('tr:first').addClass('selected');
        selection[this.value] = 1;
      });
      selection['selectall'] = this.options[this.selectedIndex].value == Drupal.vbo.selectionModes.allPages ? 1 : 0;
      $('input#edit-objects-selectall', form).val(selection['selectall']);

      if (Drupal.settings.vbo.options.preserve_selection) {
        $.post(Drupal.settings.basePath+'views-bulk-operations/js/select', {url: Drupal.settings.vbo.url, selection: JSON.stringify(selection)});
      }
    }
    else if (this.options[this.selectedIndex].value == Drupal.vbo.selectionModes.none) {
      $('input:checkbox.vbo-select', table).each(function() {
        this.checked = false;
        $(this).parents('tr:first').removeClass('selected');
      });
      $('input#edit-objects-selectall', form).val(0);

      if (Drupal.settings.vbo.options.preserve_selection) {
        $.post(Drupal.settings.basePath+'views-bulk-operations/js/select', {url: Drupal.settings.vbo.url, selection: JSON.stringify({'selectall': -1})});
      }
    }
  });

  $('#views-bulk-operations-dropdown select', form).change(function() {
    if (Drupal.settings.vbo.options.preserve_selection) {
      $.post(Drupal.settings.basePath+'views-bulk-operations/js/select', {url: Drupal.settings.vbo.url, selection: JSON.stringify({'operation': this.options[this.selectedIndex].value})});
    }
  });
  
  $(':checkbox.vbo-select', form).click(function() {
    var selection = {};
    selection[this.value] = this.checked ? 1 : 0;
    $(this).parents('tr:first')[ this.checked ? 'addClass' : 'removeClass' ]('selected');

    if (Drupal.settings.vbo.options.preserve_selection) {
      $.post(Drupal.settings.basePath+'views-bulk-operations/js/select', {url: Drupal.settings.vbo.url, selection: JSON.stringify(selection)});
    }
  }).each(function() {
    $(this).parents('tr:first')[ this.checked ? 'addClass' : 'removeClass' ]('selected');
  });
}

Drupal.vbo.startUp = function(context) {
  // Fix the form action for AJAX views.
  $('form.views-bulk-operations-form', context).each(this.fixAction);

  // Set up the VBO table for select-all functionality.
  $('form.views-bulk-operations-form table.views-bulk-operations-table', context).each(this.fixSelectors);

  // Set up the ability to click anywhere on the row to select it.
  $('tr.rowclick', context).click(function(event) {
    if (event.target.nodeName.toLowerCase() != 'input' && event.target.nodeName.toLowerCase() != 'a') {
      $(':checkbox.vbo-select', this).each(function() {
        var checked = this.checked;
        // trigger() toggles the checkmark *after* the event is set, 
        // whereas manually clicking the checkbox toggles it *beforehand*.
        // that's why we manually set the checkmark first, then trigger the
        // event (so that listeners get notified), then re-set the checkmark
        // which the trigger will have toggled. yuck!
        this.checked = !checked;
        $(this).trigger('click');
        this.checked = !checked;
      });
    }
  });
}

Drupal.vbo.fixAction = function() {
  var action = $(this).attr('action');
  var query = action.replace(/.*?\?/, '').split('&');
  var newQuery = '', newAction = action.replace(Drupal.settings.basePath, '');
  $.each(query, function(i, str) {
    var element = str.split('=');
    if (typeof element[1] == 'undefined') {
      // Do nothing.
    }
    else if (element[0] == 'view_path') {
      newAction = decodeURIComponent(element[1]);
    }
    else if (element[0].indexOf('view_') !== 0 && element[0] != 'pager_element' && element[0] != 'js') {
      newQuery += (newQuery.length ? '&' : '') + element[0] + '=' + element[1];
    }
  });
  $(this).attr('action', Drupal.settings.basePath + newAction + (newQuery.length ? '?' + newQuery : ''));
}

Drupal.behaviors.vbo = function(context) {
  // Force Firefox to reload the page if Back is hit.
  // https://developer.mozilla.org/en/Using_Firefox_1.5_caching
  window.onunload = function(){}

  // Set up VBO UI.
  if (Drupal.settings.vbo) {
    Drupal.vbo.startUp(context);
  }
}

// END jQuery
})(jQuery);

