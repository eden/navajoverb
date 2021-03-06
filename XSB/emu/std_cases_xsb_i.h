/* File:      std_cases_xsb_i.h
** Author(s): Kostis F. Sagonas
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
** $Id: std_cases_xsb_i.h,v 1.6 2002/10/07 15:20:45 dwarren Exp $
** 
*/


  case IS_ATTV:	/* r1: ?term */
    return isattv(ptoc_tag(1));

  case VAR:		/* r1: ?term */
    return isref(ptoc_tag(1));
    
  case NONVAR:	/* r1: ?term */
    return isnonvar(ptoc_tag(1));
    
  case ATOM:		/* r1: ?term */
    return isatom(ptoc_tag(1));
    
  case INTEGER:	/* r1: ?term */ {
      int tag = ptoc_tag(1);
      return (isinteger(tag) || isboxedinteger(tag));
  }
    
  case REAL:		/* r1: ?term */
    return isfloat(ptoc_tag(1));
    
  case NUMBER:	/* r1: ?term */ {
      int tag = ptoc_tag(1);
      return (isnumber(tag) || isboxedinteger(tag));
  }
  case ATOMIC: {	/* r1: ?term */
    Cell term = ptoc_tag(1);
    return (isatomic(term) || isboxedinteger(term));
  }

  case COMPOUND: {	/* r1: ?term */
    Cell term = ptoc_tag(1);
    return (((isconstr(term) && get_arity(get_str_psc(term))) ||
	    (islist(term))) && !isboxedinteger(term));
  }

  case CALLABLE: {	/* r1: ?term */
    Cell term = ptoc_tag(1);
    return (isconstr(term) || isstring(term) || islist(term));
  }

  case IS_LIST:	/* r1: ?term */
    return is_proper_list(ptoc_tag(1));
    
  case IS_MOST_GENERAL_TERM: /* r1: ?term */
    return is_most_general_term(ptoc_tag(1)); 

  case FUNCTOR:	/* r1: ?term; r2: ?functor; r3: ?arity (int)	*/
    return functor_builtin();
    
  case ARG:	/* r1: +index (int); r2: +term; r3: ?arg (term) */
    return arg_builtin();
    
  case UNIV:	/* r1: ?term; r2: ?list	*/
    return univ_builtin();
    
  case HiLog_ARG:	/* r1: +index (int); r2: +term; r3: ?arg (term) */
    return hilog_arg();

  case HiLog_UNIV:	/* r1: ?term; r2: ?list	*/
    break;
    
  /* atom_chars should be redefined to return char-atoms rather than ASCII
     codes */ 
  case ATOM_CHARS:	/* r1: ?term; r2: ?character symbol list	*/
    return atom_to_list(ATOM_CHARS);
  case ATOM_CODES:	/* r1: ?term; r2: ?character ascii code list	*/
    return atom_to_list(ATOM_CODES);
    
  /* number_chars should be redefined to return digit-atoms */
  case NUMBER_CHARS:	/* r1: ?term; r2: ?character symbol list	*/
    return number_to_list(NUMBER_CHARS);
  case NUMBER_CODES:	/* r1: ?term; r2: ?character code list	*/
    return number_to_list(NUMBER_CODES);
  case NUMBER_DIGITS:	/* r1: ?term; r2: ?digit list	*/
    return number_to_list(NUMBER_DIGITS);
    
    
  case PUT: {	/* r1: +integer	*/
    Cell term = ptoc_tag(1);
    if (isinteger(term)) {
      putc(int_val(term), fileptr(flags[CURRENT_OUTPUT]));
    } else {
      if (isnonvar(term)) err_handle(TYPE, 1, "put", 1, "integer", term);
      else err(INSTANTIATION, 1, "put", 1);
    }
    break;
  }
  case TAB: {	/* r1: +integer	*/
    Cell term = ptoc_tag(1);
    if (isinteger(term)) {
      int  i;
      for (i=1; i<=int_val(term); i++)
	putc(' ', fileptr(flags[CURRENT_OUTPUT]));
    } else {
      if (isnonvar(term)) err_handle(TYPE, 1, "tab", 1, "integer", term);
      else err(INSTANTIATION, 1, "tab", 1);
    }
    break;
  }

  case SORT:		/* r1: +list of terms; r2: ?sorted list of terms */
  return sort();
    
  case KEYSORT:	/* r1: +list of terms of the form Key-Value;	*/
    /* r2: ?sorted list of terms			*/
   return keysort();
