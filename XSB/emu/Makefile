# Generated automatically from emuMakefile.in by configure.
##############################################################################
#									     #
# This is a Makefile for making the XSB emu directory.			     #
# It has two main entries: xsb and xsbora. The latter for generating	     #
# executables with oracle support.					     #
# The EXECUTABLE variable is set by the top make file, build/Makefile	     #
#									     #
##############################################################################

## File:      emuMakefile.in
## Author(s): kifer (adapted from the original XSB makefile)
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
## $Id: emuMakefile.in,v 1.50 2003/05/13 20:49:21 lfcastro Exp $
## 


CC=gcc
CPP=gcc -E
CFLAGS= -O4 -fomit-frame-pointer -finline-functions -Wall 
# Compilation flags for files requiring lower optimization level
# (builtin.c,emuloop.c,tr_utils.c)
loaderCFLAGS= -O2 -fomit-frame-pointer -finline-functions -Wall 
builtinsCFLAGS= -O4 -fomit-frame-pointer -finline-functions -Wall 
emuloopCFLAGS= -O4 -fomit-frame-pointer -finline-functions -Wall 
trutilsCFLAGS= -O1 -fomit-frame-pointer -finline-functions -Wall 
CPPFLAGS=
LDFLAGS=  -lm -ldl -Wl,-export-dynamic
ODBCSRC=
ODBCOBJ=
INTERPROLOGSRC=
INTERPROLOGOBJ=
DLLTYPE=nodll
JAVA_HEADER_PATH=
JAVA_PLATFORM_HEADER_PATH=

# For mno-cygwin 
# -mdll option is needed so that MSVC files could link to dll
# however for old cygwin versions -dll option is used  
DLLNAME=xsb.dll
DLL_LIBS=$(LDFLAGS) 
LIB_OBJECTS=xsb.o dllinit_xsb.o
BASE_FILE=xsb.base
DEF_FILE=$(arch_config_prefix)/saved.o/xsb.def
LIB_FILE=libxsb.a
ENTRY_FUNCTION=_win_xsbent@12




# This one is used for SGI only
LINKFLAGS=-nodefaultlibs -nostartfiles 

# Substitute an assignment for the MAKE variable, because
# BSD doesn't have it as a default.



# just to be sure the sh is used 
SHELL=/bin/sh


# The default location for installation. 
prefix=/home/eden/dev/navajoverb/XSB
# where sources are
srcdir=/home/eden/dev/navajoverb/XSB
# Like `prefix', but used for architecture-specific files.
arch_config_prefix=/home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu

# Where to install XSB binaries
bindir=$(arch_config_prefix)/bin
# where XSB emu directory lives
emudir=$(srcdir)/emu
# where the object code goes
arch_config_objlibdir=$(arch_config_prefix)/saved.o

# Passed in from the top Makefile
EXECUTABLE=xsb

#=======================================================================
# Stuff to automatically make the dependencies.
#=======================================================================
#
DEPEND = makedepend
#DEPENDFLAGS = -m
#


SRCS =	auxlry.c biassert.c builtin.c cinterf.c \
	debug_xsb.c dis.c dynload.c dynamic_stack.c \
	emuloop.c error_xsb.c findall.c function.c \
	hash_xsb.c hashtable_xsb.c \
	heap_xsb.c init_xsb.c inst_xsb.c io_builtins_xsb.c \
	loader_xsb.c main_xsb.c memory_xsb.c orient_xsb.c \
	pathname_xsb.c psc_xsb.c random_xsb.c \
        remove_unf.c residual.c \
	scc_xsb.c slgdelay.c socket_xsb.c string_xsb.c \
	storage_xsb.c struct_manager.c sub_delete.c subp.c \
	system_xsb.c table_stats.c tables.c timer_xsb.c token_xsb.c \
	tr_utils.c trace_xsb.c trie_lookup.c trie_search.c tries.c \
	tst_insert.c tst_retrv.c tst_unify.c tst_utils.c varstring.c


ORASRCS = $(SRCS) orastuff.c


OBJS =	auxlry.o biassert.o builtin.o cinterf.o \
	debug_xsb.o dis.o dynload.o dynamic_stack.o \
	emuloop.o error_xsb.o findall.o function.o \
	hash_xsb.o  hashtable_xsb.o \
	heap_xsb.o init_xsb.o inst_xsb.o io_builtins_xsb.o \
	loader_xsb.o memory_xsb.o orient_xsb.o \
	pathname_xsb.o private_builtin.o psc_xsb.o random_xsb.o \
        remove_unf.o residual.o \
	scc_xsb.o slgdelay.o socket_xsb.o string_xsb.o \
	storage_xsb.o struct_manager.o sub_delete.o subp.o \
	system_xsb.o table_stats.o tables.o timer_xsb.o token_xsb.o \
	tr_utils.o trace_xsb.o trie_lookup.o trie_search.o tries.o \
	tst_insert.o tst_retrv.o tst_unify.o tst_utils.o varstring.o


allOBJS = main_xsb.o ${OBJS} ${ODBCOBJ} ${INTERPROLOGOBJ}

ORAOBJS = $(OBJS) orastuff.o

allORAOBJS = $(allOBJS) orastuff.o

xsb:: $(allOBJS)
	@echo ""; echo "Making XSB executable $(EXECUTABLE) "; echo ""
	cd $(emudir); \
	$(CC) -o $(EXECUTABLE) $(allOBJS) $(LDFLAGS) 

xsbora:: $(allORAOBJS)
	@echo ""; \
	  echo "Making XSB executable $(EXECUTABLE) with support for Oracle"; \
	  echo ""
	cd $(emudir); \
	$(CC) -o $(EXECUTABLE) $(allORAOBJS) $(LDFLAGS)

# Goal for making an XSB load module to be linked with external
# C-drivers that pass queries to XSB
xsbmod:: $(OBJS) ${ODBCOBJ} ${INTERPROLOGOBJ}
	@echo ""; \
	   echo "Making a C-callable XSB module $(arch_config_objlibdir)/xsb.o"; \
	   echo ""
	gcc -o xsb.o $(LINKFLAGS) -r $(OBJS) ${ODBCOBJ} ${INTERPROLOGOBJ}
	@cp xsb.o $(arch_config_objlibdir) 2> /dev/null || echo ""

xsbdynmod::
	echo "Making XSB Shared Library $(bindir)/libxsb.so"
	gcc -o libxsb.so -shared $(LINKFLAGS)  $(OBJS) ${ODBCOBJ} ${INTERPROLOGOBJ}
	@cp libxsb.so $(bindir) 2>/dev/null || echo ""

# same as xsbmod, but with oracle support
xsboramod:: $(ORAOBJS)
	@echo ""; \
	   echo "Making a C-callable XSB module $(arch_config_objlibdir)/xsb.o with support for Oracle"; \
	   echo ""
	gcc -o xsb.o $(LINKFLAGS) -r $(ORAOBJS)
	@cp xsb.o $(arch_config_objlibdir) 2> /dev/null || echo ""


depend::
	$(DEPEND) $(DEPENDFLAGS) -- -I$(arch_config_prefix)  -I$(JAVA_PLATFORM_HEADER_PATH) -I$(JAVA_HEADER_PATH) $(CFLAGS) -- $(SRCS) $(ODBCSRC) ${INTERPROLOGSRC}

#
# create a new DLL library in cygwin (compiled with -mno-cygwin) environment
#
# LIB_OBJECTS: xsb.o, initdll_xsb.o files
# DLLNAME: name of the new dll
# DEFFILE is the name of the definitions file.
# BASEFILE temporary
# EXPFILE  temporary
# ENTRY is the entry point  int WINAPI startup (HINSTANCE, DWORD, LPVOID)

dll: $(DLLTYPE)

nodll:

cygdll: $(allOBJS) $(HEADERS) xsbmod
	chmod ugo+x $(arch_config_prefix)/makedef.sh
	$(CC) -I$(arch_config_prefix) -c $(CFLAGS) dllinit_xsb.cc
	@cp dllinit_xsb.o $(arch_config_objlibdir) 2> /dev/null || echo ""
	$(arch_config_prefix)/makedef.sh $(allOBJS) dllinit_xsb.o
	@mv out.def $(DEF_FILE)
	$(CC) -mno-cygwin -shared -o $(DLLNAME) $(LIB_OBJECTS) $(DEF_FILE) -Wl,--out-implib=xsb.a $(DLL_LIBS) -e $(ENTRY_FUNCTION)
	@mv $(DLLNAME) $(bindir) 2> /dev/null || echo ""
	@mv $(LIB_FILE) $(bindir) 2> /dev/null || echo ""
	@rm -f $(BASE_FILE) 2> /dev/null || echo ""
	$(CC) -o $(arch_config_prefix)/bin/xsb.exe  $(CFLAGS) \
		-I$(arch_config_prefix) -L$(arch_config_prefix)/bin \
		main_xsb.c $(LINKFLAGS) $(DLL_LIBS) -lxsb


#=======================================================================
# Put in this group all actions (rules) of this Makefile.
#=======================================================================

interprolog_callback.o: interprolog_callback.c
	$(CC) -c -I$(arch_config_prefix) -I$(JAVA_PLATFORM_HEADER_PATH) -I$(JAVA_HEADER_PATH) $(CFLAGS) interprolog_callback.c
	@cp interprolog_callback.o $(arch_config_objlibdir) 2> /dev/null || echo ""

init_xsb.o: init_xsb.c
	$(CC) -I$(arch_config_prefix)  -c $(CFLAGS) init_xsb.c
	@cp init_xsb.o $(arch_config_objlibdir) 2> /dev/null || echo ""

dynload.o: dynload.c
	$(CC) -I$(arch_config_prefix)  -c $(CFLAGS) dynload.c
	@cp dynload.o $(arch_config_objlibdir) 2> /dev/null || echo ""

emuloop.o: emuloop.c
	$(CC) -I$(arch_config_prefix)  -c $(emuloopCFLAGS) emuloop.c
	@cp emuloop.o $(arch_config_objlibdir) 2> /dev/null || echo ""

# Higher optimization level has problem with some versions of gcc
tr_utils.o: tr_utils.c
	$(CC) -I$(arch_config_prefix)  -c $(trutilsCFLAGS) tr_utils.c
	@cp tr_utils.o $(arch_config_objlibdir) 2> /dev/null || echo ""

builtin.o: builtin.c
	$(CC) -I$(arch_config_prefix)  -c $(builtinsCFLAGS) builtin.c
	@cp builtin.o $(arch_config_objlibdir) 2> /dev/null || echo ""

loader_xsb.o: loader_xsb.c
	$(CC) -I$(arch_config_prefix)  -c $(loaderCFLAGS) loader_xsb.c
	@cp loader_xsb.o $(arch_config_objlibdir) 2> /dev/null || echo ""

.c.o:
	$(CC) -I$(arch_config_prefix)  -c $(CFLAGS) $*.c
	@cp $*.o $(arch_config_objlibdir) 2> /dev/null || echo ""


#=======================================================================
# All dependencies are automatically generated by makedepend.
#=======================================================================

# DO NOT DELETE THIS LINE -- `makedepend' depends on it!

auxlry.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
auxlry.o: /usr/include/stdio.h /usr/include/features.h
auxlry.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
auxlry.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
auxlry.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
auxlry.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
auxlry.o: /usr/include/bits/wchar.h /usr/include/gconv.h
auxlry.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
auxlry.o: xsb_time.h /usr/include/sys/time.h /usr/include/time.h
auxlry.o: /usr/include/bits/time.h /usr/include/sys/select.h
auxlry.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
auxlry.o: /usr/include/sys/resource.h /usr/include/bits/resource.h
biassert.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
biassert.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
biassert.o: debugs/debug_biassert.h /usr/include/stdio.h
biassert.o: /usr/include/features.h /usr/include/sys/cdefs.h
biassert.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
biassert.o: /usr/include/gnu/stubs-32.h /usr/include/bits/types.h
biassert.o: /usr/include/bits/typesizes.h /usr/include/libio.h
biassert.o: /usr/include/_G_config.h /usr/include/wchar.h
biassert.o: /usr/include/bits/wchar.h /usr/include/gconv.h
biassert.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
biassert.o: /usr/include/errno.h /usr/include/bits/errno.h
biassert.o: /usr/include/linux/errno.h /usr/include/asm/errno.h
biassert.o: /usr/include/asm-i386/errno.h /usr/include/asm-generic/errno.h
biassert.o: /usr/include/asm-generic/errno-base.h /usr/include/string.h
biassert.o: /usr/include/xlocale.h /usr/include/stdlib.h
biassert.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
biassert.o: /usr/include/endian.h /usr/include/bits/endian.h
biassert.o: /usr/include/sys/types.h /usr/include/time.h
biassert.o: /usr/include/sys/select.h /usr/include/bits/select.h
biassert.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
biassert.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
biassert.o: /usr/include/alloca.h setjmp_xsb.h /usr/include/setjmp.h
biassert.o: /usr/include/bits/setjmp.h auxlry.h basicdefs.h basictypes.h
biassert.o: cell_xsb.h celltags_xsb.h cell_def_xsb.h error_xsb.h export.h
biassert.o: cinterf.h varstring_xsb.h memory_xsb.h psc_xsb.h psc_defs.h
biassert.o: heap_xsb.h heap_defs_xsb.h register.h flags_xsb.h flag_defs_xsb.h
biassert.o: deref.h inst_xsb.h token_xsb.h token_defs_xsb.h loader_xsb.h
biassert.o: trie_internals.h struct_manager.h tries.h choice.h macro_xsb.h
biassert.o: debug_xsb.h table_status_defs.h slgdelay.h debugs/debug_delay.h
biassert.o: tr_utils.h trassert.h
builtin.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
builtin.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
builtin.o: debugs/debug_delay.h /usr/include/stdio.h /usr/include/features.h
builtin.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
builtin.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
builtin.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
builtin.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
builtin.o: /usr/include/bits/wchar.h /usr/include/gconv.h
builtin.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
builtin.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
builtin.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
builtin.o: /usr/include/bits/endian.h /usr/include/xlocale.h
builtin.o: /usr/include/sys/types.h /usr/include/time.h
builtin.o: /usr/include/sys/select.h /usr/include/bits/select.h
builtin.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
builtin.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
builtin.o: /usr/include/alloca.h /usr/include/string.h /usr/include/errno.h
builtin.o: /usr/include/bits/errno.h /usr/include/linux/errno.h
builtin.o: /usr/include/asm/errno.h /usr/include/asm-i386/errno.h
builtin.o: /usr/include/asm-generic/errno.h
builtin.o: /usr/include/asm-generic/errno-base.h /usr/include/sys/stat.h
builtin.o: /usr/include/bits/stat.h /usr/include/signal.h
builtin.o: /usr/include/bits/signum.h /usr/include/bits/siginfo.h
builtin.o: /usr/include/bits/sigaction.h /usr/include/bits/sigcontext.h
builtin.o: /usr/include/asm/sigcontext.h /usr/include/asm-i386/sigcontext.h
builtin.o: /usr/include/bits/sigstack.h /usr/include/sys/ucontext.h
builtin.o: /usr/include/bits/sigthread.h /usr/include/math.h
builtin.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
builtin.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
builtin.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
builtin.o: /usr/include/bits/mathcalls.h /usr/include/unistd.h
builtin.o: /usr/include/bits/posix_opt.h /usr/include/bits/environments.h
builtin.o: /usr/include/bits/confname.h /usr/include/getopt.h
builtin.o: /usr/include/sys/socket.h /usr/include/sys/uio.h
builtin.o: /usr/include/bits/uio.h /usr/include/bits/socket.h
builtin.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
builtin.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
builtin.o: /usr/include/bits/posix2_lim.h /usr/include/bits/xopen_lim.h
builtin.o: /usr/include/bits/sockaddr.h /usr/include/asm/socket.h
builtin.o: /usr/include/asm-i386/socket.h /usr/include/asm/sockios.h
builtin.o: /usr/include/asm-i386/sockios.h /usr/include/netdb.h
builtin.o: /usr/include/netinet/in.h /usr/include/stdint.h
builtin.o: /usr/include/bits/in.h /usr/include/bits/byteswap.h
builtin.o: /usr/include/rpc/netdb.h /usr/include/bits/netdb.h
builtin.o: /usr/include/arpa/inet.h /usr/include/fcntl.h
builtin.o: /usr/include/bits/fcntl.h auxlry.h basicdefs.h basictypes.h
builtin.o: cell_xsb.h celltags_xsb.h cell_def_xsb.h error_xsb.h setjmp_xsb.h
builtin.o: /usr/include/setjmp.h /usr/include/bits/setjmp.h export.h
builtin.o: psc_xsb.h psc_defs.h hash_xsb.h tries.h choice.h deref.h
builtin.o: memory_xsb.h heap_xsb.h heap_defs_xsb.h register.h flags_xsb.h
builtin.o: flag_defs_xsb.h loader_xsb.h binding.h macro_xsb.h debug_xsb.h
builtin.o: table_status_defs.h slgdelay.h builtin.h sig_xsb.h subp.h
builtin.o: tr_utils.h trassert.h dynload.h cinterf.h varstring_xsb.h
builtin.o: residual.h tables.h trie_internals.h inst_xsb.h struct_manager.h
builtin.o: io_builtins_xsb.h io_defs_xsb.h token_xsb.h token_defs_xsb.h
builtin.o: storage_xsb.h storage_xsb_defs.h wind2unix.h system_xsb.h
builtin.o: random_xsb.h ptoc_tag_xsb_i.h term_psc_xsb_i.h conget_xsb_i.h
builtin.o: io_builtins_xsb_i.h file_modes_xsb.h std_pred_xsb_i.h
builtin.o: sp_unify_xsb_i.h call_xsb_i.h bineg_xsb_i.h std_cases_xsb_i.h
cinterf.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
cinterf.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
cinterf.o: /usr/include/stdio.h /usr/include/features.h
cinterf.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
cinterf.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
cinterf.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
cinterf.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
cinterf.o: /usr/include/bits/wchar.h /usr/include/gconv.h
cinterf.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
cinterf.o: /usr/include/string.h /usr/include/xlocale.h /usr/include/stdlib.h
cinterf.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
cinterf.o: /usr/include/endian.h /usr/include/bits/endian.h
cinterf.o: /usr/include/sys/types.h /usr/include/time.h
cinterf.o: /usr/include/sys/select.h /usr/include/bits/select.h
cinterf.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
cinterf.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
cinterf.o: /usr/include/alloca.h auxlry.h basicdefs.h basictypes.h cell_xsb.h
cinterf.o: celltags_xsb.h cell_def_xsb.h memory_xsb.h register.h psc_xsb.h
cinterf.o: psc_defs.h flags_xsb.h flag_defs_xsb.h deref.h heap_xsb.h
cinterf.o: heap_defs_xsb.h binding.h tries.h choice.h subp.h emuloop.h
cinterf.o: export.h cinterf.h varstring_xsb.h error_xsb.h setjmp_xsb.h
cinterf.o: /usr/include/setjmp.h /usr/include/bits/setjmp.h orient_xsb.h
debug_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
debug_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
debug_xsb.o: /usr/include/stdio.h /usr/include/features.h
debug_xsb.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
debug_xsb.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
debug_xsb.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
debug_xsb.o: /usr/include/libio.h /usr/include/_G_config.h
debug_xsb.o: /usr/include/wchar.h /usr/include/bits/wchar.h
debug_xsb.o: /usr/include/gconv.h /usr/include/bits/stdio_lim.h
debug_xsb.o: /usr/include/bits/sys_errlist.h /usr/include/string.h
debug_xsb.o: /usr/include/xlocale.h auxlry.h basicdefs.h basictypes.h
debug_xsb.o: cell_xsb.h celltags_xsb.h cell_def_xsb.h error_xsb.h
debug_xsb.o: setjmp_xsb.h /usr/include/setjmp.h /usr/include/bits/setjmp.h
debug_xsb.o: /usr/include/bits/sigset.h export.h binding.h psc_xsb.h
debug_xsb.o: psc_defs.h memory_xsb.h flags_xsb.h flag_defs_xsb.h register.h
debug_xsb.o: deref.h trie_internals.h inst_xsb.h struct_manager.h tries.h
debug_xsb.o: choice.h macro_xsb.h debug_xsb.h table_status_defs.h slgdelay.h
debug_xsb.o: debugs/debug_delay.h varstring_xsb.h cinterf.h io_defs_xsb.h
debug_xsb.o: io_builtins_xsb.h token_xsb.h token_defs_xsb.h
dis.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
dis.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
dis.o: /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h
dis.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
dis.o: /usr/include/gnu/stubs-32.h /usr/include/bits/types.h
dis.o: /usr/include/bits/typesizes.h /usr/include/libio.h
dis.o: /usr/include/_G_config.h /usr/include/wchar.h
dis.o: /usr/include/bits/wchar.h /usr/include/gconv.h
dis.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
dis.o: /usr/include/string.h /usr/include/xlocale.h auxlry.h basicdefs.h
dis.o: basictypes.h psc_xsb.h psc_defs.h hash_xsb.h loader_xsb.h cell_xsb.h
dis.o: celltags_xsb.h cell_def_xsb.h inst_xsb.h builtin.h memory_xsb.h
dis.o: flags_xsb.h flag_defs_xsb.h tries.h macro_xsb.h debug_xsb.h
dis.o: table_status_defs.h slgdelay.h debugs/debug_delay.h
dynload.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
dynload.o: dynelf_xsb_i.h /usr/include/dlfcn.h /usr/include/features.h
dynload.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
dynload.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
dynload.o: /usr/include/bits/dlfcn.h /usr/include/sys/file.h
dynload.o: /usr/include/fcntl.h /usr/include/bits/fcntl.h
dynload.o: /usr/include/sys/types.h /usr/include/bits/types.h
dynload.o: /usr/include/bits/typesizes.h /usr/include/time.h
dynload.o: /usr/include/endian.h /usr/include/bits/endian.h
dynload.o: /usr/include/sys/select.h /usr/include/bits/select.h
dynload.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
dynload.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
dynload.o: /usr/include/bits/uio.h /usr/include/sys/stat.h
dynload.o: /usr/include/bits/stat.h /usr/include/errno.h
dynload.o: /usr/include/bits/errno.h /usr/include/linux/errno.h
dynload.o: /usr/include/asm/errno.h /usr/include/asm-i386/errno.h
dynload.o: /usr/include/asm-generic/errno.h
dynload.o: /usr/include/asm-generic/errno-base.h /usr/include/stdio.h
dynload.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
dynload.o: /usr/include/bits/wchar.h /usr/include/gconv.h
dynload.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
dynload.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
dynload.o: /usr/include/bits/waitstatus.h /usr/include/xlocale.h
dynload.o: /usr/include/alloca.h /usr/include/string.h wind2unix.h auxlry.h
dynload.o: basicdefs.h basictypes.h cell_xsb.h celltags_xsb.h cell_def_xsb.h
dynload.o: memory_xsb.h inst_xsb.h psc_xsb.h psc_defs.h error_xsb.h
dynload.o: setjmp_xsb.h /usr/include/setjmp.h /usr/include/bits/setjmp.h
dynload.o: export.h io_builtins_xsb.h io_defs_xsb.h token_xsb.h
dynload.o: token_defs_xsb.h varstring_xsb.h string_xsb.h extensions_xsb.h
dynamic_stack.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
dynamic_stack.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
dynamic_stack.o: debugs/debug_tries.h /usr/include/stdio.h
dynamic_stack.o: /usr/include/features.h /usr/include/sys/cdefs.h
dynamic_stack.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
dynamic_stack.o: /usr/include/gnu/stubs-32.h /usr/include/bits/types.h
dynamic_stack.o: /usr/include/bits/typesizes.h /usr/include/libio.h
dynamic_stack.o: /usr/include/_G_config.h /usr/include/wchar.h
dynamic_stack.o: /usr/include/bits/wchar.h /usr/include/gconv.h
dynamic_stack.o: /usr/include/bits/stdio_lim.h
dynamic_stack.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
dynamic_stack.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
dynamic_stack.o: /usr/include/endian.h /usr/include/bits/endian.h
dynamic_stack.o: /usr/include/xlocale.h /usr/include/sys/types.h
dynamic_stack.o: /usr/include/time.h /usr/include/sys/select.h
dynamic_stack.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
dynamic_stack.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
dynamic_stack.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
dynamic_stack.o: auxlry.h basicdefs.h basictypes.h cell_xsb.h celltags_xsb.h
dynamic_stack.o: cell_def_xsb.h tst_aux.h debugs/debug_tables.h
dynamic_stack.o: dynamic_stack.h error_xsb.h setjmp_xsb.h
dynamic_stack.o: /usr/include/setjmp.h /usr/include/bits/setjmp.h export.h
dynamic_stack.o: debug_xsb.h flags_xsb.h flag_defs_xsb.h
emuloop.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
emuloop.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
emuloop.o: /usr/include/stdio.h /usr/include/features.h
emuloop.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
emuloop.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
emuloop.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
emuloop.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
emuloop.o: /usr/include/bits/wchar.h /usr/include/gconv.h
emuloop.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
emuloop.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
emuloop.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
emuloop.o: /usr/include/bits/endian.h /usr/include/xlocale.h
emuloop.o: /usr/include/sys/types.h /usr/include/time.h
emuloop.o: /usr/include/sys/select.h /usr/include/bits/select.h
emuloop.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
emuloop.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
emuloop.o: /usr/include/alloca.h /usr/include/signal.h
emuloop.o: /usr/include/bits/signum.h /usr/include/bits/siginfo.h
emuloop.o: /usr/include/bits/sigaction.h /usr/include/bits/sigcontext.h
emuloop.o: /usr/include/asm/sigcontext.h /usr/include/asm-i386/sigcontext.h
emuloop.o: /usr/include/bits/sigstack.h /usr/include/sys/ucontext.h
emuloop.o: /usr/include/bits/sigthread.h /usr/include/string.h
emuloop.o: /usr/include/sys/un.h /usr/include/bits/sockaddr.h auxlry.h
emuloop.o: basicdefs.h basictypes.h cell_xsb.h celltags_xsb.h cell_def_xsb.h
emuloop.o: register.h psc_xsb.h psc_defs.h error_xsb.h setjmp_xsb.h
emuloop.o: /usr/include/setjmp.h /usr/include/bits/setjmp.h export.h
emuloop.o: inst_xsb.h deref.h memory_xsb.h heap_xsb.h heap_defs_xsb.h
emuloop.o: sig_xsb.h emudef.h debugs/debug_attv.h loader_xsb.h binding.h
emuloop.o: flags_xsb.h flag_defs_xsb.h trie_internals.h struct_manager.h
emuloop.o: tries.h choice.h sw_envs.h macro_xsb.h debug_xsb.h
emuloop.o: table_status_defs.h slgdelay.h debugs/debug_delay.h tables.h
emuloop.o: subinst.h scc_xsb.h subp.h tr_utils.h cut_xsb.h orient_xsb.h
emuloop.o: io_builtins_xsb.h io_defs_xsb.h token_xsb.h token_defs_xsb.h
emuloop.o: unify_xsb.h emuloop_aux.h remove_unf.h hash_xsb.h tr_delay.h
emuloop.o: tr_code_xsb_i.h schedrev_xsb_i.h complete_local.h xsb_inst_list.h
emuloop.o: slginsts_xsb_i.h complete_xsb_i.h tc_insts_xsb_i.h
emuloop.o: debugs/debug_tries.h
error_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
error_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
error_xsb.o: /usr/include/stdio.h /usr/include/features.h
error_xsb.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
error_xsb.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
error_xsb.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
error_xsb.o: /usr/include/libio.h /usr/include/_G_config.h
error_xsb.o: /usr/include/wchar.h /usr/include/bits/wchar.h
error_xsb.o: /usr/include/gconv.h /usr/include/bits/stdio_lim.h
error_xsb.o: /usr/include/bits/sys_errlist.h /usr/include/string.h
error_xsb.o: /usr/include/xlocale.h /usr/include/signal.h
error_xsb.o: /usr/include/bits/sigset.h /usr/include/bits/signum.h
error_xsb.o: /usr/include/time.h /usr/include/bits/siginfo.h
error_xsb.o: /usr/include/bits/sigaction.h /usr/include/bits/sigcontext.h
error_xsb.o: /usr/include/asm/sigcontext.h /usr/include/asm-i386/sigcontext.h
error_xsb.o: /usr/include/bits/sigstack.h /usr/include/sys/ucontext.h
error_xsb.o: /usr/include/bits/pthreadtypes.h /usr/include/bits/sigthread.h
error_xsb.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
error_xsb.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
error_xsb.o: /usr/include/bits/endian.h /usr/include/sys/types.h
error_xsb.o: /usr/include/sys/select.h /usr/include/bits/select.h
error_xsb.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
error_xsb.o: /usr/include/alloca.h auxlry.h basicdefs.h basictypes.h
error_xsb.o: cell_xsb.h celltags_xsb.h cell_def_xsb.h psc_xsb.h psc_defs.h
error_xsb.o: subp.h register.h error_xsb.h setjmp_xsb.h /usr/include/setjmp.h
error_xsb.o: /usr/include/bits/setjmp.h export.h io_builtins_xsb.h
error_xsb.o: io_defs_xsb.h token_xsb.h token_defs_xsb.h cinterf.h
error_xsb.o: varstring_xsb.h memory_xsb.h tries.h choice.h inst_xsb.h
error_xsb.o: macro_xsb.h debug_xsb.h table_status_defs.h slgdelay.h
error_xsb.o: debugs/debug_delay.h tr_utils.h cut_xsb.h flags_xsb.h
error_xsb.o: flag_defs_xsb.h term_psc_xsb_i.h
findall.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
findall.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
findall.o: /usr/include/stdio.h /usr/include/features.h
findall.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
findall.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
findall.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
findall.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
findall.o: /usr/include/bits/wchar.h /usr/include/gconv.h
findall.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
findall.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
findall.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
findall.o: /usr/include/bits/endian.h /usr/include/xlocale.h
findall.o: /usr/include/sys/types.h /usr/include/time.h
findall.o: /usr/include/sys/select.h /usr/include/bits/select.h
findall.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
findall.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
findall.o: /usr/include/alloca.h auxlry.h basicdefs.h basictypes.h cell_xsb.h
findall.o: celltags_xsb.h cell_def_xsb.h deref.h register.h psc_xsb.h
findall.o: psc_defs.h memory_xsb.h error_xsb.h setjmp_xsb.h
findall.o: /usr/include/setjmp.h /usr/include/bits/setjmp.h export.h
findall.o: heap_xsb.h heap_defs_xsb.h binding.h subp.h flags_xsb.h
findall.o: flag_defs_xsb.h loader_xsb.h cinterf.h varstring_xsb.h findall.h
findall.o: ptoc_tag_xsb_i.h
function.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
function.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
function.o: /usr/include/math.h /usr/include/features.h
function.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
function.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
function.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
function.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
function.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
function.o: /usr/include/bits/mathcalls.h auxlry.h basicdefs.h basictypes.h
function.o: cell_xsb.h celltags_xsb.h cell_def_xsb.h register.h psc_xsb.h
function.o: psc_defs.h memory_xsb.h deref.h heap_xsb.h heap_defs_xsb.h
function.o: binding.h
hash_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
hash_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
hash_xsb.o: /usr/include/stdio.h /usr/include/features.h
hash_xsb.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
hash_xsb.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
hash_xsb.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
hash_xsb.o: /usr/include/libio.h /usr/include/_G_config.h
hash_xsb.o: /usr/include/wchar.h /usr/include/bits/wchar.h
hash_xsb.o: /usr/include/gconv.h /usr/include/bits/stdio_lim.h
hash_xsb.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
hash_xsb.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
hash_xsb.o: /usr/include/endian.h /usr/include/bits/endian.h
hash_xsb.o: /usr/include/xlocale.h /usr/include/sys/types.h
hash_xsb.o: /usr/include/time.h /usr/include/sys/select.h
hash_xsb.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
hash_xsb.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
hash_xsb.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h auxlry.h
hash_xsb.o: basicdefs.h basictypes.h cell_xsb.h celltags_xsb.h cell_def_xsb.h
hash_xsb.o: hash_xsb.h psc_xsb.h psc_defs.h flags_xsb.h flag_defs_xsb.h
hashtable_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
hashtable_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
hashtable_xsb.o: /usr/include/stdio.h /usr/include/features.h
hashtable_xsb.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
hashtable_xsb.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
hashtable_xsb.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
hashtable_xsb.o: /usr/include/libio.h /usr/include/_G_config.h
hashtable_xsb.o: /usr/include/wchar.h /usr/include/bits/wchar.h
hashtable_xsb.o: /usr/include/gconv.h /usr/include/bits/stdio_lim.h
hashtable_xsb.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
hashtable_xsb.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
hashtable_xsb.o: /usr/include/endian.h /usr/include/bits/endian.h
hashtable_xsb.o: /usr/include/xlocale.h /usr/include/sys/types.h
hashtable_xsb.o: /usr/include/time.h /usr/include/sys/select.h
hashtable_xsb.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
hashtable_xsb.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
hashtable_xsb.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
hashtable_xsb.o: auxlry.h basicdefs.h basictypes.h cell_xsb.h celltags_xsb.h
hashtable_xsb.o: cell_def_xsb.h psc_xsb.h psc_defs.h cinterf.h export.h
hashtable_xsb.o: varstring_xsb.h trie_internals.h inst_xsb.h struct_manager.h
hashtable_xsb.o: tries.h macro_xsb.h debug_xsb.h table_status_defs.h
hashtable_xsb.o: slgdelay.h debugs/debug_delay.h error_xsb.h setjmp_xsb.h
hashtable_xsb.o: /usr/include/setjmp.h /usr/include/bits/setjmp.h
hashtable_xsb.o: hashtable_xsb.h tr_utils.h flags_xsb.h flag_defs_xsb.h
heap_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
heap_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
heap_xsb.o: /usr/include/string.h /usr/include/features.h
heap_xsb.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
heap_xsb.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
heap_xsb.o: /usr/include/xlocale.h /usr/include/stdlib.h
heap_xsb.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
heap_xsb.o: /usr/include/endian.h /usr/include/bits/endian.h
heap_xsb.o: /usr/include/sys/types.h /usr/include/bits/types.h
heap_xsb.o: /usr/include/bits/typesizes.h /usr/include/time.h
heap_xsb.o: /usr/include/sys/select.h /usr/include/bits/select.h
heap_xsb.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
heap_xsb.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
heap_xsb.o: /usr/include/alloca.h /usr/include/sys/stat.h
heap_xsb.o: /usr/include/bits/stat.h auxlry.h basicdefs.h basictypes.h
heap_xsb.o: cell_xsb.h celltags_xsb.h cell_def_xsb.h memory_xsb.h inst_xsb.h
heap_xsb.o: /usr/include/stdio.h /usr/include/libio.h
heap_xsb.o: /usr/include/_G_config.h /usr/include/wchar.h
heap_xsb.o: /usr/include/bits/wchar.h /usr/include/gconv.h
heap_xsb.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
heap_xsb.o: register.h psc_xsb.h psc_defs.h tries.h choice.h error_xsb.h
heap_xsb.o: setjmp_xsb.h /usr/include/setjmp.h /usr/include/bits/setjmp.h
heap_xsb.o: export.h macro_xsb.h debug_xsb.h table_status_defs.h slgdelay.h
heap_xsb.o: debugs/debug_delay.h realloc.h flags_xsb.h flag_defs_xsb.h
heap_xsb.o: heap_xsb.h heap_defs_xsb.h io_builtins_xsb.h io_defs_xsb.h
heap_xsb.o: token_xsb.h token_defs_xsb.h subp.h binding.h gc_profile.h
heap_xsb.o: gc_mark.h gc_print.h gc_slide.h gc_copy.h
init_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
init_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
init_xsb.o: /usr/include/stdio.h /usr/include/features.h
init_xsb.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
init_xsb.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
init_xsb.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
init_xsb.o: /usr/include/libio.h /usr/include/_G_config.h
init_xsb.o: /usr/include/wchar.h /usr/include/bits/wchar.h
init_xsb.o: /usr/include/gconv.h /usr/include/bits/stdio_lim.h
init_xsb.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
init_xsb.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
init_xsb.o: /usr/include/endian.h /usr/include/bits/endian.h
init_xsb.o: /usr/include/xlocale.h /usr/include/sys/types.h
init_xsb.o: /usr/include/time.h /usr/include/sys/select.h
init_xsb.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
init_xsb.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
init_xsb.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
init_xsb.o: /usr/include/string.h /usr/include/unistd.h
init_xsb.o: /usr/include/bits/posix_opt.h /usr/include/bits/environments.h
init_xsb.o: /usr/include/bits/confname.h /usr/include/getopt.h
init_xsb.o: /usr/include/sys/wait.h /usr/include/signal.h
init_xsb.o: /usr/include/bits/signum.h /usr/include/bits/siginfo.h
init_xsb.o: /usr/include/bits/sigaction.h /usr/include/bits/sigcontext.h
init_xsb.o: /usr/include/asm/sigcontext.h /usr/include/asm-i386/sigcontext.h
init_xsb.o: /usr/include/bits/sigstack.h /usr/include/sys/ucontext.h
init_xsb.o: /usr/include/bits/sigthread.h /usr/include/sys/resource.h
init_xsb.o: /usr/include/bits/resource.h auxlry.h basicdefs.h basictypes.h
init_xsb.o: cell_xsb.h celltags_xsb.h cell_def_xsb.h error_xsb.h setjmp_xsb.h
init_xsb.o: /usr/include/setjmp.h /usr/include/bits/setjmp.h export.h
init_xsb.o: inst_xsb.h psc_xsb.h psc_defs.h hash_xsb.h heap_xsb.h
init_xsb.o: heap_defs_xsb.h memory_xsb.h register.h tries.h choice.h
init_xsb.o: flags_xsb.h flag_defs_xsb.h loader_xsb.h extensions_xsb.h
init_xsb.o: macro_xsb.h debug_xsb.h table_status_defs.h slgdelay.h
init_xsb.o: debugs/debug_delay.h tr_utils.h io_builtins_xsb.h io_defs_xsb.h
init_xsb.o: token_xsb.h token_defs_xsb.h timer_defs_xsb.h sig_xsb.h
inst_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
inst_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
inst_xsb.o: auxlry.h basicdefs.h basictypes.h cell_xsb.h celltags_xsb.h
inst_xsb.o: cell_def_xsb.h inst_xsb.h subinst.h xsb_inst_list.h
io_builtins_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
io_builtins_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
io_builtins_xsb.o: /usr/include/stdio.h /usr/include/features.h
io_builtins_xsb.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
io_builtins_xsb.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
io_builtins_xsb.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
io_builtins_xsb.o: /usr/include/libio.h /usr/include/_G_config.h
io_builtins_xsb.o: /usr/include/wchar.h /usr/include/bits/wchar.h
io_builtins_xsb.o: /usr/include/gconv.h /usr/include/bits/stdio_lim.h
io_builtins_xsb.o: /usr/include/bits/sys_errlist.h /usr/include/signal.h
io_builtins_xsb.o: /usr/include/bits/sigset.h /usr/include/bits/signum.h
io_builtins_xsb.o: /usr/include/time.h /usr/include/bits/siginfo.h
io_builtins_xsb.o: /usr/include/bits/sigaction.h
io_builtins_xsb.o: /usr/include/bits/sigcontext.h
io_builtins_xsb.o: /usr/include/asm/sigcontext.h
io_builtins_xsb.o: /usr/include/asm-i386/sigcontext.h
io_builtins_xsb.o: /usr/include/bits/sigstack.h /usr/include/sys/ucontext.h
io_builtins_xsb.o: /usr/include/bits/pthreadtypes.h
io_builtins_xsb.o: /usr/include/bits/sigthread.h /usr/include/errno.h
io_builtins_xsb.o: /usr/include/bits/errno.h /usr/include/linux/errno.h
io_builtins_xsb.o: /usr/include/asm/errno.h /usr/include/asm-i386/errno.h
io_builtins_xsb.o: /usr/include/asm-generic/errno.h
io_builtins_xsb.o: /usr/include/asm-generic/errno-base.h
io_builtins_xsb.o: /usr/include/string.h /usr/include/xlocale.h
io_builtins_xsb.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
io_builtins_xsb.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
io_builtins_xsb.o: /usr/include/bits/endian.h /usr/include/sys/types.h
io_builtins_xsb.o: /usr/include/sys/select.h /usr/include/bits/select.h
io_builtins_xsb.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
io_builtins_xsb.o: /usr/include/alloca.h /usr/include/unistd.h
io_builtins_xsb.o: /usr/include/bits/posix_opt.h
io_builtins_xsb.o: /usr/include/bits/environments.h
io_builtins_xsb.o: /usr/include/bits/confname.h /usr/include/getopt.h
io_builtins_xsb.o: /usr/include/sys/stat.h /usr/include/bits/stat.h
io_builtins_xsb.o: setjmp_xsb.h /usr/include/setjmp.h
io_builtins_xsb.o: /usr/include/bits/setjmp.h auxlry.h basicdefs.h
io_builtins_xsb.o: basictypes.h cell_xsb.h celltags_xsb.h cell_def_xsb.h
io_builtins_xsb.o: error_xsb.h export.h cinterf.h varstring_xsb.h
io_builtins_xsb.o: memory_xsb.h psc_xsb.h psc_defs.h heap_xsb.h
io_builtins_xsb.o: heap_defs_xsb.h register.h flags_xsb.h flag_defs_xsb.h
io_builtins_xsb.o: inst_xsb.h loader_xsb.h subp.h tries.h choice.h
io_builtins_xsb.o: macro_xsb.h debug_xsb.h table_status_defs.h slgdelay.h
io_builtins_xsb.o: debugs/debug_delay.h io_builtins_xsb.h io_defs_xsb.h
io_builtins_xsb.o: token_xsb.h token_defs_xsb.h wind2unix.h binding.h deref.h
io_builtins_xsb.o: findall.h ptoc_tag_xsb_i.h
loader_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
loader_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
loader_xsb.o: /usr/include/stdio.h /usr/include/features.h
loader_xsb.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
loader_xsb.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
loader_xsb.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
loader_xsb.o: /usr/include/libio.h /usr/include/_G_config.h
loader_xsb.o: /usr/include/wchar.h /usr/include/bits/wchar.h
loader_xsb.o: /usr/include/gconv.h /usr/include/bits/stdio_lim.h
loader_xsb.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
loader_xsb.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
loader_xsb.o: /usr/include/endian.h /usr/include/bits/endian.h
loader_xsb.o: /usr/include/xlocale.h /usr/include/sys/types.h
loader_xsb.o: /usr/include/time.h /usr/include/sys/select.h
loader_xsb.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
loader_xsb.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
loader_xsb.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
loader_xsb.o: /usr/include/string.h auxlry.h basicdefs.h basictypes.h
loader_xsb.o: psc_xsb.h psc_defs.h loader_xsb.h extensions_xsb.h cell_xsb.h
loader_xsb.o: celltags_xsb.h cell_def_xsb.h heap_xsb.h heap_defs_xsb.h
loader_xsb.o: flags_xsb.h flag_defs_xsb.h tries.h macro_xsb.h debug_xsb.h
loader_xsb.o: table_status_defs.h slgdelay.h debugs/debug_delay.h error_xsb.h
loader_xsb.o: setjmp_xsb.h /usr/include/setjmp.h /usr/include/bits/setjmp.h
loader_xsb.o: export.h io_builtins_xsb.h io_defs_xsb.h token_xsb.h
loader_xsb.o: token_defs_xsb.h inst_xsb.h memory_xsb.h register.h
loader_xsb.o: varstring_xsb.h dynload.h
main_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
main_xsb.o: /usr/include/unistd.h /usr/include/features.h
main_xsb.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
main_xsb.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
main_xsb.o: /usr/include/bits/posix_opt.h /usr/include/bits/environments.h
main_xsb.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
main_xsb.o: /usr/include/bits/confname.h /usr/include/getopt.h
main_xsb.o: /usr/include/fcntl.h /usr/include/bits/fcntl.h
main_xsb.o: /usr/include/sys/types.h /usr/include/time.h
main_xsb.o: /usr/include/endian.h /usr/include/bits/endian.h
main_xsb.o: /usr/include/sys/select.h /usr/include/bits/select.h
main_xsb.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
main_xsb.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
main_xsb.o: /usr/include/bits/uio.h /usr/include/sys/stat.h
main_xsb.o: /usr/include/bits/stat.h /usr/include/stdio.h
main_xsb.o: /usr/include/libio.h /usr/include/_G_config.h
main_xsb.o: /usr/include/wchar.h /usr/include/bits/wchar.h
main_xsb.o: /usr/include/gconv.h /usr/include/bits/stdio_lim.h
main_xsb.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
main_xsb.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
main_xsb.o: /usr/include/xlocale.h /usr/include/alloca.h
main_xsb.o: /usr/include/string.h wind2unix.h emuloop.h export.h orient_xsb.h
main_xsb.o: basicdefs.h
memory_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
memory_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
memory_xsb.o: /usr/include/stdio.h /usr/include/features.h
memory_xsb.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
memory_xsb.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
memory_xsb.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
memory_xsb.o: /usr/include/libio.h /usr/include/_G_config.h
memory_xsb.o: /usr/include/wchar.h /usr/include/bits/wchar.h
memory_xsb.o: /usr/include/gconv.h /usr/include/bits/stdio_lim.h
memory_xsb.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
memory_xsb.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
memory_xsb.o: /usr/include/endian.h /usr/include/bits/endian.h
memory_xsb.o: /usr/include/xlocale.h /usr/include/sys/types.h
memory_xsb.o: /usr/include/time.h /usr/include/sys/select.h
memory_xsb.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
memory_xsb.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
memory_xsb.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
memory_xsb.o: /usr/include/string.h auxlry.h basicdefs.h basictypes.h
memory_xsb.o: cell_xsb.h celltags_xsb.h cell_def_xsb.h memory_xsb.h
memory_xsb.o: register.h psc_xsb.h psc_defs.h tries.h choice.h error_xsb.h
memory_xsb.o: setjmp_xsb.h /usr/include/setjmp.h /usr/include/bits/setjmp.h
memory_xsb.o: export.h macro_xsb.h debug_xsb.h table_status_defs.h slgdelay.h
memory_xsb.o: debugs/debug_delay.h flags_xsb.h flag_defs_xsb.h subp.h
orient_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
orient_xsb.o: /usr/include/unistd.h /usr/include/features.h
orient_xsb.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
orient_xsb.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
orient_xsb.o: /usr/include/bits/posix_opt.h /usr/include/bits/environments.h
orient_xsb.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
orient_xsb.o: /usr/include/bits/confname.h /usr/include/getopt.h
orient_xsb.o: /usr/include/fcntl.h /usr/include/bits/fcntl.h
orient_xsb.o: /usr/include/sys/types.h /usr/include/time.h
orient_xsb.o: /usr/include/endian.h /usr/include/bits/endian.h
orient_xsb.o: /usr/include/sys/select.h /usr/include/bits/select.h
orient_xsb.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
orient_xsb.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
orient_xsb.o: /usr/include/bits/uio.h /usr/include/sys/stat.h
orient_xsb.o: /usr/include/bits/stat.h /usr/include/stdio.h
orient_xsb.o: /usr/include/libio.h /usr/include/_G_config.h
orient_xsb.o: /usr/include/wchar.h /usr/include/bits/wchar.h
orient_xsb.o: /usr/include/gconv.h /usr/include/bits/stdio_lim.h
orient_xsb.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
orient_xsb.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
orient_xsb.o: /usr/include/xlocale.h /usr/include/alloca.h
orient_xsb.o: /usr/include/ctype.h /usr/include/string.h wind2unix.h export.h
orient_xsb.o: basicdefs.h basictypes.h cell_xsb.h celltags_xsb.h
orient_xsb.o: cell_def_xsb.h error_xsb.h setjmp_xsb.h /usr/include/setjmp.h
orient_xsb.o: /usr/include/bits/setjmp.h extensions_xsb.h
pathname_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
pathname_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
pathname_xsb.o: /usr/include/unistd.h /usr/include/features.h
pathname_xsb.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
pathname_xsb.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
pathname_xsb.o: /usr/include/bits/posix_opt.h
pathname_xsb.o: /usr/include/bits/environments.h /usr/include/bits/types.h
pathname_xsb.o: /usr/include/bits/typesizes.h /usr/include/bits/confname.h
pathname_xsb.o: /usr/include/getopt.h /usr/include/stdio.h
pathname_xsb.o: /usr/include/libio.h /usr/include/_G_config.h
pathname_xsb.o: /usr/include/wchar.h /usr/include/bits/wchar.h
pathname_xsb.o: /usr/include/gconv.h /usr/include/bits/stdio_lim.h
pathname_xsb.o: /usr/include/bits/sys_errlist.h /usr/include/errno.h
pathname_xsb.o: /usr/include/bits/errno.h /usr/include/linux/errno.h
pathname_xsb.o: /usr/include/asm/errno.h /usr/include/asm-i386/errno.h
pathname_xsb.o: /usr/include/asm-generic/errno.h
pathname_xsb.o: /usr/include/asm-generic/errno-base.h /usr/include/string.h
pathname_xsb.o: /usr/include/xlocale.h /usr/include/stdlib.h
pathname_xsb.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
pathname_xsb.o: /usr/include/endian.h /usr/include/bits/endian.h
pathname_xsb.o: /usr/include/sys/types.h /usr/include/time.h
pathname_xsb.o: /usr/include/sys/select.h /usr/include/bits/select.h
pathname_xsb.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
pathname_xsb.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
pathname_xsb.o: /usr/include/alloca.h /usr/include/ctype.h
pathname_xsb.o: /usr/include/sys/stat.h /usr/include/bits/stat.h wind2unix.h
pathname_xsb.o: export.h /usr/include/pwd.h setjmp_xsb.h
pathname_xsb.o: /usr/include/setjmp.h /usr/include/bits/setjmp.h auxlry.h
pathname_xsb.o: basicdefs.h basictypes.h psc_xsb.h psc_defs.h cell_xsb.h
pathname_xsb.o: celltags_xsb.h cell_def_xsb.h cinterf.h varstring_xsb.h
pathname_xsb.o: error_xsb.h flags_xsb.h flag_defs_xsb.h extensions_xsb.h
psc_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
psc_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
psc_xsb.o: /usr/include/stdio.h /usr/include/features.h
psc_xsb.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
psc_xsb.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
psc_xsb.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
psc_xsb.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
psc_xsb.o: /usr/include/bits/wchar.h /usr/include/gconv.h
psc_xsb.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
psc_xsb.o: /usr/include/string.h /usr/include/xlocale.h auxlry.h basicdefs.h
psc_xsb.o: basictypes.h cell_xsb.h celltags_xsb.h cell_def_xsb.h error_xsb.h
psc_xsb.o: setjmp_xsb.h /usr/include/setjmp.h /usr/include/bits/setjmp.h
psc_xsb.o: /usr/include/bits/sigset.h export.h psc_xsb.h psc_defs.h tries.h
psc_xsb.o: hash_xsb.h macro_xsb.h debug_xsb.h table_status_defs.h slgdelay.h
psc_xsb.o: debugs/debug_delay.h loader_xsb.h flags_xsb.h flag_defs_xsb.h
psc_xsb.o: sig_xsb.h inst_xsb.h memory_xsb.h register.h
random_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
random_xsb.o: cell_xsb.h celltags_xsb.h cell_def_xsb.h cinterf.h basicdefs.h
random_xsb.o: basictypes.h export.h varstring_xsb.h deref.h register.h
random_xsb.o: psc_xsb.h psc_defs.h ptoc_tag_xsb_i.h
remove_unf.o: /usr/include/stdio.h /usr/include/features.h
remove_unf.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
remove_unf.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
remove_unf.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
remove_unf.o: /usr/include/libio.h /usr/include/_G_config.h
remove_unf.o: /usr/include/wchar.h /usr/include/bits/wchar.h
remove_unf.o: /usr/include/gconv.h /usr/include/bits/stdio_lim.h
remove_unf.o: /usr/include/bits/sys_errlist.h
remove_unf.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
remove_unf.o: basictypes.h cell_xsb.h celltags_xsb.h cell_def_xsb.h
remove_unf.o: error_xsb.h setjmp_xsb.h /usr/include/setjmp.h
remove_unf.o: /usr/include/bits/setjmp.h /usr/include/bits/sigset.h export.h
remove_unf.o: psc_xsb.h psc_defs.h tries.h macro_xsb.h debug_xsb.h
remove_unf.o: table_status_defs.h slgdelay.h debugs/debug_delay.h register.h
residual.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
residual.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
residual.o: /usr/include/stdio.h /usr/include/features.h
residual.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
residual.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
residual.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
residual.o: /usr/include/libio.h /usr/include/_G_config.h
residual.o: /usr/include/wchar.h /usr/include/bits/wchar.h
residual.o: /usr/include/gconv.h /usr/include/bits/stdio_lim.h
residual.o: /usr/include/bits/sys_errlist.h debugs/debug_residual.h auxlry.h
residual.o: basicdefs.h basictypes.h cell_xsb.h celltags_xsb.h cell_def_xsb.h
residual.o: memory_xsb.h psc_xsb.h psc_defs.h register.h heap_xsb.h
residual.o: heap_defs_xsb.h binding.h tries.h macro_xsb.h debug_xsb.h
residual.o: table_status_defs.h slgdelay.h debugs/debug_delay.h error_xsb.h
residual.o: setjmp_xsb.h /usr/include/setjmp.h /usr/include/bits/setjmp.h
residual.o: /usr/include/bits/sigset.h export.h io_builtins_xsb.h
residual.o: io_defs_xsb.h token_xsb.h token_defs_xsb.h flags_xsb.h
residual.o: flag_defs_xsb.h
scc_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
scc_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
scc_xsb.o: /usr/include/stdio.h /usr/include/features.h
scc_xsb.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
scc_xsb.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
scc_xsb.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
scc_xsb.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
scc_xsb.o: /usr/include/bits/wchar.h /usr/include/gconv.h
scc_xsb.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
scc_xsb.o: auxlry.h basicdefs.h basictypes.h cell_xsb.h celltags_xsb.h
scc_xsb.o: cell_def_xsb.h register.h psc_xsb.h psc_defs.h tries.h macro_xsb.h
scc_xsb.o: debug_xsb.h table_status_defs.h slgdelay.h debugs/debug_delay.h
slgdelay.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
slgdelay.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
slgdelay.o: /usr/include/stdio.h /usr/include/features.h
slgdelay.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
slgdelay.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
slgdelay.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
slgdelay.o: /usr/include/libio.h /usr/include/_G_config.h
slgdelay.o: /usr/include/wchar.h /usr/include/bits/wchar.h
slgdelay.o: /usr/include/gconv.h /usr/include/bits/stdio_lim.h
slgdelay.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
slgdelay.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
slgdelay.o: /usr/include/endian.h /usr/include/bits/endian.h
slgdelay.o: /usr/include/xlocale.h /usr/include/sys/types.h
slgdelay.o: /usr/include/time.h /usr/include/sys/select.h
slgdelay.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
slgdelay.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
slgdelay.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
slgdelay.o: debugs/debug_delay.h auxlry.h basicdefs.h basictypes.h cell_xsb.h
slgdelay.o: celltags_xsb.h cell_def_xsb.h psc_xsb.h psc_defs.h register.h
slgdelay.o: trie_internals.h inst_xsb.h struct_manager.h tries.h memory_xsb.h
slgdelay.o: choice.h macro_xsb.h debug_xsb.h table_status_defs.h slgdelay.h
slgdelay.o: tr_utils.h error_xsb.h setjmp_xsb.h /usr/include/setjmp.h
slgdelay.o: /usr/include/bits/setjmp.h export.h io_builtins_xsb.h
slgdelay.o: io_defs_xsb.h token_xsb.h token_defs_xsb.h
socket_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
socket_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
socket_xsb.o: /usr/include/errno.h /usr/include/features.h
socket_xsb.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
socket_xsb.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
socket_xsb.o: /usr/include/bits/errno.h /usr/include/linux/errno.h
socket_xsb.o: /usr/include/asm/errno.h /usr/include/asm-i386/errno.h
socket_xsb.o: /usr/include/asm-generic/errno.h
socket_xsb.o: /usr/include/asm-generic/errno-base.h /usr/include/stdio.h
socket_xsb.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
socket_xsb.o: /usr/include/libio.h /usr/include/_G_config.h
socket_xsb.o: /usr/include/wchar.h /usr/include/bits/wchar.h
socket_xsb.o: /usr/include/gconv.h /usr/include/bits/stdio_lim.h
socket_xsb.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
socket_xsb.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
socket_xsb.o: /usr/include/endian.h /usr/include/bits/endian.h
socket_xsb.o: /usr/include/xlocale.h /usr/include/sys/types.h
socket_xsb.o: /usr/include/time.h /usr/include/sys/select.h
socket_xsb.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
socket_xsb.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
socket_xsb.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
socket_xsb.o: /usr/include/string.h /usr/include/sys/stat.h
socket_xsb.o: /usr/include/bits/stat.h /usr/include/signal.h
socket_xsb.o: /usr/include/bits/signum.h /usr/include/bits/siginfo.h
socket_xsb.o: /usr/include/bits/sigaction.h /usr/include/bits/sigcontext.h
socket_xsb.o: /usr/include/asm/sigcontext.h
socket_xsb.o: /usr/include/asm-i386/sigcontext.h /usr/include/bits/sigstack.h
socket_xsb.o: /usr/include/sys/ucontext.h /usr/include/bits/sigthread.h
socket_xsb.o: wind2unix.h xsb_time.h /usr/include/sys/time.h
socket_xsb.o: /usr/include/sys/socket.h /usr/include/sys/uio.h
socket_xsb.o: /usr/include/bits/uio.h /usr/include/bits/socket.h
socket_xsb.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
socket_xsb.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
socket_xsb.o: /usr/include/bits/posix2_lim.h /usr/include/bits/xopen_lim.h
socket_xsb.o: /usr/include/bits/sockaddr.h /usr/include/asm/socket.h
socket_xsb.o: /usr/include/asm-i386/socket.h /usr/include/asm/sockios.h
socket_xsb.o: /usr/include/asm-i386/sockios.h /usr/include/netdb.h
socket_xsb.o: /usr/include/netinet/in.h /usr/include/stdint.h
socket_xsb.o: /usr/include/bits/in.h /usr/include/bits/byteswap.h
socket_xsb.o: /usr/include/rpc/netdb.h /usr/include/bits/netdb.h
socket_xsb.o: /usr/include/arpa/inet.h /usr/include/unistd.h
socket_xsb.o: /usr/include/bits/posix_opt.h /usr/include/bits/environments.h
socket_xsb.o: /usr/include/bits/confname.h /usr/include/getopt.h auxlry.h
socket_xsb.o: basicdefs.h basictypes.h cell_xsb.h celltags_xsb.h
socket_xsb.o: cell_def_xsb.h error_xsb.h setjmp_xsb.h /usr/include/setjmp.h
socket_xsb.o: /usr/include/bits/setjmp.h export.h cinterf.h varstring_xsb.h
socket_xsb.o: io_builtins_xsb.h io_defs_xsb.h token_xsb.h token_defs_xsb.h
socket_xsb.o: socket_xsb.h socket_defs_xsb.h timer_xsb.h flags_xsb.h
socket_xsb.o: flag_defs_xsb.h timer_defs_xsb.h psc_xsb.h psc_defs.h
socket_xsb.o: register.h
string_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
string_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
string_xsb.o: /usr/include/stdio.h /usr/include/features.h
string_xsb.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
string_xsb.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
string_xsb.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
string_xsb.o: /usr/include/libio.h /usr/include/_G_config.h
string_xsb.o: /usr/include/wchar.h /usr/include/bits/wchar.h
string_xsb.o: /usr/include/gconv.h /usr/include/bits/stdio_lim.h
string_xsb.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
string_xsb.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
string_xsb.o: /usr/include/endian.h /usr/include/bits/endian.h
string_xsb.o: /usr/include/xlocale.h /usr/include/sys/types.h
string_xsb.o: /usr/include/time.h /usr/include/sys/select.h
string_xsb.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
string_xsb.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
string_xsb.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
string_xsb.o: /usr/include/string.h auxlry.h basicdefs.h basictypes.h
string_xsb.o: cell_xsb.h celltags_xsb.h cell_def_xsb.h error_xsb.h
string_xsb.o: setjmp_xsb.h /usr/include/setjmp.h /usr/include/bits/setjmp.h
string_xsb.o: export.h psc_xsb.h psc_defs.h hash_xsb.h tries.h choice.h
string_xsb.o: deref.h memory_xsb.h heap_xsb.h heap_defs_xsb.h register.h
string_xsb.o: flags_xsb.h flag_defs_xsb.h binding.h builtin.h cinterf.h
string_xsb.o: varstring_xsb.h sp_unify_xsb_i.h string_xsb.h ptoc_tag_xsb_i.h
storage_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
storage_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
storage_xsb.o: /usr/include/stdio.h /usr/include/features.h
storage_xsb.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
storage_xsb.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
storage_xsb.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
storage_xsb.o: /usr/include/libio.h /usr/include/_G_config.h
storage_xsb.o: /usr/include/wchar.h /usr/include/bits/wchar.h
storage_xsb.o: /usr/include/gconv.h /usr/include/bits/stdio_lim.h
storage_xsb.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
storage_xsb.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
storage_xsb.o: /usr/include/endian.h /usr/include/bits/endian.h
storage_xsb.o: /usr/include/xlocale.h /usr/include/sys/types.h
storage_xsb.o: /usr/include/time.h /usr/include/sys/select.h
storage_xsb.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
storage_xsb.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
storage_xsb.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
storage_xsb.o: auxlry.h basicdefs.h basictypes.h cell_xsb.h celltags_xsb.h
storage_xsb.o: cell_def_xsb.h psc_xsb.h psc_defs.h cinterf.h export.h
storage_xsb.o: varstring_xsb.h trie_internals.h inst_xsb.h struct_manager.h
storage_xsb.o: tries.h macro_xsb.h debug_xsb.h table_status_defs.h slgdelay.h
storage_xsb.o: debugs/debug_delay.h error_xsb.h setjmp_xsb.h
storage_xsb.o: /usr/include/setjmp.h /usr/include/bits/setjmp.h tr_utils.h
storage_xsb.o: storage_xsb.h storage_xsb_defs.h hashtable_xsb.h flags_xsb.h
storage_xsb.o: flag_defs_xsb.h
struct_manager.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
struct_manager.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
struct_manager.o: /usr/include/stdio.h /usr/include/features.h
struct_manager.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
struct_manager.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
struct_manager.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
struct_manager.o: /usr/include/libio.h /usr/include/_G_config.h
struct_manager.o: /usr/include/wchar.h /usr/include/bits/wchar.h
struct_manager.o: /usr/include/gconv.h /usr/include/bits/stdio_lim.h
struct_manager.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
struct_manager.o: /usr/include/bits/waitflags.h
struct_manager.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
struct_manager.o: /usr/include/bits/endian.h /usr/include/xlocale.h
struct_manager.o: /usr/include/sys/types.h /usr/include/time.h
struct_manager.o: /usr/include/sys/select.h /usr/include/bits/select.h
struct_manager.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
struct_manager.o: /usr/include/sys/sysmacros.h
struct_manager.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
struct_manager.o: auxlry.h basicdefs.h basictypes.h struct_manager.h
struct_manager.o: cell_xsb.h celltags_xsb.h cell_def_xsb.h error_xsb.h
struct_manager.o: setjmp_xsb.h /usr/include/setjmp.h
struct_manager.o: /usr/include/bits/setjmp.h export.h debug_xsb.h flags_xsb.h
struct_manager.o: flag_defs_xsb.h
sub_delete.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
sub_delete.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
sub_delete.o: /usr/include/stdio.h /usr/include/features.h
sub_delete.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
sub_delete.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
sub_delete.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
sub_delete.o: /usr/include/libio.h /usr/include/_G_config.h
sub_delete.o: /usr/include/wchar.h /usr/include/bits/wchar.h
sub_delete.o: /usr/include/gconv.h /usr/include/bits/stdio_lim.h
sub_delete.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
sub_delete.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
sub_delete.o: /usr/include/endian.h /usr/include/bits/endian.h
sub_delete.o: /usr/include/xlocale.h /usr/include/sys/types.h
sub_delete.o: /usr/include/time.h /usr/include/sys/select.h
sub_delete.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
sub_delete.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
sub_delete.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h auxlry.h
sub_delete.o: basicdefs.h basictypes.h cell_xsb.h celltags_xsb.h
sub_delete.o: cell_def_xsb.h psc_xsb.h psc_defs.h trie_internals.h inst_xsb.h
sub_delete.o: struct_manager.h tries.h macro_xsb.h debug_xsb.h
sub_delete.o: table_status_defs.h slgdelay.h debugs/debug_delay.h error_xsb.h
sub_delete.o: setjmp_xsb.h /usr/include/setjmp.h /usr/include/bits/setjmp.h
sub_delete.o: export.h
subp.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
subp.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
subp.o: debugs/debug_attv.h /usr/include/stdio.h /usr/include/features.h
subp.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
subp.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
subp.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
subp.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
subp.o: /usr/include/bits/wchar.h /usr/include/gconv.h
subp.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
subp.o: /usr/include/signal.h /usr/include/bits/sigset.h
subp.o: /usr/include/bits/signum.h /usr/include/time.h
subp.o: /usr/include/bits/siginfo.h /usr/include/bits/sigaction.h
subp.o: /usr/include/bits/sigcontext.h /usr/include/asm/sigcontext.h
subp.o: /usr/include/asm-i386/sigcontext.h /usr/include/bits/sigstack.h
subp.o: /usr/include/sys/ucontext.h /usr/include/bits/pthreadtypes.h
subp.o: /usr/include/bits/sigthread.h auxlry.h basicdefs.h basictypes.h
subp.o: cell_xsb.h celltags_xsb.h cell_def_xsb.h error_xsb.h setjmp_xsb.h
subp.o: /usr/include/setjmp.h /usr/include/bits/setjmp.h export.h psc_xsb.h
subp.o: psc_defs.h memory_xsb.h register.h heap_xsb.h heap_defs_xsb.h deref.h
subp.o: flags_xsb.h flag_defs_xsb.h binding.h trie_internals.h inst_xsb.h
subp.o: struct_manager.h tries.h trassert.h choice.h token_xsb.h
subp.o: token_defs_xsb.h sig_xsb.h macro_xsb.h debug_xsb.h
subp.o: table_status_defs.h slgdelay.h debugs/debug_delay.h table_stats.h
subp.o: unify_xsb.h hash_xsb.h
system_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
system_xsb.o: /usr/include/stdio.h /usr/include/features.h
system_xsb.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
system_xsb.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
system_xsb.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
system_xsb.o: /usr/include/libio.h /usr/include/_G_config.h
system_xsb.o: /usr/include/wchar.h /usr/include/bits/wchar.h
system_xsb.o: /usr/include/gconv.h /usr/include/bits/stdio_lim.h
system_xsb.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
system_xsb.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
system_xsb.o: /usr/include/endian.h /usr/include/bits/endian.h
system_xsb.o: /usr/include/xlocale.h /usr/include/sys/types.h
system_xsb.o: /usr/include/time.h /usr/include/sys/select.h
system_xsb.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
system_xsb.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
system_xsb.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
system_xsb.o: /usr/include/signal.h /usr/include/bits/signum.h
system_xsb.o: /usr/include/bits/siginfo.h /usr/include/bits/sigaction.h
system_xsb.o: /usr/include/bits/sigcontext.h /usr/include/asm/sigcontext.h
system_xsb.o: /usr/include/asm-i386/sigcontext.h /usr/include/bits/sigstack.h
system_xsb.o: /usr/include/sys/ucontext.h /usr/include/bits/sigthread.h
system_xsb.o: /usr/include/string.h /usr/include/sys/stat.h
system_xsb.o: /usr/include/bits/stat.h /usr/include/errno.h
system_xsb.o: /usr/include/bits/errno.h /usr/include/linux/errno.h
system_xsb.o: /usr/include/asm/errno.h /usr/include/asm-i386/errno.h
system_xsb.o: /usr/include/asm-generic/errno.h
system_xsb.o: /usr/include/asm-generic/errno-base.h /usr/include/ctype.h
system_xsb.o: /usr/include/unistd.h /usr/include/bits/posix_opt.h
system_xsb.o: /usr/include/bits/environments.h /usr/include/bits/confname.h
system_xsb.o: /usr/include/getopt.h /usr/include/sys/wait.h
system_xsb.o: /usr/include/sys/resource.h /usr/include/bits/resource.h
system_xsb.o: /usr/include/dirent.h /usr/include/bits/dirent.h
system_xsb.o: /usr/include/bits/posix1_lim.h /usr/include/bits/local_lim.h
system_xsb.o: /usr/include/linux/limits.h /usr/include/fcntl.h
system_xsb.o: /usr/include/bits/fcntl.h /usr/include/bits/uio.h auxlry.h
system_xsb.o: basicdefs.h basictypes.h cell_xsb.h celltags_xsb.h
system_xsb.o: cell_def_xsb.h error_xsb.h setjmp_xsb.h /usr/include/setjmp.h
system_xsb.o: /usr/include/bits/setjmp.h export.h cinterf.h varstring_xsb.h
system_xsb.o: syscall_xsb.h io_builtins_xsb.h io_defs_xsb.h token_xsb.h
system_xsb.o: token_defs_xsb.h wind2unix.h system_xsb.h system_defs_xsb.h
system_xsb.o: register.h psc_xsb.h psc_defs.h
table_stats.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
table_stats.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
table_stats.o: /usr/include/stdio.h /usr/include/features.h
table_stats.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
table_stats.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
table_stats.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
table_stats.o: /usr/include/libio.h /usr/include/_G_config.h
table_stats.o: /usr/include/wchar.h /usr/include/bits/wchar.h
table_stats.o: /usr/include/gconv.h /usr/include/bits/stdio_lim.h
table_stats.o: /usr/include/bits/sys_errlist.h auxlry.h basicdefs.h
table_stats.o: basictypes.h cell_xsb.h celltags_xsb.h cell_def_xsb.h
table_stats.o: psc_xsb.h psc_defs.h table_stats.h struct_manager.h
table_stats.o: trie_internals.h inst_xsb.h tries.h macro_xsb.h debug_xsb.h
table_stats.o: table_status_defs.h slgdelay.h debugs/debug_delay.h
table_stats.o: error_xsb.h setjmp_xsb.h /usr/include/setjmp.h
table_stats.o: /usr/include/bits/setjmp.h /usr/include/bits/sigset.h export.h
table_stats.o: flags_xsb.h flag_defs_xsb.h
tables.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
tables.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
tables.o: debugs/debug_tables.h debugs/debug_delay.h /usr/include/stdio.h
tables.o: /usr/include/features.h /usr/include/sys/cdefs.h
tables.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
tables.o: /usr/include/gnu/stubs-32.h /usr/include/bits/types.h
tables.o: /usr/include/bits/typesizes.h /usr/include/libio.h
tables.o: /usr/include/_G_config.h /usr/include/wchar.h
tables.o: /usr/include/bits/wchar.h /usr/include/gconv.h
tables.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
tables.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
tables.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
tables.o: /usr/include/bits/endian.h /usr/include/xlocale.h
tables.o: /usr/include/sys/types.h /usr/include/time.h
tables.o: /usr/include/sys/select.h /usr/include/bits/select.h
tables.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
tables.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
tables.o: /usr/include/alloca.h auxlry.h basicdefs.h basictypes.h cell_xsb.h
tables.o: celltags_xsb.h cell_def_xsb.h heap_xsb.h heap_defs_xsb.h
tables.o: memory_xsb.h register.h psc_xsb.h psc_defs.h binding.h
tables.o: table_stats.h struct_manager.h trie_internals.h inst_xsb.h tries.h
tables.o: macro_xsb.h debug_xsb.h table_status_defs.h slgdelay.h error_xsb.h
tables.o: setjmp_xsb.h /usr/include/setjmp.h /usr/include/bits/setjmp.h
tables.o: export.h flags_xsb.h flag_defs_xsb.h tst_utils.h loader_xsb.h
tables.o: sub_tables_xsb_i.h tst_aux.h debugs/debug_tries.h dynamic_stack.h
tables.o: deref.h
timer_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
timer_xsb.o: /usr/include/sys/types.h /usr/include/features.h
timer_xsb.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
timer_xsb.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
timer_xsb.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
timer_xsb.o: /usr/include/time.h /usr/include/endian.h
timer_xsb.o: /usr/include/bits/endian.h /usr/include/sys/select.h
timer_xsb.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
timer_xsb.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
timer_xsb.o: /usr/include/bits/pthreadtypes.h /usr/include/stdlib.h
timer_xsb.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
timer_xsb.o: /usr/include/xlocale.h /usr/include/alloca.h
timer_xsb.o: /usr/include/signal.h /usr/include/bits/signum.h
timer_xsb.o: /usr/include/bits/siginfo.h /usr/include/bits/sigaction.h
timer_xsb.o: /usr/include/bits/sigcontext.h /usr/include/asm/sigcontext.h
timer_xsb.o: /usr/include/asm-i386/sigcontext.h /usr/include/bits/sigstack.h
timer_xsb.o: /usr/include/sys/ucontext.h /usr/include/bits/sigthread.h
timer_xsb.o: /usr/include/unistd.h /usr/include/bits/posix_opt.h
timer_xsb.o: /usr/include/bits/environments.h /usr/include/bits/confname.h
timer_xsb.o: /usr/include/getopt.h /usr/include/stdio.h /usr/include/libio.h
timer_xsb.o: /usr/include/_G_config.h /usr/include/wchar.h
timer_xsb.o: /usr/include/bits/wchar.h /usr/include/gconv.h
timer_xsb.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
timer_xsb.o: cell_xsb.h celltags_xsb.h cell_def_xsb.h error_xsb.h
timer_xsb.o: basictypes.h setjmp_xsb.h /usr/include/setjmp.h
timer_xsb.o: /usr/include/bits/setjmp.h export.h timer_xsb.h flags_xsb.h
timer_xsb.o: flag_defs_xsb.h timer_defs_xsb.h basicdefs.h
token_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
token_xsb.o: /usr/include/stdio.h /usr/include/features.h
token_xsb.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
token_xsb.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
token_xsb.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
token_xsb.o: /usr/include/libio.h /usr/include/_G_config.h
token_xsb.o: /usr/include/wchar.h /usr/include/bits/wchar.h
token_xsb.o: /usr/include/gconv.h /usr/include/bits/stdio_lim.h
token_xsb.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
token_xsb.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
token_xsb.o: /usr/include/endian.h /usr/include/bits/endian.h
token_xsb.o: /usr/include/xlocale.h /usr/include/sys/types.h
token_xsb.o: /usr/include/time.h /usr/include/sys/select.h
token_xsb.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
token_xsb.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
token_xsb.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
token_xsb.o: /usr/include/math.h /usr/include/bits/huge_val.h
token_xsb.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
token_xsb.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
token_xsb.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
token_xsb.o: auxlry.h basicdefs.h basictypes.h token_xsb.h token_defs_xsb.h
token_xsb.o: cell_xsb.h celltags_xsb.h cell_def_xsb.h psc_xsb.h psc_defs.h
token_xsb.o: subp.h register.h error_xsb.h setjmp_xsb.h /usr/include/setjmp.h
token_xsb.o: /usr/include/bits/setjmp.h export.h
tr_utils.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
tr_utils.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
tr_utils.o: /usr/include/stdio.h /usr/include/features.h
tr_utils.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
tr_utils.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
tr_utils.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
tr_utils.o: /usr/include/libio.h /usr/include/_G_config.h
tr_utils.o: /usr/include/wchar.h /usr/include/bits/wchar.h
tr_utils.o: /usr/include/gconv.h /usr/include/bits/stdio_lim.h
tr_utils.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
tr_utils.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
tr_utils.o: /usr/include/endian.h /usr/include/bits/endian.h
tr_utils.o: /usr/include/xlocale.h /usr/include/sys/types.h
tr_utils.o: /usr/include/time.h /usr/include/sys/select.h
tr_utils.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
tr_utils.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
tr_utils.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
tr_utils.o: debugs/debug_tries.h auxlry.h basicdefs.h basictypes.h cell_xsb.h
tr_utils.o: celltags_xsb.h cell_def_xsb.h cinterf.h export.h varstring_xsb.h
tr_utils.o: binding.h psc_xsb.h psc_defs.h heap_xsb.h heap_defs_xsb.h
tr_utils.o: memory_xsb.h register.h deref.h flags_xsb.h flag_defs_xsb.h
tr_utils.o: trie_internals.h inst_xsb.h struct_manager.h tries.h tst_aux.h
tr_utils.o: debugs/debug_tables.h dynamic_stack.h cut_xsb.h macro_xsb.h
tr_utils.o: debug_xsb.h table_status_defs.h slgdelay.h debugs/debug_delay.h
tr_utils.o: sw_envs.h choice.h error_xsb.h setjmp_xsb.h /usr/include/setjmp.h
tr_utils.o: /usr/include/bits/setjmp.h io_builtins_xsb.h io_defs_xsb.h
tr_utils.o: token_xsb.h token_defs_xsb.h trassert.h tr_utils.h tst_utils.h
tr_utils.o: subp.h ptoc_tag_xsb_i.h term_psc_xsb_i.h
trace_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
trace_xsb.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
trace_xsb.o: /usr/include/stdio.h /usr/include/features.h
trace_xsb.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
trace_xsb.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
trace_xsb.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
trace_xsb.o: /usr/include/libio.h /usr/include/_G_config.h
trace_xsb.o: /usr/include/wchar.h /usr/include/bits/wchar.h
trace_xsb.o: /usr/include/gconv.h /usr/include/bits/stdio_lim.h
trace_xsb.o: /usr/include/bits/sys_errlist.h auxlry.h basicdefs.h
trace_xsb.o: basictypes.h cell_xsb.h celltags_xsb.h cell_def_xsb.h inst_xsb.h
trace_xsb.o: memory_xsb.h register.h psc_xsb.h psc_defs.h table_stats.h
trace_xsb.o: struct_manager.h trie_internals.h tries.h macro_xsb.h
trace_xsb.o: debug_xsb.h table_status_defs.h slgdelay.h debugs/debug_delay.h
trace_xsb.o: choice.h flags_xsb.h flag_defs_xsb.h heap_xsb.h heap_defs_xsb.h
trie_lookup.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
trie_lookup.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
trie_lookup.o: debugs/debug_tries.h /usr/include/stdio.h
trie_lookup.o: /usr/include/features.h /usr/include/sys/cdefs.h
trie_lookup.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
trie_lookup.o: /usr/include/gnu/stubs-32.h /usr/include/bits/types.h
trie_lookup.o: /usr/include/bits/typesizes.h /usr/include/libio.h
trie_lookup.o: /usr/include/_G_config.h /usr/include/wchar.h
trie_lookup.o: /usr/include/bits/wchar.h /usr/include/gconv.h
trie_lookup.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
trie_lookup.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
trie_lookup.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
trie_lookup.o: /usr/include/bits/endian.h /usr/include/xlocale.h
trie_lookup.o: /usr/include/sys/types.h /usr/include/time.h
trie_lookup.o: /usr/include/sys/select.h /usr/include/bits/select.h
trie_lookup.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
trie_lookup.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
trie_lookup.o: /usr/include/alloca.h auxlry.h basicdefs.h basictypes.h
trie_lookup.o: cell_xsb.h celltags_xsb.h cell_def_xsb.h error_xsb.h
trie_lookup.o: setjmp_xsb.h /usr/include/setjmp.h /usr/include/bits/setjmp.h
trie_lookup.o: export.h psc_xsb.h psc_defs.h deref.h table_stats.h
trie_lookup.o: struct_manager.h trie_internals.h inst_xsb.h tries.h tst_aux.h
trie_lookup.o: debugs/debug_tables.h dynamic_stack.h subp.h debug_xsb.h
trie_lookup.o: flags_xsb.h flag_defs_xsb.h
trie_search.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
trie_search.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
trie_search.o: debugs/debug_tries.h /usr/include/stdio.h
trie_search.o: /usr/include/features.h /usr/include/sys/cdefs.h
trie_search.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
trie_search.o: /usr/include/gnu/stubs-32.h /usr/include/bits/types.h
trie_search.o: /usr/include/bits/typesizes.h /usr/include/libio.h
trie_search.o: /usr/include/_G_config.h /usr/include/wchar.h
trie_search.o: /usr/include/bits/wchar.h /usr/include/gconv.h
trie_search.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
trie_search.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
trie_search.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
trie_search.o: /usr/include/bits/endian.h /usr/include/xlocale.h
trie_search.o: /usr/include/sys/types.h /usr/include/time.h
trie_search.o: /usr/include/sys/select.h /usr/include/bits/select.h
trie_search.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
trie_search.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
trie_search.o: /usr/include/alloca.h auxlry.h basicdefs.h basictypes.h
trie_search.o: cell_xsb.h celltags_xsb.h cell_def_xsb.h error_xsb.h
trie_search.o: setjmp_xsb.h /usr/include/setjmp.h /usr/include/bits/setjmp.h
trie_search.o: export.h deref.h psc_xsb.h psc_defs.h trie_internals.h
trie_search.o: inst_xsb.h struct_manager.h tries.h tst_aux.h
trie_search.o: debugs/debug_tables.h dynamic_stack.h debug_xsb.h flags_xsb.h
trie_search.o: flag_defs_xsb.h
tries.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
tries.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
tries.o: /usr/include/stdio.h /usr/include/features.h
tries.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
tries.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
tries.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
tries.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
tries.o: /usr/include/bits/wchar.h /usr/include/gconv.h
tries.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
tries.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
tries.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
tries.o: /usr/include/bits/endian.h /usr/include/xlocale.h
tries.o: /usr/include/sys/types.h /usr/include/time.h
tries.o: /usr/include/sys/select.h /usr/include/bits/select.h
tries.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
tries.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
tries.o: /usr/include/alloca.h debugs/debug_tries.h auxlry.h basicdefs.h
tries.o: basictypes.h cell_xsb.h celltags_xsb.h cell_def_xsb.h inst_xsb.h
tries.o: psc_xsb.h psc_defs.h heap_xsb.h heap_defs_xsb.h flags_xsb.h
tries.o: flag_defs_xsb.h deref.h memory_xsb.h register.h binding.h
tries.o: trie_internals.h struct_manager.h tries.h macro_xsb.h debug_xsb.h
tries.o: table_status_defs.h slgdelay.h debugs/debug_delay.h choice.h
tries.o: cinterf.h export.h varstring_xsb.h error_xsb.h setjmp_xsb.h
tries.o: /usr/include/setjmp.h /usr/include/bits/setjmp.h tr_utils.h
tries.o: term_psc_xsb_i.h ptoc_tag_xsb_i.h
tst_insert.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
tst_insert.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
tst_insert.o: /usr/include/stdio.h /usr/include/features.h
tst_insert.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
tst_insert.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
tst_insert.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
tst_insert.o: /usr/include/libio.h /usr/include/_G_config.h
tst_insert.o: /usr/include/wchar.h /usr/include/bits/wchar.h
tst_insert.o: /usr/include/gconv.h /usr/include/bits/stdio_lim.h
tst_insert.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
tst_insert.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
tst_insert.o: /usr/include/endian.h /usr/include/bits/endian.h
tst_insert.o: /usr/include/xlocale.h /usr/include/sys/types.h
tst_insert.o: /usr/include/time.h /usr/include/sys/select.h
tst_insert.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
tst_insert.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
tst_insert.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
tst_insert.o: debugs/debug_tries.h auxlry.h basicdefs.h basictypes.h
tst_insert.o: cell_xsb.h celltags_xsb.h cell_def_xsb.h inst_xsb.h register.h
tst_insert.o: psc_xsb.h psc_defs.h error_xsb.h setjmp_xsb.h
tst_insert.o: /usr/include/setjmp.h /usr/include/bits/setjmp.h export.h
tst_insert.o: deref.h table_stats.h struct_manager.h trie_internals.h tries.h
tst_insert.o: tst_aux.h debugs/debug_tables.h dynamic_stack.h
tst_retrv.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
tst_retrv.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
tst_retrv.o: /usr/include/stdio.h /usr/include/features.h
tst_retrv.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
tst_retrv.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
tst_retrv.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
tst_retrv.o: /usr/include/libio.h /usr/include/_G_config.h
tst_retrv.o: /usr/include/wchar.h /usr/include/bits/wchar.h
tst_retrv.o: /usr/include/gconv.h /usr/include/bits/stdio_lim.h
tst_retrv.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
tst_retrv.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
tst_retrv.o: /usr/include/endian.h /usr/include/bits/endian.h
tst_retrv.o: /usr/include/xlocale.h /usr/include/sys/types.h
tst_retrv.o: /usr/include/time.h /usr/include/sys/select.h
tst_retrv.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
tst_retrv.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
tst_retrv.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h auxlry.h
tst_retrv.o: basicdefs.h basictypes.h cell_xsb.h celltags_xsb.h
tst_retrv.o: cell_def_xsb.h inst_xsb.h register.h psc_xsb.h psc_defs.h
tst_retrv.o: memory_xsb.h error_xsb.h setjmp_xsb.h /usr/include/setjmp.h
tst_retrv.o: /usr/include/bits/setjmp.h export.h deref.h binding.h cut_xsb.h
tst_retrv.o: sw_envs.h subp.h table_stats.h struct_manager.h trie_internals.h
tst_retrv.o: tries.h macro_xsb.h debug_xsb.h table_status_defs.h slgdelay.h
tst_retrv.o: debugs/debug_delay.h tst_aux.h debugs/debug_tables.h
tst_retrv.o: debugs/debug_tries.h dynamic_stack.h tst_utils.h flags_xsb.h
tst_retrv.o: flag_defs_xsb.h
tst_unify.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
tst_unify.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
tst_unify.o: /usr/include/stdio.h /usr/include/features.h
tst_unify.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
tst_unify.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
tst_unify.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
tst_unify.o: /usr/include/libio.h /usr/include/_G_config.h
tst_unify.o: /usr/include/wchar.h /usr/include/bits/wchar.h
tst_unify.o: /usr/include/gconv.h /usr/include/bits/stdio_lim.h
tst_unify.o: /usr/include/bits/sys_errlist.h auxlry.h basicdefs.h
tst_unify.o: basictypes.h cell_xsb.h celltags_xsb.h cell_def_xsb.h register.h
tst_unify.o: psc_xsb.h psc_defs.h memory_xsb.h binding.h deref.h subp.h
tst_unify.o: table_stats.h struct_manager.h trie_internals.h inst_xsb.h
tst_unify.o: tries.h macro_xsb.h debug_xsb.h table_status_defs.h slgdelay.h
tst_unify.o: debugs/debug_delay.h choice.h tst_aux.h debugs/debug_tables.h
tst_unify.o: debugs/debug_tries.h dynamic_stack.h tst_utils.h error_xsb.h
tst_unify.o: setjmp_xsb.h /usr/include/setjmp.h /usr/include/bits/setjmp.h
tst_unify.o: /usr/include/bits/sigset.h export.h
tst_utils.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
tst_utils.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_debug.h
tst_utils.o: /usr/include/stdio.h /usr/include/features.h
tst_utils.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
tst_utils.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
tst_utils.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
tst_utils.o: /usr/include/libio.h /usr/include/_G_config.h
tst_utils.o: /usr/include/wchar.h /usr/include/bits/wchar.h
tst_utils.o: /usr/include/gconv.h /usr/include/bits/stdio_lim.h
tst_utils.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
tst_utils.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
tst_utils.o: /usr/include/endian.h /usr/include/bits/endian.h
tst_utils.o: /usr/include/xlocale.h /usr/include/sys/types.h
tst_utils.o: /usr/include/time.h /usr/include/sys/select.h
tst_utils.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
tst_utils.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
tst_utils.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h auxlry.h
tst_utils.o: basicdefs.h basictypes.h cell_xsb.h celltags_xsb.h
tst_utils.o: cell_def_xsb.h binding.h psc_xsb.h psc_defs.h register.h deref.h
tst_utils.o: trie_internals.h inst_xsb.h struct_manager.h tries.h tst_aux.h
tst_utils.o: debugs/debug_tables.h debugs/debug_tries.h dynamic_stack.h
tst_utils.o: macro_xsb.h debug_xsb.h table_status_defs.h slgdelay.h
tst_utils.o: debugs/debug_delay.h choice.h error_xsb.h setjmp_xsb.h
tst_utils.o: /usr/include/setjmp.h /usr/include/bits/setjmp.h export.h
varstring.o: /home/eden/dev/navajoverb/XSB/config/i686-pc-linux-gnu/xsb_config.h
varstring.o: /usr/include/stdio.h /usr/include/features.h
varstring.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
varstring.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
varstring.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
varstring.o: /usr/include/libio.h /usr/include/_G_config.h
varstring.o: /usr/include/wchar.h /usr/include/bits/wchar.h
varstring.o: /usr/include/gconv.h /usr/include/bits/stdio_lim.h
varstring.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
varstring.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
varstring.o: /usr/include/endian.h /usr/include/bits/endian.h
varstring.o: /usr/include/xlocale.h /usr/include/sys/types.h
varstring.o: /usr/include/time.h /usr/include/sys/select.h
varstring.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
varstring.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
varstring.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
varstring.o: /usr/include/errno.h /usr/include/bits/errno.h
varstring.o: /usr/include/linux/errno.h /usr/include/asm/errno.h
varstring.o: /usr/include/asm-i386/errno.h /usr/include/asm-generic/errno.h
varstring.o: /usr/include/asm-generic/errno-base.h /usr/include/string.h
varstring.o: wind2unix.h auxlry.h basicdefs.h basictypes.h cell_xsb.h
varstring.o: celltags_xsb.h cell_def_xsb.h error_xsb.h setjmp_xsb.h
varstring.o: /usr/include/setjmp.h /usr/include/bits/setjmp.h export.h
varstring.o: varstring_xsb.h
