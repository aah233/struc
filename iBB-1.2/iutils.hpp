/******************************************************************************
			iutils.h  - description
			----------------------
	begin		: February 2020
	copywirght	: (C) 2020 by L.G.Casado. leo@ual.es
	
     ********************************************************************	
     Purpose: Define new routines that I did not found in c-xsc. 
	
*******************************************************************************/
#ifndef __IUTILS__
#define __IUTILS__

/*---------------------------------------------------------------------------*/
bool iEQ		(const itv& x, const itv &y);
bool iLT		(const itv& x, const itv &y);
bool iLE		(const itv& x, const itv &y);
bool iGT		(const itv& x, const itv &y);
bool iGE		(const itv& x, const itv &y);
void iUnion		(const itv& x, const itv &y, itv &result);
void iVUnion	(const itvV &x, const itvV &y, itvV &result, const int NDim);
double MinDE0 	(const itv& x);
void PrintitvV(FILE * FOut, itvV iV, int NElem);
#endif /*__IUTILS__*/
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
