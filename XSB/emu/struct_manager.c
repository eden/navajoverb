/* File:      struct_manager.c
** Author(s): Ernie Johnson
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
** $Id: struct_manager.c,v 1.13 2002/05/22 15:41:16 lfcastro Exp $
** 
*/


#include "xsb_config.h"
#include "xsb_debug.h"

#include <stdio.h>
#include <stdlib.h>

#include "auxlry.h"
#include "struct_manager.h"
#include "cell_xsb.h"
#include "error_xsb.h"
#include "debug_xsb.h"
#include "flags_xsb.h"

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

void smPrint(Structure_Manager smRecord, char *string) {

  void *pBlock;
  counter nBlocks;

  nBlocks = 0;
  for ( pBlock = SM_CurBlock(smRecord);  IsNonNULL(pBlock);
	pBlock = SMBlk_NextBlock(pBlock) )
    nBlocks++;

  fprintf(stddbg,
	  "  Structure Manager for %s (%s)\n"
	  "\tCurBlock: %p\t\tTotal Blocks: %u\n"
	  "\tNextStr:  %p\t\tFree List:   %p\n"
	  "\tLastStr:  %p\t\tAlloc List:  %p\n"
	  "\tStructs per block: %u\t\tStruct size: %u bytes\n",
	  SM_StructName(smRecord),	string,
	  SM_CurBlock(smRecord),	nBlocks,
	  SM_NextStruct(smRecord),	SM_FreeList(smRecord),
	  SM_LastStruct(smRecord),	SM_AllocList(smRecord),
	  SM_StructsPerBlock(smRecord),	SM_StructSize(smRecord));
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/*
 *  Allocate a new block from the system and place it at the head of
 *  the block list in the Structure Manager.
 */

void smAllocateBlock(Structure_Manager *pSM) {

  void *pNewBlock;

  dbg_smPrint(LOG_STRUCT_MANAGER, *pSM,"before block allocation");
  pNewBlock = malloc(SM_NewBlockSize(*pSM));
  if ( IsNULL(pNewBlock) )
    xsb_abort("[smAllocateBlock] Out of memory in allocation of %s block\n",
	      SM_StructName(*pSM));
  SMBlk_NextBlock(pNewBlock) = SM_CurBlock(*pSM);
  SM_CurBlock(*pSM) = pNewBlock;
  SM_NextStruct(*pSM) = SMBlk_FirstStruct(pNewBlock);
  SM_LastStruct(*pSM) = SMBlk_LastStruct(pNewBlock,
					 SM_StructSize(*pSM),
					 SM_StructsPerBlock(*pSM));
  dbg_smPrint(LOG_STRUCT_MANAGER, *pSM,"after block allocation");
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/*
 *  Return all blocks held by the Structure Manager to the system.
 */

void smFreeBlocks(Structure_Manager *pSM) {

  void *pCurBlock, *pNextBlock;

  pCurBlock = SM_CurBlock(*pSM);
  while ( IsNonNULL(pCurBlock) ) {
    pNextBlock = SMBlk_NextBlock(pCurBlock);
    free(pCurBlock);
    pCurBlock = pNextBlock;
  }
  SM_CurBlock(*pSM) = SM_NextStruct(*pSM) = SM_LastStruct(*pSM) = NULL;
  SM_AllocList(*pSM) = SM_FreeList(*pSM) = NULL;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/*
 *  Determine whether a given pointer is indeed a reference to a
 *  structure maintained by the given Structure Manager.
 */

xsbBool smIsValidStructRef(Structure_Manager smRecord, void *ptr) {

  void *pBlock, *firstStruct, *lastStruct;
  size_t structSize;


  structSize = SM_StructSize(smRecord);

  for ( pBlock = SM_CurBlock(smRecord);  IsNonNULL(pBlock);
	pBlock = SMBlk_NextBlock(pBlock) ) {
    
    firstStruct = SMBlk_FirstStruct(pBlock);
    lastStruct =
      SMBlk_LastStruct(pBlock,structSize,SM_StructsPerBlock(smRecord));

    /* Determine whether pointer lies within block
       ------------------------------------------- */
    if ( (firstStruct <= ptr) && (ptr <= lastStruct) ) {

      /* Determine whether pointer is a valid reference
	 ---------------------------------------------- */
      if ( (((char *)ptr - (char *)firstStruct) MOD structSize) == 0 )
	return TRUE;
      else
	return FALSE;
    }
  }
  return FALSE;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/*
 *  Determine whether the given structure maintained by the given
 *  Structure Manager is allocated.
 */

xsbBool smIsAllocatedStruct(Structure_Manager smRecord, void *pStruct) {

  void *freeStruct;

  /* Determine whether struct lies w/i unallocated section of 1st block
     ------------------------------------------------------------------ */
  if ( (SM_NextStruct(smRecord) <= pStruct) &&
       (pStruct <= SM_LastStruct(smRecord)) )
    return FALSE;

  /* Determine whether struct is on the free list
     -------------------------------------------- */
  for ( freeStruct = SM_FreeList(smRecord);  IsNonNULL(freeStruct);
	freeStruct = SMFL_NextFreeStruct(freeStruct) )
    if ( freeStruct == pStruct )
      return FALSE;

  return TRUE;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/*
 *  Determine whether a given pointer is a reference to an allocated
 *  structure maintained by the given Structure Manager.
 */

xsbBool smIsAllocatedStructRef(Structure_Manager smRecord, void *ptr) {

  return ( smIsValidStructRef(smRecord,ptr) &&
	   smIsAllocatedStruct(smRecord,ptr) );
}
