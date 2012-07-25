<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">

<head>
<title>Arabic Normalise Examples</title>
<meta http-equiv="Content-Type" content="text/html;charset=utf-8" />
<link rel="stylesheet" type="text/css" href="style.css" media="all" />
</head>

<body>
<div class="Paragraph">
<h2 dir="ltr">Arabic Normalise Examples Output:</h2>

<?php
error_reporting(E_STRICT);
$time_start = microtime(true);

include('../Arabic.php');
$normalise = new Arabic('ArNormalise');

$file = fopen('./Normalization/sample.txt', 'r');

echo <<<END
<p>Processing <a href="./Normalization/sample.txt" target=_blank>input file</a> line by line</p>
<table border="0" cellpadding="5" cellspacing="2" dir="rtl">
END;

while($read = fgets($file)) {
    echo '<tr><th style="background-color: #E5E5E5">Function</th>
          <th style="background-color: #E5E5E5">Text</th></tr>';

    echo "<tr bgcolor=#F0F8FF><th>Original</th><td>$read</td></tr>";
    
    $n1 = $normalise->unshape($read);
    echo "<tr bgcolor=#F0F8FF><th>Unshape</th><td>$n1</td></tr>";
  
    $n2 = $normalise->utf8Strrev($n1);
    echo "<tr bgcolor=#F0F8FF><th>UTF8 Reverse</th><td>$n2</td></tr>";
  
    $n3 = $normalise->stripTashkeel($n2);
    echo "<tr bgcolor=#F0F8FF><th>Strip Tashkeel</th><td>$n3</td></tr>";
  
    $n4 = $normalise->stripTatweel($n3);
    echo "<tr bgcolor=#F0F8FF><th>Strip Tatweel</th><td>$n4</td></tr>";
  
    $n5 = $normalise->normaliseHamza($n4);
    echo "<tr bgcolor=#F0F8FF><th>Normalise Hamza</th><td>$n5</td></tr>";
  
    $n6 = $normalise->normaliseLamaleph($n5);
    echo "<tr bgcolor=#F0F8FF><th>Normalise Lam Alef</th><td>$n6</td></tr>";
}
fclose($file);

echo '</table>';
?>

</div><br />

<div class="Paragraph">
<h2>SimpleXML Example Code:</h2>
<?php
highlight_string(<<<'ENDALL'
<?php
include('../Arabic.php');
$normalise = new Arabic('ArNormalise');

$file = fopen('./Normalization/sample.txt', 'r');

echo <<<END
<p>Processing <a href="./Normalization/sample.txt" target=_blank>input file</a> line by line</p>
<table border="0" cellpadding="5" cellspacing="2" dir="rtl">
END;

while($read = fgets($file)) {
    echo '<tr><th style="background-color: #E5E5E5">Function</th>
          <th style="background-color: #E5E5E5">Text</th></tr>';

    echo "<tr bgcolor=#F0F8FF><th>Original</th><td>$read</td></tr>";
    
    $n1 = $normalise->unshape($read);
    echo "<tr bgcolor=#F0F8FF><th>Unshape</th><td>$n1</td></tr>";
  
    $n2 = $normalise->utf8Strrev($n1);
    echo "<tr bgcolor=#F0F8FF><th>UTF8 Reverse</th><td>$n2</td></tr>";
  
    $n3 = $normalise->stripTashkeel($n2);
    echo "<tr bgcolor=#F0F8FF><th>Strip Tashkeel</th><td>$n3</td></tr>";
  
    $n4 = $normalise->stripTatweel($n3);
    echo "<tr bgcolor=#F0F8FF><th>Strip Tatweel</th><td>$n4</td></tr>";
  
    $n5 = $normalise->normaliseHamza($n4);
    echo "<tr bgcolor=#F0F8FF><th>Normalise Hamza</th><td>$n5</td></tr>";
  
    $n6 = $normalise->normaliseLamaleph($n5);
    echo "<tr bgcolor=#F0F8FF><th>Normalise Lam Alef</th><td>$n6</td></tr>";
}
fclose($file);

echo '</table>';
ENDALL
);

    $time_end = microtime(true);
    $time = $time_end - $time_start;
    
    echo "<hr />Total execution time is $time seconds<br />\n";
    echo 'Amount of memory allocated to this script is ' . memory_get_usage() . ' bytes';

    $included_files = get_included_files();
    echo '<h4>Names of included or required files:</h4><ul>';
    
    foreach ($included_files as $filename) {
        echo "<li>$filename</li>";
    }

    echo '</ul>';
?>
</div>
</body>
</html>
