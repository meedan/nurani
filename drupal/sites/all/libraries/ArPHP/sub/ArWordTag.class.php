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
 * Class Name: Tagging Arabic Word Class
 *  
 * Filename: ArWordTag.class.php
 *  
 * Original  Author(s): Khaled Al-Sham'aa <khaled@ar-php.org>
 *  
 * Purpose:  Arabic grammarians describe Arabic as being derived from
 *           three main categories: noun, verb and particle. This class
 *           built to recognize the class of a given Arabic word.
 *            
 * ----------------------------------------------------------------------
 *  
 * Tagging Arabic Word
 *
 * This PHP Class can identifying names, places, dates, and other noun
 * words and phrases in Arabic language that establish the meaning of a body
 * of text.
 * 
 * This process of identifying names, places, dates, and other noun words and 
 * phrases that establish the meaning of a body of text-is critical to software 
 * systems that process large amounts of unstructured data coming from sources such 
 * as email, document files, and the Web.
 * 
 * Arabic words are classifies into three main classes, namely, verb, noun and 
 * particle. Verbs are sub classified into three subclasses (Past verbs, Present 
 * Verbs, etc.); nouns into forty six subclasses (e.g. Active participle, Passive 
 * participle, Exaggeration pattern, Adjectival noun, Adverbial noun, Infinitive 
 * noun, Common noun, Pronoun, Quantifier, etc.) and particles into twenty three 
 * subclasses (e.g. additional, resumption, Indefinite, Conditional, Conformational, 
 * Prohibition, Imperative, Optative, Reasonal, Dubious, etc.), and from these three 
 * main classes that the rest of the language is derived.
 * 
 * The most important aspect of this system of describing Arabic is that all the 
 * subclasses of these three main classes inherit properties from the parent 
 * classes.
 * 
 * Arabic is very rich in categorising words, and contains classes for almost every 
 * form of word imaginable. For example, there are classes for nouns of instruments, 
 * nouns of place and time, nouns of activity and so on. If we tried to use all the 
 * subclasses described by Arabic grammarians, the size of the tagset would soon 
 * reach more than two or three hundred tags. For this reason, we have chosen only 
 * the main classes. But because of the way all the classes inherit from others, it 
 * would be quite simple to extend this tagset to include more subclasses.      
 *
 * Example:
 * <code>
 *     include('./Arabic.php');
 *     $obj = new Arabic('ArWordTag');
 * 
 *     $hStr=$obj->highlightText($str,'#80B020');
 * 
 *     echo $str . '<hr />' . $hStr . '<hr />';
 *     
 *     $taggedText = $obj->tagText($str);
 * 
 *     foreach($taggedText as $wordTag) {
 *         list($word, $tag) = $wordTag;
 *     
 *         if ($tag == 1) {
 *             echo "<font color=#DBEC21>$word is Noun</font>, ";
 *         }
 *     
 *         if ($tag == 0) {
 *             echo "$word is not Noun, ";
 *         }
 *     }    
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
// $obj = new I18N\Arabic\ArWordTag();
// 
// use I18N\Arabic;
// $obj = new Arabic\ArWordTag();
//
// use I18N\Arabic\ArWordTag as WordTag;
// $obj = new WordTag();

/**
 * This PHP class to tagging Arabic Word
 *  
 * @category  I18N 
 * @package   Arabic
 * @author    Khaled Al-Sham'aa <khaled@ar-php.org>
 * @copyright 2006-2011 Khaled Al-Sham'aa
 *    
 * @license   LGPL <http://www.gnu.org/licenses/lgpl.txt>
 * @link      http://www.ar-php.org 
 */ 
class ArWordTag
{
    protected static $particlePreNouns    = array('⁄‰', '›Ì', '„–', '„‰–', '„‰', 
                                                  '«·Ï', '⁄·Ï', 'Õ Ï', '«·«', 
                                                  '€Ì—', '”ÊÏ', 'Œ·«', '⁄œ«', 
                                                  'Õ«‘«', '·Ì”');
    protected static $normalizeAlef       = array('√','≈','¬');
    protected static $normalizeDiacritics = array('Û','','ı','Ò','ˆ','Ú','˙','¯');

    /**
     * "isNoun" method input charset
     * @var String     
     */         
    public $isNounInput = 'windows-1256';

    /**
     * Name of the textual "isNoun" method parameters 
     * @var Array     
     */         
    public $isNounVars = array('word', 'word_befor');

    /**
     * "tagText" method output charset
     * @var String     
     */         
    public $tagTextOutput = 'windows-1256';

    /**
     * "tagText" method input charset
     * @var String     
     */         
    public $tagTextInput = 'windows-1256';

    /**
     * Name of the textual "tagText" method parameters 
     * @var Array     
     */         
    public $tagTextVars = array('str');

    /**
     * "highlightText" method output charset
     * @var String     
     */         
    public $highlightTextOutput = 'windows-1256';

    /**
     * "highlightText" method input charset
     * @var String     
     */         
    public $highlightTextInput = 'windows-1256';

    /**
     * Name of the textual "highlightText" method parameters 
     * @var Array     
     */         
    public $highlightTextVars = array('str');

    /**
     * Loads initialize values
     */         
    public function __construct()
    {
    }
    
    /**
     * Check if given rabic word is noun or not
     *      
     * @param string $word       Word you want to check if it is 
     *                           noun (windows-1256)
     * @param string $word_befor The word before word you want to check
     *                    
     * @return boolean TRUE if given word is Arabic noun
     * @author Khaled Al-Sham'aa <khaled@ar-php.org>
     */
    public static function isNoun($word, $word_befor)
    {
        $word       = trim($word);
        $word_befor = trim($word_befor);

        $word       = str_replace(self::$normalizeAlef, '«', $word);
        $word_befor = str_replace(self::$normalizeAlef, '«', $word_befor);
        $wordLen    = strlen($word);
        
        // ≈–« ”»ﬁ »Õ—› Ã— ›ÂÊ «”„ „Ã—Ê—
        if (in_array($word_befor, self::$particlePreNouns)) {
            return true;
        }
        
        // ≈–« ”»ﬁ »⁄œœ ›ÂÊ „⁄œÊœ
        if (is_numeric($word) || is_numeric($word_befor)) {
            return true;
        }
        
        // ≈–« ﬂ«‰ „‰Ê‰
        if ($word[$wordLen - 1] == '' ||
            $word[$wordLen - 1] == 'Ò' || 
            $word[$wordLen - 1] == 'Ú') {
            return true;
        }
        
        $word    = str_replace(self::$normalizeDiacritics, '', $word);
        $wordLen = strlen($word);
        
        // ≈‰ ﬂ«‰ „⁄—› »√· «· ⁄—Ì›
        if ($word[0] == '«' && $word[1] == '·' && $wordLen >= 5) {
            return true;
        }
        
        // ≈–« ﬂ«‰ ›Ì «·ﬂ·„…  À·«À √·›« 
        // ≈‰ ·„  ﬂ‰ «·√·› «·À«·À… „ ÿ—›…
        if (substr_count($word, '«') >= 3) {
            return true;
        }
        
        // ≈‰ ﬂ«‰ „ƒ‰À  √‰ÌÀ ·›ŸÌ° „‰ ÂÌ » «¡ „—»Êÿ…
        // √Ê Â„“… √Ê √·› „ﬁ’Ê—…
        if (($word[$wordLen - 1] == '…' || $word[$wordLen - 1] == '¡' || 
             $word[$wordLen - 1] == 'Ï') && $wordLen >= 4) {
            return true;
        }

        // „ƒ‰À  √‰ÌÀ ·›ŸÌ°
        // „‰ ÂÌ »√·› Ê «¡ „› ÊÕ… - Ã„⁄ „ƒ‰À ”«·„
        if ($word[$wordLen - 1] == ' ' && $word[$wordLen - 2] == '«' && 
            $wordLen >= 5) {
            return true;
        }

        // started by Noon, before REH or LAM, or Noon, is a verb and not a noun
        if ($word[0] == '‰' && ($word[1] == '—' || 
            $word[1] == '·' || $word[1] == '‰')
            && $wordLen > 3) {
            return false;
        }
        
        // started by YEH, before some letters is a verb and not a noun
        // YEH,THAL,JEEM,HAH,KHAH,ZAIN,SHEEN,SAD,DAD,TAH,ZAH,GHAIN,KAF
        if ($word[0] == 'Ì' && (strpos('Ì–ÃÂŒ“‘’÷ÿŸ€ﬂ', $word[1]) !== false) && 
            $wordLen > 3) {
            return false;
        }
        
        // started by beh or meem, before BEH,FEH,MEEM is a noun and not a verb
        if (($word[0] == '»' || $word[0] == '„') && 
            ($word[1] == '»' || $word[1] == '›' || $word[1] == '„') && 
             $wordLen > 3) {
            return true;
        }
        
        // «·ﬂ·„«  «· Ì   ‰ ÂÌ »Ì«¡ Ê‰Ê‰
        // √Ê √·› Ê‰Ê‰ √Ê Ì«¡ Ê‰Ê‰
        //  ﬂÊ‰ √”„«¡ „« ·„  »œ√ »√Õœ Õ—Ê› «·„÷«—⁄… 
        if (preg_match('/^[^«Ì ‰]\S{2}[«ÊÌ]‰$/', $word)) {
            return true;
        }

        // ≈‰ ﬂ«‰ ⁄·Ï Ê“‰ «”„ «·¬·…
        // √Ê «”„ «·„ﬂ«‰ √Ê «”„ «·“„«‰
        if (preg_match('/^„\S{3}$/', $word) || 
        preg_match('/^„\S{2}«\S$/', $word) || 
            preg_match('/^„\S{3}…$/', $word) || 
            preg_match('/^\S{2}«\S$/', $word) || 
            preg_match('/^\S«\SÊ\S$/', $word) || 
            preg_match('/^\S{2}Ê\S$/', $word) || 
            preg_match('/^\S{2}Ì\S$/', $word) || 
            preg_match('/^„\S{2}Ê\S$/', $word) || 
            preg_match('/^„\S{2}Ì\S$/', $word) || 
            preg_match('/^\S{3}…$/', $word) || 
            preg_match('/^\S{2}«\S…$/', $word) || 
            preg_match('/^\S«\S{2}…$/', $word) || 
            preg_match('/^\S«\SÊ\S…$/', $word) || 
            preg_match('/^«\S{2}Ê\S…$/', $word) || 
            preg_match('/^«\S{2}Ì\S$/', $word) || 
            preg_match('/^«\S{3}$/', $word) || 
            preg_match('/^\S{3}Ï$/', $word) || 
            preg_match('/^\S{3}«¡$/', $word) || 
            preg_match('/^\S{3}«‰$/', $word) || 
            preg_match('/^„\S«\S{2}$/', $word) || 
            preg_match('/^„‰\S{3}$/', $word) || 
            preg_match('/^„ \S{3}$/', $word) || 
            preg_match('/^„” \S{3}$/', $word) || 
            preg_match('/^„\S \S{2}$/', $word) || 
            preg_match('/^„ \S«\S{2}$/', $word) || 
            preg_match('/^\S«\S{2}$/', $word)) {
            return true;
        }

        return false;
    }
    
    /**
     * Tag all words in a given Arabic string if they are nouns or not
     *      
     * @param string $str Arabic string you want to tag all its words
     *                    
     * @return array Two dimension array where item[i][0] represent the word i
     *               in the given string, and item[i][1] is 1 if that word is
     *               noun and 0 if it is not
     * @author Khaled Al-Sham'aa <khaled@ar-php.org>
     */
    public static function tagText($str)
    {
        $text     = array();
        $words    = explode(' ', $str);
        $prevWord = '';
        
        foreach ($words as $word) {
            if ($word == '') {
                continue;
            }

            if (self::isNoun($word, $prevWord)) {
                $text[] = array($word, 1);
            } else {
                $text[] = array($word, 0);
            }
            
            $prevWord = $word;
        }

        return $text;
    }
    
    /**
     * Highlighted all nouns in a given Arabic string
     *      
     * @param string $str   Arabic string you want to highlighted 
     *                      all its nouns
     * @param string $style Name of the CSS class you would like to apply
     *                    
     * @return string Arabic string in HTML format where all nouns highlighted
     * @author Khaled Al-Sham'aa <khaled@ar-php.org>
     */
    public static function highlightText($str, $style = null)
    {
        $html     = '';
        $prevTag  = 0;
        $prevWord = '';
        
        $taggedText = self::tagText($str);
        
        foreach ($taggedText as $wordTag) {
            list($word, $tag) = $wordTag;
            
            if ($prevTag == 1) {
                if (in_array($word, self::$particlePreNouns)) {
                    $prevWord = $word;
                    continue;
                }
                
                if ($tag == 0) {
                    $html .= "</span> \r\n";
                }
            } else {
                if ($tag == 1) {
                    $html .= " \r\n<span class=\"" . $style ."\">";
                }
            }
            
            $html .= ' ' . $prevWord . ' ' . $word;
            
            if ($prevWord != '') {
                $prevWord = '';
            }
            $prevTag = $tag;
        }
        
        if ($prevTag == 1) {
            $html .= "</span> \r\n";
        }
        
        return $html;
    }
}
