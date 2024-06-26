/******************************************************************************
                     defines.h  - description
                     ----------------------
       begin		: April 2004
       copywirght	: (C) 2004 by L.G.Casado.

     ********************************************************************
     Purpose: Define new types of data and implement routines that will
       be used by other modules.
**************************************************************************+****/
#ifndef __DEFINES__
#define __DEFINES__

// kv headers
#include <kv/interval.hpp>
#include <kv/rdouble.hpp> //After interval.hpp. To verified IA.
#include <kv/interval-vector.hpp>

// boost headers
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>

namespace ub = boost::numeric::ublas;
typedef kv::interval<double> itv; // interval
typedef ub::vector<itv> itvV;     // interval vector

using namespace std;

/*---------------------------------------------------------------------------*/
typedef size_t SIZE;
typedef void VOID;
typedef VOID *PVOID;
typedef PVOID *PPVOID;
typedef PPVOID *PPPVOID;

typedef int INT;
typedef INT *PINT;
typedef PINT *PPINT;
typedef PPINT *PPPINT;

typedef unsigned long int ULINT;
typedef ULINT *PULINT;

typedef char CHAR;
typedef CHAR *PCHAR;
typedef PCHAR *PPCHAR;

typedef unsigned char UCHAR;
typedef UCHAR *PUCHAR;
typedef PUCHAR *PPUCHAR;

typedef char const CHARCt;
typedef CHARCt *PCHARCt;
typedef PCHARCt *PPCHARCt;

typedef double REAL;
typedef REAL *PREAL;
typedef PREAL *PPREAL;
typedef PPREAL *PPPREAL;
typedef PPPREAL *PPPPREAL;

//------------------------------------------------------------------------------
typedef unsigned char UCHAR;
typedef UCHAR BOOL;
typedef BOOL *PBOOL;
typedef CHAR COMPARE;

//------------------------------------------------------------------------------
#define False 0
#define True 1
#define ZeroInGrad 2
#define PosGrad 3
#define NegGrad 4
#define Reject 5
#define Divide 6

//-----------------------------------------------------------------------------
// Estructure to reduce the parameters in procedure calls.
struct ConstData
{
       int NDim;       // Dimension
       int NFunction;  // Function to evaluate
       int NWin = 0;   // Number of the window to draw. Now just the 0.
       int WWidth = 0; // Graphical width and height
       itvV InititvV;  // When search region is a box
       itvV XLim;      // interval graphical output. Box Search limits.
       BOOL Draw;      // Draw type
       BOOL IncType;   // Inclusion type. See defines below.
       REAL Min;       // Min from input file.
       bool MonTest;
       int NCheckAVL; // Number of iterations after check AVL
};

//------------------------------------------------------------------------------
#define MAXVALUE DBL_MAX
#define MINVALUE DBL_MIN
#define REALPrec 1e-16

//------------------------------------------------------------------------------
#define Greater 1
#define Equal 0
#define Smaller -1

//-----------------------------------------------------------------------------
// Define pCounters[i] names for an easy reordering/printing.
#define CNEvalFG 0    // Number of evaluated FG
#define CNEvalLB 1    // Number of Evaluated LB.
#define CNEvalP 2     // Number of evaluated poimts.
#define CNIters 3     // Number of iterations.
#define CNIncumb 4    // Number of incumbent improvements.
#define CNMonB 5      // Number of CheckMonoSInBox
#define CNSucLbF 6    // NUmber of Improvements of lower bound
#define CNRejRUp 7    // Number of rejected by RangeUp test.
#define CNRejCutOff 8 // Number of rejected by CutOff test.
#define CNRejMon 9    // Number of rejected by Monotonicity test.
#define RangeUp 10    // Number of RangeUp.
#define Coff 11       // NUmber of CutOff .
#define CinsertW 12   // Number of insertion in the work avl.
#define CinsertE 13   // Number of insertion in the End avl.

//-------
#define NCounters 14 // Number of counters.

const char CounterDesc[][40] = // Counters description. 40 Max string lenght
    {
        "N. Eval FG               = ", // 00
        "N. Eval LB               = ", // 01
        "N. Eval Points           = ", // 02
        "N. Iters                 = ", // 03
        "N. Incumbent Impro.      = ", // 04
        "N. Mon. boxes            = ", // 05
        "N. Improvements of LB    = ", // 06
        "N. Reject. by RUp        = ", // 07
        "N. Reject. by CutOff     = ", // 08
        "N. Reject. by Mono. test = ", // 09
        "N. RangeUp              = ",  // 10
        "N. CutOff                = ", // 11
        "N. Insertions in Work    = ", // 12
        "N. Insertions in End     = "  // 13
};

//-----------------------------------------------------------------------------
// Define inclusion types
#define IncTypeIA 0     // Interval Arithmetic.
#define IncTypeCFcBox 1 // Center form from centre in the box.
#define IncTypeCFbBox 2 // Centre form fron b in a box.
#define IncTypeAA 3     // Affine Arithmetic.

#endif /*__DEFINES__*/
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
