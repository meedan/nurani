<?php
    error_reporting(E_STRICT);
    
    (!empty($_GET['w'])) ? $word = $_GET['w'] : $word='خالد الشمعة';

    include('../Arabic.php');
    $x = new Arabic('Hiero');
    
    $x->setLanguage('Phoenician');
    $im = $x->str2graph($word, 'rtl', 'ar');
    
    $w = imagesx($im);
    $h = imagesy($im);
    
    $bg  = imagecreatefromjpeg('images/bg.jpg');
    $bgw = imagesx($bg);
    $bgh = imagesy($bg);

    // Set the content-type
    header ("Content-type: image/png");

    imagecopyresized($bg, $im, ($bgw-$w)/2, ($bgh-$h)/2, 0, 0, $w, $h, $w, $h);

    imagepng($bg);
    imagedestroy($im);
    imagedestroy($bg);
?>