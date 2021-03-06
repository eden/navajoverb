/* File:      asmpass2.H
** Author(s): Saumya Debray, Kostis Sagonas
** Contact:   xsb-contact@cs.sunysb.edu
** 
** Copyright (C) The Research Foundation of SUNY, 1986, 1993-1998
** Copyright (C) ECRC, Germany, 1990
** 
** XSB is free software; you can redistribute it and/or modify it under the
** terms of the GNU Library General Public License as published by the Free
** Software Foundation; either version 2 of the License, or (at your option)
** any later version.
** 
** XSB is distributed in the hope that it will be useful, but WITHOUT ANY
** WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
** FOR A PARTICULAR PURPOSE.  See the GNU Library General Public License for
** more details.
** 
** You should have received a copy of the GNU Library General Public License
** along with XSB; if not, write to the Free Software Foundation,
** Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
**
** $Id: asmpass2.H,v 1.5 2002/04/13 05:01:48 lfcastro Exp $
** 
*/


:- export force_asm_pass2_loaded/0.
:- export asm_gendata/1, asm_gentext/2, asm_genindex/2, asm_putlength/1.

:- import error/1, ll_arg/3 from auxlry.
:- import asm_inst/4 from asm_inst.
:- import membercheck/2 from listutil.
:- import term_hash/3, str_len/2 from machine.
:- import write/1, put/1, integer/1 from standard.
:- import write_int/1, write_float/1 from xsb_writ.
:- import member/2 from basics.
:- import sym_offset/2, sym_env/2, sym_category/2, sym_name/3 from symtab.

