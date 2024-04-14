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
#include "Box.hpp"
#include "itdat.h"
#include "listbox.h"
#include "test.hpp"

#define PRINT 0

/*---------------------------------------------------------------------------*/
/*
VOID CutOffTest(PBTB PBTB, ConstData &CtD, iTDAT &iTDat)
{
	itv MaxBTBKey; // Tree sorted by pB->F.
	PBOX pB = NULL;
	BOOL Pop = False; // All simplices with same Key are removed. pB=NULL.
	double IncumbVal = iTDat.pBIncumb->F.upper();

	if (PBTB->NElem == 0)
		return;

	MaxBTBKey = GetMaxBTBKey(PBTB);
	// cerr << "=========================" << endl;
	// cerr << "CutOff Test before" << endl;
	while (MaxBTBKey.lower() > IncumbVal)
	{
		//		cerr << "CutOff Test:" << endl;
		//		cerr << "MaxBTBKey=" << MaxBTBKey<< endl;
		//		fprintf(stderr,"IncumbVal=%10.10f\n",IncumbVal);
		//		cerr << "PBTB->NElem=" << PBTB->NElem << endl;
		//		CheckBTBOrder(PBTB);
		//		cerr << "=========================" << endl;
		ExtractEqualBTB(PBTB, &pB, CtD, MaxBTBKey, Pop, True, "#806080"); // Purple
		//		fprintf(stderr,"CutOff works!!!.\n");
		if (pB != NULL)
		{
			fprintf(stderr, "CutOffTest: pB!=NULL with Pop=False.\n");
			exit(1);
		}

		if (PBTB->NElem > 0)
		{
			MaxBTBKey = GetMaxBTBKey(PBTB);
			//			cerr << "MaxBTBKey=" << MaxBTBKey<< endl;
			//			cerr << "PBTB->NElem=" << PBTB->NElem << endl;
		}
		else
			break;
	}
	// cerr << "CutOff Test After" << endl;
	// CheckBTBOrder(PBTB);
	// cerr << "CutoffEnd" << endl;
	// cerr << "PBTB->NElem=" << PBTB->NElem << endl;
	// if (EQ(IncumbVal,-185.4573382571))
	//   PrintBTB(stderr,PBTB,CtD.NDim);
}
*/
/*---------------------------------------------------------------------------*/
// evaluar el punto medio sirve con el rangeuptest , que es eliminar la caja en el caso de que en la evaluación F esté por encima de la F del mejor punto
bool RangeUpTest(PBOX pB, iTDAT &iTDat)
{
	if (pB->FX.lower() > iTDat.pBIncumb->FX.upper())
		return True;
	return False;
}

/*---------------------------------------------------------------------------*/
// If return true we need to delete Box, Draw and delete
/**
 * @param  Pb to evalue
 * @param  CtD Constant data in the app
 * @param  pCounters Counter of the app
 * @param  pbItad The best box
 */
bool TestBox(PBOX pB, ConstData &CtD, PINT pCounters, iTDAT &iTDat)
{
	if (pB == NULL)
	{
		fprintf(stderr, "TestBox:pB==NULL.\n");
		exit(1);
	}
	// Rangue Up
	if (RangeUpTest(pB, iTDat))
	{
		// pinto y devuelvo
		pB->DrawBox(CtD, true, "#c08040"); // Draw  Brown
		return True;
	}

	// Monotonous
	if (pB->IsMon) // Monotonous() returns if 0 in G
	{
		if (CtD.Draw)
		{
			pB->DrawBox(CtD, true, "#00e000"); // Monotonous and interior
		}
		if (!pB->ReduceBox(CtD))
		{
			return True;
		}
		// Box was reduced, and for this need a new eval
		fgEvalIA(CtD.NFunction, pB->X, pB->FX, pB->GX);
		if (RangeUpTest(pB, iTDat))
		{
			pB->DrawBox(CtD, true, "#c08040"); // Draw  Brown
			return True;
		}
	}
	// if return False the Box pass all test, see defines.h
	return False;
}

/*---------------------------------------------------------------------------*/
void EvalBoxCentre(PBOX pB, ConstData CtD, iTDAT iTDat, PINT pCounters)
{
	PBOX pBCentre = iTDat.pBPoint;
	PBOX pBIncumb = iTDat.pBIncumb;

	// We need PREAL for ProcessPoint and rVector for innerprod
	for (int i = 0; i < CtD.NDim; i++)
		pBCentre->X[i] = iTDat.rVector(i) = mid(pB->X(i));

	pBCentre->NBox = pB->NBox;
	EvalBPoint(pBCentre, pBIncumb, CtD, pCounters);
}

/*---------------------------------------------------------------------------*/

void EvalBPoint(PBOX pBPoint, PBOX pBIncumb, ConstData CtD, PINT pCounters)
{
	fEvalIA(CtD.NFunction, pBPoint->X, pBPoint->FX);
	pCounters[CNEvalP]++;

	if (CtD.Draw)
		pBPoint->DrawBPoint(CtD, "Yellow");

	if (pBPoint->FX.upper() < pBIncumb->FX.upper())
	{
		if (CtD.Draw)
		{
			DrawColorPoint(CtD.Draw, 0, pBIncumb->NBox, "Yellow");
			DrawColorPoint(CtD.Draw, 0, pBPoint->NBox, "Red");
		}
		pCounters[CNIncumb]++;
		for (int i = 0; i < CtD.NDim; i++) // Copy pBCentre to pBIncumb
			pBIncumb->X[i] = pBPoint->X[i];
		pBIncumb->FX = pBPoint->FX;
		pBIncumb->NBox = pBPoint->NBox;
	}
}
