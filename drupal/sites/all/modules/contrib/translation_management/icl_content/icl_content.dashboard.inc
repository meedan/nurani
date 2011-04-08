<?php

module_load_include ( 'inc', 'icl_core', 'icl_core.constants' );
module_load_include ( 'inc', 'icl_core', 'icl_core.settings' );
module_load_include ( 'inc', 'icl_content', 'icl_content.contact_form' );
module_load_include ( 'inc', 'icl_content', 'icl_content.node' );

// Manual verification of previously translated contents
if (user_access(ICL_CONTENT_PERM_TRANSLATE) && isset($_GET['verify']) && isset($_GET['id']) && isset($_GET['type'])) {
  _icl_dasboard_update_previously_translated();
}

// @todo Move this
if (isset($_GET['icl_content_dashboard_hide_advanced_filter'])) {
  global $user;
  $temp = variable_get('icl_content_dashboard_hide_advanced_filter', array());
  $temp[$user->uid] = (bool)$_GET['icl_content_dashboard_hide_advanced_filter'];
  variable_set('icl_content_dashboard_hide_advanced_filter', $temp);
  die($_GET['icl_content_dashboard_hide_advanced_filter']);
}
if (isset($_GET['icl_content_dashboard_hide_legend'])) {
  global $user;
  $temp = variable_get('icl_content_dashboard_hide_legend', array());
  $temp[$user->uid] = (bool)$_GET['icl_content_dashboard_hide_legend'];
  variable_set('icl_content_dashboard_hide_legend', $temp);
  die($_GET['icl_content_dashboard_hide_legend']);
}

/**
 * Enter description here...
 *
 * @return unknown
 */
function icl_content_dashboard_filter_form() {
  $form = array(
    '#type' => 'fieldset',    
  );
  
  $languages = locale_language_list();
  $languages[] = t ('Language neutral');
  $default = _icl_content_default_value('language', language_default()->language);
  if (_icl_wrapper_is_language_neutral($default)) {
    // handle language neutral setting
    $default = '0';
    drupal_add_js(array('icl_dashboard_send_disabled' => 1), 'setting');
    global $icl_dasboard_disable_language_neutral;
    $icl_dasboard_disable_language_neutral = 1;
  }
  
  $form['language'] = array(
    '#title' => t('Show'),
    '#type' => 'select',    
    '#options' => $languages,
    '#default_value' => $default,
  );
  
  $languages_to = locale_language_list();
  $languages_to[] = t('All languages');
  $form['to'] = array(
    '#title' => t('Translated to'),
    '#type' => 'select',    
    '#options' => $languages_to,
    '#default_value' => _icl_content_default_value('to', 0),
  );

  $options = array(
    'all' => t('All documents'),
    'update' => t('Not translated or needs updating'),
    'complete' => t('Translation Complete'),
    'in_progress' => t('Translation in progress')
  );

  $additional_filters = module_invoke_all('translation_dashboard_filter_mode');
  $options = array_merge($options, $additional_filters);

  $form['translation'] = array(
    '#title' => t('With status'),
    '#type' => 'select',    
    '#options' => $options,
    '#default_value' => _icl_content_default_value('translation', 'all'),
  );
  
  // Show/hide advanced filters
  global $user;
  $temp = variable_get('icl_content_dashboard_hide_advanced_filter', array());
  if (isset($temp[$user->uid]) && $temp[$user->uid]) {
    $hide_advanced_filter_style = ' style="display:none;"';
    $hide_advanced_filter_txt = t('Show advanced filters');
  }
  else {
    $hide_advanced_filter_style = '';
    $hide_advanced_filter_txt = t('Hide advanced filters');
  }
  
  // Show/hide legend
  $temp = variable_get('icl_content_dashboard_hide_legend', array());
  if (isset($temp[$user->uid]) && $temp[$user->uid]) {
    $hide_legend_style = '';
    $hide_legend_txt = t('Show status keys');
  }
  else {
    $hide_legend_style = ' style="display:none;"';
    $hide_legend_txt = t('Hide status keys');
  }
  
  // Show/hide JS return txt
  drupal_add_js(array('icl_dashboard_show_hide' => array(
    'hide_filters_text' => t('Hide advanced filters'),
    'show_filters_text' => t('Show advanced filters'),
    'hide_legend_text' => t('Hide status keys'),
    'show_legend_text' => t('Show status keys'),
    'ajax_url' => _icl_wrapper_url(_icl_wrapper_get_root_menu('translation-management/dashboard/'))
    )),
    'setting');
  
  $form['further'] = _icl_wrapper_form_create_markup(array(
    '#type' => 'markup',
    '#prefix' => '<div id="icl-dashboard-further" class="form-item"'. $hide_advanced_filter_style . '><label id="icl-dashboard-further-label">'.t('Filters').':',    
    '#suffix' => '</label></div>',
  ));
  
  $form['further']['status'] = array(
    '#type' => 'fieldset',
  );
  $form['further']['status']['status_enabled'] = array(   
    '#type' => 'checkbox',
    '#default_value' => _icl_content_default_value('status_enabled', FALSE),
  );
  $form['further']['status']['status_status'] = array(
    '#title' => t('Status'),
    '#type' => 'select',
    '#options' => array(
      'status-1' => t('published'),
      'status-0' => t('not published'),
      'promote-1' => t('promoted'),
      'promote-0' => t('not promoted'),
      'sticky-1' => t('sticky'),
      'sticky-0' => t('not sticky'),
    ),
    '#default_value' => _icl_content_default_value('status_status', 'status-1'),
  );
  
  $form['further']['type'] = array(
    '#type' => 'fieldset',
  );
  $form['further']['type']['type_enabled'] = array(    
    '#type' => 'checkbox',
    '#default_value' => _icl_content_default_value('type_enabled', FALSE),
  );
  $types = array();
  foreach (_icl_wrapper_node_get_types() as $type => $details) {
    $types[$type] = $details->name;    
  }
  // Add a block type
  $types['block'] = 'Block (i18n)';
  // Add a string type
  $types['strings'] = 'Strings';

  if (is_standard_contact_form_enabled()) {  
    // Add standard contact form
    $types['standard_contact_form'] = 'Contact Form';
  }
  
  $form['further']['type']['type_type'] = array(
    '#title' => t('Type'),
    '#type' => 'select',
    '#options' => $types,
    '#default_value' => _icl_content_default_value('type_type', ''),
  );

  $form['further']['search'] = array(
    '#type' => 'fieldset',
  );
  $form['further']['search']['search_enabled'] = array(   
    '#type' => 'checkbox',
    '#default_value' => _icl_content_default_value('search_enabled', FALSE),
  );
  $form['further']['search']['search_text'] = array(
    '#title' => t('Title'),
    '#type' => 'textfield',
    '#default_value' => _icl_content_default_value('search_text', ''),
  );
  
  $form['show_hide'] = _icl_wrapper_form_create_markup(array(
    '#type' => 'markup',
    '#value' => '<div id="icl_dashboard_show_filter_link_wrapper"><a id="icl_dashboard_show_filter_link" href="javascript:void(0);" title="' . $hide_advanced_filter_txt . '">' . $hide_advanced_filter_txt . '</a>&nbsp;&nbsp;<a class="icl_dashboard_hide_legend_link" href="javascript:void(0);" title="' . $hide_legend_txt . '"' . $hide_legend_style . '>' . $hide_legend_txt . '</a></div>',
  ));
  
  $form['op'] = array(
    '#value' => t('Update display'),
    '#type' => 'submit',
    '#submit' => array('icl_content_dashboard_filter_form_submit'),
  );
  
  return $form;
}

/**
 * Enter description here...
 *
 */
function icl_content_dashboard_filter_form_submit($form, &$form_state) {
  global $icl_content_dashboard_filter;
  
  $icl_content_dashboard_filter = array(
    'language' => $form_state['values']['language'],
    'to' => $form_state['values']['to'],
    'translation' => $form_state['values']['translation'],
    'status_enabled' => $form_state['values']['status_enabled'] == 1,
    'status_status' => $form_state['values']['status_status'],
    'type_enabled' => $form_state['values']['type_enabled'] == 1,
    'type_type' => $form_state['values']['type_type'],
    'search_enabled' => $form_state['values']['search_enabled'] == 1,
    'search_text' => $form_state['values']['search_text'],
    
  );
  
  if ($icl_content_dashboard_filter['language'] == '0') {
    // handle language neutral setting
    $icl_content_dashboard_filter['language'] = ' ';
  }
  
  /*if ($icl_content_dashboard_filter['to'] == '0') {
    // handle language neutral setting
    $icl_content_dashboard_filter['to'] = '';
  }*/
  
  _icl_wrapper_drupal_set_session('icl_dashboard_filter', $icl_content_dashboard_filter);
  
  //$form_state['rebuild'] = TRUE;
}

/**
 * Enter description here...
 *
 * @return unknown
 */
function icl_content_dashboard_nodes_form($dashboard_mode = TRUE) {
  $form = array(
    'title' => array(),
    'type' => array(),
    'status' => array(),
    'words' => array(),
    'translation' => array(),
  );
  
  $form['#theme'] = 'icl_content_dashboard_nodes';
  $node_types = _icl_wrapper_node_get_types();
  
  $nodes = array();
  if ($dashboard_mode) {
    $content = icl_content_dashboard_build_filter_query();
  }
  
  $form['#content'] = $content;
  
  $count = 0;
  
  global $user;
  if (isset($_GET['show_all'])) {
    $show_all = $_GET['show_all'] != '0';
    variable_set('icl_dashboard_show_all_' . $user->uid, $show_all);
  } else {
    $show_all = variable_get('icl_dashboard_show_all_' . $user->uid, FALSE);
  }

  // Get the word count for nodes.
  $node_words = icl_content_get_word_count_for_nodes();
  
  foreach($content as $node) {
    if ($node['type'] == 'icl_block_marker') {
      $nid = $node['id'];
      $type = 'Block (i18n)';
      $words = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT words FROM {icl_block} WHERE bid = %d", substr($nid, 6)));
    } else if ($node['type'] == 'icl_contact_form_marker') {
      $nid = $node['id'];
      $type = 'Contact form';
      $contact_data = _icl_content_extract_standard_contact_form();
      $contact_data = icl_content_calculate_md5_and_words_from_data($contact_data);
      $words = $contact_data['words'];
    } else if ($node['type'] == 'icl_strings_marker') {
      $nid = $node['id'];
      $type = 'Strings';
      $words = _icl_content_get_words_for_string(substr($nid, 7));
    } else {
      $nid = $node['id'];
      $type = $node_types[$node['type']]->name;
      $words = $node_words[$nid];
      if ($words === null) {
        $node_test = node_load($nid);
        $node_data = icl_content_calculate_node_md5_and_words($node_test);
        icl_content_save_node_md5_and_words($node_test, $node_data['md5'], $node_data['words']);
        $words = $node_data['words'];
      }
    }
    $nodes[$nid] = '';

    if ($dashboard_mode) {
      $form['title'][$nid] = array('#value' => l($node['title'], $node['link']));
    } else {
      // translation review mode
      // add a parameter to the link.
      $form['title'][$nid] = array('#value' => l($node->title, 'node/'.$node->nid, array('query' => array('review' => '1'))));
    }
     
    $form['type'][$nid] = array('#value' => $type);
    $form['status'][$nid] = array('#value' => $node['status']);
    $form['words'][$nid] = array('#value' => $words);
    $form['translation'][$nid] = array('#value' => (empty($node['language']) || _icl_wrapper_is_language_neutral($node['language'])) ? t('Language neutral') : _icl_wrapper_theme('icl_content_fancy_status', array('node' => $node, 'short' => TRUE)));
    
    $form['translation'][$nid]['result-'.$nid] = _icl_wrapper_form_create_markup(array(
      '#type' => 'markup',
      '#prefix' => '</td></tr><tr id="tr-result-'.$nid.'" style="display:none;"><td></td><td colspan="4"><div id="result-'.$nid.'">',
      '#suffix' => '</div>',
      '#value' => '<!- This will be replaced ->',
    ));
    /*$form['translation'][$nid]['word_count'.$nid] = array(
      '#type' => 'button',
      '#value' => 'Details',
      '#submit' => array('icl_content_icl_status'),
      '#ahah' => array(
        'path' => 'icl_content/icl_status/'.$nid,
        'wrapper' => 'result-'.$nid,
        'method' => 'replace',
        'effect' => 'fade',
        'progress' => array(
          'type' => 'throbber',
        )
        ),
    );
    */
    $ahah_binding = array(
      'url' => _icl_wrapper_url('icl_content/icl_status/'.$nid),
      'event' => 'click',
      'wrapper' => 'result-'.$nid,
      'selector' => '#details-'.$nid,
      'method' => 'replace',
      'effect' => 'fade',
      'progress' => array(
        'type' => 'throbber',
      ),
      );
    
    if (strpos($form['translation'][$nid]['#value'], t ( 'Not translated yet' )) === FALSE) {
      $form['translation'][$nid]['#value'] = '<a href="#" id="details-'.$nid.'">'.$form['translation'][$nid]['#value'].'</a>';
    }
    
    drupal_add_js(array('ahah' => array('details-'.$nid => $ahah_binding)), 'setting');

    if (!$show_all) {
      $count++;
      if ($count == variable_get('icl_content_num_items_to_display', 50)) {
        break;
      }
    }
  } 

  if ($dashboard_mode) {
    $form['nodes'] = array('#type' => 'checkboxes', '#options' => $nodes, '#attributes' => _icl_wrapper_form_create_attributes(array('class' => 'icl_dashboard_checkbox_send')));
    if (isset($_GET['nid'])) {
      // select the single node
      $form['nodes']['#default_value'] = $nodes;
    }
  }
  
  return $form;
}

function _icl_content_dashboard_filter_get_params() {
  $params = array();
  
  if ( isset ($_SESSION['icl_dashboard_filter']) ) {
    $params['language'] = $_SESSION['icl_dashboard_filter']['language'];
    if ($params['language'] == null) {
      $params['language'] = language_default()->language;
    }
    $params['to'] = $_SESSION['icl_dashboard_filter']['to'];
    if ($params['to'] == null) {
      $params['to'] = 0;
    }
    $params['translation'] = $_SESSION['icl_dashboard_filter']['translation'];
    if ($params['translation'] == null) {
      $params['translation'] = 'all';
    }
    $params['status_status'] = $_SESSION['icl_dashboard_filter']['status_status'];
    $params['status_enabled'] = $_SESSION['icl_dashboard_filter']['status_enabled'];
    $params['type_type'] = $_SESSION['icl_dashboard_filter']['type_type'];
    if (isset($_SESSION['icl_dashboard_filter']['type_enabled'])) {
      $params['type_enabled'] = $_SESSION['icl_dashboard_filter']['type_enabled'];
    }
    if (isset($_SESSION['icl_dashboard_filter']['search_text'])) {
      $params['search_text'] = $_SESSION['icl_dashboard_filter']['search_text'];
    }
    if (isset($_SESSION['icl_dashboard_filter']['search_enabled'])) {
      $params['search_enabled'] = $_SESSION['icl_dashboard_filter']['search_enabled'];
    }
  } else {
    $params['language'] = language_default()->language;
    $params['translation'] = 'all';
    $params['to'] = 0;
  }
  return $params;
}


/**
 * Enter description here...
 *
 */
function icl_content_dashboard_build_filter_query($page_mode = true) {
  global $icl_content_dashboard_filter;
  
  $default_language = _icl_content_default_value('language', language_default()->language );
  
  if ($icl_content_dashboard_filter == null) {
    $icl_content_dashboard_filter = _icl_content_dashboard_filter_get_params();
  }
  
  $content = icl_content_get_nodes_for_dashboard($icl_content_dashboard_filter);
  
  if (isset($_GET['nid'])) {
    return $content;
  }
  
  if (module_exists('block')) {
  
    $content_blocks = icl_content_get_blocks_for_dashboard($icl_content_dashboard_filter);
    foreach ($content_blocks as $item) {
      $content[] = $item;
    }
  }
  
  $content_contact_form = icl_content_get_contact_form_for_dashboard($icl_content_dashboard_filter);
  if ($content_contact_form) {
    $content[] = $content_contact_form;
  }
  
  $content_strings = icl_content_get_strings_for_dashboard($icl_content_dashboard_filter);
  foreach ($content_strings as $item) {
    $content[] = $item;
  }

  if (isset($_GET['string']) && $_GET['string'] == 'queued') {
    $string = array();
    foreach ( $content as $item ) {
      if ($item['id'] == 'string-queued') {
        return array($item);
      }
    }
  }
  
  // Only allow content with the selected translation status
  foreach ($content as $key => $item) {
    if (isset($icl_content_dashboard_filter['translation'])) {
      switch ($icl_content_dashboard_filter['translation'] ) {
        case 'complete':
          // all the target languages should be complete
          foreach ($item['targets'] as $lang => $target) {
            if ($icl_content_dashboard_filter['to'] == '0' || $icl_content_dashboard_filter['to'] == $lang) {
              if ($target['rid_status'] != ICL_STATUS_SUCCESSFUL || $target['needs_update'] == 1) {
                // not complete to this language
                unset($content[$key]);
                continue;
              }
            }
          }
          break;
        
        case 'update':
          // any language requires an update
          $update_required = FALSE;
          foreach ($item['targets'] as $lang => $target) {
            if ($icl_content_dashboard_filter['to'] == '0' || $icl_content_dashboard_filter['to'] == $lang) {
              if (($target['rid_status'] == ICL_STATUS_SUCCESSFUL && $target['needs_update']) ||
                                      ($target['translated'] == 0 && $target['current_rid'] == 0)) {
                // this language is in progress so it should remain in the list
                $update_required = TRUE;
                break;
              }
            }
          }
          if (!$update_required) {
            unset($content[$key]);
          }
          break;

        case 'in_progress':
          // any language should be in progress
          $found_in_progress = FALSE;
          foreach ($item['targets'] as $lang => $target) {
            if ($icl_content_dashboard_filter['to'] == '0' || $icl_content_dashboard_filter['to'] == $lang) {
              if ($target['current_rid'] > 0  && $target['rid_status'] != ICL_STATUS_SUCCESSFUL) {
                // this language is in progress so it should remain in the list
                $found_in_progress = TRUE;
                break;
              }
            }
          }
          if (!$found_in_progress) {
            // none are in progress
            unset($content[$key]);
          }
          break;
      
        case 'all':
        default:
          // Allow all content
          break;
      }
    }
  }

  $filtered_contents = module_invoke_all('translation_dashboard_filter_nodes', $icl_content_dashboard_filter['translation'], $content);
  if (isset($filtered_contents[0]) && $filtered_contents[0] === FALSE) {
    $content = array();
  } else if (!empty($filtered_contents)) {
    $content = $filtered_contents;
  }

  return $content;
  
}


/**
 * Enter description here...
 *
 * @return unknown
 */
function icl_content_dashboard_action_form(&$form_in, $translation_options_only = false) {
  
  icl_core_add_thickbox();
  
  $form = array();
  
  // @todo Remove or uncomment
  /*if (variable_get('icl_dashboard_update_previous', 'init') == 'init') {
    $form['auto_update'] = _icl_dashboard_get_auto_update_form();
  }*/
  
  $form['operations'] = array(
    '#type' => 'fieldset',
    '#title' => t('Translation options'),
    '#attributes' => _icl_wrapper_form_create_attributes(array('id' => 'dashboard-actions')),
  );
  
  drupal_add_js(array('icl_service_info' => array(
    'ajax_url' => _icl_wrapper_url(_icl_wrapper_get_root_menu('translation-management')))),
    'setting');

  $form['service_info'] = _icl_wrapper_form_create_markup(array(
      '#type' => 'markup',
      '#access' => TRUE,
      '#value' => '<div id="icl_service_info_wrapper"></div>',
      '#weight' => 999,
      )
  );
  
  global $icl_dasboard_disable_language_neutral;
  if ($icl_dasboard_disable_language_neutral === 1) {
    $form['operations']['language_neutral_notice'] =_icl_wrapper_form_create_markup(array(
      '#type' => 'markup',
      '#value' => t("<b>Note:</b> Language Neutral content can't be translated to other languages. <br />You must change the language of the content before it can be translated."),
    ));
    return $form;
  }
  
  $languages = array();
  $no_languages = array();
  $pending_languages = array();
  $no_translator_languages = array();
  $defaults = array();
  $selected_language = _icl_content_default_value('language', language_default()->language);
  $selected_language = icl_core_get_language_name($selected_language);
  
  $translation_services = module_invoke_all('translation_service');

  if (sizeof($translation_services) > 0) {
    foreach ($translation_services as $module => $service) {
      if (module_hook($module, 'translation_dashboard_action_form')) {
        $form_in = module_invoke($module, 'translation_dashboard_action_form', $form_in);
      }
    }
  }

  if ($selected_language == null) {
    $form['operations']['message'] = _icl_wrapper_form_create_markup(array(
      '#type' => 'markup',
      '#prefix' => '<div class="status">',
      '#suffix' => '</div>',
      '#value' => t('Content that is language neutral cannot be sent for translation. Edit the content and set the language if you want to send it for translation'),
    ));
  } else {
    
    
    
    // Get the languages that are enabled on this site.
    $site_languages = language_list('enabled', TRUE);
    foreach ($site_languages[1] as $code => $value) {
      // Get all languages
      //if (icl_core_get_language_name($code) != $selected_language) {
        $languages[$code] = t('Translate to @lang ', array('@lang' => icl_core_get_drupal_language_name($code)));
      //}
      
    }
    
    foreach($languages as $code => $value) {
      $defaults[] = $code;
    }
  
    if (sizeof($languages) == 0) {
      $form['operations']['no_langs'] = _icl_wrapper_form_create_markup(array(
        '#type' => 'markup',
        '#value' => '<b>' . t('There are no translators assigned to any of your target languages.') . '</b>',
      ));
    }
    
    // Check if filter lang is submitted
    global $icl_content_dashboard_filter;
    if (isset($icl_content_dashboard_filter['language'])) {
      $lang_from = $icl_content_dashboard_filter['language'];
    }
    else {
      $lang_from = language_default()->language;
    }

    module_load_include('inc', 'icl_translate', 'icl_translate.translation_services');

    if (sizeof($translation_services) == 0) {
      $form['operations']['servicess'] = _icl_wrapper_form_create_markup(array(
        '#type' => 'markup',
        '#prefix' => '<div class="error">',
        '#suffix' => '</div>',
        '#value' => '<b>' . t('There are no translation services available. You need to enable a translation service - <a href="@url">modules</a>.',
                              array('@url' => _icl_wrapper_url(_icl_wrapper_get_drupal_menu('admin/build/modules')) . '#Translation%20Services')) . '</b>',
      ));
    } else {
    
      $last_selected_translators = variable_get('icl_last_selected_translators', array());
  
      foreach ($defaults as $k => $translation_option) {
        
        // Skip if option 'Translate to' is same as current language
        if ($lang_from == $translation_option) {
          continue;
        }
        
        $target_name = 'targets[' . $translation_option . ']';
        $form['operations']['translation_options'][$target_name] = array(
        '#type' => 'checkbox',
        '#name' => $target_name,
        '#title' => $languages[$translation_option],
        '#default_value' => 1,
        '#attributes' => _icl_wrapper_form_create_attributes(array('class' => 'icl_dashboard_checkbox_translators')),
        );
        
        $disable_checkbox = TRUE;
        $no_translators = array();
        
        $translator_select = array();
        $translator_manage_links = array();
        
        foreach ($translation_services as $module => $service) {
          
          if (module_hook($module, 'get_translators')) {
            
            $name = $service['name'];
            $name_key = icl_translate_get_service_name_key($name);
            
            if ($translators = module_invoke($module, 'get_translators', $lang_from, $translation_option)) {
              foreach ($translators as $translator) {
                if ($translator['id'] == -1) {
                  $translator_select[$name_key . '-first'] = $translator['name'] . ' (' . $name . ')';
                } else {
                  $translator_select[$name_key . '-' . $translator['id']] = $translator['name'] . ' (' . $name . ')';
                  $disable_checkbox = FALSE;
                }
              }
            }
            else {
              $no_translators[] = $module;
            }
          }
          
          if (module_hook($module, 'translators_setup_url')) {
            $setup_url = module_invoke($module, 'translators_setup_url', $lang_from, $translation_option);
            if ($setup_url != '') {
              $translator_manage_links[$module] = $setup_url;
            }
          }
        }
        
        if (sizeof($translator_select) > 0) {
        
          $form['operations']['translation_options'][$target_name]['translators'] = array(
            '#type' => 'select',
            '#options' => $translator_select,
            '#value' => 'local-first',
            '#name' => 'translators[' . $translation_option  . ']',
            '#prefix' => t(' - Use translator '),
          );
          
          if (isset($last_selected_translators[$translation_option])) {
            $form['operations']['translation_options'][$target_name]['translators']['#value'] = $last_selected_translators[$translation_option];
          }
        } else {
          $form['operations']['translation_options'][$target_name]['translators'] = _icl_wrapper_form_create_markup(array(
            '#type' => 'markup',
            '#value' => '<em>' . t(' - No translators available ') . '</em>',
          ));
        }
        // @todo Clean this

        $form['operations']['translation_options'][$target_name]['manage'] = _icl_wrapper_form_create_markup(array(
          '#value' => t('<a href="@url">Add translators</a>', array('@url' => _icl_wrapper_url(_icl_wrapper_get_root_menu('translation-management/manage-translator'), array('query' => 'from=' . $lang_from . '&to=' . $translation_option))))
        ));

//        if (sizeof($translator_manage_links) == 1) {
//          // only one translation service, so use its link.
//          $translator_manage_links = array_values($translator_manage_links);
//          $form['operations']['translation_options'][$target_name]['manage'] = _icl_wrapper_form_create_markup(array(
//            '#value' => t('<a href="@url">Manage translators</a>', array('@url' =>  $translator_manage_links[0])))
//          );
//        } else {
//          // Multiple translation services.
//
//          $value = '<a href="#TB_inline?height=410&amp;width=640&amp;inlineId=verification' . $translation_option . '&amp;modal=true" class="thickbox">' . t('Manage translators') . '</a>
//
//              <div id="verification' . $translation_option . '" style="display:none;">
//              <h2>' . t('Manage Translators') . '</h2>
//              <p style="border-bottom: 1px solid #CCCCCC; margin-bottom: 0px;">' . t('Select which translation service') . '</p>
//              <table border="0" cellspacing="0" cellpadding="0" class="icl_manage_translators_popup">';
//
//
//          foreach ($translator_manage_links as $module => $link) {
//
//            $value .= '<tr>';
//            if ($translation_services[$module]['logo']) {
//              $value .= '<td>';
//              if (module_hook($module, 'translators_setup_url_filter_link')) {
//                $link = module_invoke($module, 'translators_setup_url_filter_link', '<a href="#" onClick="window.location = \''. $link . '\'" >', $link, in_array($module, $no_translators));
//              } else {
//                $link = '<a href="#" onClick="window.location = \''. $link . '\'" >';
//              }
//              $value .= $link . '<img src="' . $translation_services[$module]['logo_small']
//                     . '" alt="' . $translation_services[$module]['name'] . '" /></a>'
//                     . sprintf($translation_services[$module]['tagline_manage_translators'], $site_languages[1][$lang_from]->name, $site_languages[1][$translation_option]->name, $link, '</a>')
//                 . '</td>';
//            } else {
//              $value .= '<td>';
//              if (module_hook($module, 'translators_setup_url_filter_link')) {
//                $link = module_invoke($module, 'translators_setup_url_filter_link', '<a onClick="window.location = \''. $link . '\'" >', $link, in_array($module, $no_translators));
//              } else {
//                $link = '<a href="#" onClick="window.location = \''. $link . '\'" >';
//              }
//              $value .= sprintf($translation_services[$module]['tagline_manage_translators'], $site_languages[1][$lang_from]->name, $site_languages[1][$translation_option]->name, $link, '</a>') . '</td>';
//            }
//            $value .= '</tr>';
//          }
//
//          $value .= '</table>';
//
//          $value .= '
//            <input type="button" name="cancel" value="' . t('Cancel') . '" onClick="tb_remove(); return false;" />
//
//            </div>';
//
//          $form['operations']['translation_options'][$target_name]['manage'] = _icl_wrapper_form_create_markup(array(
//            '#value' => $value
//          ));
//
//        }
        
        $form['operations']['translation_options']['#theme'] = 'icl_content_dashboard_translation_selection';
        
        if ($disable_checkbox) {
          $form['operations']['translation_options'][$target_name]['#default_value'] = 0;
          $form['operations']['translation_options'][$target_name]['#attributes'] = _icl_wrapper_form_create_attributes(array('disabled' => 'disabled'));
        }
      }
      
      if (sizeof($languages) == 0 && sizeof($no_translator_languages) == 0) {
        $form['operations']['message'] = _icl_wrapper_form_create_markup(array(
          '#type' => 'markup',
          '#prefix' => '<div class="status">',
          '#suffix' => '</div>',
          '#value' => t('No target languages have been set for translating from @language', array('@language' => icl_core_get_drupal_language_names_from_ican_language($selected_language))),
        ));
      } else if (sizeof($languages) != 0) {
        $form['operations']['manage_translators_link'] = _icl_wrapper_form_create_markup(array(
          '#type' => 'markup',
          '#prefix' => '<div style="margin-bottom:10px;">',
          '#suffix' => '</div>',
          '#value' => l(t('Manage translators'), _icl_wrapper_get_root_menu('translation-management/manage-translator')),
        ));
        $form['operations']['translate_request'] = array(
          '#type' => 'submit',
          '#validate' => array('icl_content_dashboard_action_validate'),
          '#submit' => array('icl_content_dashboard_action_submit'),
          '#value' => t('Translate selected documents'),
          '#attributes' => _icl_wrapper_form_create_attributes(array('disabled' => 'disabled')),
        );
        if (count($site_languages[1]) < 2) {
          drupal_add_js(array('icl_dashboard_send_disabled' => 1), 'setting');
        }
      }
    
    }
  }
  
  if (!$translation_options_only && FALSE) {
    $form['cost_estimate'] = array(
      '#type' => 'fieldset',
      '#title' => t('Translation cost estimate'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['cost_estimate']['result_count'] = _icl_wrapper_form_create_markup(array(
      '#type' => 'markup',
      '#prefix' => '<div id="result-count">',
      '#suffix' => '</div>',
      '#value' => '<!- This will be replaced ->',
    ));
    $form['cost_estimate']['word_count'] = _icl_wrapper_form_convert_ahah_to_ajax(array(
      '#type' => 'button',
      '#value' => 'Produce word count for untranslated contents',
      //'#attributes' => _icl_wrapper_form_create_attributes(array('onclick' => "javascript:on_word_count_button();return false;")),
      '#submit' => array('icl_content_word_count'),
      '#ahah' => array(
        'path' => 'icl_content/word_count',
        'wrapper' => 'result-count',
        'method' => 'replace',
        'effect' => 'fade',
        'progress' => array(
          'type' => 'throbber',
        )
        ),
    ));
  }
  
  return $form;
}

/**
 * Enter description here...
 *
 * @param unknown_type $form
 * @return unknown
 */
function theme_icl_content_dashboard_translation_selection($form) {

  if (defined('ICL_D7')) {
    $form = $form['form'];
  }
  
  $output = '';
  foreach ($form as $key => $value) {
    if (isset($value['#type']) && $value['#type'] == 'checkbox') {
      $checkbox = drupal_render($form[$key]);
      $checkbox = str_replace('</div>', drupal_render($value['translators']) . '&nbsp;&nbsp;&nbsp;' . drupal_render($value['manage']) . '</div>', $checkbox);
      $output .= $checkbox;
      
    }
    
  }
  // @todo Cleanup
  /*if ( isset ( $form['guide']) ) {
    $output .= drupal_render($form['guide']);
  }*/
  
  $output .= drupal_render($form['translate_request']);
  
  return $output;  
}

/**
 * Enter description here...
 *
 * @param unknown_type $form
 * @param unknown_type $form_state
 */
function icl_content_dashboard_action_validate($form, &$form_state) {
  $nodes = array_filter($form_state['values']['nodes']);
  if (count($nodes) == 0) {
    form_set_error('', t('No items selected.'));
  }
  
  // @todo Why doesn't $target get passed to form state values?
  //$targets = array_filter($form_state['values']['targets']);
  $targets = $_POST['targets'];
  if (count($targets) == 0) {
    form_set_error('', t('No translation targets were selected.'));
  }  
}

/**
 * Enter description here...
 *
 * @param unknown_type $form
 * @param unknown_type $form_state
 */
function icl_content_dashboard_action_submit($form, &$form_state) {
    
  // Filter out unchecked nodes
  $content_to_translate = array_filter($form_state['values']['nodes']);
  $nodes = array();
  $blocks = array();
  $contact_form = False;
  $strings = array();
  foreach($content_to_translate as $content) {
    if (strpos($content, 'block-') === 0) {
      $blocks[] = substr($content, 6);
    } else if (strpos($content, 'contact-') === 0) {
      $contact_form = True;
    } else if (strpos($content, 'string-') === 0) {
      $strings[] = substr($content, 7);
    } else {
      $nodes[] = $content;
    }
  }
  $langcodes = array();
  // @todo Why cant we get targets from form state values?
  /*foreach($form_state['values']['targets'] as $key => $value){
    if ($key === $value) {
      $langcodes[] = $value;
    }
  }
  */
  foreach($_POST['targets'] as $key => $value){
    $langcodes[] = $key;
  }
  icl_content_dashboard_filter_form_submit($form, $form_state);
  $form_state['rebuild'] = FALSE;
  
  // @todo Why can't we get translators from form state values?
  $selected_translators = $_POST['translators'];
  variable_set('icl_last_selected_translators', $selected_translators);
  
  $translators = array();
  foreach ($selected_translators as $code => $translator) {
    $translator = preg_split('/-/', $translator);
    if ($translator[1] == 'first') {
      $translator[1] = -1; // use any translator
    }
    
    $translators[$code] = array('id' => $translator[1], 'translation_service' => $translator[0]);
  }
  
  icl_content_translate_posts($nodes, $langcodes, $translators);
  icl_content_translate_blocks($blocks, $form_state['values']['language'], $langcodes, $translators);
  if ($contact_form) {
    icl_content_translate_standard_contact_form($form_state['values']['language'], $langcodes, $translators);
  }
  icl_content_translate_strings($strings, $form_state['values']['language'], $langcodes, $translators);
}

function icl_content_dashboard_email_validate($form, &$form_state) {
  variable_set('icl_core_email_address', $form_state['values']['icl_core_email_address']);
  
  $session_id = _icl_get_session_id();
  
  if ($session_id == NULL) {
    variable_set('icl_core_email_address', '');
    form_set_error('', '<b>' . t('Cannot access the ICanLocalize server with this email address') . '</b>');
  }
  
}

function icl_content_dashboard_email_submit($form, &$form_state) {
  variable_set('icl_core_email_address', $form_state['values']['icl_core_email_address']);
}

/**
 * Enter description here...
 *
 * @return unknown
 */
function icl_content_dashboard() {
  
  $translation_services = module_invoke_all('translation_service');
  if ((sizeof($translation_services) == 0) && !variable_get('icl_auto_enable_trans_services_done', FALSE)) {
    
    // Let's try to enable icanlocalize_translations and local_translations module.
    // Also the one_hour_translations module
    if (!defined('ICL_D7')) {
      include_once('includes/install.inc');
      _icl_wrapper_module_rebuild_cache();
      drupal_install_modules(array('icanlocalize_translations', 'local_translations', 'one_hour_translations'));
    }

    // only allow auto enabling once
    variable_set('icl_auto_enable_trans_services_done', TRUE); 

  }
  
  $form = array();
  
  $form = _icl_content_add_translation_service_message($form);
  
  $i18n_not_installed = _icl_wrapper_check_i18n_installed();
  if (sizeof($i18n_not_installed) > 0) {
    $form['i18n_errors'] = array (
      '#type' => 'fieldset', 
      '#title' => t ( 'Missing i18n modules.' ), 
      '#collapsible' => false );
  
    foreach($i18n_not_installed as $id => $module) {
      $form ['i18n_errors'] [$module['module']] = _icl_wrapper_form_create_markup(array (
          '#type' => 'markup', 
          '#prefix' => '<div class="error">', 
          '#suffix' => '</div>', 
          '#value' => $module['message']));
    }
  }

  $form['icl_url_changed'] = _icl_wrapper_form_create_markup(array(
    '#type' => 'markup',
    '#prefix' => '<div class="icl_red_box">',
    '#suffix' => '</div>',
    '#value' => '',
  ));

  $form = icl_content_dashboard_add_title_warning($form);
  
  $form['status_messages'] = _icl_wrapper_form_create_markup(array(
    '#type' => 'markup',
    '#prefix' => '<div class="icl_cyan_box">', 
    '#suffix' => '</div>', 
    '#value' => '',
    '#access' => FALSE,
    ));

  $form['reminders'] = _icl_wrapper_form_create_markup(array(
    '#type' => 'markup',
    '#value' => _icl_translate_render_reminders(),
  ));
  //$form = icl_core_add_reminders($form);

  /*
   $form['icl_support'] =  _icl_wrapper_form_create_markup(array(
    '#type' => 'markup',
    '#prefix' => '<div class="icl_cyan_box">',
    '#suffix' => '</div>',
    '#value' => icl_core_get_support_help(),
  ));
  */

  if (isset($_GET['nid']) or isset($_GET['string'])) {
    $form['icl_show_all'] =  _icl_wrapper_form_create_markup(array(
      '#type' => 'markup',
      '#prefix' => '<div class="icl_cyan_box">',
      '#suffix' => '</div>',
      '#value' => t('<a href="@url">Show all documents</a>', array('@url' => _icl_wrapper_url(_icl_wrapper_get_root_menu('translation-management/dashboard')))),
    ));
    
    // @todo Review this
    if (isset($_GET['string'])) {
      $form['filter']['language'] = array(
        '#type' => 'hidden',
        '#default_value' => language_default()->language,
      );
    }
  
  
  } else {
    $form['filter'] = icl_content_dashboard_filter_form();
  }

  global $user;
  
  if (isset($_GET['show_all'])) {
    $show_all = $_GET['show_all'] != '0';
    variable_set('icl_dashboard_show_all_' . $user->uid, $show_all);
  } else {
    $show_all = variable_get('icl_dashboard_show_all_' . $user->uid, FALSE);
  }
  if ($show_all) {
    $form['pager'] = _icl_wrapper_form_create_markup(array(
      '#type' => 'markup',
      '#value' => t('Displaying all @total items. <a href="@url">Show first @count items.</a>',
                        array('@count' => variable_get('icl_content_num_items_to_display', 50),
                              '@total' => $total,
                              '@url' => _icl_wrapper_url(_icl_wrapper_get_root_menu('translation-management/dashboard'), array('query' => 'show_all=0'))))
    ));
  }
  
  $form['nodes'] = icl_content_dashboard_nodes_form();
  if (!$show_all) {
    $total = sizeof($form['nodes']['#content']);
    if ($total > variable_get('icl_content_num_items_to_display', 50)) {
      $form['pager'] = _icl_wrapper_form_create_markup(array(
        '#type' => 'markup',
        '#value' => t('Displaying first @count items. <a href="@url">Show all @total items.</a>',
                          array('@count' => variable_get('icl_content_num_items_to_display', 50),
                                '@total' => $total,
                                '@url' => _icl_wrapper_url(_icl_wrapper_get_root_menu('translation-management/dashboard'), array('query' => 'show_all=1'))))
      ));
    }
  }
  
  $form['word_count'] = _icl_wrapper_form_create_markup(array('#type' => 'markup', '#value' => ''));
  $total_words = 0;
  foreach ($form['nodes']['words'] as $word_count) {
    $total_words += (int)$word_count['#value'];
  }
  $form['word_count']['#value'] = t('<strong>*</strong> Estimated total word count = @total_words<span id="icl_selected_word_count"></span>', array('@total_words' => $total_words));

  $form['action'] = icl_content_dashboard_action_form($form);
  // A small hack to include the CSS and JS
  $form ['#validate'] [] = 'icl_content_dashboard_add_js';
  icl_content_dashboard_add_js ($form);

  if (isset($_GET['nid'])) {
    // remove the top support message
    unset($form['icl_support']);
  }

  return $form;
}

function icl_content_dismiss_warning() {
  if ($_POST['command'] == 'dismiss_all') {
    variable_set('icl_dismiss_title_warning', TRUE);
  }

  if ($_POST['command'] == 'dismiss_type') {
    variable_set('icl_dismiss_title_warning_type_'.$_POST['type'], TRUE);
  }
}

function _icl_content_add_translation_service_message($form) {
  
  $translation_services = module_invoke_all('translation_service');

  if (sizeof($translation_services) > 0) {
    $data = array();
    foreach ($translation_services as $module => $service) {
      if (module_hook($module, 'translation_dashboard_help_form')) {
        $message = module_invoke($module, 'translation_dashboard_help_form');
        if ($message != NULL) {
          if (isset($service['more_info_url'])) {
            $data[$service['name']] = '<a href="' . $service['more_info_url'][0]. '"><img src="' . $service['logo_small'] . '"></a><br />' . $message;            
          } else {
            $data[$service['name']] = '<img src="' . $service['logo_small'] . '"><br />' . $message;
          }
        }
      }
    }      
    if (sizeof($data) > 0) {
      $form['translation_services_help'] = array (
        '#type' => 'fieldset', 
        '#title' => t ( 'Translation Services' ), 
        '#collapsible' => true,
        '#collapsed' => true);
      
      foreach ($data as $name => $message) {
        $form['translation_services_help']['translation_services_help_' . $name] = _icl_wrapper_form_create_markup(array(
          '#type' => 'markup',
          '#prefix' => '<div>', 
          '#suffix' => '</div><hr /><br />', 
          '#value' => $message,
          ));
      }
    }
  }

  
  return $form;
}

function icl_content_dashboard_add_title_warning($form) {
  global $base_url;
  
  $warning = array();

  if (!variable_get('icl_dismiss_title_warning', FALSE)) {
    
    $query = _icl_wrapper_db_query("SELECT * FROM {node_type}");
    while($result = db_fetch_object($query)) {
  
      if (!variable_get('icl_dismiss_title_warning_type_'. $result->type, FALSE)) {
        $enabled = variable_get('language_content_type_'. $result->type, 0);
        if ($enabled == 2) {
          $translate_fields = variable_get ( 'icl_content_node_type_fields', array ( $result->type => array () ) );
          $translate_fields = isset($translate_fields[$result->type]) ? $translate_fields[$result->type] : array();
          //if (is_array($translate_fields) && !in_array('link_title', $translate_fields)) {
          if (empty($translate_fields)) {
            $link = _icl_wrapper_url(_icl_wrapper_get_drupal_menu('admin/content/node-type/'.str_replace('_', '-', $result->type)));
            $warning[] = '<tr id="icl_row-' . $result->type . '"><td>' . $result->type . '</td><td><a href="' . $link . '">' . t('edit') . '</a></td><td><a id="icl_menu_dismiss-' . $result->type . '" href="#">' . t('dismiss') . '</a></td></tr>';
          }
        }
      }
    }
  }
  
  $message = '';  
  if (!variable_get('icl_status_check_done', FALSE)) {
    $message .= '<img src="'.$base_url.'/misc/watchdog-warning.png">&nbsp;';
    $link = _icl_wrapper_url(_icl_wrapper_get_root_menu('translation-management/icl-check'));
    $message .= t('<b>Status check</b> - Ensure you have everything setup before sending translations. Perform a <a href="@link">Status check</a>', array('@link' => $link)) . '<br>';
  }
  
  if (sizeof($warning)) {
    $message .= '<img src="'.$base_url.'/misc/watchdog-warning.png">&nbsp;';
    $message .= t('<b>NOTE - Menu translation:</b> The following content types wont have their menus sent for translation. <a id="icl_menu_dismiss_all" href="#">dismiss all</a>') . '<br>';
    $message .= '<table><thead><tr><th>' . t('Node type') . '</th><th>' . t('Go to node type') . '</th><th>' . t('Dismiss warning') . '</th></tr></thead><tbody>';
    $message = $message . implode('', $warning) . '</tbody></table>';
  }
  
  if ($message != '') {
    $form['menu_title_warning_message'] = _icl_wrapper_form_create_markup(array(
      '#type' => 'markup',
      '#prefix' => '<div id="icl_menu_warning" class="icl_cyan_box">', 
      '#suffix' => '</div>', 
      '#value' => $message,
      ));
  }  
  
  
  return $form;
}

function icl_content_dashboard_add_js($form) {
  //foreach($form['action']['operations'] as $key => $value) {
    //if (strpos($key, 'no_translator_') === 0) {
        
      $js = drupal_get_js();
      if (strpos($js, 'icl_dashboard.js') === FALSE) {
        
        // add a call to refresh the the icanlocalize have_translator states for languages.
        $ican_url = _icl_wrapper_url('icl_core/refresh');
        $ican_dismiss_warning_url = _icl_wrapper_url('icl_content_type/dismiss_warning');
        
        drupal_add_js(
                      array('ican_fetch' =>
                            array('ican_url' => $ican_url,
                                'ican_dismiss_warning_url' => $ican_dismiss_warning_url)),
                            'setting');
        drupal_add_js(
                      array('ican_ajax' =>
                            array('ican_dismiss_warning_url' => $ican_dismiss_warning_url)),
                            'setting');
        drupal_add_js(
                      array('ican_word_count' =>
                            array('ican_word_count_url' => _icl_wrapper_url('icl_content/word_count'))),
                            'setting');
        drupal_add_js ( drupal_get_path ( 'module', 'icl_content' ) . '/js/icl_dashboard.js' );
        drupal_add_js ( drupal_get_path ( 'module', 'icl_core' ) . '/js/icl_reminders.js' );
      }
      return;
    //}
  //}
}

/**
 * Enter description here...
 *
 * @return unknown
 */
function _icl_content_translatable_node_types() {
  if (module_exists('content')) {
    $node_types = array_keys(content_types());
  } else {
    $node_types = array_keys(_icl_wrapper_node_get_types());
  }

  foreach ($node_types as $key => $type) {
    $translatable = variable_get('language_content_type_'.$type, false);
    if (!$translatable) {
      unset($node_types[$key]);
    }
  }
  
  return $node_types;
}

/**
 * Helper to set the default_value for the form.
 *
 * @param unknown_type $key
 * @param unknown_type $default
 * @return unknown
 */
function _icl_content_default_value($key, $default) {
  global $icl_content_dashboard_filter;
  
  if (isset($icl_content_dashboard_filter[$key])) {
    return $icl_content_dashboard_filter[$key];
  }
  else if (isset($_SESSION['icl_dashboard_filter'][$key])) {
    return $_SESSION['icl_dashboard_filter'][$key];    
  }
  else {
    return $default;
  }
}

/**
 * Enter description here...
 *
 * @param unknown_type $form
 */
function theme_icl_content_dashboard_nodes($form) {
  
  global $base_url;

  if (defined('ICL_D7')) {
    $form = $form['form'];
  }
  
  drupal_add_css(drupal_get_path('module', 'icl_content').'/css/dashboard.css');
  
  $form_update_output = drupal_render($form['auto_update']);
  
  $has_posts = count(element_children($form['title'])) > 0;
  $select_header = $has_posts ? _icl_wrapper_theme('table_select_header_cell') : '';
  //$header = array($select_header, t('Title'), t('Type'), t('Status'), t('Translation'));
  $languages = _icl_content_dashboard_table_languages();
  $header = array($select_header, t('Title'), t('Type'), t('Status'), t('Words*'), $languages['flags']);
  
  if ($has_posts) {
    foreach (element_children($form['title']) as $key) {
      $row = array();
      if (array_key_exists($key, $form['nodes']['#default_value'])) {
        // Check the checkbox.
        // ????Why doesn't drupal do this????
        $form['nodes'][$key]['#value'] = 1;
      }
      $row[] = drupal_render(_icl_wrapper_form_create_markup($form['nodes'][$key]));
      $row[] = drupal_render(_icl_wrapper_form_create_markup($form['title'][$key]));
      $row[] = drupal_render(_icl_wrapper_form_create_markup($form['type'][$key]));
      $row[] = drupal_render(_icl_wrapper_form_create_markup($form['status'][$key]));
      $form['words'][$key]['#value'] = '<div id="' . $key . '-words">' . $form['words'][$key]['#value'] . '</div>';
      $row[] = drupal_render(_icl_wrapper_form_create_markup($form['words'][$key]));
      $row[] = drupal_render(_icl_wrapper_form_create_markup(_icl_content_dasboard_table_status($languages['list'], $form['nodes'][$key], $form['#content'])));
      $rows[] = $row;
      
    }
    
  }
  else {
    $rows[] = array(array('data' => t('No content available.'), 'colspan' => '6'));
  }
  
  $output = _icl_wrapper_theme('table', array('header' => $header, 'rows' => $rows));
  
  unset($form['#content']);
  
  // Show/hide legend
  global $user;
  $temp = variable_get('icl_content_dashboard_hide_legend', array());
  if (isset($temp[$user->uid]) && $temp[$user->uid]) {
    $hide_legend_style = ' style="display:none;"';
    $hide_legend_link_txt = t('Show status keys');
  }
  else {
    $hide_legend_style = '';
    $hide_legend_link_txt = t('Hide status keys');
  }
  
  $hide_legend_link = '<a href="javascript:void(0);" class="icl_dashboard_hide_legend_link" title="' . $hide_legend_link_txt . '"' . $hide_legend_style . '>' . $hide_legend_link_txt . '</a>';
  
  $other_legend = '';
  $other_keys = module_invoke_all('get_dashboard_status_keys');
  foreach ($other_keys as $keys) {
    if (isset($keys['icon']) && isset($keys['text'])) {
      $other_legend .= '
<div style="width: 200px; float: left;">
  <img src="' . $keys['icon'] . '" alt="' . $keys['text'] . '" /> ' . $keys['text'] . '
</div>';

    }
  }
  
                                  
  
  $legend = '

<div id="icl_dashboard_legend" class="icl_cyan_box"' . $hide_legend_style . '>

' . $hide_legend_link . '

<div style="width: 200px; float: left;">
  <img src="' . $base_url . '/' . drupal_get_path('module', 'icl_core') . '/images/RO-Mx1-16_check-boxed-green-tail.png" alt="' . t('Translated') . '" /> ' . t('Translation complete') . '
</div>

<div style="width: 200px; float: left;">
  <img src="' . $base_url . '/' . drupal_get_path('module', 'icl_core') . '/images/RO-Mx1-16_arrow-round-open.png" alt="' . t('Translation needs update') . '" /> ' . t('Translation needs update') . '
</div>

<div style="width: 200px; float: left; clear: both;">
  <img src="' . $base_url . '/' . drupal_get_path('module', 'icl_core') . '/images/RO-Mx1-16_warning.png" alt="' . t('Not translated') . '" /> ' . t('Not translated') . '
</div>

<div style="width: 200px; float: left;">
  <img src="' . $base_url . '/' . drupal_get_path('module', 'icl_core') . '/images/RO-Mx1-16_progress.png" alt="' . t('Translation in progress') . '" /> ' . t('Translation in progress') . '
</div>

' . $other_legend . '

<div style="width: 400px; clear: both;">
  <img src="' . $base_url . '/' . drupal_get_path('module', 'icl_core') . '/images/RO-Mx1-16_circle-help-3.png" alt="' . t('Translated - Status verification required') . '" /> ' . t('Translated - Status verification required') . '
</div>

</div>';
  
  return $form_update_output . $legend . $output;
}

function _icl_content_get_review_languages() {
  $languages = array();
  $languages[] = t ('All');

  $langs = _icl_core_available_targets();
  
  foreach($langs as $code => $lang) {
    $languages[$code] = icl_core_get_drupal_language_name($code);
  }
  return $languages;
}

function icl_content_translation_review() {
  $form = array();
  
  $form = icl_core_add_reminders($form);
  icl_core_add_thickbox();

  $form['icl_support'] =  _icl_wrapper_form_create_markup(array(
    '#type' => 'markup',
    '#prefix' => '<div class="icl_cyan_box">',
    '#suffix' => '</div>',
    '#value' => icl_core_get_icl_support(),
  ));
  
  $form['message'] = array(
    '#type' => 'fieldset',
    '#title' => t('Completed Translations'),
    '#value' => "<br>" . t('The following translations have been received and are waiting for review'),
  );

  $languages = _icl_content_get_review_languages();
  
  $default = _icl_content_review_default_value('review_language', array_shift(array_keys($languages)));
  if ($default == 'All') {
    // handle language neutral setting
    $default = '0';
  }
  $form['message']['review_language'] = array(
    '#title' => t('Show documents in'),
    '#type' => 'radios',    
    '#options' => $languages,
    '#default_value' => $default,
  );
  $form['message']['op'] = array(
    '#value' => t('Update display'),
    '#type' => 'submit',
    '#submit' => array('icl_content_review_filter_form_submit'),
  );

  $form['nodes'] = icl_content_dashboard_nodes_form(FALSE);
  $form['pager'] = array('#value' => _icl_wrapper_theme('pager', array('tags' => NULL, 'limit' => 10, 'element' => 0)));
  $form['pager'] = array('#value' => _icl_wrapper_theme('pager', array('tags' => NULL, 'limit' => 3)));

  return $form;
}

/**
 * Enter description here...
 *
 */
function icl_content_review_filter_form_submit($form, &$form_state) {
  global $icl_content_review_filter;
  
  $icl_content_review_filter = array(
    'review_language' => $form_state['values']['review_language'],
  );
  if ($icl_content_review_filter['review_language'] == '0') {
    // handle all language setting
    $icl_content_dashboard_filter['review_language'] = '';
  }
  $form_state['rebuild'] = TRUE;
}

function _icl_content_review_default_value($key, $default) {
  global $icl_content_review_filter;
  
  if (isset($icl_content_review_filter[$key])) {
    return $icl_content_review_filter[$key];
  }
  else if (isset($_GET[$key])) {
    return $_GET[$key];    
  }
  else {
    return $default;
  }
}

function icl_content_review_build_filter_query() {

  $lang = _icl_content_review_default_value('review_language', array_shift( array_keys(_icl_content_get_review_languages()) ));
  
  $node_types = _icl_content_translatable_node_types();
  
  $filter = array();  
  
  $filter['join'] .= ' INNER JOIN {icl_content_status} cs ON n.tnid = cs.nid 
                       INNER JOIN {icl_core_status} c ON c.rid = cs.rid';
  $filter['where'] .= " AND c.status = " . ICL_STATUS_SUCCESSFUL;
  
  if ($lang != "0") {
    $filter['where'] .= " AND n.language = '" . $lang . "'";
  }
  $sql  = "SELECT 
             distinct n.nid, 
             n.title, 
             n.type, 
             n.language, 
             n.status,
             n.tnid
           FROM 
             {node} n"
           .$filter['join'].
          " WHERE
             n.type IN ('".implode("', '", $node_types)."') AND 
             n.tnid != n.nid AND
             n.status = 0"
           .$filter['where'];
  
  $count_query = preg_replace(array('/SELECT.*?FROM /As', '/ORDER BY .*/'), array('SELECT COUNT(distinct n.nid) FROM ', ''), $sql);
  
  return pager_query($sql, 10, 0, $count_query);
}

 /**
 * Displays flags in dashboard translation table.
 */
function _icl_content_dashboard_table_languages() {
  
  global $base_url;
  global $icl_content_dashboard_filter;
  
  $list = language_list('enabled');
  
  if (isset($icl_content_dashboard_filter['language'])) {
    unset($list[1][$icl_content_dashboard_filter['language']]);
  }
  else {
    unset($list[1][language_default()->language]);
  }
  
  $return = array('list' => array());
  $flags = array();
  
  foreach ($list[1] as $language) {
    if (isset($icl_content_dashboard_filter['to']) && !empty($icl_content_dashboard_filter['to']) && $language->language != $icl_content_dashboard_filter['to']) {
      continue;
    }
    $return['list'][$language->name] = $language->language;
    $flag_file = str_replace('icl_content', 'icl_core', dirname(__FILE__)) . '/images/flags/' . $language->language . '.png';
    if (file_exists($flag_file)) {
      $flags[] = '<img src="' . $base_url . '/' . drupal_get_path('module', 'icl_core') . '/images/flags/' . $language->language . '.png" class="icl_dashboard_table_flag" alt="' . $language->name . '" title="' . $language->name . '" />';
    } else {
      $flags[] = '<img src="' . $base_url . '/' . drupal_get_path('module', 'icl_core') . '/images/flags/none.png" class="icl_dashboard_table_flag" alt="' . $language->name . '" title="' . $language->name . '" />';
    }
  }
  $width = count($flags) * 30;
  $return['flags'] = '<div style="width:' . $width . 'px;">' . join('', $flags) . '</div>';
  return $return;
}

 /**
 * Displays translation status for each language per content.
 */
function _icl_content_dasboard_table_status($list, $node, $contents) {
  global $base_url,$icl_content_dashboard_filter;
  
  // Determine type
  if (strpos($node['#return_value'], 'block-') === 0) {
    $type = 'block';
  } else if (strpos($node['#return_value'], 'contact-') === 0) {
    $type = 'contact_form';
  } else if (strpos($node['#return_value'], 'string-') === 0) {
    $type = 'string';
  } else {
    $type = 'node';
  }
  // Get status
  foreach ($contents as $item) {
    if ($item['id'] == $node['#return_value']) {
      break;
    }
  }
  $status = _icl_content_dasboard_check_status($item);
  $value = array();
  
  foreach ($list as $name => $language) {
    
    $link = '<a href="' . _icl_wrapper_url(_icl_wrapper_get_root_menu('translation-management/translator'),
                                           array('query' => 'icl_translator_ajx_action=get_translation_job_status&amp;rid=' . $item['targets'][$language]['current_rid'] . '&amp;language=' . $language . '&amp;form_token=' . drupal_get_token('icl_dashboard_form') . '&amp;form_id=icl_dashboard_form' . '&amp;TB_iframe=true' ))  . '" class="thickbox">%s</a>';
    
    switch ($status[$language]) {
      
      case 'complete':
        $output = sprintf($link, '<img src="' . $base_url . '/' . drupal_get_path('module', 'icl_core') . '/images/RO-Mx1-16_check-boxed-green-tail.png" alt="' . t('Translated') . '" class="icl_dashboard_table_icon" />');
        break;
      
      case 'not_translated':
        $output = '<img src="' . $base_url . '/' . drupal_get_path('module', 'icl_core') . '/images/RO-Mx1-16_warning.png" class="icl_dashboard_table_icon" alt="' . t('Not translated') . '" />';
        break;

      case 'update':
        $output = sprintf($link, '<img src="' . $base_url . '/' . drupal_get_path('module', 'icl_core') . '/images/RO-Mx1-16_arrow-round-open.png" alt="' . t('Translation needs update') . '" class="icl_dashboard_table_icon" />');
        break;

      case 'failed':
        $output = sprintf($link, '<img src="' . $base_url . '/' . drupal_get_path('module', 'icl_core') . '/images/RO-Mx1-16_error_warning.png" alt="' . t('Translation failed') . '" class="icl_dashboard_table_icon" />');
        break;
      
      case 'verification':
        $output = '<a href="#TB_inline?height=200&amp;width=320&amp;inlineId=verification' . $type . $node['#return_value'] . '&amp;modal=true" class="thickbox"><img src="' . $base_url . '/' . drupal_get_path('module', 'icl_core') . '/images/RO-Mx1-16_circle-help-3.png" alt="' . t('Translated - Status verification required') . '" class="icl_dashboard_table_icon" /></a>

<div id="verification'. $type . $node['#return_value'] . '" style="display:none;">

<p>What is the status of the ' . $name . ' translation?</p>

<input type="hidden" name="id" value="' . $node['#return_value'] . '" />
<input type="hidden" name="type" value="' . $type . '" />

<input type="submit" name="verify" value="' . t('Translation is up-to-date') . '" onClick="window.location = \'' . _icl_wrapper_url(_icl_wrapper_get_drupal_menu('admin/content/translation-management/dashboard'), array('query' => array('verify' => 'correct', 'id' => $node['#return_value'], 'type' => $type))) .'\'" />

<br /><br />

<input type="submit" name="verify" value="' . t('Translation needs update') . '" onClick="window.location = \'' . _icl_wrapper_url(_icl_wrapper_get_drupal_menu('admin/content/translation-management/dashboard'), array('query' => array('verify' => 'update', 'id' => $node['#return_value'], 'type' => $type))) .'\'" />

<br /><br />
<input type="button" name="cancel" value="' . t('Cancel') . '" onClick="tb_remove(); return false;" />

</div>';
        break;
      
      default: //PROGRESS
         $output = sprintf($link, '<img src="' . $base_url . '/' . drupal_get_path('module', 'icl_core') . '/images/RO-Mx1-16_progress.png" alt="' . t('Translation in progress') . '" class="icl_dashboard_table_icon" />');
    }

    $filtered_output = module_invoke_all('translation_dashboard_filter_node_icon', $item['id'], $language, $output);
    if (!empty($filtered_output)) {
      $value[] = $filtered_output[0];
    } else {
      $value[] = $output;
    }
  }
  
  $return['#value'] = join('', $value);
  
  return $return;
}

 /**
 * Checks translation status.
 * @todo Process blocks and forms
 */
function _icl_content_dasboard_check_status($item) {
  $status = array();
  foreach ($item['targets'] as $lang => $lang_status) {
    if ($lang_status['current_rid'] > 0) {
      if ($lang_status['rid_status'] == ICL_STATUS_SUCCESSFUL) {
        if ($lang_status['needs_update'] == 1) {
          $status[$lang] = 'update';
        } else {
          $status[$lang] = 'complete';
        }
      } else if($lang_status['rid_status'] == ICL_STATUS_FAILED) {
        $status[$lang] = 'failed';
      } else {
        $status[$lang] = 'in_progress';
      }
      
    } else {
      if ($lang_status['translated'] == 1) {
        // not handled by our system yet
        $status[$lang] = 'verification';
      } else {
        $status[$lang] = 'not_translated';
      }
    }
  }
  
  return $status;
}

 /**
 * Compares md5 to see if translation needs update.
 */
function _icl_content_dashboard_compare_md5($type, $id, $rid) {
  
  switch ($type) {
    
    case 'block':
      $data = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT md5 FROM {icl_block} WHERE bid = %d", $id));
      break;
    
    case 'contact_form':
      $data = icl_content_calculate_stardard_contact_form_md5();
      break;
    
    case 'node':
      $data = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT md5 FROM {icl_node} WHERE nid = %d", $id));
      break;
  }
  $md5 = _icl_content_get_md5_for_rid($type, $rid);
  return ($md5 == $data);
}

 /**
 * Updates previously translated contents (submitted by user).
 * @see _icl_dasboard_update_previously_translated_node()
 * @todo Process blocks and forms
 */
function _icl_dasboard_update_previously_translated() {
  
  switch ($_GET['type']) {
    
    case 'node':
      if ($_GET['verify'] == 'update') {
        $update = TRUE;
      } else {
        $update = FALSE;
      }
      $node = node_load($_GET['id']);
      if ($translations = translation_node_get_translations($node->tnid)) {
        _icl_dasboard_update_previously_translated_node($node, $translations, $update);
      }
      break;
    
    case 'block':
      break;
    
    case 'contact_form':
      break;
  }
  
  _icl_wrapper_drupal_goto(_icl_wrapper_get_root_menu('translation-management/dashboard'));
  // @todo Cleanup
  //header("Location: /admin/content/translation-management/dashboard");
}

 /**
 * Returns auto-update form.
 * @see icl_content_dashboard_nodes_form()
 */
function _icl_dashboard_get_auto_update_form() {
  $form = array(
    '#type' => 'fieldset',
    '#title' => t('Auto update'),
    '#attributes' => _icl_wrapper_form_create_attributes(array('id' => 'icl_auto_update')),
    //'#access' => false,
  );
  
  $form['intro'] = _icl_wrapper_form_create_markup(array('#type' => 'markup', '#value' => t('<p>Some of your content is already translated.</p>

<p>If the translation is OK you can mark it as \'Complete\' and further changes to the content will be detected so that translations can be kept up to date.</p>

<p>If the translation needs updating you can mark it as \'Update needed\'. You will then be able to send content that needs updating for translation.</p>')));
  
  $form['auto_update'] = array(
    '#title' => t('Do you want to set all current content to'),
    '#type' => 'radios',
    '#options' => array(1 => t('This translation is OK'), 2 => t('Update needed'), 0 => t('Don\'t update automatically *'), 3 => t('Don\'t show this message again')),
    '#default_value' => variable_get('icl_dashboard_update_previous', 0),
  );
  
  $form['note'] = _icl_wrapper_form_create_markup(array('#type' => 'markup', '#value' => t('<p>* You can also set the state for individual content</p>')));
  
  $form['save'] = array(
        '#type' => 'submit',
        '#submit' => array('icl_content_dashboard_auto_update_submit'),
        '#value' => t('Set content state'),
  );
  
  return $form;
}

 /**
 * Process auto-update form.
 * @todo Process blocks and forms
 */
function icl_content_dashboard_auto_update_submit($form) {
  variable_set('icl_dashboard_update_previous', $form['#post']['auto_update']);
  if ($form['#post']['auto_update'] == 0 || $form['#post']['auto_update'] == 3) {
    return;
  }
  // Process nodes
  // @todo Check query (fetch only nodes in default lang)
  $q = _icl_wrapper_db_query("SELECT * FROM {node} WHERE language='%s'", language_default()->language);
  $nodes = array();
  while ($r = db_fetch_object($q)) {
    $nodes[] = $r;
  }
  
  foreach ($nodes as $node) {
    if ($translations = translation_node_get_translations($node->tnid)) {
      if ($form['#post']['auto_update'] == 2) {
        $update = TRUE;
      }
      else {
        $update = FALSE;
      }
      _icl_dasboard_update_previously_translated_node($node, $translations, $update);
    }
  }
}

 /**
 * Updates single previously translated node.
 */
function _icl_dasboard_update_previously_translated_node($node, $translations = array(), $update = FALSE) {
  foreach ($translations as $code => $translation) {
    if ($translation->nid == $node->id) {
      $default = $code;
      continue;
    }
    $data = _icl_content_extract_node($node);
    $node_data = icl_content_calculate_md5_and_words_from_data($data);
    $md5 = $node_data['md5'];
    icl_content_save_node_md5_and_words($node, $md5, $node_data['words']);
    
    if ($update) {
      $md5 = md5($data . '-update');
    }
    
    $rid = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT max( rid ) FROM {icl_core_status}")) + 1;
    
    _icl_wrapper_db_query("INSERT INTO {icl_content_status} (rid, nid, timestamp, md5) VALUES (%d, %d, %d, '%s')", $rid, $node->nid, time(), $md5);
    
    _icl_wrapper_db_query("INSERT INTO {icl_core_status} (rid, module, origin, target, status) VALUES (%d, '%s', '%s', '%s', %d)", $rid, 'icl_content', $default, $translation->language, 6);
  }
}