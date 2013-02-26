<?php
/**
 * @file
 * nurani_general.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function nurani_general_filter_default_formats() {
  $formats = array();

  // Exported format: Filtered HTML.
  $formats['filtered_html'] = array(
    'format' => 'filtered_html',
    'name' => 'Filtered HTML',
    'cache' => '1',
    'status' => '1',
    'weight' => '0',
    'filters' => array(
      'filter_url' => array(
        'weight' => '-48',
        'status' => '1',
        'settings' => array(
          'filter_url_length' => '72',
        ),
      ),
      'filter_html' => array(
        'weight' => '-47',
        'status' => '1',
        'settings' => array(
          'allowed_html' => '<a> <em> <strong> <cite> <blockquote> <code> <ul> <ol> <li> <dl> <dt> <dd> <sup> <p>',
          'filter_html_help' => 1,
          'filter_html_nofollow' => 0,
        ),
      ),
      'filter_autop' => array(
        'weight' => '-46',
        'status' => '1',
        'settings' => array(),
      ),
      'filter_htmlcorrector' => array(
        'weight' => '-45',
        'status' => '1',
        'settings' => array(),
      ),
      'nurani_library_passages' => array(
        'weight' => '-44',
        'status' => '1',
        'settings' => array(
          'allowed_works' => array(
            'nrsv_en' => 1,
            'njps_en' => 1,
            'quran_ar' => 1,
            'quran_ahmedali_en' => 1,
            'quran_ahmedraza_en' => 1,
            'quran_arberry_en' => 1,
            'quran_asad_en' => 1,
            'quran_daryabadi_en' => 1,
            'quran_hilali_en' => 1,
            'quran_maududi_en' => 1,
            'quran_qaribullah_en' => 1,
            'quran_sahih_en' => 1,
            'quran_sarwar_en' => 1,
            'quran_shakir_en' => 1,
            'quran_transliteration_en' => 1,
            'quran_wahiduddin_en' => 1,
            'quran_yusufali_en' => 1,
            'wlc_he' => 1,
            'lxx_el' => 1,
            'tisch_el' => 1,
            'wh_el' => 1,
          ),
        ),
      ),
    ),
  );

  return $formats;
}
