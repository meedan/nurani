<?php
/*
 * $Id: icl_content.block.inc
 * 
 * @file ICanLocalize content block handling
 */

include_once dirname(__FILE__) . '/icl_content.images.inc';

function icl_content_save_block_translation($bid, $code, $data) {
  $block_original = _icl_wrapper_block_box_get($bid);
  
  foreach ($data as $item) {
    if ($item['type'] == 'title') {
      $title = $item['data'];
      
      // find the original in the locales_source
      
      $query = _icl_wrapper_db_query("SELECT lid FROM {locales_source} WHERE source = '%s' and textgroup = 'blocks'", $item['original_data']);
      while ($result = db_fetch_array($query)) {
        $lid = $result['lid'];
      
        if(!empty($lid)) {
          icl_content_update_locale_translation($lid, $code, $title);
        } else {
          watchdog ( 'icl_content', 'Nonexistent originating block title ' . $block_original['info'], WATCHDOG_ERROR );
          //return FALSE;;
          // Don't return false as the user may have changed the original text of the block and that is the reason it can't be found.
        }
      }
    }
    if ($item['type'] == 'Block titles') {
      foreach($item['data'] as $index => $title) {
        
        // find the original in the locales_source
        
        $query = _icl_wrapper_db_query("SELECT lid FROM {locales_source} WHERE source = '%s' and textgroup = 'blocks'", $item['original_data'][$index]);
        while ($result = db_fetch_array($query)) {
          $lid = $result['lid'];
        
          if(!empty($lid)) {
            icl_content_update_locale_translation($lid, $code, $title);
          } else {
            watchdog ( 'icl_content', 'Nonexistent originating block title ' . $block_original['info'], WATCHDOG_ERROR );
            //return FALSE;
            // Don't return false as the user may have changed the original text of the block and that is the reason it can't be found.
          }
        }
      }
    }
    if ($item['type'] == 'body') {
      $all_links_fixed = FALSE;
      $body = _icl_content_fix_links_in_text($item['data'], "en", $code, $all_links_fixed);
      
      $images_in_original = _icl_content_get_image_paths($body);
      
      $block_changed = FALSE;
      $file_status = array();
      icl_content_apply_image_replacement_block($images_in_original,
                                          $body,
                                          $bid,
                                          $code,
                                          $block_changed,
                                          $file_status);
      

      $query = _icl_wrapper_db_query("SELECT lid FROM {locales_source} WHERE source = '%s' and textgroup = 'blocks'", $block_original['body']);
      while ($result = db_fetch_array($query)) {
        $lid = $result['lid'];

        if(!empty($lid)) {
          icl_content_update_locale_translation($lid, $code, $body);
        } else {
          watchdog ( 'icl_content', 'Nonexistent originating block body ' . $block_original['body'], WATCHDOG_ERROR );
          //return FALSE;
          // Don't return false as the user may have changed the original text of the block and that is the reason it can't be found.
        }
      }
    }
  }
  
  return TRUE;
}


/**
 * calculate the md5 value of a block using title and body and other data.
 *
 */

function icl_content_calculate_block_md5_and_words($block) {
  $data = _icl_content_extract_block($block);
  
  return icl_content_calculate_md5_and_words_from_data($data);
  
}

function _icl_content_is_block_translation_in_progess($block) {
  $rid = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT rid FROM {icl_block_status} where bid='%d'", $block['bid']));
  
  if($rid === FALSE) {
    return FALSE;
  }
  
  $result = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT * FROM {icl_core_status} where rid='%d' and status <> '%d'", $rid, ICL_STATUS_SUCCESSFUL));
  
  return $result !== FALSE;
}

function _icl_content_is_block_i18n_enabled($block) {
  $bid = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT ibid FROM {i18n_blocks} WHERE delta = %d", $block['bid']));
  
  return $bid !== FALSE;
}

function _icl_content_is_block_i18n_with_translation($block) {
  $language = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT language FROM {i18n_blocks} WHERE delta = %d", $block['bid']));
  
  return $language == "";
}

/**
 * Sends blocks off for translation
 *
 * @param object $block
 * @return array
 */
  
function icl_content_translate_blocks($blocks, $source_lang, $dest_langs, $translators) {
  
  foreach($blocks as $bid) {
    $block = _icl_wrapper_block_box_get($bid);
    
    $targets = _icl_get_langs_not_in_progress($bid, 'block', $block, $source_lang, $dest_langs);

    if (sizeof($targets) == 0) {
      continue;
    }
    
    if (!_icl_content_is_block_i18n_enabled($block)) {
      drupal_set_message ( t ( 'error: The block is not managed by i18n block module. !block', array('!block' => $block['info'])), 'error');
      continue;
    }
    if (!_icl_content_is_block_i18n_with_translation($block)) {
      drupal_set_message ( t ( 'error: The block is not set to All languages (with translations). !block', array('!block' => $block['info'])), 'error');
      continue;
    }
    
    // Have we translated this before.
    
    $block_data = icl_content_calculate_block_md5_and_words($block);
    $block_md5 = $block_data['md5'];

    $site_languages = language_list('language', TRUE);

    $previous_rids = icl_content_get_rids($bid, 'block');

    $targets = _icl_content_get_langs_needing_update($targets, $previous_rids, 'block', $block_md5, $translators);

    if (count ( $targets )) {
      $origin = $site_languages [$source_lang];
      $data = _icl_content_extract_block($block);
      
      // create a separate cms_request for each language if possible
      // if the languages have previously been sent as a combined cms_request
      // we need to do the same this time.
      
      $grouped_targets = _icl_group_targets_by_rid($bid, 'block', $source_lang, $targets, $previous_rids);

      $rids_sent = icl_core_send_content_for_translation('icl_content',
                                            $data,
                                            $origin,
                                            $grouped_targets,
                                            $previous_rids,
                                            "",
                                            $block['info'],
                                            $translators
                                            );
      
      
      foreach ($rids_sent as $rid) {
        if ($rid != 0) {
          _icl_wrapper_db_query( "INSERT INTO {icl_block_status} VALUES(%d, %d, %d, '%s')", $rid, $block['bid'], time (), $block_md5 );
          _icl_wrapper_db_query( "INSERT INTO {icl_block} VALUES(%d, '%s', '%d')", $block['bid'], $block_md5, FALSE, $block_data['words'] );
        }
      }      
    }
  }
}
    

/**
 * Extracts valuable data from a block object.
 *
 * @param object $block
 * @return array
 */
function _icl_content_extract_block($block) {
  $table_name = _icl_wrapper_table_name('blocks');
  $query = _icl_wrapper_db_query("SELECT title FROM {" . $table_name . "} WHERE delta = %d", $block['bid']);
  $title = array();
  while ($result = db_fetch_array($query)) {
    if (strlen($result['title']) > 0 && !in_array($result['title'], $title)) {
      $title[] = $result['title'];
    }
  }

  // check the format to see if line breaks need to be converted
  $formats = filter_list_format($block['format']);
  $line_break_converter_found = false;
  foreach($formats as $format) {
    if ($format->delta == 1) {
      $line_break_converter_found = True;
    }
  }
  if (!$line_break_converter_found) {
    $filter_line_breaks = 0;
  } else {
    $filter_line_breaks = 1;
  }
  
  $data = array (
      array (
          'type' => 'bid', 
          'translate' => 0, 
          'text' => $block['bid'] ), 
      array (
          'type' => 'body', 
          'translate' => 1, 
          'text' => $block['body'],
          'filter_line_breaks' => $filter_line_breaks),
      
      
      );

  if (sizeof($title) == 1) {
    $data[] = array (
          'type' => 'title', 
          'translate' => 1, 
          'text' => $title[0]);
  } else if (sizeof($title) > 1) {
    $data[] = array (
          'type' => 'Block titles', 
          'translate' => 1, 
          'text' => $title,
          'format' => 'csv');
    
  }
  
  return $data;
}

function _icl_content_get_block_title($block_data) {
  $block_title = t('(no title)');
  foreach($block_data as $data) {
    if ($data['type'] == 'title') {
      $block_title = $data['text'];
    }
  }
  
  return $block_title;
}

function icl_content_get_blocks_for_dashboard($icl_content_dashboard_filter) {

  if (!module_exists ( 'i18nblocks' )) {
    return array();
  }
  
  $where = '';
  $query_args = array();

  $current_theme = variable_get('theme_default', 'none');
  $query_args[] = $current_theme;
  
  if (!empty($icl_content_dashboard_filter)) {
    if ($icl_content_dashboard_filter['language'] != 'en') {
      // Can only translate blocks from 'English'
      return array();
    }
    
    if (isset($icl_content_dashboard_filter['type_type']) && isset($icl_content_dashboard_filter['type_enabled'])) {
      if ($icl_content_dashboard_filter['type_enabled']) {
        if ($icl_content_dashboard_filter['type_type'] != 'block') {
          // selecting a different type so return an empty array.
          return array();
        }
      }
    }
  }

  // We don't know if a block has changed from the core status as we don't hook any saving of blocks.
  // We need to calculate each time.
  
  $query = _icl_wrapper_db_query("SELECT delta FROM {i18n_blocks} WHERE language = ''");
  while ( $bid = db_fetch_object ( $query ) ) {
    $block = _icl_wrapper_block_box_get($bid->delta);
    $block_data = icl_content_calculate_block_md5_and_words($block);
    
    // Affected rows change
    $exists = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT bid FROM {icl_block} WHERE bid = %d", $bid->delta));
    // save block md5 to database.
    if ($exists) {
      _icl_wrapper_db_query("UPDATE {icl_block} SET md5 = '%s' WHERE bid = %d", $block_data['md5'], $bid->delta);
      _icl_wrapper_db_query("UPDATE {icl_block} SET words = %d WHERE bid = %d", $block_data['words'], $bid->delta);
    } else {
      _icl_wrapper_db_query( "INSERT INTO {icl_block} VALUES(%d, '%s', %d, %d)", $bid->delta, $block_data['md5'], FALSE, $block_data['words']);
    }
  }

  $languages = locale_language_list();

  if (!empty($icl_content_dashboard_filter)) {
    if (isset($icl_content_dashboard_filter['search_text']) && isset($icl_content_dashboard_filter['search_enabled'])) {
      if ($icl_content_dashboard_filter['search_enabled'] && $icl_content_dashboard_filter['search_text'] != '') {
        $where .= " AND b.title LIKE '%%%s%%'";
        $query_args[] = $icl_content_dashboard_filter['search_text'];
      }
    }
  }
  $table_name = _icl_wrapper_table_name('blocks');
  $query = "
    SELECT b.delta, b.title
    FROM {" . $table_name . "} b
    JOIN {i18n_blocks} i18n
    ON i18n.delta = b.delta
    WHERE b.module='block' AND b.theme='%s' AND i18n.language='' $where
    ";
  $res = _icl_wrapper_db_query($query, $query_args);
 
  $matching_bids = array();
  while($row = db_fetch_array($res)){
    $status = array('id' => 'block-' . $row['delta'],
                    'link' => _icl_wrapper_get_drupal_menu('admin/build/block/configure/block/' . $row['delta']),
                    'type' => 'icl_block_marker',
                    'origin' => language_default()->language,
                    'status' => t('Enabled'),
                    'title' => $row['title'],
                    'targets' => array());
    
    if ($status['title'] == '') {
      $status['title'] = 'Block (no title)';
    }
    
    $block = _icl_wrapper_block_box_get($row['delta']);
    $title_lid = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT lid FROM {locales_source} WHERE source = '%s' and textgroup = 'blocks'", $row['title']));
    $body_lid = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT lid FROM {locales_source} WHERE source = '%s' and textgroup = 'blocks'", $block['body']));
    foreach ($languages as $lang => $name) {
      if ($lang != language_default()->language) {
        $status['targets'][$lang] = array();
  
        // see if a translation exists
        if ($title_lid > 0) {
          $translation_title = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT translation FROM {locales_target} WHERE lid = %d AND language = '%s'", $title_lid, $lang));
        } else {
          $translation_title = 0;
        }
        if ($body_lid > 0) {
          $translation_body = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT translation FROM {locales_target} WHERE lid = %d AND language = '%s'", $body_lid, $lang));
        } else {
          $translation_body = 0;
        }
        
        $status['targets'][$lang]['translated'] = $translation_title != 0 && $translation_body != 0;
        
        $current_md5 = _icl_wrapper_db_result(_icl_wrapper_db_query('SELECT md5 FROM {icl_block} WHERE bid=%d', $row['delta']));
        
        // Find the current rid and rid_status.
        $status['targets'][$lang]['current_rid'] = 0;
        $status['targets'][$lang]['rid_status'] = 0;
        $status['targets'][$lang]['needs_update'] = 0;
        $status_res = _icl_wrapper_db_query("SELECT c.rid, c.status, c.translation_service, bs.md5
                                FROM
                                  {icl_block_status} bs
                                JOIN
                                  {icl_core_status} c
                                ON
                                  bs.rid = c.rid
                                  
                                WHERE bs.bid=%d AND c.target='%s'", $row['delta'], $lang);
        $last_md5 = '';
        while($status_row = db_fetch_array($status_res)) {
          if ($status_row['rid'] > $status['targets'][$lang]['current_rid']) {
            $status['targets'][$lang]['current_rid'] = $status_row['rid'];
            $status['targets'][$lang]['rid_status'] = $status_row['status'];
            $status['targets'][$lang]['translation_service'] = $status_row['translation_service'];
            $last_md5 = $status_row['md5'];
          }
        }
        if ($last_md5 != '') {
          // The translation needs updating when the current md5 is different
          // from the md5 when the translation was last sent.
          $status['targets'][$lang]['needs_update'] = $last_md5 != $current_md5;
        }
        
        
      }
    }
    $matching_bids[] = $status;
  }
  
  return $matching_bids;
 
}

