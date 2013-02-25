/*jslint nomen: true, plusplus: true, todo: true, white: true, browser: true, indent: 2 */
(function ($) {
  "use strict";

  /**
   * Drupal integration for jQuery Expander plugin.
   *
   * Any div with the class 'expandable' will be managed by jQuery Expander.
   * Options for the div may be attached using data attributes.
   *
   * For example:
   *   <div class="expandable" data-slice-point="200">
   *     <p></p>
   *   </div>
   */
  Drupal.behaviors.nuraniHelpersExpander = {
    attach: function (context) {
      var that = this,
          defaults = {
            // expandPrefix:     ' ', // default is '... '
            expandText:       Drupal.t('Read more'),
            userCollapseText: Drupal.t('Read less')
          };

      $('.expandable:not(.expandable-processed)', context)
        .addClass('expandable-processed')
        .each(function () {
          $(this).expander($.extend({}, defaults, that.camelCaseKeys($(this).data())));
        });
    },

    camelCaseKeys: function (data) {
      var key, newData = {};

      // Return unchanged when not an object
      if (!data || typeof(data) !== 'object') {
        return data;
      }

      for (key in data) {
        if (data.hasOwnProperty(key)) {
          newData[$.camelCase(key)] = data[key];
        }
      }

      return newData;
    }
  };

}(jQuery));