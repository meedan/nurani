
/**
 * @file explorer.js
 * The nodereference explorer javascript file.
 * It's the core javascript file which is always included. Besides a
 * behavior for the core widget it is responsible for attaching js
 * and css files inline, i. e. on a JSON request.
 */
//define name space
Drupal.nodereference_explorer = Drupal.nodereference_explorer || {};

//cache added javascript sources and stylesheets
Drupal.nodereference_explorer.addedJS = [];
Drupal.nodereference_explorer.addedCSS = [];

/**
 * Return filename without path
 * 
 * @param file
 *          Filepath
 * @return basename Filename without path
 */
Drupal.nodereference_explorer.getBasename = function(file) {
  var parts = file.split('/');
  return parts[parts.length - 1];
};

/**
 * Get the nodereference_explorer settings. The component (subwidget) id
 * is provided as parameter. This function now searches in the subarray
 * "widgets" for matches and return the first one.
 * @param 
 *   id of the component
 * @return
 *   array of settings
 */
Drupal.nodereference_explorer.getSettings = function(id) {
  var settings = Drupal.settings.nodereference_explorer;
  for (var field in settings) { //field settings
  	var field_settings = settings[field];
  	for (var widget in field_settings['widgets']) { //widget settings
  	  var widget_settings = field_settings['widgets']; 
  	  for (var subwidget in widget_settings[widget]) { //subwidgets
  	    if (widget_settings[widget][subwidget] == id) { //check if match with subwidget
  	      Drupal.settings.nodereference_explorer[field]['widget'] = widget; //add widget id to be found easily
  	      return Drupal.settings.nodereference_explorer[field]; //return field
  	    }
  	  }
  	}
  }
};

/**
 * Add additional CSS to the page (see popups.js).
 */
Drupal.nodereference_explorer.addCSS = function(css) {
  for (var type in css) {
    for (var file in css[type]) {
      var link = css[type][file];
      // Does the page already contain this stylesheet?
       // Does the page already contain this stylesheet?
      var basename = Drupal.nodereference_explorer.getBasename(file);
      if (!Drupal.settings.cssInit[basename] && !$('link[href='+ $(link).attr('href') + ']').length) {
        $('head').append(link);
         Drupal.nodereference_explorer.addedCSS.push(link); // Keep a list, so we can remove them later.
      }
    }
  }
};

/**
 * Add additional Javascript to the page (see popups.js).
 */
Drupal.nodereference_explorer.addJS = function(js) {
  // Parse the json info about the new context.
  var scripts = [];
  var inlines = [];
  for (var type in js) {
    if (type != 'setting') {
      for (var file in js[type]) {
    	  //console.log(file);
        if (type == 'inline') {
          inlines.push($(js[type][file]).text());
        }
        else {
          var source = $(js[type][file]).attr('src');
          scripts.push(source);
          if (Drupal.settings.jsInit[file]) {
            Drupal.nodereference_explorer.addedJS[source] = true;
          }
        }
      }
    }
  }

  // Add new JS settings to the page, needed for #ahah properties to work.
  $.extend(Drupal.settings, js.setting);

  for (var i in scripts) {
    var src = scripts[i];
    if (!$('script[src='+ src + ']').length && !Drupal.nodereference_explorer.addedJS[src]) {
      // Get the script from the server and execute it.
      $.ajax({
        type: 'GET',
        url: src,
        dataType: 'script',
        async : false,
        success: function(script) {
          eval(script);
        }
      });
      // Mark the js as added to the underlying page.
      Drupal.nodereference_explorer.addedJS[src] = true;
    }
  }
  return inlines;
};

/**
 * Execute the jit loaded inline scripts  (see popups.js).
 * Q: Do we want to re-excute the ones already in the page?
 *
 * @source
 *   stolen straight from Popups API function Popups.addInlineJS
 * @param inlines
 *   Array of inline scripts.
 */
Drupal.nodereference_explorer.addInlineJS = function(inlines) {
  // Load the inlines into the page.
  for (var n in inlines) {
    // If the script is not already in the page, execute it.
    if (!$('script:not([src]):contains(' + inlines[n] + ')').length) {
      eval(inlines[n]);
    }
  }
};

/**
 * Behavior of core widget
 * @param
 *   DOM context
 */
Drupal.behaviors.NodereferenceExplorer = function(context) {
   //add css class to surrounding wrapper, needed for theming
  $('.nodereference-explorer .form-autocomplete', context).parent().addClass('nodereference-explorer-wrapper');
};