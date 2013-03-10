# A sample Guardfile
# More info at https://github.com/guard/guard#readme

guard 'process', :name => 'build', :dir => 'drupal/sites/all/modules/custom/nurani_bundle/js', :command => 'ruby ./build.rb', :stop_signal => "KILL" do
  watch(%r{^drupal/sites/all/modules/custom/nurani_bundle/js/(.+)\.js$})
end


## Compass is broken currently
# guard 'compass' do
#   watch(%r{^drupal/sites/all/modules/custom/nurani_bundle/css/(.*)\.s[ac]ss})
#   watch(%r{^drupal/sites/all/modules/custom/nurani_profile/css/(.*)\.s[ac]ss})
#   watch(%r{^drupal/sites/all/themes/bowerbird/(.*)\.s[ac]ss})
#   watch(%r{^drupal/sites/all/themes/nurani/(.*)\.s[ac]ss})
# end

guard 'process', :name => 'compass compile', :dir => 'drupal/sites/all/modules/custom/nurani_bundle/css', :command => 'compass compile', :stop_signal => "KILL" do
  watch(%r{^drupal/sites/all/modules/custom/nurani_bundle/css/(.*)\.s[ac]ss})
end

guard 'process', :name => 'compass compile', :dir => 'drupal/sites/all/modules/custom/nurani_helpers/css', :command => 'compass compile', :stop_signal => "KILL" do
  watch(%r{^drupal/sites/all/modules/custom/nurani_helpers/css/(.*)\.s[ac]ss})
end

guard 'process', :name => 'compass compile', :dir => 'drupal/sites/all/modules/custom/nurani_profile/css/', :command => 'compass compile', :stop_signal => "KILL" do
  watch(%r{^drupal/sites/all/modules/custom/nurani_profile/css/(.*)\.s[ac]ss})
end

guard 'process', :name => 'compass compile', :dir => 'drupal/sites/all/themes/bowerbird', :command => 'compass compile', :stop_signal => "KILL" do
  watch(%r{^drupal/sites/all/themes/bowerbird/(.*)\.s[ac]ss})
end

guard 'process', :name => 'compass compile', :dir => 'drupal/sites/all/themes/nurani', :command => 'compass compile', :stop_signal => "KILL" do
  watch(%r{^drupal/sites/all/themes/nurani/(.*)\.s[ac]ss})
end
