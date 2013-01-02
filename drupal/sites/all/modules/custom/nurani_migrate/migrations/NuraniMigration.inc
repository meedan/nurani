<?php

/**
 * Shared aspects of all migrations are stored in this parent class.
 */
abstract class NuraniMigration extends DynamicMigration {
  public function __construct() {
    parent::__construct();

    $this->d6Connection = Database::getConnection('default', 'migrate');
  }

  public function prepareRow($row) {
    // Nothing needed here yet..
  }

  /**
   * Uses Levenshtein distance to determine which option in $options that
   * $string is most similar to.
   *
   * eg: 'Ph' is most similar to 'PhD' in array('Mr', 'Mrs', 'Dr', 'PhD')
   */
  public function fuzzy_match($string, $options) {
    $best_match = $string;
    $best_lev   = strlen($string);

    foreach ($options as $option) {
      $lev = levenshtein(strtolower($string), strtolower($option));

      if ($lev == 0) { // Direct hit
        return $option;
      }
      else if ($lev < $best_lev) {
        $best_match = $option;
        $best_lev = $lev;
      }
    }

    return $best_match;
  }
}
