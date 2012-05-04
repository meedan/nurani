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
 * Class Name: Arabic Text ArStemmer Class
 *  
 * Filename: ArStemmer.class.php
 *  
 * Original  Author(s): Khaled Al-Sham'aa <khaled@ar-php.org>
 *  
 * Purpose:  Get stem of an Arabic word
 *  
 * ----------------------------------------------------------------------
 *  
 * Source: http://arabtechies.net/node/83
 * By: Taha Zerrouki <taha.zerrouki@gmail.com>
 *  
 * ----------------------------------------------------------------------
 *  
 * Arabic Word Stemmer Class
 *
 * PHP class to get stem of an Arabic word
 *
 * A stemmer is an automatic process in which morphological variants of terms 
 * are mapped to a single representative string called a stem. Arabic belongs 
 * to the Semitic family of languages which also includes Hebrew and Aramaic. 
 * Since morphological change in Arabic results from the addition of prefixes 
 * and infixes as well as suffixes, simple removal of suffixes is not as 
 * effective for Arabic as it is for English.
 * 
 * Arabic has much richer morphology than English. Arabic has two genders, 
 * feminine and masculine; three numbers, singular, dual, and plural; and three 
 * grammatical cases, nominative, genitive, and accusative. A noun has the 
 * nominative case when it is a subject; accusative when it is the object of a 
 * verb; and genitive when it is the object of a preposition. The form of an 
 * Arabic noun is determined by its gender, number, and grammatical case. The 
 * definitive nouns are formed by attaching the Arabic article "AL" to the 
 * immediate front of the nouns. Besides prefixes, a noun can also carry a 
 * suffix which is often a possessive pronoun. In Arabic, the conjunction word
 * "WA" (and) is often attached to the following word.
 *  
 * Like nouns, an Arabic adjective can also have many variants. When an 
 * adjective modifies a noun in a noun phrase, the adjective agrees with the 
 * noun in gender, number, case, and definiteness. Arabic verbs have two tenses: 
 * perfect and imperfect. Perfect tense denotes actions completed, while 
 * imperfect denotes uncompleted actions. The imperfect tense has four mood: 
 * indicative, subjective, jussive, and imperative. Arabic verbs in perfect 
 * tense consist of a stem and a subject marker. The subject marker indicates 
 * the person, gender, and number of the subject. The form of a verb in perfect 
 * tense can have subject marker and pronoun suffix. The form of a 
 * subject-marker is determined together by the person, gender, and number of 
 * the subject.
 * Example:
 * <code>
 *     include('./Arabic.php');
 *     $obj = new Arabic('ArStemmer');
 * 
 *     echo $obj->stem($word);
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
// $obj = new I18N\Arabic\ArStemmer();
// 
// use I18N\Arabic;
// $obj = new Arabic\ArStemmer();
//
// use I18N\Arabic\ArStemmer as Stemmer;
// $obj = new Stemmer();

/**
 * This PHP class get stem of an Arabic word
 *  
 * @category  I18N 
 * @package   Arabic
 * @author    Khaled Al-Sham'aa <khaled@ar-php.org>
 * @copyright 2006-2011 Khaled Al-Sham'aa
 *    
 * @license   LGPL <http://www.gnu.org/licenses/lgpl.txt>
 * @link      http://www.ar-php.org 
 */ 
class ArStemmer
{
    protected static $verb_pre  = 'وأسفلي';
    protected static $verb_post = 'ومكانيه';
    protected static $verb_may;

    protected static $verb_max_pre  = 4;
    protected static $verb_max_post = 6;
    protected static $verb_min_stem = 2;

    protected static $noun_pre  = 'ابفكلوأ';
    protected static $noun_post = 'اتةكمنهوي';
    protected static $noun_may;

    protected static $noun_max_pre  = 4;
    protected static $noun_max_post = 6;
    protected static $noun_min_stem = 2;

    /**
     * "stem" method input charset
     * @var String     
     */         
    public $stemOutput = 'utf-8';

    /**
     * "stem" method output charset
     * @var String     
     */         
    public $stemInput = 'utf-8';

    /**
     * Name of the textual "stem" method parameters 
     * @var Array     
     */         
    public $stemVars = array('word');
    
    /**
     * Loads initialize values
     */         
    public function __construct()
    {
        self::$verb_may = self::$verb_pre . self::$verb_post;
        self::$noun_may = self::$noun_pre . self::$noun_post;
    }
    
    /**
     * Get rough stem of the given Arabic word 
     *      
     * @param string $word Arabic word you would like to get its stem
     *                    
     * @return string Arabic stem of the word
     * @author Khaled Al-Sham'aa <khaled@ar-php.org>
     */
    public static function stem($word)
    {
        $nounStem = self::roughStem($word, self::$noun_may, self::$noun_pre, 
                                    self::$noun_post, self::$noun_max_pre, 
                                    self::$noun_max_post, self::$noun_min_stem);

        $verbStem = self::roughStem($word, self::$verb_may, self::$verb_pre, 
                                    self::$verb_post, self::$verb_max_pre, 
                                    self::$verb_max_post, self::$verb_min_stem);
        
        if (mb_strlen($nounStem, 'UTF-8') < mb_strlen($verbStem, 'UTF-8')) {
            $stem = $nounStem;
        } else {
            $stem = $verbStem;
        }
        
        return $stem;
    }
    
    /**
     * Get rough stem of the given Arabic word (under specific rules)
     *      
     * @param string  $word      Arabic word you would like to get its stem
     * @param string  $notChars  Arabic chars those can't be in postfix or prefix
     * @param string  $preChars  Arabic chars those may exists in the prefix
     * @param string  $postChars Arabic chars those may exists in the postfix
     * @param integer $maxPre    Max prefix length
     * @param integer $maxPost   Max postfix length
     * @param integer $minStem   Min stem length
     *
     * @return string Arabic stem of the word under giving rules
     * @author Khaled Al-Sham'aa <khaled@ar-php.org>
     */
    protected static function roughStem ($word, $notChars, $preChars, $postChars, 
                                         $maxPre, $maxPost, $minStem)
    {
        $right = -1;
        $left  = -1;
        $max   = mb_strlen($word, 'UTF-8');
        
        for ($i=0; $i < $max; $i++) {
            if (mb_strpos($notChars, mb_substr($word, $i, 1, 'UTF-8'), 0, 'UTF-8') === false) {
                if ($right == -1) {
                    $right = $i;
                }
                $left = $i;
            }
        }
        
        if ($right > $maxPre) {
            $right = $maxPre;
        }
        
        if ($max - $left - 1 > $maxPost) {
            $left = $max - $maxPost -1;
        }
        
        for ($i=0; $i < $right; $i++) {
            if (mb_strpos($preChars, mb_substr($word, $i, 1, 'UTF-8'), 0, 'UTF-8') === false) {
                $right = $i;
                break;
            }
        }
        
        for ($i=$max-1; $i>$left; $i--) {
            if (mb_strpos($postChars, mb_substr($word, $i, 1, 'UTF-8'), 0, 'UTF-8') === false) {
                $left = $i;
                break;
            }
        }

        if ($left - $right >= $minStem) {
            $stem = mb_substr($word, $right, $left-$right+1, 'UTF-8');
        } else {
            $stem = null;
        }

        return $stem;
    }
}
