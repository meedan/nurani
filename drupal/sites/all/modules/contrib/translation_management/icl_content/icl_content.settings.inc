<?php
/*
 * $Id: icl_content.settings.inc
 * 
 * @file Settings screen for icl_content
 */

/**
 * This is a page callback for the ICanLocalize Core admin page
 *
 * @return array The system settings form.
 */
function icl_content_admin_settings() {
  $form = array ();
  
  $form ['icl_content_translation'] = array(
    '#type' => 'fieldset',
    '#title' => t("Content translation"),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  
  $form['icl_content_translation']['icl_content_num_items_to_display'] = array(
    '#type' => 'select',
    '#title' => t('Number of items to display'),
    '#options' => drupal_map_assoc(array(50, 100, 200, 500, 1000)),
    '#description' => t('Show this many items when displaying translation jobs on the dashboard and elsewhere.'),
    '#default_value' => variable_get('icl_content_num_items_to_display', 50)
  );
  
  $form ['icl_content_translation']['icl_content_publish_options'] = array (
      '#type' => 'radios', 
      '#title' => t ( 'Publish state for completed translations' ), 
      '#multiple' => FALSE, 
      '#options' => array (
          ICL_CONTENT_PUBLISH_TRANSLATIONS => t ( 'Publish when received' ), 
          ICL_CONTENT_DONT_PUBLISH_TRANSLATIONS => t ( 'Don\'t publish, I will review them and publish manually' ) ), 
      '#default_value' => variable_get ( 'icl_content_publish_options', ICL_CONTENT_PUBLISH_TRANSLATIONS ), 
      '#description' => t ( 'Choose if translations should be published when received. Note: If Publish is selected, the translation will only be published if the original node is published when the translation is received.' ) );

  $form ['icl_content_translation']['icl_content_delete_options'] = array (
      '#type' => 'radios', 
      '#title' => t ( 'Select the method to handle node deletetion for translated nodes' ), 
      '#multiple' => FALSE, 
      '#options' => array (
          ICL_CONTENT_DELETE_MANUAL => t ( 'I will delete the translations manually' ), 
          ICL_CONTENT_DELETE_AUTOMATIC => t ( 'Automatically delete all translations' ) ), 
      '#default_value' => variable_get ( 'icl_content_delete_options', ICL_CONTENT_DELETE_MANUAL ), 
      '#description' => t ( 'Choose how the system will handle node deletion' ) );
  
  $form ['icl_content_translation']['icl_content_update_links_options'] = array (
      '#type' => 'radios', 
      '#title' => t ( 'Update links to internal pages so that translations link to other translations and not to original language nodes' ), 
      '#multiple' => FALSE, 
      '#options' => array (
          ICL_CONTENT_UPDATE_LINKS => t ( 'Update links' ), 
          ICL_CONTENT_DONT_UPDATE_LINKS => t ( "Don't update links" ) ), 
      '#default_value' => variable_get ( 'icl_content_update_links_options', ICL_CONTENT_UPDATE_LINKS ), 
      '#description' => t ( 'Example: Supposing /node/X is in English and /es/node/Y is the corresponding node in Spanish. When we translate a page in English that links to /node/X the translation should link to /es/node/Y.' ) );

  /////////////////////

  $form ['icl_content_menu_translation'] = array(
    '#type' => 'fieldset',
    '#title' => t("Menu translation"),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  $variables = variable_get('i18n_variables', array());
  
  $form ['icl_content_menu_translation']['icl_content_menu_options'] = array (
      '#type' => 'radios', 
      '#title' => t ( 'Select how you want the translated menu/s to be constructed' ), 
      '#multiple' => FALSE, 
      '#options' => array (
          ICL_CONTENT_MENU_ORIGINAL => t ( 'Save translations in the same menu as original' ), 
          ICL_CONTENT_MENU_SEPARATE => t ( 'Save translations to a separate menu for each language' ) ), 
      '#default_value' => variable_get ( 'icl_content_menu_options', ICL_CONTENT_MENU_ORIGINAL ), 
      '#description' => t ( 'Choose separate menus for larger menu structures. This requires setting multilingual variables. See: ' ) . '<a href="http://drupal.org/node/313302">http://drupal.org/node/313302</a>' );


  /////////////////////
  
  /*$form ['icl_content_comments'] = array(
    '#type' => 'fieldset',
    '#title' => t("Comment translation"),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  
  $form ['icl_content_comments']['icl_content_comment_view'] = array(
    '#type' => 'checkbox',
    '#title' => t("Translate comments when viewing"),
    '#default_value' => variable_get ('icl_content_comment_view', 1),
    '#description' => t("Use Google AJAX Language API to view comments in translated content in the original language."),
  );

  $form ['icl_content_comments']['icl_content_comment_translate_replies'] = array(
    '#type' => 'checkbox',
    '#title' => t("Translate my replies"),
    '#default_value' => variable_get ('icl_content_comment_translate_replies', 1),
    '#description' => t("Translate replies when replying to a comment on translated content."),
  );*/

  return $form;
  //return system_settings_form ( $form );
}