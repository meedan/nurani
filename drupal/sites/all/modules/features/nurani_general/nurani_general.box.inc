<?php
/**
 * @file
 * nurani_general.box.inc
 */

/**
 * Implements hook_default_box().
 */
function nurani_general_default_box() {
  $export = array();

  $box = new stdClass();
  $box->disabled = FALSE; /* Edit this to true to make a default box disabled initially */
  $box->api_version = 1;
  $box->delta = 'nurani_welcome';
  $box->plugin_key = 'simple';
  $box->title = 'Welcome to Nurani';
  $box->description = 'Welcome to Nurani';
  $box->options = array(
    'body' => array(
      'value' => 'I am delighted to welcome you to SCRIPTURAL REASONING online and to Nurani - a platform for dialogue between Muslims, Jews and Christians. The practice of Scriptural Reasoning enables participants to go deeper into the faiths of others while also going deeper into their own faith—for the sake of God and God’s good purposes. I have not found anything else that serves so well to sustain on-going, faith-centred engagement among the Abrahamic traditions. I hope you find this opportunity of sharing and studying your scriptures with people of other faiths a rich and rewarding experience. 

With warmest regards, 
David Ford, Regius Professor of Divinity at the University of Cambridge',
      'format' => 'filtered_html',
    ),
  );
  $export['nurani_welcome'] = $box;

  return $export;
}
