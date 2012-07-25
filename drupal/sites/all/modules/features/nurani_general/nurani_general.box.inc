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
    'body' => '<p><a href="<?php print url(\'user/password\'); ?>">Request new password &raquo;</a></p>
<p><a href="<?php print url(\'content/getting-started\'); ?>">Getting started &raquo;</a></p>
<p><a href="<?php print url(\'content/how-do-scriptural-reasoning\'); ?>">How to do SR &raquo;</a></p>
<p>Learn more about<a href="<?php print url(\'content/about-nuraniorg\'); ?>">  Nurani.org.</a></p>
<p>Read the <a href="<?php print url(\'content/terms\'); ?>">Terms of service</a> and <a href="<?php print url(\'content/privacy\'); ?>">Privacy policy</a></p>
',
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
I am delighted to welcome you to <strong>SCRIPTURAL REASONING</strong> online and to Nurani - a platform for dialogue between Muslims, Jews and Christians. The practice of Scriptural Reasoning enables participants to go deeper into the faiths of others while also going deeper into their own faith—for the sake of God and God’s good purposes. I have not found anything else that serves so well to sustain on-going, faith-centred engagement among the Abrahamic traditions. I hope you find this opportunity of sharing and studying your scriptures with people of other faiths a rich and rewarding experience.  <br /><br />With warmest regards, <br />David Ford, Regius Professor of Divinity at the University of Cambridge',
    'format' => '3',
  );
  $export['welcome_box'] = $box;

  return $export;
}
