## File:      packages/flora2/trailer/Makefile
##
## Author(s): Michael Kifer
##            Guizhen Yang
##
## Contact:   flora-users@lists.sourceforge.net
## 
## Copyright (C) The Research Foundation of SUNY, 1999-2001
## 
## FLORA-2 is free software; you can redistribute it and/or modify it under the
## terms of the GNU Library General Public License as published by the Free
## Software Foundation; either version 2 of the License, or (at your option)
## any later version.
## 
## FLORA-2 is distributed in the hope that it will be useful, but WITHOUT ANY
## WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
## FOR A PARTICULAR PURPOSE.  See the GNU Library General Public License for
## more details.
## 
## You should have received a copy of the GNU Library General Public License
## along with FLORA-2; if not, write to the Free Software Foundation,
## Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
##
## $Id: Makefile,v 1.21 2003/06/18 07:01:18 kifer Exp $
## 
##



OBJEXT=.xwam
PROLOGEXT = .P

FLORADIR = ..

CLOSURE = ../closure

HEADERINC = ../headerinc

GENINCLUDES = ../genincludes

ALLOBJS = standard$(PROLOGEXT) \
	  eqlbasic$(PROLOGEXT) \
          eqlflogic$(PROLOGEXT) \
          patch$(PROLOGEXT)

PROLOG = none

PROLOG_COMMAND = $(PROLOG) -s -m 2000 -c 2000 -e 'segfault_handler(warn).'

FLORA_INCLUDES_DIR = ../flrincludes

FLORA_TERMS = $(FLORA_INCLUDES_DIR)/flora_terms.flh

# Make sure warnings are saved in a file.
SVFILE = '$(FLORADIR)/.flora_trailer_warn.tmp'
STDWARN = 3
STDERR = 2
HDRMSG = "While compiling .../flora2/trailer:"


all: init $(ALLOBJS) finish
	@../touch.sh cmd...
	$(PROLOG_COMMAND) < cmd...
	@rm cmd...
	@cat $(SVFILE)


standard$(PROLOGEXT) : $(CLOSURE)/flrcommon.flh \
             $(CLOSURE)/flrtrailer.flh $(HEADERINC)/flrheader_inc.flh \
             $(HEADERINC)/flrtrailer_inc.flh
	@echo 'flsetuptrailer(none).' >> cmd...


eqlbasic$(PROLOGEXT) : $(CLOSURE)/flrcommon.flh \
             $(CLOSURE)/flreqltrailer.flh $(HEADERINC)/flrheader_inc.flh \
             $(HEADERINC)/flreqltrailer_inc.flh
	@echo 'flsetuptrailer(basic).' >> cmd...


eqlflogic$(PROLOGEXT) : $(CLOSURE)/flrcommon.flh \
              $(CLOSURE)/flreqltrailer.flh $(CLOSURE)/flrscalareql.flh \
              $(HEADERINC)/flrheader_inc.flh \
              $(HEADERINC)/flreqltrailer_inc.flh $(HEADERINC)/flrscalareql_inc.flh
	@echo 'flsetuptrailer(flogic).' >> cmd...


patch$(PROLOGEXT) : $(GENINCLUDES)/flrpatch.flh $(GENINCLUDES)/flrpreddef.flh \
	  $(HEADERINC)/flrheader_inc.flh \
          $(HEADERINC)/flrdefinition_inc.flh \
          $(HEADERINC)/flrpreddef_inc.flh 
	@echo 'flsetuppatch.' >> cmd...


$(CLOSURE)/flrcommon.flh : $(CLOSURE)/flrcommon.fli $(FLORA_INCLUDES_DIR)/flora_wspredicates.flh
	@cd $(CLOSURE); make


$(CLOSURE)/flrtrailer.flh : $(CLOSURE)/flrtrailer.fli $(FLORA_INCLUDES_DIR)/flora_wspredicates.flh
	@cd $(CLOSURE); make


$(CLOSURE)/flreqltrailer.flh : $(CLOSURE)/flreqltrailer.fli $(FLORA_INCLUDES_DIR)/flora_wspredicates.flh
	@cd $(CLOSURE); make


$(CLOSURE)/flrscalareql.flh : $(CLOSURE)/flrscalareql.fli $(FLORA_INCLUDES_DIR)/flora_wspredicates.flh
	@cd $(CLOSURE); make


$(GENINCLUDES)/flrpatch.flh : $(GENINCLUDES)/flrpatch.fli $(FLORA_TERMS)
	@cd $(GENINCLUDES); make


$(GENINCLUDES)/flrpreddef.flh : $(GENINCLUDES)/flrpreddef.fli $(FLORA_TERMS)
	@cd $(GENINCLUDES); make


init:
	/bin/rm -f $(SVFILE)
	@echo "['../flora2devel']." >> cmd...
	@echo "import bootstrap_flora/0 from flora2." >> cmd...
	@echo "bootstrap_flora." >> cmd...
	@echo "[flrutils]." >> cmd...
	@echo "import flsetuptrailer/1 from flrutils." >> cmd...
	@echo "import flsetuppatch/0 from flrutils." >> cmd...
	@echo "file_reopen($(SVFILE),w,$(STDWARN),_)." >> cmd...
	@echo "file_clone($(STDWARN),$(STDERR),_)." >> cmd...
	@echo "file_write($(STDWARN),'-------------- Warnings/Errors --------------------'), file_nl($(STDWARN))." >> cmd...
	@echo "file_write($(STDWARN),'$(HDRMSG)'), file_nl($(STDWARN))." >> cmd...
	@echo "file_flush($(STDWARN),_)." >> cmd...


finish:
	@echo "file_write($(STDWARN),'-------------------- End --------------------------'), file_nl($(STDWARN))." >> cmd...


clean:
	/bin/rm -f *~ .*~ *$(PROLOGEXT) *$(OBJEXT) *.O *.flh *.bak .#*


.DONE:
	@echo Done
