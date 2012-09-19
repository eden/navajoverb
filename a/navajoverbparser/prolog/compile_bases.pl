#!/usr/bin/perl -w

# Version: MPL 1.1
#
# The contents of this file are subject to the Mozilla Public License
# Version 1.1 (the "License"); you may not use this file except in
# compliance with the License. You may obtain a copy of the License at
# http://www.mozilla.org/MPL/
#
# Software distributed under the License is distributed on an "AS IS"
# basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
# the License for the specific language governing rights and
# limitations under the License.
#
# The Original Code is Navajo Verb Morphology Parser code.
#
# The Initial Developer of the Original Code is
# Eden Siu-yue Li.
# Portions created by the Initial Developer are Copyright (C) 2004
# the Initial Developer. All Rights Reserved.

use strict;
use warnings;

use Util;
use Segmentizer;

use XML::DOM;

my ($license) = <<LICENSE;
/*
 * Version: MPL 1.1
 *
 * The contents of this file are subject to the Mozilla Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
 * the License for the specific language governing rights and
 * limitations under the License.
 *
 * The Original Code is Navajo Verb Morphology Parser code.
 *
 * The Initial Developer of the Original Code is
 * Eden Siu-yue Li.
 * Portions created by the Initial Developer are Copyright (C) 2004
 * the Initial Developer. All Rights Reserved.
 *
 */
LICENSE

@ARGV >= 4 or die "Usage: $0 <segments> <verbbases> " .
                  "<basesOutfile> <segmentsOutfile>";

my $segmentsFile = shift;
my $verbbasesFile = shift;
my $baseOut = shift;
my $segOut = shift;

my $parser = new XML::DOM::Parser ();

print "Parsing '$segmentsFile' for segments.\n";
my ($segmentizer) = new Segmentizer ($segmentsFile);

print "Parsing '$verbbasesFile' for verb bases and\n",
      "        saving to '$baseOut'.\n";
open OUT, ">$baseOut" or die "Couldn't open '$baseOut': $!";
outputBases (\*OUT, $parser,
    $verbbasesFile,
    $segmentizer);
close OUT;

print "Saving segments to '$segOut'.\n";
open OUT, ">$segOut" or die "Couldn't open '$baseOut': $!";
outputSegments (\*OUT, $segmentizer);
close OUT;

sub outputSegments {
    my $out = shift;
    my $segmentizer = shift;

    print $out $license, "\n";
    print $out ":- export vowel/3, consonant/3.\n";

    while (my ($type,$val) = each (%{$segmentizer->{Sorted}})) {
        foreach my $seg (@$val) {
            print $out <<O;
$type([$seg]) --> [$seg].
O
        }
    }
}

sub outputBases {
    my $out = shift;
    my $parser = shift;
    my $file = shift; 
    my $segmentizer = shift;

    my $baseFile = $parser->parsefile ($file) or die $!;
    print $out $license, "\n";
    print $out ":- export stem/4.\n";
    foreach my $base ($baseFile->getElementsByTagName("VerbBase")) {
        my $stem;
        my $stemset = [];
        my $aspect = '';
        my $conjugation = '';
        my $classifier = '';
        my $gloss = '';
        my $prefix = {};
        my $trans = '';

        # extract the stem set
        my $ss = $base->getElementsByTagName("StemSet");
        next unless defined $ss;
        $ss = $ss->item(0);
        foreach $stem ($ss->getChildNodes) {
            if ($stem->getNodeType == XML::DOM::ELEMENT_NODE &&
                    $stem->getNodeName =~ /I|P|F|R|O/i) {
                push @{$stemset}, 
                    [ $stem->getNodeName,
                      $segmentizer->segmentize (
                          $stem->getFirstChild->getNodeValue) ];
            }
        }

        # extract prefixes
        my $prefixes = $base->getElementsByTagName("Prefix")->item(0);
        if (defined $prefixes) {
            foreach my $pref ($prefixes->getChildNodes) {
                if ($pref->getNodeType == XML::DOM::ELEMENT_NODE &&
                        $pref->getNodeName =~ /Inner|Outer|Object/i) {
                    $prefix->{lc ($pref->getNodeName)} =
                        $segmentizer->segmentize (
                            $pref->getFirstChild->getNodeValue);
                }
            }
        }

        $gloss = $base
            ->getElementsByTagName("Gloss")->item(0)
                ->getElementsByTagName("English")
                    ->item(0)->getFirstChild->getNodeValue;

        $aspect = lc($base
            ->getElementsByTagName("Aspect")
                ->item(0)->getFirstChild->getNodeValue);

        $conjugation = lc($base
            ->getElementsByTagName("Conjugation")
                ->item(0)->getFirstChild->getNodeValue);

        $classifier = lc($base
            ->getElementsByTagName("Classifier")
                ->item(0)->getFirstChild->getNodeValue);

        $trans = lc($base
            ->getElementsByTagName("Transitivity")
                ->item(0)->getFirstChild->getNodeValue) eq "transitive";

        foreach $stem (@{$stemset}) {
            my ($mode, $value) = @$stem;
            $mode = lc($mode);
            my $outer = listToPrologList ($prefix->{outer});
            my $inner = listToPrologList ($prefix->{inner});
            my $object = listToPrologList ($prefix->{object});
            my $trans = $trans ? "trans" : "intrans";

            # escape single quotes
            $gloss =~ s/'/''/g;
            $value = listToPrologList ($value);
            print $out <<TEMPLATE;
stem(steminfo($trans,$outer,$inner,$object,$mode,$conjugation,$classifier),stem($value,mode($mode),aspect($aspect),english('$gloss'))) --> $value.
TEMPLATE
        }
    }

    # clean up document
    $baseFile->dispose ();
}

