<?php
/**
 * @file
 * nodereference-explorer-view-row-fields-selectable.tpl.php
 * Template to display selectable fields from the views query.
 *
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->separator: an optional separator that may appear before a field.
 * - $row: The raw result object from the query, with all data it fetched.
 * - $selectable: View item class for marking a selectable entity
 * @ingroup views_templates
 *
 * Each row object has to have a node id (nid) and a title. These properties must
 * be provided as view fields because they rendered into the title attribute of
 * each field. Otherwise the field will not be selectable.
 */
if (!isset($selectable)) $selectable = 'views-item-selectable';
?>
<div class="<?php print $selectable; ?>">
<?php foreach ($fields as $id => $field): ?>
  <?php if (!empty($field->separator)): ?>
    <?php print $field->separator; ?>
  <?php endif; ?>

  <?php if (!empty($field->class)):?>
    <<?php print $field->inline_html;?> class="views-field-<?php print $field->class; ?>">
      <?php if ($field->label): ?>
        <label class="views-label-<?php print $field->class; ?>">
          <?php print $field->label; ?>:
        </label>
      <?php endif; ?>
  <?php endif; ?>
    <?php
      // $field->element_type is either SPAN or DIV depending upon whether or not
      // the field is a 'block' element type or 'inline' element type.
    ?>
    <?php if (!empty($field->element_type) && !empty($field->content)):?>
      <<?php print $field->element_type; ?> class="field-content"><?php print $field->content; ?></<?php print $field->element_type; ?>>
    <?php  endif; ?>
  </<?php print $field->inline_html;?>>
<?php endforeach; ?>
</div>