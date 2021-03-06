/* File:      flrundefined.H
**
** Author(s): Chang Zhao
**
** Contact:   flora-users@lists.sourceforge.net
**
** Copyright (C) The Research Foundation of SUNY, 2002
**
** FLORA-2 is free software; you can redistribute it and/or modify it under the
** terms of the GNU Library General Public License as published by the Free
** Software Foundation; either version 2 of the License, or (at your option)
** any later version.
**
** FLORA-2 is distributed in the hope that it will be useful, but WITHOUT ANY
** WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
** FOR A PARTICULAR PURPOSE.  See the GNU Library General Public License for
** more details.
** 
** You should have received a copy of the GNU Library General Public License
** along with FLORA-2; if not, write to the Free Software Foundation,
** Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
**
** $Id: flrundefined.H,v 1.12 2003/06/18 07:01:36 kifer Exp $
**
*/


:- compiler_options([xpp_on]).

#include "flora_porting.flh"

:- dynamic term_seen(_).

:- import length/2 from basics.

:- import close_open_tables/0 from machine.

:- import subsumes/2 from subsumes.

:- import
	flora_db_find_base/2,
	flora_db_insert_base/2
   from flrstoragebase.

:- import
	flora_write_atom/1,
	flora_write_quoted_atom/1,
	flora_concat_atoms/2,
	flora_concat_items/2
   from flrporting.

:- import flora_disabled_undefinedness_check_registry/3 from flrregistry.

:- import flora_prlgdef/2 from flrprolog.

:- import
	is_prrule/3,
	is_prfact/2,
	is_pratom/3,
	is_prvariable/3,
	is_prterm/4,
	is_pratomlit/3,
	is_prtermlit/4
   from flrcoder.

:- import flora_decode_predicate/6 from flrwrapper.

:- export
	flora_debug_code/2,
	flora_temp_protect_call/2,
	flora_temp_unprotect_call/1,
	flora_define_predicate/1,
	flora_error_undefined/1.
