<?php if (isset($page['top_strip'])): ?>
  <div id="top-strip">
    <?php print render($page['top_strip']); ?>
  </div>
<?php endif; ?>

<div id="page" class="<?php print $classes; ?>"<?php print $attributes; ?>>

  <!-- ______________________ HEADER _______________________ -->

  <div id="header">

    <?php if (isset($logo)): ?>
      <div id="logo-box">
        <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo">
          <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>"/>
        </a>
      </div>
    <?php endif; ?>

    <?php if (isset($site_name) || isset($site_slogan)): ?>
      <div id="name-and-slogan">

        <?php if (isset($site_name)): ?>
          <?php if (isset($title)): ?>
            <div id="site-name">
              <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><?php print $site_name; ?></a>
            </div>
          <?php else: /* Use h1 when the content title is empty */ ?>
            <h1 id="site-name">
              <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><?php print $site_name; ?></a>
            </h1>
          <?php endif; ?>
        <?php endif; ?>

        <?php if (isset($site_slogan)): ?>
          <div id="site-slogan"><?php print $site_slogan; ?></div>
        <?php endif; ?>

      </div>
    <?php endif; ?>

    <?php if (isset($page['header'])): ?>
      <div id="header-region">
        <?php print render($page['header']); ?>
      </div>
    <?php endif; ?>

  </div> <!-- /header -->

  <!-- ______________________ MAIN _______________________ -->

  <div id="main" class="clearfix">

    <div id="content">
      <div id="content-inner" class="inner column center">

        <?php if (isset($breadcrumb) || isset($title)|| isset($messages) || isset($tabs) || isset($action_links)): ?>
          <div id="content-header">

            <?php print $breadcrumb; ?>

            <?php if (isset($page['highlight'])): ?>
              <div id="highlight"><?php print render($page['highlight']) ?></div>
            <?php endif; ?>

            <?php if (isset($title)): ?>
              <h1 class="title"><?php print $title; ?></h1>
            <?php endif; ?>

            <?php print render($title_suffix); ?>
            <?php print $messages; ?>
            <?php print render($page['help']); ?>

            <?php if (isset($tabs)): ?>
              <div class="tabs"><?php print render($tabs); ?></div>
            <?php endif; ?>

            <?php if (isset($action_links)): ?>
              <ul class="action-links"><?php print render($action_links); ?></ul>
            <?php endif; ?>
            
          </div> <!-- /#content-header -->
        <?php endif; ?>

        <div id="content-area">
          <?php print render($page['content']) ?>
         <!--  <?php print render($page['content_bottom']) ?> -->
        </div>
        <div id="content-bottom">
          <div id="content-bottom-left"><?php print render($page['content_bottom_left']) ?></div>
          <div id="content-bottom-right"><?php print render($page['content_bottom_right']) ?></div>
        </div>

        <?php print $feed_icons; ?>

      </div>
    </div> <!-- /content-inner /content -->

    <?php if (isset($main_menu) || isset($secondary_menu)): ?>
      <div id="navigation" class="menu <?php if (!empty($main_menu)) {print "with-primary";} if (!empty($secondary_menu)) {print " with-secondary";} ?>">
        <!--<?php print theme('links', array('links' => $main_menu, 'attributes' => array('id' => 'primary', 'class' => array('links', 'clearfix', 'main-menu')))); ?> -->
        <!--<?php print theme('links', array('links' => $secondary_menu, 'attributes' => array('id' => 'secondary', 'class' => array('links', 'clearfix', 'sub-menu')))); ?> -->
      </div>
    <?php endif; ?>

    <?php if (isset($page['sidebar_first'])): ?>
      <div id="sidebar-first" class="column sidebar first">
        <div id="sidebar-first-inner" class="inner">
          <?php print render($page['sidebar_first']); ?>
        </div>
      </div>
    <?php endif; ?> <!-- /sidebar-first -->

    <?php if (isset($page['sidebar_second'])): ?>
      <div id="sidebar-second" class="column sidebar second">
        <div id="sidebar-second-inner" class="inner">
          <?php print render($page['sidebar_second']); ?>
        </div>
      </div>
    <?php endif; ?> <!-- /sidebar-second -->

  </div> <!-- /main -->

  <!-- ______________________ FOOTER _______________________ -->

  <?php if (isset($page['footer'])): ?>
    <div id="footer">
      <div class="footer footer-logos">
         <a href="http://www.interfaith.cam.ac.uk/"><img src="<?php print base_path() . path_to_theme() . '/' . 'images/CIP.png'; ?>" alt="University of Cambridge Logo" /></a>
          <img src="<?php print base_path() . path_to_theme() . '/' . 'images/rcuk.png'; ?>" alt="Digital Economy Logo" />
          <a href="http://meedan.org"><img src="<?php print base_path() . path_to_theme() . '/' . 'images/meedan-fade2.png'; ?>" alt="Meedan Logo" /></a>
          <a href="http://www.coexistfoundation.net/"><img src="<?php print base_path() . path_to_theme() . '/' . 'images/coexist-fade.png'; ?>" alt="Meedan Logo" /></a>
      </div>
      <?php print render($page['footer']); ?> 
    </div> <!-- /footer -->
  <?php endif; ?>

</div> <!-- /page -->
