(function ($) {
// START jQuery

Drupal.views_autorefresh = Drupal.views_autorefresh || {};

Drupal.behaviors.views_autorefresh = function(context) {
  if (Drupal.settings && Drupal.settings.views && Drupal.settings.views.ajaxViews) {
    var ajax_path = Drupal.settings.views.ajax_path;
    // If there are multiple views this might've ended up showing up multiple times.
    if (ajax_path.constructor.toString().indexOf("Array") != -1) {
      ajax_path = ajax_path[0];
    }
    $.each(Drupal.settings.views.ajaxViews, function(i, settings) {
      var view = '.view-dom-id-' + settings.view_dom_id;
      if (!$(view).size()) {
        // Backward compatibility: if 'views-view.tpl.php' is old and doesn't
        // contain the 'view-dom-id-#' class, we fall back to the old way of
        // locating the view:
        view = '.view-id-' + settings.view_name + '.view-display-id-' + settings.view_display_id;
      }
      $(view).filter(':not(.views-autorefresh-processed)')
        // Don't attach to nested views. Doing so would attach multiple behaviors
        // to a given element.
        .filter(function() {
          // If there is at least one parent with a view class, this view
          // is nested (e.g., an attachment). Bail.
          return !$(this).parents('.view').size();
        })
        .each(function() {
          // Set a reference that will work in subsequent calls.
          var target = this;
          $('select,input,textarea', target)
          .click(function () {
            if (Drupal.settings.views_autorefresh[settings.view_name].timer) {
              clearTimeout(Drupal.settings.views_autorefresh[settings.view_name].timer);
            }
          })
          .change(function () {
            if (Drupal.settings.views_autorefresh[settings.view_name].timer) {
              clearTimeout(Drupal.settings.views_autorefresh[settings.view_name].timer);
            }
          });
          $(this)
            .addClass('views-autorefresh-processed')
            // Process pager, tablesort, and attachment summary links.
            .find('.auto-refresh a')
            .each(function () {
              var viewData = { 'js': 1 };
              var anchor = this;
              // Construct an object using the settings defaults and then overriding
              // with data specific to the link.
              $.extend(
                viewData,
                Drupal.Views.parseQueryString($(this).attr('href')),
                // Extract argument data from the URL.
                Drupal.Views.parseViewArgs($(this).attr('href'), settings.view_base_path),
                // Settings must be used last to avoid sending url aliases to the server.
                settings
              );
              $(this).click(function () {
                // Clone viewData
                // http://stackoverflow.com/questions/122102/what-is-the-most-efficient-way-to-clone-a-javascript-object
                var actualViewData = $.extend({}, viewData);
                // Handle secondary view for auto-refresh.
                if (Drupal.settings.views_autorefresh[settings.view_name].incremental) {
                  actualViewData.view_args += (viewData.view_args.length ? '/' : '') + Drupal.settings.views_autorefresh[settings.view_name].timestamp;
                  actualViewData.view_base_path = Drupal.settings.views_autorefresh[settings.view_name].incremental.view_base_path;
                  actualViewData.view_display_id = Drupal.settings.views_autorefresh[settings.view_name].incremental.view_display_id;
                  actualViewData.view_name = Drupal.settings.views_autorefresh[settings.view_name].incremental.view_name;
                }
                // Handle ping path.
                var ping_base_path;
                if (Drupal.settings.views_autorefresh[settings.view_name].ping) {
                  ping_base_path = Drupal.settings.views_autorefresh[settings.view_name].ping.ping_base_path;
                }

                $(anchor).addClass('views-throbbing');

                // If there's a ping URL, hit it first.
                if (ping_base_path) {
                  $.ajax({
                    url: Drupal.settings.basePath + ping_base_path,
                    data: {
                      timestamp: Drupal.settings.views_autorefresh[settings.view_name].timestamp
                    },
                    success: function(response) {
                      if (response.pong && parseInt(response.pong) > 0) {
                        Drupal.views_autorefresh.update(ajax_path, actualViewData, target, anchor);
                      }
                      else {
                        $(anchor).removeClass('views-throbbing');
                        Drupal.views_autorefresh.timer(settings.view_name, anchor);
                      }
                    },
                    error: function(xhr) { $(anchor).removeClass('views-throbbing'); Drupal.Views.Ajax.handleErrors(xhr, ping_base_path); },
                    dataType: 'json',
                  });
                }
                else {
                  Drupal.views_autorefresh.update(ajax_path, actualViewData, target, anchor);
                }
                return false;
              });
              // Activate refresh timer.
              Drupal.views_autorefresh.timer(settings.view_name, anchor);
            }); // .each function () {
      }); // $view.filter().each
    });
  }
}

Drupal.views_autorefresh.update = function(path, data, target, anchor) {
  $.ajax({
    url: path,
    type: 'GET',
    data: data,
    success: function(response) {
      $(anchor).removeClass('views-throbbing');
      // Call all callbacks.
      if (response.__callbacks) {
        $.each(response.__callbacks, function(i, callback) {
          eval(callback)(target, response);
        });
      }
    },
    error: function(xhr) { $(anchor).removeClass('views-throbbing'); Drupal.Views.Ajax.handleErrors(xhr, path); },
    dataType: 'json'
  });
}

// http://stackoverflow.com/questions/1394020/jquery-each-backwards
jQuery.fn.reverse = [].reverse;

Drupal.views_autorefresh.timer = function(view_name, anchor) {
  Drupal.settings.views_autorefresh[view_name].timer = setTimeout(function() {
    clearTimeout(Drupal.settings.views_autorefresh[view_name].timer);
    $(anchor).click();
  }, Drupal.settings.views_autorefresh[view_name].interval);
}

Drupal.views_autorefresh.ajaxViewResponseRefresh = function(view, response) {
  // Reactivate refresh timer.
  Drupal.views_autorefresh.timer(response.view_name, $('.auto-refresh a', view));
}

Drupal.views_autorefresh.ajaxViewResponseUpdate = function(view, response) {
  if (response.debug) {
    alert(response.debug);
  }

  var $view = $(view);
  if (response.status && response.display) {
    var sourceSelector = Drupal.settings.views_autorefresh[response.view_name].incremental.sourceSelector || '.view-content';
    var $source = $(response.display).find(sourceSelector).not(sourceSelector + ' ' + sourceSelector).children();
    if ($source.size() > 0) {
      var targetSelector = Drupal.settings.views_autorefresh[response.view_name].incremental.targetSelector || '.view-content';
      var $target = $view.find(targetSelector);

      // If initial view was empty, remove the empty divs then add the target div.
      if ($target.size() == 0) {
        var emptySelector = Drupal.settings.views_autorefresh[response.view_name].incremental.emptySelector || '.view-empty';
        var afterSelector = Drupal.settings.views_autorefresh[response.view_name].incremental.afterSelector || '.view-header';
        var targetStructure = Drupal.settings.views_autorefresh[response.view_name].incremental.targetStructure || '<div class="view-content"></div>';
        if ($(emptySelector, $view).size() > 0) {
          // replace empty div with content.
          $(emptySelector, $view).replaceWith(targetStructure);
        }
        else if ($(afterSelector, $view).size() > 0) {
          // insert content after given div.
          $(afterSelector, $view).after(targetStructure);
        }
        else {
          // insert content as first child of view div.
          $view.prepend(targetStructure);
        }
        // Now that it's inserted, find it for manipulation.
        $target = $view.find(targetSelector);
      }

      // Remove first, last row classes from items.
      var firstClass = Drupal.settings.views_autorefresh[response.view_name].incremental.firstClass || 'views-row-first';
      var lastClass = Drupal.settings.views_autorefresh[response.view_name].incremental.lastClass || 'views-row-last';
      $target.children().removeClass(firstClass);
      $source.removeClass(lastClass);

      // Adjust even-odd classes.
      var oddClass = Drupal.settings.views_autorefresh[response.view_name].incremental.oddClass || 'views-row-odd';
      var evenClass = Drupal.settings.views_autorefresh[response.view_name].incremental.evenClass || 'views-row-even';
      var oddness = $target.children(':first').hasClass(oddClass);
      $source.filter('.' + oddClass + ', .' + evenClass).reverse().each(function() {
        $(this).removeClass(oddClass + ' ' + evenClass).addClass(oddness ? evenClass : oddClass);
        oddness = !oddness;
      });

      // Add the new items to the view.
      $target.prepend($source);

      // Adjust row number classes.
      var rowClassPrefix = Drupal.settings.views_autorefresh[response.view_name].incremental.rowClassPrefix || 'views-row-';
      var rowRegex = new RegExp('views-row-(\\d+)');
      $target.children().each(function(i) {
        $(this).attr('class', $(this).attr('class').replace(rowRegex, rowClassPrefix + (i+1)));
      });

      // Trigger custom event on any plugin that needs to do extra work.
      $view.trigger('autorefresh');
    }

    // Reactivate refresh timer.
    Drupal.views_autorefresh.timer(response.view_name, $('.auto-refresh a', view));
  }

  // Save the response's timestamp for next refresh.
  if (response.timestamp) {
    Drupal.settings.views_autorefresh[response.view_name].timestamp = response.timestamp;
  }

  if (response.messages) {
    // Show any messages (but first remove old ones, if there are any).
    $view.find('.views-messages').remove().end().prepend(response.messages);
  }
}

// END jQuery
})(jQuery);

