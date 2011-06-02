<?php

/**
 * Implementation of hook_strongarm().
 */
function nurani_general_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'admin_theme';
  $strongarm->value = 'garland';

  $export['admin_theme'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'agreement_checkbox_text';
  $strongarm->value = 'I agree.';

  $export['agreement_checkbox_text'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'agreement_enforceable_pages';
  $strongarm->value = '';

  $export['agreement_enforceable_pages'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'agreement_frequency';
  $strongarm->value = '0';

  $export['agreement_frequency'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'agreement_message_failure';
  $strongarm->value = 'You must accept our agreement to continue.';

  $export['agreement_message_failure'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'agreement_message_success';
  $strongarm->value = 'Thank you for accepting our agreement.';

  $export['agreement_message_success'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'agreement_page_title';
  $strongarm->value = 'Privacy';

  $export['agreement_page_title'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'agreement_page_url';
  $strongarm->value = 'privacy';

  $export['agreement_page_url'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'agreement_page_visibility_pages';
  $strongarm->value = '';

  $export['agreement_page_visibility_pages'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'agreement_page_visibility_settings';
  $strongarm->value = '0';

  $export['agreement_page_visibility_settings'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'agreement_role';
  $strongarm->value = '2';

  $export['agreement_role'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'agreement_submit_text';
  $strongarm->value = 'Submit';

  $export['agreement_submit_text'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'agreement_success_destination';
  $strongarm->value = '';

  $export['agreement_success_destination'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'agreement_text';
  $strongarm->value = '<p>Nurani.org is designed to allow you to take part in dialogues about your beliefs and opinions, so it is very important that you read and agree to the following terms which relate to how we store personal data that you submit to the platform. The terms form part of the contract that you agree to on registering with this website, but are also here to reassure you that the Cambridge Inter-faith Programme and Meedan, Inc. (the Service Providers) have a strict data policy in place to protect your personal data.</p>
<p>We (The Service Providers) reserve the right to modify the information contained herein at anytime. If we do make changes to our privacy policy that affect your personal data, we will notify You (the Registered User) using the email that you have given us. This site and all information and materials on it are provided to you "as is" without warranty of any kind. Ÿour use of this site, or your provision to us of any personal information constitutes your agreement to these terms; do not use the site or provide information if you do not agree with all of the terms.</p>
<p>Information You Provide</p>
<p>1. Registration</p>
<p>When you register for an account you will be asked to give your name, email address and password.  You can update this information at any time. Only you will be able to see your password. Your email address will be viewable by system administrators representing The Service Providers and moderators granted permission to manage dialogues on Nurani.org by CIP. We will use your email address to communicate important notifications about this privacy policy, requests for disclosure by Third Parties, or other notifications that relate to your use of Nurani.org.   Moderators may use your email address to help manage dialogues on Nurani.org and to warn you if your behaviour is deemed inappropriate.  You can also opt to receive notifications of new content that will be delivered automatically to your email address.</p>
<p>2. Profile Information</p>
<p>When you register for an account you will have the option to build a profile. This profile may include, but is not limited to, information such as your personal names, location, education, professional experience and affiliations. You will be able to edit and remove this information at any time, and to control whether it is viewable publicly or only by other users of Nurani.org. We encourage you to supply this information to help other users learn more about you. We think this will help you to have more productive dialogues with other users.</p>
<p>3. Posting</p>
<p>On Nurani.org you can post three kinds of content: texts, glossary terms, and discussion comments.  We intend for all texts and glossary terms added to Nurani.org to be publicly viewable.  Discussions, however, depend on the privacy settings of the group to which you were invited by a moderator. A discussion on Nurani may have one of three settings: private to the members of the group, viewable by all groups on Nurani, or public on the web. Identification of all contributed content may include, but is not limited to, display of your account name. All content may be retained for restorative, archival, or research purposes by The Service Providers. Editing or deleting content may alter the displayed state of the content, but will not permanently delete the content from the website.</p>
<p>4. Normal Browsing</p>
<p>The Service Providers collect certain information about your browsing habits, including your IP address, URL request, browser type, and date and time of your request. This information is gathered on an aggregate basis only. For example, we track which pages are most popular among visitors as a whole.  We do not track information on which pages an individual user visits. We do not collect any other information without your knowledge and permission.</p>
<p>We analyze traffic to Nurani.org  in various ways, including using a service called Google Analytics. (Google Analytics is subject to the privacy policy of Google, Inc., which you can find at the following url: <a href="http://www.google.co.uk/intl/en/privacy/privacy-policy.html">http://www.google.co.uk/intl/en/privacy/privacy-policy.html</a>) Unless you affirmatively provide additional information, we do not collect or store personally identifiable information such as mailing address, phone number, or social security number.<br />
Storage</p>
<p>By agreeing to these terms you consent that personal data collected on Nurani.org may be transferred to, and stored at, a destination outside the European Economic Area (“EEA”). It may also be processed by staff operating outside the EEA who work for the Cambridge Inter-faith Programme (CIP) or for Meedan, Inc. By submitting your personal data, you agree to this transfer, storing or processing.</p>
<p>Security</p>
<p>The Service Providers will take all reasonable steps to ensure that your data is treated securely and in accordance with the European Commission’s contractual requirements for the transfer of personal data to processors outside the EU. In order to prevent against accidental or unlawful destruction or accidental loss, alteration, or unauthorised disclosure or access, The Service Providers have put in place strict technical and managerial procedures to safeguard and secure the information processed by Nurani.org.  If you wish to review these measures click here.</p>
<p>Disclosure of Information</p>
<p>Available log records, account information, and all data stored on our servers may be accessed by system administrators representing The Service Providers.</p>
<p>In the event that we are required by law (including a court order) to disclose the information you submit, we will provide you with notice that a request for your information has been made so that you may object to the disclosure. We will send this notice by email to the address you have given us.</p>
<p>The Service Providers will take all reasonable measures to notify you in advance of any planned transfer of your personal data to a Third Party or Subprocessor so that you can opt to remove your data from this transfer if you wish. In the unlikely event of unauthorised access to your data, The Service Providers undertake to inform you promptly.</p>
<p>If you have any questions regarding the personal data The Service Providers hold about you, you can contact Meedan’s Data Protection Manager at the following address:</p>
<p><a href="mailto:privacy@meedan.net">privacy@meedan.net</a></p>
<p>Meedan, Inc.<br />
972 Mission Street,<br />
San Francisco<br />
California 94310<br />
USA<br />
Cookies<br />
The Service Providers may use session cookies when you visit our website while your browser is open, or while you are logged into Nurani.org. To facilitate registration and login functions, The Service Providers may use cookies to recognise when you return to the website. If you do not logout of your account, these cookies keep track of your username and password so that you do not have to resubmit the information to log into your account. If others will be using your computer, you should log out of your account so that your login information is cleared.</p>
<p>These Terms are licensed under CC <a href="http://www.citmedialaw.org/">http://www.citmedialaw.org/</a>)</p>
';

  $export['agreement_text'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_annotation';
  $strongarm->value = '0';

  $export['comment_annotation'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_annotation';
  $strongarm->value = 0;

  $export['comment_anonymous_annotation'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_comment';
  $strongarm->value = 0;

  $export['comment_anonymous_comment'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_discussion';
  $strongarm->value = 0;

  $export['comment_anonymous_discussion'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_page';
  $strongarm->value = 0;

  $export['comment_anonymous_page'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_profile';
  $strongarm->value = 0;

  $export['comment_anonymous_profile'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_term';
  $strongarm->value = 0;

  $export['comment_anonymous_term'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_text';
  $strongarm->value = 0;

  $export['comment_anonymous_text'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_comment';
  $strongarm->value = 0;

  $export['comment_comment'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_controls_annotation';
  $strongarm->value = '3';

  $export['comment_controls_annotation'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_controls_comment';
  $strongarm->value = '3';

  $export['comment_controls_comment'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_controls_discussion';
  $strongarm->value = '3';

  $export['comment_controls_discussion'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_controls_page';
  $strongarm->value = '3';

  $export['comment_controls_page'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_controls_profile';
  $strongarm->value = '3';

  $export['comment_controls_profile'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_controls_term';
  $strongarm->value = '3';

  $export['comment_controls_term'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_controls_text';
  $strongarm->value = '3';

  $export['comment_controls_text'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_annotation';
  $strongarm->value = '4';

  $export['comment_default_mode_annotation'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_comment';
  $strongarm->value = '4';

  $export['comment_default_mode_comment'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_discussion';
  $strongarm->value = '4';

  $export['comment_default_mode_discussion'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_page';
  $strongarm->value = '4';

  $export['comment_default_mode_page'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_profile';
  $strongarm->value = '4';

  $export['comment_default_mode_profile'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_term';
  $strongarm->value = '4';

  $export['comment_default_mode_term'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_text';
  $strongarm->value = '4';

  $export['comment_default_mode_text'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_order_annotation';
  $strongarm->value = '1';

  $export['comment_default_order_annotation'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_order_comment';
  $strongarm->value = '1';

  $export['comment_default_order_comment'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_order_discussion';
  $strongarm->value = '1';

  $export['comment_default_order_discussion'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_order_page';
  $strongarm->value = '1';

  $export['comment_default_order_page'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_order_profile';
  $strongarm->value = '1';

  $export['comment_default_order_profile'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_order_term';
  $strongarm->value = '1';

  $export['comment_default_order_term'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_order_text';
  $strongarm->value = '1';

  $export['comment_default_order_text'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_annotation';
  $strongarm->value = '50';

  $export['comment_default_per_page_annotation'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_comment';
  $strongarm->value = '50';

  $export['comment_default_per_page_comment'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_discussion';
  $strongarm->value = '50';

  $export['comment_default_per_page_discussion'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_page';
  $strongarm->value = '50';

  $export['comment_default_per_page_page'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_profile';
  $strongarm->value = '50';

  $export['comment_default_per_page_profile'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_term';
  $strongarm->value = '50';

  $export['comment_default_per_page_term'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_text';
  $strongarm->value = '50';

  $export['comment_default_per_page_text'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_discussion';
  $strongarm->value = 0;

  $export['comment_discussion'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_annotation';
  $strongarm->value = '0';

  $export['comment_form_location_annotation'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_comment';
  $strongarm->value = '0';

  $export['comment_form_location_comment'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_discussion';
  $strongarm->value = '1';

  $export['comment_form_location_discussion'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_page';
  $strongarm->value = '0';

  $export['comment_form_location_page'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_profile';
  $strongarm->value = '0';

  $export['comment_form_location_profile'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_term';
  $strongarm->value = '1';

  $export['comment_form_location_term'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_text';
  $strongarm->value = '0';

  $export['comment_form_location_text'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_page';
  $strongarm->value = '0';

  $export['comment_page'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_annotation';
  $strongarm->value = '1';

  $export['comment_preview_annotation'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_comment';
  $strongarm->value = '1';

  $export['comment_preview_comment'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_discussion';
  $strongarm->value = '0';

  $export['comment_preview_discussion'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_page';
  $strongarm->value = '1';

  $export['comment_preview_page'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_profile';
  $strongarm->value = '1';

  $export['comment_preview_profile'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_term';
  $strongarm->value = '0';

  $export['comment_preview_term'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_text';
  $strongarm->value = '1';

  $export['comment_preview_text'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_profile';
  $strongarm->value = '0';

  $export['comment_profile'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_annotation';
  $strongarm->value = '1';

  $export['comment_subject_field_annotation'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_comment';
  $strongarm->value = '1';

  $export['comment_subject_field_comment'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_discussion';
  $strongarm->value = '0';

  $export['comment_subject_field_discussion'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_page';
  $strongarm->value = '1';

  $export['comment_subject_field_page'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_profile';
  $strongarm->value = '1';

  $export['comment_subject_field_profile'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_term';
  $strongarm->value = '0';

  $export['comment_subject_field_term'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_text';
  $strongarm->value = '1';

  $export['comment_subject_field_text'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_term';
  $strongarm->value = 0;

  $export['comment_term'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_text';
  $strongarm->value = '0';

  $export['comment_text'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_discussion';
  $strongarm->value = array(
    'title' => '-5',
    'body_field' => '-3',
    'revision_information' => '4',
    'author' => '5',
    'options' => '6',
    'comment_settings' => '8',
    'language' => '3',
    'translation' => '9',
    'menu' => '-4',
    'path' => '7',
  );

  $export['content_extra_weights_discussion'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_profile';
  $strongarm->value = array(
    'title' => '-5',
    'body_field' => '8',
    'revision_information' => '10',
    'author' => '11',
    'options' => '12',
    'comment_settings' => '14',
    'language' => '9',
    'translation' => '15',
    'menu' => '7',
    'path' => '13',
  );

  $export['content_extra_weights_profile'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_term';
  $strongarm->value = array(
    'title' => '-5',
    'revision_information' => '2',
    'author' => '3',
    'options' => '4',
    'comment_settings' => '6',
    'menu' => '-4',
    'path' => '5',
  );

  $export['content_extra_weights_term'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_text';
  $strongarm->value = array(
    'title' => '-5',
    'body_field' => '-1',
    'revision_information' => '1',
    'author' => '2',
    'options' => '3',
    'comment_settings' => '5',
    'language' => '0',
    'translation' => '6',
    'menu' => '-4',
    'path' => '4',
  );

  $export['content_extra_weights_text'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_profile_profile';
  $strongarm->value = array();

  $export['content_profile_profile'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_profile_use_annotation';
  $strongarm->value = 0;

  $export['content_profile_use_annotation'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_profile_use_comment';
  $strongarm->value = 0;

  $export['content_profile_use_comment'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_profile_use_discussion';
  $strongarm->value = 0;

  $export['content_profile_use_discussion'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_profile_use_page';
  $strongarm->value = 0;

  $export['content_profile_use_page'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_profile_use_profile';
  $strongarm->value = 1;

  $export['content_profile_use_profile'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_profile_use_term';
  $strongarm->value = 0;

  $export['content_profile_use_term'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_profile_use_text';
  $strongarm->value = 0;

  $export['content_profile_use_text'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ds_all_build_modes';
  $strongarm->value = array(
    'nd' => array(
      'full' => array(
        'weight' => -1,
        'title' => 'Full node',
      ),
      'teaser' => array(
        'weight' => 1,
        'title' => 'Teaser',
      ),
      'sticky' => array(
        'weight' => 2,
        'title' => 'Sticky',
      ),
      4 => array(
        'weight' => 3,
        'title' => 'RSS',
      ),
      2 => array(
        'weight' => 13,
        'title' => 'Search Index',
      ),
      3 => array(
        'weight' => 14,
        'title' => 'Search Result',
      ),
      'token' => array(
        'weight' => 17,
        'title' => 'Token',
      ),
      'text_summary' => array(
        'weight' => 10,
        'title' => 'Text summary',
        'build modes' => array(
          'text_summary' => array(
            'title' => 'Text summary',
          ),
        ),
      ),
      'discussion_participants' => array(
        'weight' => 11,
        'title' => 'Discussion participants',
        'build modes' => array(
          'discussion_participants' => array(
            'title' => 'Discussion participants',
          ),
        ),
      ),
    ),
  );

  $export['ds_all_build_modes'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ds_build_mode_4';
  $strongarm->value = 'not_all';

  $export['ds_build_mode_4'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_hide_translation_links';
  $strongarm->value = 0;

  $export['i18n_hide_translation_links'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_lock_node_annotation';
  $strongarm->value = 1;

  $export['i18n_lock_node_annotation'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_lock_node_comment';
  $strongarm->value = 1;

  $export['i18n_lock_node_comment'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_lock_node_discussion';
  $strongarm->value = 1;

  $export['i18n_lock_node_discussion'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_lock_node_page';
  $strongarm->value = 1;

  $export['i18n_lock_node_page'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_lock_node_profile';
  $strongarm->value = 1;

  $export['i18n_lock_node_profile'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_lock_node_story';
  $strongarm->value = 1;

  $export['i18n_lock_node_story'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_lock_node_term';
  $strongarm->value = 1;

  $export['i18n_lock_node_term'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_lock_node_text';
  $strongarm->value = 1;

  $export['i18n_lock_node_text'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_newnode_current_annotation';
  $strongarm->value = 1;

  $export['i18n_newnode_current_annotation'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_newnode_current_comment';
  $strongarm->value = 1;

  $export['i18n_newnode_current_comment'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_newnode_current_discussion';
  $strongarm->value = 1;

  $export['i18n_newnode_current_discussion'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_newnode_current_page';
  $strongarm->value = 1;

  $export['i18n_newnode_current_page'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_newnode_current_profile';
  $strongarm->value = 1;

  $export['i18n_newnode_current_profile'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_newnode_current_story';
  $strongarm->value = 1;

  $export['i18n_newnode_current_story'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_newnode_current_term';
  $strongarm->value = 1;

  $export['i18n_newnode_current_term'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_newnode_current_text';
  $strongarm->value = 1;

  $export['i18n_newnode_current_text'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_node_annotation';
  $strongarm->value = '1';

  $export['i18n_node_annotation'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_node_comment';
  $strongarm->value = '1';

  $export['i18n_node_comment'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_node_discussion';
  $strongarm->value = '1';

  $export['i18n_node_discussion'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_node_page';
  $strongarm->value = '1';

  $export['i18n_node_page'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_node_profile';
  $strongarm->value = '1';

  $export['i18n_node_profile'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_node_story';
  $strongarm->value = '1';

  $export['i18n_node_story'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_node_term';
  $strongarm->value = '1';

  $export['i18n_node_term'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_node_text';
  $strongarm->value = '1';

  $export['i18n_node_text'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_required_node_annotation';
  $strongarm->value = 1;

  $export['i18n_required_node_annotation'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_required_node_comment';
  $strongarm->value = 1;

  $export['i18n_required_node_comment'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_required_node_discussion';
  $strongarm->value = 1;

  $export['i18n_required_node_discussion'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_required_node_page';
  $strongarm->value = 1;

  $export['i18n_required_node_page'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_required_node_profile';
  $strongarm->value = 1;

  $export['i18n_required_node_profile'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_required_node_story';
  $strongarm->value = 1;

  $export['i18n_required_node_story'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_required_node_term';
  $strongarm->value = 1;

  $export['i18n_required_node_term'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_required_node_text';
  $strongarm->value = 1;

  $export['i18n_required_node_text'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_selection_mode';
  $strongarm->value = 'off';

  $export['i18n_selection_mode'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18n_translation_switch';
  $strongarm->value = 1;

  $export['i18n_translation_switch'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'i18ntaxonomy_vocabulary';
  $strongarm->value = array(
    1 => '1',
  );

  $export['i18ntaxonomy_vocabulary'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'icl_content_books_to_update';
  $strongarm->value = array();

  $export['icl_content_books_to_update'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'icl_content_dashboard_hide_legend';
  $strongarm->value = array(
    1 => FALSE,
  );

  $export['icl_content_dashboard_hide_legend'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'icl_content_delete_options';
  $strongarm->value = 'automatic';

  $export['icl_content_delete_options'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'icl_content_menu_options';
  $strongarm->value = 'menu_original';

  $export['icl_content_menu_options'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'icl_content_node_type_fields';
  $strongarm->value = array(
    'story' => array(
      'title' => 'title',
      'body' => 'body',
    ),
    'text' => array(
      'title' => 'title',
      'body' => 'body',
    ),
    'term' => array(),
    'discussion' => array(
      'title' => 'title',
      'body' => 'body',
    ),
    'page' => array(
      'title' => 'title',
      'body' => 'body',
    ),
    'profile' => array(),
    'comment' => array(
      'body' => 'body',
    ),
    'annotation' => array(
      'body' => 'body',
    ),
  );

  $export['icl_content_node_type_fields'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'icl_content_num_items_to_display';
  $strongarm->value = '50';

  $export['icl_content_num_items_to_display'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'icl_content_publish_options';
  $strongarm->value = 'publish_translations';

  $export['icl_content_publish_options'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'icl_content_skip_per_node';
  $strongarm->value = array(
    1 => -1,
    3 => -1,
    6 => -1,
    7 => -1,
    8 => -1,
    14 => -1,
    16 => -1,
    17 => -1,
    18 => -1,
    20 => -1,
    22 => -1,
    5 => -1,
  );

  $export['icl_content_skip_per_node'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'icl_content_update_links_options';
  $strongarm->value = 'update_links';

  $export['icl_content_update_links_options'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'icl_menus_to_sync';
  $strongarm->value = array();

  $export['icl_menus_to_sync'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'icl_status_check_done';
  $strongarm->value = TRUE;

  $export['icl_status_check_done'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'icl_translate_notifications';
  $strongarm->value = array(
    'translator_new_job' => '1',
    'manager_job_completed' => '1',
    'translator_self_removed_from_job' => '1',
    'settings' => array(
      'show_in_reminders' => '1',
      'delete_old_messages_period' => '30',
    ),
  );

  $export['icl_translate_notifications'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'icl_translate_xliffed';
  $strongarm->value = array();

  $export['icl_translate_xliffed'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'icl_unassigned_jobs';
  $strongarm->value = array();

  $export['icl_unassigned_jobs'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_annotation';
  $strongarm->value = '2';

  $export['language_content_type_annotation'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_comment';
  $strongarm->value = '2';

  $export['language_content_type_comment'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_discussion';
  $strongarm->value = '2';

  $export['language_content_type_discussion'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_page';
  $strongarm->value = '2';

  $export['language_content_type_page'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_profile';
  $strongarm->value = '2';

  $export['language_content_type_profile'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_term';
  $strongarm->value = '1';

  $export['language_content_type_term'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_text';
  $strongarm->value = '2';

  $export['language_content_type_text'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_count';
  $strongarm->value = 2;

  $export['language_count'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'nd_build_modes';
  $strongarm->value = array(
    'text_summary' => 'Text summary',
    'discussion_participants' => 'Discussion participants',
  );

  $export['nd_build_modes'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'nd_buildmodes_exclude';
  $strongarm->value = array(
    'annotation' => array(
      'ds_block_all' => 0,
      'full' => 0,
      'teaser' => 0,
      'sticky' => 0,
      4 => 0,
      'token' => 0,
      'text_summary' => 1,
      'discussion_participants' => 1,
    ),
    'comment' => array(
      'ds_block_all' => 0,
      'full' => 0,
      'teaser' => 0,
      'sticky' => 0,
      4 => 0,
      'token' => 0,
      'text_summary' => 1,
      'discussion_participants' => 1,
    ),
    'discussion' => array(
      'ds_block_all' => 0,
      'full' => 0,
      'teaser' => 0,
      'sticky' => 0,
      4 => 0,
      'token' => 0,
      'text_summary' => 1,
      'discussion_participants' => 0,
    ),
    'page' => array(
      'ds_block_all' => 0,
      'full' => 0,
      'teaser' => 0,
      'sticky' => 0,
      4 => 0,
      'token' => 0,
      'text_summary' => 1,
      'discussion_participants' => 1,
    ),
    'profile' => array(
      'ds_block_all' => 0,
      'full' => 0,
      'teaser' => 0,
      'sticky' => 0,
      4 => 0,
      'token' => 0,
      'text_summary' => 1,
      'discussion_participants' => 1,
    ),
    'term' => array(
      'ds_block_all' => 0,
      'full' => 0,
      'teaser' => 0,
      'sticky' => 0,
      4 => 0,
      'token' => 0,
      'text_summary' => 1,
      'discussion_participants' => 1,
    ),
    'text' => array(
      'ds_block_all' => 0,
      'full' => 0,
      'teaser' => 0,
      'sticky' => 0,
      4 => 0,
      'token' => 0,
      'text_summary' => 0,
      'discussion_participants' => 1,
    ),
  );

  $export['nd_buildmodes_exclude'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'nd_display_settings_comment';
  $strongarm->value = array(
    'full' => array(
      'fields' => array(
        'title' => array(
          'region' => 'disabled',
          'weight' => '-94',
          'format' => 'nd_title_h1_nolink',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
        'author' => array(
          'region' => 'header',
          'weight' => '-100',
          'format' => 'ds_author_nolink',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
        'links' => array(
          'region' => 'footer',
          'weight' => '-96',
          'format' => '',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
        'read_more' => array(
          'region' => 'disabled',
          'weight' => '-95',
          'format' => 'ds_eval_code',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
        'post_date' => array(
          'region' => 'header',
          'weight' => '-99',
          'format' => 'nd_post_date_long',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
        'body' => array(
          'region' => 'middle',
          'weight' => '-98',
          'format' => 'nd_bodyfield',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
        'translation_status' => array(
          'region' => 'middle',
          'weight' => '-97',
          'format' => 'ds_eval_code',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
      ),
      'status' => 1,
      'region_styles' => array(
        'header' => '',
        'left' => '',
        'middle' => '',
        'right' => '',
        'footer' => '',
      ),
    ),
  );

  $export['nd_display_settings_comment'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'nd_display_settings_discussion';
  $strongarm->value = array(
    'discussion_participants' => array(
      'fields' => array(
        'field_texts' => array(
          'region' => 'disabled',
          'weight' => '-90',
          'format' => 'default',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
        'field_moderators' => array(
          'region' => 'middle',
          'weight' => '-99',
          'format' => 'default',
          'css-class' => '',
          'labelformat' => 'above',
        ),
        'field_translators' => array(
          'region' => 'middle',
          'weight' => '-97',
          'format' => 'default',
          'css-class' => '',
          'labelformat' => 'above',
        ),
        'field_scholars' => array(
          'region' => 'middle',
          'weight' => '-98',
          'format' => 'default',
          'css-class' => '',
          'labelformat' => 'above',
        ),
        'field_exp_comments' => array(
          'region' => 'middle',
          'weight' => '-96',
          'format' => 'countdown',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
        'title' => array(
          'region' => 'disabled',
          'weight' => '-91',
          'format' => 'nd_title_h1_nolink',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
        'author' => array(
          'region' => 'middle',
          'weight' => '-100',
          'format' => 'ds_author_link',
          'css-class' => '',
          'label_value' => 'Moderator',
          'labelformat' => 'above',
        ),
        'links' => array(
          'region' => 'disabled',
          'weight' => '-95',
          'format' => '',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
        'read_more' => array(
          'region' => 'disabled',
          'weight' => '-94',
          'format' => 'ds_eval_code',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
        'post_date' => array(
          'region' => 'disabled',
          'weight' => '-93',
          'format' => 'nd_post_date_long',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
        'body' => array(
          'region' => 'disabled',
          'weight' => '-92',
          'format' => 'nd_bodyfield',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
      ),
      'status' => 1,
      'region_styles' => array(
        'header' => '',
        'left' => '',
        'middle' => '',
        'right' => '',
        'footer' => '',
      ),
    ),
    'full' => array(
      'fields' => array(
        'field_texts' => array(
          'region' => 'disabled',
          'weight' => '-98',
          'format' => 'default',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
        'field_moderators' => array(
          'region' => 'disabled',
          'weight' => '-95',
          'format' => 'default',
          'css-class' => '',
          'label_value' => 'Moderators',
          'labelformat' => 'above',
        ),
        'field_translators' => array(
          'region' => 'disabled',
          'weight' => '-96',
          'format' => 'default',
          'css-class' => '',
          'label_value' => 'Translators',
          'labelformat' => 'above',
        ),
        'field_scholars' => array(
          'region' => 'disabled',
          'weight' => '-97',
          'format' => 'default',
          'css-class' => '',
          'label_value' => 'Scholars',
          'labelformat' => 'above',
        ),
        'field_exp_comments' => array(
          'region' => 'disabled',
          'weight' => '-89',
          'format' => 'default',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
        'title' => array(
          'region' => 'disabled',
          'weight' => '-90',
          'format' => 'nd_title_h1_nolink',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
        'author' => array(
          'region' => 'disabled',
          'weight' => '-94',
          'format' => 'ds_author_link',
          'css-class' => '',
          'label_value' => 'Author',
          'labelformat' => 'above',
        ),
        'links' => array(
          'region' => 'disabled',
          'weight' => '-93',
          'format' => '',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
        'read_more' => array(
          'region' => 'disabled',
          'weight' => '-92',
          'format' => 'ds_eval_code',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
        'post_date' => array(
          'region' => 'disabled',
          'weight' => '-91',
          'format' => 'nd_post_date_long',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
        'body' => array(
          'region' => 'middle',
          'weight' => '-100',
          'format' => 'nd_bodyfield',
          'css-class' => '',
          'label_value' => 'Thoughts from the Moderator',
          'labelformat' => 'above',
        ),
        'translation_status' => array(
          'region' => 'middle',
          'weight' => '-99',
          'format' => 'ds_eval_code',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
      ),
      'status' => 1,
      'region_styles' => array(
        'header' => '',
        'left' => '',
        'middle' => '',
        'right' => '',
        'footer' => '',
      ),
    ),
  );

  $export['nd_display_settings_discussion'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'nd_display_settings_term';
  $strongarm->value = array(
    'full' => array(
      'fields' => array(
        'field_part_of_speech' => array(
          'region' => 'middle',
          'weight' => '-100',
          'format' => 'default',
          'css-class' => '',
          'labelformat' => 'above',
        ),
        'field_translation_term' => array(
          'region' => 'middle',
          'weight' => '-100',
          'format' => 'default',
          'css-class' => '',
          'labelformat' => 'hidden',
          'parent' => 'group_translations',
        ),
        'field_translation_context' => array(
          'region' => 'middle',
          'weight' => '-99',
          'format' => 'default',
          'css-class' => '',
          'labelformat' => 'hidden',
          'parent' => 'group_translations',
        ),
        'group_translations' => array(
          'region' => 'middle',
          'weight' => '-97',
          'format' => 'ds_field',
          'css-class' => '',
          'labelformat' => 'above',
        ),
        'title' => array(
          'region' => 'disabled',
          'weight' => '-91',
          'format' => 'nd_title_h1_nolink',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
        'author' => array(
          'region' => 'disabled',
          'weight' => '-92',
          'format' => 'ds_author_nolink',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
        'links' => array(
          'region' => 'disabled',
          'weight' => '-95',
          'format' => '',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
        'read_more' => array(
          'region' => 'disabled',
          'weight' => '-94',
          'format' => 'ds_eval_code',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
        'post_date' => array(
          'region' => 'disabled',
          'weight' => '-93',
          'format' => 'nd_post_date_long',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
        'glossary_references' => array(
          'region' => 'middle',
          'weight' => '-96',
          'format' => 'ds_eval_code',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
      ),
      'status' => 1,
      'region_styles' => array(
        'header' => '',
        'left' => '',
        'middle' => '',
        'right' => '',
        'footer' => '',
      ),
    ),
  );

  $export['nd_display_settings_term'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'nd_display_settings_text';
  $strongarm->value = array(
    'title_body' => array(
      'fields' => array(
        'field_description' => array(
          'region' => 'middle',
          'weight' => '-99',
          'format' => 'default',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
        'title' => array(
          'region' => 'middle',
          'weight' => '-100',
          'format' => 'nd_title_h1_nolink',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
        'author' => array(
          'region' => 'disabled',
          'weight' => '-93',
          'format' => 'ds_author_nolink',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
        'links' => array(
          'region' => 'disabled',
          'weight' => '-94',
          'format' => '',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
        'read_more' => array(
          'region' => 'disabled',
          'weight' => '-97',
          'format' => 'ds_eval_code',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
        'post_date' => array(
          'region' => 'disabled',
          'weight' => '-95',
          'format' => 'nd_post_date_long',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
        'body' => array(
          'region' => 'disabled',
          'weight' => '-96',
          'format' => 'nd_bodyfield',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
        'view_text' => array(
          'region' => 'footer',
          'weight' => '-98',
          'format' => 'ds_eval_code',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
      ),
      'status' => 1,
      'region_styles' => array(
        'header' => '',
        'left' => '',
        'middle' => '',
        'right' => '',
        'footer' => '',
      ),
    ),
    'text_summary' => array(
      'fields' => array(
        'field_description' => array(
          'region' => 'middle',
          'weight' => '-99',
          'format' => 'default',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
        'title' => array(
          'region' => 'middle',
          'weight' => '-100',
          'format' => 'nd_title_h1_nolink',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
        'author' => array(
          'region' => 'disabled',
          'weight' => '-93',
          'format' => 'ds_author_nolink',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
        'links' => array(
          'region' => 'disabled',
          'weight' => '-94',
          'format' => '',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
        'read_more' => array(
          'region' => 'disabled',
          'weight' => '-95',
          'format' => 'ds_eval_code',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
        'post_date' => array(
          'region' => 'disabled',
          'weight' => '-97',
          'format' => 'nd_post_date_long',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
        'body' => array(
          'region' => 'disabled',
          'weight' => '-96',
          'format' => 'nd_bodyfield',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
        'view_text' => array(
          'region' => 'footer',
          'weight' => '-98',
          'format' => 'ds_eval_code',
          'css-class' => '',
          'labelformat' => 'hidden',
        ),
      ),
      'status' => 1,
      'region_styles' => array(
        'header' => '',
        'left' => '',
        'middle' => '',
        'right' => '',
        'footer' => '',
      ),
    ),
  );

  $export['nd_display_settings_text'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'nd_fields';
  $strongarm->value = array(
    'view_text' => array(
      'title' => 'View text',
      'exclude' => array(
        'annotation' => 'annotation',
        'comment' => 'comment',
        'discussion' => 'discussion',
        'page' => 'page',
        'profile' => 'profile',
        'term' => 'term',
        'text' => 0,
      ),
      'type' => 5,
      'status' => 3,
      'properties' => array(
        'formatters' => array(
          'ds_eval_code' => 'Default',
        ),
        'code' => '<?php echo l(t("View Text"), "node/$object->nid"); ?>',
        'token' => 0,
      ),
    ),
    'glossary_references' => array(
      'title' => 'Glossary references',
      'exclude' => array(
        'annotation' => 'annotation',
        'comment' => 'comment',
        'discussion' => 'discussion',
        'page' => 'page',
        'profile' => 'profile',
        'text' => 'text',
        'term' => 0,
      ),
      'type' => 5,
      'status' => 3,
      'properties' => array(
        'formatters' => array(
          'ds_eval_code' => 'Default',
        ),
        'code' => '<?php
$view = views_get_view(\'glossary_references\');
$view->set_arguments(array(\'discussion\', $object->title));
$view->execute();
print \'<h2>\' . $view->get_title() . \'</h2>\';
print $view->render();
$view->destroy();

$view = views_get_view(\'glossary_references\');
$view->set_arguments(array(\'text\', $object->title));
$view->execute();
print \'<h2>\' . $view->get_title() . \'</h2>\';
print $view->render();
$view->destroy();
?>',
        'token' => 0,
      ),
    ),
    'translation_status' => array(
      'title' => 'Translation status',
      'exclude' => array(
        'page' => 'page',
        'annotation' => 0,
        'discussion' => 0,
        'profile' => 0,
        'term' => 0,
        'text' => 0,
        'comment' => 0,
      ),
      'type' => 5,
      'status' => 3,
      'properties' => array(
        'formatters' => array(
          'ds_eval_code' => 'Default',
        ),
        'code' => '<?php
return theme(\'translation_status\', $object);
?>',
        'token' => 0,
      ),
    ),
  );

  $export['nd_fields'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'nd_type_annotation';
  $strongarm->value = 0;

  $export['nd_type_annotation'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'nd_type_comment';
  $strongarm->value = 0;

  $export['nd_type_comment'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'nd_type_discussion';
  $strongarm->value = 0;

  $export['nd_type_discussion'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'nd_type_page';
  $strongarm->value = 0;

  $export['nd_type_page'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'nd_type_profile';
  $strongarm->value = 0;

  $export['nd_type_profile'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'nd_type_term';
  $strongarm->value = 0;

  $export['nd_type_term'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'nd_type_text';
  $strongarm->value = 0;

  $export['nd_type_text'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_comment_annotation';
  $strongarm->value = 0;

  $export['node_comment_annotation'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_comment_comment';
  $strongarm->value = 0;

  $export['node_comment_comment'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_comment_discussion';
  $strongarm->value = '2';

  $export['node_comment_discussion'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_comment_page';
  $strongarm->value = 0;

  $export['node_comment_page'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_comment_plural_annotation';
  $strongarm->value = 'comments';

  $export['node_comment_plural_annotation'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_comment_plural_comment';
  $strongarm->value = 'comments';

  $export['node_comment_plural_comment'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_comment_plural_discussion';
  $strongarm->value = 'comments';

  $export['node_comment_plural_discussion'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_comment_plural_page';
  $strongarm->value = 'comments';

  $export['node_comment_plural_page'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_comment_plural_profile';
  $strongarm->value = 'comments';

  $export['node_comment_plural_profile'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_comment_plural_term';
  $strongarm->value = 'annotations';

  $export['node_comment_plural_term'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_comment_plural_text';
  $strongarm->value = 'comments';

  $export['node_comment_plural_text'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_comment_profile';
  $strongarm->value = 0;

  $export['node_comment_profile'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_comment_term';
  $strongarm->value = '2';

  $export['node_comment_term'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_comment_text';
  $strongarm->value = 0;

  $export['node_comment_text'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_comment_topic_review_annotation';
  $strongarm->value = '0';

  $export['node_comment_topic_review_annotation'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_comment_topic_review_comment';
  $strongarm->value = '0';

  $export['node_comment_topic_review_comment'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_comment_topic_review_discussion';
  $strongarm->value = '0';

  $export['node_comment_topic_review_discussion'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_comment_topic_review_page';
  $strongarm->value = '0';

  $export['node_comment_topic_review_page'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_comment_topic_review_profile';
  $strongarm->value = '0';

  $export['node_comment_topic_review_profile'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_comment_topic_review_term';
  $strongarm->value = '0';

  $export['node_comment_topic_review_term'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_comment_topic_review_text';
  $strongarm->value = '0';

  $export['node_comment_topic_review_text'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_comment_type_annotation';
  $strongarm->value = '';

  $export['node_comment_type_annotation'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_comment_type_comment';
  $strongarm->value = '';

  $export['node_comment_type_comment'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_comment_type_discussion';
  $strongarm->value = 'comment';

  $export['node_comment_type_discussion'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_comment_type_page';
  $strongarm->value = '';

  $export['node_comment_type_page'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_comment_type_profile';
  $strongarm->value = '';

  $export['node_comment_type_profile'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_comment_type_term';
  $strongarm->value = 'annotation';

  $export['node_comment_type_term'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_comment_type_text';
  $strongarm->value = '';

  $export['node_comment_type_text'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_comment_view_annotation';
  $strongarm->value = 'nodecomments';

  $export['node_comment_view_annotation'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_comment_view_comment';
  $strongarm->value = 'nodecomments';

  $export['node_comment_view_comment'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_comment_view_discussion';
  $strongarm->value = 'nurani_comments';

  $export['node_comment_view_discussion'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_comment_view_page';
  $strongarm->value = 'nodecomments';

  $export['node_comment_view_page'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_comment_view_profile';
  $strongarm->value = 'nodecomments';

  $export['node_comment_view_profile'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_comment_view_term';
  $strongarm->value = 'nurani_comments';

  $export['node_comment_view_term'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_comment_view_text';
  $strongarm->value = 'nodecomments';

  $export['node_comment_view_text'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_code';
  $strongarm->value = 'all';

  $export['node_export_code'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_file_list';
  $strongarm->value = '10';

  $export['node_export_file_list'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_filename';
  $strongarm->value = 'node-export[nid-list]([node-count]-nodes).[timestamp].export';

  $export['node_export_filename'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_format';
  $strongarm->value = array(
    'node_code' => 'node_code',
  );

  $export['node_export_format'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_omitted';
  $strongarm->value = array(
    'annotation' => 0,
    'comment' => 0,
    'discussion' => 0,
    'page' => 0,
    'profile' => 0,
    'term' => 0,
    'text' => 0,
  );

  $export['node_export_omitted'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_annotation';
  $strongarm->value = 0;

  $export['node_export_reset_annotation'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_book_mlid_annotation';
  $strongarm->value = 0;

  $export['node_export_reset_book_mlid_annotation'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_book_mlid_comment';
  $strongarm->value = 1;

  $export['node_export_reset_book_mlid_comment'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_book_mlid_discussion';
  $strongarm->value = 1;

  $export['node_export_reset_book_mlid_discussion'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_book_mlid_page';
  $strongarm->value = 0;

  $export['node_export_reset_book_mlid_page'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_book_mlid_profile';
  $strongarm->value = 1;

  $export['node_export_reset_book_mlid_profile'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_book_mlid_term';
  $strongarm->value = 1;

  $export['node_export_reset_book_mlid_term'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_book_mlid_text';
  $strongarm->value = 1;

  $export['node_export_reset_book_mlid_text'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_changed_annotation';
  $strongarm->value = 0;

  $export['node_export_reset_changed_annotation'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_changed_comment';
  $strongarm->value = 1;

  $export['node_export_reset_changed_comment'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_changed_discussion';
  $strongarm->value = 1;

  $export['node_export_reset_changed_discussion'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_changed_page';
  $strongarm->value = 0;

  $export['node_export_reset_changed_page'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_changed_profile';
  $strongarm->value = 1;

  $export['node_export_reset_changed_profile'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_changed_term';
  $strongarm->value = 1;

  $export['node_export_reset_changed_term'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_changed_text';
  $strongarm->value = 1;

  $export['node_export_reset_changed_text'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_comment';
  $strongarm->value = 0;

  $export['node_export_reset_comment'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_created_annotation';
  $strongarm->value = 0;

  $export['node_export_reset_created_annotation'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_created_comment';
  $strongarm->value = 1;

  $export['node_export_reset_created_comment'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_created_discussion';
  $strongarm->value = 1;

  $export['node_export_reset_created_discussion'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_created_page';
  $strongarm->value = 0;

  $export['node_export_reset_created_page'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_created_profile';
  $strongarm->value = 1;

  $export['node_export_reset_created_profile'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_created_term';
  $strongarm->value = 1;

  $export['node_export_reset_created_term'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_created_text';
  $strongarm->value = 1;

  $export['node_export_reset_created_text'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_discussion';
  $strongarm->value = 0;

  $export['node_export_reset_discussion'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_menu_annotation';
  $strongarm->value = 0;

  $export['node_export_reset_menu_annotation'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_menu_comment';
  $strongarm->value = 1;

  $export['node_export_reset_menu_comment'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_menu_discussion';
  $strongarm->value = 1;

  $export['node_export_reset_menu_discussion'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_menu_page';
  $strongarm->value = 0;

  $export['node_export_reset_menu_page'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_menu_profile';
  $strongarm->value = 1;

  $export['node_export_reset_menu_profile'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_menu_term';
  $strongarm->value = 1;

  $export['node_export_reset_menu_term'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_menu_text';
  $strongarm->value = 1;

  $export['node_export_reset_menu_text'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_page';
  $strongarm->value = 0;

  $export['node_export_reset_page'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_path_annotation';
  $strongarm->value = 0;

  $export['node_export_reset_path_annotation'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_path_comment';
  $strongarm->value = 1;

  $export['node_export_reset_path_comment'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_path_discussion';
  $strongarm->value = 1;

  $export['node_export_reset_path_discussion'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_path_page';
  $strongarm->value = 0;

  $export['node_export_reset_path_page'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_path_profile';
  $strongarm->value = 1;

  $export['node_export_reset_path_profile'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_path_term';
  $strongarm->value = 1;

  $export['node_export_reset_path_term'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_path_text';
  $strongarm->value = 1;

  $export['node_export_reset_path_text'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_profile';
  $strongarm->value = 0;

  $export['node_export_reset_profile'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_term';
  $strongarm->value = 0;

  $export['node_export_reset_term'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_export_reset_text';
  $strongarm->value = 0;

  $export['node_export_reset_text'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_annotation';
  $strongarm->value = array(
    0 => 'status',
  );

  $export['node_options_annotation'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_comment';
  $strongarm->value = array(
    0 => 'status',
  );

  $export['node_options_comment'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_discussion';
  $strongarm->value = array(
    0 => 'status',
    1 => 'promote',
  );

  $export['node_options_discussion'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_page';
  $strongarm->value = array(
    0 => 'status',
  );

  $export['node_options_page'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_profile';
  $strongarm->value = array(
    0 => 'status',
  );

  $export['node_options_profile'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_term';
  $strongarm->value = array(
    0 => 'status',
  );

  $export['node_options_term'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_text';
  $strongarm->value = array(
    0 => 'status',
    1 => 'promote',
  );

  $export['node_options_text'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_ignore_words';
  $strongarm->value = 'a,an,as,at,before,but,by,for,from,is,in,into,like,of,off,on,onto,per,since,than,the,this,that,to,up,via,with';

  $export['pathauto_ignore_words'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_indexaliases';
  $strongarm->value = FALSE;

  $export['pathauto_indexaliases'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_max_component_length';
  $strongarm->value = '100';

  $export['pathauto_max_component_length'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_max_length';
  $strongarm->value = '100';

  $export['pathauto_max_length'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_modulelist';
  $strongarm->value = array(
    0 => 'node',
    1 => 'user',
    2 => 'taxonomy',
  );

  $export['pathauto_modulelist'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_applytofeeds';
  $strongarm->value = '';

  $export['pathauto_node_applytofeeds'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_bulkupdate';
  $strongarm->value = FALSE;

  $export['pathauto_node_bulkupdate'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_forum_pattern';
  $strongarm->value = '';

  $export['pathauto_node_forum_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_image_pattern';
  $strongarm->value = '';

  $export['pathauto_node_image_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_page_pattern';
  $strongarm->value = '';

  $export['pathauto_node_page_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_pattern';
  $strongarm->value = 'content/[title-raw]';

  $export['pathauto_node_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_story_pattern';
  $strongarm->value = '';

  $export['pathauto_node_story_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_supportsfeeds';
  $strongarm->value = 'feed';

  $export['pathauto_node_supportsfeeds'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_punctuation_hyphen';
  $strongarm->value = 1;

  $export['pathauto_punctuation_hyphen'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_punctuation_quotes';
  $strongarm->value = 0;

  $export['pathauto_punctuation_quotes'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_separator';
  $strongarm->value = '-';

  $export['pathauto_separator'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_taxonomy_1_pattern';
  $strongarm->value = '';

  $export['pathauto_taxonomy_1_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_taxonomy_2_pattern';
  $strongarm->value = '';

  $export['pathauto_taxonomy_2_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_taxonomy_applytofeeds';
  $strongarm->value = FALSE;

  $export['pathauto_taxonomy_applytofeeds'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_taxonomy_bulkupdate';
  $strongarm->value = FALSE;

  $export['pathauto_taxonomy_bulkupdate'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_taxonomy_pattern';
  $strongarm->value = 'category/[vocab-raw]/[catpath-raw]';

  $export['pathauto_taxonomy_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_taxonomy_supportsfeeds';
  $strongarm->value = '0/feed';

  $export['pathauto_taxonomy_supportsfeeds'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_transliterate';
  $strongarm->value = FALSE;

  $export['pathauto_transliterate'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_update_action';
  $strongarm->value = '2';

  $export['pathauto_update_action'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_user_bulkupdate';
  $strongarm->value = FALSE;

  $export['pathauto_user_bulkupdate'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_user_pattern';
  $strongarm->value = 'users/[user-raw]';

  $export['pathauto_user_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_user_supportsfeeds';
  $strongarm->value = '';

  $export['pathauto_user_supportsfeeds'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_verbose';
  $strongarm->value = FALSE;

  $export['pathauto_verbose'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'site_403';
  $strongarm->value = 'toboggan/denied';

  $export['site_403'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'site_footer';
  $strongarm->value = '';

  $export['site_footer'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'site_frontpage';
  $strongarm->value = 'overview';

  $export['site_frontpage'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'site_mission';
  $strongarm->value = '';

  $export['site_mission'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'site_slogan';
  $strongarm->value = '';

  $export['site_slogan'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'theme_basic_settings';
  $strongarm->value = array(
    'basic_zen_tabs' => 1,
    'basic_wireframe' => 0,
    'basic_block_editing' => 1,
    'basic_rebuild_registry' => 0,
    'basic_breadcrumb' => 'yes',
    'basic_breadcrumb_separator' => ' » ',
    'basic_breadcrumb_home' => 0,
    'basic_breadcrumb_trailing' => 0,
    'basic_breadcrumb_title' => 0,
    'mission' => '',
    'default_logo' => 1,
    'logo_path' => '',
    'default_favicon' => 1,
    'favicon_path' => '',
    'primary_links' => 1,
    'secondary_links' => 1,
    'toggle_logo' => 1,
    'toggle_favicon' => 1,
    'toggle_name' => 0,
    'toggle_search' => 0,
    'toggle_slogan' => 0,
    'toggle_mission' => 0,
    'toggle_node_user_picture' => 0,
    'toggle_comment_user_picture' => 0,
    'toggle_primary_links' => 0,
    'toggle_secondary_links' => 0,
    'logo_upload' => '',
    'favicon_upload' => '',
  );

  $export['theme_basic_settings'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'theme_default';
  $strongarm->value = 'nurani';

  $export['theme_default'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'theme_settings';
  $strongarm->value = array(
    'toggle_node_info_page' => FALSE,
  );

  $export['theme_settings'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_picture_default';
  $strongarm->value = 'sites/all/themes/nurani/images/default.png';

  $export['user_picture_default'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_picture_dimensions';
  $strongarm->value = '85x85';

  $export['user_picture_dimensions'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_picture_file_size';
  $strongarm->value = '8000';

  $export['user_picture_file_size'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_picture_guidelines';
  $strongarm->value = '';

  $export['user_picture_guidelines'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_picture_imagecache_comments';
  $strongarm->value = 'thumbnail_view';

  $export['user_picture_imagecache_comments'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_picture_imagecache_profiles';
  $strongarm->value = 'thumbnail';

  $export['user_picture_imagecache_profiles'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_picture_imagecache_profiles_default';
  $strongarm->value = 'thumbnail';

  $export['user_picture_imagecache_profiles_default'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_picture_imagecache_profiles_min_height';
  $strongarm->value = '';

  $export['user_picture_imagecache_profiles_min_height'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_picture_imagecache_profiles_min_width';
  $strongarm->value = '';

  $export['user_picture_imagecache_profiles_min_width'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_picture_path';
  $strongarm->value = 'pictures';

  $export['user_picture_path'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_pictures';
  $strongarm->value = '1';

  $export['user_pictures'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'views_filters_autosubmit';
  $strongarm->value = array(
    'glossary_terms' => 'glossary_terms',
    'nodecomments' => 0,
    'discussions' => 0,
    'nuranis' => 0,
    'discussion_texts' => 0,
    'texts' => 0,
    'glossary' => 0,
    'comments_recent' => 0,
    'tracker' => 0,
    'frontpage' => 0,
    'archive' => 0,
    'taxonomy_term' => 0,
    'date_browser' => 0,
    'admin_content' => 0,
    'admin_users' => 0,
  );

  $export['views_filters_autosubmit'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'views_filters_reset';
  $strongarm->value = array(
    'glossary_terms' => 'glossary_terms',
    'nodecomments' => 0,
    'discussions' => 0,
    'nuranis' => 0,
    'discussion_texts' => 0,
    'texts' => 0,
    'glossary' => 0,
    'comments_recent' => 0,
    'tracker' => 0,
    'frontpage' => 0,
    'archive' => 0,
    'taxonomy_term' => 0,
    'date_browser' => 0,
    'admin_content' => 0,
    'admin_users' => 0,
  );

  $export['views_filters_reset'] = $strongarm;
  return $export;
}
