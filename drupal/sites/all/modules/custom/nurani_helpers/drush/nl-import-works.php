<?php
#!/usr/bin/env drush
if (php_sapi_name() !== 'cli') {
  header('Location: http://' . $_SERVER['HTTP_HOST']);
  return;
}
if (!function_exists('nurani_library_provider_works_path')) {
  echo 'Error, Must be run inside a Drupal environment, eg: drush script nl-import-works.php';
  exit(1);
}

$all_imports = imports_list();
$to_import = array();

while ($arg = drush_shift()) {
  if (array_key_exists($arg, $all_imports)) {
    $to_import[$arg] = $all_imports[$arg];
  }
}

if (empty($to_import)) {
  $to_import = $all_imports;
}

echo "Will import: " . implode(', ', array_keys($to_import)) . "\n\n";
echo "Starting in 3s...\n";
sleep(3); // Enable the user to ctrl+c before going to far

foreach ($to_import as $work_name => $import) {
  $start = microtime(TRUE);

  // Additional settings
  $import['path']             = DRUPAL_ROOT;
  $import['stripChars']       = $import['language'] == 'he' ? '/' : '';
  $import['includeApocrypha'] = TRUE;

  $library = new NuraniLibrary(array('backend' => 'Drupal'));
  $library->import(array($work_name => $import));

  echo "Imported $work_name.. (" . (microtime(TRUE) - $start) . "s)\n";
}


function imports_list() {
  return array(
    'nrsv_en' => array(
      'name'      => 'nrsv_en',
      'full_name' => 'NRSV (English)',
      'language'  => 'en',
      'format'    => 'OSIS',
      'files'     => array(
        'sites/all/texts/nrsvae.xml',
      ),
    ),
    'njps_en' => array(
      'name'      => 'njps_en',
      'full_name' => 'NJPS (English)',
      'language'  => 'en',
      'format'    => 'OSIS',
      'files'     => array(
        'sites/all/texts/en_njps_2006.xml',
      ),
    ),
    'quran_ar' => array(
      'name'      => 'quran_ar',
      'full_name' => 'Qur\'an (Arabic)',
      'language'  => 'ar',
      'format'    => 'TanzilXML',
      'files'     => array(
        'sites/all/texts/quran/enhanced/quran-simple-enhanced.xml',
      ),
    ),
    'quran_ahmedali_en' => array(
      'name'      => 'quran_ahmedali_en',
      'full_name' => 'Qur\'an (English, Ahmed Ali)',
      'language'  => 'en',
      'format'    => 'TanzilXML',
      'files'     => array(
        'sites/all/texts/quran/en/en.ahmedali.xml',
      ),
    ),
    'quran_ahmedraza_en' => array(
      'name'      => 'quran_ahmedraza_en',
      'full_name' => 'Qur\'an (English, Ahmed Raza Kha)',
      'language'  => 'en',
      'format'    => 'TanzilXML',
      'files'     => array(
        'sites/all/texts/quran/en/en.ahmedraza.xml',
      ),
    ),
    'quran_arberry_en' => array(
      'name'      => 'quran_arberry_en',
      'full_name' => 'Qur\'an (English, Arberry)',
      'language'  => 'en',
      'format'    => 'TanzilXML',
      'files'     => array(
        'sites/all/texts/quran/en/en.arberry.xml',
      ),
    ),
    'quran_asad_en' => array(
      'name'      => 'quran_asad_en',
      'full_name' => 'Qur\'an (English, Asad)',
      'language'  => 'en',
      'format'    => 'TanzilXML',
      'files'     => array(
        'sites/all/texts/quran/en/en.asad.xml',
      ),
    ),
    'quran_daryabadi_en' => array(
      'name'      => 'quran_daryabadi_en',
      'full_name' => 'Qur\'an (English, Daryabadi)',
      'language'  => 'en',
      'format'    => 'TanzilXML',
      'files'     => array(
        'sites/all/texts/quran/en/en.daryabadi.xml',
      ),
    ),
    'quran_hilali_en' => array(
      'name'      => 'quran_hilali_en',
      'full_name' => 'Qur\'an (English, Hilali & Kha)',
      'language'  => 'en',
      'format'    => 'TanzilXML',
      'files'     => array(
        'sites/all/texts/quran/en/en.hilali.xml',
      ),
    ),
    'quran_maududi_en' => array(
      'name'      => 'quran_maududi_en',
      'full_name' => 'Qur\'an (English, Maududi)',
      'language'  => 'en',
      'format'    => 'TanzilXML',
      'files'     => array(
        'sites/all/texts/quran/en/en.maududi.xml',
      ),
    ),
    'quran_qaribullah_en' => array(
      'name'      => 'quran_qaribullah_en',
      'full_name' => 'Qur\'an (English, Qaribullah & Darwish)',
      'language'  => 'en',
      'format'    => 'TanzilXML',
      'files'     => array(
        'sites/all/texts/quran/en/en.qaribullah.xml',
      ),
    ),
    'quran_sahih_en' => array(
      'name'      => 'quran_sahih_en',
      'full_name' => 'Qur\'an (English, Saheeh I)',
      'language'  => 'en',
      'format'    => 'TanzilXML',
      'files'     => array(
        'sites/all/texts/quran/en/en.sahih.xml',
      ),
    ),
    'quran_sarwar_en' => array(
      'name'      => 'quran_sarwar_en',
      'full_name' => 'Qur\'an (English, Sarwar)',
      'language'  => 'en',
      'format'    => 'TanzilXML',
      'files'     => array(
        'sites/all/texts/quran/en/en.sarwar.xml',
      ),
    ),
    'quran_shakir_en' => array(
      'name'      => 'quran_shakir_en',
      'full_name' => 'Qur\'an (English, Shakir)',
      'language'  => 'en',
      'format'    => 'TanzilXML',
      'files'     => array(
        'sites/all/texts/quran/en/en.shakir.xml',
      ),
    ),
    'quran_transliteration_en' => array(
      'name'      => 'quran_transliteration_en',
      'full_name' => 'Qur\'an (English, Tra)',
      'language'  => 'en',
      'format'    => 'TanzilXML',
      'files'     => array(
        'sites/all/texts/quran/en/en.transliteration.xml',
      ),
    ),
    'quran_wahiduddin_en' => array(
      'name'      => 'quran_wahiduddin_en',
      'full_name' => 'Qur\'an (English, Wahiduddi)',
      'language'  => 'en',
      'format'    => 'TanzilXML',
      'files'     => array(
        'sites/all/texts/quran/en/en.wahiduddin.xml',
      ),
    ),
    'quran_yusufali_en' => array(
      'name'      => 'quran_yusufali_en',
      'full_name' => 'Qur\'an (English, Yusuf Ali)',
      'language'  => 'en',
      'format'    => 'TanzilXML',
      'files'     => array(
        'sites/all/texts/quran/en/en.yusufali.xml',
      ),
    ),
    'wlc_he' => array(
      'name'      => 'wlc_he',
      'full_name' => 'Westminster Leningrad Codex (Hebrew)',
      'language'  => 'he',
      'format'    => 'OSIS',
      'files'     => array(
        'sites/all/texts/WLC/1Chr.xml',
        'sites/all/texts/WLC/1Kgs.xml',
        'sites/all/texts/WLC/1Sam.xml',
        'sites/all/texts/WLC/2Chr.xml',
        'sites/all/texts/WLC/2Kgs.xml',
        'sites/all/texts/WLC/2Sam.xml',
        'sites/all/texts/WLC/Amos.xml',
        'sites/all/texts/WLC/Dan.xml',
        'sites/all/texts/WLC/Deut.xml',
        'sites/all/texts/WLC/Eccl.xml',
        'sites/all/texts/WLC/Esth.xml',
        'sites/all/texts/WLC/Exod.xml',
        'sites/all/texts/WLC/Ezek.xml',
        'sites/all/texts/WLC/Ezra.xml',
        'sites/all/texts/WLC/Gen.xml',
        'sites/all/texts/WLC/Hab.xml',
        'sites/all/texts/WLC/Hag.xml',
        'sites/all/texts/WLC/Hos.xml',
        'sites/all/texts/WLC/Isa.xml',
        'sites/all/texts/WLC/Jer.xml',
        'sites/all/texts/WLC/Job.xml',
        'sites/all/texts/WLC/Joel.xml',
        'sites/all/texts/WLC/Jonah.xml',
        'sites/all/texts/WLC/Josh.xml',
        'sites/all/texts/WLC/Judg.xml',
        'sites/all/texts/WLC/Lam.xml',
        'sites/all/texts/WLC/Lev.xml',
        'sites/all/texts/WLC/Mal.xml',
        'sites/all/texts/WLC/Mic.xml',
        'sites/all/texts/WLC/Nah.xml',
        'sites/all/texts/WLC/Neh.xml',
        'sites/all/texts/WLC/Num.xml',
        'sites/all/texts/WLC/Obad.xml',
        'sites/all/texts/WLC/Prov.xml',
        'sites/all/texts/WLC/Ps.xml',
        'sites/all/texts/WLC/Ruth.xml',
        'sites/all/texts/WLC/Song.xml',
        'sites/all/texts/WLC/Zech.xml',
        'sites/all/texts/WLC/Zeph.xml',
      ),
    ),
    'lxx_el' => array(
      'name'      => 'lxx_el',
      'full_name' => 'Septuagint (Greek)',
      'language'  => 'el',
      'format'    => 'OSIS',
      'files'     => array(
        'sites/all/texts/LXX/nlxx_osis.xml',
      ),
    ),
    'tisch_el' => array(
      'name'      => 'tisch_el',
      'full_name' => 'Tischendorf\'s New Testament (Greek)',
      'language'  => 'el',
      'format'    => 'OSIS',
      'files'     => array(
        'sites/all/texts/TISCH/sf_Tischendorf_Greek_NT_str_rev1_osis.xml',
      ),
    ),
    'wh_el' => array(
      'name'      => 'wh_el',
      'full_name' => 'Westcott-Hort\'s New Testament (Greek)',
      'language'  => 'el',
      'format'    => 'OSIS',
      'files'     => array(
        'sites/all/texts/Wescott-Hort/greekwh_osis.xml',
      ),
    ),
  );
}
