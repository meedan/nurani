<?php
/*
 * $Id: icl_content.links.inc
 * 
 * @file ICanLocalize translated links handling
 */

/**
 * get the link paths in the body of the content
 */

/*
 * admin/content/icl-link-translation page
 */
 function icl_content_link_translations() {
   $form = array();
  
  drupal_add_css(drupal_get_path('module', 'icl_core').'/css/icl_core.css');
  drupal_add_css(drupal_get_path('module', 'icl_content').'/css/image_replace.css');
  drupal_add_css(drupal_get_path('module', 'icl_content').'/css/dashboard.css');
  
  drupal_add_js(drupal_get_path('module', 'icl_content') . '/js/icl_link_replace.js');
  
  $ican_link_replace_url = _icl_wrapper_url('icl_content/icl_link_replace');
  drupal_add_js(array('ican_ajax' =>
                      array('ican_link_replace_url' => $ican_link_replace_url)),
                      'setting');
  drupal_add_js(array('ican_ajax' =>
                      array('ican_edit_text' => t('edit'),
                            'ican_add_text' => t('add'),
                            'ican_link_token' => drupal_get_token('ican_link_token'))),
                      'setting');

  $form = icl_core_add_reminders($form);
  icl_core_add_thickbox();

  $form ['icl_link_replace_internal'] = array (
    '#type' => 'fieldset', 
    '#title' => t ( '<b>Automatic Internal Link Replacement</b>' ), 
    '#collapsible' => false );

  $form['icl_link_replace_internal']['icl_link_replace_internal'] = array(
    '#type' => 'radios',    
    '#options' => array(
      'replace' => t('Replace links so they point to translations if available'),
      'none' => t('Don\'t convert'),
    ),
    '#default_value' => variable_get('icl_link_replace_internal', 'none'),
    '#description' => t('The alternative links will only be used if they exist. Otherwise link to the original content will be used.'),
  );

  $form ['icl_link_replace_external'] = array (
    '#type' => 'fieldset', 
    '#title' => t ( '<b>Automatic External Link Replacement</b>' ), 
    '#collapsible' => false );

  $form['icl_link_replace_external']['icl_link_replace_external'] = array(
    '#title' => t('Select the method to use to select alternative links for translated content'),
    '#type' => 'radios',    
    '#options' => array(
      'override' => t('Use replacement from override table'),
      'none' => t('None - I\'ll set them manually'),
    ),
    '#default_value' => variable_get('icl_link_replace_external', 'none'),
  );

  $form['icl_link_replace_external']['icl_link_replace_external_check'] = array(
    '#type' => 'checkbox',
    '#title' => t('Make sure external links exist before replacing'),
    '#default_value' => variable_get('icl_link_replace_external_check', FALSE)
  );

  $form ['icanlocalize_link_scan'] = array (
    '#type' => 'fieldset', 
    '#title' => t ( '<b>Link Replacement Overrides</b>' ), 
    '#collapsible' => false );

  $form ['icanlocalize_link_scan'] ['message'] = _icl_wrapper_form_create_markup(array (
    '#type' => 'markup',
    '#value' => t("Search nodes and blocks for any links requiring translation: ")
  ));

  $form['icanlocalize_link_scan']['Scan'] = array(
    '#type' => 'submit',
    '#submit' => array('icl_content_links_scan_submit'),
    '#value' => t('Scan for new links')
  );

  $form ['icanlocalize_link_scan'] ['message_2'] = _icl_wrapper_form_create_markup(array (
    '#type' => 'markup',
    '#value' => t("Use this table to override the automatic link replacement method and enter different replacement link to be used in translated content."),
    '#prefix' => '<br /><br />',
    '#suffix' => '<br />',
   ));

  $form ['icanlocalize_link_scan']['message_3'] = _icl_wrapper_form_create_markup(array (
    '#type' => 'markup',
    '#value' => t("* Your changes have not been applied to the translated content yet."),
    '#prefix' => '<div class="warning" id="icl_changes_message_2" style="display:none">',
    '#suffix' => '<br /></div>',
  ));

  $form ['icanlocalize_link_scan']['link_table'] = icl_content_link_form_table();

  $form ['icanlocalize_link_scan']['throbber'] = _icl_wrapper_form_create_markup(array(
    '#type' => 'markup',
    '#prefix' => '<div id="icl_throbber" style="display:none"><div class="icl_throbber">',
    '#suffix' => '</div></div>',
    '#value' => ' ',
  ));

  $form ['message_3'] = _icl_wrapper_form_create_markup(array (
    '#type' => 'markup',
    '#value' => t("* Your changes have not been applied to the translated content yet."),
    '#prefix' => '<div class="warning" id="icl_changes_message" style="display:none">',
    '#suffix' => '<br /></div>',
  ));

  $form ['action'] = array(
    '#type' => 'submit',
    '#submit' => array('icl_content_links_submit'),
    '#value' => t('Apply link replacement to translated content'),
  );

  return $form;
 }


/*
 * admin/content/icl-link-translation page edit table
 */
 function icl_content_link_form_table() {
  
  $clean_url = variable_get('clean_url', 1);
  $language_negotiation = variable_get('language_negotiation', 'prefix');
  
  $languages = language_list('enabled');
  $languages = $languages[1];
  $source_lang = language_default()->language;
  
  $form = array(
    'id' => array(),
    $source_lang => array(),
  );
  foreach($languages as $lang) {
    if ($lang->language != $source_lang) {
      $form[$lang->language] = array();
    }
  }
  
  $form['#theme'] = 'icl_content_links';
  
  $links = array();
  $source_lang = language_default()->language;
  $langs_targets = _icl_core_available_targets_for_origin ( $source_lang );

  $query = pager_query("SELECT * FROM {icl_link_status} WHERE tnid=id OR tnid=0", icl_content_link_table_count());
  
  while ( $request = db_fetch_object ( $query ) ) {
    $id = $request->id;
    $links[$id] = $id;
    $form['id'][$id] = array('#value' => $id);
    $form[$request->language][$id] = array('#value' => '<b>' . $request->data . '</b>');
    
    // do we have translations.
    $translations = icl_content_links_get_translations($id);
    foreach ($languages as $lang) {
      if ($lang->language != $request->language) {
        
        $language_prefix = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT prefix FROM {languages} WHERE language='%s'", $lang->language));
        $language_domain = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT domain FROM {languages} WHERE language='%s'", $lang->language));
        
        $control_id = $id . '_' . $lang->language;
        
        if (isset($translations[$lang->language])) {
          // we have a translation
          $value = $translations[$lang->language]->data;
          $form[$lang->language][$id] = array('#value' => '<a class="icl_edit_link" id="icl_add_edit_' . $control_id . '"></a>');
        } else {
          // we don't have a translation.
          // use the selected replacement menthod
          $value = _icl_content_link_get_replacement_name($request->data, $lang->language, $source_lang, $clean_url, $language_negotiation, $language_prefix, $language_domain);
        
          $form[$lang->language][$id] = array('#value' => '<a class="icl_add_link" id="icl_add_edit_' . $control_id . '"></a>');
        }
        $form[$lang->language][$id]['#value'] = '<div>' . $form[$lang->language][$id]['#value'] . '</div>';
        $form[$lang->language][$id]['#value'] .= '<div class="icl_edit" id="icl_edit_' . $control_id . '" style="display:none;">';
        $form[$lang->language][$id]['#value'] .= '<input type="text" value="' . $value . '" id="icl_text_' . $control_id . '" style="width:300px;"><br />';
        $form[$lang->language][$id]['#value'] .= '<input class="icl_save" type="button" value="' . t('Save') . '" id="icl_save_' . $control_id . '" >';
        if (isset($translations[$lang->language])) {
          // we have a translation, add a delete button
          $form[$lang->language][$id]['#value'] .= '<input class="icl_delete" type="button" value="' . t('Delete') . '" id="icl_delete_' . $control_id . '" >';
        } else {
          // we don't have a translation, add a delete button hidden
          $form[$lang->language][$id]['#value'] .= '<input style="display:none" class="icl_delete" type="button" value="' . t('Delete') . '" id="icl_delete_' . $control_id . '" >';
        }
        $form[$lang->language][$id]['#value'] .= '<input class="icl_cancel" type="button" value="' . t('Cancel') . '" id="icl_cancel_' . $control_id . '" >';
        $form[$lang->language][$id]['#value'] .= '</div>';
        $form[$lang->language][$id] = _icl_wrapper_form_create_markup($form[$lang->language][$id]);
      }
    }
    
  }
  
  
  $form['links'] = array('#type' => 'checkboxes', '#options' => $links, '#default_value' => array_keys($links));
 
  return $form;
}

/*
* called by 
* icl_content_link_form_table()
* theme_icl_content_links()
*/
function icl_content_link_table_count() {
  return 30;
}

/*
* called by icl_content_link_form_table()
*/
function icl_content_links_get_translations($id) {
  $query = _icl_wrapper_db_query("SELECT id, language, data FROM {icl_link_status} WHERE tnid=%d AND id<>tnid", $id);
  
  $ids = array();
  while ( $request = db_fetch_object ( $query ) ) {
    $ids[$request->language] = $request;
  }
  
  return $ids;
  
}

/*
* called by icl_content_link_form_table() $form['#theme'] = 'icl_content_links';
* registred at icl_content_theme() icl_content.module
*/
function theme_icl_content_links($form) {

  $languages = language_list('enabled');
  $languages = $languages[1];
  $source_lang = language_default()->language;
  
  $header = array($languages[$source_lang]->name);
  foreach($languages as $lang) {
    if ($lang->language != $source_lang) {
      $header[] = $lang->name;
    }
  }
  
  
  foreach (element_children($form['id']) as $key) {
    $row = array();      
    $row[] = drupal_render($form[$source_lang][$key]);
    foreach($languages as $lang) {
      if ($lang->language != $source_lang) {
        $row[] = drupal_render($form[$lang->language][$key]);
      }
    }
    $rows[] = $row;
  }
  
  $output = _icl_wrapper_theme('table', array('header' => $header, 'rows' => $rows));
  $output .= _icl_wrapper_theme('pager', array('tags' => icl_content_link_table_count()));
  return $output;
}




/*
* SUBMIT ACTION
* 
* 
* 
*/

function icl_content_links_submit($form, &$form_state) {

  $nodes_effected = 0;
  
  $file_status = array();
  
  $link_replace_internal = $form_state['values']['icl_link_replace_internal'];
  variable_set('icl_link_replace_internal', $link_replace_internal);
  
  $link_replace_external = $form_state['values']['icl_link_replace_external'];
  variable_set('icl_link_replace_external', $link_replace_external);
  
  $link_replace_external_check = $form_state['values']['icl_link_replace_external_check'];
  variable_set('icl_link_replace_external_check', $link_replace_external_check);

  // apply the changes to all the translated nodes.
  
  $sql = "SELECT DISTINCT tnid FROM {node} WHERE nid<>tnid AND tnid <> 0";
  
  $query = _icl_wrapper_db_query( $sql);
  while ( $request = db_fetch_object ( $query ) ) {
    $nid = $request->tnid;
    $links_in_original_node = _icl_content_get_link_paths_for_node($nid);
  
  if (variable_get('icl_link_replace_external', 'none') != 'none') {
      $external_links = $links_in_original_node['external'];
    unset($links_in_original_node['external']);
      $check_external = TRUE;
    }
    
    if (sizeof($links_in_original_node) > 0) {
      
      // get all the translations.
      $sql = "SELECT DISTINCT nid FROM {node} WHERE tnid=%d and nid<>tnid";
      
      $query_2 = _icl_wrapper_db_query( $sql, $nid);
      while ( $request_2 = db_fetch_object ( $query_2 ) ) {
        $trans_nid = $request_2->nid;
        $node = node_load($trans_nid);

        $node_changed = FALSE;

        _icl_content_undo_link_replacement($node, $node_changed);

        $source_path = "node/" . $trans_nid;
        $source_path = drupal_get_path_alias($source_path);

        icl_content_apply_link_replacement($source_path,
                                            $links_in_original_node,
                                            $node,
                                            $node_changed,
                                            $file_status);
        
    if ($check_external && !empty($external_links)) {
      _icl_content_link_replace_external('node', $trans_nid, $node->body, $node->language, $node_changed, $external_links);
    }
    
        if ($node_changed) {
          if (isset($node->teaser) && $node->teaser != "") {
            $node->teaser = node_teaser($node->body);
          }
          
          node_save($node);
          
          $nodes_effected += 1;
          
        }
      
      }
    }
  }
  
  if ($nodes_effected > 0) {
    drupal_set_message(t('Alternative links were used in @count translated nodes.', array('@count' => $nodes_effected)));
  } else {
    drupal_set_message(t('No alternative links were used in any translated nodes.'));
  }
  
  // Apply to all the translatable blocks.
  
  $blocks_effected = 0;

  $table_name = _icl_wrapper_table_name('boxes');
  $sql = "SELECT b.bid, b.body FROM {" . $table_name . "} b JOIN {i18n_blocks} i18b ON b.bid=i18b.delta WHERE i18b.language=''";
  $query = _icl_wrapper_db_query( $sql);
  while ( $request = db_fetch_object ( $query ) ) {
    $bid = $request->bid;
    $lid = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT lid FROM {locales_source} WHERE source='%s' AND textgroup='blocks'", $request->body));
    if ($lid !== FALSE) {
      $links_in_block = _icl_content_get_link_paths($request->body);
      
      if (sizeof($links_in_block) > 0) {
            $sql = "SELECT language, translation FROM {locales_target} WHERE lid=%d";
            $query_2 = _icl_wrapper_db_query( $sql, $lid);
            while ( $request_2 = db_fetch_object ( $query_2 ) ) {
              $block_changed = FALSE;
              $lang = $request_2->language;
              $translation = $request_2->translation;
        
              _icl_content_undo_link_replacement_block($translation, $bid, $lang, $block_changed);
      
              icl_content_apply_link_replacement_block($links_in_block,
                                                  $translation,
                                                  $bid,
                                                  $lang,
                                                  $block_changed,
                                                  $file_status);
             
              if ($block_changed) {
                // save the changes.
                icl_content_update_locale_translation($lid, $lang, $translation);
                $blocks_effected += 1;
              }
            }
          }
    }
  }    

  if ($blocks_effected > 0) {
    drupal_set_message(t('Alternative links were used in @count translated blocks.', array('@count' => $blocks_effected)));
  } else {
    drupal_set_message(t('No alternative links were used in any translated blocks.'));
  }
  
}


/*
* called by icl_content_links_submit()
*/

function _icl_content_get_link_paths_for_node($nid) {

  global $base_url;
  global $base_root;
  
  $link_paths = array();
  $node = node_load($nid);
  
  $source_path = "node/" . $nid;
  $source_path = drupal_get_path_alias($source_path);

  $links = _icl_content_get_link_paths($node->body);

  if (module_exists('content')) {
    $type = content_types($node->type);
    if (isset($type['fields'])) {
      foreach ($type['fields'] as $field) {
        $field_name = $field['field_name'];
        $cck_data = $node->$field_name;
        if ($cck_data) {
          foreach ($cck_data as $index => $data) {
            
            if (isset($data['value'])) {
              $links = array_merge($links, _icl_content_get_link_paths($data['value']));
            }
            
          }
        }
      }
    }
  }
  
  // if external links enabled, add links to 'external' array
  if (variable_get('icl_link_replace_external', 'none') != 'none') {
      $link_paths['external'] = array();
      $check_external = TRUE;
  }
  
  foreach ($links as $path) {
  
    $path[2] = trim($path[2]);
    if (strpos($path[2], $base_root) === 0) {
      $link_path = $path[2];
    } else {
      $link_path = resolve_url($base_url . '/' . $source_path, $path[2]);
    }
    if (strpos($link_path, $base_root) === 0) {
      if (strpos($link_path, $base_url) === 0) {
        $link_path = substr($link_path, strlen($base_url));
      } else {
        $link_path = substr($link_path, strlen($base_root));
      }
      
      $link_paths[] = array('lang' => $node->language, 'path' => $link_path);
    } else if ($check_external) { // add link to 'external' array
     $link_paths['external'][] = array('lang' => $node->language, 'path' => $link_path);
  }
  }
  
  return $link_paths;
}

function _icl_content_get_link_regex() {
  $regexp = array(
      "/<a\shref\s*=\s*([\"\']??)([^\"]*)[\"']>(.*)<\/a>/siU"
                    );

  return $regexp;
}


function _icl_content_undo_link_replacement(&$node, &$node_changed) {
  $regexp_links = _icl_content_get_link_regex();

  foreach($regexp_links as $regexp_link) {
    if (preg_match_all($regexp_link, $node->body, $matches, PREG_SET_ORDER)) {
      foreach($matches as $match) {
        $sql = "SELECT original FROM {icl_link_replacement_history} WHERE id=%d AND type='%s' AND replacement='%s' LIMIT 1";
        $old_link = _icl_wrapper_db_result(_icl_wrapper_db_query($sql, $node->nid, 'node', $match[2]));
        if ($old_link !== FALSE) {
          $old_link = str_replace($match[2], $old_link, $match[0]);
          $node->body = str_replace($match[0], $old_link, $node->body);
          $node_changed = TRUE;
        }
      }
    }
  }
  
  if (module_exists('content')) {
    $type = content_types($node->type);
    if (isset($type['fields'])) {
      foreach ($type['fields'] as $field) {
        $field_name = $field['field_name'];
        $cck_data = $node->$field_name;
        if (is_array($cck_data)) {
          foreach ($cck_data as $index => $data) {
            
            if (isset($data['value'])) {
              foreach($regexp_links as $regexp_link) {
                if (preg_match_all($regexp_link, $data['value'], $matches, PREG_SET_ORDER)) {
                  foreach($matches as $match) {
                    $sql = "SELECT original FROM {icl_link_replacement_history} WHERE id=%d AND type='%s' AND replacement='%s'";
                    $old_link = _icl_wrapper_db_result(_icl_wrapper_db_query($sql, $node->nid, 'node', $match[2]));
                    if ($old_link !== FALSE) {
                      $old_link = str_replace($match[2], $old_link, $match[0]);
                      $data['value'] = str_replace($match[0], $old_link, $data['value']);
                      $node_changed = TRUE;
                    }
                  }
                }
              }
              $cck_data[$index] = $data;
            }
          }          
        }
        $node->$field_name = $cck_data;
      }
    }
  }
  
  
}

function icl_content_apply_link_replacement($source_path,
                                             $links_in_original_node,
                                             &$node,
                                             &$node_changed,
                                             &$file_status) {
  global $base_url;
  global $base_root;

  _icl_wrapper_db_query("DELETE FROM {icl_link_replacement_history} WHERE id=%d AND type='node'", $node->nid);
  
  $regexp_links = _icl_content_get_link_regex();
  _icl_content_apply_link_replacement_to_data($node->body,
                                                $source_path,
                                                $links_in_original_node,
                                                $node->language,
                                                $node->nid,
                                                'node',
                                                $node_changed,
                                                $file_status);

  if (module_exists('content')) {
    $type = content_types($node->type);
    if (isset($type['fields'])) {
      foreach ($type['fields'] as $field) {
        $field_name = $field['field_name'];
        $cck_data = $node->$field_name;
        if (is_array($cck_data)) {
          foreach ($cck_data as $index => $data) {
            
            if (isset($data['value'])) {
              _icl_content_apply_link_replacement_to_data($data['value'],
                                                            $source_path,
                                                            $links_in_original_node,
                                                            $node->language,
                                                            $node->nid,
                                                            'node',
                                                            $node_changed,
                                                            $file_status);
              $cck_data[$index] = $data;
  
            }
            
          }
        }
        $node->$field_name = $cck_data;
      }
    }
  }

}

function icl_content_apply_link_replacement_block($links_in_original,
                                    &$translation,
                                    $bid,
                                    $lang,
                                    &$block_changed,
                                    &$file_status) {

  _icl_wrapper_db_query("DELETE FROM {icl_link_replacement_history} WHERE id=%d AND type='%s'", $bid, 'block-'.$lang);
  
  foreach ($links_in_original as $index => $link) {
    //external
  if (_icl_content_get_block_relative_image($link[2])) {
      $link = array('lang' => 'en',
                   'path' => _icl_content_get_block_relative_image($link[2]));
      $internal_links[$index] = $link;
  } else {
    $external_links[] = array('lang' => 'en',
                   'path' => $link[2]);
  }
  }
  
  if (!empty($internal_links)) {
    _icl_content_apply_link_replacement_to_data($translation,
                                                '',
                                                $internal_links,
                                                $lang,
                                                $bid,
                                                'block-'.$lang,
                                                $block_changed,
                                                $file_status);
  }
  if (!empty($external_links) && variable_get('icl_link_replace_external', 'none') != 'none') {
  _icl_content_link_replace_external('block-'.$lang, $bid, $translation, $lang, $block_changed, $external_links);
  }
}

function _icl_content_apply_link_replacement_to_data(&$data,
                                                      $source_path,
                                                      $links_in_original,
                                                      $language,
                                                      $type_id,
                                                      $type,
                                                      &$changed,
                                                      &$file_status) {
  global $base_url;
  global $base_root;

  $regexp_links = _icl_content_get_link_regex();
  $clean_url = variable_get('clean_url', 1);
  $language_negotiation = variable_get('language_negotiation', 'prefix');
  $language_prefix = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT prefix FROM {languages} WHERE language='%s'", $language));
  $language_domain = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT domain FROM {languages} WHERE language='%s'", $language));

  foreach($regexp_links as $regexp) {
    if (preg_match_all($regexp, $data, $matches, PREG_SET_ORDER)) {
      foreach ($matches as $match) {
        if ($source_path != '') {
          $link_path = resolve_url($base_url . '/' . $source_path, $match[2]);
        } else {
          $link_path = resolve_url($base_url, $match[2]);
        }
        if (strpos($link_path, $base_url) === 0) {
          $link_path = substr($link_path, strlen($base_url));
        } else {
          $link_path = substr($link_path, strlen($base_root));
        }
    
        foreach($links_in_original as $link) {
          
          if ($link['path'] ==  $link_path) {
            // same image - use a replacement if we have one.
            
            $trans_data = FALSE;
            $original_id = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT id FROM {icl_link_status} WHERE data='%s' AND language='%s' LIMIT 1", $link['path'], $link['lang']));
            if ($original_id !== FALSE) {
              $trans_data = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT data FROM {icl_link_status} WHERE tnid=%d AND language='%s' LIMIT 1", $original_id, $language));
            }
            
            if ($trans_data === FALSE) {
              $trans_data = _icl_content_link_get_replacement_name($link['path'], $language, $link['lang'], $clean_url, $language_negotiation, $language_prefix, $language_domain);
            }
      
            $new_link = $match[0];
            $new_link = str_replace($match[2], $trans_data, $new_link);
            $data = str_replace($match[0], $new_link, $data);
            $changed = TRUE;
      
            // Check doubled
            $sql = "SELECT id FROM {icl_link_replacement_history} WHERE id = %d AND type = '%s' AND original = '%s' AND replacement = '%s' LIMIT 1";
            if (_icl_wrapper_db_result(_icl_wrapper_db_query($sql, $type_id, $type, $link_path, $trans_data))) {
              continue;
            }
      
            $sql = "INSERT INTO {icl_link_replacement_history} (id, type, original, replacement) VALUES (%d, '%s', '%s', '%s')";
            _icl_wrapper_db_query($sql, $type_id, $type, $link_path, $trans_data);
          }
        }
      }
  
    }
  }
}

function icl_content_links_scan_submit($form, &$form_state) {
  
  global $base_root;
  global $base_url;
  
  $sql = "SELECT DISTINCT tnid FROM {node} WHERE nid<>tnid AND tnid <> 0";
  
  $link_paths = array();
  
  $query = _icl_wrapper_db_query( $sql);
  while ( $request = db_fetch_object ( $query ) ) {
    $nid = $request->tnid;
    $links_in_node = _icl_content_get_link_paths_for_node($nid);
  
    $external_links = $links_in_node['external'];
  unset($links_in_node['external']);
  
    foreach($links_in_node as $link) {
      if (!in_array($link, $link_paths)) {
        $link_paths[] = $link;
        
        // add to the database.

        $sql = "SELECT * FROM {icl_link_status} WHERE type='link' AND language='%s' AND data='%s'";

        $result = _icl_wrapper_db_query( $sql, $link['lang'], $link['path'] );
        
        if (_icl_wrapper_db_result($result) === false) {
          $sql = "INSERT INTO {icl_link_status} (data, type, language) VALUES ('%s', '%s', '%s')";
          _icl_wrapper_db_query( $sql, $link['path'], 'link', $link['lang']);
        }
        
      }
    }
  
  if (!empty($external_links)) {
    foreach ($external_links as $k => $url) {
      $sql = "SELECT * FROM {icl_link_status} WHERE type='link' AND language='%s' AND data='%s'";
      $result = _icl_wrapper_db_query( $sql, $url['lang'], $url['path'] );
      if (_icl_wrapper_db_result($result) === false) {
        $sql = "INSERT INTO {icl_link_status} (data, type, language) VALUES ('%s', '%s', '%s')";
        _icl_wrapper_db_query( $sql, $url['path'], 'link', $url['lang']);
      }
    }
  }
  }
  
  // Scan for images in blocks.

  $table_name = _icl_wrapper_table_name('boxes');
  $sql = "SELECT b.body FROM {" . $table_name . "} b JOIN {i18n_blocks} i18b ON b.bid=i18b.delta WHERE i18b.language=''";
  $query = _icl_wrapper_db_query( $sql);
  while ( $request = db_fetch_object ( $query ) ) {
    $links_in_block = _icl_content_get_link_paths($request->body);
    
    foreach($links_in_block as $link) {
      
      $link_before_check = $link;
      $link = _icl_content_get_block_relative_link($link[2]);

      if ($link) {        
        $link = array('lang' => 'en', 'path' => $link);
      } else {
      $link = array('lang' => 'en', 'path' => $link_before_check[2]);
    }
        if (!in_array($link, $link_paths)) {
          $link_paths[] = $link;
          
          // add to the database.
  
          $sql = "SELECT * FROM {icl_link_status} WHERE type='link' AND language='%s' AND data='%s'";
  
          $result = _icl_wrapper_db_query( $sql, $link['lang'], $link['path'] );
          
          if (_icl_wrapper_db_result($result) === false) {
            $sql = "INSERT INTO {icl_link_status} (data, type, language) VALUES ('%s', '%s', '%s')";
            _icl_wrapper_db_query( $sql, $link['path'], 'link', $link['lang']);
          }
        }
    }
  }
  
}

function _icl_content_get_block_relative_link($link) {
  global $base_root, $base_url;
  
  $link = trim($link);
  if (strpos($link, $base_root) === 0) {
    $link_path = $link;
  } else {
    $link_path = resolve_url($base_url, $link);
  }
  if (strpos($link_path, $base_root) === 0) {
    if (strpos($link_path, $base_url) === 0) {
      $link_path = substr($link_path, strlen($base_url));
    } else {
      $link_path = substr($link_path, strlen($base_root));
    }
    return $link_path;
  } else {
    return FALSE;
  }
}

function _icl_content_link_get_replacement_name($data, $language, $original_language, $clean_url, $language_negotiation, $language_prefix, $language_domain) {
  
  // clean link
          $link['path'] = $data;
        $temp = '';
        $temp_link = '';
        $temp_prefix = '';
        $temp_add = '';
        $temp_id = '';
        $alias = '';
        
        if (strpos($link['path'], 'q=') !== FALSE) {
           parse_str(ltrim(trim($link['path'], '/'), '?'), $temp);
        if (!isset($temp['q'])) {
          return $data;
        }
        $temp_link = trim($temp['q'], '/');
        unset($temp['q']);
        $temp_add = '';
        if (!empty($temp)) {
          foreach ($temp as $k => $v) {
            $temp_add .= '&' . $k . '=' . $v;
          }
        }
        } else if ($clean_url && strpos($link['path'], '?') !== FALSE) {
          $temp = explode('?',$link['path']);
        $temp_link = trim($temp[0], '/');
        $temp_add = '?' . trim($temp[1], '/');
        } else {
          $temp_link = trim($link['path'], '/');
        }
        
        
        // check if admin link
        if (strpos($temp_link, 'admin/') === 0) {
          if ($clean_url && ($language_negotiation == 1 || $language_negotiation == 2)) {
            $temp_prefix = '/' . $language_prefix;
          } else if ($language_negotiation == 3) {
            $temp_prefix = $language_domain;
          }
          if ($clean_url) {
            $temp_link = $temp_prefix . '/' . $temp_link . $temp_add;
          } else {
            $temp_link = $temp_prefix . '/?q=' . $temp_link . $temp_add;
          }
        }
        // check if there is system link
        //else if (strpos($temp_link, 'node/') === 0) {
        else {
          // get system link
          $temp_link = drupal_get_normal_path($temp_link, $original_language);
          if (strpos($temp_link, 'node/') === FALSE) {
          return $data;
        }
          $temp_id = explode('node/', $temp_link);
          $temp_id = $temp_id[1];
          
          // check if there is translation
          $sql = "SELECT nid FROM {node} WHERE tnid=%d and nid<>tnid and language='$language'";
          if (!$temp_translation_id = _icl_wrapper_db_result(_icl_wrapper_db_query($sql, $temp_id, $language))) {
            return $data;
          }
          if ($clean_url && ($language_negotiation == 1 || $language_negotiation == 2)) {
            $temp_prefix = '/' . $language_prefix;
          } else if ($language_negotiation == 3) {
            $temp_prefix = $language_domain;
          }
          if ($clean_url) {
          if ($alias = drupal_lookup_path('alias', 'node/' . $temp_translation_id, $language)) {
            $temp_link = $temp_prefix . '/' . $alias . $temp_add;
          } else {
            $temp_link = $temp_prefix . '/node/' . $temp_translation_id . $temp_add;
          }
          } else {
            $temp_link = $temp_prefix . '/?q=node/' . $temp_translation_id . $temp_add;
          }
        }
        $trans_data = $temp_link;
        return $temp_link;
}

function _icl_content_undo_link_replacement_block(&$translation, $bid, $lang, &$block_changed) {
  $regexp_links = _icl_content_get_link_regex();

  foreach($regexp_links as $regexp_link) {
    if (preg_match_all($regexp_link, $translation, $matches, PREG_SET_ORDER)) {
      foreach($matches as $match) {
        $sql = "SELECT original FROM {icl_link_replacement_history} WHERE id=%d AND type='%s' AND replacement='%s'";
        $old_link = _icl_wrapper_db_result(_icl_wrapper_db_query($sql, $bid, 'block-'.$lang, $match[2]));
        if ($old_link !== FALSE) {
          $old_link = str_replace($match[2], $old_link, $match[0]);
          $translation = str_replace($match[0], $old_link, $translation);
          $block_changed = TRUE;
        }
      }
    }
  }
}


/*
* AJAX
*/
function icl_content_link_replace_callback() {
  global $language;
  global $base_url;
  global $base_root;

  $result = '0|0';
  
  if (isset($_POST['icl_link_cmd'])) {
    switch ($_POST['icl_link_cmd']) {
      case 'icl_link_exists':
        $file = realpath($_POST['icl_link_name']);
        
        $root_dir = realpath(".");
        
        if (file_exists($root_dir . $file)) {
          $result = '1|1';
        } else {
          $result = '1|0';
        }
        break;
       
      case 'icl_save':
        if ($_POST["ican_link_token"] == drupal_get_token("ican_link_token") ) {
          $id = $_POST["icl_id"];
          $file_name = $_POST["icl_file_name"];
          
          $parts = explode('_', $id);
          $link_id = $parts[2];
          $lang = $parts[3];
          
          $trans_id = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT id FROM {icl_link_status} WHERE tnid=%d AND language='%s'", $link_id, $lang));
          if ($trans_id !== false) {
            // update the record
            $sql = "UPDATE {icl_link_status} SET data='%s' WHERE tnid=%d AND language='%s'";
            _icl_wrapper_db_query( $sql, $file_name, $link_id, $lang);
          } else {
            // create a new record
            $sql = "INSERT INTO {icl_link_status} (data, type, language, tnid) VALUES ('%s', '%s', '%s', %d)";
            _icl_wrapper_db_query( $sql, $file_name, 'link', $lang, $link_id);
          }
          // set the tnid for the original
          $sql = "UPDATE {icl_link_status} SET tnid=id WHERE id=%d";
          _icl_wrapper_db_query( $sql, $link_id);
          
          $result = '1|1';
        }
        break;

      case 'icl_delete':
        if ($_POST["ican_link_token"] == drupal_get_token("ican_link_token") ) {
          $id = $_POST["icl_id"];
  
          $parts = explode('_', $id);
          $link_id = $parts[2];
          $lang = $parts[3];
  
          $sql = "DELETE FROM {icl_link_status} WHERE tnid=%d AND language='%s'";
          _icl_wrapper_db_query( $sql, $link_id, $lang);
  
          $result = '1|1';
        }
        break;
    }
  }
  
  echo $result;
}

/*
* Replace external links
*/

function _icl_content_link_replace_external($type, $nid, &$body, $language, &$changed, $external_links) {
  
    foreach($external_links as $link) {
      $link_preg = str_replace('/', "\/", $link['path']);
      if (preg_match_all("/<a\shref\s*=\s*([\"\']??)(".$link_preg.")[\"']>(.*)<\/a>/siU", $body, $matches, PREG_SET_ORDER)) {
        foreach ($matches as $key => $match) {
          if (!$original_id = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT id FROM {icl_link_status} WHERE data='%s' AND language='%s' LIMIT 1", $link['path'], $link['lang']))) {
                      continue;
          }
          if (!$trans_data = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT data FROM {icl_link_status} WHERE tnid=%d AND language='%s' LIMIT 1", $original_id, $language))) {
                      continue;
          }
          
          // Check if external exists exists
          if (variable_get('icl_link_replace_external_check', FALSE) && !_icl_content_link_external_check($nid, $trans_data, $link['path'], $node)) {
            continue;
          }
          
          $new_link = $match[0];
          $new_link = str_replace($match[2], $trans_data, $new_link);
          
          $body = str_replace($match[0], $new_link, $body);
          $changed = TRUE;
          // Check doubled
          $sql = "SELECT id FROM {icl_link_replacement_history} WHERE id = %d AND type = '%s' AND original = '%s' AND replacement = '%s' LIMIT 1";
          
          if (_icl_wrapper_db_result(_icl_wrapper_db_query($sql, $nid, $type, $link['path'], $trans_data))) {
            continue;
          }
          
          $sql = "INSERT INTO {icl_link_replacement_history} (id, type, original, replacement) VALUES (%d, '%s', '%s', '%s')";
          _icl_wrapper_db_query($sql, $nid, $type, $link['path'], $trans_data);
        }
      }
    }
}

function _icl_content_link_external_check($nid, $url, $original_url, $node) {
  $responses = array(400 => 'Bad Request', 403 => 'Forbidden', 404 => 'Not Found', 405 => 'Method Not Allowed', 406 => 'Not Acceptable', 408 => 'Request Time-out', 409 => 'Conflict', 410 => 'Gone', 411 => 'Length Required', 412 => 'Precondition Failed', 413 => 'Request Entity Too Large', 414 => 'Request-URI Too Large', 415 => 'Unsupported Media Type', 416 => 'Requested range not satisfiable', 417 => 'Expectation Failed',
    500 => 'Internal Server Error', 501 => 'Not Implemented', 502 => 'Bad Gateway', 503 => 'Service Unavailable', 504 => 'Gateway Time-out', 505 => 'HTTP Version not supported'
    );
  $response = _icl_wrapper_drupal_http_request($url);
  if (array_key_exists($response->code, $responses)) {
    drupal_set_message(sprintf(t('Invalid translated external link: \'%s\' -> \'%s\' (%s)'), '<a href="'.$original_url.'" target="_blank">'.$original_url.'</a>', '<a href="'.$url.'" target="_blank">'.$url.'</a>', $responses[$response->code]));
    return FALSE;
  }
  return TRUE;
}
