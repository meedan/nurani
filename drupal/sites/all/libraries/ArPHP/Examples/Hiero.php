<?php
    error_reporting(E_STRICT);
    
    (!empty($_GET['w'])) ? $word = $_GET['w'] : $word='Khaled Shamaa';

    include('../Arabic.php');
    $x = new Arabic('Hiero');
    
    $im = $x->str2graph($word);
    
    // Set the content-type
    header ("Content-type: image/png");

    imagepng($im);
    imagedestroy($im);
?>