<?php
/**
 * ----------------------------------------------------------------------
 *  
 * Copyright (c) 2006-2011 Khaled Al-Shamaa.
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
 * Class Name: PHP and Arabic Language
 *  
 * Filename:   Arabic.php
 *  
 * Original    Author(s): Khaled Al-Sham'aa <khaled.alshamaa@gmail.com>
 *  
 * Purpose:    Set of PHP classes developed to enhance Arabic web 
 *             applications by providing set of tools includes stem-based searching, 
 *             translitiration, soundex, Hijri calendar, charset detection and
 *             converter, spell numbers, keyboard language, Muslim prayer time, 
 *             auto-summarization, and more...
 *              
 * ----------------------------------------------------------------------
 *
 * @desc   Set of PHP classes developed to enhance Arabic web
 *         applications by providing set of tools includes stem-based searching, 
 *         translitiration, soundex, Hijri calendar, charset detection and
 *         converter, spell numbers, keyboard language, Muslim prayer time, 
 *         auto-summarization, and more...
 *          
 * @category  I18N 
 * @package   Arabic
 * @author    Khaled Al-Shamaa <khaled.alshamaa@gmail.com>
 * @copyright 2006-2011 Khaled Al-Shamaa
 *    
 * @license   LGPL <http://www.gnu.org/licenses/lgpl.txt>
 * @version   2.8 released in Apr 14, 2011
 * @link      http://www.ar-php.org
 */

// New in PHP V5.3: Namespaces
// namespace I18N\Arabic;

// error_reporting(E_STRICT);

/**
 * Core PHP and Arabic language class
 *  
 * @category  I18N 
 * @package   Arabic
 * @author    Khaled Al-Shamaa <khaled.alshamaa@gmail.com>
 * @copyright 2006-2011 Khaled Al-Shamaa
 *    
 * @license   LGPL <http://www.gnu.org/licenses/lgpl.txt>
 * @link      http://www.ar-php.org
 */  
class Arabic
{
    protected $inputCharset  = 'utf-8';
    protected $outputCharset = 'utf-8';
    protected $path;
    protected $useAutoload;
    protected $useException;
    protected $compatibleMode;
    
    protected $compatible = array('EnTransliteration'=>'Transliteration', 
                                  'ArTransliteration'=>'Transliteration',
                                  'a4_max_chars'=>'a4MaxChars',
                                  'a4_lines'=>'a4Lines',
                                  'swap_ea'=>'swapEa',
                                  'swap_ae'=>'swapAe');
    
    public $myObject;
    public $myClass;

    /**
     * Load selected library/Arabic class you would like to use its functionality
     *          
     * @param string  $library      [ArAutoSummarize|ArCharsetC|ArCharsetD|ArDate|
     *                              ArGender|ArGlyphs|ArIdentifier|ArKeySwap|
     *                              Numbers|ArQuery|ArSoundex|ArStrToTime|Mktime|
     *                              ArTransliteration|ArWordTag|EnTransliteration|
     *                              Salat|ArCompressStr|ArStandard|ArStemmer|
     *                              ArNormalise]
     * @param boolean $useAutoload  True to use Autoload (default is false)    
     * @param boolean $useException True to use Exception (default is false)    
     *                    
     * @desc Load selected library/class you would like to use its functionality 
     * @author Khaled Al-Shamaa <khaled.alshamaa@gmail.com>
     */
    public function __construct($library, $useAutoload=false, 
                                $useException=false, $compatibleMode=true)
    {
        $this->useAutoload    = $useAutoload;
        $this->useException   = $useException;
        $this->compatibleMode = $compatibleMode;

        if ($this->useAutoload) {
            spl_autoload_register('Arabic::autoload');
        }
        
        if ($this->useException) {
            set_error_handler('Arabic::myErrorHandler');
        }
        
        if ($library) {
            if ($this->compatibleMode && 
                array_key_exists($library, $this->compatible)) {
                
                $library = $this->compatible[$library];
            }

            $this->load($library);
        }
    }

    /**
     * Include file that include requested class
     * 
     * @param string $className Class name
     * 
     * @return null      
     * @author Khaled Al-Shamaa <khaled.alshamaa@gmail.com>
     */ 
    public static function autoload($className) 
    {
        include self::getClassFile($className);
    }

    /**
     * Error handler function
     * 
     * @param int    $errno   The level of the error raised
     * @param string $errstr  The error message
     * @param string $errfile The filename that the error was raised in
     * @param int    $errline The line number the error was raised at
     * 
     * @return boolean FALSE      
     * @author Khaled Al-Shamaa <khaled.alshamaa@gmail.com>
     */ 
    public static function myErrorHandler($errno, $errstr, $errfile, $errline)
    {
        if ($errfile == __FILE__ || 
            file_exists(dirname(__FILE__).DIRECTORY_SEPARATOR.'sub'.
                                          DIRECTORY_SEPARATOR.basename($errfile))) {
            $msg  = '<b>Arabic Class Exception:</b> ';
            $msg .= $errstr;
            $msg .= " in <b>$errfile</b>";
            $msg .= " on line <b>$errline</b><br />";
    
            throw new ArabicException($msg, $errno);
        }
        
        // If the function returns false then the normal error handler continues
        return false;
    }

    /**
     * Load selected Arabic library and create an instance of its class
     * 
     * @param string $library Library name
     * 
     * @return null      
     * @author Khaled Al-Shamaa <khaled.alshamaa@gmail.com>
     */ 
    public function load($library)
    {
        if ($this->compatibleMode && 
            array_key_exists($library, $this->compatible)) {
            
            $library = $this->compatible[$library];
        }

        $this->myClass = $library;

        if (!$this->useAutoload && !class_exists($this->myClass)) {
            require self::getClassFile($this->myClass); 
        }

        $this->myObject   = new $library();
        $this->{$library} = &$this->myObject;
    }
    
    /**
     * Magic method __call() allows to capture invocation of non existing methods. 
     * That way __call() can be used to implement user defined method handling that 
     * depends on the name of the actual method being called.
     * 
     * @method Call a method from loaded sub class and take care of needed 
     *         character set conversion for both input and output values.          
     * 
     * @param string $methodName Method name
     * @param array  $arguments  Array of arguments
     * 
     * @return The value returned from the __call() method will be returned to 
     *         the caller of the method.
     * @author Khaled Al-Shamaa <khaled.alshamaa@gmail.com>
     */                                  
    public function __call($methodName, $arguments)
    {
        if ($this->compatibleMode && 
            array_key_exists($methodName, $this->compatible)) {
            
            $methodName = $this->compatible[$methodName];
        }

        // Create an instance of the ReflectionMethod class
        $method = new ReflectionMethod($this->myClass, $methodName);
        
        $params     = array();
        $parameters = $method->getParameters();

        foreach ($parameters as $parameter) {
            $name  = $parameter->getName();
            $value = array_shift($arguments);
            
            if (is_null($value) && $parameter->isDefaultValueAvailable()) {
                $value = $parameter->getDefaultValue();
            }
            
            $params[$name] = $value;
        }

        $in  = "{$methodName}Input";
        $out = "{$methodName}Output";
        $var = "{$methodName}Vars";

        if (isset($this->myObject->$in)) {
            foreach ($this->myObject->$var as $argument) {
                $params[$argument] = $this->coreConvert($params[$argument], 
                                                        $this->getInputCharset(), 
                                                        $this->myObject->$in);
            }
        }

        $value = call_user_func_array(array(&$this->myObject, $methodName), $params);

        if (isset($this->myObject->$out)) {
            if (!is_array($value)) {
                $value = $this->coreConvert($value, 
                                            $this->myObject->$out, 
                                            $this->getOutputCharset());
            } else {
                if ($methodName == 'tagText') {
                    foreach ($value as $key=>$text) {
                        $value[$key][0] = $this->coreConvert($text[0], 
                                                      $this->myObject->$out, 
                                                      $this->getOutputCharset());
                    }
                }
            }
        }

        return $value;
    }

    /**
     * Garbage collection, release child objects directly
     *          
     * @author Khaled Al-Shamaa <khaled.alshamaa@gmail.com>
     */
    public function __destruct() 
    {
        $this->inputCharset  = null;
        $this->outputCharset = null;
        $this->path          = null;
        $this->myObject      = null;
        $this->myClass       = null;
    }

    /**
     * Set charset used in class input Arabic strings
     *          
     * @param string $charset Input charset [utf-8|windows-1256|iso-8859-6]
     *      
     * @return TRUE if success, or FALSE if fail
     * @author Khaled Al-Shamaa <khaled.alshamaa@gmail.com>
     */
    public function setInputCharset($charset)
    {
        $flag = true;
        
        $charset = strtolower($charset);
        
        if (in_array($charset, array('utf-8', 'windows-1256', 'iso-8859-6'))) {
            $this->inputCharset = $charset;
        } else {
            $flag = false;
        }
        
        return $flag;
    }
    
    /**
     * Set charset used in class output Arabic strings
     *          
     * @param string $charset Output charset [utf-8|windows-1256|iso-8859-6]
     *      
     * @return boolean TRUE if success, or FALSE if fail
     * @author Khaled Al-Shamaa <khaled.alshamaa@gmail.com>
     */
    public function setOutputCharset($charset)
    {
        $flag = true;
        
        $charset = strtolower($charset);
        
        if (in_array($charset, array('utf-8', 'windows-1256', 'iso-8859-6'))) {
            $this->outputCharset = $charset;
        } else {
            $flag = false;
        }
        
        return $flag;
    }

    /**
     * Get the charset used in the input Arabic strings
     *      
     * @return string return current setting for class input Arabic charset
     * @author Khaled Al-Shamaa <khaled.alshamaa@gmail.com>
     */
    public function getInputCharset()
    {
        return $this->inputCharset;
    }
    
    /**
     * Get the charset used in the output Arabic strings
     *         
     * @return string return current setting for class output Arabic charset
     * @author Khaled Al-Shamaa <khaled.alshamaa@gmail.com>
     */
    public function getOutputCharset()
    {
        return $this->outputCharset;
    }
    
    /**
     * Convert Arabic string from one charset to another
     *          
     * @param string $str           Original Arabic string that you would like
     *                              to convert
     * @param string $inputCharset  Input charset
     * @param string $outputCharset Output charset
     *      
     * @return string Converted Arabic string in defined charset
     * @author Khaled Al-Shamaa <khaled.alshamaa@gmail.com>
     */
    public function coreConvert($str, $inputCharset, $outputCharset)
    {
        if ($inputCharset != $outputCharset) {
            if ($inputCharset == 'windows-1256') {
                $inputCharset = 'cp1256';
            }
            
            if ($outputCharset == 'windows-1256') {
                $outputCharset = 'cp1256';
            }
            
            $convStr = iconv($inputCharset, "$outputCharset", $str);

            if ($convStr == '' && $str != '') {
                include_once self::getClassFile('ArCharsetC');

                $c = ArCharsetC::singleton();
                
                if ($inputCharset == 'cp1256') {
                    $convStr = $c->win2utf($str);
                } else {
                    $convStr = $c->utf2win($str);
                }
            }
        } else {
            $convStr = $str;
        }
        
        return $convStr;
    }

    /**
     * Convert Arabic string from one format to another
     *          
     * @param string $str           Arabic string in the format set by setInput
     *                              Charset
     * @param string $inputCharset  (optional) Input charset 
     *                              [utf-8|windows-1256|iso-8859-6]
     *                              default value is NULL (use set input charset)
     * @param string $outputCharset (optional) Output charset 
     *                              [utf-8|windows-1256|iso-8859-6]
     *                              default value is NULL (use set output charset)
     *                                  
     * @return string Arabic string in the format set by method setOutputCharset
     * @author Khaled Al-Shamaa <khaled.alshamaa@gmail.com>
     */
    public function convert($str, $inputCharset = null, $outputCharset = null)
    {
        if ($inputCharset == null) {
            $inputCharset = $this->inputCharset;
        }
        
        if ($outputCharset == null) {
            $outputCharset = $this->outputCharset;
        }
        
        $str = $this->coreConvert($str, $inputCharset, $outputCharset);

        return $str;
    }

    /**
     * Get sub class file path to be included (mapping between class name and 
     * file name/path become independent now)
     *          
     * @param string $class Sub class name
     *                                  
     * @return string Sub class file path
     * @author Khaled Al-Shamaa <khaled.alshamaa@gmail.com>
     */
    private static function getClassFile($class)
    {
        $dir  = dirname(__FILE__) . DIRECTORY_SEPARATOR . 'sub';
        $file = $dir . DIRECTORY_SEPARATOR . $class . '.class.php';

        return $file;
    }
}

/**
 * Arabic Exception class defined by extending the built-in Exception class.
 *  
 * @category  Text 
 * @package   Arabic
 * @author    Khaled Al-Shamaa <khaled.alshamaa@gmail.com>
 * @copyright 2009 Khaled Al-Shamaa
 *    
 * @license   LGPL <http://www.gnu.org/licenses/lgpl.txt>
 * @link      http://www.ar-php.org
 */  
class ArabicException extends Exception
{
    /**
     * Make sure everything is assigned properly
     * 
     * @param string $message Exception message
     * @param int    $code    User defined exception code            
     */         
    public function __construct($message, $code=0)
    {
        parent::__construct($message, $code);
    }
}
