<?php

/**
 * Theme implementation for Nurani 'welcome_login' block.
 */
function theme_nurani_helpers_block_welcome_login($variables) {
  $account = $variables['account'];

  $output = '';
  if (!$account->uid) {
    $output  = '<span class="login">';
    $output .=   l(t("Login"), 'user/login', array('query' => array('destination' => '<front>')));
    $output .= '</span>';
  }
  else {
    $output  = '<span class="welcome">';
    $output .=   t("Welcome, <strong>!name</strong>", array('!name' => l($account->name, '<front>')));
    $output .= '</span>';
    $output .= '<span class="logout">';
    $output .=   l(t("Logout"), 'user/logout', array('query' => array('destination' => '<front>')));
    $output .= '</span>';
  }

  return $output;
}

function theme_nurani_helpers_block_recent_annotations($variables) {
  $annotations = $variables['annotations'];

  $output  = '';
  $output .= '<div class="annotations">';
  foreach($annotations as $annotation) {
    $passage_title = '<strong class="passage-title">' . check_plain($annotation['passage_title']) . '</strong>';

    if (isset($annotation['author'])) {
      $author = user_load($annotation['author']['uid']);
      $action = t('!author privately annotated !passage_title', array('!author' => theme('username', array('account' => $author)), '!passage_title' => $passage_title));
    }
    else if (isset($annotation['author_uuid'])) {
      $action = t('<em>Unknown author</em> annotated !passage_title', array('!passage_title' => $passage_title));
    }
    else {
      $action = t('!passage_title is annotated with', array('!passage_title' => $passage_title));
    }

    $output .= '<div class="annotation">';
    $output .=   $action;
    $output .=   '<div class="contents">';
    $output .=   check_plain($annotation['value']);
    $output .=   '</div>';
    $output .= '</div>';
  }
  $output .= '</div>';

  return $output;
}

/**
 * Theme implementation for Nurani attribution helper.
 */
function theme_nurani_attribution($variables) {
  $output  = '';
  $output .= '<span class="attribution">';
  $output .=   '&mdash; ';
  $output .=   theme('username', array('account' => $variables['account']));
  if ($variables['timestamp']) {
    $output .= ' <span class="date">';
    $output .=   format_date($variables['timestamp'], 'attribution', '', $variables['account']->timezone);
    $output .= '</span>';
  }
  if ($variables['account']->field_country && $variables['account']->field_country[LANGUAGE_NONE][0]) {
    $output .= ' <span class="country">';
    $output .=   check_plain($variables['account']->field_country[LANGUAGE_NONE][0]['value']);
    $output .= '</span>';
  }
  $output .= '</span>';
  return $output;
}
