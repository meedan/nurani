<?php 

module_load_include('inc', 'icl_translate', 'icl_translate.translator');

function icl_translator_manage_translators_form_cb(){
  return _icl_wrapper_drupal_get_form('icl_translator_manage_translators_form');
}

function theme_icl_translator_translators_form($form) {

  if (defined('ICL_D7')) {
    $form = $form['form'];
  }

  $header = array(t('Name'), t('Languages'), t('Type'), t('Action'));
  $rows = array();
  foreach (element_children($form['name']) as $key) {
    $row = array();
    $row[] = drupal_render(_icl_wrapper_form_create_markup($form['name'][$key]));
    $row[] = drupal_render(_icl_wrapper_form_create_markup($form['langs'][$key]));
    $row[] = drupal_render(_icl_wrapper_form_create_markup($form['type'][$key]));
    $row[] = drupal_render(_icl_wrapper_form_create_markup($form['action'][$key]));
    $rows[] = $row;
  }
    
  $output = _icl_wrapper_theme('table', array('header' => $header, 'rows' => $rows));

  return $output;
}

function icl_translator_manage_translators_form(){
  $form = array();
  $form['helper'] = array(
    '#type' => 'fieldset',
    '#title' => t('About managing translators'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  
  $form['helper']['add'] = _icl_wrapper_form_create_markup(array(
      '#type' => 'markup',
      '#value' => t('<p>Translators are special Drupal users who can translate between language pairs that you choose.</p>
                    <p>You can use your own translators or translation services.</p>
                    <p>Your own translators will translate in Drupal, using the <a href="http://drupal-translation.com/content/guide-translators">translation editor</a>.</p>
                    <p>Professional services work in their own translation systems. They support more advanced workflows including translation memory, review and QA. Drupal will send the content directly to the translation service and it will be returned back using server-to-server communication (<a href="http://drupal-translation.com/content/working-translation-services">using translation services</a>).</p>
                    <p>There can be a number of translators in the same language pair, including a mix of your own translators and professional services. When you send jobs to translation, you can choose who they are assigned to.</p>
                    <p><a href="http://drupal-translation.com/content/setting-translators">More on managing translators</a><p>'),
  ));

  // hook services
  $translation_services = module_invoke_all('translation_service');
  // if no services show warning
  if (sizeof($translation_services) == 0) {
    $form['no_services'] = _icl_wrapper_form_create_markup(array(
        '#type' => 'markup',
        '#prefix' => '<br /><br /><div class="error">',
        '#suffix' => '</div>',
        '#value' => '<b>' . t('There are no translation services available. You need to enable a translation service - <a href="@url">modules</a>.',
                              array('@url' => _icl_wrapper_url(_icl_wrapper_get_drupal_menu('admin/build/modules')) . '#Translation%20Services')) . '</b>',
      ));
    return $form;
  }

  // Check languages lists
  $languages_list = language_list('enabled');
  $languages_list = $languages_list[1];

  if (sizeof($languages_list) < 2) {
    $form['no_languages'] = _icl_wrapper_form_create_markup(array(
        '#type' => 'markup',
        '#prefix' => '<br /><br /><div class="error">',
        '#suffix' => '</div>',
        '#value' => '<b>' . t('There are no target languages available. You need to <a href="@url">enable more languages</a>.',
                              array('@url' => _icl_wrapper_url(_icl_wrapper_get_drupal_menu('admin/settings/language/add')))) . '</b>',
      ));
    return $form;
  }
  
  $messages = array();

  foreach ($translation_services as $module => $service) {
    if (module_hook($module, 'manage_translators_messages')) {
      $message = module_invoke($module, 'manage_translators_messages');
      if (!empty($message) && $message !== ' ') {
        $messages[] = $message;
      }
    }
  }

  if (!empty($messages)) {
    $messages = implode('<br />', $messages);
    $form['hook_messages'] = _icl_wrapper_form_create_markup(array(
        '#type' => 'markup',
        '#value' => '<div class="messages status">' . $messages . '</div>',
        '#weight' => -99
    ));
  }

  $hidden = ' style="display:none;"';
  $toggle_txt_open = $toggle_txt = t('Add translator') . ' >>';
  $toggle_txt_close = t('Add translator') . ' <<';
  if (isset($_GET['from']) || isset($_GET['to']) || isset($_GET['translation_service']) ) {
    $hidden = '';
    $toggle_txt = $toggle_txt_close;
  }

  $form['add_translator_form_toggle'] = array(
      '#type' => 'button',
      '#value' => $toggle_txt,
      '#id' => 'add_translator_form_toggle',
      '#prefix' => '<br style="clear:both;" />',
      '#attributes' => _icl_wrapper_form_create_attributes(array('onclick' => 'jQuery(\'#add-translator-form-wrapper\').slideToggle(function(){ if (jQuery(\'#add-translator-form-wrapper\').is(\':visible\')) { jQuery(\'#add_translator_form_toggle\').val(\'' . $toggle_txt_close . '\'); } else { jQuery(\'#add_translator_form_toggle\').val(\'' . $toggle_txt_open . '\');}}); return false;'))
  );

  $form['add_translator_form_wrapper_open'] = _icl_wrapper_form_create_markup(array(
      '#type' => 'markup',
      '#value' => '<div id="add-translator-form-wrapper"' . $hidden . '>'
  ));

  $form['add_translator'] = _icl_translate_translator_form('add');

  $form['add_translator_form_wrapper_close'] = _icl_wrapper_form_create_markup(array(
      '#type' => 'markup',
      '#value' => '</div>'
  ));
  
  $form['users'] = array(
    'name' => array(),
    'langs' => array(),
    'type' => array(),
    'action' => array(),
    '#theme' => 'icl_translator_translators_form',
  );

  if (isset($_GET['from']) && isset($_GET['to'])) {
    $args = array('from_lang' => $_GET['from'], 'to_lang' => $_GET['to']);
  } else {
    $args = NULL;
  }

  foreach ($translation_services as $module => $service) {
    if (module_hook($module, 'manage_translators_list')) {
      $users = module_invoke($module, 'manage_translators_list', $args);
      
      if (!empty($users) && is_array($users)) {

        foreach ($users as $key => $user) {

          if (empty($user) || !is_array($user)) {
            continue;
          }
          
          $form['users']['name'][] = isset($user['name']) ? _icl_wrapper_form_create_markup(array('#value' => $user['name'])) : '';
          // Set languages
          if (isset($user['langs'])) {
            $output = '';
            foreach ($user['langs'] as $from => $to_list) {
              foreach ($to_list as $to) {
                if ($output != '') {
                  $output .= '<br />';
                }
                $from = isset($languages_list[$from]->name) ? $languages_list[$from]->name : $from;
                $to = isset($languages_list[$to]->name) ? $languages_list[$to]->name : $to;
                $output .= t('@from_language to @target_language', array('@from_language' => $from,
                                                                         '@target_language' => $to));
              } 
            }
            $form['users']['langs'][] = _icl_wrapper_form_create_markup(array('#value' => $output));
          } else {
            $form['users']['langs'][] = '';
          }
          
          $form['users']['type'][] = isset($user['type']) ? _icl_wrapper_form_create_markup(array('#value' => $user['type'])) : '';
          $form['users']['action'][] = isset($user['action']) ? _icl_wrapper_form_create_markup(array('#value' => $user['action'])) : '';
        }
      }
    }
  }

  return $form; 
}