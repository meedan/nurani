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

echo "Will import: " . implode(' ', array_keys($to_import)) . "\n\n";
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
        'sites/all/texts/wlc/1Chr.xml',
        'sites/all/texts/wlc/1Kgs.xml',
        'sites/all/texts/wlc/1Sam.xml',
        'sites/all/texts/wlc/2Chr.xml',
        'sites/all/texts/wlc/2Kgs.xml',
        'sites/all/texts/wlc/2Sam.xml',
        'sites/all/texts/wlc/Amos.xml',
        'sites/all/texts/wlc/Dan.xml',
        'sites/all/texts/wlc/Deut.xml',
        'sites/all/texts/wlc/Eccl.xml',
        'sites/all/texts/wlc/Esth.xml',
        'sites/all/texts/wlc/Exod.xml',
        'sites/all/texts/wlc/Ezek.xml',
        'sites/all/texts/wlc/Ezra.xml',
        'sites/all/texts/wlc/Gen.xml',
        'sites/all/texts/wlc/Hab.xml',
        'sites/all/texts/wlc/Hag.xml',
        'sites/all/texts/wlc/Hos.xml',
        'sites/all/texts/wlc/Isa.xml',
        'sites/all/texts/wlc/Jer.xml',
        'sites/all/texts/wlc/Job.xml',
        'sites/all/texts/wlc/Joel.xml',
        'sites/all/texts/wlc/Jonah.xml',
        'sites/all/texts/wlc/Josh.xml',
        'sites/all/texts/wlc/Judg.xml',
        'sites/all/texts/wlc/Lam.xml',
        'sites/all/texts/wlc/Lev.xml',
        'sites/all/texts/wlc/Mal.xml',
        'sites/all/texts/wlc/Mic.xml',
        'sites/all/texts/wlc/Nah.xml',
        'sites/all/texts/wlc/Neh.xml',
        'sites/all/texts/wlc/Num.xml',
        'sites/all/texts/wlc/Obad.xml',
        'sites/all/texts/wlc/Prov.xml',
        'sites/all/texts/wlc/Ps.xml',
        'sites/all/texts/wlc/Ruth.xml',
        'sites/all/texts/wlc/Song.xml',
        'sites/all/texts/wlc/Zech.xml',
        'sites/all/texts/wlc/Zeph.xml',
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
