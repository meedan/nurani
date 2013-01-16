#!/usr/bin/env ruby
require 'sinatra'
require 'rack'
require 'rack/contrib/try_static'

use Rack::TryStatic,
    :root => ".", :urls => %w[/], :try => ['Readings.html']
