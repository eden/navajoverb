package Segmentizer;

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

use lib qw(/home/eden/verbs);
use Util;

use Carp qw/cluck croak/;
 
use strict;
use warnings;

use XML::DOM;

sub new {
    my $class = shift;
    my $file = shift;

    my $self = {};

    $self->{Segments} = [];
    $self->{Sorted} = [];
    
    bless $self, $class;

    $self->parseSegments ($file);
    $self
}


sub segmentize {
    my $self = shift;
    my $src = convertFromUnicode (shift);
    my $orig = $src;

    my (@output) = ();

    # Compare the first part of the source string
    # with the first item in the segment list, attempting
    # shorter and shorter matches until a segment is matched.
    # If no segment is matched, this takes off that character
    # and tries again
    my $found = undef;
    while (length ($src) > 0) {
        $found = 0;
        for my $seg (@{$self->{Segments}}) {
            if (substr ($src, 0, length ($seg)) eq $seg) {
                push @output => $seg;
                substr ($src, 0, length ($seg)) = '';
                $found = 1;
                last;
            }
        }

        # not found
        unless ($found) {
            croak "Invalid segment '$src' in '$orig'";
            last;
        }
    }

    # return the result
    [ @output ]
}

sub parseSegments {
    my $self = shift;
    my $file = shift; 

    my (@segments) = ();
    my (%sorted) = ();

    my $parser = new XML::DOM::Parser ();
    my $baseFile = $parser->parsefile ($file) or die $!;

    foreach my $base (
            $baseFile->getElementsByTagName("vowel"),
            $baseFile->getElementsByTagName ("consonant"))
    {
        my $nodeValue = $base->getFirstChild->getNodeValue;
        for (split/\s+/, $nodeValue) { 
            chomp;
            next if not defined $_ or $_ eq "";
            my $seg = convertFromUnicode ($_);
            push @segments => $seg;
            push @{$sorted{$base->getTagName()}} => $seg;
        }
    }

    $self->{Sorted} = \%sorted;
    $self->{Segments} = \@segments
}

1
