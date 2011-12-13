<?php

/**
 * Implementation of hook_default_box().
 */
function nurani_general_default_box() {
  $export = array();
  $box = new stdClass;
  $box->disabled = FALSE; /* Edit this to true to make a default box disabled initially */
  $box->api_version = 1;
  $box->delta = 'action_links';
  $box->plugin_key = 'simple';
  $box->title = '';
  $box->description = 'Action links';
  $box->options = array(
    'body' => '<?php
$links = nurani_custom_action_links();
print theme(\'links\', $links);
?>',
    'format' => '3',
  );

  $export['action_links'] = $box;
  $box = new stdClass;
  $box->disabled = FALSE; /* Edit this to true to make a default box disabled initially */
  $box->api_version = 1;
  $box->delta = 'discussion_info';
  $box->plugin_key = 'simple';
  $box->title = 'About This Discussion';
  $box->description = 'Discussion info';
  $box->options = array(
    'body' => '<?php
$vars[\'row\'] = (object) array(\'nid\' => arg(1));
ds_views_row_node($vars, \'discussion_participants\');
return $vars[\'object\'];
?>',
    'format' => '3',
  );

  $export['discussion_info'] = $box;
  $box = new stdClass;
  $box->disabled = FALSE; /* Edit this to true to make a default box disabled initially */
  $box->api_version = 1;
  $box->delta = 'login_footer';
  $box->plugin_key = 'simple';
  $box->title = '';
  $box->description = 'Login form footer';
  $box->options = array(
    'body' => '<p><a href="<?php print url(\'user/password\'); ?>">Request new password »</a></p>
<p><a href="<?php print url(\'content/about-nuraniorg\'); ?>">Learn more</a> about Nurani.org.</p>
<p><a href="<?php print url(\'content/guidance\'); ?>">Find out</a> about the ground rules for discussion.</p>
<p><a href="<?php print url(\'content/terms\'); ?>">Read</a> the terms of service.</p>',
    'format' => '3',
  );

  $export['login_footer'] = $box;
  $box = new stdClass;
  $box->disabled = FALSE; /* Edit this to true to make a default box disabled initially */
  $box->api_version = 1;
  $box->delta = 'login_title';
  $box->plugin_key = 'simple';
  $box->title = '';
  $box->description = 'Login form header';
  $box->options = array(
    'body' => '<h2>Currently an Invitation-only Private Project</h2>',
    'format' => '3',
  );

  $export['login_title'] = $box;
  $box = new stdClass;
  $box->disabled = FALSE; /* Edit this to true to make a default box disabled initially */
  $box->api_version = 1;
  $box->delta = 'welcome_box';
  $box->plugin_key = 'simple';
  $box->title = 'Welcome to Nurani';
  $box->description = 'Welcome to Nurani';
  $box->options = array(
    'body' => '<img class="d_ford" src="<?php print base_path() . path_to_theme() . \'/images/d_ford.jpg\'; ?>" />
I am delighted to welcome you to Nurani - a platform for dialogue between Muslims and Christians in two languages - Arabic and English.  One of the greatest blessings we have been given is our scriptures, so it is not surprising that one of the main ways we are able to bless each other is by sharing them. I have not found anything else that serves so well to sustain ongoing, faith-centred engagement among the Abrahamic traditions. I hope you find the experience of sharing and studying your scriptures with people of other faiths a rich and rewarding experience. <br /><br />With warmest regards, <br />David Ford, Regius Professor of Divinity at the University of Cambridge',
    'format' => '3',
  );

  $export['welcome_box'] = $box;
  return $export;
}
