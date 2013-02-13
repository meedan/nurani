<?php
/**
 * @file
 * nurani_general.features.node_export_features.inc
 */

/**
 * Implements hook_node_export_features_default().
 */
function nurani_general_node_export_features_default() {
  $node_export = array(
  'code_string' => 'array(
  (object) array(
      \'vid\' => \'1\',
      \'uid\' => \'1\',
      \'title\' => \'Contact Us\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'2\',
      \'promote\' => \'1\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'93b02565-2cc6-469d-afa5-fb75fd23130b\',
      \'nid\' => \'1\',
      \'type\' => \'webform\',
      \'language\' => \'und\',
      \'created\' => \'1360582081\',
      \'changed\' => \'1360582081\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'23d0a8f2-0ef4-4e00-a35c-ccbd4e72f4ee\',
      \'revision_timestamp\' => \'1360582081\',
      \'revision_uid\' => \'1\',
      \'body\' => array(),
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
          \'sioc:Item\',
          \'foaf:Document\',
        ),
        \'title\' => array(
          \'predicates\' => array(
            \'dc:title\',
          ),
        ),
        \'created\' => array(
          \'predicates\' => array(
            \'dc:date\',
            \'dc:created\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'changed\' => array(
          \'predicates\' => array(
            \'dc:modified\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'body\' => array(
          \'predicates\' => array(
            \'content:encoded\',
          ),
        ),
        \'uid\' => array(
          \'predicates\' => array(
            \'sioc:has_creator\',
          ),
          \'type\' => \'rel\',
        ),
        \'name\' => array(
          \'predicates\' => array(
            \'foaf:name\',
          ),
        ),
        \'comment_count\' => array(
          \'predicates\' => array(
            \'sioc:num_replies\',
          ),
          \'datatype\' => \'xsd:integer\',
        ),
        \'last_activity\' => array(
          \'predicates\' => array(
            \'sioc:last_activity_date\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
      ),
      \'webform\' => array(
        \'nid\' => \'1\',
        \'confirmation\' => \'\',
        \'confirmation_format\' => NULL,
        \'redirect_url\' => \'<confirmation>\',
        \'status\' => \'1\',
        \'block\' => \'0\',
        \'teaser\' => \'0\',
        \'allow_draft\' => \'0\',
        \'auto_save\' => \'0\',
        \'submit_notice\' => \'1\',
        \'submit_text\' => \'\',
        \'submit_limit\' => \'-1\',
        \'submit_interval\' => \'-1\',
        \'total_submit_limit\' => \'-1\',
        \'total_submit_interval\' => \'-1\',
        \'record_exists\' => TRUE,
        \'roles\' => array(
          \'1\',
          \'2\',
        ),
        \'emails\' => array(),
        \'components\' => array(
          1 => array(
            \'nid\' => 1,
            \'cid\' => \'1\',
            \'pid\' => \'0\',
            \'form_key\' => \'name\',
            \'name\' => \'Name\',
            \'type\' => \'textfield\',
            \'value\' => \'\',
            \'extra\' => array(
              \'title_display\' => \'before\',
              \'private\' => 0,
              \'disabled\' => 0,
              \'unique\' => 0,
              \'width\' => \'\',
              \'maxlength\' => \'\',
              \'field_prefix\' => \'\',
              \'field_suffix\' => \'\',
              \'description\' => \'\',
              \'attributes\' => array(),
            ),
            \'mandatory\' => \'1\',
            \'weight\' => \'0\',
            \'page_num\' => 1,
          ),
          2 => array(
            \'nid\' => 1,
            \'cid\' => \'2\',
            \'pid\' => \'0\',
            \'form_key\' => \'email_address\',
            \'name\' => \'Email Address\',
            \'type\' => \'textfield\',
            \'value\' => \'\',
            \'extra\' => array(
              \'title_display\' => \'before\',
              \'private\' => 0,
              \'disabled\' => 0,
              \'unique\' => 0,
              \'width\' => \'\',
              \'maxlength\' => \'\',
              \'field_prefix\' => \'\',
              \'field_suffix\' => \'\',
              \'description\' => \'\',
              \'attributes\' => array(),
            ),
            \'mandatory\' => \'1\',
            \'weight\' => \'1\',
            \'page_num\' => 1,
          ),
          3 => array(
            \'nid\' => 1,
            \'cid\' => \'3\',
            \'pid\' => \'0\',
            \'form_key\' => \'telephone\',
            \'name\' => \'Telephone \',
            \'type\' => \'textfield\',
            \'value\' => \'\',
            \'extra\' => array(
              \'title_display\' => \'before\',
              \'private\' => 0,
              \'disabled\' => 0,
              \'unique\' => 0,
              \'width\' => \'\',
              \'maxlength\' => \'\',
              \'field_prefix\' => \'\',
              \'field_suffix\' => \'\',
              \'description\' => \'\',
              \'attributes\' => array(),
            ),
            \'mandatory\' => \'0\',
            \'weight\' => \'2\',
            \'page_num\' => 1,
          ),
          4 => array(
            \'nid\' => 1,
            \'cid\' => \'4\',
            \'pid\' => \'0\',
            \'form_key\' => \'message\',
            \'name\' => \'Message\',
            \'type\' => \'textarea\',
            \'value\' => \'\',
            \'extra\' => array(
              \'title_display\' => 0,
              \'private\' => 0,
              \'resizable\' => 1,
              \'disabled\' => 0,
              \'cols\' => \'\',
              \'rows\' => \'\',
              \'description\' => \'\',
              \'attributes\' => array(),
            ),
            \'mandatory\' => \'1\',
            \'weight\' => \'3\',
            \'page_num\' => 1,
          ),
        ),
        \'conditionals\' => array(),
      ),
      \'cid\' => \'0\',
      \'last_comment_timestamp\' => \'1360582081\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'1\',
      \'comment_count\' => \'0\',
      \'print_display\' => 1,
      \'print_display_comment\' => 0,
      \'print_display_urllist\' => 1,
      \'name\' => \'admin\',
      \'picture\' => \'31\',
      \'data\' => \'a:1:{s:7:"overlay";i:1;}\',
      \'print_pdf_display\' => 1,
      \'print_pdf_display_comment\' => 0,
      \'print_pdf_display_urllist\' => 1,
      \'menu\' => array(
        \'link_title\' => \'Contact Us\',
        \'mlid\' => 0,
        \'plid\' => \'0\',
        \'menu_name\' => \'main-menu\',
        \'weight\' => \'0\',
        \'options\' => array(),
        \'module\' => \'menu\',
        \'expanded\' => \'0\',
        \'hidden\' => \'0\',
        \'has_children\' => \'0\',
        \'customized\' => 0,
        \'parent_depth_limit\' => 8,
        \'description\' => \'\',
        \'enabled\' => 1,
      ),
      \'path\' => array(
        \'pid\' => \'3\',
        \'source\' => \'node/1\',
        \'alias\' => \'content/contact-us\',
        \'language\' => \'und\',
      ),
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'2\',
      \'uid\' => \'1\',
      \'title\' => \'Getting started\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'1\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'9f1bc141-b187-4df1-99a2-4d0507894d2e\',
      \'nid\' => \'2\',
      \'type\' => \'page\',
      \'language\' => \'und\',
      \'created\' => \'1360584714\',
      \'changed\' => \'1360589284\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'2928f1d4-6be9-404d-a3ca-3945316189af\',
      \'revision_timestamp\' => \'1360589284\',
      \'revision_uid\' => \'1\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => "SCRIPTURAL REASONING online Practicalities and guidelines\\r\\n\\r\\nWELCOME to Scriptural Reasoning online. We hope that you enjoy being part of a discussion group and that you come away from this experience enriched and stimulated.\\r\\n\\r\\nThis document contains important practical points including instructions to get you started. You’ll find some guidelines on what makes a good SR discussion under ‘How to do Scriptural Reasoning’. Please read these through carefully before you begin and get in touch if you have any further questions.\\r\\n\\r\\nYour group is made up of 6-10 people from a variety of religious traditions, usually Jewish, Muslim and Christian. The group will have three Scripture texts to study together, one from each tradition, and these will be posted on the Scriptural Reasoning discussion platform by the moderator. Group discussion will run for a fixed period of time – normally between 3 and 6 weeks, and you will be informed by email of the start date of the group and how long it will run for. After the group finishes we will ask you to complete a short online survey about your experience of SR online and you will have the option to take part in another group.\\r\\n\\r\\nScriptural Reasoning online operates through a custom-made online platform called Nurani, designed by the not-for-profit organisation, Meedan. The Nurani Platform is easy to use, but please be aware that some features on it, such as the English-Arabic translation and the Glossary, are not yet fully functional. As soon as we issue you with a username and password you will receive an email from the site administrator. To activate this and be invited to a discussion, simply click the link and log into the site for the first time. You will have to agree to the Privacy policy before continuing. You then have the option to create a password known only to you and to add other details about yourself if you wish. Don’t forget to click the ‘Save’ button at the end, and to return to the main page click ‘Overview’. When you receive an email inviting you to your first discussion, log onto the site where you will see the discussion title with a welcome note from the moderator. Simply click on the ‘View’ button to access the discussion where the text will be displayed along with some introductory comments. All you have to do is read the texts carefully and reflect on them, and then join in the discussion - see the guidelines below. Please keep your comments brief – ideally no more than 250 words.\\r\\n\\r\\nBy logging onto the Nurani site you agree to be bound by the Nurani terms and conditions, http://nurani.org/content/terms and the Privacy policy, http://nurani.org/content/privacy .\\r\\n ",
            \'summary\' => \'\',
            \'format\' => \'filtered_html\',
            \'safe_value\' => "<p>SCRIPTURAL REASONING online Practicalities and guidelines</p>\\n<p>WELCOME to Scriptural Reasoning online. We hope that you enjoy being part of a discussion group and that you come away from this experience enriched and stimulated.</p>\\n<p>This document contains important practical points including instructions to get you started. You’ll find some guidelines on what makes a good SR discussion under ‘How to do Scriptural Reasoning’. Please read these through carefully before you begin and get in touch if you have any further questions.</p>\\n<p>Your group is made up of 6-10 people from a variety of religious traditions, usually Jewish, Muslim and Christian. The group will have three Scripture texts to study together, one from each tradition, and these will be posted on the Scriptural Reasoning discussion platform by the moderator. Group discussion will run for a fixed period of time – normally between 3 and 6 weeks, and you will be informed by email of the start date of the group and how long it will run for. After the group finishes we will ask you to complete a short online survey about your experience of SR online and you will have the option to take part in another group.</p>\\n<p>Scriptural Reasoning online operates through a custom-made online platform called Nurani, designed by the not-for-profit organisation, Meedan. The Nurani Platform is easy to use, but please be aware that some features on it, such as the English-Arabic translation and the Glossary, are not yet fully functional. As soon as we issue you with a username and password you will receive an email from the site administrator. To activate this and be invited to a discussion, simply click the link and log into the site for the first time. You will have to agree to the Privacy policy before continuing. You then have the option to create a password known only to you and to add other details about yourself if you wish. Don’t forget to click the ‘Save’ button at the end, and to return to the main page click ‘Overview’. When you receive an email inviting you to your first discussion, log onto the site where you will see the discussion title with a welcome note from the moderator. Simply click on the ‘View’ button to access the discussion where the text will be displayed along with some introductory comments. All you have to do is read the texts carefully and reflect on them, and then join in the discussion - see the guidelines below. Please keep your comments brief – ideally no more than 250 words.</p>\\n<p>By logging onto the Nurani site you agree to be bound by the Nurani terms and conditions, <a href=\\"http://nurani.org/content/terms\\">http://nurani.org/content/terms</a> and the Privacy policy, <a href=\\"http://nurani.org/content/privacy\\">http://nurani.org/content/privacy</a> .<br />\\n </p>\\n",
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
          \'sioc:Item\',
          \'foaf:Document\',
        ),
        \'title\' => array(
          \'predicates\' => array(
            \'dc:title\',
          ),
        ),
        \'created\' => array(
          \'predicates\' => array(
            \'dc:date\',
            \'dc:created\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'changed\' => array(
          \'predicates\' => array(
            \'dc:modified\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'body\' => array(
          \'predicates\' => array(
            \'content:encoded\',
          ),
        ),
        \'uid\' => array(
          \'predicates\' => array(
            \'sioc:has_creator\',
          ),
          \'type\' => \'rel\',
        ),
        \'name\' => array(
          \'predicates\' => array(
            \'foaf:name\',
          ),
        ),
        \'comment_count\' => array(
          \'predicates\' => array(
            \'sioc:num_replies\',
          ),
          \'datatype\' => \'xsd:integer\',
        ),
        \'last_activity\' => array(
          \'predicates\' => array(
            \'sioc:last_activity_date\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
      ),
      \'cid\' => \'0\',
      \'last_comment_timestamp\' => \'1360584714\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'1\',
      \'comment_count\' => \'0\',
      \'print_display\' => 1,
      \'print_display_comment\' => 0,
      \'print_display_urllist\' => 1,
      \'name\' => \'admin\',
      \'picture\' => \'31\',
      \'data\' => \'a:1:{s:7:"overlay";i:1;}\',
      \'print_pdf_display\' => 1,
      \'print_pdf_display_comment\' => 0,
      \'print_pdf_display_urllist\' => 1,
      \'menu\' => NULL,
      \'path\' => array(
        \'pid\' => \'103\',
        \'source\' => \'node/2\',
        \'alias\' => \'content/getting-started\',
        \'language\' => \'und\',
      ),
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'3\',
      \'uid\' => \'1\',
      \'title\' => \'About Nurani.org\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'1\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'5973078b-dc56-42b7-9b0a-64026af952f4\',
      \'nid\' => \'3\',
      \'type\' => \'page\',
      \'language\' => \'und\',
      \'created\' => \'1360588891\',
      \'changed\' => \'1360588891\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'57816b30-c59b-4b0e-9fc0-dea7b6c723ef\',
      \'revision_timestamp\' => \'1360588891\',
      \'revision_uid\' => \'1\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => "Nurani.org is a platform for dialogue between Muslims, Jews and Christians, where participants from three faiths, Christianity, Judaism and Islam, meet to discuss short texts from their respective scriptures. The product of a collaboration between the Cambridge Inter-faith Programme at the University of Cambridge, the nonprofit technology company Meedan, the Coexist Foundation, and a consortium of universities and research centres, it allows scholars from the three faith traditions to share and study their scriptures together.\\r\\n\\r\\nNurani.org specifically aims to:\\r\\n\\r\\n* enable rich and fruitful discussion of scriptural texts between Muslims, Jews and Christians;\\r\\n* facilitate deeper understanding of the lived traditions and beliefs of Islam, Judaism and Christianity;\\r\\n* build trust and friendship between Jewish, Christian and Muslim participants; and\\r\\n* develop new research methods and tools for collaboratively studying texts across languages.\\r\\nParticipating in Nurani.org is initially by invitation only, as we are seeking to create a context in which high-quality, well moderated and safe inter-faith discussion can take place between people from a wide range of locations and backgrounds. No prior experience in Scriptural Reasoning or expertise in scriptural texts is necessary. To request further information or an invitation to the platform, email sronline[at]interfaith.cam.ac.uk.  \\r\\n\\r\\nNurani.org is designed to be bi-lingual, although this feature is not yet functional. Every piece of text will be translated between two languages - Arabic and English - as it is published. This is made possible by a team of professional translators with religious knowledge working with the translation tools built into the platform. Currently though we are testing monolingual discussions.\\r\\n\\r\\nPartners\\r\\n\\r\\nThe Inter-faith Platform Project is a collaboration between a number of the world’s leading institutions for faith research, led by the Cambridge Inter-faith Programme (CIP), a program of the Faculty of Divinity at the University of Cambridge, UK, and Meedan, a social technology nonprofit based in San Francisco.\\r\\n\\r\\nCIP is a flagship project of the University of Cambridge 800th Anniversary Campaign, offering a distinctive scholarly approach to furthering understanding across the Abrahamic traditions with a strong emphasis on collaboration and translation. It is taking the lead in building the network of partner institutions using this platform, initiating and moderating dialogues, and creating scholarly resources. Learn more here.\\r\\n\\r\\nThis platform was built by Meedan, a leading charitable provider of advanced technologies for dialogue and cross-language encounter, with expertise in cross-language interaction design and system design for Arabic-English translation on the web. Learn more here.\\r\\n\\r\\nThank you for visiting this website today. Find out how you can contribute by emailing sronline@interfaith.cam.ac.uk.\\r\\n\\r\\nAbout Nurani.org\\r\\nHow to do Scriptural Reasoning\\r\\nGetting started\\r\\nPrivacy\\r\\nTerms\\r\\n",
            \'summary\' => \'\',
            \'format\' => \'filtered_html\',
            \'safe_value\' => "<p>Nurani.org is a platform for dialogue between Muslims, Jews and Christians, where participants from three faiths, Christianity, Judaism and Islam, meet to discuss short texts from their respective scriptures. The product of a collaboration between the Cambridge Inter-faith Programme at the University of Cambridge, the nonprofit technology company Meedan, the Coexist Foundation, and a consortium of universities and research centres, it allows scholars from the three faith traditions to share and study their scriptures together.</p>\\n<p>Nurani.org specifically aims to:</p>\\n<p>* enable rich and fruitful discussion of scriptural texts between Muslims, Jews and Christians;<br />\\n* facilitate deeper understanding of the lived traditions and beliefs of Islam, Judaism and Christianity;<br />\\n* build trust and friendship between Jewish, Christian and Muslim participants; and<br />\\n* develop new research methods and tools for collaboratively studying texts across languages.<br />\\nParticipating in Nurani.org is initially by invitation only, as we are seeking to create a context in which high-quality, well moderated and safe inter-faith discussion can take place between people from a wide range of locations and backgrounds. No prior experience in Scriptural Reasoning or expertise in scriptural texts is necessary. To request further information or an invitation to the platform, email sronline[at]interfaith.cam.ac.uk.  </p>\\n<p>Nurani.org is designed to be bi-lingual, although this feature is not yet functional. Every piece of text will be translated between two languages - Arabic and English - as it is published. This is made possible by a team of professional translators with religious knowledge working with the translation tools built into the platform. Currently though we are testing monolingual discussions.</p>\\n<p>Partners</p>\\n<p>The Inter-faith Platform Project is a collaboration between a number of the world’s leading institutions for faith research, led by the Cambridge Inter-faith Programme (CIP), a program of the Faculty of Divinity at the University of Cambridge, UK, and Meedan, a social technology nonprofit based in San Francisco.</p>\\n<p>CIP is a flagship project of the University of Cambridge 800th Anniversary Campaign, offering a distinctive scholarly approach to furthering understanding across the Abrahamic traditions with a strong emphasis on collaboration and translation. It is taking the lead in building the network of partner institutions using this platform, initiating and moderating dialogues, and creating scholarly resources. Learn more here.</p>\\n<p>This platform was built by Meedan, a leading charitable provider of advanced technologies for dialogue and cross-language encounter, with expertise in cross-language interaction design and system design for Arabic-English translation on the web. Learn more here.</p>\\n<p>Thank you for visiting this website today. Find out how you can contribute by emailing <a href=\\"mailto:sronline@interfaith.cam.ac.uk\\">sronline@interfaith.cam.ac.uk</a>.</p>\\n<p>About Nurani.org<br />\\nHow to do Scriptural Reasoning<br />\\nGetting started<br />\\nPrivacy<br />\\nTerms</p>\\n",
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
          \'sioc:Item\',
          \'foaf:Document\',
        ),
        \'title\' => array(
          \'predicates\' => array(
            \'dc:title\',
          ),
        ),
        \'created\' => array(
          \'predicates\' => array(
            \'dc:date\',
            \'dc:created\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'changed\' => array(
          \'predicates\' => array(
            \'dc:modified\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'body\' => array(
          \'predicates\' => array(
            \'content:encoded\',
          ),
        ),
        \'uid\' => array(
          \'predicates\' => array(
            \'sioc:has_creator\',
          ),
          \'type\' => \'rel\',
        ),
        \'name\' => array(
          \'predicates\' => array(
            \'foaf:name\',
          ),
        ),
        \'comment_count\' => array(
          \'predicates\' => array(
            \'sioc:num_replies\',
          ),
          \'datatype\' => \'xsd:integer\',
        ),
        \'last_activity\' => array(
          \'predicates\' => array(
            \'sioc:last_activity_date\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
      ),
      \'cid\' => \'0\',
      \'last_comment_timestamp\' => \'1360588891\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'1\',
      \'comment_count\' => \'0\',
      \'print_display\' => 1,
      \'print_display_comment\' => 0,
      \'print_display_urllist\' => 1,
      \'name\' => \'admin\',
      \'picture\' => \'31\',
      \'data\' => \'a:1:{s:7:"overlay";i:1;}\',
      \'print_pdf_display\' => 1,
      \'print_pdf_display_comment\' => 0,
      \'print_pdf_display_urllist\' => 1,
      \'menu\' => NULL,
      \'path\' => array(
        \'pid\' => \'105\',
        \'source\' => \'node/3\',
        \'alias\' => \'content/about-nuraniorg\',
        \'language\' => \'und\',
      ),
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'4\',
      \'uid\' => \'1\',
      \'title\' => \'Privacy\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'1\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'8f145232-73a4-450d-aa18-0622122b7f19\',
      \'nid\' => \'4\',
      \'type\' => \'page\',
      \'language\' => \'und\',
      \'created\' => \'1360589094\',
      \'changed\' => \'1360589094\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'61f94109-8276-4c06-be47-76c4a5148fc5\',
      \'revision_timestamp\' => \'1360589094\',
      \'revision_uid\' => \'1\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => "Nurani.org is designed to allow you to take part in dialogues about your beliefs and opinions, so it is very important that you read and agree to the following terms which relate to how we store personal data that you submit to the platform. The terms form part of the contract that you agree to on registering with this website, but are also here to reassure you that the Cambridge Inter-faith Programme and Meedan, Inc. (the Service Providers) have a strict data policy in place to protect your personal data.\\r\\n\\r\\nWe (The Service Providers) reserve the right to modify the information contained herein at anytime. If we do make changes to our privacy policy that affect your personal data, we will notify You (the Registered User) using the email that you have given us. This site and all information and materials on it are provided to you \\"as is\\" without warranty of any kind. Ÿour use of this site, or your provision to us of any personal information constitutes your agreement to these terms; do not use the site or provide information if you do not agree with all of the terms.\\r\\n\\r\\nInformation You Provide\\r\\n\\r\\n1. Registration\\r\\n\\r\\nWhen you register for an account you will be asked to give your name, email address and password. You can update this information at any time. Only you will be able to see your password. Your email address will be viewable by system administrators representing The Service Providers and moderators granted permission to manage dialogues on Nurani.org by CIP. We will use your email address to communicate important notifications about this privacy policy, requests for disclosure by Third Parties, or other notifications that relate to your use of Nurani.org. Moderators may use your email address to help manage dialogues on Nurani.org and to warn you if your behaviour is deemed inappropriate. You can also opt to receive notifications of new content that will be delivered automatically to your email address.\\r\\n\\r\\n2. Profile Information\\r\\n\\r\\nWhen you register for an account you will have the option to build a profile. This profile may include, but is not limited to, information such as your personal names, location, education, professional experience and affiliations. You will be able to edit and remove this information at any time, and to control whether it is viewable publicly or only by other users of Nurani.org. We encourage you to supply this information to help other users learn more about you. We think this will help you to have more productive dialogues with other users.\\r\\n\\r\\n3. Posting\\r\\n\\r\\nOn Nurani.org you can post three kinds of content: texts, glossary terms, and discussion comments. We intend for all texts and glossary terms added to Nurani.org to be publicly viewable. Discussions, however, depend on the privacy settings of the group to which you were invited by a moderator. A discussion on Nurani may have one of three settings: private to the members of the group, viewable by all groups on Nurani, or public on the web. Identification of all contributed content may include, but is not limited to, display of your account name. All content may be retained for restorative, archival, or research purposes by The Service Providers. Editing or deleting content may alter the displayed state of the content, but will not permanently delete the content from the website.\\r\\n\\r\\n4. Normal Browsing\\r\\n\\r\\nThe Service Providers collect certain information about your browsing habits, including your IP address, URL request, browser type, and date and time of your request. This information is gathered on an aggregate basis only. For example, we track which pages are most popular among visitors as a whole. We do not track information on which pages an individual user visits. We do not collect any other information without your knowledge and permission.\\r\\n\\r\\nWe analyze traffic to Nurani.org in various ways, including using a service called Google Analytics. (Google Analytics is subject to the privacy policy of Google, Inc., which you can find at the following url: http://www.google.co.uk/intl/en/privacy/privacy-policy.html) Unless you affirmatively provide additional information, we do not collect or store personally identifiable information such as mailing address, phone number, or social security number.\\r\\nStorage\\r\\n\\r\\nBy agreeing to these terms you consent that personal data collected on Nurani.org may be transferred to, and stored at, a destination outside the European Economic Area (“EEA”). It may also be processed by staff operating outside the EEA who work for the Cambridge Inter-faith Programme (CIP) or for Meedan, Inc. By submitting your personal data, you agree to this transfer, storing or processing.\\r\\n\\r\\nSecurity\\r\\n\\r\\nThe Service Providers will take all reasonable steps to ensure that your data is treated securely and in accordance with the European Commission’s contractual requirements for the transfer of personal data to processors outside the EU. In order to prevent against accidental or unlawful destruction or accidental loss, alteration, or unauthorised disclosure or access, The Service Providers have put in place strict technical and managerial procedures to safeguard and secure the information processed by Nurani.org. If you wish to review these measures click here.\\r\\n\\r\\nDisclosure of Information\\r\\n\\r\\nAvailable log records, account information, and all data stored on our servers may be accessed by system administrators representing The Service Providers.\\r\\n\\r\\nIn the event that we are required by law (including a court order) to disclose the information you submit, we will provide you with notice that a request for your information has been made so that you may object to the disclosure. We will send this notice by email to the address you have given us.\\r\\n\\r\\nThe Service Providers will take all reasonable measures to notify you in advance of any planned transfer of your personal data to a Third Party or Subprocessor so that you can opt to remove your data from this transfer if you wish. In the unlikely event of unauthorised access to your data, The Service Providers undertake to inform you promptly.\\r\\n\\r\\nIf you have any questions regarding the personal data The Service Providers hold about you, you can contact Meedan’s Data Protection Manager at the following address:\\r\\n\\r\\nprivacy@meedan.net\\r\\n\\r\\nMeedan, Inc.\\r\\n972 Mission Street,\\r\\nSan Francisco\\r\\nCalifornia 94310\\r\\nUSA\\r\\nCookies\\r\\nThe Service Providers may use session cookies when you visit our website while your browser is open, or while you are logged into Nurani.org. To facilitate registration and login functions, The Service Providers may use cookies to recognise when you return to the website. If you do not logout of your account, these cookies keep track of your username and password so that you do not have to resubmit the information to log into your account. If others will be using your computer, you should log out of your account so that your login information is cleared.\\r\\n\\r\\nThese Terms are licensed under CC http://www.citmedialaw.org/)",
            \'summary\' => \'\',
            \'format\' => \'filtered_html\',
            \'safe_value\' => "<p>Nurani.org is designed to allow you to take part in dialogues about your beliefs and opinions, so it is very important that you read and agree to the following terms which relate to how we store personal data that you submit to the platform. The terms form part of the contract that you agree to on registering with this website, but are also here to reassure you that the Cambridge Inter-faith Programme and Meedan, Inc. (the Service Providers) have a strict data policy in place to protect your personal data.</p>\\n<p>We (The Service Providers) reserve the right to modify the information contained herein at anytime. If we do make changes to our privacy policy that affect your personal data, we will notify You (the Registered User) using the email that you have given us. This site and all information and materials on it are provided to you \\"as is\\" without warranty of any kind. Ÿour use of this site, or your provision to us of any personal information constitutes your agreement to these terms; do not use the site or provide information if you do not agree with all of the terms.</p>\\n<p>Information You Provide</p>\\n<p>1. Registration</p>\\n<p>When you register for an account you will be asked to give your name, email address and password. You can update this information at any time. Only you will be able to see your password. Your email address will be viewable by system administrators representing The Service Providers and moderators granted permission to manage dialogues on Nurani.org by CIP. We will use your email address to communicate important notifications about this privacy policy, requests for disclosure by Third Parties, or other notifications that relate to your use of Nurani.org. Moderators may use your email address to help manage dialogues on Nurani.org and to warn you if your behaviour is deemed inappropriate. You can also opt to receive notifications of new content that will be delivered automatically to your email address.</p>\\n<p>2. Profile Information</p>\\n<p>When you register for an account you will have the option to build a profile. This profile may include, but is not limited to, information such as your personal names, location, education, professional experience and affiliations. You will be able to edit and remove this information at any time, and to control whether it is viewable publicly or only by other users of Nurani.org. We encourage you to supply this information to help other users learn more about you. We think this will help you to have more productive dialogues with other users.</p>\\n<p>3. Posting</p>\\n<p>On Nurani.org you can post three kinds of content: texts, glossary terms, and discussion comments. We intend for all texts and glossary terms added to Nurani.org to be publicly viewable. Discussions, however, depend on the privacy settings of the group to which you were invited by a moderator. A discussion on Nurani may have one of three settings: private to the members of the group, viewable by all groups on Nurani, or public on the web. Identification of all contributed content may include, but is not limited to, display of your account name. All content may be retained for restorative, archival, or research purposes by The Service Providers. Editing or deleting content may alter the displayed state of the content, but will not permanently delete the content from the website.</p>\\n<p>4. Normal Browsing</p>\\n<p>The Service Providers collect certain information about your browsing habits, including your IP address, URL request, browser type, and date and time of your request. This information is gathered on an aggregate basis only. For example, we track which pages are most popular among visitors as a whole. We do not track information on which pages an individual user visits. We do not collect any other information without your knowledge and permission.</p>\\n<p>We analyze traffic to Nurani.org in various ways, including using a service called Google Analytics. (Google Analytics is subject to the privacy policy of Google, Inc., which you can find at the following url: <a href=\\"http://www.google.co.uk/intl/en/privacy/privacy-policy.html\\">http://www.google.co.uk/intl/en/privacy/privacy-policy.html</a>) Unless you affirmatively provide additional information, we do not collect or store personally identifiable information such as mailing address, phone number, or social security number.<br />\\nStorage</p>\\n<p>By agreeing to these terms you consent that personal data collected on Nurani.org may be transferred to, and stored at, a destination outside the European Economic Area (“EEA”). It may also be processed by staff operating outside the EEA who work for the Cambridge Inter-faith Programme (CIP) or for Meedan, Inc. By submitting your personal data, you agree to this transfer, storing or processing.</p>\\n<p>Security</p>\\n<p>The Service Providers will take all reasonable steps to ensure that your data is treated securely and in accordance with the European Commission’s contractual requirements for the transfer of personal data to processors outside the EU. In order to prevent against accidental or unlawful destruction or accidental loss, alteration, or unauthorised disclosure or access, The Service Providers have put in place strict technical and managerial procedures to safeguard and secure the information processed by Nurani.org. If you wish to review these measures click here.</p>\\n<p>Disclosure of Information</p>\\n<p>Available log records, account information, and all data stored on our servers may be accessed by system administrators representing The Service Providers.</p>\\n<p>In the event that we are required by law (including a court order) to disclose the information you submit, we will provide you with notice that a request for your information has been made so that you may object to the disclosure. We will send this notice by email to the address you have given us.</p>\\n<p>The Service Providers will take all reasonable measures to notify you in advance of any planned transfer of your personal data to a Third Party or Subprocessor so that you can opt to remove your data from this transfer if you wish. In the unlikely event of unauthorised access to your data, The Service Providers undertake to inform you promptly.</p>\\n<p>If you have any questions regarding the personal data The Service Providers hold about you, you can contact Meedan’s Data Protection Manager at the following address:</p>\\n<p><a href=\\"mailto:privacy@meedan.net\\">privacy@meedan.net</a></p>\\n<p>Meedan, Inc.<br />\\n972 Mission Street,<br />\\nSan Francisco<br />\\nCalifornia 94310<br />\\nUSA<br />\\nCookies<br />\\nThe Service Providers may use session cookies when you visit our website while your browser is open, or while you are logged into Nurani.org. To facilitate registration and login functions, The Service Providers may use cookies to recognise when you return to the website. If you do not logout of your account, these cookies keep track of your username and password so that you do not have to resubmit the information to log into your account. If others will be using your computer, you should log out of your account so that your login information is cleared.</p>\\n<p>These Terms are licensed under CC <a href=\\"http://www.citmedialaw.org/\\">http://www.citmedialaw.org/</a>)</p>\\n",
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
          \'sioc:Item\',
          \'foaf:Document\',
        ),
        \'title\' => array(
          \'predicates\' => array(
            \'dc:title\',
          ),
        ),
        \'created\' => array(
          \'predicates\' => array(
            \'dc:date\',
            \'dc:created\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'changed\' => array(
          \'predicates\' => array(
            \'dc:modified\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'body\' => array(
          \'predicates\' => array(
            \'content:encoded\',
          ),
        ),
        \'uid\' => array(
          \'predicates\' => array(
            \'sioc:has_creator\',
          ),
          \'type\' => \'rel\',
        ),
        \'name\' => array(
          \'predicates\' => array(
            \'foaf:name\',
          ),
        ),
        \'comment_count\' => array(
          \'predicates\' => array(
            \'sioc:num_replies\',
          ),
          \'datatype\' => \'xsd:integer\',
        ),
        \'last_activity\' => array(
          \'predicates\' => array(
            \'sioc:last_activity_date\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
      ),
      \'cid\' => \'0\',
      \'last_comment_timestamp\' => \'1360589094\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'1\',
      \'comment_count\' => \'0\',
      \'print_display\' => 1,
      \'print_display_comment\' => 0,
      \'print_display_urllist\' => 1,
      \'name\' => \'admin\',
      \'picture\' => \'31\',
      \'data\' => \'a:1:{s:7:"overlay";i:1;}\',
      \'print_pdf_display\' => 1,
      \'print_pdf_display_comment\' => 0,
      \'print_pdf_display_urllist\' => 1,
      \'menu\' => NULL,
      \'path\' => array(
        \'pid\' => \'107\',
        \'source\' => \'node/4\',
        \'alias\' => \'content/privacy\',
        \'language\' => \'und\',
      ),
      \'node_export_drupal_version\' => \'7\',
    ),
  (object) array(
      \'vid\' => \'5\',
      \'uid\' => \'1\',
      \'title\' => \'How to do Scriptural Reasoning\',
      \'log\' => \'\',
      \'status\' => \'1\',
      \'comment\' => \'1\',
      \'promote\' => \'0\',
      \'sticky\' => \'0\',
      \'vuuid\' => \'4fc367bd-78d2-4a6d-8576-8d6938b858d1\',
      \'nid\' => \'5\',
      \'type\' => \'page\',
      \'language\' => \'und\',
      \'created\' => \'1360588531\',
      \'changed\' => \'1360588594\',
      \'tnid\' => \'0\',
      \'translate\' => \'0\',
      \'uuid\' => \'e89bb55b-083c-441f-8a57-ec2d0b2e14df\',
      \'revision_timestamp\' => \'1360588594\',
      \'revision_uid\' => \'1\',
      \'body\' => array(
        \'und\' => array(
          array(
            \'value\' => "Guidelines for Scriptural Reasoning discussions\\r\\n\\r\\nHere are some ground rules to keep in mind, which can help the Scriptural Reasoning discussion work well:\\r\\n\\r\\nThe first and most important ground rule is to stick to the texts.\\r\\nIt is our experience that these discussions are much more fruitful if the discussion remains focused on the scriptural texts and on the ways in which they can be read – rather than spiralling off to become a general discussion of Judaism, Islam and Christianity. Be prepared to answer the question, ‘Where do you see that in the text?’ If you draw from sources other than the passage in question, you should be able to connect them to that particular text.\\r\\n\\r\\nThe second ground rule is give space to others’ readings.\\r\\nEven if you have very firm, clear and well-formed ideas about how a particular text should be read (perhaps it is just obvious to you what this text means, or you know other scriptural texts that help interpret this one, or you know authoritative commentaries on the text from your tradition) don’t simply impose that reading on the group. The discussion will work best if the other participants are able to hear about the way you believe the text should be read whilst exploring the text, and other possible ways of reading it, for themselves. That may sometimes mean that you have to sit back for a while, and let a discussion continue that you believe to be mistaken – before finding a way gently to explain to people how and why you read the text the way you do.\\r\\n\\r\\nThe third ground rule is be playful.\\r\\nThis is not an instruction to be frivolous or trivial, or to show disrespect to the group or to the texts. It is simply that we have found that discussions work best when the participants feel able to make suggestions about how to read the text, even if they are newcomers to it, and don’t yet know whether their suggestions really make sense. And discussions work best when the participants feel able to ask questions, even if they suspect that the answers might be obvious to other members of the group.\\r\\n\\r\\nThe fourth ground rule is be honest\\r\\nYou are not expected to be an ‘expert’ on your own Scriptures and faith tradition, so be honest about the things you don’t know or understand. You may not agree with other people’s interpretations and it is OK to say so – respectfully. Avoid too much generalisation - it is better to say, ‘As a Christian I think this text means …’ than ‘Christians believe …’.\\r\\n\\r\\nHow might a Scriptural Reasoning discussion work?\\r\\n\\r\\nQuestions of clarification\\r\\n\\r\\nThere’s no fixed format or recipe, but a discussion might start off with simple questions for clarification:\\r\\n\\r\\n•What does this word mean?\\r\\n•Is this text part of a longer narrative?\\r\\n•Who is speaking in this verse?\\r\\n\\r\\nHow participants read their own texts\\r\\nThe discussion might then begin to move on to questions about how Jewish, Christian and Muslims read their respective texts:\\r\\n\\r\\n•So, would you normally read this text as a promise?\\r\\n•How were you taught that this command should be put into practice?\\r\\n•What sort of things have you heard preachers say about this text?\\r\\n•Does this text really get used at marriage ceremonies?\\r\\n\\r\\nAs the participants get into the rhythm of their discussion, the questions might begin to change to be more probing:\\r\\n\\r\\n•Couldn’t you read it this way?\\r\\n•What if you take this not as a promise but as a threat?\\r\\n•Would it mean something different if you assumed it was addressed to someone who was already a believer?\\r\\n\\r\\nRemember, Scriptural Reasoning is meant to be an enjoyable experience, not an ordeal. It is designed to encourage dialogue between members of different faith traditions and nothing that’s said in a discussion is ‘cast in stone’. So relax and enjoy it!\\r\\n\\r\\n© SRonline, Feb 2012",
            \'summary\' => \'\',
            \'format\' => \'filtered_html\',
            \'safe_value\' => "<p>Guidelines for Scriptural Reasoning discussions</p>\\n<p>Here are some ground rules to keep in mind, which can help the Scriptural Reasoning discussion work well:</p>\\n<p>The first and most important ground rule is to stick to the texts.<br />\\nIt is our experience that these discussions are much more fruitful if the discussion remains focused on the scriptural texts and on the ways in which they can be read – rather than spiralling off to become a general discussion of Judaism, Islam and Christianity. Be prepared to answer the question, ‘Where do you see that in the text?’ If you draw from sources other than the passage in question, you should be able to connect them to that particular text.</p>\\n<p>The second ground rule is give space to others’ readings.<br />\\nEven if you have very firm, clear and well-formed ideas about how a particular text should be read (perhaps it is just obvious to you what this text means, or you know other scriptural texts that help interpret this one, or you know authoritative commentaries on the text from your tradition) don’t simply impose that reading on the group. The discussion will work best if the other participants are able to hear about the way you believe the text should be read whilst exploring the text, and other possible ways of reading it, for themselves. That may sometimes mean that you have to sit back for a while, and let a discussion continue that you believe to be mistaken – before finding a way gently to explain to people how and why you read the text the way you do.</p>\\n<p>The third ground rule is be playful.<br />\\nThis is not an instruction to be frivolous or trivial, or to show disrespect to the group or to the texts. It is simply that we have found that discussions work best when the participants feel able to make suggestions about how to read the text, even if they are newcomers to it, and don’t yet know whether their suggestions really make sense. And discussions work best when the participants feel able to ask questions, even if they suspect that the answers might be obvious to other members of the group.</p>\\n<p>The fourth ground rule is be honest<br />\\nYou are not expected to be an ‘expert’ on your own Scriptures and faith tradition, so be honest about the things you don’t know or understand. You may not agree with other people’s interpretations and it is OK to say so – respectfully. Avoid too much generalisation - it is better to say, ‘As a Christian I think this text means …’ than ‘Christians believe …’.</p>\\n<p>How might a Scriptural Reasoning discussion work?</p>\\n<p>Questions of clarification</p>\\n<p>There’s no fixed format or recipe, but a discussion might start off with simple questions for clarification:</p>\\n<p>•What does this word mean?<br />\\n•Is this text part of a longer narrative?<br />\\n•Who is speaking in this verse?</p>\\n<p>How participants read their own texts<br />\\nThe discussion might then begin to move on to questions about how Jewish, Christian and Muslims read their respective texts:</p>\\n<p>•So, would you normally read this text as a promise?<br />\\n•How were you taught that this command should be put into practice?<br />\\n•What sort of things have you heard preachers say about this text?<br />\\n•Does this text really get used at marriage ceremonies?</p>\\n<p>As the participants get into the rhythm of their discussion, the questions might begin to change to be more probing:</p>\\n<p>•Couldn’t you read it this way?<br />\\n•What if you take this not as a promise but as a threat?<br />\\n•Would it mean something different if you assumed it was addressed to someone who was already a believer?</p>\\n<p>Remember, Scriptural Reasoning is meant to be an enjoyable experience, not an ordeal. It is designed to encourage dialogue between members of different faith traditions and nothing that’s said in a discussion is ‘cast in stone’. So relax and enjoy it!</p>\\n<p>© SRonline, Feb 2012</p>\\n",
            \'safe_summary\' => \'\',
          ),
        ),
      ),
      \'rdf_mapping\' => array(
        \'rdftype\' => array(
          \'sioc:Item\',
          \'foaf:Document\',
        ),
        \'title\' => array(
          \'predicates\' => array(
            \'dc:title\',
          ),
        ),
        \'created\' => array(
          \'predicates\' => array(
            \'dc:date\',
            \'dc:created\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'changed\' => array(
          \'predicates\' => array(
            \'dc:modified\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
        \'body\' => array(
          \'predicates\' => array(
            \'content:encoded\',
          ),
        ),
        \'uid\' => array(
          \'predicates\' => array(
            \'sioc:has_creator\',
          ),
          \'type\' => \'rel\',
        ),
        \'name\' => array(
          \'predicates\' => array(
            \'foaf:name\',
          ),
        ),
        \'comment_count\' => array(
          \'predicates\' => array(
            \'sioc:num_replies\',
          ),
          \'datatype\' => \'xsd:integer\',
        ),
        \'last_activity\' => array(
          \'predicates\' => array(
            \'sioc:last_activity_date\',
          ),
          \'datatype\' => \'xsd:dateTime\',
          \'callback\' => \'date_iso8601\',
        ),
      ),
      \'cid\' => \'0\',
      \'last_comment_timestamp\' => \'1360588531\',
      \'last_comment_name\' => NULL,
      \'last_comment_uid\' => \'1\',
      \'comment_count\' => \'0\',
      \'print_display\' => 1,
      \'print_display_comment\' => 0,
      \'print_display_urllist\' => 1,
      \'name\' => \'admin\',
      \'picture\' => \'31\',
      \'data\' => \'a:1:{s:7:"overlay";i:1;}\',
      \'print_pdf_display\' => 1,
      \'print_pdf_display_comment\' => 0,
      \'print_pdf_display_urllist\' => 1,
      \'menu\' => NULL,
      \'path\' => array(
        \'pid\' => \'104\',
        \'source\' => \'node/5\',
        \'alias\' => \'content/how-do-scriptural-reasoning\',
        \'language\' => \'und\',
      ),
      \'node_export_drupal_version\' => \'7\',
    ),
)',
);
  return $node_export;
}
