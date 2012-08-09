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
  $box->delta = 'nurani_about_nurani';
  $box->plugin_key = 'simple';
  $box->title = 'About Nurani';
  $box->description = 'About Nurani Video';
  $box->options = array(
    'body' => array(
      'value' => 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Duis vehicula imperdiet aliquam. Nunc molestie libero ac massa laoreet fermentum. Nulla semper consectetur orci eu sagittis. Nullam sit amet felis quam, sit amet egestas felis. Integer eget mauris velit, suscipit gravida diam. Cras non neque iaculis turpis malesuada bibendum. Mauris tempor tempus eros, a egestas tellus euismod et. Maecenas lobortis erat ac sapien adipiscing tincidunt. Nunc tincidunt dolor pellentesque turpis vulputate sed sollicitudin lectus pellentesque. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Pellentesque mauris tortor, fermentum et blandit at, accumsan et orci. Maecenas malesuada rutrum commodo. Duis ultrices massa eu nibh accumsan commodo.',
      'format' => 'filtered_html',
    ),
    'additional_classes' => '',
  );
  $export['nurani_about_nurani'] = $box;

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
