<?php

class views_bulk_operations_plugin_style extends views_plugin_style_table {

  var $all_operations = array();

  /**
   * Implementation of views_plugin::init().
   */
  function init(&$view, &$display, $options = NULL) {
    parent::init($view, $display, $options);

    $this->populate_operations();
  }

  /**
   * Implementation of views_plugin::option_definition().
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['operations'] = array('default' => array());
    $options['execution_type'] = array('default' => VBO_EXECUTION_DIRECT);
    $options['display_type'] = array('default' => 0);
    $options['display_result'] = array('default' => TRUE);
    $options['merge_single_action'] = array('default' => TRUE);
    $options['hide_selector'] = array('default' => FALSE);
    $options['preserve_selection'] = array('default' => TRUE);

    return $options; 
  }

  /**
   * Implementation of views_plugin::options_form().
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    
    $execution = array(
      VBO_EXECUTION_DIRECT => t('Invoke them directly'),
      VBO_EXECUTION_BATCH => t('Use Batch API'),
    );
    if (module_exists('job_queue')) {
      $execution[VBO_EXECUTION_QUEUE] = t('Use <a href="@jobqueue">Job Queue</a>', array('@jobqueue' => url('http://drupal.org/project/job_queue'))); 
    }
    $form['execution_type'] = array(
      '#type' => 'radios',
      '#title' => t('To execute operations'),
      '#default_value' => $this->options['execution_type'],
      '#options' => $execution,
    );
    $form['display_type'] = array(
      '#type' => 'radios',
      '#title' => t('Display operations as'),
      '#default_value' => $this->options['display_type'],
      '#options' => array(
        t('Dropdown selectbox with Submit button'),
        t('Each action as a separate button'),
      ),
    );
    $form['hide_selector'] = array(
      '#type' => 'checkbox',
      '#title' => t('Hide selector dropdown'),
      '#description' => t('Check this box to hide the selector dropdown.'),
      '#default_value' => $this->options['hide_selector'],
    );
    $form['preserve_selection'] = array(
      '#type' => 'checkbox',
      '#title' => t('Preserve selection across pages'),
      '#description' => t('Check this box to preserve item selection across multiple pages. Requires JavaScript.'),
      '#default_value' => $this->options['preserve_selection'],
    );
    $form['display_result'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display processing result'),
      '#description' => t('Check this box to let Drupal display a message with the result of processing the selected objects.'),
      '#default_value' => $this->options['display_result'],
    );
    $form['merge_single_action'] = array(
      '#type' => 'checkbox',
      '#title' => t('Merge single action\'s form with item selection view'),
      '#description' => t('In case only one action is selected *and* this action is configurable, display its action form along with the item selection view.'),
      '#default_value' => $this->options['merge_single_action'],
    );

    // Display operations and their settings.
    $form['operations'] = array(
      '#tree' => TRUE,
      '#type' => 'fieldset',
      '#title' => t('Selected operations'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    foreach ($this->get_operations_options() as $key => $label) {
      $dom_id = 'edit-style-options-operations-' . str_replace('_', '-', $key) . '-selected';
      $form['operations'][$key]['selected'] = array(
        '#type' => 'checkbox',
        '#title' => $label,
        '#default_value' => @$this->options['operations'][$key]['selected'],
      );
      $form['operations'][$key]['skip_confirmation'] = array(
        '#type' => 'checkbox',
        '#title' => t('Skip confirmation step'),
        '#default_value' => @$this->options['operations'][$key]['skip_confirmation'],
        '#process' => array('views_process_dependency'),
        '#dependency' => array(
          $dom_id => array(1),
        ),
      );
      $form['operations'][$key]['label'] = array(
        '#type' => 'textfield',
        '#title' => t('Override label'),
        '#default_value' => @$this->options['operations'][$key]['label'],
        '#process' => array('views_process_dependency'),
        '#dependency' => array(
          $dom_id => array(1),
        ),
      );
      $form_function = $this->all_operations[$key]['callback'] . '_views_bulk_operations_form';
      if (function_exists($form_function)) {
        $form_settings = call_user_func($form_function, @$this->options['operations'][$key]['settings']);
        foreach (element_children($form_settings) as $child) {
          $form_settings[$child] += array(
            '#process' => array('views_process_dependency'),
            '#dependency' => array(
              $dom_id => array(1),
            ),
          );
        }
        $form['operations'][$key]['settings'] = $form_settings;
      }
    }
  }

  /**
   * Implementation of views_plugin::options_validate().
   */
  function options_validate(&$form, &$form_state) {
    foreach ($form_state['values']['style_options']['operations'] as $key => &$options) {
      if (empty($options['selected'])) continue;
      if (!isset($options['settings'])) continue;
      $operation = $this->all_operations[$key];
      $form_function = $operation['callback'] . '_views_bulk_operations_form_validate';
      if (function_exists($form_function)) {
        $options['settings']['_error_element_base'] = 'style_options][operations][' . $key . '][settings][';
        call_user_func($form_function, $form, array('values' => $options['settings']));
      }
    }
  }

  /**
   * Implementation of views_plugin::options_submit().
   */
  function options_submit(&$form, &$form_state) {
    foreach ($form_state['values']['style_options']['operations'] as $key => $options) {
      if (empty($options['selected'])) continue;
      if (!isset($options['settings'])) continue;
      $operation = $this->all_operations[$key];
      $form_function = $operation['callback'] . '_views_bulk_operations_form_submit';
      if (function_exists($form_function)) {
        call_user_func($form_function, $form, array('values' => $options['settings']));
      }
    }
  }

  /**
   * Implementation of hook_views_pre_execute().
   */
  function pre_execute() {
    // If preserving selection across pages, reset the pager.
    if ($this->options['preserve_selection'] || !$this->options['hide_selector']) {
      $this->pager = new views_bulk_operations_pager_helper($this->view);
    }
  }

  /**
   * Implementation of hook_views_post_execute().
   */
  function post_execute() {
    // Store the results with their signature.
    foreach ($this->view->result as $result) {
      $this->result[md5(serialize($result))] = $result;
    }
    // Restore the pager to its original settings.
    if (!empty($this->pager)) {
      $this->pager->slice();
    }
    // Signal that we did this already.
    $this->post_executed = TRUE;
  }

  /**
   * Implementation of views_plugin::pre_render().
   */
  function pre_render($result) {
    // Check that post_execute wasn't called, which is the case for earlier versions of Views 2.
    if (empty($this->post_executed)) {
      $this->post_execute();
    }
  }

  /**
   * Implementation of views_plugin::render().
   */
  function render() {
    // We build the groups here to pass them to the node_selector function through the form.
    $sets = $this->render_grouping($this->view->result, $this->options['grouping']);
    $this->sets = $sets;

    // Append suffix to avoid clashing between multiple VBOs on same page.
    static $form_suffix;
    if (isset($form_suffix)) {
      $form_suffix++;
    }
    else {
      $form_suffix = 1;
    }
    return drupal_get_form('views_bulk_operations_form__' . $form_suffix, $this);
  }

  /**
   * API function to get list of selected operations.
   */
  function get_selected_operations() {
    $selected = array();
    foreach ($this->options['operations'] as $key => $options) {
      if (empty($options['selected'])) continue;
      if (empty($this->all_operations[$key])) continue;
      if (module_exists('actions_permissions')) {
        $perm = actions_permissions_get_perm($this->all_operations[$key]['label'], $this->all_operations[$key]['callback']);
        if (!user_access($perm)) continue;
      }
      if (!empty($this->all_operations[$key]['permissions'])) foreach ($this->all_operations[$key]['permissions'] as $perm) {
        if (!user_access($perm)) continue 2;
      }
      $selected[$key] = !empty($this->options['operations'][$key]['label']) ? t($this->options['operations'][$key]['label']) : $this->all_operations[$key]['label'];
    }
    return $selected;
  }

  /**
   * API function to get operation information.
   */
  function get_operation_info($key) {
    if (empty($this->all_operations[$key])) {
      return NULL;
    }
    $operation = $this->all_operations[$key];
    $operation['perm label'] = $operation['label'];
    if (!empty($this->options['operations'][$key]['label'])) {
      $operation['label'] = t($this->options['operations'][$key]['label']);
    }
    $operation['options'] = $this->options['operations'][$key] + array('settings' => NULL);
    return $operation;
  }

  /**
   * API function to strip view of additional components.
   */
  function strip_view() {
    if (isset($this->view->query->pager)) {
      $this->view->pager_original = $this->view->query->pager;
      $this->view->query->pager = NULL;
    }
    else {
      $this->view->pager_original = $this->view->pager;
      $this->view->set_use_pager(FALSE);
    }
    $this->view->exposed_widgets = NULL;
    $this->view->display_handler->set_option('header', '');
    $this->view->display_handler->set_option('footer', '');
    $this->view->display_handler->set_option('use_pager', FALSE);
    $this->view->attachment_before = '';
    $this->view->attachment_after = '';
    $this->view->feed_icon = NULL;
  }

  private function get_operations_options() {
    static $options = array();
    if (empty($options)) {
      $object_info = _views_bulk_operations_object_info_for_view($this->view);
      if (!$object_info) return $options;
      foreach ($this->all_operations as $key => $operation) {
        if ($operation['type'] == $object_info['type'] || $operation['type'] == 'system' || in_array($object_info['hook'], (array) $operation['hooks'])) {
          $options[$key] = $operation['label'] .' ('. $key .')'; 
        }
      }
    }
    return $options;
  }

  private function populate_operations() {
    module_load_include('inc', 'node', 'node.admin');

    $operations = array();
    foreach (_views_bulk_operations_get_object_info() as $object_type => $object_info) {
      $hook_name = $object_type .'_operations';
      foreach (module_invoke_all($hook_name) as $operation) {
        if (empty($operation['callback'])) continue;
        $key = $operation['callback'] . (empty($operation['callback arguments']) ? '' : '-'. md5(serialize($operation['callback arguments'])));
        if (!isset($operation['behavior'])) { // assume operations modify nodes by default
          $operation['behavior'] = array('changes_node_property');
        }
        $operations[$key] = array(
          'key'                 => $key,
          'label'               => $operation['label'],
          'callback'            => $operation['callback'],
          'callback arguments'  => isset($operation['callback arguments']) ? $operation['callback arguments'] : array(),
          'configurable'        => isset($operation['configurable']) ? $operation['configurable'] : FALSE,
          'form properties'     => isset($operation['form properties']) ? $operation['form properties'] : array(),
          'source'              => 'operation',
          'type'                => $object_type,
          'aggregate'           => isset($operation['aggregate']) ? (int)$operation['aggregate'] : VBO_AGGREGATE_OPTIONAL,
          'access op'           => $this->get_access_op($operation),
          'permissions'         => isset($operation['permissions']) ? $operation['permissions'] : NULL,
          'hooks'               => array(),
        );
      }
    }

    $action_operations = actions_list() + $this->get_custom_actions();
    foreach ($action_operations as $callback => $operation) {
      $key = isset($operation['key']) ? $operation['key'] : $callback;
      $operations[$key] = array(
        'key'                   => $key,
        'label'                 => $operation['description'],
        'callback'              => isset($operation['callback']) ? $operation['callback'] : $callback,
        'callback arguments'    => isset($operation['parameters']) ? $operation['parameters'] : array(),
        'configurable'          => isset($operation['configurable']) ? $operation['configurable'] : FALSE,
        'form properties'       => isset($operation['form properties']) ? $operation['form properties'] : array(),
        'source'                => 'action',
        'type'                  => $operation['type'],
        'aggregate'             => isset($operation['aggregate']) ? (int)$operation['aggregate'] : VBO_AGGREGATE_FORBIDDEN,
        'access op'             => $this->get_access_op($operation),
        'permissions'           => isset($operation['permissions']) ? $operation['permissions'] : NULL,
        'hooks'                 => isset($operation['hooks']) ? array_keys((array) $operation['hooks']) : array(),
      );
    }

    uasort($operations, create_function('$a, $b', 'return strcasecmp($a["label"], $b["label"]);'));
    $this->all_operations = $operations;
  }

  private function get_access_op($operation) {
    $access_op = 0;
    if (isset($operation['behavior'])) {
      if (in_array('views_node_property', $operation['behavior'])) {
        $access_op |= VBO_ACCESS_OP_VIEW;
      }
      if (in_array('changes_node_property', $operation['behavior'])) {
        $access_op |= VBO_ACCESS_OP_UPDATE;
      }
      if (in_array('creates_node_property', $operation['behavior'])) {
        $access_op |= VBO_ACCESS_OP_CREATE;
      }
      if (in_array('deletes_node_property', $operation['behavior'])) {
        $access_op |= VBO_ACCESS_OP_DELETE;
      }
    }
    return $access_op;
  }

  private function get_custom_actions() {
    $actions = array();
    $static_actions = actions_list();
    $result = db_query("SELECT * FROM {actions} WHERE parameters > ''");
    while ($action = db_fetch_object($result)) {
      $parameters = unserialize($action->parameters);
      $actions[$action->aid] = array(
        'description' => $action->description,
        'type' => $action->type,
        'configurable' => FALSE,
        'parameters' => $parameters,
        'key' => $action->callback . (empty($parameters) ? '' : '-'. md5($action->parameters)),
      );
      foreach (array('callback', 'behavior', 'aggregate', 'permissions', 'hooks', 'form properties') as $attribute) {
        if (isset($static_actions[$action->callback][$attribute])) $actions[$action->aid][$attribute] = $static_actions[$action->callback][$attribute];
      }
      if (isset($static_actions[$action->callback['parameters']])) {
        $actions[$action->aid]['parameters'] = array_merge($actions[$action->aid]['parameters'], $static_actions[$action->callback]['parameters']);
      }
    }
    return $actions;
  }
}

/**
 * Helper class to deal with pager differences between Views 2 and 3.
 */
class views_bulk_operations_pager_helper {

  function __construct($view) {
    $this->view = $view;
    if (version_compare(views_api_version(), '3', '<')) { // Views 2
      $this->pager = $this->view->pager;
      $this->view->set_items_per_page(0);
    }
    else { // Views 3
      $this->pager = array(
        'limit' => $this->view->query->limit,
        'offset' => $this->view->query->offset,
        'use_pager' => TRUE,
      );
      $this->view->query->set_limit(0);
      $this->view->query->set_offset(0);
    }
  }

  function slice() {
    if (isset($this->pager) && $this->pager['use_pager']) {
      if (version_compare(views_api_version(), '3', '<')) { // Views 2
        $this->view->pager = $this->pager;
        if (method_exists($this->view, 'synchronize_pager')) {
          $this->view->synchronize_pager();
        }
        else {
          $this->synchronize();
        }
        $offset = $this->view->pager['current_page'] * $this->view->pager['items_per_page'] + $this->view->pager['offset'];
        $limit = $this->view->pager['items_per_page'];
      }
      else { // Views 3
        $offset = $this->pager['offset'];
        $limit = $this->pager['limit'];
        $this->view->query->set_limit($limit);
        $this->view->query->set_offset($offset);
      }
      $results = array_slice($this->view->result, $offset, $limit);
      $this->view->result = $results;
    }
  }

  function synchronize() {
    if (!empty($this->view->pager['use_pager'])) {
    // dump information about what we already know into the globals
      global $pager_page_array, $pager_total, $pager_total_items;
      // total rows in query
      $pager_total_items[$this->view->pager['element']] = $this->view->total_rows;
      // total pages
      $pager_total[$this->view->pager['element']] = ceil($pager_total_items[$this->view->pager['element']] / $this->view->pager['items_per_page']);

      // What page was requested:
      $pager_page_array = isset($_GET['page']) ? explode(',', $_GET['page']) : array();

      // If the requested page was within range. $this->pager['current_page']
      // defaults to 0 so we don't need to set it in an out-of-range condition.
      if (!empty($pager_page_array[$this->view->pager['element']])) {
        $page = intval($pager_page_array[$this->view->pager['element']]);
        if ($page > 0 && $page < $pager_total[$this->view->pager['element']]) {
          $this->view->pager['current_page'] = $page;
        }
      }
      $pager_page_array[$this->view->pager['element']] = $this->view->pager['current_page'];
    }
  }
}

