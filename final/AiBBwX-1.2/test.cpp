/******************************************************************************
			test.c  - description
			----------------------
	begin		: February 2020
	copywirght	: (C) 2020 by L.G.Casado. leo@ual.es
	
*******************************************************************************/
#include <limits.h>
#include "defines.h"
#include "getmem.h"
#include "utils.h"  
#include "iutils.hpp"
#include "Functions.hpp"
#include "box.hpp"
#include "listbox.h"
#include "btbox.h"
#include "test.hpp"

#define PRINT 0

/*---------------------------------------------------------------------------*/
VOID CutOffTest(PBTB PBTB, ConstData & CtD, iTDAT & iTDat, PINT pCounters)
{
 itv MaxBTBKey; //Tree sorted by pB->F.
 PBOX pB=NULL;
 BOOL Pop=False; //All simplices with same Key are removed. pB=NULL.
 double IncumbVal=iTDat.pBIncumb->F.upper();
 
 if (PBTB->NElem==0)
	return;
 
 MaxBTBKey=GetMaxBTBKey(PBTB);
// cerr << "=========================" << endl;
// cerr << "CutOff Test before" << endl;
 while ( MaxBTBKey.lower() > IncumbVal )
	   {
//		cerr << "CutOff Test:" << endl;
//		cerr << "MaxBTBKey=" << MaxBTBKey<< endl;
//		fprintf(stderr,"IncumbVal=%10.10f\n",IncumbVal);
//		cerr << "PBTB->NElem=" << PBTB->NElem << endl; 
//		CheckBTBOrder(PBTB);
//		cerr << "=========================" << endl;
		ExtractEqualBTB(PBTB,&pB,CtD,MaxBTBKey,Pop,True,"#806080"); //Purple
		pCounters[CNRejCutOff]++;
//		fprintf(stderr,"CutOff works!!!.\n");
		if (pB!=NULL)
		   {
			fprintf(stderr,"CutOffTest: pB!=NULL with Pop=False.\n");
			exit(1);
		   }

		if (PBTB->NElem>0)
		   {
			MaxBTBKey=GetMaxBTBKey(PBTB);
//			cerr << "MaxBTBKey=" << MaxBTBKey<< endl;
//			cerr << "PBTB->NElem=" << PBTB->NElem << endl; 
		   } 
		else
		   break;
	   }
// cerr << "CutOff Test After" << endl;
//CheckBTBOrder(PBTB); 
// cerr << "CutoffEnd" << endl; 
// cerr << "PBTB->NElem=" << PBTB->NElem << endl;
//if (EQ(IncumbVal,-185.4573382571))
//   PrintBTB(stderr,PBTB,CtD.NDim);
}

/*---------------------------------------------------------------------------*/
BOOL RangeUpTest(PBOX pB, iTDAT & iTDat)
{
 if ( pB->F.lower() > iTDat.pBIncumb->F.upper() )
	return True;
 return False;
}


/*---------------------------------------------------------------------------*/
PBOX TestBox(PBOX pB,ConstData & CtD,iTDAT & iTDat,PINT pCounters)
{
 if (pB==NULL)
 	{
 	 fprintf(stderr,"TestBox:pB==NULL.\n");
 	 exit(1);
 	}
 //Rangue Up
 if ( RangeUpTest(pB,iTDat) )
	{
	 pCounters[CNRejRUp]++;
	 //fprintf(stderr,"BOX %d RangueUpTest.\n",pB->NBox);
	 pB=FreeBox(pB,CtD,True,"#c08040"); //Brown
	 return pB;
	} 
 
 //Monotonous
 if (CtD.MonTest && pB->IsMon) //Monotonous() returns if 0 in G
 	{
 	 if (CtD.Draw)
 	 	{
 	 	 DelBox(CtD.NWin,pB->NBox);
 	 	 DrawBox(pB,CtD,true,"#00e000"); //Monotonous and interior
 	 	 pB->NBox=GetNewNBox(); //To not delete the reduced area at reduce 
 	 	}
 	 if (!ReduceBox(pB,CtD))
 	    {
 	     pB=FreeBox(pB,CtD,true,"#00e000"); //Green
 	     return pB;
 	    }
 	 //TODO: What if a zero size box? 
 	 //Box was reduced.
 	 EvalBox(pB,CtD,iTDat,pCounters);
	 if (RangeUpTest(pB,iTDat) )
		{
		 pCounters[CNRejRUp]++;
	 	 pB=FreeBox(pB,CtD,true,"#c08040"); //Brown
	 	 return pB;
		}
 	}
 
 return pB;
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
