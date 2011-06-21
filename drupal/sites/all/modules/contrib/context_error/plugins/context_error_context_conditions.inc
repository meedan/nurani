<?php

/**
 * Expose the 404 error page as the context condition.
 */
class context_error_context_condition_error extends context_condition {
  function condition_values() {
    $values = array();
    $values['403'] = t('403 error');
    $values['404'] = t('404 error');
    return $values;
  }

  /**
   * Execute.
   */
  function execute() {
    if ($this->condition_used()) {
      // Include both the path alias and normal path for matching.
      $current_path = array(drupal_get_path_alias($_GET['q']));
      if ($current_path != $_GET['q']) {
        $current_path[] = $_GET['q'];
      }
      foreach ($this->get_contexts() as $context) {
        $errors = $this->fetch_from_context($context, 'values');
        foreach ($errors as $error) {
          if (in_array(variable_get("site_$error", ''), $current_path)) {
            $this->condition_met($context);
          }
          global $logintoboggan_denied;
          if ($error == '403' && !empty($logintoboggan_denied)) {
            $this->condition_met($context);
          }
        }
      }
    }
  }
}
