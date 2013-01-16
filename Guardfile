# see https://github.com/guard/guard#readme

guard 'compass' do
  watch(%r{^sass/(.*)\.s[ac]ss})
end

guard 'livereload', :latency => '0.1', :host => '127.0.0.1', :api_version => '2.0.9', :port => '35729', :apply_css_live => true  do
  watch(%r{^css/(.*)\.css})
end