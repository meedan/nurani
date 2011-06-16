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
 * Class Name: Arabic Soundex
 *
 * Filename:   ArSoundex.class.php
 *
 * Original    Author(s): Khaled Al-Sham'aa <khaled@ar-php.org>
 *
 * Purpose:    Arabic soundex algorithm takes Arabic word as an input
 *             and produces a character string which identifies a set words
 *             that are (roughly) phonetically alike.
 *              
 * ----------------------------------------------------------------------
 *  
 * Arabic Soundex
 *
 * PHP class for Arabic soundex algorithm takes Arabic word as an input and
 * produces a character string which identifies a set words of those are
 * (roughly) phonetically alike.
 * 
 * Terms that are often misspelled can be a problem for database designers. Names, 
 * for example, are variable length, can have strange spellings, and they are not 
 * unique. Words can be misspelled or have multiple spellings, especially across 
 * different cultures or national sources.
 * 
 * To solve this problem, we need phonetic algorithms which can find similar 
 * sounding terms and names. Just such a family of algorithms exists and is called 
 * SoundExes, after the first patented version.
 * 
 * A Soundex search algorithm takes a word, such as a person's name, as input and 
 * produces a character string which identifies a set of words that are (roughly) 
 * phonetically alike. It is very handy for searching large databases when the user 
 * has incomplete data.
 * 
 * The original Soundex algorithm was patented by Margaret O'Dell and Robert 
 * C. Russell in 1918. The method is based on the six phonetic classifications of 
 * human speech sounds (bilabial, labiodental, dental, alveolar, velar, and 
 * glottal), which in turn are based on where you put your lips and tongue to make 
 * the sounds.
 * 
 * Soundex function that is available in PHP, but it has been limited to English and 
 * other Latin-based languages. This function described in PHP manual as the 
 * following: Soundex keys have the property that words pronounced similarly produce 
 * the same soundex key, and can thus be used to simplify searches in databases 
 * where you know the pronunciation but not the spelling. This soundex function 
 * returns string of 4 characters long, starting with a letter.
 * 
 * We develop this class as an Arabic counterpart to English Soundex, it handle an 
 * Arabic input string formatted in UTF-8 character set to return Soundex key 
 * equivalent to normal soundex function in PHP even for English and other 
 * Latin-based languages because the original algorithm focus on phonetically 
 * characters alike not the meaning of the word itself.
 * 
 * Example:
 * <code>
 *   include('./Arabic.php');
 *   $obj = new Arabic('ArSoundex');
 *     
 *   $soundex = $obj->soundex($name);
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
// $obj = new I18N\Arabic\ArSoundex();
// 
// use I18N\Arabic;
// $obj = new Arabic\ArSoundex();
//
// use I18N\Arabic\ArSoundex as Soundex;
// $obj = new Soundex();

/**
 * This PHP class implement Arabic soundex algorithm
 *  
 * @category  I18N 
 * @package   Arabic
 * @author    Khaled Al-Sham'aa <khaled@ar-php.org>
 * @copyright 2006-2011 Khaled Al-Sham'aa
 *    
 * @license   LGPL <http://www.gnu.org/licenses/lgpl.txt>
 * @link      http://www.ar-php.org 
 */ 
class ArSoundex
{
    protected $asoundexCode    = array();
    protected $aphonixCode     = array();
    protected $transliteration = array();
    protected $map             = array();
    
    protected $len  = 4;
    protected $lang = 'en';
    protected $code = 'soundex';

    /**
     * "soundex" method output charset
     * @var String     
     */         
    public $soundexOutput = 'utf-8';

    /**
     * "soundex" method input charset
     * @var String     
     */         
    public $soundexInput = 'utf-8';

    /**
     * Name of the textual "soundex" method parameters 
     * @var Array     
     */         
    public $soundexVars = array('word');
    
    /**
     * Loads initialize values
     */         
    public function __construct()
    {
        $xml = simplexml_load_file(dirname(__FILE__).'/data/ArSoundex.xml');
        
        foreach ($xml->asoundexCode->item as $item) {
            $index = $item['id'];
            $value = (string) $item;
            $this->asoundexCode["$value"] = $index;
        } 

        foreach ($xml->aphonixCode->item as $item) {
            $index = $item['id'];
            $value = (string) $item;
            $this->aphonixCode["$value"] = $index;
        } 
        
        foreach ($xml->transliteration->item as $item) {
            $index = $item['id'];
            $this->transliteration["$index"] = (string)$item;
        } 

        $this->map = $this->asoundexCode;
    }
    
    /**
     * Set the length of soundex key (default value is 4)
     *      
     * @param integer $integer Soundex key length
     *      
     * @return object $this to build a fluent interface
     * @author Khaled Al-Sham'aa <khaled@ar-php.org>
     */
    public function setLen($integer)
    {
        $this->len = (int)$integer;
        
        return $this;
    }
    
    /**
     * Set the language of the soundex key (default value is "en")
     *      
     * @param string $str Soundex key language [ar|en]
     *      
     * @return object $this to build a fluent interface
     * @author Khaled Al-Sham'aa <khaled@ar-php.org>
     */
    public function setLang($str)
    {
        $str = strtolower($str);
        
        if ($str == 'ar' || $str == 'en') {
            $this->lang = $str;
        }
        
        return $this;
    }
    
    /**
     * Set the mapping code of the soundex key (default value is "soundex")
     *      
     * @param string $str Soundex key mapping code [soundex|phonix]
     *      
     * @return object $this to build a fluent interface
     * @author Khaled Al-Sham'aa <khaled@ar-php.org>
     */
    public function setCode($str)
    {
        $str = strtolower($str);
        
        if ($str == 'soundex' || $str == 'phonix') {
            $this->code = $str;
            if ($str == 'phonix') {
                $this->map = $this->aphonixCode;
            } else {
                $this->map = $this->asoundexCode;
            }
        }
        
        return $this;
    }
    
    /**
     * Get the soundex key length used now
     *      
     * @return integer return current setting for soundex key length
     * @author Khaled Al-Sham'aa <khaled@ar-php.org>
     */
    public function getLen()
    {
        return $this->len;
    }
    
    /**
     * Get the soundex key language used now
     *      
     * @return string return current setting for soundex key language
     * @author Khaled Al-Sham'aa <khaled@ar-php.org>
     */
    public function getLang()
    {
        return $this->lang;
    }
    
    /**
     * Get the soundex key calculation method used now
     *      
     * @return string return current setting for soundex key calculation method
     * @author Khaled Al-Sham'aa <khaled@ar-php.org>
     */
    public function getCode()
    {
        return $this->code;
    }
    
    /**
     * Methode to get soundex/phonix numric code for given word
     *      
     * @param string $word The word that we want to encode it
     *      
     * @return string The calculated soundex/phonix numeric code
     * @author Khaled Al-Sham'aa <khaled@ar-php.org>
     */
    protected function mapCode($word)
    {
        $encodedWord = '';
        
        $max   = mb_strlen($word, 'UTF-8');
        
        for ($i=0; $i < $max; $i++) {
            $char = mb_substr($word, $i, 1, 'UTF-8');
            if (isset($this->map["$char"])) {
                $encodedWord .= $this->map["$char"];
            } else {
                $encodedWord .= '0';
            }
        }
        
        return $encodedWord;
    }
    
    /**
     * Remove any characters replicates
     *      
     * @param string $word Arabic word you want to check if it is feminine
     *      
     * @return string Same word without any duplicate chracters
     * @author Khaled Al-Sham'aa <khaled@ar-php.org>
     */
    protected function trimRep($word)
    {
        $lastChar  = null;
        $cleanWord = null;
        $max       = mb_strlen($word, 'UTF-8');
        
        for ($i = 0; $i < $max; $i++) {
            $char = mb_substr($word, $i, 1, 'UTF-8');
            if ($char != $lastChar) {
                $cleanWord .= $char;
            }
            $lastChar = $char;
        }
        
        return $cleanWord;
    }
    
    /**
     * Arabic soundex algorithm takes Arabic word as an input and produces a 
     * character string which identifies a set words that are (roughly) 
     * phonetically alike.
     *      
     * @param string $word Arabic word you want to calculate its soundex
     *                    
     * @return string Soundex value for a given Arabic word
     * @author Khaled Al-Sham'aa <khaled@ar-php.org>
     */
    public function soundex($word)
    {
        $soundex = mb_substr($word, 0, 1, 'UTF-8');
        $rest    = mb_substr($word, 1, mb_strlen($word, 'UTF-8'), 'UTF-8');
        
        if ($this->lang == 'en') {
            $soundex = $this->transliteration[$soundex];
        }
        
        $encodedRest      = $this->mapCode($rest);
        $cleanEncodedRest = $this->trimRep($encodedRest);
        
        $soundex .= $cleanEncodedRest;
        
        $soundex = str_replace('0', '', $soundex);
        
        $totalLen = mb_strlen($soundex, 'UTF-8');
        if ($totalLen > $this->len) {
            $soundex = mb_substr($soundex, 0, $this->len, 'UTF-8');
        } else {
            $soundex .= str_repeat('0', $this->len - $totalLen);
        }
        
        return $soundex;
    }
}
