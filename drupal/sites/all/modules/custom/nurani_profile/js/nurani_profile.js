(function ($) {

  /**
   * Drupal integration. Applies a tooltip effect.
   */
  Drupal.behaviors.nuraniProfileTooltip = {
    attach: function (context) {
      var that = this;

      $('.tooltip:not(.tooltip-processed)', context)
        .addClass('tooltip-processed')
        .each(function () {
          $(this).data('nuraniTooltip', new NuraniTooltip(this));
        });
    }
  };


  function NuraniTooltip(element) {
    this.$element = $(element);
    this.$tooltip = null;

    this.data     = this.$element.data('tooltip');
    this.yOffset  = 10;

    this.init();

    return this;
  }

  NuraniTooltip.prototype.init = function () {
    var that = this;


    this.$element.hover(function (e) { that.hoverOver(e); },
                        function (e) { that.hoverOut(e); });
  };

  NuraniTooltip.prototype.hoverOver = function (e) {
    var that = this;

    this.$tooltip = $('<div id="tooltip" class="loading"></div>').appendTo('body');
    this.underRugTitles();

    $.ajax({
      url: Drupal.settings.basePath + 'ajax/nurani_profile?data=' + this.data,
      cache: true,
      success: function (data) {
        that.$tooltip
          .html(data)
          .removeClass('loading');

        that.positionTooltip();
      }
    });

    this.positionTooltip().fadeIn('fast');
  };

  NuraniTooltip.prototype.hoverOut = function (e) {
    this.reinstateTitles();
    this.$tooltip.remove();
    this.$tooltip = null;
  };

  NuraniTooltip.prototype.positionTooltip = function () {
    var offset = this.$element.offset(),
        width = this.$tooltip.outerWidth(true),
        height = this.$tooltip.outerHeight(true);

    return this.$tooltip
             .css('top', offset.top - height - this.yOffset)
             .css('left', offset.left);
  };

  /**
   * Recursively sweeps all titles under the rug.
   */
  NuraniTooltip.prototype.underRugTitles = function () {
    this.$element
      .find('*[title]')
      .andSelf()
      .each(function () {
        var $this = $(this);
        $this.data('title', $this.attr('title'));
        $this.attr('title', '');
      })
  };

  /**
   * Recursively puts the titles back.
   */
  NuraniTooltip.prototype.reinstateTitles = function () {
    this.$element
      .find('*[title]')
      .andSelf()
      .each(function () {
        var $this = $(this);
        $this.attr('title', $this.data('title'));
        $this.data('title', null);
      })
  };

})(jQuery);
