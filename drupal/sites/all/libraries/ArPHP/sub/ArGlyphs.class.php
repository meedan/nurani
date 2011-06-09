<?php
/**
 * ----------------------------------------------------------------------
 *  
 * Copyright (c) 2006-2011 Khaled Al-Sham'aa.
 *  
 * http://www.ar-php.org
 *  
 * PHP Version 5 
 *  
 * ----------------------------------------------------------------------
 *  
 * LICENSE
 *
 * This program is open source product; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License (LGPL)
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *  
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *  
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/lgpl.txt>.
 *  
 * ----------------------------------------------------------------------
 *  
 * Class Name: Arabic Glyphs is a simple class to render Arabic text
 *  
 * Filename:   ArGlyphs.class.php
 *  
 * Original    Author(s): Khaled Al-Sham'aa <khaled@ar-php.org>
 *  
 * Purpose:    This class takes Arabic text (encoded in Windows-1256 character 
 *             set) as input and performs Arabic glyph joining on it and outputs 
 *             a UTF-8 hexadecimals stream that is no longer logically arranged 
 *             but in a visual order which gives readable results when formatted 
 *             with a simple Unicode rendering just like GD and UFPDF libraries 
 *             that does not handle basic connecting glyphs of Arabic language 
 *             yet but simply outputs all stand alone glyphs in left-to-right 
 *             order.
 *              
 * ----------------------------------------------------------------------
 *  
 * Arabic Glyphs is class to render Arabic text
 *
 * PHP class to render Arabic text by performs Arabic glyph joining on it,
 * then output a UTF-8 hexadecimals stream gives readable results on PHP
 * libraries supports UTF-8.
 *
 * Example:
 * <code>
 *   include('./Arabic.php');
 *   $obj = new Arabic('ArGlyphs');
 *
 *   $text = $obj->utf8Glyphs($text);
 *      
 *   imagettftext($im, 20, 0, 200, 100, $black, $font, $text);
 * </code>
 *
 * @category  I18N 
 * @package   Arabic
 * @author    Khaled Al-Sham'aa <khaled@ar-php.org>
 * @copyright 2006-2011 Khaled Al-Sham'aa
 *    
 * @license   LGPL <http://www.gnu.org/licenses/lgpl.txt>
 * @link      http://www.ar-php.org 
 */

// New in PHP V5.3: Namespaces
// namespace I18N\Arabic;
// 
// $obj = new I18N\Arabic\ArGlyphs();
// 
// use I18N\Arabic;
// $obj = new Arabic\ArGlyphs();
//
// use I18N\Arabic\ArGlyphs as Glyphs;
// $obj = new Glyphs();

/**
 * This PHP class render Arabic text by performs Arabic glyph joining on it
 *  
 * @category  I18N 
 * @package   Arabic
 * @author    Khaled Al-Sham'aa <khaled@ar-php.org>
 * @copyright 2006-2011 Khaled Al-Sham'aa
 *    
 * @license   LGPL <http://www.gnu.org/licenses/lgpl.txt>
 * @link      http://www.ar-php.org 
 */ 
class ArGlyphs
{
    protected $glyphs   = null;
    protected $hex      = null;
    protected $prevLink = null;
    protected $nextLink = null;
    protected $vowel    = null;

    /**
     * "a4Lines" method input charset
     * @var String     
     */         
    public $a4LinesInput = 'windows-1256';

    /**
     * Name of the textual "a4Lines" method parameters 
     * @var Array     
     */         
    public $a4LinesVars = array('str');

    /**
     * "utf8Glyphs" method input charset
     * @var String     
     */         
    public $utf8GlyphsInput = 'windows-1256';

    /**
     * Name of the textual "utf8Glyphs" method parameters 
     * @var Array     
     */         
    public $utf8GlyphsVars = array('str');
    
    /**
     * Loads initialize values
     */         
    public function __construct()
    {
        $this->prevLink = '°ø∫‹∆» ÀÃÕŒ”‘’÷ÿŸ⁄€›ﬁﬂ·„‰ÂÌ';
        $this->nextLink = '‹¬√ƒ≈«∆»… ÀÃÕŒœ–—“”‘’÷ÿŸ⁄€›ﬁﬂ·„‰ÂÊÏÌ';
        $this->vowel    = 'ÒÚÛıˆ¯˙';

        /*
         $this->glyphs['']  = array('FE70','FE71');
         $this->glyphs['Ò']  = array('FE72','FE72');
         $this->glyphs['Ú']  = array('FE74','FE74');
         $this->glyphs['Û']  = array('FE76','FE77');
         $this->glyphs['ı']  = array('FE78','FE79');
         $this->glyphs['ˆ']  = array('FE7A','FE7B');
         $this->glyphs['¯']  = array('FE7C','FE7D');
         $this->glyphs['˙']  = array('FE7E','FE7E');
         */
        $this->glyphs = 'ÒÚÛıˆ¯˙';
        $this->hex    = '064B064B064B064B064C064C064C064C064D064D064D064D064E064E';
        $this->hex   .= '064E064E064F064F064F064F06500650065006500651065106510651';
        $this->hex   .= '0652065206520652';

        $this->glyphs .= '¡¬√ƒ≈∆«»';
        $this->hex    .= 'FE80FE80FE80FE80FE81FE82FE81FE82FE83FE84FE83FE84FE85FE86';
        $this->hex    .= 'FE85FE86FE87FE88FE87FE88FE89FE8AFE8BFE8CFE8DFE8EFE8DFE8E';
        $this->hex    .= 'FE8FFE90FE91FE92';

        $this->glyphs .= '… ÀÃÕŒœ–';
        $this->hex    .= 'FE93FE94FE93FE94FE95FE96FE97FE98FE99FE9AFE9BFE9CFE9DFE9E';
        $this->hex    .= 'FE9FFEA0FEA1FEA2FEA3FEA4FEA5FEA6FEA7FEA8FEA9FEAAFEA9FEAA';
        $this->hex    .= 'FEABFEACFEABFEAC';

        $this->glyphs .= '—“”‘’÷ÿŸ';
        $this->hex    .= 'FEADFEAEFEADFEAEFEAFFEB0FEAFFEB0FEB1FEB2FEB3FEB4FEB5FEB6';
        $this->hex    .= 'FEB7FEB8FEB9FEBAFEBBFEBCFEBDFEBEFEBFFEC0FEC1FEC2FEC3FEC4';
        $this->hex    .= 'FEC5FEC6FEC7FEC8';

        $this->glyphs .= '⁄€›ﬁﬂ·„‰';
        $this->hex    .= 'FEC9FECAFECBFECCFECDFECEFECFFED0FED1FED2FED3FED4FED5FED6';
        $this->hex    .= 'FED7FED8FED9FEDAFEDBFEDCFEDDFEDEFEDFFEE0FEE1FEE2FEE3FEE4';
        $this->hex    .= 'FEE5FEE6FEE7FEE8';

        $this->glyphs .= 'ÂÊÏÌ‹°ø∫';
        $this->hex    .= 'FEE9FEEAFEEBFEECFEEDFEEEFEEDFEEEFEEFFEF0FEEFFEF0FEF1FEF2';
        $this->hex    .= 'FEF3FEF40640064006400640060C060C060C060C061F061F061F061F';
        $this->hex    .= '061B061B061B061B';

        // Support the extra 4 Persian letters (p), (ch), (zh) and (g)
        // This needs value in getGlyphs function to be 52 instead of 48
        // $this->glyphs .= chr(129).chr(141).chr(142).chr(144);
        // $this->hex    .= 'FB56FB57FB58FB59FB7AFB7BFB7CFB7DFB8AFB8BFB8AFB8BFB92';
        // $this->hex    .= 'FB93FB94FB95';
        //
        // $this->prevLink .= chr(129).chr(141).chr(142).chr(144);
        // $this->nextLink .= chr(129).chr(141).chr(142).chr(144);
        //
        // Example:     $text = '‰„Ê‰… ﬁ·„: ·«êç é«›Å';
        // Email Yossi Beck <yosbeck@gmail.com> ask him to save that example
        // string using ANSI encoding in Notepad

        $this->glyphs .= '·¬·√·≈·«';
        $this->hex    .= 'FEF5FEF6FEF5FEF6FEF7FEF8FEF7FEF8FEF9FEFAFEF9FEFAFEFBFEFC';
        $this->hex    .= 'FEFBFEFC';
    }
    
    /**
     * Get glyphs
     * 
     * @param string  $char Char
     * @param integer $type Type
     * 
     * @return string
     */                                  
    protected function getGlyphs($char, $type)
    {

        $pos = strpos($this->glyphs, $char);
        
        if ($pos > 48) {
            $pos = ($pos-48)/2 + 48;
        }
        
        $pos = $pos*16 + $type*4;
        
        return substr($this->hex, $pos, 4);
    }
    
    /**
     * Convert Arabic Windows-1256 charset string into glyph joining in UTF-8 
     * hexadecimals stream
     *      
     * @param string $str Arabic string in Windows-1256 charset
     *      
     * @return string Arabic glyph joining in UTF-8 hexadecimals stream
     * @author Khaled Al-Sham'aa <khaled@ar-php.org>
     */
    protected function preConvert($str)
    {
        $crntChar = null;
        $prevChar = null;
        $nextChar = null;
        $output   = '';
        
        $chars = str_split($str);
        $max   = count($chars);

        for ($i = $max - 1; $i >= 0; $i--) {
            $crntChar = $chars[$i];
            
            if ($i > 0) {
                $prevChar = $chars[$i - 1];
            }
            
            if ($prevChar && strpos($this->vowel, $prevChar) !== false) {
                $prevChar = $chars[$i - 2];
                if ($prevChar && strpos($this->vowel, $prevChar) !== false) {
                    $prevChar = $chars[$i - 3];
                }
            }
            
            $Reversed    = false;
            $flip_arr    = ')]>}';
            $ReversedChr = '([<{';
            
            if ($crntChar && strpos($flip_arr, $crntChar) !== false) {
                $crntChar = $ReversedChr[strpos($flip_arr, $crntChar)];
                $Reversed = true;
            } else {
                $Reversed = false;
            }
            
            if ($crntChar && !$Reversed && 
                (strpos($ReversedChr, $crntChar) !== false)) {
                $crntChar = $flip_arr[strpos($ReversedChr, $crntChar)];
            }
            
            if (ord($crntChar) < 128) {
                $output  .= $crntChar;
                $nextChar = $crntChar;
                continue;
            }
            
            if ($crntChar == '·' && isset($chars[$i + 1]) && 
                (strpos('¬√≈«', $chars[$i + 1]) !== false)) {
                continue;
            }
            
            if ($crntChar && strpos($this->vowel, $crntChar) !== false) {
                if ((strpos($this->nextLink, $chars[$i + 1]) !== false) && 
                    (strpos($this->prevLink, $prevChar) !== false)) {
                    $output .= '&#x' . $this->getGlyphs($crntChar, 1) . ';';
                } else {
                    $output .= '&#x' . $this->getGlyphs($crntChar, 0) . ';';
                }
                continue;
            }
            
            $form = 0;
            
            if ($prevChar == '·' && (strpos('¬√≈«', $crntChar) !== false)) {
                if (strpos($this->prevLink, $chars[$i - 2]) !== false) {
                    $form++;
                }
                
                $output  .= '&#x'.$this->getGlyphs($prevChar.$crntChar, $form).';';
                $nextChar = $prevChar;
                continue;
            }
            
            if ($prevChar && strpos($this->prevLink, $prevChar) !== false) {
                $form++;
            }
            
            if ($nextChar && strpos($this->nextLink, $nextChar) !== false) {
                $form += 2;
            }
            
            $output  .= '&#x' . $this->getGlyphs($crntChar, $form) . ';';
            $nextChar = $crntChar;
        }
        
        // from Arabic Presentation Forms-B, Range: FE70-FEFF, 
        // file "UFE70.pdf" (in reversed order)
        // into Arabic Presentation Forms-A, Range: FB50-FDFF, file "UFB50.pdf"
        // Example: $output = str_replace('&#xFEA0;&#xFEDF;', '&#xFCC9;', $output);
        // Lam Jeem

        $output = $this->decodeEntities($output, $exclude = array('&'));
        return $output;
    }
    
    /**
     * Regression analysis calculate roughly the max number of character fit in 
     * one A4 page line for a given font size.
     *      
     * @param integer $font Font size
     *      
     * @return integer Maximum number of characters per line
     * @author Khaled Al-Sham'aa <khaled@ar-php.org>
     */
    public function a4MaxChars($font)
    {
        $x = 381.6 - 31.57 * $font + 1.182 * pow($font, 2) - 0.02052 * 
             pow($font, 3) + 0.0001342 * pow($font, 4);
        return floor($x - 2);
    }
    
    /**
     * Calculate the lines number of given Arabic text and font size that will 
     * fit in A4 page size
     *      
     * @param string  $str  Arabic string you would like to split it into lines
     * @param integer $font Font size
     *                    
     * @return integer Number of lines for a given Arabic string in A4 page size
     * @author Khaled Al-Sham'aa <khaled@ar-php.org>
     */
    public function a4Lines($str, $font)
    {
        $str = str_replace(array("\r\n", "\n", "\r"), "\n", $str);
        
        $lines     = 0;
        $chars     = 0;
        $words     = explode(' ', $str);
        $w_count   = count($words);
        $max_chars = $this->a4MaxChars($font);
        
        for ($i = 0; $i < $w_count; $i++) {
            $w_len = strlen($words[$i]) + 1;
            
            if ($chars + $w_len < $max_chars) {
                if (strpos($words[$i], "\n") !== false) {
                    $words_nl = explode("\n", $words[$i]);
                    
                    $nl_num = count($words_nl) - 1;
                    for ($j = 1; $j < $nl_num; $j++) {
                        $lines++;
                    }
                    
                    $chars = strlen($words_nl[$nl_num]) + 1;
                } else {
                    $chars += $w_len;
                }
            } else {
                $lines++;
                $chars = $w_len;
            }
        }
        $lines++;
        
        return $lines;
    }
    
    /**
     * Convert Arabic Windows-1256 charset string into glyph joining in UTF-8 
     * hexadecimals stream (take care of whole the document including English 
     * sections as well as numbers and arcs etc...)
     *                    
     * @param string  $str       Arabic string in Windows-1256 charset
     * @param integer $max_chars Max number of chars you can fit in one line
     * @param boolean $hindo     If true use Hindo digits else use Arabic digits
     *                    
     * @return string Arabic glyph joining in UTF-8 hexadecimals stream (take
     *                care of whole document including English sections as well
     *                as numbers and arcs etc...)
     * @author Khaled Al-Sham'aa <khaled@ar-php.org>
     */
    public function utf8Glyphs($str, $max_chars = 50, $hindo = true)
    {
        $str = str_replace(array("\r\n", "\n", "\r"), " \n", $str);
        $str = str_replace("\t", "        ", $str);
        
        $lines   = array();
        $words   = explode(' ', $str);
        $w_count = count($words);
        $c_chars = 0;
        $c_words = array();
        
        $english  = array();
        $en_index = -1;
        
        for ($i = 0; $i < $w_count; $i++) {
            $pattern  = '/^(\n?)';
            $pattern .= '[a-z\d\\/\@\#\$\%\^\&\*\(\)\_\~\"\'\[\]\{\}\;\,\|\-\.\:]*';
            $pattern .= '([\.\:\+\=\-\!°ø]?)$/i';
            
            if (preg_match($pattern, $words[$i], $matches)) {
                if ($matches[1]) {
                    $words[$i] = substr($words[$i], 1).$matches[1];
                }
                if ($matches[2]) {
                    $words[$i] = $matches[2].substr($words[$i], 0, -1);
                }
                $words[$i] = strrev($words[$i]);
                array_push($english, $words[$i]);
                if ($en_index == -1) {
                    $en_index = $i;
                }
            } elseif ($en_index != -1) {
                $en_count = count($english);
                
                for ($j = 0; $j < $en_count; $j++) {
                    $words[$en_index + $j] = $english[$en_count - 1 - $j];
                }
                
                $en_index = -1;
                $english  = array();
            }
        }
        
        for ($i = 0; $i < $w_count; $i++) {
            $w_len = strlen($words[$i]) + 1;
            
            if ($c_chars + $w_len < $max_chars) {
                if (strpos($words[$i], "\n") !== false) {
                    $words_nl = explode("\n", $words[$i]);
                    
                    array_push($c_words, $words_nl[0]);
                    array_push($lines, implode(' ', $c_words));
                    
                    $nl_num = count($words_nl) - 1;
                    for ($j = 1; $j < $nl_num; $j++) {
                        array_push($lines, $words_nl[$j]);
                    }
                    
                    $c_words = array($words_nl[$nl_num]);
                    $c_chars = strlen($words_nl[$nl_num]) + 1;
                } else {
                    array_push($c_words, $words[$i]);
                    $c_chars += $w_len;
                }
            } else {
                array_push($lines, implode(' ', $c_words));
                $c_words = array($words[$i]);
                $c_chars = $w_len;
            }
        }
        array_push($lines, implode(' ', $c_words));
        
        $maxLine = count($lines);
        $output  = '';
        
        for ($j = $maxLine - 1; $j >= 0; $j--) {
            $output .= $lines[$j] . "\n";
        }
        
        $output = rtrim($output);
        
        $output = $this->preConvert($output);
        if ($hindo) {
            $nums   = array(0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
            $arNums = array('Ÿ†', 'Ÿ°', 'Ÿ¢', 'Ÿ£', 'Ÿ§', 
                            'Ÿ•', 'Ÿ¶', 'Ÿß', 'Ÿ®', 'Ÿ©');
            $output = str_replace($nums, $arNums, $output);
        }
        
        return $output;
    }
    
    /**
     * Decode all HTML entities (including numerical ones) to regular UTF-8 bytes. 
     * Double-escaped entities will only be decoded once 
     * ("&amp;lt;" becomes "&lt;", not "<").
     *                   
     * @param string $text    The text to decode entities in.
     * @param array  $exclude An array of characters which should not be decoded.
     *                        For example, array('<', '&', '"'). This affects
     *                        both named and numerical entities.
     *                        
     * @return string           
     */
    protected function decodeEntities($text, $exclude = array())
    {
        static $table;
        
        // We store named entities in a table for quick processing.
        if (!isset($table)) {
            // Get all named HTML entities.
            $table = array_flip(get_html_translation_table(HTML_ENTITIES));
            
            // PHP gives us ISO-8859-1 data, we need UTF-8.
            $table = array_map('utf8_encode', $table);
            
            // Add apostrophe (XML)
            $table['&apos;'] = "'";
        }
        $newtable = array_diff($table, $exclude);
        
        // Use a regexp to select all entities in one pass, to avoid decoding 
        // double-escaped entities twice.
        //return preg_replace('/&(#x?)?([A-Za-z0-9]+);/e', 
        //                    '$this->decodeEntities2("$1", "$2", "$0", $newtable, 
        //                                             $exclude)', $text);

        $pieces = explode('&', $text);
        $text   = array_shift($pieces);
        foreach ($pieces as $piece) {
            if ($piece[0] == '#') {
                if ($piece[1] == 'x') {
                    $one = '#x';
                } else {
                    $one = '#';
                }
            } else {
                $one = '';
            }
            $end   = strpos($piece, ';');
            $start = strlen($one);
            
            $two   = substr($piece, $start, $end - $start);
            $zero  = '&'.$one.$two.';';
            $text .= $this->decodeEntities2($one, $two, $zero, $newtable, $exclude).
                     substr($piece, $end+1);
        }
        return $text;
    }
    
    /**
     * Helper function for decodeEntities
     * 
     * @param string $prefix    Prefix      
     * @param string $codepoint Codepoint         
     * @param string $original  Original        
     * @param array  &$table    Store named entities in a table      
     * @param array  &$exclude  An array of characters which should not be decoded
     * 
     * @return string                  
     */
    protected function decodeEntities2($prefix, $codepoint, $original, 
                                       &$table, &$exclude)
    {
        // Named entity
        if (!$prefix) {
            if (isset($table[$original])) {
                return $table[$original];
            } else {
                return $original;
            }
        }
        
        // Hexadecimal numerical entity
        if ($prefix == '#x') {
            $codepoint = base_convert($codepoint, 16, 10);
        }
        
        // Encode codepoint as UTF-8 bytes
        if ($codepoint < 0x80) {
            $str = chr($codepoint);
        } elseif ($codepoint < 0x800) {
            $str = chr(0xC0 | ($codepoint >> 6)) . 
                   chr(0x80 | ($codepoint & 0x3F));
        } elseif ($codepoint < 0x10000) {
            $str = chr(0xE0 | ($codepoint >> 12)) . 
                   chr(0x80 | (($codepoint >> 6) & 0x3F)) . 
                   chr(0x80 | ($codepoint & 0x3F));
        } elseif ($codepoint < 0x200000) {
            $str = chr(0xF0 | ($codepoint >> 18)) . 
                   chr(0x80 | (($codepoint >> 12) & 0x3F)) . 
                   chr(0x80 | (($codepoint >> 6) & 0x3F)) . 
                   chr(0x80 | ($codepoint & 0x3F));
        }
        
        // Check for excluded characters
        if (in_array($str, $exclude)) {
            return $original;
        } else {
            return $str;
        }
    }
}

