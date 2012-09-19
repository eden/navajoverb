package Util;

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

use warnings;
use strict;

use Encode qw/is_utf8 decode_utf8/;
use Exporter 'import';

our (@EXPORT) =
 qw/convertFromUnicode
    prologListToUnicodeList
    listToPrologList
    prologListToHTML
    asciiToUnicode/;

sub convertFromUnicode {
    my ($input) = shift;

    return $input unless defined $input;

    $input = decode_utf8 ($input, Encode::FB_CROAK)
        unless is_utf8 ($input);

    # high tone       
    $input =~ s/\x{0301}/H/g; 

    # nasal
    $input =~ s/\x{0345}/N/g;

    # barred l
    $input =~ s/\x{026b}/lB/g;

    # glottal stop
    $input =~ s/'/xG/g;

    $input
}

sub convertToUnicode {
    my ($input) = shift;

    return $input unless defined $input;

    # high tone       
    $input =~ s/H/\x{0301}/g; 

    # nasal
    $input =~ s/N/\x{0345}/g;

    # barred l
    $input =~ s/lB/\x{026b}/g;

    # glottal stop
    $input =~ s/xG/'/g;

    $input
}

sub listToPrologList {
    defined ($_[0]) ?
        "[" . (join "," => @{$_[0]}) . "]" :
        "[]"
}

sub prologListToUnicodeList {
    my $input = shift;

    $input =~ s/^\[([^\]]*)\]$/$1/;

    map { convertToUnicode ($_) } split /,/ => $input
}

sub asciiToUnicode {
    my $input = shift;

    $input = convertToUnicode ($input);
    $input =~ s/\x{0301}/&#x0301;/g;
    $input =~ s/\x{0345}/&#x0345;/g;
    $input =~ s/\x{026b}/&#x026b;/g;

    $input
}

sub prologListToHTML {
    my $input = shift;

    $input =~ s/^\[([^\]]*)\]$/$1/;

    join "", map {
        $_ = convertToUnicode ($_);
        s/\x{0301}/&#x0301;/g;
        s/\x{0345}/&#x0345;/g;
        s/\x{026b}/&#x026b;/g;
        $_
    } split /,/ => $input
}
