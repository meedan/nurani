<?php if ($results) : ?>
<div class="glossary-search-results">
<h2><?php print $title ?></h2>
<?php foreach ($results as $result) : ?>
<div class="glossary-search-result">
<div class="field-title">
<?php print l($result['node']->title, 'node/' . $result['node']->nid) ?>
</div>
<div class="field-snippets">
<?php foreach ($result['snippet'] as $snippet) : ?>
<div class="field-snippet">
<?php print $snippet ?>
</div>
<?php endforeach ?>
</div>
</div>
<?php endforeach ?>
</div>
<?php else : ?>
<?php endif ?>
