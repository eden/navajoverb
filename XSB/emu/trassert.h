/* File:      trassert.h
** Author(s): Prasad Rao
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
** $Id: trassert.h,v 1.4 1999/07/15 21:41:22 ejohnson Exp $
** 
*/


extern int trie_assert(void);
extern int trie_retract(void);
extern int trie_retract_safe(void);


#define switch_to_trie_assert {		\
   smBTN = &smAssertBTN;		\
   smBTHT = &smAssertBTHT;		\
}

#define switch_from_trie_assert {	\
   smBTN = &smTableBTN;			\
   smBTHT = &smTableBTHT;		\
}
