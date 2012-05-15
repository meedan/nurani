<?php
/*
 * OneHourTranslation API Client Library for PHP Platform
 * Version 1.0
 * Copyright (c) 2010 OneHourTranslation(tm) Ltd. <info@onehourtranslation.com>
 */


if (!function_exists('curl_init')) {
  throw new Exception('OneHourTranslation needs the CURL PHP extension.');
}
if (!function_exists('json_decode')) {
  throw new Exception('OneHourTranslation needs the JSON PHP extension.');
}

define('OHT_API_ACCOUNT_ID' , '269'); //demo account
define('OHT_API_SECRET_KEY' , '5a68561984276108fa42d7cffbbf91a5'); //demo account
define('OHT_API_SANDBOX' , true);

class OHTAPI_Exception extends Exception{
	
	protected 
		$httpCode ,
		$statusCode ,
		$statusMessage
	;
	
	function __construct($http_code , $status_code , $status_message){
		parent::__construct(sprintf("#%d %s (HTTP %d)" , $status_code , $status_message , $http_code ));
		$this->setHttpCode($http_code);
		$this->setStatusCode($status_code);
		$this->setStatusMessage($status_message);
		
	}
	

	/**
	 * 
	 * @return 
	 */
	public function getHttpCode()
	{
	    return $this->httpCode;
	}

	/**
	 * 
	 * @param $httpCode
	 */
	public function setHttpCode($httpCode)
	{
	    $this->httpCode = $httpCode;
	}

	/**
	 * 
	 * @return 
	 */
	public function getStatusCode()
	{
	    return $this->statusCode;
	}

	/**
	 * 
	 * @param $statusCode
	 */
	public function setStatusCode($statusCode)
	{
	    $this->statusCode = $statusCode;
	}

	/**
	 * 
	 * @return 
	 */
	public function getStatusMessage()
	{
	    return $this->statusMessage;
	}

	/**
	 * 
	 * @param $statusMessage
	 */
	public function setStatusMessage($statusMessage)
	{
	    $this->statusMessage = $statusMessage;
	}
	
	function __toString(){
		return $this->getMessage();
	}
}

class OHTAPI {
	/**
	 * @var string
	 */
	static $account_id ;
	
	/**
	 * @var string
	 */
	static $secret_key;
	
	/**
	 * @var boolean
	 */
	static $sandbox;
	
	/**
	 * @var OHTAPI
	 */
	protected static $instance = NULL;
	
	const 
		VERSION='1.0b' ,
		OHT_PRODUCTION_URL='https://www.onehourtranslation.com/api/1' ,
		OHT_SANDBOX_URL='https://sandbox.onehourtranslation.com/api/1'
		
	;
	
	
	
	/**
	 * @var string
	 */
	protected $_account_id ;
	/**
	 * @var string
	 */
	protected $_secret_key;
	
	/**
	 * @var boolean
	 */
	protected $_sandbox;
	
	/**
	 * Performes preliminary configuration on the OHTAPI class.<br />Make sure to run it before calling OHTAPI::instance() for the first time
	 * 
	 * @param array $conf - contains the following parameters:<br />
	 * 	<ol>
	 * 	<li>'account_id' - Your OHT account ID</li>
	 *  <li>'secret_key' - Your OHT secret API key</li>
	 *  <li>'sandbox' - (boolean) Use OHT sandbox</li>
	 *  </ol>
	 * 
	 */
	static public function config($conf=array()){
		self::$account_id = (!empty($conf['account_id'])) ? $conf['account_id'] : OHT_API_ACCOUNT_ID;
		self::$secret_key = (!empty($conf['secret_key'])) ? $conf['secret_key'] : OHT_API_SECRET_KEY;
		self::$sandbox = (!empty($conf['sandbox'])) ? $conf['sandbox'] : OHT_API_SANDBOX;
		
	}

	/**
	 * Fetch OHTAPI Instance. Make sure to run this right after running config()
	 * 
	 * @return OHTAPI
	 */
	static public function instance(){
		if (!self::$instance){
			$className = __CLASS__;
			self::$instance = new $className (self::$account_id , self::$secret_key , self::$sandbox);
		}
		return self::$instance;
	} 
	
	/**
	 * @param $account_id
	 * @param $secret_key
	 * @param $sandbox boolean true to use OHT sandbox 
	 */
	public function __construct($account_id = OHT_API_ACCOUNT_ID , $secret_key = OHT_API_SECRET_KEY , $sandbox=OHT_API_SANDBOX){
		$this->setAccountId( $account_id );
		$this->setSecretKey($secret_key);
		$this->setSandbox( $sandbox );
	}
	
	/**
	 * Create a new Translation Project
	 * @param string $source
	 * @param string $target
	 * @param string $content
	 * @param integer $word_count (optional)
	 * @param string $notes (optional)
	 * @param string $callback_url (optional)
	 * @param array $params (optional)
	 * @return stdClass response object
	 */
	public function newProject($source , $target , $content , $word_count=0 , $notes='' , $callback_url='', $params=array()){
		$url = '/project/new/';
		$method = 'post';
		$params['source'] = $source;
		$params['target'] = $target;
		$params['content'] = $content;
		$params['word_count'] = $word_count;
		$params['notes'] = $notes;
		$params['callback_url'] = $callback_url;
		
		return $this->request($url , $method , $params);
		
	}
	
	/**
	 * Fetch project details by project id
	 * 
	 * @param integer $project_id
	 * @return stdClass response object
	 */
	public function getProjectDetails($project_id){
		$url = "/project/{$project_id}/details/";
		$method='get';
		return $this->request($url , $method);
	}
	/**
	 * Fetch project translated text and source text by project id
	 * 
	 * @param integer $project_id
	 * @return stdClass response object
	 */
	public function getProjectContents($project_id){
		$url = "/project/{$project_id}/contents/";
		$method='get';
		$result = $this->request($url , $method);
		if (!empty($result->original_content)){
			$result->original_content = base64_decode($result->original_content);
		}
		if (!empty($result->translated_content)){
			$result->translated_content = base64_decode($result->translated_content);
		}
		return $result;
	}
	
	/**
	 * Fetch account details and credits balance
	 * 
	 * @return stdClass response object
	 */
	public function getAccountDetails(){
		$url = "/account/details/";
		$method='get';
		return $this->request($url , $method);
	}
	
	protected function request($requestURL , $method='get' , $params=array()){
		$ch = curl_init();
		$url = $this->getBaseURL() . $requestURL;
		$opts = array();
		$params['account_id'] = $this->getAccountId();
		$params['secret_key'] = $this->getSecretKey();
		
		if ($method=='post'){
			$opts[CURLOPT_URL] = $url;
			$opts[CURLOPT_POSTFIELDS] = $params;
		}else{
			$opts[CURLOPT_URL] = $url. '?' . http_build_query($params, '', '&');
		}
		$opts[CURLOPT_RETURNTRANSFER] = TRUE;
		//$opts[CURLOPT_HEADER] = TRUE;
		if (strstr(strtoupper(PHP_OS) , 'WIN')){
			$opts[CURLOPT_SSL_VERIFYPEER] = FALSE;
		}

		curl_setopt_array($ch , $opts);
		$result = curl_exec($ch);
		
		
		$http_code = curl_getinfo($ch,CURLINFO_HTTP_CODE);
		
		curl_close($ch);
		
		if ($http_code==404){
			throw new Exception('OneHourTranslation could not be reached.');
		}else{
			$obj = json_decode($result);
			if (!is_object($obj)){
				throw new Exception('OneHourTranslation response was malformed.');
			}elseif($http_code != 200){
				throw new OHTAPI_Exception($http_code , $obj->status_code , $obj->status_msg);
			}else{
				return $obj;
			}
			
		}
	}
	

	/**
	 * 
	 * @return 
	 */
	public function getAccountId()
	{
	    return $this->_account_id;
	}

	/**
	 * 
	 * @param $_account_id
	 */
	public function setAccountId($_account_id)
	{
	    $this->_account_id = $_account_id;
	}

	/**
	 * 
	 * @return 
	 */
	public function getSecretKey()
	{
	    return $this->_secret_key;
	}

	/**
	 * 
	 * @param $_secret_key
	 */
	public function setSecretKey($_secret_key)
	{
	    $this->_secret_key = $_secret_key;
	}

	/**
	 * 
	 * @return 
	 */
	public function getSandbox()
	{
	    return (boolean)$this->_sandbox;
	}

	/**
	 * 
	 * @param $_sandbox
	 */
	public function setSandbox($_sandbox)
	{
	    $this->_sandbox = (boolean)$_sandbox;
	}
	
	public function getBaseURL(){
		if ($this->getSandbox()){
			return self::OHT_SANDBOX_URL;
		}
		return self::OHT_PRODUCTION_URL;
	}
}


?>