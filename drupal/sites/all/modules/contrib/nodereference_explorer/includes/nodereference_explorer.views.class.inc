<?php
/**
 * @file
 * nodereference_explorer.views.inc
 * Class responsible for widget and dialog initialization
 */
class nodereference_explorer_views {

  public $view;  //referenced view
  public $view_args; //view arguments
  public $field; //referenced field

  private $selection; // the string that identifies the selection

  /**
   * @return unknown
   */
  public function get_selection() {
    return $this->selection;
  }

  /**
   * @param unknown_type $view_name
   */
  public function set_selection($selection) {
    $this->selection = $selection;
  }

  /**
   * Initialize the handler (ids, options, field)
   * @param $field
   *   cck field
   */
  public function __construct($field) {
    $this->field  = $field;

    //default view
    if (empty($this->field['advanced_view']) || $this->field['advanced_view'] == '--') {
      //pretend the field to be a view (for function _nodereference_potential_references())
      $this->field['advanced_view'] = NODE_REFERENCE_EXPLORER_DEFAULT_VIEW_NAME;

      $this->view = views_get_view(NODE_REFERENCE_EXPLORER_DEFAULT_VIEW_NAME);
    }
    else {
      $this->view = views_get_view($this->field['advanced_view']);
    }

    // Get arguments for the view.
    if (!empty($this->field['advanced_view_args'])) {
      if (!empty($this->view_args)) //append to existing arguments
         $this->view_args .= ',';
      $this->view_args .= $this->field['advanced_view_args'];
    }
  }

  /**
   * Get a specific view item by node ids
   * @param $value node id or form state value of field
   * @return rendered view item
   */
  public function get_item($value) {
    if (is_array($value) && isset($value['nid'])) {
      // taken from nodereference_autocomplete_validate() in nodereference.module
      preg_match('/^(?:\s*|(.*) )?\[\s*nid\s*:\s*(\d+)\s*\]$/', $value['nid'], $matches);
      if (!empty($matches)) {
        // Explicit [nid:n].
        $nid = $matches[2];
      }
    }
    elseif (!is_array($value)) {
      $nid = $value;
    }
    //$match = isset($this->field['widget']['autocomplete_match']) ? $this->field['widget']['autocomplete_match'] : 'contains';
    $output = views_embed_view($this->view->name, $this->field['widget']['content_preview'], $nid);
  if (!is_array($output)) //return rendered output for pages
      return $output;
    else { //if an array then output rendered for blocks
      return $output['content'];
    }
  }

  /**
   * Get a filter form for a display
   * @param $display_id display identifier
   * @return rendered filter form
   */
  public function get_exposed_form($display_id) {
    $view = $this->view->clone_view();
    //force use of Ajax, as otherwise the dialog is redirected to the view page,
    //i. e. breaking the dialog
    if (!$view->use_ajax) {
      $view->use_ajax = TRUE;
    }
    $view->set_display($display_id);
    $view->init_handlers(); //initialize display handlers
    $form_state = array(
      'view' => $view,
      'display' => $view->display_handler->display,
      'exposed_form_plugin' => $view->display_handler->get_plugin('exposed_form'), //exposed form plugins are used in Views 3
      'method' => 'get',
      'rerender' => TRUE,
      'no_redirect' => TRUE,
    );
    $form = drupal_build_form('views_exposed_form', $form_state); //create the filter form
    return $form;
  }

  /**
   * Get all available displays of the assigend
   * view.
   * @return array of display objects
   */
  public function get_all_displays() {
    $displays = $this->view->display;
    
    unset($displays['default']);

    if (!empty($this->field['widget']['content_preview']) && $this->field['widget']['content_preview'] != '--')
      unset($displays[$this->field['widget']['content_preview']]); //hide preview in dialog window
    else {
      unset($displays['preview']);
    }
    return $displays; //get all available displays
  }

  /**
   * Get a display by id.
   * @param $display_id display identifier
   * @return rendered display
   */
  public function get_display($display_id) {
    $view = $this->view->clone_view();
    $view->set_display($display_id); //set display, e. g. thumbnails or table

    $title = drupal_get_title();

    if (!empty($this->view_args)) {//view (default or custom) with arguments
      $args = split(',', $this->view_args); //split multiple arguments by slashes
      //append view's name and display id as arguments 1 and 2
      array_unshift($args, $display_id);
      array_unshift($args, $view->name);
      //call embed view by name
      $output = call_user_func_array('views_embed_view', $args);
    }
    elseif ($view->name == NODE_REFERENCE_EXPLORER_DEFAULT_VIEW_NAME && !empty($this->field['referenceable_types'])) { //no arguments, default view
      $ref_types = array_filter($this->field['referenceable_types'], '_nodereference_explorer_views_is_not_zero');
      $content_types = implode('\',\'', $ref_types); //list content types
      if ($ref_types && count($ref_types) > 1) { //view argument: get multiple content types
      	//render the display, Views query to be rewriten in nodereference_explorer_views_pre_execute()
        $output = views_embed_view($view->name, $display_id, "'$content_types'"); 
      }
      elseif ($content_types) { //view argument: get a single content type
        $output = views_embed_view($view->name, $display_id, $content_types); //render the display
      }
      else { //view argument:  get all content types, e. g. for links, as default view "displays all values"
      	     //if no argument is provided
        $output = views_embed_view($view->name, $display_id); //render the display
      }
    }
    else { //advanced view, no arguments
      $output = views_embed_view($view->name, $display_id); //render the display
    }
    drupal_set_title($title);
    if (!is_array($output)) //return rendered output for pages
      return $output;
    else { //if an array then output rendered for blocks
      return $output['content'];
    }
  }
}

/**
 * Checks whether a certain value is '0'
 * @param $var
 * @return
 *   TRUE if not '0'
 */
function _nodereference_explorer_views_is_not_zero($var) {
   return $var != '0' ? TRUE : FALSE;
 }
