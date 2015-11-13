#!/usr/bin/perl
use strict;
use warnings;
use File::Spec;
use File::Basename;
use XML::LibXML;
use Data::Dumper;
#.hpp / .cpp
my @templates = (
	'templates/inc/', #hpp
	'templates/src/' #cpp
	);
my @extensions = qw/.hpp .cpp/;

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

my @classes = qw/Reader Writer Importer Processor Content/;

sub intro {
	my $name = shift @_;
	die "Need name\n" if (not defined $name);

	print "Generating ";
	for (@classes) {
		print ucfirst "$name$_ " ;
	}
	print "y/n?";
	return 0 if (getc(STDIN) !~ /y/i);

	return 1;
}

sub main {
	my $path = dirname(File::Spec->rel2abs( __FILE__));
	# get the base dir
	$path =~ s!(.+?)tools.+!$1!i;
	my $vsfolder = "vs2013\\sani";
	my $vcxproj = "sani.vcxproj";
	my $filters = "sani.vcxproj.filters";

	my $name = $ARGV[0];
	return 0 if (!intro($name));

	my $i = 0;

	my @headers;
	my @sources;

	for my $c(@classes) {
		my $className = ucfirst "$name$c";
		my $lcName = lc $name;
		my $ucName = ucfirst $name;
		my $j = 0;
		for my $template (@templates) {
			my $file = "$template$files[$i]$extensions[$j]";
			die $! if (!open my $handle, $file);
			my $content = do { local $/; <$handle>};
			close $handle;
			# replace our 'vars'
			$content =~ s/\$CLASSNAME/$className/g;
			$content =~ s/\$LCNAME/$lcName/g;
			$content =~ s/\$UCNAME/$ucName/g;
			

			my $isCPP = $j % 2 == 1;
			my $out = $header_save_loc[$i];
			$out = $src_save_loc[$i] if ($isCPP);

			my $target = $out .= "$lcName$files[$i]$extensions[$j]";
			$out = "$path$out";
			open $handle, ">$out" or die $!;
			print $handle $content;
			close $handle;
			print "Wrote $out\n";


			$target =~ s!/!\\!g;
			#the thing is that .vcxproj has first .cpp and then .hpp, then .inl
			# we need to inlcude ..\..\ before our file
			$target = "..\\..\\$target";
			if ($isCPP) {
				push @sources, $target;
			} else {
				push @headers, $target;
			}

			$j++;
		}
		$i++;
	}
	updateProject($vcxproj, \@sources, \@headers);
	updateFilters($filters, \@sources, \@headers);
}

sub updateProject {
	my ($vcxproj, $sources, $headers) = @_;
	
	die $! if (!open my $handle, "+<$vcxproj");
	my $content = do { local $/; <$handle>};
	close $handle;
	die $! if (!open my $handle, ">$vcxproj");

	my $data = "";
	foreach (@{$sources}) {
		$data .= "    <ClCompile Include=\"$_\" />\n";
	}
	$data =~ s/^\s{2}//;
	$content =~ s/(<ClCompile.+?)(<\/ItemGroup>)/$1${data}  $2/is;

	$data = "";
	foreach (@{$headers}) {
		$data .= "    <ClInclude Include=\"$_\" />\n";
	}
	$data =~ s/^\s{2}//;
	$content =~ s/(<ClInclude.+?)(<\/ItemGroup>)/$1${data}  $2/is;

	print $handle $content;
	close $handle;
}

sub updateFilters {
	my ($filters, @sources, @headers) = @_;
}

main();