<html><head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" >
</head><body>
<?php

  $list[] = 'ض';
  $list[] = 'ص';
  $list[] = 'ث';
  $list[] = 'ق';
  $list[] = 'ف';
  $list[] = 'غ';
  $list[] = 'ع';
  $list[] = 'ه';
  $list[] = 'خ';
  $list[] = 'ح';
  $list[] = 'ج';
  $list[] = 'د';
  $list[] = 'ش';
  $list[] = 'س';
  $list[] = 'ي';
  $list[] = 'ب';
  $list[] = 'ل';
  $list[] = 'ا';
  $list[] = 'ت';
  $list[] = 'ن';
  $list[] = 'م';
  $list[] = 'ك';
  $list[] = 'ط';
  $list[] = 'ئ';
  $list[] = 'ء';
  $list[] = 'ؤ';
  $list[] = 'ر';
  $list[] = 'لا';
  $list[] = 'ى';
  $list[] = 'ة';
  $list[] = 'و';
  $list[] = 'ز';
  $list[] = 'ظ';
  $list[] = 'ذ';
  $list[] = 'لإ';
  $list[] = 'إ';
  $list[] = 'لأ';
  $list[] = 'أ';
  $list[] = 'لآ';
  $list[] = 'آ';

  sort($list);
  
  foreach ($list as $item) {
      echo "$item <br/>\n";
  }  

  $xml = simplexml_load_file(dirname(__FILE__).'/data/ArSort.xml');
  $find = array();
  $replace = array();

  foreach ($xml->xpath("//preg_replace[@function='normalize']/pair") as $pair) {
      array_push($find, (string)$pair->search);
      array_push($replace, (string)$pair->replace);
  }
  
  function cmp($a, $b)
  {
      global $find, $replace;
      $a = preg_replace($find, $replace, $a);
      $b = preg_replace($find, $replace, $b);

      if ($a == $b) {
          return 0;
      }
      return ($a < $b) ? -1 : 1;
  }

  echo '<hr/>';
  usort($list, "cmp");
  
  foreach ($list as $item) {
      echo "$item <br/>\n";
  }  


?>
</body></html>