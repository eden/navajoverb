/*  -*-c-*-  Make sure this file comes up in the C mode of emacs */ 
/* File:      desc_sli.i
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
** $Id: desc_sli_xsb_i.h,v 1.2 2000/10/03 15:47:37 ejohnson Exp $
** 
*/

/*
 * DESCRIBE the SQL Statement's Select List Items
 * ----------------------------------------------
 *  Initilizes the select list descriptor after examining the select list
 *  items in the PREPAREd dynamic SQL statement to determine each item's
 *  name, datatype, constraints, length, scale, and precision.
 */

  switch (cursorHandle) {
  case 0:
    EXEC SQL DESCRIBE SELECT LIST FOR S0 INTO DESCRIPTOR descriptor;
    break;
  case 1:
    EXEC SQL DESCRIBE SELECT LIST FOR S1 INTO DESCRIPTOR descriptor;
    break;
  case 2:
    EXEC SQL DESCRIBE SELECT LIST FOR S2 INTO DESCRIPTOR descriptor;
    break;
  case 3:
    EXEC SQL DESCRIBE SELECT LIST FOR S3 INTO DESCRIPTOR descriptor;
    break;
  case 4:
    EXEC SQL DESCRIBE SELECT LIST FOR S4 INTO DESCRIPTOR descriptor;
    break;
  case 5:
    EXEC SQL DESCRIBE SELECT LIST FOR S5 INTO DESCRIPTOR descriptor;
    break;
  case 6:
    EXEC SQL DESCRIBE SELECT LIST FOR S6 INTO DESCRIPTOR descriptor;
    break;
  case 7:
    EXEC SQL DESCRIBE SELECT LIST FOR S7 INTO DESCRIPTOR descriptor;
    break;
  case 8:
    EXEC SQL DESCRIBE SELECT LIST FOR S8 INTO DESCRIPTOR descriptor;
    break;
  case 9:
    EXEC SQL DESCRIBE SELECT LIST FOR S9 INTO DESCRIPTOR descriptor;
    break;
  case 10:
    EXEC SQL DESCRIBE SELECT LIST FOR S10 INTO DESCRIPTOR descriptor;
    break;
  case 11:
    EXEC SQL DESCRIBE SELECT LIST FOR S11 INTO DESCRIPTOR descriptor;
    break;
  case 12:
    EXEC SQL DESCRIBE SELECT LIST FOR S12 INTO DESCRIPTOR descriptor;
    break;
  case 13:
    EXEC SQL DESCRIBE SELECT LIST FOR S13 INTO DESCRIPTOR descriptor;
    break;
  case 14:
    EXEC SQL DESCRIBE SELECT LIST FOR S14 INTO DESCRIPTOR descriptor;
    break;
  case 15:
    EXEC SQL DESCRIBE SELECT LIST FOR S15 INTO DESCRIPTOR descriptor;
    break;
  case 16:
    EXEC SQL DESCRIBE SELECT LIST FOR S16 INTO DESCRIPTOR descriptor;
    break;
  case 17:
    EXEC SQL DESCRIBE SELECT LIST FOR S17 INTO DESCRIPTOR descriptor;
    break;
  case 18:
    EXEC SQL DESCRIBE SELECT LIST FOR S18 INTO DESCRIPTOR descriptor;
    break;
  case 19:
    EXEC SQL DESCRIBE SELECT LIST FOR S19 INTO DESCRIPTOR descriptor;
    break;
  case 20:
    EXEC SQL DESCRIBE SELECT LIST FOR S20 INTO DESCRIPTOR descriptor;
    break;
  }
