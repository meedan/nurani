
Drupal.behaviors.selectText = function(context) {
    var language = Drupal.settings.nurani_glossary.language;
    var addUrl = Drupal.settings.nurani_glossary.url + '?title=%term%&language=' + language + '&destination=' + Drupal.settings.getQ;

    $('.node-type-discussion .field-body, .node-type-discussion .field-description, .node-type-text .content', context)
    .not('.nurani-glossary-processed').addClass('nurani-glossary-processed')
    .each(function(key, element) {
      $(element).selectlink({
        url : addUrl,
        text : Drupal.t('Add to glossary'),
        target: '_self',
        title: Drupal.t('Create glossary term out of the highlighted text.'),
        min: 2,
        exceptions: '.field-label, .glossary-term'
      });
    });
};

