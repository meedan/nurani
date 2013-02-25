#Nurani D6 -> D7 Migration

The nurani_migrate module leverages the Drupal [migrate](http://drupal.org/project/migrate) project to port Drupal 6 data into the new Drupal 7 system. These migrations provide support for:

* Users, including some profile information and pictures
* Discussions
* D6 "Texts", these are migrated into "Bundles" in D7
* D6 "Responses", these are migrated into Discussion comments in D7


## "Texts" to "Bundles" migration

Conversion of the D6 "Text" nodes into D7 "Bundles" is a tricky task. On the D6 site multiple "Text" nodes were attached to a single discussion using the [nodereference](http://drupal.org/project/nodereference) module. As usual with nodereference + CCK, each "Text" node is ordered on the discussion via delta number, eg: $discussion->field_texts[0]['nid'], '0' is the first delta, then '1', etc.

The migration process for "Texts" is as follows:

* The first "Text" (delta '0') attached to each discussion is directly migrated into the D7 "Bundle" node for that discussion.
* This first "Text" *and* subsequent "Texts" (delta '1', '2', etc.) are migrated into the field_passage_collection of the "Bundle".


## D7 "Bundles" field_passage_collection and OSIS references

One major difficulty is migrating the D6 free-form passage information from "Text" nodes into a structured OSIS reference system for D7.

In the end this proved too time-consuming so a manual approach was used. The migration process for free-form passages into OSIS references is:

* Use the query in text_to_bundles.sql to generate a list of all migratable "Texts" and their free-form passage information
* Export that query as TSV (don't use CSV, there are many commas in the free-form passages which cause problems)
* Import the TSV into your favourite editor (I used Google Docs)
* Create an extra two columns, osisIDWork and osisID
* Manually create entries for each osisIDWork and osisID (I used a combination of guesswork, intuition and searching to map most of them. The final ones I needed to have the original "Text" node authors fill in)
* Export a list of "nid" (aka "text_nid"), "osisIDWork", and "osisID" and use a simple script to turn them into the correct format (see NuraniDiscussionBundleMigration.inc). An example of the script I used can be found in text_to_bundles.php.

