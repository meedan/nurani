<?php
// $Id: messaging_simple_handler_field_body.inc,v 1.1.2.1 2010/05/10 17:03:53 jareyero Exp $

/**
 * Field handler
 */
class messaging_simple_handler_field_body extends views_handler_field {

  function render($values) {

    $method_info = messaging_method_info('simple');
    $value = $values->{$this->field_alias};

    // The filter is applied now only once.
    if ($method_info['filter']) {
      return check_markup($value, $filter, FALSE);
    }

    return check_plain($value);

  }

}
