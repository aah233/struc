/******************************************************************************
			box.hpp  - description
			----------------------
	begin		: April 2023
	copywirght	: (C) 2023 by L.G.Casado.

	 ********************************************************************
	 Purpose: Define the container box.

	 Stores:
	NBox 		: Box's number; for drawing purposes.
	Size		: Size of the longest edge of the box.
	F			: Inclusion of the real rangue over the box.
	G			: Inclusion of the derivatives over the box.
	IsMon		: If f is monotonous on B.
	Feas		: If the box is feasible:: 0 No, 1

	--------------
	If search region is a box: !CtD.SInBox, to update
	pIsBorderFacet[i]=False after reduction:
	pVertexAtBorder: index of the vertex at initial border.
	pEdgeOfVertexAtBorder: Edge the vertex at border belongs to.
		Initial vertices may belong to many.

	Functions:

		EvalBox()   : Set the values of F and G.
		InitBox()   : Creates the init box. Allocates memory an
						  initialice  the values. The vertexes are stored in
						  the BTV if they did not be there.
						  The vertex's number of boxes is increased.
	FreeBox() : Free the memory allocates by box. Decrease the
		vertex's box counter and if it is cero, the vertex is
		removed from the balanced binary tree of vertexes.
	PrintBox(): Print the contents of the box.
	DrawBox(): Graphical output of the box.
	DelBox(): Delete the box from the graphical output.
	DivideBox(): Generates two simplices. One of them inherit the data
		structure of the parent.

   Notes: The vertexes are stored in btvertex when the box is initiated
	  or when it is splitted.

******************************************************************************/
#ifndef __BOX__
#define __BOX__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <signal.h>
#include "defines.h"
#include "getmem.h"
#include "utils.h"
#include "iutils.hpp"
#include "Functions.hpp"

using namespace std;

#define Unfeas 0
#define Feas 1
#define Unknown -1

/*---------------------------------------------------------------------------*/
struct typebox
{
	INT NBox;
	itvV pX; // interval vector defining B.
	itv F;	 // inclusion of f(B)
	itvV G;	 // Gradient of B
	REAL Size;
	bool IsMon = false;
};

typedef struct typebox BOX;
typedef BOX *PBOX;
typedef PBOX *PPBOX;

struct iTDAT // Temporal data to kv
{
	PBOX pBIncumb; // For Incombent
	PBOX pBPoint;  // For centoid, bumman, etc
	ub::vector<double> rVector;
};

/*---------------------------------------------------------------------------*/
INT GetNewNBox();
PBOX GetMemBox(const int NDim);
VOID PrintBox(FILE *FOut, PBOX pB, const INT NDim);
VOID DrawBox(const PBOX pB, ConstData &CtD, bool Fill, PCHARCt color);
VOID DelBox(const int NWin, const int NBox);
void EvalBox(PBOX pB, ConstData &CtD, iTDAT &iTDat, PINT pCounters);
PBOX InitBox(ConstData &CtD, iTDAT &iTDat, PINT pCounters);
PBOX FreeBox(PBOX pB, ConstData &CtD, const BOOL Fill, PCHARCt Color);
void DivideBox(PBOX &pB, PBOX &pB1, PBOX &pB2, ConstData &CtD, iTDAT &iTDat,
			   PINT pCounters);
bool ReduceBox(PBOX pB, ConstData &CtD);
#endif /*__BOX__*/
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
