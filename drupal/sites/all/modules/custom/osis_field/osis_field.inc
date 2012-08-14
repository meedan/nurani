<?php

// TODO: Un-stub osis_field_texts().
function osis_field_texts() {
  return array(
    (object) array('machine_name' => 'niv', 'name' => t("NIV"), 'type' => 'biblical'),
    (object) array('machine_name' => 'nkjv', 'name' => t("NKJV"), 'type' => 'biblical'),
    (object) array('machine_name' => 'wlc', 'name' => t("WLC"), 'type' => 'hebraic'),
  );
}

function osis_field_text_options() {
  $options = array();
  foreach (osis_field_texts() as $type) {
    $options[$type->machine_name] = $type->name;
  }
  return $options;
}

// TODO: Un-stub osis_field_text_types().
function osis_field_text_types() {
  return array(
    (object) array('machine_name' => 'biblical', 'name' => t("Biblical")),
    (object) array('machine_name' => 'biblical_apocryhpa', 'name' => t("Biblical (including Apocrypha)")),
    (object) array('machine_name' => 'hebraic', 'name' => t("Hebraic (Hebrew bible)")),
    (object) array('machine_name' => 'quranic', 'name' => t("Quranic")),
  );
}

function osis_field_text_type_options() {
  $options = array();
  foreach (osis_field_text_types() as $type) {
    $options[$type->machine_name] = $type->name;
  }
  return $options;
}