/* File:      xcallxsb.H
** Author(s): Ernie Johnson
** Contact:   xsb-contact@cs.sunysb.edu
** 
** Copyright (C) The Research Foundation of SUNY, 1997-1998
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
** $Id: xcallxsb.H,v 1.9 2002/08/27 20:06:57 tswift Exp $
** 
*/



:- import
       integer/1, close_open_tables/0
   from machine.

:- import file_open/3, file_close/1
     from file_io.

:- import call_c/1, call_expose/1, catch/3,
 	  goal_cut_trans/3, repeat/0, (=..)/2  from standard.
:- import set_inthandler/2 from loader.
:- import file_write/2, file_nl/1 from xsb_writ.
:- import file_read_foe/3, file_read/3 from xsb_read.
:- import excess_vars/4 from setof.
:- import conset/2 from gensym.
:- import [] / 0 from usermod.	       % just to make usermod typed "module"
