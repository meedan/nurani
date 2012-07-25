<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">

<head>
<title>Detect Arabic String Character Set</title>
<meta http-equiv="Content-Type" content="text/html;charset=windows-1256" />
<link rel="stylesheet" type="text/css" href="style.css" media="all" />
</head>

<body>

<div class="Paragraph">
<h2>Example Output:</h2>
<?php
    error_reporting(E_STRICT);
    $time_start = microtime(true);

    $text = 'بسم الله الرحمن الرحيم';

    include('../Arabic.php');
    $object = new Arabic('ArCharsetD');
    
    $charset = $object->getCharset($text);
    
    echo "$text ($charset) <br/>";
	
	print_r($object->guess($text));
?>

</div><br />
<div class="Paragraph">
<h2>Example Code:</h2>
<?php
highlight_string(<<<'END'
<?php
    $text = 'بسم الله الرحمن الرحيم';

    include('../Arabic.php');
    $object = new Arabic('ArCharsetD');
    
    $charset = $object->getCharset($text);
    
    echo "$text ($charset) <br/>";
	
	print_r($object->guess($text));
END
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
<a href="../Documentation/Arabic/_sub---ArCharsetD.class.php.html" target="_blank">Related Class Documentation</a>
</div>
</body>
</html>
