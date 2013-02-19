<?php
/**
 * @file
 * nurani_general.menu_block.inc
 */

/**
 * Implements hook_menu_block_defaults().
 */
function nurani_general_menu_block_defaults() {
  $export = array();

  $menu_block = new stdClass();
  $menu_block->disabled = FALSE; /* Edit this to true to make a default menu_block disabled initially */
  $menu_block->api_version = 1;
  $menu_block->name = 'nurani_footer_menu';
  $menu_block->label = 'Nurani footer menu';
  $menu_block->description = '';
  $menu_block->depth = 0;
  $menu_block->expanded = 0;
  $menu_block->follow = '0';
  $menu_block->level = 1;
  $menu_block->parent = 'menu-footer-links:0';
  $menu_block->sort = 0;
  $menu_block->title_link = 0;
  $export['nurani_footer_menu'] = $menu_block;

  $menu_block = new stdClass();
  $menu_block->disabled = FALSE; /* Edit this to true to make a default menu_block disabled initially */
  $menu_block->api_version = 1;
  $menu_block->name = 'nurani_main_menu';
  $menu_block->label = 'Nurani main menu';
  $menu_block->description = '';
  $menu_block->depth = 0;
  $menu_block->expanded = 0;
  $menu_block->follow = '0';
  $menu_block->level = 1;
  $menu_block->parent = 'main-menu:0';
  $menu_block->sort = 0;
  $menu_block->title_link = 0;
  $export['nurani_main_menu'] = $menu_block;

  return $export;
}
