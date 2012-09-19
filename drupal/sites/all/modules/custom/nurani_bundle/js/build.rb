#!/usr/bin/env ruby
#
# Build tool for combining the nurani_bundle_ui.js JavaScript files.
#
# Usage: ruby build.rb
# Author: James Andres
#
require 'fileutils'

@root = File.expand_path(File.dirname(__FILE__))

@src_files = [
  "src/drupal-integration.js",
  "src/Util.js",
  "src/BundleUI.js",
  "src/CloneBundle.js",
  "src/PassageBox.js",
  "src/Picker.js",
]
@out_file = "nurani_bundle_ui.js"

@prefix  = "(function ($) {\n\n"
@prefix += "  // paulirish.com/2009/log-a-lightweight-wrapper-for-consolelog/\n"
@prefix += "  var log = function f(){ log.history = log.history || []; log.history.push(arguments); if(this.console) { var args = arguments, newarr; args.callee = args.callee.caller; newarr = [].slice.call(args); if (typeof console.log === 'object') log.apply.call(console.log, console, newarr); else console.log.apply(console, newarr);}};\n\n";
@suffix  = "})(jQuery);"

# Ensure the out_file exists and has zero bytes
out_file = File.join(@root, @out_file)
FileUtils.touch(out_file)
File.truncate(out_file, 0)

puts "Building #{File.join(@root, @out_file)} .."

# Write out the prefix, the contents of each src file and the suffix
File.open(out_file, 'a') do |f|
  f << @prefix

  @src_files.each do |file|
    path = File.join(@root, file)
    contents = File.open(path, 'rb').read

    # Indent all non-empty lines by 2 spaces (prettiness), add an extra newline
    contents.gsub!(/^(?!\n)/, '  ')

    f << contents + "\n"
  end

  f << @suffix
end
