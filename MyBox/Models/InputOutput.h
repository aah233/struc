#include <kv/interval.hpp>
#include <kv/rdouble.hpp> //After interval.hpp. To verified IA.
#include <kv/interval-vector.hpp>

#ifndef __INPUTOUTPUT__   //Check if the header has been defined
#define __INPUTOUTPUT__   //If not, define it      //Include the define.h header file

//Definde a new type of data
typedef char		CHAR;
typedef CHAR	*	PCHAR;
typedef	PCHAR	* 	PPCHAR;

//Define a new type of data
typedef ub::vector <itv>  itvV; 		//interval vector
struct ConstData
       {
        int NDim;		//Dimension
        int NFunction;	//Function to evaluate
        int NWin=0; 	//Number of the window to draw. Now just the 0.
        int WWidth=0; 	//Graphical width and height
        itvV InitBox;   //When search region is a box
        itvV XLim;	    //interval graphical output. Box Search limits.
        BOOL Draw;	    //Draw type
        BOOL IncType;   //Inclusion type. See defines below.
        REAL Min;		//Min from input file.
       };

void GetParams   (int argc, PPCHAR argv, ConstData & CtD, double & Alpha);

#endif /*__INPUTOUTPUT__*/  //simple end of the header file