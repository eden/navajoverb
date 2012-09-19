/* File:      hashtable_xsb.h  -- a simple generic hash table ADT
** Author(s): Michael Kifer
** Contact:   xsb-contact@cs.sunysb.edu
** 
** Copyright (C) The Research Foundation of SUNY, 2002
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
** $Id: hashtable_xsb.h,v 1.2 2002/04/02 06:31:10 kifer Exp $
** 
*/


/* clients can define their own bucket structures as long as the top of that
   structure coinsides with xsbBucket */
typedef struct bucket xsbBucket;
struct bucket {
  Cell        name;
  xsbBucket  *next;
};

typedef struct hash_table  xsbHashTable;
struct hash_table {
  int           length;
  int           bucket_size;  
  xsbBool       initted;
  byte         *table;
};

enum  xsbHashSearchOp {hashtable_insert, hashtable_delete, hashtable_find};


extern xsbBucket *search_bucket(Cell name, xsbHashTable *tbl,
				enum xsbHashSearchOp search_op);

extern void destroy_hash_table(xsbHashTable *table);

extern void show_table_state(xsbHashTable *table);
