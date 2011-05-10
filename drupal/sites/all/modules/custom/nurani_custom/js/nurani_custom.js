// $Id$
Drupal.behaviors.selectText = function(context) {
    var lang_setting = Drupal.settings.nurani_custom.selected_node_lang;
    
    // JS isArray.
    var language = (lang_setting.constructor.toString().indexOf("Array") == -1)? lang_setting : lang_setting[0];
    
    var addUrl = Drupal.settings.basePath + 'node/add/term?title=%term%&language=' + language + '&diestination=' + Drupal.settings.getQ;

    $('#content-area .node-type-discussion, #block-views-discussion_texts-block_1 .views-row, #comments .comment-content-wrapper div.content, .node-type-text div.content', context)
    .not('.nurani-custom-processed').addClass('nurani-custom-processed')
    .each(function(key, element) {
      $(element).selectlink({
        url : addUrl,
        text : Drupal.t('Add Term'),
        target: '_self',
        title: Drupal.t('Create Glossary Term')
      });
    });
    
};
