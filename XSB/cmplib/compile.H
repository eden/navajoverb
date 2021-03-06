/* File:      compile.H
** Author(s): Saumya Debray, Jiyang Xu, Terrance Swift, David S. Warren,
**            Kostis Sagonas
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
** $Id: compile.H,v 1.11 2002/06/03 16:27:13 dwarren Exp $
** 
*/


:- export compile/4, mc/2, abort_if_syntax_errors/1. 
:- export 'table #'/0, 'error occurred'/0, current_compiled_module/1.

:- import spec/2 from spec.
:- import cp_opt/2 from cp_opt.
:- import str_cat/3, stat_flag/2 from machine.
:- import useinfer/3 from useinfer.
:- import db_optimize/4 from db_opt.
%%:- import build_graph/1 from cutcheck.
:- import print_result/1 from printres.
:- import standard_symbol/3 from std_xsb.
:- import 'syntax errors'/0 from xsb_read.
:- import perform_auto_table/1 from tabdef.
:- import parse/4, get_symtab/2 from parse.
:- import force_inprog_loaded/0 from inprog.
:- import force_tp_var_loaded/0 from tp_var.
:- import force_flatten_loaded/0 from flatten.
:- import force_tp_eval_loaded/0 from tp_eval.
:- import force_tp_comp_loaded/0 from tp_comp.
:- import force_tp_cond_loaded/0 from tp_cond.
:- import force_tp_goal_loaded/0 from tp_goal.
:- import asm_genheader/4, asm_PIL/4 from asm.
:- import force_varproc_loaded/0 from varproc.
:- import force_asm_opt_loaded/0 from asm_opt.
:- import force_asm_inst_loaded/0 from asm_inst.
:- import force_listutil_loaded/0 from listutil.
:- import supplementary_tabling/2 from suppltab.
:- import force_asm_pass2_loaded/0 from asmpass2.
:- import dump_module/2, write_preds/1 from sanity.
:- import force_tp_geninline_loaded/0 from tpinline.
:- import sym_name/3, sym_type/2, sym_prop/2 from symtab.
:- import dispose_symtab/1 from symtab.
:- import force_tprog_loaded/0, compile_clause/5 from tprog.
:- import force_tp_index_loaded/0, makeindex/6 from tp_index.
:- import force_preprocess_loaded/0, preprocess/3 from preproc.
:- import write_asmheader/4, write_asm_instructions/1 from writeasm.
:- import abort/0, tell/1, telling/1, told/0, cputime/1 from standard.
:- import force_peephole_loaded/0, compile_peephole_opt/2 from peephole.
:- import message/1, warning/1, error/1, time_message/2,
	  setoptions/1, option/1
     from auxlry.
:- import prepare/0, gennum/1, conget/2, conset/2 from gensym.
:- import sys_unlink/2 from shell.
:- import member/2 from basics.
:- import force_ti_mod_loaded/0, ti_pred_block/3 from ti_mod.

:- import modeanalyze/3 from modeinf.
:- import assert/1, retractall/1, (dynamic)/1  from assert.
