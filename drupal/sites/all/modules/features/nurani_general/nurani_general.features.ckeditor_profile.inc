<?php

/**
 * Implementation of hook_ckeditor_profile_defaults().
 */
function nurani_general_ckeditor_profile_defaults() {
  $data = array(
    'Advanced' => array(
      'name' => 'Advanced',
      'settings' => array(
        'allow_user_conf' => 'f',
        'filters' => array(
          'filter/3' => 0,
          'filter/0' => 1,
          'nurani_glossary/0' => 0,
        ),
        'ss' => '2',
        'min_rows' => '1',
        'excl_mode' => '0',
        'excl' => '',
        'simple_incl' => '',
        'default' => 't',
        'show_toggle' => 't',
        'popup' => 'f',
        'skin' => 'kama',
        'uicolor' => 'default',
        'uicolor_textarea' => '<p>
	Click the <strong>UI Color Picker</strong> button to set your color preferences.</p>
',
        'uicolor_user' => 'default',
        'toolbar' => '[
    [\'Source\'],
    [\'Cut\',\'Copy\',\'Paste\',\'PasteText\',\'PasteFromWord\',\'-\',\'SpellChecker\',\'Scayt\'],
    [\'Undo\',\'Redo\',\'Find\',\'Replace\',\'-\',\'SelectAll\',\'RemoveFormat\'],
    [\'Image\',\'Flash\',\'Table\',\'HorizontalRule\',\'Smiley\',\'SpecialChar\'],
    \'/\',
    [\'Bold\',\'Italic\',\'Underline\',\'Strike\',\'-\',\'Subscript\',\'Superscript\'],
    [\'NumberedList\',\'BulletedList\',\'-\',\'Outdent\',\'Indent\',\'Blockquote\'],
    [\'JustifyLeft\',\'JustifyCenter\',\'JustifyRight\',\'JustifyBlock\',\'-\',\'BidiRtl\',\'BidiLtr\'],
    [\'Link\',\'Unlink\',\'Anchor\',\'Linkit\',\'LinkToNode\',\'LinkToMenu\'],
    \'/\',
    [\'Format\',\'Font\',\'FontSize\'],
    [\'TextColor\',\'BGColor\'],
    [\'Maximize\',\'ShowBlocks\'],
    [\'DrupalBreak\',\'DrupalPageBreak\']
]',
        'expand' => 't',
        'width' => '100%',
        'lang' => 'en',
        'auto_lang' => 't',
        'language_direction' => 'default',
        'enter_mode' => 'br',
        'shift_enter_mode' => 'br',
        'font_format' => 'p;div;pre;address;h1;h2;h3;h4;h5;h6',
        'custom_formatting' => 'f',
        'formatting' => array(
          'custom_formatting_options' => array(
            'indent' => 'indent',
            'breakBeforeOpen' => 'breakBeforeOpen',
            'breakAfterOpen' => 'breakAfterOpen',
            'breakAfterClose' => 'breakAfterClose',
            'breakBeforeClose' => 0,
            'pre_indent' => 0,
          ),
        ),
        'css_mode' => 'none',
        'css_path' => '',
        'css_style' => 'theme',
        'styles_path' => '',
        'filebrowser' => 'none',
        'filebrowser_image' => '',
        'filebrowser_flash' => '',
        'UserFilesPath' => '%b%f/',
        'UserFilesAbsolutePath' => '%d%b%f/',
        'ckeditor_load_method' => 'ckeditor.js',
        'ckeditor_load_time_out' => '0',
        'forcePasteAsPlainText' => 'f',
        'html_entities' => 't',
        'scayt_autoStartup' => 'f',
        'theme_config_js' => 'f',
        'js_conf' => '',
        'loadPlugins' => array(
          'tableresize' => array(
            'name' => 'tableresize',
            'desc' => 'Table Resize plugin',
            'path' => '%base_path%%editor_path%plugins/tableresize/',
            'buttons' => FALSE,
            'default' => 't',
          ),
        ),
        'excl_regex' => '',
        'simple_incl_regex' => '',
      ),
      'roles' => array(
        'administrator' => 'administrator',
      ),
    ),
    'CKEditor Global Profile' => array(
      'name' => 'CKEditor Global Profile',
      'settings' => array(
        'rank' => array(
          '0' => '3',
        ),
        'excl_mode' => '0',
        'excl' => 'admin/user/settings.edit-user-mail-*
*.edit-pages
*.edit-pathauto-ignore-words
*.edit-recipients
*.edit-reply
*.edit-description
*.edit-synonyms
*.edit-img-assist-textareas
*.edit-img-assist-paths
*.edit-nodewords-description
*.edit-nodewords-description-value
admin/content/nodewords/global*
*.edit-relatedlinks-fieldset-relatedlinks
*.edit-allowed-values-php
*.edit-allowed-values
*.edit-update-notify-emails
*.edit-googleanalytics-*
*.edit-piwik-*
*.edit-feedburner-useragents
*@*.edit-webform-*
webform@*.edit-extra-items
admin/*/logintoboggan
admin/settings/actions/configure/*
*.edit-target
*.edit-wysiwyg-filter-*
admin/build/views/*
',
        'simple_incl' => '*.edit-signature
admin/settings/site-information.*
admin/settings/site-maintenance.*
*.edit-page-help
*.edit-user-registration-help
*.edit-user-picture-guidelines
',
        'ckeditor_path' => '%m/ckeditor',
        'ckeditor_local_path' => '',
        'ckeditor_plugins_path' => '%m/plugins',
        'ckeditor_plugins_local_path' => '',
        'show_fieldnamehint' => 't',
        'loadPlugins' => array(),
        'excl_regex' => '#(?:^.*:.*@admin/user/settings\\.edit\\-user\\-mail\\-.*$)|(?:^.*:.*@.*\\.edit\\-pages$)|(?:^.*:.*@.*\\.edit\\-pathauto\\-ignore\\-words$)|(?:^.*:.*@.*\\.edit\\-recipients$)|(?:^.*:.*@.*\\.edit\\-reply$)|(?:^.*:.*@.*\\.edit\\-description$)|(?:^.*:.*@.*\\.edit\\-synonyms$)|(?:^.*:.*@.*\\.edit\\-img\\-assist\\-textareas$)|(?:^.*:.*@.*\\.edit\\-img\\-assist\\-paths$)|(?:^.*:.*@.*\\.edit\\-nodewords\\-description$)|(?:^.*:.*@.*\\.edit\\-nodewords\\-description\\-value$)|(?:^.*:.*@admin/content/nodewords/global.*\\..*$)|(?:^.*:.*@.*\\.edit\\-relatedlinks\\-fieldset\\-relatedlinks$)|(?:^.*:.*@.*\\.edit\\-allowed\\-values\\-php$)|(?:^.*:.*@.*\\.edit\\-allowed\\-values$)|(?:^.*:.*@.*\\.edit\\-update\\-notify\\-emails$)|(?:^.*:.*@.*\\.edit\\-googleanalytics\\-.*$)|(?:^.*:.*@.*\\.edit\\-piwik\\-.*$)|(?:^.*:.*@.*\\.edit\\-feedburner\\-useragents$)|(?:^.*:.*@.*\\.edit\\-webform\\-.*$)|(?:^.*:webform@.*\\.edit\\-extra\\-items$)|(?:^.*:.*@admin/.*/logintoboggan\\..*$)|(?:^.*:.*@admin/settings/actions/configure/.*\\..*$)|(?:^.*:.*@.*\\.edit\\-target$)|(?:^.*:.*@.*\\.edit\\-wysiwyg\\-filter\\-.*$)|(?:^.*:.*@admin/build/views/.*\\..*$)#',
        'simple_incl_regex' => '#(?:^.*:.*@.*\\.edit\\-signature$)|(?:^.*:.*@admin/settings/site\\-information\\..*$)|(?:^.*:.*@admin/settings/site\\-maintenance\\..*$)|(?:^.*:.*@.*\\.edit\\-page\\-help$)|(?:^.*:.*@.*\\.edit\\-user\\-registration\\-help$)|(?:^.*:.*@.*\\.edit\\-user\\-picture\\-guidelines$)#',
      ),
      'roles' => array(),
    ),
    'Default' => array(
      'name' => 'Default',
      'settings' => array(
        'allow_user_conf' => 'f',
        'min_rows' => 1,
        'excl_mode' => 0,
        'filebrowser' => 'none',
        'quickupload' => 'f',
        'excl' => '',
        'simple_incl' => '',
        'ss' => '2',
        'filters' => array(
          'filter/0' => 1,
        ),
        'default' => 't',
        'show_toggle' => 't',
        'popup' => 'f',
        'skin' => 'kama',
        'toolbar' => '
[
    [ \'Format\', \'Bold\', \'Italic\', \'-\', \'NumberedList\',\'BulletedList\', \'-\', \'Link\', \'Unlink\', \'Image\' ]
]
      ',
        'expand' => 't',
        'width' => '100%',
        'lang' => 'en',
        'auto_lang' => 't',
        'language_direction' => 'default',
        'enter_mode' => 'p',
        'shift_enter_mode' => 'br',
        'font_format' => 'p;div;pre;address;h1;h2;h3;h4;h5;h6',
        'format_source' => 't',
        'format_output' => 't',
        'custom_formatting' => 'f',
        'formatting' => array(
          'custom_formatting_options' => array(
            'indent' => 'indent',
            'breakBeforeOpen' => 'breakBeforeOpen',
            'breakAfterOpen' => 'breakAfterOpen',
            'breakAfterClose' => 'breakAfterClose',
          ),
        ),
        'css_mode' => 'theme',
        'css_path' => '',
        'user_choose' => 'f',
        'show_fieldnamehint' => 't',
        'ckeditor_load_method' => 'ckeditor.js',
        'ckeditor_load_time_out' => 0,
        'scayt_autoStartup' => 'f',
        'excl_regex' => '',
        'simple_incl_regex' => '',
      ),
      'roles' => array(
        'anonymous user' => 'anonymous user',
      ),
    ),
    'Nurani' => array(
      'name' => 'Nurani',
      'settings' => array(
        'allow_user_conf' => 'f',
        'filters' => array(
          'filter/3' => 0,
          'filter/0' => 1,
          'wysiwyg_filter/0' => 0,
        ),
        'ss' => '2',
        'min_rows' => '1',
        'excl_mode' => '0',
        'excl' => '*.edit-export
node_export@node/add/node_export.edit-code
text@node/add/text.edit-field-description-0-value
admin/build/block/configure/boxes/discussion_info.edit-body
*.edit-field-education-0-value
*.edit-field-societies-0-value
*.edit-field-experience-0-value
*.edit-field-research-0-value
*.edit-field-publications-0-value


',
        'simple_incl' => '',
        'default' => 't',
        'show_toggle' => 'f',
        'popup' => 'f',
        'skin' => 'kama',
        'uicolor' => 'default',
        'uicolor_textarea' => '<p>
	Click the <strong>UI Color Picker</strong> button to set your color preferences.</p>
',
        'uicolor_user' => 'default',
        'toolbar' => '[
    [\'Source\'],
    [\'Copy\',\'Cut\',\'Paste\',\'Undo\',\'Redo\'],
    [\'SpellChecker\',\'Scayt\'],
    [\'Bold\',\'Italic\',\'Superscript\']
]',
        'expand' => 't',
        'width' => '100%',
        'lang' => 'en',
        'auto_lang' => 't',
        'language_direction' => 'default',
        'enter_mode' => 'p',
        'shift_enter_mode' => 'br',
        'font_format' => 'p;div;pre;address;h1;h2;h3;h4;h5;h6',
        'custom_formatting' => 'f',
        'formatting' => array(
          'custom_formatting_options' => array(
            'indent' => 'indent',
            'breakBeforeOpen' => 'breakBeforeOpen',
            'breakAfterOpen' => 'breakAfterOpen',
            'breakAfterClose' => 'breakAfterClose',
            'breakBeforeClose' => 0,
            'pre_indent' => 0,
          ),
        ),
        'css_mode' => 'theme',
        'css_path' => '',
        'css_style' => 'theme',
        'styles_path' => '',
        'filebrowser' => 'none',
        'filebrowser_image' => '',
        'filebrowser_flash' => '',
        'UserFilesPath' => '%b%f/',
        'UserFilesAbsolutePath' => '%d%b%f/',
        'ckeditor_load_method' => 'ckeditor.js',
        'ckeditor_load_time_out' => '0',
        'forcePasteAsPlainText' => 'f',
        'html_entities' => 't',
        'scayt_autoStartup' => 'f',
        'theme_config_js' => 'f',
        'js_conf' => '',
        'loadPlugins' => array(
          'counter' => array(
            'name' => 'counter',
            'desc' => 'Plugin to count symbols, symbols without blanks and words',
            'path' => '%base_path%%plugin_dir%counter/',
            'buttons' => FALSE,
            'default' => 'f',
          ),
          'tableresize' => array(
            'name' => 'tableresize',
            'desc' => 'Table Resize plugin',
            'path' => '%base_path%%editor_path%plugins/tableresize/',
            'buttons' => FALSE,
            'default' => 't',
          ),
        ),
        'excl_regex' => '#(?:^.*:.*@.*\\.edit\\-export$)|(?:^.*:node_export@node/add/node_export\\.edit\\-code$)|(?:^.*:text@node/add/text\\.edit\\-field\\-description\\-0\\-value$)|(?:^.*:.*@admin/build/block/configure/boxes/discussion_info\\.edit\\-body$)|(?:^.*:.*@.*\\.edit\\-field\\-education\\-0\\-value$)|(?:^.*:.*@.*\\.edit\\-field\\-societies\\-0\\-value$)|(?:^.*:.*@.*\\.edit\\-field\\-experience\\-0\\-value$)|(?:^.*:.*@.*\\.edit\\-field\\-research\\-0\\-value$)|(?:^.*:.*@.*\\.edit\\-field\\-publications\\-0\\-value$)#',
        'simple_incl_regex' => '',
      ),
      'roles' => array(
        'administrator' => 'administrator',
        'moderator' => 'moderator',
        'translator' => 'translator',
      ),
    ),
  );
  return $data;
}
