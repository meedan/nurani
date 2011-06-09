<?php if ($results) : ?>
<ul class="glossary-references">
<?php foreach ($results as $term) : ?>
<li class="glossary-reference">
<?php print l($term->title, 'node/' . $term->nid) ?>
</li>
<?php endforeach ?>
</ul>
<?php endif ?>
