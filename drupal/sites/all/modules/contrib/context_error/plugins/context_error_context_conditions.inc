<?php
/**
 * @file
 * Context condition plugin to provide a trigger for 404 and 403 error pages.
 */

/**
 * Trigger for 403 pages only.
 */
define('CONTEXT_ERROR_403', 403);

/**
 * Trigger for 404 pages only.
 */
define('CONTEXT_ERROR_404', 404);

/**
 * Trigger for both 403 and 404 pages.
 */
define('CONTEXT_ERROR_403_404', 2);

/**
 * Trigger for a case when its neither a 403 nor a 404 page.
 */
define('CONTEXT_ERROR_NOT_ERROR', 1);

/**
 * Expose the 404 error page as the context condition.
 */
class context_error_context_condition_error extends context_condition {
  private $known_errors = array(
    CONTEXT_ERROR_403 => '403 Forbidden',
    CONTEXT_ERROR_404 => '404 Not Found',
  );

  function condition_values() {
    $values = array();
    $values[CONTEXT_ERROR_403] = t('403 only');
    $values[CONTEXT_ERROR_404] = t('404 only');
    $values[CONTEXT_ERROR_403_404] = t('404 or 403 pages');
    $values[CONTEXT_ERROR_NOT_ERROR] = t('Not an error page');
    return $values;
  }

  /**
   * Condition form.
   */
  function condition_form($context) {
    return array(
      '#title' => $this->title,
      '#description' => t('Select which error case should this condition activate.'),
      '#options' => $this->condition_values(),
      '#type' => 'radios',
      '#default_value' => count($this->fetch_from_context($context, 'values')) > 1 ?
        CONTEXT_ERROR_403_404 : key($this->fetch_from_context($context, 'values')),
    );
  }

  /**
   * Condition form submit handler.
   *
   * Convert the values to an array, otherwise only string is submitted.
   * Store the 403 AND 404 case as an array with both values stored.
   */
  function condition_form_submit($values) {
    if ($values == CONTEXT_ERROR_403_404) {
      return array(
        CONTEXT_ERROR_403 => CONTEXT_ERROR_403,
        CONTEXT_ERROR_404 => CONTEXT_ERROR_404,
      );
    }
    return array($values => $values);
  }

  /**
   * Helper function to decide wether we are on a 404 or 403 page or not.
   */
  function is_error($header_status) {
    foreach ($this->known_errors as $error => $status) {
      if ($status == $header_status) return TRUE;
    }
    return FALSE;
  }

  /**
   * Execute.
   */
  function execute() {
    if ($this->condition_used()) {
      $headers = drupal_get_http_header();

      foreach ($this->get_contexts() as $context) {
        $errors = $this->fetch_from_context($context, 'values');

        if (isset($headers['status']) && $this->is_error($headers['status'])) {
          foreach ($errors as $error) {
            if (isset($this->known_errors[$error]) && $this->known_errors[$error] == $headers['status']) {
              $this->condition_met($context);
            }
          }
        }
        // This is a case when we trigger on non-error pages, so we don't need a status check.
        else if (array_key_exists(CONTEXT_ERROR_NOT_ERROR, $this->fetch_from_context($context, 'values'))) {
          $this->condition_met($context);
        }
      }
    }
  }
}
