<?php

/**
 * Implementation of hook_taxonomy_default_vocabularies().
 */
function nurani_general_taxonomy_default_vocabularies() {
  return array(
    'term_contexts' => array(
      'name' => 'Term Contexts',
      'description' => 'Context for the translation of glossary terms.',
      'help' => '',
      'relations' => '1',
      'hierarchy' => '0',
      'multiple' => '0',
      'required' => '0',
      'tags' => '0',
      'module' => 'features_term_contexts',
      'weight' => '0',
      'language' => '',
      'type' => NULL,
      'nodes' => array(),
    ),
  );
}
