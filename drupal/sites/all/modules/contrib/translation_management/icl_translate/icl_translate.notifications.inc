<?php
// icl_translate.notifications.inc

define('ICL_NOTIFICATIONS_MAIL', 0);
define('ICL_NOTIFICATIONS_MAIL_SENT', 1);
define('ICL_NOTIFICATIONS_REMINDER', 2);
define('ICL_NOTIFICATIONS_REMINDER_VIEWED', 3);
define('ICL_NOTIFICATIONS_MAIL_AND_REMINDER', 4);
define('ICL_NOTIFICATIONS_MAIL_AND_REMINDER_PROCESSED', 5);


/**
 * Implementation of hook_mail()
 * 
 * @param string $key
 * @param array $message
 * @param aray $params
 *      If 'daily digest' it holds all messages
 */
function icl_translate_mail($key, &$message, $params) {
  
  $language = $message['language'];
  
  $variables = _icl_wrapper_user_mail_tokens($params['account'], $language);
  $footer = _icl_wrapper_t("\r\n\r\n-- \r\n\r\nThis message was automatically sent by Translation Management running on !site. To stop receiving these notifications, go to Notification Settings, or contact the system administrator at !site.\r\n\r\nThis email is not monitored for replies.", $variables, $language->language);
  
  switch ($key) {
    
    case 'daily_digest':
      $message['subject'] = _icl_wrapper_t('Daily digest', $variables, $language->language);
      foreach ($params['messages'] as $messages) {
        $message['body'][] = $messages['subject'] . "\r\n" . implode('', $messages['body']) . "\r\n";
      }
      break;
    
    case 'translator_new_job':
      $variables['!rid'] = $params['rid'];
      $variables['!translate_url'] = _icl_wrapper_url('translate/' . $params['rid'], array('absolute' => TRUE));
      $variables['!jobs_url'] = _icl_wrapper_url('translator', array('absolute' => TRUE));
      $language_list = language_list('enabled');   
      $language_list = $language_list[1];   
      $variables['!source'] = $language_list[$params['from']]->name;
      $variables['!target'] = $language_list[$params['to']]->name;
      $message['subject'] = _icl_wrapper_t('New translation job from !site', $variables, $language->language);
      $message['body'][] = _icl_wrapper_t("You have been assigned to new translation job from !source to !target.\r\n\r\nStart editing: !translate_url\r\nYou can view your other translation jobs here: !jobs_url", $variables, $language->language) . $footer;
      break;
    
    case 'translator_first_available_job':
      $variables['!rid'] = $params['rid'];
      $variables['!translate_url'] = _icl_wrapper_url('translate/' . $params['rid'], array('absolute' => TRUE));
      $variables['!jobs_url'] = _icl_wrapper_url('translator', array('absolute' => TRUE));
      $language_list = language_list('enabled');   
      $language_list = $language_list[1];   
      $variables['!source'] = $language_list[$params['from']]->name;
      $variables['!target'] = $language_list[$params['to']]->name;
      $message['subject'] = _icl_wrapper_t('New translation job from !site', $variables, $language->language);
      $message['body'][] = _icl_wrapper_t("New job available from !source to !target.\r\n\r\nStart editing: !translate_url\r\nYou can view your other translation jobs here: !jobs_url", $variables, $language->language) . $footer;
      break;
    
    case 'manager_job_completed':
      $job_info = _icl_translate_get_job_info($params['rid']);
      $variables['!translator'] = $job_info['translator']['name'];
      $variables['!title'] = $job_info['title'];
      $variables['!title_link'] = $job_info['title_link'];
      $variables['!source'] = $job_info['origin']['name'];
      $variables['!target'] = $job_info['target']['name'];
      $variables['!jobs_url'] = _icl_wrapper_url(_icl_wrapper_get_root_menu('translation-management/translator'), array('absolute' => TRUE));
      $message['subject'] = _icl_wrapper_t('Translator has completed translation job for !site', $variables, $language->language);
      $message['body'][] = _icl_wrapper_t("Translator (!translator) has completed translation of job \"!title\" for !source to !target.\r\n!title_link\r\n\r\nView translation jobs: !jobs_url", $variables, $language->language) . $footer;
      break;
    
    case 'translator_self_removed_from_job':
      $job_info = _icl_translate_get_job_info($params['rid']);
      $variables['!translator'] = $job_info['translator']['name'];
      $variables['!title'] = $job_info['title'];
      $variables['!source'] = $job_info['origin']['name'];
      $variables['!target'] = $job_info['target']['name'];
      $variables['!jobs_url'] = _icl_wrapper_url(_icl_wrapper_get_root_menu('translation-management/translator'), array('absolute' => TRUE));
      $message['subject'] = _icl_wrapper_t('Translator has resigned from job on !site', $variables, $language->language);
      $message['body'][] = _icl_wrapper_t("Translator (!translator) has resigned from the translation job \"!title\" for !source to !target\r\nView translation jobs: !jobs_url", $variables, $language->language) . $footer;
      break;
  }
}

/**
 * Return formatted messages
 */
function _icl_translate_notifications($k = 'all') {
  $messages = array(
    'translator_new_job' => array(
      'name' => t('Notify translator about new job'),
      '#options' => array('1' => t('Notify immediately')),
      '#default_value' => 1
    ),
    'manager_job_completed' => array(
      'name' => t('Notify translator manager when job is completed'),
      '#default_value' => 0
    ),
    'translator_self_removed_from_job' => array(
      'name' => t('Notify translator when removed from job'),
      '#default_value' => 0
    ),
  );
  if ($k == 'all') {
    return $messages;
  }
  else if ($k == 'defaults') {
    $defaults = array();
    foreach ($messages as $name => $message) {
      $defaults[$name] = $message['#default_value'];
    }
    $defaults['settings']['show_in_reminders'] = 1;
    $defaults['settings']['delete_old_messages_period'] = 30;
    return $defaults;
  }
  else {
    return $messages[$k];
  }
}

function icl_translate_notifications_form() {
  $form = array();
  $form['notifications'] = array(
    '#type' => 'fieldset'
  );
  $notifications = _icl_translate_notifications();
  $settings = variable_get('icl_translate_notifications', _icl_translate_notifications('defaults'));
  foreach ($notifications as $k => $notification) {
    $form['notifications'][$k]['settings[' . $k . ']'] = array(
      '#type' => 'radios',
      '#title' => $notification['name'],
      '#options' => isset($notification['#options']) ? $notification['#options'] : array('1' => t('Notify immediately'), 2 => t('Daily notifications summary'), 0 => t('No notification')),
      '#default_value' => isset($settings[$k]) ? $settings[$k] : $notification['#default_value'],
      '#name' => 'settings[' . $k . ']',
    );
  }
  
  $form['notifications']['show_in_reminders'] = array(
    '#name' => 'settings[settings][show_in_reminders]',
    '#type' => 'checkbox',
    '#title' => t('Show notifications on the translation dashboard'),
    '#default_value' => isset($settings['settings']['show_in_reminders'])
  );
  
  $form['notifications']['delete_old_messages_period'] = array(
    '#name' => 'settings[settings][delete_old_messages_period]',
    '#type' => 'select',
    '#title' => t('Delete old messages after'),
    '#options' => array(0 => t("Don't delete"), 7 => t('7 days'), 15 => t('15 days'), 30 => t('30 days'), 60 => ('60 days'), 90 => t('90 days')),
    '#default_value' => $settings['settings']['delete_old_messages_period']
  );
  
  $form['action'] = array(
    '#type' => 'submit',
    '#submit' => array('icl_translate_notifications_form_submit'),
    '#value' => t('Save')
  );
  
  return $form;
}

function icl_translate_notifications_form_submit() {
  if (user_access(ICL_TRANSLATE_MANAGE_JOBS) && isset($_POST['settings']) && is_array($_POST['settings'])) {
    variable_set('icl_translate_notifications', $_POST['settings']);
  }
}

/**
 * Use this function to send mail
 * 
 * @param int $uid
 * @param string $key
 *      Key to get from _icl_translate_notifications()
 */
function _icl_translate_notify($uid, $key, $rid = 0, $from = '', $to = '') {
  
  $settings = variable_get('icl_translate_notifications', _icl_translate_notifications('defaults'));
  
  if (!$settings[$key]) {
    return;
  }
  
  $account = FALSE;
  
  if ($uid == -1) {
    _icl_translate_notify_first_available($key, $rid, $from, $to);
  }
  else if ($key == 'translator_self_removed_from_job') {
    $account = user_load(_icl_wrapper_db_result(_icl_wrapper_db_query("SELECT manager_uid FROM {icl_translate_job} WHERE rid=%d", $rid)));
  }
  else {
    $account = user_load($uid);
  }
  
  if ($account) {
    $params['account'] = $account;
    $params['rid'] = $rid;
    $params['from'] = $from;
    $params['to'] = $to;
    if ($settings[$key] == 1) {
      $result = drupal_mail('icl_translate', $key, $account->mail, user_preferred_language($account), $params);
      if ($result['result']) {
        drupal_set_message(t('Notification sent to %name (%mail)', array('%name' => $account->name, '%mail'=> $account->mail)));
      }
      else {
        drupal_set_message(t('Error occurred while notifying %name (%mail)', array('%name' => $account->name, '%mail'=> $account->mail)), 'error');
      }
    }
    else if ($settings[$key] == 2) {
      // Insert message in DB for daily digest
      _icl_translate_notify_daily_digest_insert($uid, $key, $params);
      // Trigger daily digest send mail
      _icl_translate_notify_daily_digest_process();
    }
  }
  if ($cleanup = $settings['settings']['delete_old_messages_period']) {
    _icl_translate_notifications_cleanup($cleanup);
  }
}

/**
 * Insert message for daily digest
 */
function _icl_translate_notify_daily_digest_insert($uid, $key, $params) {
  $message = array();
  icl_translate_mail($key, $message, $params);
  $data = array('uid' => $uid, 'timestamp' => time(), 'message' => $message);
  drupal_write_record('icl_notifications', $data);
}

/**
 * Sends daily digest mail
 */
function _icl_translate_notify_daily_digest_process($time = 86400) {
  $last_time_processed = variable_get('icl_notifications_daily_processed', 0);
  if (time()-$last_time_processed < $time) {
    return FALSE;
  }
  //$time = time()-$time;
  //$q = _icl_wrapper_db_query("SELECT * FROM {icl_notifications} WHERE timestamp<%d AND (status=%d OR status=%d)", $time, ICL_NOTIFICATIONS_MAIL, ICL_NOTIFICATIONS_MAIL_AND_REMINDER);
  $q = _icl_wrapper_db_query("SELECT * FROM {icl_notifications} WHERE status=%d OR status=%d", ICL_NOTIFICATIONS_MAIL, ICL_NOTIFICATIONS_MAIL_AND_REMINDER);
  $rows = array();
  $mails = array();
  while ($r = db_fetch_array($q)) {
    if (!$r['uid']) {
      continue;
    }
    // Store whole message
    $mails[$r['uid']][$r['id']] = unserialize($r['message']);
  }
  // Loop mail send
  foreach ($mails as $uid => $messages) {
    $account = user_load($uid);
    $params['account'] = $account;
    // Store all messages in $params
    $params['messages'] = $messages;
    $result = drupal_mail('icl_translate', 'daily_digest', $account->mail, user_preferred_language($account), $params);
    // If sent update statuses of all messages
    if ($result['result']) {
      _icl_translate_notification_dismiss(array_keys($messages), ICL_NOTIFICATIONS_MAIL_SENT);
    }
  }
  variable_set('icl_notifications_daily_processed', time());
}

/**
 * Insert any message
 */
function icl_translate_add_notification($message, $uid = 0, $send_mail = FALSE) {
  $status = $send_mail ? ICL_NOTIFICATIONS_MAIL_AND_REMINDER : ICL_NOTIFICATIONS_REMINDER;
  $data = array('uid' => $uid, 'timestamp' => time(), 'message' => $message, 'status' => $status);
  drupal_write_record('icl_notifications', $data);
}

/**
 * Cleanup (delete old messages)
 */
function _icl_translate_notifications_cleanup($time) {
  $time = 60*60*24*(int)$time;
  $processed = variable_get('icl_translate_notifications_cleanup', time());
  if ((time() - $processed) > $time) {
    $time = time()-$time;
    _icl_wrapper_db_query("DELETE FROM {icl_notifications} WHERE timestamp<%d AND (status=%d OR status=%d)", $time, ICL_NOTIFICATIONS_MAIL_SENT, ICL_NOTIFICATIONS_REMINDER_VIEWED);
    variable_set('icl_translate_notifications_cleanup', time());
  }
}

function _icl_translate_render_reminders($action = 'init', $reminders = array(), $process = TRUE, $uid = FALSE) {
  
  if (!$uid) {
    global $user;
    $uid = $user->uid;
  }
  
  $out = '';
  
  switch ($action) {
    
    case 'init':
      drupal_add_css(drupal_get_path('module', 'icl_translate') . '/css/icl_translate_notifications.css');
      drupal_add_js(drupal_get_path('module', 'icl_translate') . '/js/icl_translate_notifications.js');
      drupal_add_js(array('icl_reminders_message' => array(
        'ajax_url' => _icl_wrapper_url(_icl_wrapper_get_root_menu('translation-management/translator')),
        'show_txt' => t('Show reminders'),
        'hide_txt' => t('Hide reminders'),
        'hide_link' => _icl_wrapper_url(_icl_wrapper_get_root_menu('translation-management/translator'), array('query' => 'show=0')),
        'show_link' => _icl_wrapper_url(_icl_wrapper_get_root_menu('translation-management/translator'), array('query' => 'show=1')))),
        'setting');
      $out .= '<div id="icl_reminders_wrapper"></div>';
      break;
    
    case 'render':
      $out .= '<script type="text/javascript">iclRemindersInit();</script>';
      $show = variable_get('icl_show_reminders', array());
      $show = isset($show[$user->uid]) ? $show[$user->uid] : 1;
      if ($show) {
        $txt = t('Hide reminders');
        $show_link = _icl_wrapper_url(_icl_wrapper_get_root_menu('translation-management/translator'), array('query' => 'show=0'));
      }
      else {
        $txt = t('Show reminders');
        $show_link = _icl_wrapper_url(_icl_wrapper_get_root_menu('translation-management/translator'), array('query' => 'show=1'));
      }
      if ($process) {
        if (user_access(ICL_TRANSLATE_MANAGE_JOBS)) {
          $q = _icl_wrapper_db_query("SELECT * FROM {icl_notifications} WHERE uid=%d AND (status=%d OR status=%d)", 0, ICL_NOTIFICATIONS_REMINDER, ICL_NOTIFICATIONS_MAIL_AND_REMINDER);
          while ($r = db_fetch_array($q)) {
            $reminders['manager'][$r['id']] = _icl_translate_reminders_process_message($r['message']);
          }
        }
        $q = _icl_wrapper_db_query("SELECT * FROM {icl_notifications} WHERE uid=%d AND (status=%d OR status=%d)", $uid, ICL_NOTIFICATIONS_REMINDER, ICL_NOTIFICATIONS_MAIL_AND_REMINDER);
        while ($r = db_fetch_array($q)) {
          $reminders['translator'][$r['id']] = _icl_translate_reminders_process_message($r['message']);
        }
      }
      
      if (!empty($reminders)) $out .= '<div id="icl_reminders"><a href="' . $show_link . '" id="icl_reminders_show">' . $txt . '</a>';
      foreach ($reminders as $type => $arr) {
        foreach ($arr as $k => $reminder) {
          $out .= '<div';
          if (!$show) {
            $out .= ' style="display: none;"';
          }
          $out .= '>' . $reminder . '&nbsp;<a href="' . _icl_wrapper_url(_icl_wrapper_get_root_menu('translation-management/translator'), array('query' => 'id=' . $k)) . '" class="icl_reminders_link_dismiss">' . t('Dismiss') . '</a></div>';
        }
      }
      if (!empty($reminders)) $out .= '</div>';
      break;
  }
  
  return $out;
}

function _icl_translate_reminders_process_message($data) {
  $data = unserialize($data);
  if (is_array($data)) {
    $out = '';
    if (isset($data['subject'])) {
      $out .= '<span class="icl_reminders_subject">' . $data['subject'] . '</span>';
    }
    if (isset($data['body'])) {
      $out .= '&nbsp;<span class="icl_reminders_body">' . implode('', $data['body']) . '</span>';
    }
    $data = $out;
  }
  return $data;
}

function _icl_translate_reminders_dismiss_ajax() {
  if (isset($_GET['id'])) {
    _icl_translate_notification_dismiss(array($_GET['id']), ICL_NOTIFICATIONS_REMINDER_VIEWED);
  }
}

function _icl_translate_notification_dismiss($ids, $status) {
  global $user;
  foreach ($ids as $k => $id) {
    $do = FALSE;
    // Check if belongs to user
    if (_icl_wrapper_db_result(_icl_wrapper_db_query("SELECT id FROM {icl_notifications} WHERE id=%d AND uid=%d", $id, $user->uid))) {
      $do = TRUE;
    }
    // Check if it's manager's notification
    else if (_icl_wrapper_db_result(_icl_wrapper_db_query("SELECT id FROM {icl_notifications} WHERE id=%d AND uid=%d", $id, 0))) {
      if (user_access(ICL_TRANSLATE_MANAGE_JOBS)) {
        $do = TRUE;
      }
    }
    if ($do) {
      _icl_wrapper_db_query("UPDATE {icl_notifications} SET status=%d WHERE id=%d", $status, $id);
    }
  }
}

function _icl_translate_notifications_render_list($list = array(), $id = FALSE, $class = 'icl_cyan_box') {
  if (empty($list)) {
    return '';
  }
  if ($id) {
    $id = ' id="' . $id . '"';
  }
  
  $items = '';
  foreach ($list as $k => $item) {
    if (empty($item)) {
      continue;
    }
    if ($items != '') {
      $items .= '<hr /><br />';
    }
    $items .= '<div>' . $item . '</div>';
  }
  
  if (!empty($items)) {
    return '<div' . $id . ' class="' . $class . '">' . $items . '</div>';
  }
  else {
    return '';
  }
}

function _icl_translate_notify_first_available($key, $rid, $from, $to) {
  if ($users = _icl_translate_get_translators_for_pair($from, $to)) {
    foreach ($users as $account) {
      $account = user_load($account['id']);
      $params['account'] = $account;
      $params['rid'] = $rid;
      $params['from'] = $from;
      $params['to'] = $to;
      $result = drupal_mail('icl_translate', $key, $account->mail, user_preferred_language($account), $params);
      if ($result['result']) {
        drupal_set_message(t('Notification sent to %name (%mail)', array('%name' => $account->name, '%mail'=> $account->mail)));
      }
      else {
        drupal_set_message(t('Error occurred while notifying %name (%mail)', array('%name' => $account->name, '%mail'=> $account->mail)), 'error');
      }
    }
  }
}
