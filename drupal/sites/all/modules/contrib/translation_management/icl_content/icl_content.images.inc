<?php
/*
 * $Id: icl_content.images.inc
 * 
 * @file ICanLocalize translated image handling
 */

/**
 * get the paths to images in the body of the content
 */

function _icl_content_get_image_regex() {
  $regexp_images = array(
                    "/<img[^>]*?src\s*=\s*([\"\']??)([^\"]*)\".*>/siU",
                    "/<embed[^>]*?src\s*=\s*([\"\'])([^\"]*)\"[^<]*>/siU",
                    "/<object.*?<param[^>]name\s*=\s*[\"\']movie[\"\'][^>]*?value\s*=\s*([\"\'])([^\"]*)\"[^<]*>/siU",
                    );

  return $regexp_images;
}

function _icl_content_get_image_paths($body) {
  
  $regexp_images = _icl_content_get_image_regex();
  
  $links = array();
  
  if (is_string($body)) {
    foreach($regexp_images as $regexp) {
      if (preg_match_all($regexp, $body, $matches, PREG_SET_ORDER)) {
        foreach ($matches as $match) {
          $links[] = $match;
        }
      }
    }
  }
  
  return $links;
}

function _icl_content_get_image_paths_for_node($nid) {

  global $base_url;
  global $base_root;
  
  $image_paths = array();
  $node = node_load($nid);
  
  $source_path = "node/" . $nid;
  $source_path = drupal_get_path_alias($source_path);

  $images = _icl_content_get_image_paths($node->body);

  if (module_exists('content')) {
    $type = content_types($node->type);
    if (isset($type['fields'])) {
      foreach ($type['fields'] as $field) {
        $field_name = $field['field_name'];
        $cck_data = $node->$field_name;
        if ($cck_data) {
          foreach ($cck_data as $index => $data) {
            
            if (isset($data['value'])) {
              $images = array_merge($images, _icl_content_get_image_paths($data['value']));
            }
            
          }
        }
      }
    }
  }

  foreach ($images as $path) {
    $path[2] = trim($path[2]);
    if (strpos($path[2], $base_root) === 0) {
      $image_path = $path[2];
    } else {
      $image_path = resolve_url($base_url . '/' . $source_path, $path[2]);
    }
    if (strpos($image_path, $base_root) === 0) {
      if (strpos($image_path, $base_url) === 0) {
        $image_path = substr($image_path, strlen($base_url));
      } else {
        $image_path = substr($image_path, strlen($base_root));
      }
      
      $image_paths[] = array('lang' => $node->language, 'path' => $image_path);
    }
  }
  
  return $image_paths;
}

function icl_content_images_get_translations($id) {
  $query = _icl_wrapper_db_query("SELECT id, language, data FROM {icl_image_status} WHERE tnid=%d AND id<>tnid", $id);
  
  $ids = array();
  while ( $request = db_fetch_object ( $query ) ) {
    $ids[$request->language] = $request;
  }
  
  return $ids;
  
}

function icl_content_image_table_count() {
  return 30;
}

function icl_content_image_translations() {
  $form = array();
  
  drupal_add_css(drupal_get_path('module', 'icl_core').'/css/icl_core.css');
  drupal_add_css(drupal_get_path('module', 'icl_content').'/css/image_replace.css');
  drupal_add_css(drupal_get_path('module', 'icl_content').'/css/dashboard.css');
  
  drupal_add_js(drupal_get_path('module', 'icl_content') . '/js/icl_image_replace.js');
  $ican_image_replace_url = _icl_wrapper_url('icl_content/icl_image_replace');
  drupal_add_js(array('ican_ajax' =>
                      array('ican_image_replace_url' => $ican_image_replace_url)),
                      'setting');
  drupal_add_js(array('ican_ajax' =>
                      array('ican_edit_text' => t('edit'), 'ican_add_text' => t('add'))),
                      'setting');

  $form = icl_core_add_reminders($form);
  icl_core_add_thickbox();

  $form ['icl_image_replace_method'] = array (
     '#type' => 'fieldset', 
     '#title' => t ( '<b>Automatic Image Replacement</b>' ), 
     '#collapsible' => false );
  $form['icl_image_replace_method']['icl_image_replace_method'] = array(
    '#title' => t('Select the method to use to select alternative images for translated content'),
    '#type' => 'radios',    
    '#options' => array(
      'prefix' => t('Add language prefix to name (eg. image_1_es.jpg)'),
      'dir' => t('In a sub-directory using language prefix (eg. /es/image_1.jpg)'),
      'none' => t('None - I\'ll set them manually'),
    ),
    '#default_value' => variable_get('icl_image_replace_method', 'prefix'),
    '#description' => t('The alternative images will only be used if they exist. Otherwise the image in the original content will be used.'),
  );
  
  $form ['icanlocalize_image_scan'] = array (
     '#type' => 'fieldset', 
     '#title' => t ( '<b>Image Replacement Overrides</b>' ), 
     '#collapsible' => false );
  $form ['icanlocalize_image_scan'] ['message'] = _icl_wrapper_form_create_markup(array (
        '#type' => 'markup',
        '#value' => t("Search nodes and blocks for any images requiring translation: ")));

  $form['icanlocalize_image_scan']['Scan'] = array(
    '#type' => 'submit',
    '#submit' => array('icl_content_images_scan_submit'),
    '#value' => t('Scan for new images'),
  );

  $form ['icanlocalize_image_scan'] ['message_2'] = _icl_wrapper_form_create_markup(array (
        '#type' => 'markup',
        '#value' => t("Use this table to override the automatic image replacement method and enter different replacement images to be used in translated content."),
        '#prefix' => '<br /><br />',
        '#suffix' => '<br />',
        ));
  $form ['icanlocalize_image_scan']['message_3'] =_icl_wrapper_form_create_markup(array (
        '#type' => 'markup',
        '#value' => t("* Your changes have not been applied to the translated content yet."),
        '#prefix' => '<div class="warning" id="icl_changes_message_2" style="display:none">',
        '#suffix' => '<br /></div>',
        ));
    
  
  $form ['icanlocalize_image_scan']['image_table'] = icl_content_images_form_table();
  $form ['icanlocalize_image_scan']['throbber'] = _icl_wrapper_form_create_markup(array(
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
    '#submit' => array('icl_content_images_submit'),
    '#value' => t('Apply image replacement to translated content'),
  );
  return $form;
}


function theme_icl_content_images($form) {

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
  $output .= _icl_wrapper_theme('pager', array('tags' => icl_content_image_table_count()));
  return $output;
}

function _icl_content_get_replacement_name($image_replace_method, $data, $lang) {
  switch ($image_replace_method) {
    case 'prefix':
      $path_parts = pathinfo($data);
      $new_name = $path_parts['dirname'] . '/' . $path_parts['filename'] . '_' . $lang;
      if ($path_parts['extension'] != '') {
        $new_name .= '.' . $path_parts['extension'];
      }
      $value = $new_name;
      break;

    case 'dir':
      $path_parts = pathinfo($data);
      $new_name = $path_parts['dirname'] . '/'  . $lang . '/' . $path_parts['filename'];
      if ($path_parts['extension'] != '') {
        $new_name .= '.' . $path_parts['extension'];
      }
      $value = $new_name;
      break;

    default:
      $value = $data;
      break;
  }

  return $value;
}

function icl_content_images_form_table() {
  
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
  
  $form['#theme'] = 'icl_content_images';
  
  $image_replace_method = variable_get('icl_image_replace_method', 'prefix');
  $images = array();
  $source_lang = language_default()->language;
  $langs_targets = _icl_core_available_targets_for_origin ( $source_lang );

  $query = pager_query("SELECT * FROM {icl_image_status} WHERE tnid=id OR tnid=0", icl_content_image_table_count());
  
  while ( $request = db_fetch_object ( $query ) ) {
    $id = $request->id;
    $images[$id] = $id;
    $form['id'][$id] = array('#value' => $id);
    $form[$request->language][$id] = array('#value' => '<b>' . $request->data . '</b>');
    
    // do we have translations.
    $translations = icl_content_images_get_translations($id);
    foreach ($languages as $lang) {
      if ($lang->language != $request->language) {
        $control_id = $id . '_' . $lang->language;

        if (isset($translations[$lang->language])) {
          // we have a translation
          $value = $translations[$lang->language]->data;
          $form[$lang->language][$id] = array('#value' => '<a class="icl_edit_link" id="icl_add_edit_' . $control_id . '"></a>');
        } else {
          // we don't have a translation.
          // use the selected replacement menthod
          $value = _icl_content_get_replacement_name($image_replace_method, $request->data, $lang->language);
        
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
  
  
  $form['images'] = array('#type' => 'checkboxes', '#options' => $images, '#default_value' => array_keys($images));
 
  return $form;
}

function icl_content_images_scan_submit($form, &$form_state) {
  
  global $base_root;
  global $base_url;
  
  $sql = "SELECT DISTINCT tnid FROM {node} WHERE nid<>tnid AND tnid <> 0";
  
  $image_paths = array();
  
  $query = _icl_wrapper_db_query( $sql);
  while ( $request = db_fetch_object ( $query ) ) {
    $nid = $request->tnid;
    $images_in_node = _icl_content_get_image_paths_for_node($nid);
    
    foreach($images_in_node as $image) {
      if (!in_array($image, $image_paths)) {
        $image_paths[] = $image;
        
        // add to the database.

        $sql = "SELECT * FROM {icl_image_status} WHERE type='image' AND language='%s' AND data='%s'";

        $result = _icl_wrapper_db_query( $sql, $image['lang'], $image['path'] );
        
        if (_icl_wrapper_db_result($result) === false) {
          $sql = "INSERT INTO {icl_image_status} (data, type, language) VALUES ('%s', '%s', '%s')";
          _icl_wrapper_db_query( $sql, $image['path'], 'image', $image['lang']);
        }
        
      }
    }
  }
  
  // Scan for images in blocks.
  $table_name = _icl_wrapper_table_name('boxes');
  $sql = "SELECT b.body FROM {" . $table_name . "} b JOIN {i18n_blocks} i18b ON b.bid=i18b.delta WHERE i18b.language=''";
  $query = _icl_wrapper_db_query( $sql);
  while ( $request = db_fetch_object ( $query ) ) {
    $images_in_block = _icl_content_get_image_paths($request->body);
    
    foreach($images_in_block as $image) {
      
      $image = _icl_content_get_block_relative_image($image[2]);

      if ($image) {        
        $image = array('lang' => 'en', 'path' => $image);
        
        if (!in_array($image, $image_paths)) {
          $image_paths[] = $image;
          
          // add to the database.
  
          $sql = "SELECT * FROM {icl_image_status} WHERE type='image' AND language='%s' AND data='%s'";
  
          $result = _icl_wrapper_db_query( $sql, $image['lang'], $image['path'] );
          
          if (_icl_wrapper_db_result($result) === false) {
            $sql = "INSERT INTO {icl_image_status} (data, type, language) VALUES ('%s', '%s', '%s')";
            _icl_wrapper_db_query( $sql, $image['path'], 'image', $image['lang']);
          }
        }          
      }
    }
  }
  
}

function _icl_content_get_block_relative_image($image) {
  global $base_root, $base_url;
  
  $image = trim($image);
  if (strpos($image, $base_root) === 0) {
    $image_path = $image;
  } else {
    $image_path = resolve_url($base_url, $image);
  }
  if (strpos($image_path, $base_root) === 0) {
    if (strpos($image_path, $base_url) === 0) {
      $image_path = substr($image_path, strlen($base_url));
    } else {
      $image_path = substr($image_path, strlen($base_root));
    }
    return $image_path;
  } else {
    return FALSE;
  }
}

function icl_content_images_submit($form, &$form_state) {
  $nodes_effected = 0;
  
  $file_status = array();
  
  $image_replace_method = $form_state['values']['icl_image_replace_method'];
  variable_set('icl_image_replace_method', $image_replace_method);

  // apply the changes to all the translated nodes.
  
  $sql = "SELECT DISTINCT tnid FROM {node} WHERE nid<>tnid AND tnid <> 0";
  
  $query = _icl_wrapper_db_query( $sql);
  while ( $request = db_fetch_object ( $query ) ) {
    $nid = $request->tnid;
    $images_in_original_node = _icl_content_get_image_paths_for_node($nid);
    
    if (sizeof($images_in_original_node) > 0) {
      
      // get all the translations.
      $sql = "SELECT DISTINCT nid FROM {node} WHERE tnid=%d and nid<>tnid";
      
      $query_2 = _icl_wrapper_db_query( $sql, $nid);
      while ( $request_2 = db_fetch_object ( $query_2 ) ) {
        $trans_nid = $request_2->nid;
        $node = node_load($trans_nid);

        $node_changed = FALSE;

        _icl_content_undo_image_replacement($node, $node_changed);

        $source_path = "node/" . $trans_nid;
        $source_path = drupal_get_path_alias($source_path);

        icl_content_apply_image_replacement($source_path,
                                            $images_in_original_node,
                                            $node,
                                            $node_changed,
                                            $file_status);
        
        if ($node_changed) {
          if (isset($node->teaser) && $node->teaser != "") {
            $node->teaser = icl_wrapper_node_teaser($node->body);
          }
          
          node_save($node);
          
          $nodes_effected += 1;
          
        }
      
      }
    }
  }
  
  if ($nodes_effected > 0) {
    drupal_set_message(t('Alternative images were used in @count translated nodes.', array('@count' => $nodes_effected)));
  } else {
    drupal_set_message(t('No alternative images were used in any translated nodes.'));
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
      $images_in_block = _icl_content_get_image_paths($request->body);
  
      if (sizeof($images_in_block) > 0) {    
        foreach($images_in_block as $image) {
        
          $image = _icl_content_get_block_relative_image($image[2]);
          
          if ($image) {
            $sql = "SELECT language, translation FROM {locales_target} WHERE lid=%d";
            $query_2 = _icl_wrapper_db_query( $sql, $lid);
            while ( $request_2 = db_fetch_object ( $query_2 ) ) {
              $block_changed = FALSE;
              $lang = $request_2->language;
              $translation = $request_2->translation;
              _icl_content_undo_image_replacement_block($translation, $bid, $lang, $block_changed);

              icl_content_apply_image_replacement_block($images_in_block,
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
    }
  }    

  if ($blocks_effected > 0) {
    drupal_set_message(t('Alternative images were used in @count translated blocks.', array('@count' => $blocks_effected)));
  } else {
    drupal_set_message(t('No alternative images were used in any translated blocks.'));
  }
  
}

function _icl_content_undo_image_replacement(&$node, &$node_changed) {
  $regexp_images = _icl_content_get_image_regex();

  foreach($regexp_images as $regexp_image) {
    if (preg_match_all($regexp_image, $node->body, $matches, PREG_SET_ORDER)) {
      foreach($matches as $match) {
        $sql = "SELECT original FROM {icl_image_replacement_history} WHERE id=%d AND type='%s' AND replacement='%s'";
        $old_image = _icl_wrapper_db_result(_icl_wrapper_db_query($sql, $node->nid, 'node', $match[2]));
        if ($old_image !== FALSE) {
          $old_image = str_replace($match[2], $old_image, $match[0]);
          $node->body = str_replace($match[0], $old_image, $node->body);
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
        foreach ($cck_data as $index => $data) {
          
          if (isset($data['value'])) {
            foreach($regexp_images as $regexp_image) {
              if (preg_match_all($regexp_image, $data['value'], $matches, PREG_SET_ORDER)) {
                foreach($matches as $match) {
                  $sql = "SELECT original FROM {icl_image_replacement_history} WHERE id=%d AND type='%s' AND replacement='%s'";
                  $old_image = _icl_wrapper_db_result(_icl_wrapper_db_query($sql, $node->nid, 'node', $match[2]));
                  if ($old_image !== FALSE) {
                    $old_image = str_replace($match[2], $old_image, $match[0]);
                    $data['value'] = str_replace($match[0], $old_image, $data['value']);
                    $node_changed = TRUE;
                  }
                }
              }
            }
            $cck_data[$index] = $data;
          }
          
        }
        $node->$field_name = $cck_data;
      }
    }
  }
  
  
}

function _icl_content_undo_image_replacement_block(&$translation, $bid, $lang, &$block_changed) {
  $regexp_images = _icl_content_get_image_regex();

  foreach($regexp_images as $regexp_image) {
    if (preg_match_all($regexp_image, $translation, $matches, PREG_SET_ORDER)) {
      foreach($matches as $match) {
        $sql = "SELECT original FROM {icl_image_replacement_history} WHERE id=%d AND type='%s' AND replacement='%s'";
        $old_image = _icl_wrapper_db_result(_icl_wrapper_db_query($sql, $bid, 'block-'.$lang, $match[2]));
        if ($old_image !== FALSE) {
          $old_image = str_replace($match[2], $old_image, $match[0]);
          $translation = str_replace($match[0], $old_image, $translation);
          $block_changed = TRUE;
        }
      }
    }
  }
}

function icl_content_image_replace_callback() {
  global $language;
  global $base_url;
  global $base_root;

  $result = '0|0';
  
  if (isset($_POST['icl_image_cmd'])) {
    switch ($_POST['icl_image_cmd']) {
      case 'icl_file_exists':
        $file = realpath($_POST['icl_file_name']);
        
        $root_dir = realpath(".");
        
        if (file_exists($root_dir . $file)) {
          $result = '1|1';
        } else {
          $result = '1|0';
        }
        break;
       
      case 'icl_save':
        $id = $_POST["icl_id"];
        $file_name = $_POST["icl_file_name"];
        
        $parts = explode('_', $id);
        $image_id = $parts[2];
        $lang = $parts[3];
        
        $trans_id = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT id FROM {icl_image_status} WHERE tnid=%d AND language='%s'", $image_id, $lang));
        if ($trans_id !== false) {
          // update the record
          $sql = "UPDATE {icl_image_status} SET data='%s' WHERE tnid=%d AND language='%s'";
          _icl_wrapper_db_query( $sql, $file_name, $image_id, $lang);
        } else {
          // create a new record
          $sql = "INSERT INTO {icl_image_status} (data, type, language, tnid) VALUES ('%s', '%s', '%s', %d)";
          _icl_wrapper_db_query( $sql, $file_name, 'image', $lang, $image_id);
        }
        // set the tnid for the original
        $sql = "UPDATE {icl_image_status} SET tnid=id WHERE id=%d";
        _icl_wrapper_db_query( $sql, $image_id);
        
        $result = '1|1';
        break;

      case 'icl_delete':
        $id = $_POST["icl_id"];

        $parts = explode('_', $id);
        $image_id = $parts[2];
        $lang = $parts[3];

        $sql = "DELETE FROM {icl_image_status} WHERE tnid=%d AND language='%s'";
        _icl_wrapper_db_query( $sql, $image_id, $lang);

        $result = '1|1';
        break;
    }
  }
  
  echo $result;
}


function icl_content_apply_image_replacement($source_path,
                                             $images_in_original_node,
                                             &$node,
                                             &$node_changed,
                                             &$file_status) {
  global $base_url;
  global $base_root;

  _icl_wrapper_db_query("DELETE FROM {icl_image_replacement_history} WHERE id=%d AND type='node'", $node->nid);
  
  $regexp_images = _icl_content_get_image_regex();

  $image_replace_method = variable_get('icl_image_replace_method', 'prefix');

  _icl_content_apply_image_replacement_to_data($node->body,
                                                $source_path,
                                                $images_in_original_node,
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
        foreach ($cck_data as $index => $data) {
          
          if (isset($data['value'])) {
            _icl_content_apply_image_replacement_to_data($data['value'],
                                                          $source_path,
                                                          $images_in_original_node,
                                                          $node->language,
                                                          $node->nid,
                                                          'node',
                                                          $node_changed,
                                                          $file_status);
            $cck_data[$index] = $data;

          }
          
        }
        $node->$field_name = $cck_data;
      }
    }
  }

}

function icl_content_apply_image_replacement_block($images_in_original,
                                    &$translation,
                                    $bid,
                                    $lang,
                                    &$block_changed,
                                    &$file_status) {

  _icl_wrapper_db_query("DELETE FROM {icl_image_replacement_history} WHERE id=%d AND type='%s'", $bid, 'block-'.$lang);
  
  foreach ($images_in_original as $index => $image) {
    $image = array('lang' => 'en',
                   'path' => _icl_content_get_block_relative_image($image[2]));
    
    $images_in_original[$index] = $image;
  }
  
  _icl_content_apply_image_replacement_to_data($translation,
                                                '',
                                                $images_in_original,
                                                $lang,
                                                $bid,
                                                'block-'.$lang,
                                                $block_changed,
                                                $file_status);
}


function _icl_content_apply_image_replacement_to_data(&$data,
                                                      $source_path,
                                                      $images_in_original,
                                                      $language,
                                                      $type_id,
                                                      $type,
                                                      &$changed,
                                                      &$file_status) {
  global $base_url;
  global $base_root;

  $regexp_images = _icl_content_get_image_regex();
  $image_replace_method = variable_get('icl_image_replace_method', 'prefix');

  foreach($regexp_images as $regexp) {
    if (preg_match_all($regexp, $data, $matches, PREG_SET_ORDER)) {
      foreach ($matches as $match) {
        if ($source_path != '') {
          $image_path = resolve_url($base_url . '/' . $source_path, $match[2]);
        } else {
          $image_path = resolve_url($base_url, $match[2]);
        }
        if (strpos($image_path, $base_url) === 0) {
          $image_path = substr($image_path, strlen($base_url));
        } else {
          $image_path = substr($image_path, strlen($base_root));
        }
        foreach($images_in_original as $image) {
          
          if ($image['path'] ==  $image_path) {
            // same image - use a replacement if we have one.
            
            $trans_data = FALSE;
            $original_id = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT id FROM {icl_image_status} WHERE data='%s' AND language='%s'", $image['path'], $image['lang']));
            if ($original_id !== FALSE) {
              $trans_data = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT data FROM {icl_image_status} WHERE tnid=%d AND language='%s'", $original_id, $language));
            }
            
            if ($trans_data === FALSE) {
              // Use default image replacement.
              $trans_data = _icl_content_get_replacement_name($image_replace_method, $image['path'], $language);
            }
            
            // check if the file exists
  
            $path = realpath(".") . $trans_data;
            
	    if (!file_exists($path) && module_exists('imagecache')) {
              // check if this is an imagecache preset
              $check = explode("/", $trans_data);
            
              if ($check[4] == "imagecache") {
                $presetname = $check[5];
              
                unset($check[4]);
                unset($check[5]);
                unset($check[0]); //This is empty
                
                $originalimagepath = implode("/",$check);
                $destination = imagecache_create_path($presetname, $originalimagepath);
                $preset = imagecache_preset_by_name($presetname);

                //Create imagecache image
                imagecache_build_derivative($preset['actions'], $originalimagepath, $destination);
              }
            }
			
            if (!isset($file_status[$path])) {
              $file_status[$path] = file_exists($path);
            }
            
            if ($file_status[$path]) {
              // file exists so we can use the replacement.
              
              $new_image = $match[0];
              $new_image = str_replace($match[2], $trans_data, $new_image);
              
              $data = str_replace($match[0], $new_image, $data);
              $changed = TRUE;
  
              
              // record in the data base.
  
              $sql = "INSERT INTO {icl_image_replacement_history} (id, type, original, replacement) VALUES (%d, '%s', '%s', '%s')";
              
              _icl_wrapper_db_query($sql, $type_id, $type, $image_path, $trans_data);
              
            }
          }
        }
      }
  
    }
  }
}