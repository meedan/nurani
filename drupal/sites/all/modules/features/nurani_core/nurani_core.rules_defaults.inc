<?php
/**
 * @file
 * nurani_core.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function nurani_core_default_rules_configuration() {
  $items = array();
  $items['rules_nurani_discussion_reminder'] = entity_import('rules_config', '{ "rules_nurani_discussion_reminder" : {
      "LABEL" : "Nurani discussion reminder",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "Nurani" ],
      "REQUIRES" : [ "rules" ],
      "ON" : [ "cron" ],
      "DO" : []
    }
  }');
  $items['rules_nurani_new_discussion'] = entity_import('rules_config', '{ "rules_nurani_new_discussion" : {
      "LABEL" : "Nurani new discussion",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "Nurani" ],
      "REQUIRES" : [ "rules", "meedan_notifications" ],
      "ON" : [ "node_insert" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "discussion" : "discussion" } }
          }
        },
        { "node_is_published" : { "node" : [ "node" ] } }
      ],
      "DO" : [
        { "notify_subscribers" : {
            "object" : [ "node" ],
            "event" : "discussion",
            "subject" : "[node:author:name] has invited you to participate in a new discussion",
            "message" : "Hello [recipient:name]\\r\\n\\r\\n[node:author:name] has just started a new discussion about [node:title] on [site:name].\\r\\n\\r\\nYou can be the first to comment here: [node:url]\\r\\n\\r\\nwe are looking forward to reading your comments!\\r\\n\\r\\nWe are testing the site and trying our best to improve it as much as possible, so we would appreciate it if you leave us feedback at [site:mail]\\r\\n\\r\\nThanks,\\r\\nThe [site:name] team.",
            "actor" : "[node:author:uid]"
          }
        }
      ]
    }
  }');
  $items['rules_nurani_new_discussion_response'] = entity_import('rules_config', '{ "rules_nurani_new_discussion_response" : {
      "LABEL" : "Nurani new discussion response",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "Nurani" ],
      "REQUIRES" : [ "rules", "meedan_notifications", "comment" ],
      "ON" : [ "comment_insert" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "comment:node" ],
            "type" : { "value" : { "discussion" : "discussion" } }
          }
        },
        { "node_is_published" : { "node" : [ "comment:node" ] } }
      ],
      "DO" : [
        { "notify_subscribers" : {
            "object" : [ "comment" ],
            "event" : "comment",
            "subject" : "[comment:author:name] has just responded on [comment:node:title] on [site:name]",
            "message" : "Dear [recipient:name],\\r\\n\\r\\n[comment:author:name] has just posted a new response to [site:name] on [comment:node:title]. \\r\\n\\r\\nyou can be the first to reply here: [comment:node:url]\\r\\n\\r\\nwe look forward to hearing what you have to say.\\r\\n\\r\\nThanks,\\r\\nThe [site:name] team.\\r\\n",
            "actor" : "[comment:author:uid]"
          }
        }
      ]
    }
  }');
  return $items;
}
