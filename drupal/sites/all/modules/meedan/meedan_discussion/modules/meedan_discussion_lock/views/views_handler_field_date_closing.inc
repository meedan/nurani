<?php
/**
 * Meedan discussion lock date formatter.
 */
class views_handler_field_date_closing extends views_handler_field_date {
  function option_definition() {
    $options = parent::option_definition();

    $options['date_format'] = array('default' => 'small');
    $options['custom_date_format'] = array('default' => '');

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['date_format']['#options']['time closing'] = t('Meedan Discussion Lock: Time until discussion close');
  }

  function render($values) {
    $value = $this->get_value($values);
    $format = $this->options['date_format'];

    if ($format == 'time closing') {
      return meedan_discussion_lock_countdown_text($value, $GLOBALS['user']->timezone);
    }
    else {
      return parent::render($values);
    }
  }
}
