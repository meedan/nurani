<?php
/**
 * @file
 * nodereference_explorer.views.inc
 * Views related hooks.
 * It contains currently the views plugin style and
 * row definition, as well a the default view responsible
 * for the referenced content types option of the
 * nodereference module.
 */

/**
 * Implementation of hook_views_plugin().
 * Definition of style and row plugins for views
 */
function nodereference_explorer_views_plugins() {
  return array(
    'style' => array( //declare the views_json style plugin
      'table_selectable' => array(
        'path' => drupal_get_path('module', 'views') . '/plugins',
        'title' => t('Table (Selectable)'),
        'theme' => 'views_view_table',
        'theme path' => drupal_get_path('module', 'views') . '/theme',
        'theme file' => 'theme.inc',
        'help' => t('Displays and wraps a table with selectable rows.'),
        'handler' => 'views_plugin_style_table',
        'uses row plugin' => FALSE,
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
      ),
    ),
    'row' => array( //declare the unformatted row plugin
      'fields_selectable' => array(
        'path' => drupal_get_path('module', 'views') . '/plugins',
        'title' => t('Fields (Selectable)'),
        'help' => t('(Displays and wraps each field in a selectable row.'),
        'handler' => 'views_plugin_row_fields',
        'theme' => 'nodereference_explorer_view_row_fields_selectable',
        'theme path' => NODE_REFERENCE_EXPLORER_MODULE_PATH . '/theme',
        'theme file' => 'theme.inc',
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
      ),
    )
  );
}

/**
 * Implementation of hook_views_pre_execute()
 * 
 * Views doesn't support multiple arguments for strings, e. g. node type, yet.
 * Therefore we have to rewrite the query in order to support the selection
 * of multiple content types of a nodereference (default view).
 **/
function nodereference_explorer_views_pre_execute(&$view) {
  switch($view->name) { 
    // If it's the default nre view
    case NODE_REFERENCE_EXPLORER_DEFAULT_VIEW_NAME: 
    	
      //check if there are multiple arguments for node.type and rewrite query with IN instead
      //first argument must be node type
      $type = $view->args[0];
      // in case HTML escaping has happened before
      $type = htmlspecialchars_decode($type, ENT_QUOTES);
      // Multiple node type arguments come like 'page','story'.
      // We have to do some placeholder replacements here as we want to prevent SQL injections
      if (stristr($type, ',') ||
          stristr($type, '+')) { 
        $args = explode("','", trim($type, "'")); // get arguments without quotes
        // generate string placeholders and alter the node type where clause
        $placeholders = implode("', '", array_fill(0, sizeof($args), '%s')); 
        $where = "node.type IN ('" . $placeholders . "')";
        // replace placeholders with real arguments
        _db_query_callback($args, TRUE);
        $where = preg_replace_callback(DB_QUERY_REGEXP, '_db_query_callback', $where);
        // alter the views queries
        $view->build_info['query'] = str_ireplace("node.type = '%s'", $where, $view->build_info['query']);
        $view->build_info['count_query'] = str_ireplace("node.type = '%s'", $where, $view->build_info['count_query']);
      }
  } 
}

/**
 * Implementation of hook_views_pre_render().
 * 
 * This hook is called before the rendering process. In this context
 * it has the task to assign a unique view dom id which is needed for
 * Ajax views. View operations, e. g. filtering or sorting, replace
 * the view's html snippet.
 */
function nodereference_explorer_views_pre_render(&$view) {
  if ($view->use_ajax || ($view->display_handler && $view->display_handler->options['defaults']['use_ajax'])) {
    //If dom_id property is already set, use it as identifier
    if (!empty($view->dom_id)) { 
      return;
    }
    //It allows clients to set the dom_id per request as they may bypass the views_ajax() function
    //with a custom menu call back and the invokation of views_embed_view(). It is needed when
    //the same display is rendered mulitple times on a common HTML page by separate requests. 
    //Clients are supposed to look up the view_dom_id entry the Drupal.settings.views.AjaxViews
    //array and calculate a unique id by themselves.
    elseif (isset($_REQUEST['view_dom_id'])) { 
      $view->dom_id = $_REQUEST['view_dom_id'];
    }
    //It provides a unique identifier per request. It is needed when the same view display is rendered
    //multiple times on a common HTML page within the same request. The ID is determined by the view's 
    //name, display name and an incremential counter. It also prevents ID clashing if different view 
    //displays are rendered by separate requests. This wouldn't be avoided by an incremental counter only.
    else {
      static $dom_ids = array(); //store dom ids within one request
      $counter = 0;
      do {
        //dom id, e. g. view-display-1
        $unique_dom_id = form_clean_id($view->name . '-' . $view->current_display . '-' . ++$counter);
        //check if dom ids already exists, otherwise increment counter with next loop iteration
        if (!in_array($unique_dom_id, $dom_ids)) { 
      	  $dom_ids[] = $unique_dom_id;
      	  $view->dom_id = $unique_dom_id;
      	  return;
        }
      } while ($counter <= count($dom_ids));
      //shouldn't happen, but just in case
      $view->dom_id = form_clean_id($view->name . '-' . $view->current_display . '-' . ++$counter);
    }
  }
}


/**
 * Wrap views table plugin rows into selectable ones.
 * Preprocess hook is called before view is rendered
 * @param $vars
 * 	theming variables
 */
function nodereference_explorer_preprocess_views_view_table(&$vars) {
  if ($vars['view']->display_handler->options['style_plugin'] == 'table_selectable' ||
      $vars['view']->display_handler->view->plugin_name == 'table_selectable') {
    foreach ($vars['rows'] as $id => &$row) {
      $vars['row_classes'][$id][] = 'views-item-selectable';
      //get node id for each row, retrieve from result if nid is hidden
      $nid = isset($vars['view']->result[$id]->nid) ? $vars['view']->result[$id]->nid : strip_tags($row['nid']);      
      $title = isset($vars['view']->result[$id]->node_title) ? $vars['view']->result[$id]->node_title : strip_tags($row['title']);
      $element = array( //wrap id table fields with radio buttons
        '#type' => 'radio',
        '#id' => 'nodereference-explorer-row-'. $id,
        '#name' => 'nodereference-explorer-row',
        '#return_value' => "$title [nid:$nid]",
      );
      $row['nid'] .= drupal_render($element);
    }
  }
}

/**
 * Implementation of hook_views_default_views().
 *
 * Default view used when referencing content types. Instead of accessing
 * the database directly, this view is assigned to do the work now. Additionally
 * any views can be placed here which are exported (better performance and versioning).
 * @return default views
 */
function nodereference_explorer_views_default_views() {
  
  nodereference_explorer_include('nodereference_explorer.util'); // for node types
  
  $views = array();
    
  /*
   * View 'nodereference_explorer_default'
   */
  $view = new view();
  $view->name = 'nodereference_explorer_default';
  $view->description = 'Generic nodereference explorer view including three default displays (table, thumbnails and list)';
  $view->tag = 'nodereference_explorer';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  //default display
  $handler = $view->new_display('default', 'Defaults', 'default');
  
  //set default fields for the view
  $handler->override_option('fields', array(
    'nid' => array(
      'label' => 'Node Id',
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'nid',
      'table' => 'node',
      'field' => 'nid',
      'relationship' => 'none',
    ),
    'title' => array(
      'label' => 'Title',
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
    ),
    'type' => array(
      'label' => 'Type',
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
    ),
    'changed' => array(
      'label' => 'Last changed date',
      'date_format' => 'small',
      'custom_date_format' => '',
      'exclude' => 0,
      'id' => 'changed',
      'table' => 'node',
      'field' => 'changed',
      'relationship' => 'none',
    ),
    'name' => array(
      'label' => 'User',
      'id' => 'name',
      'table' => 'users',
      'field' => 'name',
    ),
    'status' => array(
      'label' => 'Published',
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
    ),
  ));
  $handler->override_option('sorts', array(
    'changed' => array(
      'order' => 'DESC',
      'granularity' => 'second',
      'id' => 'changed',
      'table' => 'node',
      'field' => 'changed',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('arguments', array(
    'type' => array(
      'default_action' => 'ignore',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '',
      'breadcrumb' => '',
      'default_argument_type' => 'fixed',
      'default_argument' => '',
      'validate_type' => 'none',
      'validate_fail' => 'not found',
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(),
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(),
      'validate_argument_type' => 'tid',
      'validate_argument_transform' => 0,
      'validate_user_restrict_roles' => 0,
      'validate_argument_php' => '',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'none',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('header_format', '1');
  $handler->override_option('header_empty', 0);
  $handler->override_option('use_ajax', TRUE);
  $handler->override_option('items_per_page', 6);
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_plugin', 'table_selectable');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 1,
    'order' => 'desc',
    'columns' => array(
      'nid' => 'nid',
      'title' => 'title',
      'type' => 'type',
      'changed' => 'changed',
      'name' => 'name',
      'status' => 'status',
    ),
    'info' => array(
      'nid' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'title' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'type' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'changed' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'name' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'status' => array(
        'sortable' => 1,
        'separator' => '',
      ),
    ),
    'default' => 'changed',
  ));
  $handler->override_option('exposed_block', TRUE);
  $handler = $view->new_display('page', 'Table', 'table');
  $handler->override_option('filters', array(
    'title' => array(
      'operator' => 'contains',
      'value' => '',
      'group' => '0',
      'exposed' => TRUE,
      'expose' => array(
        'use_operator' => 0,
        'operator' => 'title_op',
        'identifier' => 'title',
        'label' => 'Title',
        'optional' => 1,
        'remember' => 0,
      ),
      'case' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'body' => array(
      'operator' => 'contains',
      'value' => '',
      'group' => '0',
      'exposed' => TRUE,
      'expose' => array(
        'use_operator' => 0,
        'operator' => 'body_op',
        'identifier' => 'body',
        'label' => 'Body',
        'optional' => 1,
        'remember' => 0,
      ),
      'case' => 0,
      'id' => 'body',
      'table' => 'node_revisions',
      'field' => 'body',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'type' => array(
      'operator' => 'in',
      //set all node types as default, underlying nodereference field has to care about narrowing filter options
      'value' => nodereference_explorer_util_get_all_referenceable_node_types(),
      'group' => '0',
      'exposed' => TRUE,
      'expose' => array(
        'use_operator' => 0,
        'operator' => 'type_op',
        'identifier' => 'type',
        'label' => 'Type',
        'bef_filter_description' => '',
        'bef_format' => 'default',
        'optional' => 1,
        'single' => 1,
        'remember' => 0,
        'reduce' => 1,
        'bef_select_all_none' => 0,
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'status' => array(
      'operator' => '=',
      'value' => 'All',
      'group' => '0',
      'exposed' => TRUE,
      'expose' => array(
        'operator' => '',
        'identifier' => 'status',
        'label' => 'Published',
        'bef_filter_description' => '',
        'bef_format' => 'default',
        'optional' => 1,
        'remember' => 0,
        'bef_select_all_none' => 0,
      ),
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
  ));
  $handler->override_option('path', 'nodereference_explorer/menu_display_table');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler = $view->new_display('page', 'Grid', 'grid');
  $handler->override_option('filters', array(
    'title' => array(
      'operator' => 'contains',
      'value' => '',
      'group' => '0',
      'exposed' => TRUE,
      'expose' => array(
        'use_operator' => 0,
        'operator' => 'title_op',
        'identifier' => 'title',
        'label' => 'Title',
        'optional' => 1,
        'remember' => 0,
      ),
      'case' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'body' => array(
      'operator' => 'contains',
      'value' => '',
      'group' => '0',
      'exposed' => TRUE,
      'expose' => array(
        'use_operator' => 0,
        'operator' => 'body_op',
        'identifier' => 'body',
        'label' => 'Body',
        'optional' => 1,
        'remember' => 0,
      ),
      'case' => 0,
      'id' => 'body',
      'table' => 'node_revisions',
      'field' => 'body',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'type' => array(
      'operator' => 'in',
      // set all node types as default, underlying nodereference field has to care about narrowing filter options
      'value' => nodereference_explorer_util_get_all_referenceable_node_types(),
      'group' => '0',
      'exposed' => TRUE,
      'expose' => array(
        'use_operator' => 0,
        'operator' => 'type_op',
        'identifier' => 'type',
        'label' => 'Type',
        'bef_filter_description' => '',
        'bef_format' => 'default',
        'optional' => 1,
        'single' => 1,
        'remember' => 0,
        'reduce' => 1,
        'bef_select_all_none' => 0,
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'status' => array(
      'operator' => '=',
      'value' => 'All',
      'group' => '0',
      'exposed' => TRUE,
      'expose' => array(
        'operator' => '',
        'identifier' => 'status',
        'label' => 'Published',
        'bef_filter_description' => '',
        'bef_format' => 'default',
        'optional' => 1,
        'remember' => 0,
        'bef_select_all_none' => 0,
      ),
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
  ));
  $handler->override_option('style_plugin', 'grid');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'columns' => '6',
    'alignment' => 'horizontal',
  ));
  $handler->override_option('row_plugin', 'fields_selectable');
  $handler->override_option('row_options', array(
    'inline' => array(),
    'separator' => '',
  ));
  $handler->override_option('path', 'nodereference_explorer/menu_display_thumbnail');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler = $view->new_display('page', 'List', 'list');
  $handler->override_option('filters', array(
    'title' => array(
      'operator' => 'contains',
      'value' => '',
      'group' => '0',
      'exposed' => TRUE,
      'expose' => array(
        'use_operator' => 0,
        'operator' => 'title_op',
        'identifier' => 'title',
        'label' => 'Title',
        'optional' => 1,
        'remember' => 0,
      ),
      'case' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'body' => array(
      'operator' => 'contains',
      'value' => '',
      'group' => '0',
      'exposed' => TRUE,
      'expose' => array(
        'use_operator' => 0,
        'operator' => 'body_op',
        'identifier' => 'body',
        'label' => 'Body',
        'optional' => 1,
        'remember' => 0,
      ),
      'case' => 0,
      'id' => 'body',
      'table' => 'node_revisions',
      'field' => 'body',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'type' => array(
      'operator' => 'in',
      //set all node types as default, underlying nodereference field has to care about narrowing filter options
      'value' => nodereference_explorer_util_get_all_referenceable_node_types(),
      'group' => '0',
      'exposed' => TRUE,
      'expose' => array(
        'use_operator' => 0,
        'operator' => 'type_op',
        'identifier' => 'type',
        'label' => 'Type',
        'bef_filter_description' => '',
        'bef_format' => 'default',
        'optional' => 1,
        'single' => 1,
        'remember' => 0,
        'reduce' => 1,
        'bef_select_all_none' => 0,
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'status' => array(
      'operator' => '=',
      'value' => 'All',
      'group' => '0',
      'exposed' => TRUE,
      'expose' => array(
        'operator' => '',
        'identifier' => 'status',
        'label' => 'Published',
        'bef_filter_description' => '',
        'bef_format' => 'default',
        'optional' => 1,
        'remember' => 0,
        'bef_select_all_none' => 0,
      ),
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
  ));
  $handler->override_option('style_plugin', 'list');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'type' => 'ul',
  ));
  $handler->override_option('row_plugin', 'fields_selectable');
  $handler->override_option('row_options', array(
    'inline' => array(
      'nid' => 'nid',
      'title' => 'title',
      'type' => 'type',
      'changed' => 'changed',
      'name' => 'name',
      'status' => 'status',
    ),
    'separator' => '',
  ));
  $handler->override_option('path', 'nodereference_explorer/menu_display_list');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler = $view->new_display('page', 'Preview', 'preview');
  $handler->override_option('arguments', array(
    'nid' => array(
      'default_action' => 'empty',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '',
      'breadcrumb' => '',
      'default_argument_type' => 'fixed',
      'default_argument' => '',
      'validate_type' => 'none',
      'validate_fail' => 'not found',
      'break_phrase' => 0,
      'not' => 0,
      'id' => 'nid',
      'table' => 'node',
      'field' => 'nid',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(),
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(),
      'validate_argument_type' => 'tid',
      'validate_argument_transform' => 0,
      'validate_user_restrict_roles' => 0,
      'validate_argument_php' => '',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
  ));
  $handler->override_option('style_plugin', 'default');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'columns' => '6',
    'alignment' => 'horizontal',
  ));
  $handler->override_option('row_options', array(
    'inline' => array(),
    'separator' => '',
  ));
  $handler->override_option('path', 'nodereference_explorer/menu_display_preview');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));

  $views[$view->name] = $view;
  return $views;
}