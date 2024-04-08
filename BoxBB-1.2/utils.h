/******************************************************************************
			utils.h  - description
			----------------------
	begin		: April 2004
	copywirght	: (C) 2004 by L.G.Casado.

	 ********************************************************************
	 Purpose: Define common and basic routines.

	OpenFile(): Open a file given by "name" in the mode given by "mode".
	CloseFile(): Check the correct close.
	PrintVR(): Print the contents od a real vector.
	CopyVR(): Copy two real vectors.
	CompareVR(): Compare in order each component of two real vectors.
		If there is a difference it returns if the first is smaller or
		greater, otherwise both vectors are equal.
	CopySQMatrixR(): Copy a square matrix.
	RandomInt(): Generates a real random number between 0 an n with an
		integer value.
	XInWindow(): Given a point in the simplex space, calculates its X
		coordinate in the graphical window space.
	YInWindow(): Given a point in the simplex space, calculates its Y
		coordinate in the graphical window space.
*******************************************************************************/
#ifndef __UTILS__
#define __UTILS__

/*---------------------------------------------------------------------------*/
FILE *OpenFile(char *name, char const *mode);
void CloseFile(FILE *f);
void PrintVR(FILE *FOut, PREAL vr, INT NDim);
void PrintMR(FILE *FOut, PPREAL ppA, INT Rows, INT Cols);
ULINT CountSetBits(ULINT n);
void PrintVINT(FILE *FOut, PINT vr, INT NDim);
void PrintVBOOL(FILE *FOut, PBOOL pB, INT NDim);
void CopyVR(PREAL PD, PREAL PO, INT NDim);
void CopyVINT(PINT PD, PINT PO, INT NDim);
void SwapPInt(int *x, int *y);
double Normalice(double Value, double Lowerbound, double Width);
void CopyVBOOL(PBOOL PD, PBOOL PO, INT NDim);
BOOL IsFalseVBOOL(PBOOL pB, INT NDim);
COMPARE CompareVR(PREAL VR1, PREAL VR2, INT NDim);
REAL RandomInt(INT n);
REAL XInWindow(PREAL pX, const itvV &XLim, INT WWidth);
REAL YInWindow(PREAL pX, const itvV &XLim, INT WWidth);
VOID DrawPoint(PREAL pX, ConstData CtD, const int NPoint,
			   PCHARCt color);
VOID DrawColorPoint(const BOOL Draw, const INT NWin, const INT NPoint,
					PCHARCt color);
VOID DelPoint(const INT NWin, const INT NPoint);
VOID DrawArrow(const INT NWin, PREAL pR1, PREAL pR2,
			   const int NArrow, const itvV &XLim,
			   const INT WWidth, PCHARCt Color);
double Normalice(double Value, double Lowerbound, double Width);
VOID DelArrow(INT NWin, int NArrow);
VOID DrawCircle(PREAL pX, int NCircle, ConstData CtD, PCHARCt color);
VOID DelCircle(const INT NWin, const INT NCircle);
VOID DrawPolygon(PPREAL ppPoints, int NPoints, int NDim, int NPoly,
				 ConstData CtD, PCHARCt color);
VOID DrawWait(const int NWin);
INT Fact(INT n);
PPINT CombNoRep(INT n, INT k, PINT pNComb);
INT CombN2ToIndex(INT N, INT x, INT y);
VOID IndexToCombN2(INT N, INT Index, PINT px, PINT py);
REAL DistPoints(PREAL p1, PREAL p2, INT NDim);
bool EQ(REAL a, REAL b);
bool LT(REAL a, REAL b);
bool GT(REAL a, REAL b);
bool LE(REAL a, REAL b);
bool GE(REAL a, REAL b);
void MiddlePoint(PREAL pA, PREAL pB, PREAL pMiddle, INT NDim);
void SwapR(REAL &A, REAL &B);

#endif /*__UTILS__*/
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
