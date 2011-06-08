<?php
/**
 * @file nodereference_explorer_plugin_content.inc
 * Nodereference Explorer plugins care about the different handling of CCK field types.
 * They provide a bunch of object methods which hook into the rendering process of
 * the widget.
 *
 * Child classes must inherit the methods provided here.
 */
abstract class nodereference_explorer_plugin_content {

  public $value_callback = NULL; //define callback function for the widget value

  /**
   * The parent widget to which actions and preview is assigned, e. g. autocomplete widget.
   * @param $element
   * @param $edit
   * @param $form_state
   * @param $form
   */
  public abstract function widget_process($element, $edit, $form_state, $form);

  /**
   * Extended rendering function for parent widget.
   * @param $element
   */
  public abstract function theme_nodereference_explorer($element);

  /**
   * Additional widget settings form elements.
   * @param $widget
   */
  public abstract function widget_settings_form($widget);

  /**
   * Additional widget settings validation.
   * @param $widget
   */
  public abstract function widget_settings_validate($widget);

  /**
   * Additional widget settings save fields.
   * @param $widget
   */
  public abstract function widget_settings_save($widget);

}