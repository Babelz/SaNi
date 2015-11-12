#!/usr/bin/perl
use strict;
use warnings;
#.hpp / .cpp
my @templates = (
	'templates/inc/', #hpp
	'templates/src/' #cpp
	);

my $hpp_base = 'include/sani/resource';
my @header_save_loc = (
		"$hpp_base/reader/",
		"$hpp_base/compiler/",
		"$hpp_base/pipeline/",
		"$hpp_base/processor/",
		"$hpp_base/"	
	);

my $src_base = 'src/resource';
my @src_save_loc = (
		"$src_base/reader/",
		"$src_base/compiler/",
		"$src_base/pipeline/",
		"$src_base/processor/",
		"$src_base/"	
	);
my @files = (
	'_reader',
	'_writer',
	'_importer',
	'_processor',
	'_content'
	);

