<?php
/**
 * @file nodereference_explorer.widget.settings.inc
 * Holds all settings related events
 * - form creation
 * - form saving
 * - form validation
 */

/**
 * Implementation of CCK's hook_widget_settings().
 */
function nodereference_explorer_widget_settings($op, $widget) {
  switch ($op) {
    case 'form':
      return nodereference_explorer_widget_settings_form($widget);
    case 'validate':
      return nodereference_explorer_widget_settings_validate($widget);
    case 'save':
      return nodereference_explorer_widget_settings_save($widget);
  }
}

/**
 * Implementation of hook_widget_settings_form(). Create the settings form
 * @param $widget
 * @return
 *   settings form
 */
function nodereference_explorer_widget_settings_form($widget) {
  if ($widget['type'] == NODE_REFERENCE_EXPLORER_MODULE_NAME) {

    $form = array();

    $boolean = array(
      t('yes'),
      t('no'),
    );

    //CONTENT SETTINGS
    $form['content'] = array(
      '#type' => 'fieldset',
      '#title' => t('Content'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
      '#description' => t('These settings let you configure the widget related content, e. g. preview.'),
    );

    $field = _nodereference_explorer_widget_settings_get_content_field($widget);
    $plugin = nodereference_explorer_plugins_load_plugin($field['type']);
    if (isset($plugin)) {
      foreach ($plugin->widget_settings_form($widget) as $id => $element) {
        $form['content'][$id] = $element;
      }
    }

    //update the preview display options according to the selection in the advanced view selection
    $setting[NODE_REFERENCE_EXPLORER_MODULE_NAME] = array(
      'edit-advanced-view' => array(
        'path' => url(NODE_REFERENCE_EXPLORER_MENU_CALLBACK_PREVIEW_DISPLAYS),
        'widget' => 'edit-' . form_clean_id('content_preview'),
        'value' => isset($widget['content_preview']) ? $widget['content_preview'] : 'preview',
      ),
    );
    drupal_add_js($setting, 'setting'); //js settings
    nodereference_explorer_add_js('explorer.settings'); //preview displays behavior js

    $form['content']['content_preview'] = array(
      '#type' => 'select',
      '#options' => array(),
      '#title' => t('Preview display'),
      '#default_value' => isset($widget['content_preview']) ? $widget['content_preview'] : 'preview',
      '#description' => t('Leave it blank if you do not want to use any preview.'),
	  '#element_validate' => array(),
      //Avoid a form error message on validation, by skipping this element, i. e. set to already validated.
      //Options are updated via JSON on the JavaScript side, so we do not know the allowed
      //values yet. Users may choose a preview display according to "View used to select the nodes" selection.
      '#validated' => true,
    );

    $form['content']['content_preview_position'] = array(
      '#type' => 'select',
      '#options' => array('below' => t('Below'), 'above' => t('Above')),
      '#title' => t('Preview position'),
      '#default_value' => isset($widget['content_preview_position']) ? $widget['content_preview_position'] : 'below',
      '#description' => t('Determine whether the preview should be shown above or below the core widget.'),
    );

    //DIALOG SETTINGS
    $align = array(
      'center' => t('Center'),
      'left' => t('Left middle'),
      'right' => t('Right middle'),
      'top' => t('Top center'),
      'bottom' => t('Bottom center'),
    );

    //core settings: title, width, height
    $form['dialog'] = array(
      '#type' => 'fieldset',
      '#title' => t('Dialog'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
      '#description' => t('These settings are the configuration options of the jQuery UI dialog window.'),
    );

    $form['dialog']['dialog_title'] = array(
      '#type' => 'textfield',
      '#title' => t('Title'),
      '#default_value' => isset($widget['dialog_title']) ? $widget['dialog_title'] : $widget['label'] . ' ' . t('Explorer'),
      '#required' => TRUE,
      '#description' => t('The label in the title bar.'),
    );

    $form['dialog']['dialog_width@int'] = array(
      '#type' => 'textfield',
      '#title' => t('Width'),
      '#default_value' => isset($widget['dialog_width@int']) ? $widget['dialog_width@int'] : 800,
      '#required' => TRUE,
      '#description' => t('The preferred width of the dialog window.'),
    );

    $form['dialog']['dialog_height@int'] = array(
      '#type' => 'textfield',
      '#title' => t('Height'),
      '#default_value' => isset($widget['dialog_height@int']) ? $widget['dialog_height@int'] : 600,
      '#required' => TRUE,
      '#description' => t('The preferred height of the dialog window.'),
    );

    //Set dialog API, modalframe, if existing
    $api = 'nodereference_explorer';
    $dialog_apis = array(
      $api => 'Built-in (Deprecated)',
    );
    if (module_exists('modalframe')) {
      $api = 'modalframe';
      $dialog_apis[$api] = 'Modal Frame (Recommended)';
    }

    $form['dialog']['dialog_api'] = array(
      '#type' => 'select',
      '#title' => t('Dialog API'),
      '#default_value' => isset($widget['dialog_api']) ? $widget['dialog_api'] : $api,
      '#options' => $dialog_apis,
      '#description' => t('It is recommended to install !modalframe instead of the deprecated "Built-in" API.',
        array(
          '!modalframe' => l(theme('placeholder', 'Modal Frame'), 'http://drupal.org/project/modalframe', array('html' => TRUE)),
        )
      ),
    );

    //alignment of window
    $form['dialog']['align']['dialog_position'] = array(
      '#type' => 'select',
      '#title' => t('Position'),
      '#options' => $align,
      '#default_value' => isset($widget['dialog_position']) ? $widget['dialog_position'] : 'center',
      '#description' => t('The position of the dialog window.'),
    );

    $form['dialog']['theming'] = array(
      '#type' => 'fieldset',
      '#title' => t('Theming'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    global $theme;
    //get all system themes
    $system_themes = system_theme_data();
    //standard themes
    $themes = array(
      t('Module (built-in)') => array('<module>' => t('Default')),
      t('Global (current)') => array('<global>' => $system_themes[$theme]->info['name']),
    );
    //get all jquery ui themes
    $jq_ui_theme_path = JQUERY_UI_PATH .'/themes';
    $jquery_themes =
      file_scan_directory(
        $jq_ui_theme_path, '.*', array('.', '..', 'CVS'), 0, FALSE);

    foreach ($jquery_themes as $jquery_theme) {
      if (file_check_location($jquery_theme->filename)) {
        $themes['jQuery UI'][$jquery_theme->basename] = ucfirst($jquery_theme->basename);
      }
    }

    $form['dialog']['theming']['theme_css'] = array(
      '#type' => 'select',
      '#options' => $themes,
      '#title' => t('Themes'),
      '#default_value' => isset($widget['theme_css']) ? $widget['theme_css'] : '<module>', //$default_theme_path,
      '#description' => t('Widget theme composed of module, global and jquery_ui module themes (subpath:') . '<br/>"' . $jq_ui_theme_path .'").',
    );

    $form['dialog']['theming']['dialog_dialogClass'] = array(
      '#type' => 'textfield',
      '#title' => t('CSS scope'),
      '#default_value' => isset($widget['dialog_dialogClass']) ? $widget['dialog_dialogClass'] : '', //flora',
      '#description' => t('This field allows you to specify a CSS scope to limit your theme to a particular portion of a page. This is helpful when using multiple themes on a page.
        If you don\'t provide a CSS scope, your theme will apply to all UI elements on a page.'),
    );

    $form['dialog']['theming']['dialog_bgiframe@boolean'] = array(
      '#type' => 'select',
      '#title' => t('Background iFrame (IE 6)'),
      '#options' => $boolean,
      '#default_value' => isset($widget['dialog_bgiframe@boolean']) ? $widget['dialog_bgiframe@boolean'] : 0,
      '#description' => t('Loads a background iframe, fixes the IE 6 z-Index issue that background form controls <br/>like a drop-down or select list show on top of the dialog'),
    );


    $form['dialog']['advanced_dimensions'] = array(
      '#type' => 'fieldset',
      '#title' => t('Extra dimensions'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $form['dialog']['advanced_dimensions']['dialog_minWidth@int'] = array(
      '#type' => 'textfield',
      '#title' => t('Minimal width'),
      '#default_value' => isset($widget['dialog_minWidth@int']) ? $widget['dialog_minWidth@int'] : '',
      '#description' => t('The minimal width of the dialog window (leave blank or 0 if no limit).'),
    );

    $form['dialog']['advanced_dimensions']['dialog_minHeight@int'] = array(
      '#type' => 'textfield',
      '#title' => t('Minimal height'),
      '#default_value' => isset($widget['dialog_minHeight@int']) ? $widget['dialog_minHeight@int'] : '',
      '#description' => t('The minimal height of the dialog window (leave blank or 0 if no limit).'),
    );

    $form['dialog']['advanced_dimensions']['dialog_maxWidth@int'] = array(
      '#type' => 'textfield',
      '#title' => t('Maximal width'),
      '#default_value' => isset($widget['dialog_maxWidth@int']) ? $widget['dialog_maxWidth@int'] : '',
      '#description' => t('The maximal width of the dialog window (leave blank or 0 if no limit).'),
    );

    $form['dialog']['advanced_dimensions']['dialog_maxHeight@int'] = array(
      '#type' => 'textfield',
      '#title' => t('Maximal height'),
      '#default_value' => isset($widget['dialog_maxHeight@int']) ? $widget['dialog_maxHeight@int'] : '',
      '#description' => t('The maximal height of the dialog window (leave blank or 0 if no limit).'),
    );

    $form['dialog']['control'] = array(
      '#type' => 'fieldset',
      '#title' => t('Controls'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $form['dialog']['control']['dialog_draggable@boolean'] = array(
      '#type' => 'select',
      '#title' => t('Draggable'),
      '#options' => $boolean,
      '#default_value' => isset($widget['dialog_draggable@boolean']) ? $widget['dialog_draggable@boolean'] : 0,
      '#description' => t('Specify if the dialog can be dragged by clicking the title bar.'),
    );

    $form['dialog']['control']['dialog_resizable@boolean'] = array(
      '#type' => 'select',
      '#title' => t('Resizable'),
      '#options' => $boolean,
      '#default_value' => isset($widget['dialog_resizable@boolean']) ? $widget['dialog_resizable@boolean'] : 0,
      '#description' => t('Specify if the dialog can be resized.'),
    );

    //close on escape is only supported in jquery ui version >= 1.6
    $form['dialog']['control']['dialog_closeOnEscape@boolean'] = array(
      '#type' => 'select',
      '#title' => t('Close by escape'),
      '#options' => $boolean,
      '#default_value' => isset($widget['dialog_closeOnEscape@boolean']) ? $widget['dialog_closeOnEscape@boolean'] : 0,
      '#description' => t('Specify if the dialog can be closed when pressing the escape (Esc) button'),
    );

    $form['dialog']['effects'] = array(
      '#type' => 'fieldset',
      '#title' => t('Effects'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );


    //effets on dialog open and close
    $effects = array(
      'null'  => t('None'),
      'slide' => t('Slide'),
    );

    $form['dialog']['effects']['dialog_show'] = array(
      '#type' => 'select',
      '#title' => t('Show effect'),
      '#options' => $effects,
      '#default_value' => isset($widget['dialog_show']) ? $widget['dialog_show'] : 'null',
      '#description' => t('Specify the effect when the dialog window opens.'),
    );

    $form['dialog']['effects']['dialog_hide'] = array(
      '#type' => 'select',
      '#title' => t('Close effect'),
      '#options' => $effects,
      '#default_value' => isset($widget['dialog_hide']) ? $widget['dialog_hide'] : 'null',
      '#description' => t('Specify the effect when the dialog window closes.'),
    );    
    return $form;
  }
}

/**
 * Implementation of hook_widget_settings_validate(). Verifies a form submit
 * @param $widget
 */
function nodereference_explorer_widget_settings_validate($widget) {
  //autocomplete validation
  $field = _nodereference_explorer_widget_settings_get_content_field($widget);
  if ($field) {
    $plugin = nodereference_explorer_plugins_load_plugin($field['type']);
    if (isset($plugin))
      $plugin->widget_settings_validate($widget);

    nodereference_explorer_include('nodereference_explorer.widget.validate');

    //validate dimensions (mandatory)
    nodereference_explorer_widget_validate_textfield_number($widget, 'dialog_height@int', 'Height', TRUE);
    nodereference_explorer_widget_validate_textfield_number($widget, 'dialog_width@int', 'Width', TRUE);

    //validate optional dimensions
    nodereference_explorer_widget_validate_textfield_number($widget, 'dialog_minHeight@int', 'Minimum height', FALSE);
    nodereference_explorer_widget_validate_textfield_number($widget, 'dialog_minWidth@int', 'Minimum width', FALSE);
    nodereference_explorer_widget_validate_textfield_number($widget, 'dialog_maxHeight@int', 'Maximum height', FALSE);
    nodereference_explorer_widget_validate_textfield_number($widget, 'dialog_maxWidth@int', 'Maximum width', FALSE);
    // nodereference_explorer_widget_validate_theme_file($widget, 'theme_css');
  }
}

/**
 * Implementation of hook_widget_settings_save(). Determines which fields to save to
 * the database.
 * @param $widget
 */
function nodereference_explorer_widget_settings_save($widget) {

  $field = _nodereference_explorer_widget_settings_get_content_field($widget);
  if ($field) {
    $plugin = nodereference_explorer_plugins_load_plugin($field['type']);
  	if (isset($plugin))
      $save = $plugin->widget_settings_save($widget); //get additional plugin settings
  	else {
      $save = array();
    }

    return array_merge(
      $save,
      array(
        'content_preview',
        'content_preview_position',
        'dialog_title',
        'theme_css',
        'dialog_api',
        'dialog_dialogClass',
        'dialog_bgiframe@boolean',
        'dialog_width@int',
        'dialog_height@int',
        'dialog_position',
        'dialog_minWidth@int',
        'dialog_minHeight@int',
        'dialog_maxWidth@int',
        'dialog_maxHeight@int',
        'dialog_draggable@boolean',
        'dialog_resizable@boolean',
        'dialog_show',
        'dialog_hide',
        'actions_ok',
        'actions_cancel',
      )
    );
  }
}

/**
 * Retrieve the current field from the URL.
 * This method currently tries different approaches to get
 * the correct field name.
 * TODO: find a clean way to retrieve the field name.
 * @return
 *   CCK field
 */
function _nodereference_explorer_widget_settings_get_content_field($widget) {

  //1. get field name from widget settings
  if (isset($widget['field_name'])) {
    return content_fields($widget['field_name']);
  }

  //2. get field name from error element
  if (isset($widget['default_value'][0]['_error_element'])) {
    $error_element = $widget['default_value'][0]['_error_element'];
    $parts = explode('][', $error_element);
    $field_name = $parts[1];
    if (isset($field_name))
      return content_fields($field_name);
  }

  //3. look up url
  $url = $_GET['q']; //look up url
  $delimit = strrpos($url, '/'); //find last slash
  $field_name = substr($url, $delimit + 1); //last path is field name
  return content_fields($field_name);
}