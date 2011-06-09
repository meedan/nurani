Nodereference Explorer README
---------------------------------------

The Nodereference Explorer (NRE) provides a selection dialog for creating references between nodes. Editors can link arbitrary 
content type instances, e. g. pages, stories, news, images etc., with each other. Typical use-cases are for instance:

    * Reuse of assets, such as images, audio and video clips for display on other pages
    * Providing a list of internal links

The motivation arouses from the usage scalabiltiy limitations of in-built nodereferences widgets, i. e. autocomplete, select list and 
option boxes, when dealing with a large number of nodes. Therefore the NRE enhances the autocomplete widget by an explorer-like selection
dialog. It contains several view displays and optionally exposed filters where list items can be selected via mouse click.


Features
--------

The Nodereference Explorer is a high-level rich widget improving strongly CCK's content editing/referencing usabilty and is highly
configurable at the same time. The most important features are:

* Themable jQuery dialog with list of nodes for selection as nodereferences
* Node list is a customizable view with various displays, like grid, table, list and unformatted containing selectable view items
* Exposed view filter forms for content search/exploration
* Simple mouse point and click selection
* Field preview (as an additional view display)
* Plugin architecture for support of other CCK fields, e. g. Link
* Different Dialog APIs:
    o Built-in
    o Modal Frame (recommended since version 1.1), see http://drupal.org/project/modalframe
* Integrated third party modules:
    o Popups: Add & Reference
    o Flexifield
* Leveraging indirectly the power of views:
    o Multilinguality
    o Image, Imagefield, Imagecache compatiblity
    o Lightbox or thickbox support
    o ... and much more


Installation & Updating Guide
-----------------------------

You just have to enable the Nodererence Explorer module and its dependent modules. 

It is recommended that you use the "Modalframe" dialog API including the onbeforeunload module, as "built-in" is deprecated since version 1.1. 

NRE is compatible with the jQuery UI 1.6 and 1.7 JS libraries which are attached to your jquery_ui module. The underlying module 
configuration varies, therefore here some important notes:

* jQuery UI 1.6 MAY optionally use jquery_update 6.x-1.x (jQuery 1.2.6)
  Modalframe version 1.6 or lower

* jQuery UI 1.7 REQUIRES jquery_update 6.x-2.x (jQuery 1.3)
  Modalframe version 1.7 or higher

When you update the module you should always flush Drupal's and your browser's cache!


Administration Guide
--------------------

The NRE is basically an additional CCK field widget embedding a referenced View into a selection dialog. Therefore the configuration is two-fold: 

Views:

The default view is called "nodereference_explorer_default". If you want to have custom fields and filters (you probably will) you should clone
this view. The View's output is embedded into the content area of the selection dialog and nodes are selectable in this context. In the CCK field 
settings you can reference the view (see CCK).

When you customize your view, don't run into issue http://drupal.org/node/921292. Concerning exposed filters do the following:

- Set up exposed filters in Default display as you like
- Override any single filter exposed filter in any display
- Remove the exposed filters from the Defaults display

Apart from you can treat the NRE view as a normal view!


CCK:

1. Adding a new explorer widget: Go to "Manage fields" of your CCK's content types settings, e. g. "admin/content/node-type/page/fields". Select
   as field "nodereference" or "link" and as widget "Explorer".
2. Field settings:
   a. Content: Choose the field preview display from the list the displays (depends on choosen View)
   b. Dialog: Specify dialog related settings here, e. g. title or window size. It is recommended that you select "Modalframe"
      as your dialog API. Choose a dialog theme from the available options. Note that you might specify a CSS scope for certain themes.
3. Global settings (two possibilities):
   a. Content types that can be referenced: A default view shipped with the module will be referenced with
   	  three displays: table, grid and list. Use this as a starting point for your custom view.
   b. View used to select the nodes: A customized view can be referenced here. Be aware to create a view with 
   	  displays having a table (selectable) or fields (selectable) plugin. Otherwise view items cannot be selected
   	  visually and logically. Note that the default display will not be rendered.
4. Finally, save the field and widget settings.

  
Usage Guide
-----------

When creating or editing existing content you will face additional buttons near the configured fields in the node edit form. 

1. Click on "Browse" to open the dialog
2. Apply any filters located at the top of the dialog area
3. Move your mouse over the items and select an item by a simple mouse click
4. Confirm the selection by clicking the "OK" button at the bottom of the dialog

You can discard references by clicking the "Remove" button.


TO-DOs:
-----------------
* In built "Add & Reference" functionality
* Multiple selection
* Integration with WYSIWIG editors
* Universial CCK browser: Deploy and use the explorer widget on any field type
* Use outside of CCK context
	* Integration with WYSIWIG editors
	* Taxonomy browser
* Port to Drupal 7 (and then into the Drupal core of course :))


Authors
-------
Gottfried Nindl (gnindl: http://drupal.org/user/421442), Web Developer, OSCE (Organisation for Security and Cooperation in Europe)
Velimir Alic (valic: http://drupal.org/user/406104), Web Architect, OSCE (Organisation for Security and Cooperation in Europe)
Benjamin J Doherty (bangpound: http://drupal.org/user/100456)