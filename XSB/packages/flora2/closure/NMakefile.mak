# Make file for Microsoft NMAKE

ALLOBJS = flrcommon.flh \
          flrtrailer.flh \
	  flreqltrailer.flh \
          flrscalareql.flh

!IF EXISTS (..\.prolog_path_wind) 
!INCLUDE ..\.prolog_path_wind
!ENDIF

.SUFFIXES: .flh .fli

ALL: $(ALLOBJS)

CLEAN :
	-@erase *~
	-@erase *.flh
	-@erase *.bak
	-@erase .#*

.fli.flh:
	$(PROLOG) -e "['..\flora2devel']. import bootstrap_flora/0 from flora2. bootstrap_flora. [flrwraparound]. import flWrapAround/1 from flrwraparound. flWrapAround(%|fF). halt."

