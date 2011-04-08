<?php


module_load_include ( 'inc', 'icl_core', 'icl_core.constants' );
module_load_include ( 'inc', 'icl_core', 'icl_core.settings' );


function icl_status_check() {
  include_once 'includes/install.inc';

  $requirements = array();

  if (variable_get ( 'icl_core_project_kind_options', 2 ) == 0) {
    $requirements['project_kind'] = array(
                                        'title' => t('Kind of website'),
                                        'description' => t("You have set the website kind to 'Test site'. Translators will not be assigned to translate this site. Go to <a href='../settings/icl-core'>ICanLocalize Core</a> and change the website kind."),
                                        'severity' => REQUIREMENT_WARNING,
                                        );
    
  }
  
/*  
  $requirements['languages'] = array(
                                      'title' => t('Translation languges'),
                                      'description' => t('This section lists which languages already have assigned translators.'),
                                      'severity' => REQUIREMENT_INFO,
                                      );
  
  // check translation languages.
  $icl_core_languages = variable_get('icl_core_languages', array());
  $icl_core_languages = variable_get('icl_core_languages', array());
  
  if (isset($icl_core_languages['have_translators'])) {
    foreach($icl_core_languages['have_translators'] as $from_lang => $to_langs) {
      $from_lang = icl_core_get_drupal_language_names_from_ican_language($from_lang);
      foreach($to_langs as $to_lang => $available) {
        $to_lang = icl_core_get_drupal_language_names_from_ican_language($to_lang);
        if ($available) {
          $requirements['icl_languages_'.$from_lang.'_'.$to_lang] = array(
                                                'title' => $to_lang,
                                                'value' => t('Translators available for @from to @to', array('@from' => $from_lang, '@to' => $to_lang)),
                                                'severity' => REQUIREMENT_OK,
                                                );
        } else {
          $requirements['icl_languages_'.$from_lang.'_'.$to_lang] = array(
                                                'title' => $to_lang,
                                                'value' => t('No translators assigned yet for @from to @to', array('@from' => $from_lang, '@to' => $to_lang)),
                                                'severity' => REQUIREMENT_WARNING,
                                                );
        }
      }
    }
  }
*/

  $requirements['Multi-lingual-support'] = array(
                                      'title' => t('Multilingual support'),
                                      'description' => t('This section details multilingual support for different content types.'),
                                      'severity' => REQUIREMENT_INFO,
                                      );
  
  $query = _icl_wrapper_db_query("SELECT * FROM {node_type}");
  while($result = db_fetch_object($query)) {

    $enabled = variable_get('language_content_type_'. $result->type, 0);
    if ($enabled == 2) {
      $requirements['language_content_type_'. $result->type] = array(
                                          'title' => $result->name,
                                          'value' => t('Content type @type has multilingual support enabled', array('@type' => $result->name)),
                                          'severity' => REQUIREMENT_OK,
                                          );
      module_load_include ( 'inc', 'icl_content', 'icl_content.contentype' );
      $fields = icl_content_get_node_type_fields ( $result->type );
      // don't translate these fields normally.
      unset($fields['date']);
      unset($fields['log']);
      unset($fields['name']);
      $translate_fields = variable_get ( 'icl_content_node_type_fields', array (
          $result->type => array (
              'title', 
              'body' ) ) );
      
      $translate_fields = $translate_fields[$result->type];
      
      if ($translate_fields == null) {
        $translate_fields = array();
      }
      
      $untranslated_fields = array();
      foreach ($fields as $field => $value) {
        if (!in_array($field, $translate_fields)) {
          $untranslated_fields[] = $field;
        }
      }
      
      if (sizeof($untranslated_fields) > 0) {
        $requirements['language_content_type_'. $result->type]['severity'] = REQUIREMENT_WARNING;
        $warning = t('Not all fields will be sent for translation.<br>The following fields wont be sent for translation<br><ul>');
        
        foreach ($untranslated_fields as $field) {
          $warning .= '<li>' . $fields[$field] . '</li>';
        }
        $warning .= '</ul>';

        $link = _icl_wrapper_url(_icl_wrapper_get_drupal_menu('admin/content/node-type/'.str_replace('_', '-', $result->type)));
        $warning .= t('To enable translation of these fields, go to <a href="@link">@type edit</a> and enable it in the Content Translation section', array('@link' => $link, '@type' => $result->type));
        
        $requirements['language_content_type_'. $result->type]['description'] = $warning;
      }
      

    } else {
      $link = _icl_wrapper_url(_icl_wrapper_get_drupal_menu('admin/content/node-type/'.str_replace('_', '-', $result->type)));
      $requirements['language_content_type_'. $result->type] = array(
                                          'title' => $result->name,
                                          'value' => t('Multilingual support is not enabled for content type @type', array('@type' => $result->name)),
                                          'description' => t('To enable multilingual support, go to <a href="@link">@type edit</a> and enable it in the Workflow settings', array('@link' => $link, '@type' => $result->type)),
                                          'severity' => REQUIREMENT_WARNING,
                                          );
      
    }
    
  }
  $table_name = _icl_wrapper_table_name('boxes');
  $block_count = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT COUNT(*) from {" . $table_name . "}"));
  if ($block_count > 0) {
    $requirements['block-translation-support'] = array(
                                        'title' => t('Block Translation'),
                                        'description' => t('This section details status for translation of blocks.'),
                                        'severity' => REQUIREMENT_INFO,
                                        );

    if (module_exists ( 'i18nblocks' )) {
      $requirements['i18nblocks'] = array(
                                            'title' => t('i18n Blocks'),
                                            'value' => t('i18nblocks module enabled'),
                                            'severity' => REQUIREMENT_OK,
                                            );
      $table_name = _icl_wrapper_table_name('boxes');
      $block_query = _icl_wrapper_db_query("SELECT * from {" . $table_name . "}");
      $non_multilingual_blocks = array();
      $non_all_language_blocks = array();
      while ($block_result = db_fetch_object($block_query)) {
        $block_language = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT language from {i18n_blocks} where delta = %d", $block_result->bid));
        if ($block_language === FALSE) {
          $non_multilingual_blocks[] = $block_result;
        } else if ($block_language != "") {
          $non_all_language_blocks[] = $block_result;
        }
      }
      
      if (sizeof($non_multilingual_blocks) > 0) {
        
        $warning = t("Not all blocks have been enabled for multilingual support.<br>The following blocks can't be sent for translation.<br><ul>");
        
        foreach ($non_multilingual_blocks as $block) {
          $warning .= '<li><a href="' . _icl_wrapper_url(_icl_wrapper_get_drupal_menu('admin/build/block/configure/block/'. $block->bid)) . '">' . $block->info . '</a></li>';
        }
        $warning .= '</ul>' . t('Set the language to "All languages (Translatable)" to allow the block to be translated with the ICanLocalize system.');

        $requirements['i18nblocks_non_multi_block'] = array(
                                                'title' => t('Non multilingual blocks'),
                                                'description' => $warning,
                                                'severity' => REQUIREMENT_WARNING,
                                                );
      }
      if (sizeof($non_all_language_blocks) > 0) {
        
        $warning = t('Only blocks set to "All languages (Translatable)" are supported.');
        $warning .= t("<br>The following blocks can't be sent for translation.<br><ul>");
        
        foreach ($non_all_language_blocks as $block) {
          $warning .= '<li><a href="' . _icl_wrapper_url(_icl_wrapper_get_drupal_menu('admin/build/block/configure/block/'. $block->bid)) . '">' . $block->info . '</a></li>';
        }
        $warning .= '</ul>' . t('Set the language to "All languages (Translatable)" to allow the block to be translated with the ICanLocalize system.');

        $requirements['i18nblocks_non_allblock'] = array(
                                                'title' => t('Non translatable blocks'),
                                                'description' => $warning,
                                                'severity' => REQUIREMENT_WARNING,
                                                );
      }
    } else {
      $requirements['i18nblocks'] = array(
                                            'title' => t('i18n Blocks'),
                                            'value' => t('i18nblocks module is not enabled'),
                                            'description' => t('Enable the i18nblocks module if you want to have blocks translated.'),
                                            'severity' => REQUIREMENT_WARNING,
                                            );
    }
  }

  // Contact form translation.

  if (module_exists('contact')) {
    $requirements['contact-translation-support'] = array(
                                        'title' => t('Contact Form Translation'),
                                        'description' => t('This section details status for translation of the standard contact form.'),
                                        'severity' => REQUIREMENT_INFO,
                                        );

    if (module_exists ( 'i18nmenu' )) {
      $requirements['i18nmenu'] = array(
                                            'title' => t('i18n Menu'),
                                            'value' => t('i18nmenu module enabled'),
                                            'description' => t('The i18nmenu module is required so that the contact form menu can be translated.'),
                                            'severity' => REQUIREMENT_OK,
                                            );
      
      $menu_title = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT link_title FROM {menu_links} where link_path = 'contact' and module='menu'"));
      if ($menu_title === FALSE) {
        $requirements['contact_menu'] = array(
                                              'title' => t('Contact Menu'),
                                              'value' => t('The standard contact form menu can not be translated.'),
                                              'description' => t('A new contact from menu needs to be created so that contact form menu can be translated.<br><ul><li>Create a new menu - path should be "contact"</li><li>Disable standard contact form menu</li></ul>'),
                                              'severity' => REQUIREMENT_WARNING,
                                              );
        
      } else {
        $requirements['contact_menu'] = array(
                                              'title' => t('Contact Menu'),
                                              'value' => t('A user defined contact form menu is available.'),
                                              'severity' => REQUIREMENT_OK,
                                              );
        
      }
      
    } else {
      $requirements['i18nmenu'] = array(
                                            'title' => t('i18n Menu'),
                                            'value' => t('i18nmenu module not enabled'),
                                            'description' => t('Enable the i18nmenu module so that the contact form menu can be translated.'),
                                            'severity' => REQUIREMENT_WARNING,
                                            );
    }
  }
  
  $requirements['i18n-support'] = array(
                                      'title' => t('i18n status'),
                                      'description' => t('This section details status for i18n modules.'),
                                      'severity' => REQUIREMENT_INFO,
                                      );

  if (module_exists ( 'i18ntaxonomy' )) {
    $requirements['i18ntaxonomy'] = array(
                                          'title' => t('i18n Taxonomy'),
                                          'value' => t('i18ntaxonomy module enabled'),
                                          'severity' => REQUIREMENT_OK,
                                          );
  } else {
    $requirements['i18ntaxonomy'] = array(
                                          'title' => t('i18n Taxonomy'),
                                          'value' => t('i18ntaxonomy module is not enabled'),
                                          'description' => t('Enable the i18ntaxonomy module if you want to have taxonomy translated.'),
                                          'severity' => REQUIREMENT_WARNING,
                                          );
  }

  if (module_exists ( 'i18nblocks' )) {
    $requirements['i18nblocks'] = array(
                                          'title' => t('i18n Blocks'),
                                          'value' => t('i18nblocks module enabled'),
                                          'severity' => REQUIREMENT_OK,
                                          );
  } else {
    $requirements['i18nblocks'] = array(
                                          'title' => t('i18n Blocks'),
                                          'value' => t('i18nblocks module is not enabled'),
                                          'description' => t('Enable the i18nblocks module if you want to have taxonomy translated.'),
                                          'severity' => REQUIREMENT_WARNING,
                                          );
  }

  variable_set('icl_status_check_done', TRUE);

  return _icl_wrapper_theme('status_report', array('requirements' => $requirements));

}