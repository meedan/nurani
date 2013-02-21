/*jslint nomen: true, plusplus: true, todo: true, white: true, browser: true, indent: 2 */
(function ($) {
  "use strict";

  /**
   * Drupal integration. Hides the default views exposed filter sort form and
   * replaces it with links.
   *
   * The commentSortUI object can be communicated with by fetching it from
   * the jQuery data storage on the views exposed form.
   *
   * eg: $('#views-exposed-form-nurani-comment-list-block')
   *       .data('commentSortUI');
   *       .applySort('DESC');
   */
  Drupal.behaviors.nuraniCommentSortLinks = {
    attach: function (context) {
      var that = this;

      $('#views-exposed-form-nurani-comment-list-block:not(.nurani-comment-processed)', context)
        .addClass('nurani-comment-processed')
        .each(function () {
          $(this).data('commentSortUI', new CommentSortUI(this));
        });
    }
  };

  /**
   * Main controller object for the bundle UI.
   */
  function CommentSortUI(element) {
    this.$wrapper = $(element);
    this.init();

    return this;
  }

  CommentSortUI.prototype.init = function () {
    this.$wrapper.hide();
    this.addSortLinks();
  };

  CommentSortUI.prototype.addSortLinks = function () {
    var that        = this,
        currentSort = $('select[name="sort_order"]', this.$wrapper).val();

    this.$sortLinks = $('<div class="nurani-sort-links"></div>');

    this.sortLinks = [
      new SortLink('DESC', Drupal.t("Most recent first"), currentSort === 'DESC', function () { that.applySort('DESC'); }),
      new SortLink('ASC', Drupal.t("Oldest first"), currentSort === 'ASC',        function () { that.applySort('ASC'); })
    ];

    this.$sortLinks
      .append(this.sortLinks[0].$link)
      .append(this.sortLinks[1].$link)
      .insertAfter(this.$wrapper);
  };

  CommentSortUI.prototype.applySort = function (direction) {
    $('select[name="sort_by"]', this.$wrapper).val('created');
    $('select[name="sort_order"]', this.$wrapper).val(direction);
    $('input[type=submit]', this.$wrapper).click();
  };


  /**
   * A Sort link object.
   */
  function SortLink(direction, text, isActive, callback) {
    var that = this;

    this.direction = direction;
    this.isActive = isActive;
    this.$link = this.createLink(text);

    this.$link.click(function () {
      callback(that);
      return false;
    });
  }

  SortLink.prototype.createLink = function(text) {
    return $('<a href="#" class="nurani-comment-sort-link ' + this.direction.toLowerCase() + (this.isActive ? ' active' : '') + '">' + text + '</a>');
  };

}(jQuery));