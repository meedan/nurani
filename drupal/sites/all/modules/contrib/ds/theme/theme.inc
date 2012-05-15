<?php

/**
 * @file
 * Theming functions for ds.
 */

/**
 * Theme function to render the field content.
 *
 * @param array $field Collection of field properties.
 */
function theme_ds_field($field) {
  $output = '';

  if (!empty($field['content'])) {
    $output .= '<div class="field '. $field['class'] .'">';
    // Above label.
    if ($field['labelformat'] == 'above') {
      $output .= '<div class="field-label">'. $field['title'] .': </div>';
    }
    // Inline label
    if ($field['labelformat'] == 'inline') {
      $output .= '<div class="field-label-inline-first">'. $field['title'] .': </div>';
    }
    $output .= $field['content'];
    $output .= '</div>';
  }

  return $output;
}

/**
 * Theme function to render the field content inline
 *
 * This does not support "above" labels, for obvious reasons.
 *
 * @param array $field Collection of field properties.
 */
function theme_ds_field_inline($field) {
  $output = '';

  if (!empty($field['content'])) {
    $output .= '<div class="field field-inline '. $field['class'] .'">';
    // Inline label
    if ($field['labelformat'] == 'inline') {
      $output .= '<div class="field-label-inline-first">'. $field['title'] .': </div>';
    }
    $output .= $field['content'];
    $output .= '</div>';
  }

  return $output;
}

/**
 * Theme function to render all regions with their content.
 *
 * @param stdClass $object_display The complete object and display properties.
 * @param string $module The module name.
 *
 * Other variables which you can use:
 *  - $region_data['count']: holds the number of fields per region.
 */
function theme_ds_regions($object_display, $module) {
  $output = '';

  foreach ($object_display->themed_regions as $region_name => $region_data) {
    $output .= '<div class="'. $module .'-region-'. $region_name;

    // The middle region has a wrapper region and some sidebar related classes.
    if ($region_name == 'middle') {
      $output .= '-wrapper ';
    }
    if ($region_name == 'header' || $region_name == 'footer') {
      $output .= ' clear-block';
    }

    // Extra classes or inline styles.
    if (!empty($region_data['extra_class'])) {
      $output .= $region_data['extra_class'];
    }
    $output .= '" ';
    if (isset($region_data['inline_css'])) {
      $output .= $region_data['inline_css'];
    }

    // Close the wrapper for middle if necessary.
    if ($region_name == 'middle') {
      $output .= '><div class="'. $module .'-region-'. $region_name .'">'. $region_data['content'] .'</div></div>';
    }
    else {
      $output .= '>'. $region_data['content'] .'</div>';
    }
  }

  return $output;
}

/**
 * Evaluate custom code.
 *
 * @param array $field The field with all its properties.
 */
function theme_ds_eval_code($field) {
  if (isset($field['properties']['code'])) {
    $value = ds_eval($field['properties']['code'], $field['object']);
    // Token support - check on token property so we don't run every single field through token.
    if (module_exists('token') && isset($field['properties']['token']) && $field['properties']['token'] == TRUE) {
      $value = token_replace($value, $field['object_type'], $field['object']);
    }
    return $value;
  }
}

/**
 * Evaluate block field.
 *
 * @param array $field The field array.
 */
function theme_ds_eval_block($field) {
  if (isset($field['properties'])) {
    list($module, $delta) = explode('|', $field['properties']['block']);
    $block = module_invoke($module, 'block', 'view', $delta);
    if (!empty($block)) {
      switch ($field['properties']['render']) {
        case DS_BLOCK_TEMPLATE:
          global $theme_key;
          if ($block['content']) {
            $block = (object) $block;
            $block->region = NULL;
            $block->module = $module;
            $block->delta = $delta;
            $block_title = db_result(db_query("SELECT title FROM {blocks} WHERE module = '%s' AND delta = '%s' AND theme = '%s'", $module, $delta, $theme_key));
            if (!empty($block_title)) {
              $block->subject = $block_title == '<none>' ? '' : check_plain($block_title);
            }
            $content = theme('block', $block);
          }
          break;
        case DS_BLOCK_TITLE_CONTENT:
          $content = '<h2 class="block-title">'. $block['subject'] .'</h2>';
          $content .= $block['content'];
          break;
        case DS_BLOCK_CONTENT:
          $content = $block['content'];
          break;
      }
      return $content;
    }
  }
}

/**
 * Theme a collection of ds objects.
 *
 * @param array $data A collection of data to print.
 * @param array $extra A collection data, ie context etc ..
 */
function theme_ds_objects($data, $extra) {
  $output = '';
  foreach ($data as $key => $value) {
    $output .= $value->content;
  }
  return $output;
}

/**
 * Theme a group (fieldset).
 *
 * @param string $field The field to theme.
 */
function theme_ds_group_fieldset($field) {
  $add_js = FALSE;
  $class = $field['class'];
  $variation = array_pop(explode('_', $field['theme']));

  switch ($variation) {
    case 'collapsible':
      $add_js = TRUE;
      $class .= ' collapsible';
      break;
    case 'collapsed':
      $add_js = TRUE;
      $class .= ' collapsible collapsed';
      break;
    default:
      break;
  }

  // Add js.
  if ($add_js == TRUE) {
    drupal_add_js('misc/collapse.js');
  }
  
  // Set a legend if a field title exists
  $legend = NULL;
  if (!empty($field['title'])) {
    $legend = '<legend>'. $field['title'] .'</legend>';
  }

  return '<fieldset class="group '. $class .'">'. $legend . $field['content'] .'</fieldset>';
}

/**
 * Theme a multigroup as a collection of simple objects
 *
 * @param string $group 
 *  The multigroup to theme.
 */
function theme_ds_multigroup_div($group) {
  $output = '';

  foreach ($group['rows'] as $row){
    $row_output = '';
    
    // Set a legend if a field title exists
    $output .= '<div class="'. $row['class'] .'">';
    if (!empty($row['title'])) {
      $row_output = theme('ds_subgroup_label', $row['title']);
    }
    foreach ($row['fields'] as $field) {
      $class = (!empty($field['class']) ? ' '. $field['class'] : '');
      $row_output .= '<div class="field field-item '. $field['key'] . $class .'">';
      // Above label.
      if ($field['labelformat'] == 'above') {
        $row_output .= '<div class="field-label">'. $field['title'] .': </div>';
      }
      // Inline label
      elseif ($field['labelformat'] == 'inline') {
        $row_output .= '<div class="field-label-inline-first">'. $field['title'] .': </div>';
      }

      $row_output .= $field['view'] .'</div>';
    }

    $output .= $row_output;
    $output .= '</div>';
  }

  return $output;
}

/**
 * Theme a multigroup as a collection of fieldsets.
 *
 * @param string $group 
 *  The multigroup to theme.
 */
function theme_ds_multigroup_fieldset($group) {
  $collapsible = FALSE;
  $class = NULL;
  $variation = array_pop(explode('_', $group['theme']));

  switch ($variation) {
    case 'collapsible':
      $collapsible = TRUE;
      $class = ' collapsible';
      break;
    case 'collapsed':
      $collapsible = TRUE;
      $class = ' collapsible collapsed';
      break;
    default:
      break;
  }

  // Add js.
  if ($collapsible == TRUE) {
    drupal_add_js('misc/collapse.js');
  }

  // Build content by iterating over subgroups
  $content = '';

  foreach($group['rows'] as $row){
    // Set a legend if a field title exists
    $legend = NULL;
    if (!empty($row['title']) || $collapsible == TRUE) {
      if (empty($row['title'])){
        // @todo - what goes here when no value is present?
        $row['title'] = 'open/close';
      }
      $legend = '<legend>'. $row['title'] .'</legend>';
    }

    $content .= '<fieldset class="group '. $row['class'] . $class .'">'. $legend . $row['content'] .'</fieldset>';
  }
  
  return $content;
}

/**
 * Theme a multigroup (fieldset).
 *
 * @param string $group 
 *  The multigroup to theme.
 */
function theme_ds_multigroup_table_simple($group) {
  $headers = array();
  $rows = array();
  foreach ($group['rows'] as $row) {
    $items = array();
    foreach ($row['fields'] as $field) {
      $item = $field['view'];
      if (!empty($item)) {
        $items[] = $item;
      }
    }
    if (!empty($items)) {
      if (!empty($row['title'])) {
        array_unshift($items, '<label class="content-multigroup">'. $row['title'] .':</label>');
      }
      $rows[] = array('data' => array(implode("\n", $items)), 'class' => $field['class']);
    }
  }
  
  return count($rows) ? theme('table', $headers, $rows) : '';
}

/**
 * Theme a multigroup (fieldset).
 *
 * @param string $field The field to theme.
 */
function theme_ds_multigroup_table_multiple($group) {
  $headers = array();

  // Set up row labels from subgroup labels, if applicable
  $row_labels = array();
  $labels = FALSE;
  foreach ($group['rows'] as $row_delta => $row) {
    if (isset($row['title'])){
      $row_labels[$row_delta] = $row['title'];
      $labels = TRUE;
    }
    else {
      $row_labels[$row_delta] = '';
    }
  }

  foreach ($group['fields'] as $field) {
    if(isset($labels) && $labels == TRUE) {
      $headers[0] = array(
        'data' => '',
        'class' => $field['class'] .' ds-subgroup-label content-multigroup-cell-'. str_replace('_', '-', $field_name),
      );
    }
  
    $label_display = isset($field['labelformat']) ? $field['labelformat'] : 'above';
    $headers[] = array(
      'data' => ($label_display != 'hidden' ? check_plain(t($field['title'])) : ''),
      'class' => 'content-multigroup-cell-'. str_replace('_', '-', $field_name),
    );
  }

  // Prepare the data
  $rows = array();
  foreach ($group['rows'] as $row_delta => $row) {
    $cells = array();
    $empty = TRUE;
    // Pick up subgroup labels
    if(isset($labels) && $labels == TRUE) {
      $cells[0] = array(
        'data' => $row_labels[$row_delta],
        'class' => $field['class'] .' content-multigroup-cell-row-label',
      );
    }
    // Regular content
    foreach ($row['fields'] as $field_name => $field) {
      $cells[] = array(
        'data' => $field['view'],
        'class' => $field['class'] .' content-multigroup-cell-'. str_replace('_', '-', $field_name),
      );
      if (!empty($field['view'])) {
        $empty = FALSE;
      }
    }
    // Get the row only if there is at least one non-empty field.
    if (!$empty) {
      $rows[] = $cells;
    }
  }

  return count($rows) ? theme('table', $headers, $rows) : '';
}

/**
 * Theme a multigroup divided by horizontal lines
 *
 * @param string $group The group to theme.
 */
function theme_ds_multigroup_horizontal_line($group) {
  $output = '';
  foreach ($group['rows'] as $row_delta => $row) {
    $divider = ($row_delta > 0 ? '<hr class="content-multigroup" />' : '');
    $output .= '<div'. drupal_attributes(array('class' => $row['class'])) .'>'. $divider;
    if (!empty($row['title'])) {
      $output .= theme('ds_subgroup_label', $row['title']);
    }
    $output .= $row['rendered'].'</div>';
  }
  return $output;
}

/**
 * Theme a multigroup list.
 *
 * @param string $group The group to theme.
 */
function theme_ds_multigroup_list($group) {
  $variation = array_pop(explode('_', $group['theme']));

  switch ($variation) {
    case 'ol':
      $type = 'ol';
      break;
    case 'ul':
    default:
      $type = 'ul';
      break;
  }

  $items = array();
  foreach ($group['rows'] as $row) {
    if (!empty($row['rendered'])) {
      $items[] = $row['rendered'];
    }
  }
  $attr['class'] .= $row['class'];
  return count($items) ? theme('item_list', $items, NULL, $type, $attr) : '';
}

/**
 * Theme a multigroup as a comma separated list
 *
 * @param string $group 
 *  The multigroup to theme.
 */
function theme_ds_multigroup_comma_separated($group) {
  $output = '';

  foreach ($group['rows'] as $row){
    $row_output = '';
    
    // Set a legend if a field title exists
    $output .= '<div class="'. $row['class'] .'">';
    if (!empty($row['title'])) {
      $row_output = theme('ds_subgroup_label', $row['title']);
    }
    $n = count($row['fields']);
    $count = 1;
    foreach ($row['fields'] as $field) {
      $class = (!empty($field['class']) ? ' '. $field['class'] : '');
      $row_output .= '<span class="field-item '. $field['key'] . $class .'">';
      if ($field['labelformat'] == 'inline') {
        $row_output .= '<span class="field-label-inline-first">'. $field['title'] .': </span>';
      }
      $row_output .= $field['view'] .'</span>';
      if ($count != $n) {
        $row_output .= ', ';
      }
      $count++;
    }

    $output .= $row_output;
    $output .= '</div>';
  }

  return $output;
}

/**
 * Theme tabs. This is based on the theme_tabset() function
 * from the tabs module. We use our own theming function because
 * otherwhise we need to loop through our fields to build the
 * right array before we an send it to theme('tabset');
 */
function theme_ds_tabs($field) {
  tabs_load();

  static $i = 1;
  $fields = $field['fields'];
  ksort($fields);

  $tab_navigation = (variable_get('tabs_navigation', 0)) ? ' tabs-navigation' : '';

  $tabs_content = '';
  $output = '<div id="tabs-'. $field['name'] .'" class="drupal-tabs js-hide'. $tab_navigation .'" style="display:block;">';
  $tabs = '<ul class="clear-block ui-tabs-nav tabs">';
  foreach ($fields as $weight => $data) {
    $tabs .= '<li class="tabset-tab-'. $i .'">
    <a href="#tabset-tab-'. $i .'"><span class="tab">'. $data['title'] .'</span></a></li>';
    $tabs_content .= '<div id="tabset-tab-'. $i .'" class="tabs-'. $field['name'] .' ui-tabs-panel '. $data['class'] .'">'. $data['content'] .'</div>';
    $i++;
  }
  $tabs .= '</ul>';
  $output .= $tabs;
  $output .= $tabs_content;
  $output .= '</div>';
  return $output;
}

/**
 * Theme the subgroup label
 */
function theme_ds_subgroup_label($label, $class = NULL) {
  $classes = 'content_multigroup';
  if (!empty($class)) {
    $classes = $classes .' '. $class;
  }

  return '<legend class="'. $classes .'">'. $label .'</legend>';
}

/**
 * Theme author name.
 */
function theme_ds_author_nolink($field) {
  return $field['object']->name;
}

/**
 * Theme author name linked.
 */
function theme_ds_author_link($field) {
  return theme('username', $field['object']);
}

/**
 * Theme the user picture.
 */
function theme_ds_picture($field) {
  return theme('user_picture', $field['object']);
}

/**
 * Template preprocess function for theme_views_view_row_object().
 * We delegate the manipulation of the object to a function
 * which every module implementing the ds_api should define.
 */
function template_preprocess_ds_row_object(&$vars) {
  $options = $vars['options'];
  $vars['object'] = '';
  $vars['data_object'] = '';

  // The advanced selector searches for a function called
  // ds_views_row_adv_VIEWSNAME.
  if ($options['advanced']) {
    $build_mode = $options['build_mode'];
    $row_function = 'ds_views_row_adv_'. $vars['view']->name;
    $row_function($vars, $build_mode);
  }
  // The default selector searches for a function called
  // ds_views_row_VIEWSBASETABLE.
  // This function also takes care for changing the build
  // mode per row and pagination. Simple grouping is
  // also supported if there is a sort handler.
  else {
    static $nrs, $grouping = array();
    $group_value_content = '';
    $view_name = $vars['view']->name .'_'. $vars['view']->current_display;

    // Keep a static number for this view.
    if (!isset($nrs[$view_name])) {
      $nrs[$view_name] = 0;
    }

    // Change the build mode per view.
    if (isset($options['changing']) && $options['changing']) {
      // Check for paging to determine the build mode.
      if (isset($_GET['page']) && isset($options['changing_fieldset']['allpages']) && !$options['changing_fieldset']['allpages']) {
        $build_mode = $options['build_mode'];
      }
      else {
        $build_mode = $options['changing_fieldset']['item_'. $nrs[$view_name]];
      }
    }
    else {
      $build_mode = $options['build_mode'];
    }

    // Call the function.
    $row_function = 'ds_views_row_'. $vars['view']->base_table;
    $row_function($vars, $build_mode);

    // Keep a static grouping for this view.
    if (isset($options['grouping']) && $options['grouping']) {
      $group_value = $vars['view']->result[$nrs[$view_name]]->$options['grouping_fieldset']['group_field'];
      if (!isset($grouping[$view_name][$group_value])) {
        $group_value_content = '<h2 class="grouping-title">'. $group_value .'</h2>';
        $grouping[$view_name][$group_value] = $group_value;
      }
    }

    // Grouping or not ?
    if (!empty($grouping[$view_name])) {
      if (!empty($group_value_content)) {
        $vars['data_object'] = $group_value_content;
      }
      $vars['data_object'] .= '<div class="grouping-content">'. $vars['object'] .'</div>';
    }
    else {
      $vars['data_object'] = $vars['object'];
    }

    // Increment the number for this view.
    $nrs[$view_name]++;
  }
}

/**
 * Preprocess theme function to print a single record from a row, with fields.
 */
function template_preprocess_ds_row_fields(&$vars) {
  template_preprocess_views_view_fields($vars);
}
