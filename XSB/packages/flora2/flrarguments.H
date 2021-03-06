/* File:      flrarguments.H
**
** Author(s): Guizhen Yang
**
** Contact:   flora-users@lists.sourceforge.net
**
** Copyright (C) The Research Foundation of SUNY, 1999-2001
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
** $Id: flrarguments.H,v 1.5 2003/06/18 07:01:37 kifer Exp $
**
*/


:- dynamic flora_dynarg(_,_,_).

:- dynamic flora_sharg(_,_,_).

:- index(flora_dynarg/3,trie).

:- index(flora_sharg/3,trie).

:- index flora_arguments_spec/3-1.

:- import assert/1, retractall/1 from assert.

:- import conget/2 from gensym.

:- export
	flora_argdef/3,
	flora_conflict_arguments/3,
	flora_reset_arguments/0,
	flora_define_arguments/3,
	flora_shreset_arguments/0,
	flora_shdefine_arguments/3.
