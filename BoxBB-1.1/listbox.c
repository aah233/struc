/******************************************************************************
			listbox.c  - description
			----------------------
	begin		: June 2004
	copywirght	: (C) 2004 by L.G.Casado.
	
*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "defines.h"
#include "getmem.h"
#include "utils.h" 
#include "iutils.hpp"
#include "Functions.hpp" 
#include "box.hpp"
#include "listbox.h"

using namespace std;

/*---------------------------------------------------------------------------*/
PLBNODE NewLBNODE(PBOX pB)
{
 PLBNODE plsn;

 plsn       = (PLBNODE) GetMem ((SIZE)1, (SIZE)sizeof(LBNODE),"NewLBNODE");
 plsn->pB   = pB;
 plsn->pnext = NULL;
 
 return plsn;
}

/*---------------------------------------------------------------------------*/
/*Free the memory allocated by a one node of the list.                       */
/*---------------------------------------------------------------------------*/
PLBNODE FreeLBNODE (PLBNODE l, ConstData CtD,const BOOL Fill, PCHARCt Color)
{
 if (l==NULL)
    {
     fprintf(stderr,"Trying to free a NULL node in a list of vertexes\n");
     exit(1);
    }
    
 if (l->pB==NULL)
    {
     fprintf(stderr,"FreeLBNODE: The contained box is NULL.\n");
     exit(1);
    }   
 
 //fprintf(stderr,"FreeLBNODE: Nbox=%d.\n",l->pB->NBox);
 
 l->pB=FreeBox(l->pB,CtD,Fill,Color);
 free((PVOID)l);
     
 return NULL;
}


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
PLISTB NewListB(PLISTB pls)
{
 pls=(PLISTB)GetMem(1,sizeof(LISTB),"NewListB");
 pls->pFirstLB = NULL;
 pls->NElem    = 0;
 pls->MaxNElem = 0;
 return pls;
}

/*---------------------------------------------------------------------------*/
PLISTB FreeListB (PLISTB pls, ConstData CtD, const BOOL Fill, PCHARCt Color)
{
 PLBNODE aux;

 if (pls->pFirstLB!=NULL)
    {
     while (pls->pFirstLB!=NULL)
	   {
            aux=pls->pFirstLB;
            pls->pFirstLB=pls->pFirstLB->pnext;
            aux=FreeLBNODE(aux,CtD,Fill,Color);
	   }
    } 
    
 free((PVOID)pls);
 pls=NULL; 
 return pls; 
}

/*---------------------------------------------------------------------------*/
/*All simplices has the same F                                               */
VOID InsertListB(PLISTB pls, PBOX pB )
{
 PLBNODE pnew,pcurr;
  
 pnew = NewLBNODE(pB);
 
 pls->NElem++;
 if (pls->NElem > pls->MaxNElem)
    pls->MaxNElem = pls->NElem;
  
 if (pls->pFirstLB==NULL)
    {   
     pls->pFirstLB = pnew;
     return;
    }
 
 /*Insert at the beginning*/
 pcurr=pls->pFirstLB;
 pls->pFirstLB=pnew;
 pnew->pnext=pcurr;
}

/*---------------------------------------------------------------------------*/
/*Extract the first Element of the list.                                     */
/*---------------------------------------------------------------------------*/
PBOX ExtractListB(PLISTB pls)
{
 PLBNODE  paux;
 PBOX pB;

 if (pls->pFirstLB==NULL)
    {
     fprintf(stderr,"Trying to extract from a NULL List of boxes\n");
     exit(1);
    }
    
 pls->NElem--;
 paux=pls->pFirstLB;
 pls->pFirstLB=pls->pFirstLB->pnext;
 pB=paux->pB;
 paux->pB=NULL;
 
 free((PVOID)paux);
 
 return pB;
}


/*---------------------------------------------------------------------------*/
VOID PrintListB (FILE * FOut, PLISTB pls, 
				 const INT NDim, const INT MonTest)
{
 PLBNODE pprev,pnext;

 if ( pls->pFirstLB==NULL )
    { 
     fprintf(FOut,"PrintListB: Empty List");
     exit(1);
    }
 else
     {
      fprintf(FOut, "\n---------------------PrintLisS----------------------\n");
      fprintf(FOut,"PLB:nElem = %d.\n",pls->NElem);
      
      pprev=pls->pFirstLB;
      pnext=pprev->pnext;
      PrintBox(FOut,pprev->pB, NDim);
      fprintf(FOut,"->");
      while (pnext!=NULL)
            {
             pprev=pnext;
	     pnext=pnext->pnext;
             PrintBox(FOut,pprev->pB, NDim);
            }
     }
 fprintf(FOut,"PLB:null");
 fprintf(FOut,"\n-----------------End-PrintLisS----------------------\n");
}

/*---------------------------------------------------------------------------*/
VOID DrawListB (PLISTB pls, ConstData &CtD, const BOOL Fill, PCHARCt color)
{
 PLBNODE pprev,pnext;

 if ( pls->pFirstLB==NULL )
    { 
     fputs("DrawListB: Empty List",stderr);
     exit(1);
    } 
 else
     {
      pprev=pls->pFirstLB;
      pnext=pprev->pnext;
      
      DelBox(CtD.NWin,pprev->pB->NBox);
      DrawBox(pprev->pB,CtD,Fill,color);
      
      while (pnext!=NULL)
            {
             pprev=pnext;
			 DelBox(CtD.NWin,pprev->pB->NBox);
			 DrawBox(pprev->pB,CtD,Fill,color);
			 pnext=pnext->pnext;
            }
     }
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
