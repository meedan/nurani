#Bowerbird Compass Framework

Shared SCSS partials available to sub-themes.


## Usage

1. In your sub-theme's config.rb file include a line like this:

         load '../bowerbird/framework'

2. In your sub-theme's SCSS file utilize the framework like this:

         @import "bowerbird";
         @import "bowerbird/basic";

         // Example: 1200px wide side with 400px first sidebar and
         //          300px second sidebar.
         @include basic-default(1200px, 400px, 300px);
