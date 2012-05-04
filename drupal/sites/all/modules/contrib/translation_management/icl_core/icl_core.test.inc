<?php

class IclTestCase extends DrupalWebTestCase {
  
  function setUp($full_setup = TRUE) {
    if ($full_setup) {
      parent::setUp('locale',
                    'translation',
                    'icl_core',
                    'icl_content',
                    'taxonomy',
                    'i18n',
                    'i18ncontent',
                    'i18nmenu',
                    'i18nstrings',
                    'i18ntaxonomy');
  
      // We have to set to sandbox mode.
      variable_set ( 'icl_core_mode', ICL_MODE_SANDBOX );
  
      $this->admin_user = $this->drupalCreateUser(array('administer languages',
                                                        'administer content types',
                                                        'access administration pages',
                                                        'administer icanlocalize',
                                                        'create page content',
                                                        'administer taxonomy',
                                                        'submit content for translation',
                                                        'administer menu'));
  
      $this->drupalLogin($this->admin_user);
      
      // Add languages.
      $this->addLanguage('en');
      $this->addLanguage('es');
      $this->addLanguage('de');
      $this->addLanguage('fr');
      $this->addLanguage('zh-hans');
  
      // Set page content type to use multilingual support with translation.
      $this->drupalGet(_icl_wrapper_get_drupal_menu('admin/content/node-type/page'));
      $this->drupalPost(_icl_wrapper_get_drupal_menu('admin/content/node-type/page'), array('language_content_type' => '2'), t('Save content type'));
      $this->assertRaw(t('The content type %type has been updated.', array('%type' => 'Page')), t('Page content type has been updated.'));
      
      $this->drupalGet(_icl_wrapper_get_drupal_menu('admin/content/taxonomy/add/vocabulary'));
      $edit = array();
      $edit['i18nmode'] = '2';
      $edit['name'] = 'Tags';
      $edit['nodes[page]'] = TRUE;
      $edit['tags'] = TRUE;
      $this->drupalPost(_icl_wrapper_get_drupal_menu('admin/content/taxonomy/add/vocabulary'), $edit, t('Save'));
      
      $this->assertRaw(t('Created new vocabulary'), t('Vocabulary created'));
  
      $this->drupalGet(_icl_wrapper_get_drupal_menu('admin/content/node-type/page'));
      $edit = array();
      $edit['language_content_type'] = '2';
      $edit['icl_content_node_type_fields[title]'] = TRUE;
      $edit['icl_content_node_type_fields[body]'] = TRUE;
      $edit['icl_content_node_type_fields[link_title]'] = TRUE;
      $edit['icl_content_node_type_fields[taxonomy[1]]'] = TRUE;
      $this->drupalPost(_icl_wrapper_get_drupal_menu('admin/content/node-type/page'), $edit, t('Save content type'));
      $this->assertRaw(t('The content type %type has been updated.', array('%type' => 'Page')), t('Page content type has been updated.'));
    } else {
     parent::setUp();

      // We have to set to sandbox mode.
      variable_set ( 'icl_core_mode', ICL_MODE_SANDBOX );
  
    }
  }

    
  /**
   * Install a the specified language if it has not been already. Otherwise make sure that
   * the language is enabled.
   *
   * @param string $language_code The langauge code the check.
   *
   * Copied from translation_overview.test
   */
  
  function addLanguage($language_code) {
    // Check to make sure that language has not already been installed.
    $this->drupalGet(_icl_wrapper_get_drupal_menu('admin/settings/language'));

    if (strpos($this->drupalGetContent(), 'enabled[' . $language_code . ']') === FALSE) {
      // Doesn't have language installed so add it.
      $edit = array();
      $edit['langcode'] = $language_code;
      $this->drupalPost(_icl_wrapper_get_drupal_menu('admin/settings/language/add'), $edit, t('Add language'));

      $languages = language_list('language', TRUE); // make sure not using cached version
      $this->assertTrue(array_key_exists($language_code, $languages), t('Language [' . $language_code . '] was installed successfully.'));
      if (array_key_exists($language_code, $languages)) {
#        $this->assertRaw(t('The language %language has been created and can now be used. More information is available on the <a href="@locale-help">help screen</a>.', array('%language' => t($languages[$language_code]->name), '@locale-help' => url(_icl_wrapper_url(_icl_wrapper_get_drupal_menu('admin/help/locale')))), t('Language has been created.'));
      }
    }
    else {
      // Ensure that it is enabled.
      $this->assertTrue(true, 'Language [' . $language_code . '] already installed.');
      $this->drupalPost(NULL, array('enabled[' . $language_code . ']' => TRUE), t('Save configuration'));

      $this->assertRaw(t('Configuration saved.'), t('Language successfully enabled.'));
    }
  }

  /**
   * Create a page in the specified language.
   *
   * @param string $title Title of page in specified language.
   * @param string $body Body of page in specified language.
   * @param string $language Langauge code.
   *
   * Copied from translation_overview.test
   */
  
  function createPage($title, $body, $language, $tags = "", $menu = "") {
    $edit = array();
    $edit['title'] = $title;
    $edit['body'] = $body;
    $edit['language'] = $language;
    $edit['taxonomy[tags][1]'] = $tags;
    $edit['menu[link_title]'] = $menu;
    $this->drupalPost('node/add/page', $edit, t('Save'));
    $this->assertRaw(t('Page %title has been created.', array('%title' => $edit['title'])), t('Page created.'));

    // Check to make sure the node was created.
    $node = node_load(array('title' => $edit['title']));
    $this->assertTrue($node, t('Node found in database.'));

    return $node;
  }

}

?>