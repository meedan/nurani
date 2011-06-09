<?php
/**
 * @file nodereference_explorer_plugin_content_nodereference.inc
 * Nodereference Explorer plugins care about the different handling of CCK field types.
 * They provide a bunch of object methods which hook into the rendering process of
 * the widget.
 */

module_load_include('inc', NODE_REFERENCE_EXPLORER_MODULE_NAME, 'plugins/content/nodereference_explorer_plugin_content');
      
class nodereference_explorer_plugin_content_nodereference extends nodereference_explorer_plugin_content  {

  public function __construct() {
    $this->value_callback = 'nodereference_autocomplete_value';
  }

  /**
   * The parent widget to which actions and preview is assigned, e. g. autocomplete widget.
   * @param $element
   * @param $edit
   * @param $form_state
   * @param $form
   */
  public function widget_process($element, $edit, $form_state, $form) {
    $element['#value_callback'] = 'nodereference_autocomplete_value';
    return nodereference_autocomplete_process($element, $edit, $form_state, $form);
  }

  /**
   * Extended rendering function for parent widget.
   * @param $element
   */
  public function theme_nodereference_explorer($element) {
    return theme('nodereference_autocomplete', $element);
  }

  /**
   * Additional widget settings form elements.
   * @param $widget
   */
  public function widget_settings_form($widget) {
    $widget['type'] = 'nodereference_autocomplete'; //pretend being an autocomplete field
    $form = nodereference_widget_settings('form', $widget);
    $widget['type'] = 'nodereference_explorer'; //nodereference explorer
    return $form;
  }

  /**
   * Additional widget settings validation.
   * @param $widget
   */
  public function widget_settings_validate($widget) {
    nodereference_widget_settings('validate', $widget);
  }

  /**
   * Additional widget settings save fields.
   * @param $widget
   */
  public function widget_settings_save($widget) {
    return nodereference_widget_settings('save', $widget); //autocomplete base settings
  }
}