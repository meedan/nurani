<?php

function icl_translate_get_service_name_key($name) {
  return strtolower(str_replace(' ', '_', $name));
}

