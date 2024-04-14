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
bool RangeUpTest(PBOX pB, iTDAT &iTDat);
// VOID CutOffTest		(PBTB pbtb, ConstData & CtD,iTDAT & iTDat);
bool TestBox(PBOX pB, ConstData &CtD, PINT pCounters, iTDAT &iTDat);
void EvalBoxCentre(PBOX pB, ConstData CtD, iTDAT iTDat, PINT pCounters);
void EvalBPoint(PBOX pBPoint, PBOX pBIncumb, ConstData CtD, PINT pCounters);

#endif /*__TEST__*/
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
