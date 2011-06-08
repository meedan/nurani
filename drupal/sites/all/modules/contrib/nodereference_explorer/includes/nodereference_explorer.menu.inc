<?php
/**
 * @file
 * nodereference_explorer.menu.inc
 * File containing all menu call backs of
 * the module.
 */

/**
 * Menu call back for showing a view item
 * @param $type_name content type
 * @param $field_name label of the CCK field
 * @param $index ascending number of widget (needed for multiple value per widget)
 * @return rendered view item
 */
function nodereference_explorer_preview($type_name, $field_name) {
  if (!empty($_GET['val'])) {
    preg_match('/^(?:\s*|(.*) )?\[\s*nid\s*:\s*(\d+)\s*\]$/', $_GET['val'], $matches);
    if (!empty($matches)) {
      // Explicit [nid:n].
      list(, $title, $nid) = $matches;
    }
  }
  //retrieve the field by name and content type
  $field = content_fields($field_name, $type_name);

  //get the selected rendered view item
  nodereference_explorer_include('nodereference_explorer.views.class');
  $handler = new nodereference_explorer_views($field);
  $output = $handler->get_item($nid);
  drupal_json(array('status' => TRUE, 'data' => $output));
}

/**
 * List of available displays for a preview. This is
 * automatically updated in the settings form.
 * @return
 *   JSON string
 */
function nodereference_explorer_preview_displays() {
  if (!empty($_GET['view'])) {
    $view_name = $_GET['view'];
    if ($view_name == '--')
      $view_name = NODE_REFERENCE_EXPLORER_DEFAULT_VIEW_NAME;
    $view = views_get_view($view_name);
    $preview_options = array();
    $preview_options['--'] = ''; //prepend no preview
    $displays = $view->display;
    foreach ($displays as $id => $display) //build optoins array
      $preview_options[$id] = $display->display_title;
    drupal_json(array('status' => TRUE, 'data' => $preview_options));
  }
}

/**
 * Dialog theme layer.
 * A dialog template is applied which is filled by field and widget
 * settings of a CCK field. Third party CCK fields can hook in here
 * and override/supply custom settings.
 * Necessary JS and CSS files are included in the JSON repsone as well.
 * @param $type_name
 * @param $field_name
 * @param $title
 * @return
 *  json string output of dialog html, as well as js and css references.
 */
function nodereference_explorer_dialog($type_name, $field_name, $title = '') {
  
  //retrieve field by name
  $field = content_fields($field_name, $type_name);
  
  //a CCK field is manadatory, return if nothing present
  if (!$field)
    return '';  
    
  //JSON array to be return message 
  $ret_msg = array('status' => TRUE);
  
  //differ between dialog api and built-in here for delegating
  switch ($field['widget']['dialog_api']) {
    case 'modalframe':
      //Modalframe API first loads the parent window. The content is
      //rendered by the nodereference_explorer_modalframe callback   
      //So, therefore there's nothing to do right now :)
	  break;
    case NODE_REFERENCE_EXPLORER_MODULE_NAME:
    default: //render dialog
      $output = nodereference_explorer_get_overlay_content($field, $title);
      $ret_msg['data'] = $output;
  }
  
  /* TODO the scripts array contains additional settings and scripts that
   * ideally could inform some process of loading and setting those things.
   * instead, we're calling views_add_js('ajax_view') with the element..
   * $scripts = drupal_add_js(NULL);
   */
  nodereference_explorer_include('nodereference_explorer.util');
  $ret_msg['js'] = nodereference_explorer_util_get_js();
   
  //settings needed by javascript, i. e. explorer.actions.js
  $dialog = nodereference_explorer_util_parse_settings($field, 'dialog');
  $ret_msg['js']['setting']['dialog'] = $dialog;
  
  //button labels for dialog
  $ret_msg['js']['setting']['actions'] = nodereference_explorer_get_overlay_actions();

  //dynamically loaded css files
  $ret_msg['css'] = nodereference_explorer_util_get_css();
  
  drupal_json($ret_msg);
}

/**
 * Dialog content containing view displays, filters and tabs.
 * @param $field
 *   CCK content field
 * @param $title
 *   selection value
 * @return
 *   Rendered dialog content (HTML)
 */
function nodereference_explorer_get_overlay_content($field, $title = '') {
  //parse dialog settings
  nodereference_explorer_include('nodereference_explorer.util');
  $dialog = nodereference_explorer_util_parse_settings($field, 'dialog');  

  //fill template for dialog content
  nodereference_explorer_include('nodereference_explorer.views.class');
  $handler = new nodereference_explorer_views($field);
  $handler->set_selection($title);
  $filters = array();
  foreach ($handler->get_all_displays() as $display) {
  	//Render tabs links manually, as their behavior will be defined by jQuery tabs on the client side.
  	//Usage of the l() functions leads to problems as HTTP requests are triggered, e. g.
  	//$tabs[$display->id] = l($display->display_title, $_GET['q'], array('fragment' => $display->id));
    $tabs[$display->id] = "<a href=\"#$display->id\">$display->display_title</a>";
    
    //display filters only separately if they are exposed in a block
    $handler->view->set_display($display->id);
    if ($handler->view->display_handler->get_option('exposed_block'))
      $filters[$display->id] = $handler->get_exposed_form($display->id);
    $displays[$display->id] = $handler->get_display($display->id);
  }
  return theme('nodereference_explorer_dialog', $dialog['title'], $tabs, $filters, $displays);
}

/**
 * Buttons/actions for the dialog
 * @return
 *   array of action labels
 */
function nodereference_explorer_get_overlay_actions() {
 //button labels for dialog
  $actions = array();
  $actions['ok'] = t('OK');
  $actions['cancel'] = t('Cancel');
  return $actions;
}

/**
 * Theme layer for modalframe api.
 * @param $type_name
 * @param $field_name
 */
function nodereference_explorer_modalframe($type_name, $field_name, $title = '') {
	
  //retrieve field by name
  $field = content_fields($field_name, $type_name);
  
  nodereference_explorer_include('nodereference_explorer.util');
  nodereference_explorer_util_explorer_js($field); //common content js
  nodereference_explorer_add_css('explorer.modalframe');
  
  modalframe_child_js(); //window content javascript
  
  $output = nodereference_explorer_get_overlay_content($field);
  
  //add submit buttons of a form outside the dialog, avoiding nested forms when
  //using exposed filters. It would lead to incompatiblity with IE.
  return $output . drupal_get_form('nodereference_explorer_modalframe_form', $title, nodereference_explorer_get_overlay_actions()); //form of internal area
}

/**
 * Content of the modalframe dialog
 * @param $form_state
 * @param $dialog
 * @param $title
 * @return
 *   a form
 */
function nodereference_explorer_modalframe_form($form_state, $title, $actions) {
  $form['selection'] = array(
    '#type' => 'hidden',
    '#default_value' => $title,
  );
  
  foreach ($actions as $key => $action) {
  	$form[$key] = array(
  	  '#type' => 'submit',
  	  '#value' => $action,	
  	);
  }
  return $form;
}

/**
 * Modalframe form submit, i. e. confirmation of the selection
 * @param $form
 * @param $form_state
 */
function nodereference_explorer_modalframe_form_submit($form, $form_state) {
  if ($form_state['clicked_button']['#id'] == 'edit-ok')
    modalframe_close_dialog($form_state['values']); //modalframe is closed
  else {
  	modalframe_close_dialog(); //do not store any selection on abort
  }
}