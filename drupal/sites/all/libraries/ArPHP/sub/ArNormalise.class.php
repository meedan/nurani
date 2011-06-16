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
 * Class Name: Functions to normalise Arabic text.
 *  
 * Filename:   ArNormalise.class.php
 *  
 * Original    Author(s): Khaled Al-Sham'aa <khaled@ar-php.org>
 *  
 * Purpose:   Text normalisation through various stages. Also: unshaping. 
 *  
 * ----------------------------------------------------------------------
 *  
 *  This class provides various functions to manipulate arabic text and
 *  normalise it by applying filters, for example, to strip tatweel and
 *  tashkeel, to normalise hamza and lamalephs, and to unshape
 *  a joined Arabic text back into its normalised form.
 *
 *  There is also a function to reverse a utf8 string.
 *
 *  The functions are helpful for searching, indexing and similar 
 *  functions.
 *
 * Note that this class can only deal with UTF8 strings. You can use functions
 * from the other classes to convert between encodings if necessary.
 *
 * Example:
 * <code>
 *     include('./Arabic.php');
 *     $Ar = new Arabic('ArNormalise');
 * 
 *     $str = "Arabic text with tatweel, tashkeel...";
 * 
 *     echo "<p><u><i>Before:</i></u><br />$str<br /><br />";
 *     
 *     $text = $Ar->stripTatweel($str);
 *        
 *     echo "<u><i>After:</i></u><br />$text<br /><br />";    
 * </code>                  
 *
 * @category  I18N 
 * @package   Arabic
 * @author    Djihed Afifi <djihed@gmail.com>
 * @copyright 2006-2011 Khaled Al-Sham'aa
 *    
 * @license   LGPL <http://www.gnu.org/licenses/lgpl.txt>
 * @link      http://www.ar-php.org 
 */

// New in PHP V5.3: Namespaces
// namespace I18N\Arabic;
// 
// $obj = new I18N\Arabic\ArNormalise();
// 
// use I18N\Arabic;
// $obj = new Arabic\ArNormalise();
//
// use I18N\Arabic\ArNormalise as Normalise;
// $obj = new Normalise();

/**
 *  This class provides various functions to manipulate arabic text and
 *  normalise it by applying filters, for example, to strip tatweel and
 *  tashkeel, to normalise hamza and lamalephs, and to unshape
 *  a joined Arabic text back into its normalised form.
 *
 *  The functions are helpful for searching, indexing and similar 
 *  functions.
 *  
 * @category  I18N 
 * @package   Arabic
 * @author    Djihed Afifi <djihed@gmail.com>
 * @copyright 2006-2011 Khaled Al-Sham'aa
 *    
 * @license   LGPL <http://www.gnu.org/licenses/lgpl.txt>
 * @link      http://www.ar-php.org 
 */ 
class ArNormalise
{
    protected $unshape_map    = array();
    protected $unshape_keys   = array();
    protected $unshape_values = array();
    protected $chars          = array();

    /**
     * "stripTatweel" method input charset
     * @var String     
     */         
    public $stripTatweelInput = 'utf-8';

    /**
     * Name of the textual "stripTatweel" method parameters 
     * @var Array     
     */         
    public $stripTatweelVars = array('text');

    /**
     * "stripTatweel" method output charset
     * @var String     
     */         
    public $stripTatweelOutput = 'utf-8';

    /**
     * "stripTashkeel" method input charset
     * @var String     
     */         
    public $stripTashkeelInput = 'utf-8';

    /**
     * Name of the textual "stripTashkeel" method parameters 
     * @var Array     
     */         
    public $stripTashkeelVars = array('text');

    /**
     * "stripTashkeel" method output charset
     * @var String     
     */         
    public $stripTashkeelOutput = 'utf-8';

    /**
     * "normaliseHamza" method input charset
     * @var String     
     */         
    public $normaliseHamzaInput = 'utf-8';

    /**
     * Name of the textual "normaliseHamza" method parameters 
     * @var Array     
     */         
    public $normaliseHamzaVars = array('text');

    /**
     * "normaliseHamza" method output charset
     * @var String     
     */         
    public $normaliseHamzaOutput = 'utf-8';

    /**
     * "normaliseLamaleph" method input charset
     * @var String     
     */         
    public $normaliseLamalephInput = 'utf-8';

    /**
     * Name of the textual "normaliseLamaleph" method parameters 
     * @var Array     
     */         
    public $normaliseLamalephVars = array('text');

    /**
     * "normaliseLamaleph" method output charset
     * @var String     
     */         
    public $normaliseLamalephOutput = 'utf-8';

    /**
     * "normalise" method input charset
     * @var String     
     */         
    public $normaliseInput = 'utf-8';

    /**
     * Name of the textual "normalise" method parameters 
     * @var Array     
     */         
    public $normaliseVars = array('text');

    /**
     * "normalise" method output charset
     * @var String     
     */         
    public $normaliseOutput = 'utf-8';

    /**
     * "utf8Strrev" method input charset
     * @var String     
     */         
    public $utf8StrrevInput = 'utf-8';

    /**
     * Name of the textual "utf8Strrev" method parameters 
     * @var Array     
     */         
    public $utf8StrrevVars = array('str');

    /**
     * "utf8Strrev" method output charset
     * @var String     
     */         
    public $utf8StrrevOutput = 'utf-8';
   
     /**
      * Load the Unicode constants that will be used ibn substitutions
      * and normalisations.
      */
    public function __construct() 
    {
        include_once(dirname(__FILE__) . '/charset/ArUnicode.constants.php');

        $this->unshape_map    = $ligature_map;
        $this->unshape_keys   = array_keys($this->unshape_map);
        $this->unshape_values = array_values($this->unshape_map);
        $this->chars          = $char_names;
    }    

    /**
     * Strip all tatweel characters from an Arabic text.
     * 
     * @param string $text The text to be stripped.
     *      
     * @return string the stripped text.
     * @author Djihed Afifi <djihed@gmail.com>
     */ 
    public function stripTatweel($text) 
    {
        return str_replace($this->chars['TATWEEL'], '', $text); 
    }

    /**
     * Strip all tashkeel characters from an Arabic text.
     * 
     * @param string $text The text to be stripped.
     *      
     * @return string the stripped text.
     * @author Djihed Afifi <djihed@gmail.com>
     */ 
    public function stripTashkeel($text) 
    {
        $tashkeel = array(
             $this->chars['FATHATAN'], 
             $this->chars['DAMMATAN'], 
             $this->chars['KASRATAN'], 
             $this->chars['FATHA'], 
             $this->chars['DAMMA'], 
             $this->chars['KASRA'],
             $this->chars['SUKUN'],
             $this->chars['SHADDA']
        );
        return str_replace($tashkeel, "", $text);
    }

    /**
     * Normalise all Hamza characters to their corresponding aleph 
     * character in an Arabic text.
     *
     * @param string $text The text to be normalised.
     *      
     * @return string the normalised text.
     * @author Djihed Afifi <djihed@gmail.com>
     */ 
    public function normaliseHamza($text) 
    {
        $replace = array(
             $this->chars['WAW_HAMZA'] = $this->chars['WAW'],
             $this->chars['YEH_HAMZA'] = $this->chars['YEH'],
        );
        $alephs = array(
             $this->chars['ALEF_MADDA'],
             $this->chars['ALEF_HAMZA_ABOVE'],
             $this->chars['ALEF_HAMZA_BELOW'],
             $this->chars['HAMZA_ABOVE,HAMZA_BELOW']
        );

        $text = str_replace(array_keys($replace), array_values($replace), $text);
        $text = str_replace($alephs, $this->chars['ALEF'], $text);
        return $text;
    }

    /**
     * Unicode uses some special characters where the lamaleph and any
     * hamza above them are combined into one code point. Some input
     * system use them. This function expands these characters.
     *
     * @param string $text The text to be normalised.
     *      
     * @return string the normalised text.
     * @author Djihed Afifi <djihed@gmail.com>
     */ 
    public function normaliseLamaleph ($text) 
    {
        $text = str_replace($this->chars['LAM_ALEPH'], $simple_LAM_ALEPH, $text);
        $text = str_replace($this->chars['LAM_ALEPH_HAMZA_ABOVE'], 
                            $simple_LAM_ALEPH_HAMZA_ABOVE, $text);
        $text = str_replace($this->chars['LAM_ALEPH_HAMZA_BELOW'], 
                            $simple_LAM_ALEPH_HAMZA_BELOW, $text);
        $text = str_replace($this->chars['LAM_ALEPH_MADDA_ABOVE'], 
                            $simple_LAM_ALEPH_MADDA_ABOVE, $text);
        return $text;
    }

    /**
     * Return unicode char by its code point.
     *
     * @param char $u code point
     *      
     * @return string the result character.
     * @author Djihed Afifi <djihed@gmail.com>
     */
    public function unichr($u) 
    {
        return mb_convert_encoding('&#'.intval($u).';', 'UTF-8', 'HTML-ENTITIES');
    }

    /**
     * Takes a string, it applies the various filters in this class
     * to return a unicode normalised string suitable for activities
     * such as searching, indexing, etc.
     *
     * @param string $text the text to be normalised.
     *      
     * @return string the result normalised string.
     * @author Djihed Afifi <djihed@gmail.com>
     */ 
    public function normalise($text)
    {
        $text = $this->stripTashkeel($text);
        $text = $this->stripTatweel($text);
        $text = $this->normaliseHamza($text);
        $text = $this->normaliseLamaleph($text);

        return $text;
    } 

    /**
     * Takes Arabic text in its joined form, it untangles the characters
     * and  unshapes them.
     *
     * This can be used to process text that was processed through OCR
     * or by extracting text from a PDF document.
     *
     * Note that the result text may need further processing. In most
     * cases, you will want to use the utf8Strrev function from
     * this class to reverse the string.
     *  
     * Most of the work of setting up the characters for this function
     * is done through the ArUnicode.constants.php constants and 
     * the constructor loading.
     *
     * @param string $text the text to be unshaped.
     *      
     * @return string the result normalised string.
     * @author Djihed Afifi <djihed@gmail.com>
     * */
    public function unshape($text)
    {
          return str_replace($this->unshape_keys, $this->unshape_values, $text);
    }

    /**
     * Take a UTF8 string and reverse it.
     *
     * @param string  $str             the string to be reversed.
     * @param boolean $reverse_numbers whether to reverse numbers.
     *      
     * @return string The reversed string.
     * */
    public function utf8Strrev($str, $reverse_numbers = false) 
    {
        preg_match_all('/./us', $str, $ar);
        if ($reverse_numbers) {
            return join('', array_reverse($ar[0]));
        } else {
            $temp = array();
            foreach ($ar[0] as $value) {
                if (is_numeric($value) && !empty($temp[0]) && is_numeric($temp[0])) {
                    foreach ($temp as $key => $value2) {
                        if (is_numeric($value2)) {
                            $pos = ($key + 1);
                        } else {
                            break;
                        }
                    }
                    $temp2 = array_splice($temp, $pos);
                    $temp  = array_merge($temp, array($value), $temp2);
                } else {
                    array_unshift($temp, $value);
                }
            }
            return implode('', $temp);
        }
    }
}

