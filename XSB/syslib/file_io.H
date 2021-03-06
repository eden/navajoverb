/* File:      file_io.H
** Author(s): kifer
** Contact:   xsb-contact@cs.sunysb.edu
** 
** Copyright (C) The Research Foundation of SUNY, 1999
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
** $Id: file_io.H,v 1.23 2002/04/13 05:01:59 lfcastro Exp $
** 
*/


:- import stat_flag/2, file_function/7,
	parse_filename/4, is_absolute_filename/1,
	expand_filename/2,
	sys_system/7, formatted_io/5 
      from machine.
:- import conpsc/2, psc_set_type/2, psc_set_prop/2 from machine.

:- import
	abort/1, atom_codes/2, '\='/2, repeat/0,
	file_exists/1
      from standard.

:- import gensym/2 from gensym.

:- import is_plain_file/1, is_directory/1, rename/2, rm/1, cwd/1,
	cd/1, sys_link/3, sys_mkdir/2, sys_rmdir/2, sys_access/3
      from shell.

:- import file_write/2 from xsb_writ.

:- export fmt_write_string/3, fmt_write/2, fmt_read/3,
	  fmt_write/3, fmt_read/4,
	  print_file_contents/1,
	  print_file_contents/2,
	  path_sysop/2, path_sysop/3,
	  copyIOport/2,
	  file_flush/2, file_seek/4, file_truncate/3,
	  file_pos/2, file_size/2, file_time/2,
	  file_open/3, file_close/1, file_get/2, file_put/2,
	  file_getbuf/4,
	  file_getbuf_atom/4, file_getbuf_atom/3,
	  file_getbuf_list/4, file_getbuf_list/3,
	  file_putbuf/5, file_putbuf/4,
	  file_write_line/2, file_write_line/3,
      	  file_read_line/2,
	  file_read_line_atom/1, file_read_line_atom/2,
	  file_read_line_list/1, file_read_line_list/2,
	  file_reopen/4, file_clone/3,
	  pipe_open/2, fd2ioport/2, ioport2iostream/2,
	  file_clearerr/1, tmpfile_open/1,
	  is_valid_ioport/1.
