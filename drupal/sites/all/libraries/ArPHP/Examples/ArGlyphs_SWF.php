<?php
    include('../Arabic.php');
    $Arabic = new Arabic('ArGlyphs');

    $text_before = 'اللغة العربية';
    $text_after = $Arabic->utf8Glyphs($text_before);

    $f = new SWFFont(dirname(__FILE__).'/GD/ae_AlHor.ttf');

    $m = new SWFMovie();
    $m->setRate(24.0);
    $m->setDimension(520, 320);
    $m->setBackground(105, 121, 47);

    // This functions was based on the example from
    // http://ming.sourceforge.net/examples/animation.html

    function text($r, $g, $b, $a, $rot, $x, $y, $scale, $string) {
        global $f, $m;

        $t = new SWFText();
        $t->setFont($f);
        $t->setColor($r, $g, $b, $a);
        $t->setHeight(96);
        $t->moveTo(-($t->getWidth($string)) / 5, 32);
        $t->addUTF8String($string);

        $i = $m->add($t);
        $i->rotateTo($rot);
        $i->moveTo($x, $y);
        $i->scale($scale, $scale);

        return $i;
    }

    $x = 1040;
    $y = 50;
    $size = 0.4;
    $t[0] = text(220, 220, 220, 0xff, 0, $x, $y, $size, $text_before);

    $y = 80;
    $size = 0.8;
    $t[1] = text(255, 255, 0, 0xff, 0, $x, $y, $size, $text_after);

    $frames = 400;
    for ($j = 0; $j < $frames; $j++) {
        for ($i = 0; $i < 2; $i++) {
            $t[$i]->moveTo(260 + round(sin($j / $frames * 2 * pi() + $i) * (50 + 50 * ($i + 1))), 160 + round(sin($j / $frames * 4 * pi() + $i) * (20 + 20 * ($i + 1))));
            $t[$i]->rotateTo(round(sin($j / $frames * 2 * pi() + $i / 10) * 360));
        }
        $m->nextFrame();
    }

    header('Content-Type: application/x-shockwave-flash');
    $m->output(0);
