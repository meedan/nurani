
/**
 * @file explorer.tabs.js
 * Create tabs which contains the displays of the referenced view.
 * The default display is hidden. When there's only one display to
 * be shown the tabs are hidden as well.
 */

/**
 * Tab related events, e. g. show/hide filter a form or
 * render the initial display
 * @param
 *   DOM context
 */
Drupal.behaviors.NodereferenceExplorerTabs = function(context) {
  
  //Since jQuery UI 1.7 markup requires a container for list and panels, thus can no longer tabify a UL directly
  if (parseFloat($.ui['version']) > 1.6) {
    var tabs = $('div.nodereference-explorer-tabset', context);
  }
  else { //in jQuery UI 1.6 we have to call "ul" tag directly for rendering tabs
    var tabs = $('div.nodereference-explorer-tabset ul.nodereference-explorer-tabs', context);
  }
  $(tabs).tabs();
  
  //event when tab is switched
  $(tabs).bind('tabsselect', function(event, ui) {
	//FIX for browser hiding of multiple identical ids of filter forms
	$('.views-widget .form-item', context).show();
	
    //The selected node needs to be highlighted across the different displays.
	//On each tab switch the current selected value is retrieved and the radio 
	//button on the new display is selected manually
	$('.viewItemSelected').removeClass('viewItemSelected'); //remove all selections first
	var selected = $('#edit-selection').val(); //get current selection
	$('input:radio[value="'+selected+'"]', context).click(); //select items (if shown or not)	
    
	//hide all filters because all are shown by default
    $('.nodereference-explorer-views-filters', context).hide();
    //display exposed filters if they are in a separate block for selected tab
    var display = $(ui.panel).attr('id');
    $('#nodereference-explorer-filter-'+display, context).show();
    
    //TODO: synchronize filters to have the same nodes and selection shown
  });
  
  //apply changes on 'tabsselect' by selectin manually, i. e. hide other filter forms
  //select second than first, otherwise nothing is processed
  $(tabs).tabs('select', 1); 
  $(tabs).tabs('select', 0);
  
  //show no tab if only one display
  if ($(tabs).children().length < 2)
    $('li.nodereference-explorer-tab', tabs).hide();
};