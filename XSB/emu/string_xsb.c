/* File:      string_xsb.c  -- string manipulation stuff
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
** $Id: string_xsb.c,v 1.15 2002/08/07 15:42:13 lfcastro Exp $
** 
*/

#include "xsb_config.h"
#include "xsb_debug.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "auxlry.h"
#include "cell_xsb.h"
#include "error_xsb.h"
#include "psc_xsb.h"
#include "hash_xsb.h"
#include "tries.h"
#include "choice.h"
#include "deref.h"
#include "memory_xsb.h"
#include "heap_xsb.h"
#include "register.h"
#include "flags_xsb.h"
#include "binding.h"
#include "builtin.h"
#include "cinterf.h"

#include "sp_unify_xsb_i.h"
#include "string_xsb.h"

extern char *p_charlist_to_c_string(prolog_term term, VarString *outstring, 
				    char *in_func, char *where);
extern void c_string_to_p_charlist(char *name, prolog_term list,
				   char *in_func, char *where);

static Cell term, term2, term3;

static XSB_StrDefine(input_buffer);
static XSB_StrDefine(subst_buf);
static XSB_StrDefine(output_buffer);


#include "ptoc_tag_xsb_i.h"


xsbBool str_cat(void)
{
  static char *str1, *str2, *tmpstr;

  term = ptoc_tag(1);
  term2 = ptoc_tag(2);
  if (isatom(term) && isatom(term2)) {
    str1 = string_val(term);
    str2 = string_val(term2);
    
    tmpstr = (char *)malloc(strlen(str1) + strlen(str2) + 1);
    strcpy(tmpstr, str1);
    strcat(tmpstr, str2);
    str1 = string_find(tmpstr, 1);
    free(tmpstr);
    return atom_unify(makestring(str1), ptoc_tag(3));
  } else return FALSE;
}


/*
  Input:
      Arg1: +Substr
      Arg2: + String
      Arg3: +forward/reverse (checks only f/r)
        f means the first match from the start of String
	r means the first match from the end of String
  Output:
      Arg4: Beg
        Beg is the offset where Substr matches. Must be a variable or an
	integer
      Arg5: End
	End is the offset of the next character after the end of Substr
	Must be a variable or an integer.

      Both Beg and End can be negative, in which case they represent the offset
      from the 2nd character past the end of String.
      For instance, -1 means the next character past the end of String,
      so End = -1 means that Substr must be a suffix of String..

      The meaning of End and of negative offsets is consistent with substring
      and string_substitute predicates.
*/
xsbBool str_match(void)
{
  static char *subptr, *stringptr, *direction, *matchptr;
  static int substr_beg, substr_end;
  int reverse=TRUE; /* search in reverse */
  int beg_bos_offset=TRUE; /* measure beg offset from the beg of string */
  int end_bos_offset=TRUE; /* measure end offset from the beg of string */
  int str_len, sub_len; /* length of string and substring */
  Cell beg_offset_term, end_offset_term;

  term = ptoc_tag(1);
  term2 = ptoc_tag(2);
  term3 = ptoc_tag(3);
  beg_offset_term = ptoc_tag(4);
  end_offset_term = ptoc_tag(5);
  if (!isatom(term) || !isatom(term2) || !isatom(term3)) {
    xsb_abort("STR_MATCH: Arguments 1,2,3 must be bound to strings");
  }
  subptr = string_val(term);
  stringptr = string_val(term2);
  direction = string_val(term3);

  if (*direction == 'f')
    reverse=FALSE;
  else if (*direction != 'r')
    xsb_abort("STR_MATCH: Argument 3 must be bound to forward/reverse");

  str_len=strlen(stringptr);
  sub_len=strlen(subptr);

  if (isinteger(beg_offset_term)|isboxedinteger(beg_offset_term)) {
    if (int_val(beg_offset_term) < 0) {
      beg_bos_offset = FALSE;
    }
  }
  if (isinteger(end_offset_term)|isboxedinteger(end_offset_term)) {
    if (int_val(end_offset_term) < 0) {
      end_bos_offset = FALSE;
    }
  }

  if (reverse)
    matchptr = xsb_strrstr(stringptr, subptr);
  else
    matchptr = strstr(stringptr, subptr);

  if (matchptr == NULL) return FALSE;

  substr_beg = (beg_bos_offset?
		matchptr - stringptr : -(str_len - (matchptr - stringptr))
		);
  substr_end = (end_bos_offset?
		(matchptr - stringptr) + sub_len
		: -(str_len + 1 - (matchptr - stringptr) - sub_len)
		);
  
  return
    (p2p_unify(beg_offset_term, makeint(substr_beg))
     && p2p_unify(end_offset_term, makeint(substr_end)));
}




/* XSB string substitution entry point
   In: 
      Arg1: string
      Arg2: beginning offset
      Arg3: ending offset. `_' or -1: end of string, -2: char before last, etc.
   Out:
      Arg4: new (output) string
   Always succeeds, unless error.
*/
xsbBool substring(void)
{
  /* Prolog args are first assigned to these, so we could examine the types
     of these objects to determine if we got strings or atoms. */
  prolog_term input_term, output_term;
  prolog_term beg_offset_term, end_offset_term;
  char *input_string=NULL;    /* string where matches are to be found */
  int beg_offset=0, end_offset=0, input_len=0, substring_len=0;
  int conversion_required=FALSE;

  XSB_StrSet(&output_buffer,"");

  input_term = reg_term(1);  /* Arg1: string to find matches in */
  if (isatom(input_term)) /* check it */
    input_string = string_val(input_term);
  else if (islist(input_term)) {
    input_string = p_charlist_to_c_string(input_term, &input_buffer,
					  "SUBSTRING", "input string");
    conversion_required = TRUE;
  } else
    xsb_abort("[SUBSTRING] Arg 1 (the input string) must be an atom or a character list");

  input_len = strlen(input_string);

  /* arg 2: beginning offset */
  beg_offset_term = reg_term(2);
  if (! (isinteger(beg_offset_term)|isboxedinteger(beg_offset_term)))
    xsb_abort("[SUBSTRING] Arg 2 (the beginning offset) must be an integer");
  beg_offset = int_val(beg_offset_term);
  if (beg_offset < 0)
    beg_offset = 0;
  else if (beg_offset > input_len)
    beg_offset = input_len;

  /* arg 3: ending offset */
  end_offset_term = reg_term(3);
  if (isref(end_offset_term))
    end_offset = input_len;
  else if (! (isinteger(end_offset_term)|isboxedinteger(end_offset_term)))
    xsb_abort("[SUBSTRING] Arg 3 (the end offset) must be integer or _");
  else end_offset = int_val(end_offset_term);

  if (end_offset < 0)
    end_offset = input_len + 1 + end_offset;
  else if (end_offset > input_len)
    end_offset = input_len;
  else if (end_offset < beg_offset)
    end_offset = beg_offset;

  output_term = reg_term(4);
  if (! isref(output_term))
    xsb_abort("[SUBSTRING] Arg 4 (the output string) must be an unbound variable");

  /* do the actual replacement */
  substring_len = end_offset-beg_offset;
  XSB_StrAppendBlk(&output_buffer, input_string+beg_offset, substring_len);
  XSB_StrNullTerminate(&output_buffer);
  
  /* get result out */
  if (conversion_required)
    c_string_to_p_charlist(output_buffer.string, output_term,
			   "SUBSTRING", "Arg 4");
  else
    c2p_string(output_buffer.string, output_term);
  
  return(TRUE);
}


/* XSB string substitution entry point: replace substrings specified in Arg2
   with strings in Arg3.
   In: 
       Arg1: string
       Arg2: substring specification, a list [s(B1,E1),s(B2,E2),...]
       Arg3: list of replacement strings
   Out:
       Arg4: new (output) string
   Always succeeds, unless error.
*/
xsbBool string_substitute(void)
{
  /* Prolog args are first assigned to these, so we could examine the types
     of these objects to determine if we got strings or atoms. */
  prolog_term input_term, output_term;
  prolog_term subst_reg_term, subst_spec_list_term, subst_spec_list_term1;
  prolog_term subst_str_term=(prolog_term)0,
    subst_str_list_term, subst_str_list_term1;
  char *input_string=NULL;    /* string where matches are to be found */
  char *subst_string=NULL;
  prolog_term beg_term, end_term;
  int beg_offset=0, end_offset=0, input_len;
  int last_pos = 0; /* last scanned pos in input string */
  /* the output buffer is made large enough to include the input string and the
     substitution string. */
  int conversion_required=FALSE; /* from C string to Prolog char list */

  XSB_StrSet(&output_buffer,"");

  input_term = reg_term(1);  /* Arg1: string to find matches in */
  if (isatom(input_term)) /* check it */
    input_string = string_val(input_term);
  else if (islist(input_term)) {
    input_string = p_charlist_to_c_string(input_term, &input_buffer,
					  "STRING_SUBSTITUTE", "input string");
    conversion_required = TRUE;
  } else
    xsb_abort("[STRING_SUBSTITUTE] Arg 1 (the input string) must be an atom or a character list");

  input_len = strlen(input_string);

  /* arg 2: substring specification */
  subst_spec_list_term = reg_term(2);
  if (!islist(subst_spec_list_term) && !isnil(subst_spec_list_term))
    xsb_abort("[STRING_SUBSTITUTE] Arg 2 must be a list [s(B1,E1),s(B2,E2),...]");

  /* handle substitution string */
  subst_str_list_term = reg_term(3);
  if (! islist(subst_str_list_term))
    xsb_abort("[STRING_SUBSTITUTE] Arg 3 must be a list of strings");

  output_term = reg_term(4);
  if (! isref(output_term))
    xsb_abort("[STRING_SUBSTITUTE] Arg 4 (the output) must be an unbound variable");

  subst_spec_list_term1 = subst_spec_list_term;
  subst_str_list_term1 = subst_str_list_term;

  if (isnil(subst_spec_list_term1)) {
    XSB_StrSet(&output_buffer, input_string);
    goto EXIT;
  }
  if (isnil(subst_str_list_term1))
    xsb_abort("[STRING_SUBSTITUTE] Arg 3 must not be an empty list");

  do {
    subst_reg_term = p2p_car(subst_spec_list_term1);
    subst_spec_list_term1 = p2p_cdr(subst_spec_list_term1);

    if (!isnil(subst_str_list_term1)) {
      subst_str_term = p2p_car(subst_str_list_term1);
      subst_str_list_term1 = p2p_cdr(subst_str_list_term1);

      if (isatom(subst_str_term)) {
	subst_string = string_val(subst_str_term);
      } else if (islist(subst_str_term)) {
	subst_string = p_charlist_to_c_string(subst_str_term, &subst_buf,
					      "STRING_SUBSTITUTE",
					      "substitution string");
      } else 
	xsb_abort("[STRING_SUBSTITUTE] Arg 3 must be a list of strings");
    }

    beg_term = p2p_arg(subst_reg_term,1);
    end_term = p2p_arg(subst_reg_term,2);

    if (!(isinteger(beg_term)|isboxedinteger(beg_term)) || 
	!(isinteger(end_term)|isboxedinteger(end_term)))
      xsb_abort("[STRING_SUBSTITUTE] Non-integer in Arg 2");
    else{
      beg_offset = int_val(beg_term);
      end_offset = int_val(end_term);
    }
    /* -1 means end of string */
    if (end_offset < 0)
      end_offset = input_len;
    if ((end_offset < beg_offset) || (beg_offset < last_pos))
      xsb_abort("[STRING_SUBSTITUTE] Substitution regions in Arg 2 not sorted");

    /* do the actual replacement */
    XSB_StrAppendBlk(&output_buffer,input_string+last_pos,beg_offset-last_pos);
    XSB_StrAppend(&output_buffer, subst_string);
    
    last_pos = end_offset;

  } while (!isnil(subst_spec_list_term1));

  XSB_StrAppend(&output_buffer, input_string+end_offset);

 EXIT:
  /* get result out */
  if (conversion_required)
    c_string_to_p_charlist(output_buffer.string, output_term,
			   "STRING_SUBSTITUTE", "Arg 4");
  else
    c2p_string(output_buffer.string, output_term);
  
  return(TRUE);
}


/*
 * strrstr.c -- find last occurence of string in another string
 *
 */

char *xsb_strrstr(char *str, char *pat)
{
  size_t len, patlen;
  const char *p;
  
  len = strlen(str);
  patlen = strlen(pat);
  
  if (patlen > len)
    return NULL;
  for (p = str + (len - patlen); p >= str; --p)
    if (*p == *pat && strncmp(p, pat, patlen) == 0)
      return (char *) p;
  return NULL;
}
