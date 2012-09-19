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

use lib qq(perl);
 
use Encode qw/is_utf8 encode_utf8 decode_utf8/;
use warnings;
use strict;

use CGI qw/:standard/;
use Segmentizer;
use Util;

use constant XSB => "/home/eden/XSB/bin/xsb";
use constant SCRIPT_DIR => "/home/eden/dev/navajoverb/prolog";
use constant SEGMENTS_XML => "/home/eden/dev/navajoverb/xml/Segments.xml";

sub printQueryForm();
sub parse($);
sub deescapify ($);

print header,
    start_html(-title    => 'Parse Navajo Verbs',
               -script   => { -src => 'charHandle.js' },
               -encoding => 'utf-8',
               -style    => { -src => 'parse.css' }
    );



# print menu
print div({-id => "menu"}, <<MENU);
    <a href="parse.s">Main</a>
    <a href="about.html">About</a>
    <a href="help.html">Help</a>
    <a href="contact.s">Contact</a>
MENU


print '<div id="main">';
print h1("Navajo Verb Parser");
print p("You may want to start",
    a({-href=>"help.html"}, "here."));
print p("Some caveats:"), ul(
    li("Verbs that begin with glottal stops must be spelled with the glottal",
        " stop (') at the beginning.  It is not optional."),
    li("Currently the alternate spelling for h is not recognized."),
    li("Internet Explorer does not render the Unicode characters correctly. ",
       "You will see boxes in the place of barred-ls and nasal hooks in",
       "that browser.  Use ", a({-href=>"http://www.firefox.com/"},"Firefox"),
       "to view these characters correctly."),
    li("Currently, only",
            a({-href=>"xml/VerbBases.xml"},"these verbs"),
        "are supported by the parser.",
        a({-href=>"contact.s"}, "Contact me"), "if you'd like to add more.")
    );

printQueryForm ();

if (param()) {
    my $s = new Segmentizer (SEGMENTS_XML);
    my $input = param('input');

    my $segmentized = '';
    eval {
         $segmentized = $s->segmentize(deescapify($input));
    };

    if ($@) {
        my $msg = $@;
        $msg =~ s/\/home\/eden\/verbs\///;
        print p({-class=>'warning'}, $msg);
    }
    else {
        print h2("Input");
        print p({-class => 'input'}, $input);

        my $prologList = listToPrologList($segmentized);

        print h2("Segmentized Form");
        print pre($prologList);
        
        print h2("Morphology");
        my $parsed = parse($prologList);

        $parsed =~ s{(\[[A-Za-z,]+\])}{
               prologListToHTML($1)
        }seg;
        print $parsed;
    }
}

print p({-id=>'footer'},
    qq{Copyright &copy; 2004 Eden Li.  Licensed under the
    <a href="MPL-1.1.html">
        Mozilla Public License</a>.});
print '</div>';
print end_html;


#=======================================================================
# Subs

sub printQueryForm () {
    print
        start_form,
#        div ({-id => 'parseTypeGroup'},
#            radio_group(-name => 'parseType',
#                    -class => 'parseTypeClass',
#                    -values => [qw/surface underlying/],
#                    -default => 'surface',
#                    -labels => {
#                        underlying => 'Underlying Form',
#                        surface => 'Surface Form'
#                    }
#        )),
        textfield(-name => 'input',
                  -id => 'input'),
        submit({-id => 'submit'}),
        end_form;
}

sub parse ($) {
    my ($input) = (shift) . ".";
    chdir (SCRIPT_DIR);
    my $output = `echo $input | ${[XSB]}[0] do_parse --nobanner --quietload`;
    return $output;
}

sub deescapify ($) {
    my $escaped = shift;

    $escaped =~ s/&#[xX]([0-9a-fA-F]+);/chr(hex($1))/eg;
    $escaped =~ s/&#(\d+);/chr($1)/eg;

    $escaped
}
