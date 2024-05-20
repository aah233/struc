/******************************************************************************
			test.h  - description
			----------------------
	begin		: April 2023
	copywirght	: (C) 2023 by L.G.Casado. leo@ual.es.
	
     ********************************************************************	

     Purpose: Define diferent test to be done in the search to remove boxes
     *************************************************************************/
#ifndef __TEST__
#define __TEST__

/*---------------------------------------------------------------------------*/
BOOL RangeUpTest	(PBOX pB, iTDAT & iTDat);
VOID CutOffTest		(PBTB pbtb, ConstData & CtD,iTDAT & iTDat, PINT pCounters);
PBOX TestBox		(PBOX pB,ConstData & CtD, iTDAT & iTDat, PINT pCounters);

#endif /*__TEST__*/
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
