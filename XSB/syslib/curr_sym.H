/* File:      curr_sym.H
** Author(s): Kostis Sagonas
** Contact:   xsb-contact@cs.sunysb.edu
** 
** Copyright (C) The Research Foundation of SUNY, 1986, 1993-1998
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
** $Id: curr_sym.H,v 1.13 2002/07/15 12:28:43 dwarren Exp $
** 
*/


:- export current_op/3, 
	current_input/1, current_output/1,
	current_input_port/1, current_output_port/1,
	current_module/1, current_module/2,
	current_atom/1, current_atom/2, 
	current_functor/1, current_functor/2, 
	current_predicate/1, current_predicate/2,
	predicate_property/2, module_property/2, 
	xsb_flag/2, garbage_collection/1, hilog_symbol/1.

:- import '_$op'/3 from file_op.
:- import '_$hilog_symbol'/1 from hilogsym.
:- import libpath/1 from loader.
:- import functor/3, warning/1, abort/1, number/1 from standard.
:- import standard_symbol/3 from std_xsb.
:- import psc_name/2, psc_arity/2, psc_prop/2, psc_type/2, term_psc/2,
	  term_type/2, stat_flag/2, stat_set_flag/2, machine_file_exists/1, 
	  psc_env/2, psc_spy/2, psc_tabled/2, dereference_the_bucket/2,
	  pair_psc/2, pair_next/2, next_bucket/2, conpsc/2,
	  str_cat/3, intern_string/2, slash/1
     from machine.
:- import xsb_configuration/2 from xsb_configuration.
:- import fmt_write_string/3 from file_io.


/* ----------------- end of file current_sym.H -------------------- */
