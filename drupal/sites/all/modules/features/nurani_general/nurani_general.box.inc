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
  $box->title = '<none>';
  $box->description = 'About Nurani Video';
  $box->options = array(
    'body' => array(
      'value' => '<iframe width="380" height="300" src="http://www.youtube.com/embed/fwb-J4ACYp0" frameborder="0" allowfullscreen></iframe>
<p> Lorem ipsum dolor sit amet, consectetur adipiscing elit. Duis vehicula imperdiet aliquam. Nunc molestie libero ac massa laoreet fermentum. Nulla semper consectetur orci eu sagittis. Nullam sit amet felis quam, sit amet egestas felis. Integer eget mauris velit, suscipit gravida diam. Cras non neque iaculis turpis malesuada bibendum.  </p>

<a  class ="welcome-link" href="#">View example Discussion</a>',
      'format' => 'full_html',
    ),
    'additional_classes' => '',
  );
  $export['nurani_about_nurani'] = $box;

  $box = new stdClass();
  $box->disabled = FALSE; /* Edit this to true to make a default box disabled initially */
  $box->api_version = 1;
  $box->delta = 'nurani_discussion_initation';
  $box->plugin_key = 'simple';
  $box->title = 'The Nurani Discussion';
  $box->description = 'Nurani discussion invitation';
  $box->options = array(
    'body' => array(
      'value' => '<p>Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry\'s standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged.</p>
<a  class ="invitation-link" href="#">Request an invitation to participate</a>',
      'format' => 'filtered_html',
    ),
    'additional_classes' => '',
  );
  $export['nurani_discussion_initation'] = $box;

  $box = new stdClass();
  $box->disabled = FALSE; /* Edit this to true to make a default box disabled initially */
  $box->api_version = 1;
  $box->delta = 'nurani_library_invitation';
  $box->plugin_key = 'simple';
  $box->title = 'Nurani Library';
  $box->description = 'Nurani library invitation';
  $box->options = array(
    'body' => array(
      'value' => '<p>Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry\'s standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged.</p>

<a  class ="invitation-link" href="#">Request invitation to Nurani Library</a>',
      'format' => 'filtered_html',
    ),
    'additional_classes' => '',
  );
  $export['nurani_library_invitation'] = $box;

  $box = new stdClass();
  $box->disabled = FALSE; /* Edit this to true to make a default box disabled initially */
  $box->api_version = 1;
  $box->delta = 'nurani_welcome';
  $box->plugin_key = 'simple';
  $box->title = '<none>';
  $box->description = 'Welcome to Nurani';
  $box->options = array(
    'body' => array(
      'value' => '<img class="d_ford" src="<?php print base_path() . path_to_theme() . \'/images/d_ford.jpg\'; ?>" />
<p>I am delighted to welcome you to SCRIPTURAL REASONING online and to Nurani - a platform for dialogue between Muslims, Jews and Christians. The practice of Scriptural Reasoning enables participants to go deeper into the faiths of others while also going deeper into their own faith—for the sake of God and God’s good purposes. I have not found anything else that serves so well to sustain on-going, faith-centred engagement among the Abrahamic traditions. I hope you find this opportunity of sharing and studying your scriptures with people of other faiths a rich and rewarding experience. </p>
 <br/>
With warmest regards, <br/><br/>
David Ford, Regius Professor of Divinity <br/>
University of Cambridge',
      'format' => 'php_code',
    ),
    'additional_classes' => '',
  );
  $export['nurani_welcome'] = $box;

  return $export;
}
