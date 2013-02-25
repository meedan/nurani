<?php

/**
 * Assumes user pictures are already inside the sites/default/files/pictures
 * folder and creates {file_managed} records accordingly.
 */
class NuraniUserPicturesMigration extends NuraniMigration {
  public function __construct() {
    parent::__construct();

    $this->pictures_path = 'public://' . variable_get('user_picture_path', 'pictures');

    $this->description = t('User pictures');

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'picture' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
          'description' => 'Image URI.'
        )
      ),
      MigrateDestinationFile::getKeySchema()
    );

    $query = $this
               ->d6Connection
               ->select('users', 'u')
               ->fields('u', array('picture'))
               ->isNotNull('picture')
               ->condition('picture', '', '!=')
               ->orderBy('u.uid');
    $query->distinct();
    $this->source = new MigrateSourceSQL($query, array(), null, array('map_joinable' => false));

    $this->destination = new MigrateDestinationFile();

    // Just map the incoming URL to the destination's 'uri'
    $this->addFieldMapping('value', 'picture')->callbacks(array($this, 'path_to_uri'));
    $this->addUnmigratedDestinations(array('fid', 'uid', 'timestamp',
      'destination_dir', 'destination_file', 'source_dir', 'preserve_files',
      'file_replace'));
    $this->removeFieldMapping('path');
    $this->removeFieldMapping('pathauto');

  }

  public function path_to_uri($path) {
    return $this->pictures_path . '/' . str_replace('sites/default/files/pictures/', '', $path);
  }
}
