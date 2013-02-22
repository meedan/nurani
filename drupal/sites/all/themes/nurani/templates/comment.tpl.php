<div class="<?php print $classes . ' ' . $zebra; ?>">
  <div class="comment-number ">
    <span><?php echo $comment_number; ?></span>
  </div>

  <div class="comment-inner">

    <!-- <h3 class="title"><?php print $title ?></h3> -->
    <?php if (isset($new) && $new) : ?>
        <span class="new"><?php print drupal_ucfirst($new) ?></span>
    <?php endif; ?>

    <?php print $picture ?>

    <div class="content">
      <?php
        hide($content['links']);
        print render($content);
        ?>

      <?php echo theme('nurani_attribution', array('account' => user_load($comment->uid), 'timestamp' => $comment->created)); ?>
    </div>

    <?php if (!empty($content['links'])): ?>
      <div class="links"><?php print render($content['links']); ?></div>
    <?php endif; ?>

  </div> <!-- /comment-inner -->
</div> <!-- /comment -->
