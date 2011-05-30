<?php
/**
 * @file
 * Plugin to provide an relationship handler for node from translated node.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Node translation'),
  'keyword' => 'translation',
  'description' => t('Creates the translation of a node as a node context.'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'context' => 'ctools_translation_from_node_context',
  'settings form' => 'ctools_translation_from_node_settings_form',
  'defaults' => array('language' => 'en', 'fallback' => FALSE),
);

/**
 * Return a new context based on an existing context.
 */
function ctools_translation_from_node_context($context, $conf) {
  // If unset it wants a generic, unfilled context, which is just NULL.
  if (empty($context->data)) {
    return ctools_context_create_empty('node', NULL);
  }

  if (isset($context->data->nid)) {
    $original = node_load($context->data->nid);
    $tnids = translation_node_get_translations($original->tnid);
    if (empty($tnids[$conf['language']])) {
      return $conf['fallback'] ? 
        ctools_context_create('node', $original) :
        ctools_context_create_empty('node', NULL);
    }
    $translation = node_load($tnids[$conf['language']]->nid);

    // Send it to ctools.
    return ctools_context_create('node', $translation);
  }
}

function ctools_translation_from_node_settings_form($conf) {
  $form['language'] = array(
    '#type' => 'select',
    '#title' => t('Language'),
    '#options' => locale_language_list(),
    '#default_value' => $conf['language'],
  );
  $form['fallback'] = array(
    '#type' => 'checkbox',
    '#title' => t('Fallback to original node'),
    '#description' => t('Use original node if desired translation is not found.'),
    '#default_value' => $conf['fallback'],
  );
  return $form;
}

