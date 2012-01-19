<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function nurani_general_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "boxes" && $api == "box") {
    return array("version" => 1);
  }
  elseif ($module == "context" && $api == "context") {
    return array("version" => 3);
  }
  elseif ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_imagecache_default_presets().
 */
function nurani_general_imagecache_default_presets() {
  $items = array(
    'thumbnail' => array(
      'presetname' => 'thumbnail',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '85',
            'height' => '85',
          ),
        ),
      ),
    ),
    'thumbnail_view' => array(
      'presetname' => 'thumbnail_view',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '48',
            'height' => '48',
          ),
        ),
      ),
    ),
  );
  return $items;
}

/**
 * Implementation of hook_node_info().
 */
function nurani_general_node_info() {
  $items = array(
    'annotation' => array(
      'name' => t('Annotation'),
      'module' => 'features',
      'description' => t('A comment on a glossary term.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Annotation'),
      'min_word_count' => '1',
      'help' => '',
    ),
    'discussion' => array(
      'name' => t('Discussion'),
      'module' => 'features',
      'description' => t('A scholarly discussion.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Your Thoughts'),
      'min_word_count' => '0',
      'help' => '',
    ),
    'page' => array(
      'name' => t('Page'),
      'module' => 'features',
      'description' => t('A static page.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
    'profile' => array(
      'name' => t('Profile'),
      'module' => 'features',
      'description' => t('A user profile built as content.'),
      'has_title' => '1',
      'title_label' => t('Username'),
      'has_body' => '0',
      'body_label' => '',
      'min_word_count' => '0',
      'help' => '',
    ),
    'response' => array(
      'name' => t('Response'),
      'module' => 'features',
      'description' => t('A comment in a scholarly discussion.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Response'),
      'min_word_count' => '1',
      'help' => '',
    ),
    'term' => array(
      'name' => t('Term'),
      'module' => 'features',
      'description' => t('A glossary term.'),
      'has_title' => '1',
      'title_label' => t('Term'),
      'has_body' => '0',
      'body_label' => '',
      'min_word_count' => '0',
      'help' => '',
    ),
    'text' => array(
      'name' => t('Text'),
      'module' => 'features',
      'description' => t('A scholarly text.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Text Passage'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implementation of hook_rules_defaults().
 */
function nurani_general_rules_defaults() {
  return array(
    'rules' => array(
      'rules_a_new_discussion_is_posted' => array(
        '#type' => 'rule',
        '#set' => 'event_node_insert',
        '#label' => 'A new discussion is posted',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'Nurani_notification',
          'nurani_general' => 'nurani_general',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#type' => 'condition',
            '#settings' => array(
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#name' => 'rules_condition_content_is_published',
            '#info' => array(
              'label' => 'Created content is published',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#weight' => 0,
          ),
          '1' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Created content is Discussion',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#name' => 'rules_condition_content_is_type',
            '#settings' => array(
              'type' => array(
                'discussion' => 'discussion',
              ),
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#type' => 'condition',
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#type' => 'action',
            '#settings' => array(
              'subject_ar' => '[author-name] has invited you to participate in a new discussion',
              'message_ar' => '
مرحبا [user]
مناقشة جديدة حول [eltit] قد بدأت للتو على موقع نورانى
يمكنك أن تكون أول من يبدي رأيه هنا : [node-url]
نحن نتطلع إلى قراءة تعليقاتك وأفكارك.
بالاضافة الى هذا فاننا بصدداختبار موقع نورانى ونبذل قصارى جهدنا لتحسينه قدر الإمكان، لذلك فإننا نرجوأن ترسل لنا ملاحظاتك واقتراحاتك الى البريد الاكتروني:  
sronline@interfaith.cam.ac.uk

شكرا ،
فريق نورانى
',
              'subject_en' => '[author-name] has invited you to participate in a new discussion',
              'message_en' => 'Hello [user]

[author-name] has just started a new discussion about [title] on Nurani.

You can be the first to comment here: [node-url]

we are looking forward to reading your comments!

We are testing the site and trying our best to improve it as much as possible, so we would appreciate it if you leave us feedback at zab23@cam.ac.uk

Thanks,
The Nurani team',
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#name' => 'rules_core_yallah_notifications_action',
            '#info' => array(
              'module' => 'Node',
              'arguments' => array(
                'node' => array(
                  'label' => 'Content',
                  'type' => 'node',
                ),
              ),
              'label' => 'Notify subscribed users',
              'base' => 'rules_core_action_execute',
              'action_name' => 'yallah_notifications_action',
              'configurable' => TRUE,
            ),
          ),
        ),
        '#version' => 6003,
      ),
      'rules_a_new_user_joins_a_discussion' => array(
        '#type' => 'rule',
        '#set' => 'event_agreement_event',
        '#label' => 'A new user Joins a discussion',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'Nurani_notification',
          'nurani_general' => 'nurani_general',
        ),
        '#status' => 'default',
        '#conditions' => array(),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Load User profile',
              'label callback' => FALSE,
              'arguments' => array(
                'user' => array(
                  'type' => 'user',
                  'label' => 'User, whose profile should be loaded',
                ),
              ),
              'new variables' => array(
                'user_profile' => array(
                  'type' => 'node',
                  'label' => 'Content Profile',
                ),
              ),
              'module' => 'Content Profile',
            ),
            '#name' => 'content_profile_action_load',
            '#settings' => array(
              'type' => 'profile',
              '#argument map' => array(
                'user' => 'user',
                'profile_node' => 'user_profile',
              ),
            ),
            '#type' => 'action',
          ),
          '1' => array(
            '#type' => 'action',
            '#settings' => array(
              'subject_ar' => '',
              'message_ar' => '',
              'subject_en' => '[author-name] has joined Nurani',
              'message_en' => 'Hello [user]

[author-name] has just joined Nurani. 

You can be the first to view [author-name]\'s profile here: [author-url]

We hope you\'ll get to know each other!

Thanks,
The Nurani team',
              '#argument map' => array(
                'node' => 'user_profile',
              ),
            ),
            '#name' => 'rules_core_yallah_notifications_action',
            '#info' => array(
              'module' => 'Node',
              'arguments' => array(
                'node' => array(
                  'label' => 'Content',
                  'type' => 'node',
                ),
              ),
              'label' => 'Notify subscribed users',
              'base' => 'rules_core_action_execute',
              'action_name' => 'yallah_notifications_action',
              'configurable' => TRUE,
            ),
            '#weight' => 0,
          ),
        ),
        '#version' => 6003,
      ),
      'rules_response_is_posted' => array(
        '#type' => 'rule',
        '#set' => 'event_node_insert',
        '#label' => 'Response is posted',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'Nurani_notification',
          'nurani_general' => 'nurani_general',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#type' => 'condition',
            '#settings' => array(
              'type' => array(
                'response' => 'response',
              ),
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#name' => 'rules_condition_content_is_type',
            '#info' => array(
              'label' => 'Created content is Response',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#weight' => 0,
          ),
          '1' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Created content is published',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#name' => 'rules_condition_content_is_published',
            '#settings' => array(
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#type' => 'condition',
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#type' => 'action',
            '#settings' => array(
              'subject_ar' => '[author-name] has just responded on [current-page-title] on Nurani',
              'message_ar' => 'مرحبا [user]

 [current-page-title]  تعليقا جديدا[author-name] لقد نشر   

قائلا: 

[node-body]

 [node-url]يرد عليه   أول من يمكنك أن تكون
نحن نتطلع إلى قراءة تعليقاتك وأفكارك
بالاضافة الى هذا فاننا بصدداختبار موقع نورانى ونبذل قصارى جهدنا لتحسينه قدر الإمكان، لذلك فإننا نرجوأن ترسل لنا ملاحظاتك واقتراحاتك الى البريد الاكتروني:  
sronline@interfaith.cam.ac.uk

 شكرا ،
فريق نورانى
',
              'subject_en' => '[author-name] has just responded on [current-page-title] on Nurani',
              'message_en' => 'Dear [user],

[author-name] has just posted a new response to Nurani on [current-page-title]. 

Saying:

[node-body]

you can be the first to reply here:[node-url]

we look forward to hearing what you have to say.

Thanks,
The Nurani Team.

',
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#name' => 'rules_core_yallah_notifications_action',
            '#info' => array(
              'module' => 'Node',
              'arguments' => array(
                'node' => array(
                  'label' => 'Content',
                  'type' => 'node',
                ),
              ),
              'label' => 'Notify subscribed users',
              'base' => 'rules_core_action_execute',
              'action_name' => 'yallah_notifications_action',
              'configurable' => TRUE,
            ),
          ),
        ),
        '#version' => 6003,
      ),
    ),
  );
}

/**
 * Implementation of hook_views_api().
 */
function nurani_general_views_api() {
  return array(
    'api' => '2',
  );
}
