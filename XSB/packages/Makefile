## File:      packages/Makefile
## Author(s): kifer
## Contact:   xsb-contact@cs.sunysb.edu
## 
## Copyright (C) The Research Foundation of SUNY, 1998
## 
## XSB is free software; you can redistribute it and/or modify it under the
## terms of the GNU Library General Public License as published by the Free
## Software Foundation; either version 2 of the License, or (at your option)
## any later version.
## 
## XSB is distributed in the hope that it will be useful, but WITHOUT ANY
## WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
## FOR A PARTICULAR PURPOSE.  See the GNU Library General Public License for
## more details.
## 
## You should have received a copy of the GNU Library General Public License
## along with XSB; if not, write to the Free Software Foundation,
## Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
##
## $Id: Makefile,v 1.28 2003/02/28 16:28:43 lfcastro Exp $
## 
##

OBJEXT=.xwam

ALL = 	slx${OBJEXT} perlmatch${OBJEXT} gap${OBJEXT} \
	regmatch${OBJEXT} wildmatch${OBJEXT} \
	xasp${OBJEXT} libwww${OBJEXT} clpr${OBJEXT} xsbdoc${OBJEXT} \
	xmc${OBJEXT} iprolog${OBJEXT}

SUBDIR = iprolog flora2 slx perlmatch gap regmatch wildmatch libwww xasp \
	clpqr xsbdoc xmc iprolog

Option = [optimize]

#-----------------------------------------------------------------------#
#
# Self-make: Version 1.4.1
#
XSB=../bin/xsb
Prolog = $(XSB) -i -s -m 2000 -c 2000
#
#-----------------------------------------------------------------------#

# Make sure warnings are saved in a file.
SVFILE = '../build/.apkgs.tmp'
STDWARN = 3
STDERR = 2
HDRMSG = "While compiling XSB/packages:"


# continue to the next when one error occurs
.IGNORE:

# suffix rules
.SUFFIXES: .P ${OBJEXT} .H

.P${OBJEXT}:
	echo 'mc($*, $(Option)).' >> cmd...


all:  init $(ALL) finish $(SUBDIR)
	@../build/touch.sh cmd...
	$(Prolog) < cmd...
	@rm cmd...
	@cat $(SVFILE)

clpqr::
	@echo ""
	cd clpqr; make

slx::
	@echo ""
	cd slx; make

flora2::
	@echo ""
	@rm -f flora2.P flora2$(OBJEXT)
	@ln -s flora2/flora2.P .
	cd flora2; makeflora all $(XSB)

#Add interprolog
iprolog::
	@echo ""
	cd iprolog; make

libwww::
	@echo ""
	cd libwww; make

perlmatch::
	@echo ""
	cd perlmatch; make

xasp::
	@echo ""
	cd xasp; make

gap::
	@echo ""
	cd gap; make

regmatch::
	@echo ""
	cd regmatch; make

wildmatch::
	@echo ""
	cd wildmatch; make

xmc::
	@echo ""
	cd xmc; make

init:
	/bin/rm -f $(SVFILE)
	@echo "file_reopen($(SVFILE),w,$(STDWARN),_)." >> cmd...
	@echo "file_clone($(STDWARN), $(STDERR),_)." >> cmd...
	@echo 'fmt_write($(STDWARN),"-------------- Warnings/Errors --------------------\n",_).' >> cmd...
	@echo 'fmt_write($(STDWARN),"%s\n",arg($(HDRMSG))).' >> cmd...
	@echo "file_flush($(STDWARN), _)." >> cmd...

finish:
	@echo 'fmt_write($(STDWARN),"-------------------- End --------------------------\n",_).' >> cmd...


clean:
	/bin/rm -f core *${OBJEXT} *.O *~ .*~ *.bak .#*

.DONE:
	@echo Done
