<?php
/**
 * @file
 * nodereference-explorer-dialog.tpl.php
 * Template to display a dialog with views
 *
 * - $handler: The widget handler object
 *   - $handler->nid: current node id
 *   - $handler->get_id($key): get an id of a html tag
 * 	 - $handler->get_all_displays: get all displays of the view
 *   - $handler->get_display($id): get a specific display of a view
 * - $dialog: Array containing window dialog settings, e. g. theme class
 * - $display: A display of a view
 *   - $display->display_title: Label of the display
 * @ingroup views_templates
 *
 * The style attribute "overflow: auto" enables automatic scrollbars when resizing
 * the dialog.
 */
?>
<div title="<?php print $title; ?>" style="overflow: auto" class="nodereference-explorer-dialog">
  <?php foreach ($filters as $display_id => $filter): ?>
    <div id="nodereference-explorer-filter-<?php print $display_id; ?>" class="nodereference-explorer-views-filters"><?php print $filter; ?></div>
  <?php endforeach; ?>
  <div id="tabs" class="nodereference-explorer-tabset">
	<ul class="tabs primary nodereference-explorer-tabs">
	  <?php foreach ($tabs as $display_id => $tab): ?>
		<li class="nodereference-explorer-tab" title="<?php print $display->display_title; ?>">
          <?php print $tab; ?>
		</li>
	  <?php endforeach; ?>
	</ul>
    <?php foreach ($displays as $display_id => $display): ?>
      <div id="<?php print $display_id; ?>"><?php print $display; ?></div>
    <?php endforeach; ?>
  </div>
</div>