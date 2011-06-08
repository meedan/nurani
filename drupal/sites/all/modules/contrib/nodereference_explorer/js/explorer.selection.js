
/**
 * @file explorer.selection.js
 * This behavior synchronizes the selections in the view with the stored value
 * that will be sent back to the autocomplete widget when the dialog is closed.
 */

/**
 * Behavior concering the choise of a view item
 * @param
 *   DOM context
 */
Drupal.behaviors.NodereferenceExplorerSelection = function(context) {
 
  //fix for hover over active table cell (column sorted)
  $('.views-item-selectable', context).mouseover(function() {
    var background = $(this).css('background-color');
    $('td', this).css('background-color', background);
  }).mouseout(function() {
    $('td', this).css('background-color', '');
  });

  //select view item logically and visually
  $('.views-item-selectable', context).click(function(eventObject) {
    if (eventObject.target.type !== 'radio') {
      $(':radio', this).trigger('click');
    }
  });

  //hide underlying radion button and process click behavior
  $('.views-item-selectable input:radio', context).hide().click(function (eventObject) {
    var title = $(this).val();
    $('#edit-selection').val(title);
    //selected item is marked and attached by a class
    $(this).parents('.view-content').find('.views-item-selectable').each(function () {
      $(this).removeClass('viewItemSelected');
    });
    $(this).parents('.views-item-selectable').addClass('viewItemSelected');
  });
  //cache selected value in form
  var selected = $('#edit-selection').val();
  $('input:radio[value="'+selected+'"]', context).click();
};