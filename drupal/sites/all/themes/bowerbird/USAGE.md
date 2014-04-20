#Bowerbird Usage

##Short version

1. Copy the boilerplate included with Bowerbird, eg:

		cd sites/all/themes
		cp -r bowerbird/boilerplate mytheme
		mv mytheme/boilerplate.info mytheme/mytheme.info

2. Edit the mytheme.info file as needed


##Manual version

1. Create a directory in sites/all/themes for your theme (eg: mytheme)
2. Create a .info file for your theme.  Make sure it looks like this!!!

		name = My Theme
		description = "A Bowerbird based Meedan child theme"
		core = "7.x"
		engine = phptemplate
		base theme = bowerbird
		
		;; Put custom CSS stylesheets here
		; eg: stylesheets[all][] = css/mytheme.css

3. Create a config.rb file for your theme, ensure it contains:

		load '../bowerbird/framework'
		
		# Set this to the root of your project when deployed:
		http_path = "/"
		css_dir = "css"
		sass_dir = "scss"
		images_dir = "images"
		javascripts_dir = "js"
