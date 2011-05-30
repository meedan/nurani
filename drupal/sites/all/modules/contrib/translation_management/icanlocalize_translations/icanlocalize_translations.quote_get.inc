<?php

/**
 * Main function
 */
function icanlocalize_translations_quote_get() {

  // Set data (cached and posted)
  $cache = variable_get('icl_quote_get', $_POST);
  if (!isset($cache['step'])) {
    $step = 1;
  } else {
    $step = $cache['step'];
  }
  if (isset($_POST['next'])) {
    $step += 1;
    $_POST['step'] = $step;
  } else if (isset($_POST['back'])) {
    $step -= 1;
    $_POST['step'] = $step;
  }
  $cache = array_merge($cache, $_POST);
  variable_set('icl_quote_get', $cache);

  // Process if submitted
  if (isset($_POST['submit-for-later']) || isset($_POST['submit-produce'])) {
    _icanlocalize_translations_quote_get_submit($cache);
  }

  // Render form
?>
  <script type="text/javascript">
    jQuery(document).ready(function(){
      jQuery('.icl-quote-get-next').click(function(){
        jQuery(this).parent().parent().fadeOut('fast', function(){
          jQuery(this).next('div').fadeIn();
        });
      });
      jQuery('.icl-quote-get-back').click(function(){
        jQuery(this).parent().parent().fadeOut('fast', function(){
          jQuery(this).prev('div').fadeIn();
        });
      });
      iclQuoteGetCheckContentCb();
      jQuery('#icl-quote-get-form').ajaxForm({target:'#icl-quote-get-wrap'});
    });
    function iclQuoteGetSetSelectLangs() {
      if (jQuery('#icl-quote-get-from').val() == 0) {
        jQuery('.icl-quote-get-toggle-to').fadeOut();
        jQuery('.icl-quote-get-to').attr('checked', 0);
        iclQuoteGetCheckFromTo();
        return false;
      }
      jQuery('.icl-quote-get-toggle-to').fadeIn();
      jQuery('#icl-quote-get-to-'+jQuery('#icl-quote-get-from').val()).attr('checked', 0).parent().hide(0,
      function(){
        iclQuoteGetCheckFromTo();
      }
    );
      jQuery('.icl-quote-get-to').not('#icl-quote-get-to-'+jQuery('#icl-quote-get-from').val()).parent().show();
      iclQuoteGetCheckFromTo();
    }
    function iclQuoteGetCheckFromTo() {
      var enable = false;
      jQuery('.icl-quote-get-to').each(function(){
        if (jQuery(this).is(':checked')) {
          enable = true;
        }
      });
      if (jQuery('#icl-quote-get-from').val() == 0) {
        enable = false;
      }
      if (enable) {
        jQuery('#icl-quote-next-1').attr('disabled', 0);
      } else {
        jQuery('#icl-quote-next-1').attr('disabled', 1);
      }
    }
    function iclQuoteGetCheckContentCb() {
      var enable = false;
      jQuery('.icl-quote-get-content-checbox').each(function(){
        if (jQuery(this).is(':checked')) {
          enable = true;
        }
      });
      if (enable) {
        jQuery('#icl-quote-next-2').attr('disabled', 0);
      } else {
        jQuery('#icl-quote-next-2').attr('disabled', 1);
      }
    }
  </script>
  <div id="icl-quote-get-wrap" style="margin-top: 20px;">
    <form id="icl-quote-get-form" action="<?php echo url('icl-translations/quote-get'); ?>" method="post">
    <?php
    // Include form steps
    switch ($step) {
      case 1:
        _icanlocalize_translations_quote_get_form_step_one($cache);
        break;

      case 2:
        _icanlocalize_translations_quote_get_form_step_two($cache);
        break;

      case 3:
        _icanlocalize_translations_quote_get_form_step_three($cache);
        break;

      default:
        break;
    }
    ?>
  </form>
</div>
<?php
  }

  /**
   * 'From' and 'to' language select
   * 
   * @param array $saved Cached data
   */
  function _icanlocalize_translations_quote_get_form_step_one($saved) {
    $languages = language_list('enabled');
    $languages = $languages[1];
?>
    <input type="hidden" name="step" value="1" />
    <h1><?php echo t('Translation Languages'); ?></h1>
    <p>
      <label><?php echo t('I need translation from'); ?>
        <select id="icl-quote-get-from" name="from" onchange="iclQuoteGetSetSelectLangs();">
          <option value="0"><?php echo t('Select Language'); ?>&nbsp;</option>
      <?php
      foreach ($languages as $code => $language) {
      ?>
        <option value="<?php echo $language->language; ?>"><?php echo $language->name; ?></option>
      <?php
      }
      ?>
    </select>
  </label>
  <br />
  <?php echo t('to these languages:'); ?>
  <?php
      foreach ($languages as $code => $language) {
        $selected = is_array($saved['to']) && in_array($code, $saved['to']) ? ' checked="checked"' : '';
  ?>
      <div class="icl-quote-get-toggle-to" style="display:none;">
        <label><input type="checkbox" name="to[<?php echo $language->language; ?>]" onclick="iclQuoteGetCheckFromTo();" value="<?php echo $language->language; ?>" class="icl-quote-get-to" id="icl-quote-get-to-<?php echo $language->language; ?>"<?php echo $selected; ?> />&nbsp;<?php echo $language->name; ?><br /></label>
      </div>
<?php
      }
?>
      </p>
      <p>
        <input type="submit" id="icl-quote-next-1" value="<?php echo t('Continue'); ?>" name="next" disabled="disabled" class="button-secondary icl-quote-get-next" />
      </p>
<?php
    }

    /**
     * Content types, blocks, contact form... summary table
     * 
     * @param array $saved Cached data
     */
    function _icanlocalize_translations_quote_get_form_step_two($saved) {

      // Get nodes

      $types = _icl_content_translatable_node_types();
      foreach ($types as $key => $name) {
        $nodes = icl_content_get_nodes_for_dashboard(array(
            'language' => language_default('language'),
            'translation' => 'update',
            'type_enabled' => 1,
            'type_type' => $name,
          ));
        $type_title = _icl_wrapper_db_result(_icl_wrapper_db_query(
              "SELECT name FROM {node_type} WHERE type='%s'", $name));
        $rows['nodes-' . $name]['ID'] = $name;
        $rows['nodes-' . $name]['title'] = $type_title;
        $rows['nodes-' . $name]['num'] = count($nodes);
        $rows['nodes-' . $name]['words'] = 0;
        if (!empty($nodes)) {
          foreach ($nodes as $node) {
            $node = node_load($node['id']);
            $rows['nodes-' . $name]['words'] += intval(icl_content_get_words_in_node($node));
          }
        }
      }

      // Get blocks
      
      $blocks = icl_content_get_blocks_for_dashboard(array(
          'language' => language_default('language'),
          'translation' => 'update',
        ));
      $rows['blocks']['ID'] = 'blocks';
      $rows['blocks']['title'] = t('Blocks');
      $rows['blocks']['num'] = count($blocks);
      $rows['blocks']['words'] = 0;
      if (!empty($blocks)) {
        foreach ($blocks as $block) {
          $block = _icl_wrapper_block_box_get(substr($block['id'], 6));
          $block_data = _icl_content_extract_block($block);
          $rows['blocks']['words'] += icl_content_get_words_in_data($block_data);
        }
      }

      // Get contact form

      $rows['cf']['ID'] = 'contact_form';
      $rows['cf']['title'] = t('Contact Form');
      $rows['cf']['num'] = 1;
      $rows['cf']['words'] = icl_content_get_words_in_data(_icl_content_extract_standard_contact_form());

      // Render table
?>
      <h1><?php echo t('Content Types'); ?></h1>
      <p>
  <?php printf(t('Your site includes different kinds of content items. Choose which types to include in the quote. <br /><br />To get the word count of specific documents, use the %sTranslation Dashboard%s.'),
        '<a href="/' . _icl_wrapper_get_root_menu('translation-management/dashboard') . '">', '</a>'); ?>
    </p>
    <input type="hidden" name="step" value="2" />
    <table border="0" cellpadding="5" cellspacing="15" class="widefat" style="margin-top: 15px;">
      <thead>
        <tr>
          <th></th>
          <th><?php echo t('Type'); ?></th>
          <th><?php echo t('Number of items'); ?></th>
          <th><?php echo t('Number of words'); ?></th>
        </tr>
      </thead>
      <tbody>
    <?php
      foreach ($rows as $type => $data) {
        $selected = is_array($saved['content']) && array_key_exists($data['ID'], $saved['content']) ? ' checked="checked"' : '';
    ?>
        <tr>
          <td>
            <input type="checkbox" name="content[<?php echo $data['ID']; ?>]" value="1" class="icl-quote-get-content-checbox" onclick="iclQuoteGetCheckContentCb();"<?php echo $selected; ?> />
            <input type="hidden" name="description[<?php echo $data['ID']; ?>][title]" value="<?php echo $data['title']; ?>" />
            <input type="hidden" name="description[<?php echo $data['ID']; ?>][num]" value="<?php echo $data['num']; ?>" />
            <input type="hidden" name="description[<?php echo $data['ID']; ?>][words]" value="<?php echo $data['words']; ?>" />
          </td>
          <td><?php echo $data['title']; ?></td>
          <td><?php echo $data['num']; ?></td>
          <td><?php echo $data['words']; ?></td>
        </tr>
    <?php
      }
    ?>
    </tbody>
  </table>
  <p>
    <input type="submit" id="icl-quote-back-1" value="<?php echo t('Back'); ?>" name="back" class="button-secondary icl-quote-get-back" />
    <input type="submit" id="icl-quote-next-2" value="<?php echo t('Continue'); ?>" name="next" disabled="disabled" class="button-secondary icl-quote-get-next" />
  </p>
<?php
    }

    /**
     * Submit or save for later
     *
     * @param array $saved Cached data
     */
    function _icanlocalize_translations_quote_get_form_step_three($saved) {
      if ($saved['content']) {

        // Set description
        
        $wc_description = array();
        foreach ($saved['content'] as $ID => $true) {
          $wc_description[] = $saved['description'][$ID]['num'] . ' '
            . $saved['description'][$ID]['title'] . ' with '
            . $saved['description'][$ID]['words'] . ' words';
        }

        // Render table
?>
        <h1><?php echo t('Summary'); ?></h1>
        <br />
<?php echo t('You have selected the following content:'); ?>
        <br /><br />
        <ul style="list-style: square; margin-left: 15px;">
          <li><?php echo implode('</li><li>', $wc_description); ?></li>
        </ul>
        <input type="hidden" name="step" value="3" />
        <p>
          <input type="submit" id="icl-quote-back-2" value="<?php echo t('Back'); ?>" name="back" class="button-secondary icl-quote-get-back" />
          <input type="submit" value="<?php echo t('Produce Quote'); ?>" name="submit-produce" id="icl-quote-get-submit-produce" class="button-primary" />
          <input type="submit" value="<?php echo t('Save for later'); ?>" name="submit-for-later" id="icl-quote-get-submit-for-later" class="button-secondary" />
        </p>
<?php
      }
    }

    /**
     * Process submitted data and display quote
     */
    function _icanlocalize_translations_quote_get_submit($saved) {
      if (isset($_POST['submit-for-later'])) {
        echo '<script type="text/javascript">jQuery(\'#TB_closeWindowButton\').trigger(\'click\');</script>';
        exit;
      }
      if (empty($saved['from']) || empty($saved['to'])
        || empty($saved['content'])
      ) {
          echo 'data not valid';
          return FALSE;
      }
      $word_count = 0;
      $wc_description = array();
      foreach ($saved['content'] as $ID => $true) {
          $wc_description[] = $saved['description'][$ID]['num'] . ' '
                  . $saved['description'][$ID]['title'] . ' with '
                  . $saved['description'][$ID]['words'] . ' words';
          $word_count += intval($saved['description'][$ID]['words']);
      }
      $wc_description = implode(', ', $wc_description);

      $data['word_count'] = $word_count;
      $data['wc_description'] = $wc_description;
      $data['site_id'] = $site_id = variable_get('icl_core_website_id', FALSE);
      $data['accesskey'] = $accesskey = variable_get('icl_core_accesskey', FALSE);
      $data['ignore_languages'] = 1;

      if (!$site_id) {
        icl_core_create_anon_account($data);
        $site_id = variable_get('icl_core_website_id', FALSE);
        $accesskey = variable_get('icl_core_accesskey', FALSE);
        if (!$site_id) {
          echo t('An unknown error has occurred when communicating with the ICanLocalize server. Please try again.');
          return FALSE;
        }
      } else {
        if (is_string(icl_core_update_account($data))){
          echo t('An unknown error has occurred when communicating with the ICanLocalize server. Please try again.');
          return FALSE;
        }
      }

      /**
       * Set URL query
       */
      $languages = language_list('enabled');// print_r($languages); exit;
      $languages = $languages[1];
      $language_pairs = array($saved['from'] => $saved['to']);
      $incr = 1;
      $query = '';
      if (isset($language_pairs)) {
          foreach ($language_pairs as $k => $v) {
              $query .= '&to_lang_num=' . count($v);
              $query .= '&from_language_name=' . $languages[$k]->name;
              foreach ($v as $k => $v) {
                  $query .= '&to_language_name_' . $incr . '=' . $languages[$k]->name;
                  $incr++;
              }
          }
      }
      $url = variable_get ( 'icl_core_mode', ICL_MODE_PRODUCTION ) == ICL_MODE_PRODUCTION ? ICL_PRODUCTION_URL : ICL_SANDBOX_URL;
      $url .= '/websites/' . $site_id . '/quote?accesskey=' . $accesskey . '&locale=' . language_default('language') . $query . '&compact=1';
      // Call reopen JS
      echo '<script type="text/javascript">iclThickboxReopen(\'' . $url . '\');</script>';
      exit;
    }