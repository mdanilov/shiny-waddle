# frozen_string_literal: true

require 'getoptlong'
require 'ostruct'
require 'fileutils'

opts = GetoptLong.new(
  ['--help', '-h', GetoptLong::NO_ARGUMENT],
  ['--num-readers', GetoptLong::OPTIONAL_ARGUMENT],
  ['--num-writers', GetoptLong::OPTIONAL_ARGUMENT],
  ['--num-items', GetoptLong::OPTIONAL_ARGUMENT]
)

def help
  <<~EOF
    ruby generate_test.rb [OPTION] ... DIR

    Generates `executor` configuration

    --help, -h:
      show help

    --num-readers [number]:
      number of readers in config

    --num-writers [number]:
      number of writers in config

    --num-items [number]:
      number of items in config

    DIR: The directory where config will be generated.
  EOF
end

options = OpenStruct.new
options.num_readers = 10
options.num_writers = 2
options.num_items = 1000

opts.each do |opt, arg|
  case opt
  when '--help'
    puts help
    exit(0)
  when '--num-readers'
    options.num_readers = arg.to_i
  when '--num-writers'
    options.num_writers = arg.to_i
  when '--num-items'
    options.num_items = arg.to_i
  end
end

options.output_dir = ARGV.shift

FileUtils.mkdir_p options.output_dir

readers_config = File.join(options.output_dir, "Reader.txt")
File.open(readers_config, 'w') do |file|
  (1..options.num_readers).each do |reader_id|
    file.puts "Reader#{reader_id}.txt"
    reader_config = File.join(options.output_dir, "Reader#{reader_id}.txt")
    File.open(reader_config, 'w') do |reader_file|
      (1..(options.num_items * 10)).each do
        reader_file.puts rand(1..(options.num_items / reader_id)).to_s
      end
    end
  end
end

writers_config = File.join(options.output_dir, "Writer.txt")
File.open(writers_config, 'w') do |file|
  (1..options.num_writers).each do |writer_id|
    file.puts "Writer#{writer_id}.txt"
    writer_config = File.join(options.output_dir, "Writer#{writer_id}.txt")
    File.open(writer_config, 'w') do |writer_file|
      (1..options.num_items).each do
        writer_file.puts "#{rand(1..options.num_items)} #{writer_id}"
      end
    end
  end
end

items_config = File.join(options.output_dir, "Items.txt")
File.open(items_config, 'w') do |file|
  (1..options.num_items).each { |i| file.puts i }
end
