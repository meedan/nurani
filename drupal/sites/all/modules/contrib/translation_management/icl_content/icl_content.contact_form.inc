<?php
/*
 * $Id: icl_content.contact_form.inc
 * 
 * @file ICanLocalize content contact form handling
 */

function is_standard_contact_form_enabled() {
  return module_exists('contact');
}

/**
 * Extracts valuable data from the contact form.
 *
 * @return array
 */
function _icl_content_extract_standard_contact_form() {
  
  $form_text = array(
                     'contact' => 'Contact',
                     'name' => 'Your name',
                     'email' => 'Your e-mail address',
                     'subject' => 'Subject',
                     'category' => 'Category',
                     'message' => 'Message',
                     'send_copy' => 'Send yourself a copy.',
                     'send' => 'Send e-mail',
                     );
  
    
  
  $data = array (
      array (
          'type' => 'body', 
          'translate' => 1, 
          'text' => ""),
      );
  
  foreach($form_text as $type => $text) {
    $data[] = array (
          'type' => $type, 
          'translate' => 1, 
          'text' => $text);
  }
  
  // add the support categories
  
  $query = _icl_wrapper_db_query("SELECT * FROM {contact}");
  
  while($result = db_fetch_object($query)) {
    $cid = $result->cid;

    if (strlen($result->category) > 0) {
      $data[] = array (
          'type' => 'category['.$cid.']', 
          'translate' => 1, 
          'text' => $result->category);
      _icl_wrapper_add_locale_source($result->category);
    }
    if (strlen($result->reply) > 0) {
      $data[] = array (
          'type' => 'reply['.$cid.']', 
          'translate' => 1, 
          'text' => $result->reply);
      _icl_wrapper_add_locale_source($result->reply);
    }
    
  }
  
  $contact_info = variable_get('contact_form_information', 'You can leave a message using the contact form below.');
  if (strlen($contact_info) > 0) {
    $data[] = array (
        'type' => 'category_info', 
        'translate' => 1, 
        'text' => $contact_info);
    _icl_wrapper_add_locale_source($contact_info);
  }
  
  // get the contact menu.
  $menu_title = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT link_title FROM {menu_links} where link_path = 'contact' and module='menu'"));
  if (strlen($menu_title) > 0) {
    $data[] = array (
        'type' => 'menu_title', 
        'translate' => 1, 
        'text' => $menu_title);
    _icl_wrapper_add_locale_source($menu_title);

    $menu_option = unserialize(_icl_wrapper_db_result(_icl_wrapper_db_query("SELECT options  FROM {menu_links} where link_path = 'contact' and module='menu'")));
    $menu_description = $menu_option['attributes']['title'];

    if ($menu_description && strlen($menu_description) > 0) {
      $data[] = array (
          'type' => 'menu_description', 
          'translate' => 1, 
          'text' => $menu_description);
      _icl_wrapper_add_locale_source($menu_description);
    }


  }
  
  
  return $data;
}


function icl_content_calculate_stardard_contact_form_md5() {
  $data = _icl_content_extract_standard_contact_form();
  
  $contact_data = icl_content_calculate_md5_and_words_from_data($data);
  return $contact_data['md5'];
  
}

function _icl_content_fix_old_contact_form_rids() {
  // Make sure the previous rids are a list of rids
  $rids = variable_get('icl_contact_form_rids', FALSE);
  if($rids !== FALSE) {
    $fixup_done = FALSE;
    foreach ($rids as $lang => $rid) {
      if (!is_array($rid)) {
        $rids[$lang] = array($rid);
        $fixup_done = TRUE;
      }
    }
    
    if ($fixup_done) {
      variable_set('icl_contact_form_rids', $rids);
    }
  }
  
}

function icl_content_get_contact_form_for_dashboard($icl_content_dashboard_filter) {
  
  if (!module_exists('contact')) {
    return NULL;
  }
  
  if (!empty($icl_content_dashboard_filter)) {
    if ($icl_content_dashboard_filter['language'] != 'en') {
      // Can only translate contact form from 'English'
      return NULL;
    }
  
    if (isset($icl_content_dashboard_filter['type_type']) && isset($icl_content_dashboard_filter['type_enabled'])) {
      if ($icl_content_dashboard_filter['type_enabled']) {
        if ($icl_content_dashboard_filter['type_type'] != 'standard_contact_form') {
          // selecting a different type so return null.
          return NULL;
        }
      }
    }
  }
  
  _icl_content_fix_old_contact_form_rids();
  
  $languages = locale_language_list();
  
  $status = array('id' => 'contact-1',
                  'link' => _icl_wrapper_get_drupal_menu('admin/build/contact'),
                  'type' => 'icl_contact_form_marker',
                  'origin' => language_default()->language,
                  'status' => t('Enabled'),
                  'title' => t('Contact form'),
                  'targets' => array());
  
  $current_md5 = icl_content_calculate_stardard_contact_form_md5();
  
  foreach ($languages as $lang => $name) {
    if ($lang != language_default()->language) {
      $status['targets'][$lang] = array();

      $status['targets'][$lang]['translated'] = 0; // Not sure if this should be 0 or 1
      
      
      // Find the current rid and rid_status.
      $status['targets'][$lang]['current_rid'] = 0;
      $status['targets'][$lang]['rid_status'] = 0;
      $status['targets'][$lang]['needs_update'] = 0;

      $rids = variable_get('icl_contact_form_rids', FALSE);
      if($rids !== FALSE) {
        $previous_md5s = variable_get('icl_contact_form_md5s', '');

        $last_md5 = '';
        foreach ($rids as $rid_lang => $rid) {
          $rid = max($rid);
          if ($rid_lang == $lang) {
            $rid_status = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT status FROM {icl_core_status} WHERE rid=%d", $rid));
            $status['targets'][$lang]['current_rid'] = $rid;
            $status['targets'][$lang]['rid_status'] = $rid_status;
            $status['targets'][$lang]['translation_service'] = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT translation_service FROM {icl_core_status} WHERE rid=%d", $rid));
            $last_md5 = $previous_md5s[$rid];
          }
        }
        
      }
      if ($last_md5 != '') {
        // The translation needs updating when the current md5 is different
        // from the md5 when the translation was last sent.
        $status['targets'][$lang]['needs_update'] = $last_md5 != $current_md5;
      }
      
      
    }
  }

  return $status;  
  
}


function icl_content_translate_standard_contact_form($source_lang, $dest_langs, $translators) {
   
  $targets = _icl_get_langs_not_in_progress(0, 'contact_form', NULL, $source_lang, $dest_langs);
   
  // Have we translated this before.

  $site_languages = language_list('language', TRUE);
  
  $previous_rids = variable_get('icl_contact_form_rids', array());
  // Only use the most recent rid
  foreach ($previous_rids as $lang => $rids) {
    $previous_rids[$lang] = max($rids);
  }
  $contact_md5 = icl_content_calculate_stardard_contact_form_md5();
  $targets = _icl_content_get_langs_needing_update($targets, $previous_rids, 'contact_form', $contact_md5, $translators);
   
  $origin = $site_languages [$source_lang];
  $data = _icl_content_extract_standard_contact_form();
   
  if (count ( $targets )) {
  
    $rids_sent = icl_core_send_content_for_translation('icl_content',
                                          $data,
                                          $origin,
                                          $targets,
                                          $previous_rids,
                                          "",
                                          'Contact form',
                                          $translators
                                          );
    
    
    foreach ($rids_sent as $rid) {
      if ($rid != 0) {
        $rid = (int)$rid;
        $values = variable_get('icl_contact_form_rids', array());
        $query = _icl_wrapper_db_query( "SELECT target FROM {icl_core_status} WHERE rid = %d", $rid );
        while ( $target = _icl_wrapper_db_result( $query ) ) {
          $values[$target][] = $rid;
        }
        variable_set('icl_contact_form_rids', $values);
        
        $values = variable_get('icl_contact_form_md5s', array());
        $values[$rid] = $contact_md5;
        variable_set('icl_contact_form_md5s', $values);
        
      }
    }
  }
}



function icl_content_save_contact_form_translation($bid, $code, $data) {
  
  if (is_string($data)) {
    // this indicates an error.
    return FALSE;
  }
  $form_data = array(
                     'contact',
                     'name',
                     'email',
                     'subject',
                     'category',
                     'message',
                     'send_copy',
                     'send',
                     );
  
  
  foreach ($data as $item) {
    if (in_array($item['type'], $form_data)) {
      $query = _icl_wrapper_db_query("SELECT lid FROM {locales_source} WHERE source = '%s' and textgroup = 'default'", $item['original_data']);
      while ($result = db_fetch_array($query)) {
        $lid = $result['lid'];
      
        if(!empty($lid)) {
          icl_content_update_locale_translation($lid, $code, $item['data']);
        } else {
          watchdog ( 'icl_content', 'Nonexistent originating contact form ' . $block_original['info'], WATCHDOG_ERROR );
          //return FALSE;
          // Don't return false as the user may have changed the original text of the block and that is the reason it can't be found.
        }
      }
    } else if ($item['type'] == 'category_info') {
      $query = _icl_wrapper_db_query("SELECT lid FROM {locales_source} WHERE source = '%s' and textgroup = 'default'", variable_get('contact_form_information', 'You can leave a message using the contact form below.'));
      while ($result = db_fetch_array($query)) {
        $lid = $result['lid'];
        if(!empty($lid)) {
          icl_content_update_locale_translation($lid, $code, $item['data']);
        } else {
          watchdog ( 'icl_content', 'Nonexistent originating contact form ' . $block_original['info'], WATCHDOG_ERROR );
          //return FALSE;
          // Don't return false as the user may have changed the original text of the block and that is the reason it can't be found.
        }
      }
    } else if ($item['type'] == 'menu_title') {
      $menu_title = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT link_title FROM {menu_links} where link_path = 'contact' and module = 'menu'"));
      
      $query = _icl_wrapper_db_query("SELECT lid FROM {locales_source} WHERE source = '%s' and textgroup = 'menu'", $menu_title);
      while ($result = db_fetch_array($query)) {
        $lid = $result['lid'];
        if(!empty($lid)) {
          icl_content_update_locale_translation($lid, $code, $item['data']);
        } else {
          watchdog ( 'icl_content', 'Nonexistent originating contact form ' . $block_original['info'], WATCHDOG_ERROR );
          //return FALSE;
          // Don't return false as the user may have changed the original text of the block and that is the reason it can't be found.
        }
      }
    } else if ($item['type'] == 'menu_description') {
      $menu_option = unserialize(_icl_wrapper_db_result(_icl_wrapper_db_query("SELECT options  FROM {menu_links} where link_path = 'contact' and module='menu'")));
      $menu_description = $menu_option['attributes']['title'];
      
      $query = _icl_wrapper_db_query("SELECT lid FROM {locales_source} WHERE source = '%s' and textgroup = 'default'", $menu_description);
      while ($result = db_fetch_array($query)) {
        $lid = $result['lid'];
        if(!empty($lid)) {
          icl_content_update_locale_translation($lid, $code, $item['data']);
        } else {
          watchdog ( 'icl_content', 'Nonexistent originating contact form ' . $block_original['info'], WATCHDOG_ERROR );
          //return FALSE;
          // Don't return false as the user may have changed the original text of the block and that is the reason it can't be found.
        }
      }
    } else if (substr ( $item['type'], 0, strlen ( 'category' ) ) == 'category') {
      $matches = array ();
      preg_match ( '/category\[(\d+)\]/i', $item['type'], $matches );
      $cid = $matches [1];
      $category = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT category FROM {contact} where cid=%d", $cid));

      $query = _icl_wrapper_db_query("SELECT lid FROM {locales_source} WHERE source = '%s' and textgroup = 'default'", $category);
      while ($result = db_fetch_array($query)) {
        $lid = $result['lid'];
        if(!empty($lid)) {
          icl_content_update_locale_translation($lid, $code, $item['data']);
        } else {
          watchdog ( 'icl_content', 'Nonexistent originating contact form ' . $block_original['info'], WATCHDOG_ERROR );
          //return FALSE;
          // Don't return false as the user may have changed the original text of the block and that is the reason it can't be found.
        }
      }
      
    } else if (substr ( $item['type'], 0, strlen ( 'reply' ) ) == 'reply') {
      $matches = array ();
      preg_match ( '/reply\[(\d+)\]/i', $item['type'], $matches );
      $cid = $matches [1];
      $reply = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT reply FROM {contact} where cid=%d", $cid));

      $query = _icl_wrapper_db_query("SELECT lid FROM {locales_source} WHERE source = '%s' and textgroup = 'default'", $reply);
      while ($result = db_fetch_array($query)) {
        $lid = $result['lid'];
        if(!empty($lid)) {
          icl_content_update_locale_translation($lid, $code, $item['data']);
        } else {
          watchdog ( 'icl_content', 'Nonexistent originating contact form ' . $block_original['info'], WATCHDOG_ERROR );
          //return FALSE;
          // Don't return false as the user may have changed the original text of the block and that is the reason it can't be found.
        }
      }
      
    }
  }
  
  cache_clear_all('locale:', 'cache', TRUE);
  
  return TRUE;
}

function icl_content_alter_standard_contact_form(&$form, $form_state) {
  global $language;
  
  $contact_info = variable_get('contact_form_information', '');
  if (strlen($contact_info) > 0) {
    $form['contact_information']['#value'] = filter_xss_admin(t($contact_info));
    $form['contact_information'] = _icl_wrapper_form_create_markup($form['contact_information']);
  }
  if (isset($form['cid']['#options'])) {
    foreach($form['cid']['#options'] as $index => $value) {
      $form['cid']['#options'][$index] = t($value);
    }
  }
  
  $block = locale_block('view');
  
  $form['translation-links'] = _icl_wrapper_form_create_markup(array (
          '#type' => 'markup', 
          '#value' => '<br><br>' . str_replace('<ul>', '<ul class="links inline">', $block['content']),
          ));
  
  $form['#submit'][0] = 'icl_content_contact_mail_page_submit';
  
}

/**
 * This is taken from contect.pages.inc
 * We need to supply the translated "Reply"
 * Process the site-wide contact page form submission.
 */
function icl_content_contact_mail_page_submit($form, &$form_state) {
  global $language;

  $values = $form_state['values'];

  // E-mail address of the sender: as the form field is a text field,
  // all instances of \r and \n have been automatically stripped from it.
  $from = $values['mail'];

  // Load category properties and save form values for email composition.
  $contact = contact_load($values['cid']);
  if (strlen($contact['reply']) > 0) {
    $contact['reply'] = t($contact['reply']);
  }
  $values['contact'] = $contact;

  // Send the e-mail to the recipients using the site default language.
  drupal_mail('contact', 'page_mail', $contact['recipients'], language_default(), $values, $from);

  // If the user requests it, send a copy using the current language.
  if ($values['copy']) {
    drupal_mail('contact', 'page_copy', $from, $language, $values, $from);
  }

  // Send an auto-reply if necessary using the current language.
  if ($contact['reply']) {
    drupal_mail('contact', 'page_autoreply', $from, $language, $values, $contact['recipients']);
  }

  flood_register_event('contact');
  watchdog('mail', '%name-from sent an e-mail regarding %category.', array('%name-from' => $values['name'] ." [$from]", '%category' => $contact['category']));
  drupal_set_message(t('Your message has been sent.'));

  // Jump to home page rather than back to contact page to avoid
  // contradictory messages if flood control has been activated.
  $form_state['redirect'] = '';
}

