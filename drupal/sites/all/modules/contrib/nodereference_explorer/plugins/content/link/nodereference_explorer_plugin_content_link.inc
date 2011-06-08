<?php
/**
 * @file nodereference_explorer_plugin_content_link.inc
 * Nodereference Explorer plugins care about the different handling of CCK field types.
 * They provide a bunch of object methods which hook into the rendering process of
 * the widget.
 */

module_load_include('inc', NODE_REFERENCE_EXPLORER_MODULE_NAME, 'plugins/content/nodereference_explorer_plugin_content');

class nodereference_explorer_plugin_content_link extends nodereference_explorer_plugin_content {

  public function __construct() {}

  /**
   * The parent widget to which actions and preview is assigned, e. g. autocomplete widget.
   * @param $element
   * @param $edit
   * @param $form_state
   * @param $form
   */
  public function widget_process($element, $edit, $form_state, $form) {
    $element = link_process($element, $edit, $form_state, $form);
    if (isset($element['#default_value']['title']))
      $node = node_load(array('title' => $element['#default_value']['title']));
    $element['value'] = array(
      '#id' => $element['#id'],
      '#type' => 'hidden',
      '#value' => !empty($element['#default_value']['title']) && !empty($node->nid) ? $element['#default_value']['title'] . '[nid: ' . $node->nid .']': '',
    );
    //create an error element, needed for storing field name for widget settings form and
    //validates widget settings properly
    $field_key  = $element['#columns'][0];
    $element['_error_element'] = array(
      '#type' => 'value',
      // Wrapping the element around a text_textfield element creates a
      // nested element, so the final id will look like 'field-name-0-url'.
      '#value' => implode('][', array_merge($element['#parents'], array($field_key))),
    );
    return $element;
  }

  /**
   * Extended rendering function for parent widget.
   * @param $element
   */
  public function theme_nodereference_explorer($element) {
    $output .= theme_link($element);
    $output .= $element['actions']['#children'];
    $output .= theme('hidden', $element['value']);
    $output .= theme('markup', $element['preview']);
    return $output;
  }

  /**
   * Additional widget settings form elements.
   * @param $widget
   */
  public function widget_settings_form($widget) {
    $form = nodereference_field_settings('form', $widget);
    $form['referenceable_types']['#weight'] = '1';
    $form['advanced']['#weight'] = '2';
    return $form;
  }

  /**
   * Additional widget settings validation.
   * @param $widget
   */
  public function widget_settings_validate($widget) {
    nodereference_field_settings('validate', $widget);
  }

   /**
   * Additional widget settings save fields.
   * @param $widget
   */
  public function widget_settings_save($widget) {
    return nodereference_field_settings('save', $widget);
  }
}