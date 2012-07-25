<?php
// $Id: icl_translate.manager.inc

function icl_translate_manager() {

  // We need the dashboard css to use icl_status class.  
  drupal_add_css(drupal_get_path('module', 'icl_content').'/css/dashboard.css');
  // Add the collapse javascript file for the helper.
  drupal_add_js('misc/collapse.js');
  
  global $base_url;
  $path = $base_url . '/' . drupal_get_path('module', 'icl_core') . '/images/web_logo_medium.png';
  $output = '';
  
  module_load_include('inc', 'system', 'system.admin');
  
  $output .= system_admin_menu_block_page();
	
	$output .= '<br /><hr /><br /><a href="http://www.icanlocalize.com/site/" title="ICanLocalize"><img src="' . $path . '"  style="float:left; margin: -13px 15px 0 0;" alt="ICanLocalize" /></a>';
  $output .= t('<h4>Sponsored by @link_open ICanLocalize @link_close</h4> Experts in Drupal translation', array('@link_open' => '<a href="http://www.icanlocalize.com/site/">',
														'@link_close' => '</a>'));
  
  return $output;
}