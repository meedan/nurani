<?php
/**
 * @file nurani-profile-tooltip-user-profile.tpl.php
 * Default theme implementation for Nurani Profile user_profile tooltip.
 *
 * Available variables:
 * - $account: The user account.
 *
 * @see template_preprocess_nurani_profile_tooltip_user_profile()
 */
?>
<div class="user-profile">
  <div class="user-picture">
    <?php echo $user_picture; ?>
  </div>

  <h4><?php echo $account->name; ?></h4>
</div>