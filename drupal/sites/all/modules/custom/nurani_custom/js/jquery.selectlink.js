/*!
 * Select Link Plugin - Arshad Chummun
 * http://preprocess.me/selectlink
 *
 * Copyright (c) 2009 Arshad Chummun (http://preprocess.me)
 * Dual licensed under the MIT (http://www.opensource.org/licenses/mit-license.php)
 * and GPL (http://www.opensource.org/licenses/gpl-license.php) licenses.
 *
 *
 */
(function($) {
  $.fn.selectlink = function(options) {
    //default values
    $.fn.selectlink.defaults = {
      min : 3,
      max : 1000,
      text : '?',
      url : '#',
      target : '_blank',
      title : 'Select link'
    };

    // build main options
    var opts = $.extend({}, $.fn.selectlink.defaults, options);

    return this.each(function() {
        $this = $(this);
        
        $(this).mouseup(function(e) {
          //get the text selected
          var q = getSelectedText();
          //check limit
          if (q && String(q).length > opts.min && String(q).length < opts.max) {
            //remove any popText
            $("#popText").remove();

            if (!popText) {
              var popText = $("<a>").attr({
                href : opts.url.replace('%term%',q),
                id : 'popText',
                title : opts.title.replace('%term%',q),
                target : opts.target
              }).html(opts.text.replace('%term%',q)).css({
                'position' : 'absolute',
                'top' : e.pageY - 40,
                'left' : e.pageX - 10,
                'zIndex': 100
              }).hide();
            }

            //insert the popText
            $("body").append(popText).find('#popText').fadeIn("slow");

            //hide popText on document click
            $(document).mousedown(function() {
              $("#popText").fadeOut("slow");
            });
          }
        });
    });
  };

})(jQuery);

/**
 * Function to find selected text - cross browser compatible
 */
function getSelectedText() {
  if (window.getSelection) {
    return window.getSelection();
  }
  else if (document.getSelection) {
    return document.getSelection();
  }
  else {
    var selectedText = document.selection && document.selection.createRange();
    if (selectedText.text) {
      return selectedText.text;
    }
    return false;
  }
  return false;
}
