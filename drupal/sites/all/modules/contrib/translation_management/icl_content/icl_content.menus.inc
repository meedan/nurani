<?php
/*
 * $Id: icl_content.menus.inc
 * 
 * @file ICanLocalize translated menu handling
 */

function icl_content_sync_menus_waiting() {
  $icl_menus_to_sync = variable_get('icl_menus_to_sync', array());

  foreach($icl_menus_to_sync as $menu_data) {
    icl_content_menu_sync($menu_data[0],
                          $menu_data[1],
                          $menu_data[2],
                          $menu_data[3],
                          true,
                          true,
                          false,
                          false,
                          false
                          );
  }
  
  variable_set('icl_menus_to_sync', array());
}

function icl_content_menu_sync($source_menu_name,
                                $menu_to_sync_name,
                                $source_lang,
                                $target_lang,
                                $sync_weight,
                                $sync_parent,
                                $sync_missing_menu,
                                $sync_enabled,
                                $sync_expanded) {

  ////////////////////////////////////////////////////
  
  
  $sql = "
          SELECT 
            * 
          FROM 
            {menu_links}
          WHERE
            link_path LIKE 'node/%'
            AND menu_name = '%s'";
            
  $query = _icl_wrapper_db_query( $sql, $source_menu_name);
  while ( $request = db_fetch_object ( $query ) ) {
    $matches = array ();
    if (preg_match ( '/node\/(\d+)/', $request->link_path, $matches )) {
        
      // get the original node.
      
      $tnid = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT tnid FROM {node} WHERE nid=%d AND language='%s'", $matches[1], $source_lang));
      if ($tnid == $matches[1]) {
        // get the translated nodes
        $trans_sql = "
                SELECT 
                  * 
                FROM 
                  {node}
                WHERE
                  tnid=%d AND tnid <> nid AND language='%s'";

        $trans_query = _icl_wrapper_db_query( $trans_sql, $tnid, $target_lang);
        $translations_found = false;
        while ( $trans_request = db_fetch_object ( $trans_query ) ) {
          $translations_found = true;
          $translated_nid = $trans_request->nid;
          
          $trans_sql = "
                  SELECT 
                    * 
                  FROM 
                    {menu_links}
                  WHERE
                    link_path = 'node/%d'
                    AND menu_name = '%s'";
                    
          $trans_menu_query = _icl_wrapper_db_query( $trans_sql, $translated_nid, $menu_to_sync_name);
          $translated_menu_found = false;
          while ( $trans_menu = db_fetch_object ( $trans_menu_query ) ) {
            $translated_menu_found = true;
            // check weight
            if ($trans_menu->weight != $request->weight) {
              // The weights are different
              if ($sync_weight) {
                _icl_wrapper_db_query("UPDATE {menu_links} SET weight=%d WHERE mlid=%d", $request->weight, $trans_menu->mlid);
              }
            }

            // check enabled
            if ($trans_menu->hidden != $request->hidden) {
              // The hidden states are different
              if ($sync_enabled) {
                _icl_wrapper_db_query("UPDATE {menu_links} SET hidden=%d WHERE mlid=%d", $request->hidden, $trans_menu->mlid);
              }
            }

            // check expanded
            if ($trans_menu->expanded != $request->expanded) {
              // The expanded states are different
              if ($sync_expanded) {
                _icl_wrapper_db_query("UPDATE {menu_links} SET expanded=%d WHERE mlid=%d", $request->expanded, $trans_menu->mlid);
              }
            }

            // check the menu parents
            
            if ($request->plid != 0) {
              // The original has a parent menu
              $original_parent_link = db_fetch_object(_icl_wrapper_db_query('SELECT * FROM {menu_links} WHERE mlid=%d', $request->plid));
              $matches = array ();
              if (preg_match ( '/node\/(\d+)/', $original_parent_link->link_path, $matches )) {
                $parent_nid = $matches[1];
                $expected_translated_parent_nid = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT nid FROM {node} WHERE language='%s' AND tnid=%d", $target_lang, $parent_nid));
                if ($expected_translated_parent_nid) {
                  if ($trans_menu->plid == 0) {
                    // The translation doesn't have a parent
                    // try to find the parent menu
                            
                    if ($sync_parent) {
                      $parent_mlid = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT mlid FROM {menu_links} WHERE link_path = 'node/%d' AND menu_name = '%s'", $expected_translated_parent_nid, $menu_to_sync_name));
                      if ($parent_mlid) {
                        $item = menu_link_load($trans_menu->mlid);
                        $item['plid'] = $parent_mlid;
                        
                        menu_link_save($item);
                      }
                    }
                    
                  } else {
                    // The translation does have a parent
                    // make sure it is the correct one.
                    $translated_parent_link = db_fetch_object(_icl_wrapper_db_query('SELECT * FROM {menu_links} WHERE mlid=%d', $trans_menu->plid));
                    $matches = array ();
                    if (preg_match ( '/node\/(\d+)/', $translated_parent_link->link_path, $matches )) {
                      $translated_parent_nid = $matches[1];
                      if ($translated_parent_nid != $expected_translated_parent_nid) {
                        // The parent isn't correct.
                        if ($sync_parent) {
                          $parent_mlid = _icl_wrapper_db_result(_icl_wrapper_db_query("SELECT mlid FROM {menu_links} WHERE link_path = 'node/%d' AND menu_name = '%s'", $expected_translated_parent_nid, $menu_to_sync_name));
                          if ($parent_mlid) {
                            
                            $item = menu_link_load($trans_menu->mlid);
                            $item['plid'] = $parent_mlid;
                            
                            menu_link_save($item);
                          }
                        }
                      }
                    }
                  }
                }
              }
            } else {
              // The original doesn't have a parent
              if ($trans_menu->plid != 0) {
                // The menu should not have a parent because the original doesn't.
                if ($sync_parent) {
                  $item = menu_link_load($trans_menu->mlid);
                  $item['plid'] = 0;
                  
                  menu_link_save($item);
                }
              }
            }
          
          }
        
          if (!$translated_menu_found) {
            // no translated menu was found
            // we can create one if the node is translated.
            if ($sync_missing_menu) {
              // load original menu
              $item = menu_link_load($request->mlid);
              $menu = array('link_title' => $trans_request->title, 'mlid' => 0, 'plid' => 0, 'menu_name' => $item['menu_name'], 'weight' => $item['weight'], 'options' => $item['options'], 'module' => 'menu', 'expanded' => $item['expanded'], 'hidden' => $item['hidden'], 'has_children' => 0, 'customized' => $item['customized'], 'localized_options' => $item['localized_options']);
              $menu['link_path'] = 'node/' . $trans_request->nid;
              $menu['router_path'] = 'node/%';
              $menu['menu_name'] = $menu_to_sync_name;
              
              menu_link_save($menu);
              
            }
          }
        }
    
      }
    
    }
      
  }
  
  cache_clear_all(NULL, 'cache_menu');
  
}  

function icl_content_menu_overview_form_alter(&$form, $form_state) {
  
  if (module_exists ( 'i18n' )) {  
    $default = language_default();
    $languages = language_list('enabled');
    $languages = $languages[1];
    
    $variables = variable_get('i18n_variables', array());
    
    $i18n_v_orig = _i18n_variable_init($default->language);
    foreach ($variables as $v_name) {
      if ($i18n_v_orig[$v_name] == $form['#menu']['menu_name']) {
        // this menu is set via a i18n variable
        // see if there are any translated menus
  
        $found = array();
        
        foreach($languages as $lang) {
          if ($lang->language != $default->language) {
            $i18n_v_target = _i18n_variable_init($lang->language);
            if (isset($i18n_v_target[$v_name])) {
              $found[$lang->language] = $i18n_v_target[$v_name];            
            }
          }          
        }
        
        if (sizeof($found) > 0) {
          $form ['icl_content_menu_translation'] = array(
              '#type' => 'fieldset',
              '#title' => t("Translated Menu Synchronization"),
              '#collapsible' => FALSE,
              '#collapsed' => FALSE,
              '#weight' => -1,
              '#description' => t('Keep the translated menus in sync with changes to this menu.'),
            );
          $form['#icl_menu_data'] = $found;
          
          // put before the submit button
          $form['submit']['#weight'] = 0;
          
          $form ['icl_content_menu_translation'] ['sync_items'] = array (
              '#type' => 'checkboxes',
              '#options' => array('sync_order' => t('Synchronize menu order.'),
                                  'sync_parent' => t('Synchronize menu hierarchy'),
                                  'sync_enabled' => t('Synchronize enabled state'),
                                  'sync_expanded' => t('Synchronize expanded state')),
              '#default_value' => variable_get('icl_menu_sync', array()),
              );

          if (isset($form['#submit'])) {
            $form['#submit'] = array('menu_overview_form_submit', 'icl_content_menu_overview_form_submit');
          } else {
            $form['#submit'][] = 'icl_content_menu_overview_form_submit';
          }


        }
        
      }
      
    }
  }  
}

function icl_content_menu_overview_form_submit($form, &$form_state) {
  $sync = $form_state['values']['icl_content_menu_translation']['sync_items'];
  variable_set('icl_menu_sync', $sync);
  
  $sync_required = false;
  
  foreach($sync as $key => $state) {
    if ($key == (string)$state) {
      $sync_required = true;
    }
  }
  
  if ($sync_required) {

    $default = language_default();
  
    foreach ($form['#icl_menu_data'] as $lang => $target_menu) {
      icl_content_menu_sync($form['#menu']['menu_name'],
                            $target_menu,
                            $default->language,
                            $lang,
                            (string)$sync['sync_order'] == 'sync_order',
                            (string)$sync['sync_parent'] == 'sync_parent',
                            false, // don't sync missing menus
                            (string)$sync['sync_enabled'] == 'sync_enabled',
                            (string)$sync['sync_expanded'] == 'sync_expanded'
                          );
    }
  }
}
