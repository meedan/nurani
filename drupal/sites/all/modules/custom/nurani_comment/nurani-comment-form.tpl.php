<div class="head">
  <?php echo render($element['info']['picture']); ?>
  <div class="info">
    <p><?php echo render($element['info']['response_number']); ?></p>
    <p><?php echo render($element['info']['by']); ?></p>
  </div>
  <div class="tip">
    <?php echo render($element['info']['tip']); ?>
  </div>
</div>

<?php echo render($element['comment_body']); ?>

<div class="actions">
  <?php echo render($element['actions']); ?>
</div>

<?php unset($element['#theme']); echo render($element); ?>
