/**
 * Equal Heights Plugin
 * Equalize the heights of elements. Great for columns or any elements
 * that need to be the same size (floats, etc).
 * 
 * Version 1.0
 * Updated 12/10/2008
 *
 * Copyright (c) 2008 Rob Glazebrook (cssnewbie.com) 
 *
 * Usage: $(object).equalHeights([minHeight], [maxHeight]);
 * 
 * Example 1: $(".cols").equalHeights(); Sets all columns to the same height.
 * Example 2: $(".cols").equalHeights(400); Sets all cols to at least 400px tall.
 * Example 3: $(".cols").equalHeights(100,300); Cols are at least 100 but no more
 * than 300 pixels tall. Elements with too much content will gain a scrollbar.
 * 
 */

(function($) {
	
	$.fn.equalHeights = function(minHeight, maxHeight) {
		var tallest = (minHeight) ? minHeight : 0;
		this.each(function() {
			if($(this).height() > tallest) {
				tallest = $(this).height();
			}
		});
		if((maxHeight) && tallest > maxHeight) tallest = maxHeight;
		return this.each(function() {
			$(this).height(tallest).css("overflow","hidden");
		});
	};

	/**
	 * Extension to the equalHeights plugin which adds support for equalizing
	 * heights per-row.  Automatically calculates the number of columns per row.
	 *
	 * @author James Andres (jamesandres.com)
	 */
	$.fn.equalHeightsPerRow = function(minHeight, maxHeight) {
		var group = [], offset = null, lastX = 0;

		this.each(function () {
			offset = $(this).offset();

			if (group.length > 0 && offset.left <= lastX) {
				$(group).equalHeights(minHeight, maxHeight);
				group = [];
			}

			lastX = offset.left;
			group.push(this);
		});

		if (group.length > 0) {
			$(group).equalHeights(minHeight, maxHeight);
		}

		return this;
	};

})(jQuery);