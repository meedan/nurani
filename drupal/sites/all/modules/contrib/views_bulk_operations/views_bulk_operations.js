(function ($) {
// START jQuery

Drupal.vbo = Drupal.vbo || {};

Drupal.vbo.selectAll = function() {
  var table = this;
  var form = $(table).parents('form');

  var select = $('th.select-all', table).click(function() {
    setSelectAll(false);
    var selection = {};
    checkboxes.each(function() {
      selection[this.value] = this.checked ? 1 : 0;
    });
    $.post(Drupal.settings.basePath+'views-bulk-operations/js/select', {url: Drupal.settings.vbo.url, selection: JSON.stringify(selection)});
  });

  $('input#vbo-select-all-pages', table).click(function() {
    setSelectAll(true);
    $.post(Drupal.settings.basePath+'views-bulk-operations/js/select', {url: Drupal.settings.vbo.url, selection: JSON.stringify({'select_all': 1})});
  });

  $('input#vbo-select-this-page', table).click(function() {
    setSelectAll(false);
    $.post(Drupal.settings.basePath+'views-bulk-operations/js/select', {url: Drupal.settings.vbo.url, selection: JSON.stringify({'select_all': 0})});
  });
  $('input#vbo-deselect', table).click(function() {
    $('th.select-all input:checkbox', table).each(function() {
      this.checked = false;
    });
    $('input:checkbox.vbo-select', table).each(function() {
      this.checked = false;
      $(this).parents('tr:first')[ this.checked ? 'addClass' : 'removeClass' ]('selected');
    });
    setSelectAll(false);
    $.post(Drupal.settings.basePath+'views-bulk-operations/js/select', {url: Drupal.settings.vbo.url, selection: JSON.stringify({'select_all': -1})});
  });
  $('#views-bulk-operations-dropdown select').change(function() {
    $.post(Drupal.settings.basePath+'views-bulk-operations/js/select', {url: Drupal.settings.vbo.url, selection: JSON.stringify({'operation': this.options[this.selectedIndex].value})});
  });

  var checkboxes = $(':checkbox.vbo-select', form).click(function() {
    var selection = {};
    if (checkboxes.length > $(checkboxes).filter(':checked').length) {
      $('input#edit-objects-select-all', form).val(0);
      selection['select_all'] = 0;
    }
    setSelectAll($('input#edit-objects-select-all', form).val() == 1);
    selection[this.value] = this.checked ? 1 : 0;
    $.post(Drupal.settings.basePath+'views-bulk-operations/js/select', {url: Drupal.settings.vbo.url, selection: JSON.stringify(selection)});
  }).each(function() {
    $(this).parents('tr:first')[ this.checked ? 'addClass' : 'removeClass' ]('selected');
  });

  var setSelectAll = function(all) {
    $('input#edit-objects-select-all', form).val(all ? 1 : 0);
    $('th.select-all input:checkbox', table).each(function() {
      if (this.checked) {
        $('td.view-field-select-all', table).css('display', $.browser.msie ? 'inline-block' : 'table-cell');
        $('span#vbo-this-page', table).css('display', all ? 'none' : 'inline');
        $('span#vbo-all-pages', table).css('display', all ? 'inline' : 'none');
      }
      else {
        $('td.view-field-select-all', table).css('display', 'none');
      }
    });
  }

  // Update UI based on initial values.
  if ($('input#edit-objects-select-all', form).val() == 1 || checkboxes.length == $(checkboxes).filter(':checked').length) {
    $('th.select-all input:checkbox', table).each(function() {
      this.checked = true;
    });
    setSelectAll($('input#edit-objects-select-all', form).val() == 1);
  }
}

Drupal.vbo.startUp = function(context) {
  // Fix the form action for AJAX views.
  $('form.views-bulk-operations-form', context).each(this.fixAction);

  // Set up the VBO table for select-all functionality.
  $('form.views-bulk-operations-form table:has(th.select-all)', context).each(this.selectAll);

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

