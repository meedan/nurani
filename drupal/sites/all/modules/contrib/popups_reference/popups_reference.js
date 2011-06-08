// $Id: popups_reference.js,v 1.1.4.3 2009/03/21 01:03:20 starbow Exp $

/**
 * Popups: Add and Reference behavior
 * 
 * Adds the behavior of selecting the newly created node.
 */

/**
 * Parse the cookies to find a value.
 *
 * @param name of cookie value.
 */ 
function popups_reference_get_cookie_value(name) {
  name += '=';
  var cookies = document.cookie.split(';');
  for (var i=0; i < cookies.length; i++) {
    var cookie = jQuery.trim(cookies[i]);
    if (cookie.indexOf(name) === 0) {
      return cookie.substring(name.length, cookie.length);
    }
  }
}

/**
 * Attach the behavior.
 */
Drupal.behaviors.popups_reference = function(context) {
  $('.popups-reference', context).not('.popups-reference-processed').each(function() {
    $(this).addClass('popups-reference-processed'); // Don't re-add to processed links.
    $(this).click(function() {
      var rel = $(this).attr('rel'); // Rel attribute of the clicked link is the wrapper id.
      // Unbind namespaced event, so bindings don't pile up every click.
      $(document).unbind('popups_form_success.popups_reference');
      
      // Bind to the popups API custom form_success event.
      $(document).bind('popups_form_success.popups_reference', function(obj, popup) {
        var $wrapper = $(popup.targetLayerSelector() + ' div.' + rel);
        // Info about the new node was placed in a cookie when it was created.
        var nid = popups_reference_get_cookie_value('PopupRefNid');
        var title = decodeURIComponent(popups_reference_get_cookie_value('PopupRefTitle'));
        $wrapper.find('select').val(nid); // Select
        $wrapper.find(':radio[value=' + nid + ']').select(); // Radio buttons
        
        // Get the first empty autocomplete field to fill (http://drupal.org/node/388406).
        $emptyAutos = $wrapper.find('input.form-autocomplete').filter(function(i) {
          return !$(this).val();
        });
        if ($emptyAutos.length) {
          $emptyAutos.eq(0).val(title);
        }
        else { // There are no empty fields, use the first one.
          $wrapper.find('input.form-autocomplete:first').val(title);
        }
      });
    });
  });
};

