/******************************************************************************
                        iutils.cpp  - description
                        ----------------------
        begin           : Feb 2020
        copywirght      : (C) 2020 by L.G.Casado. leo@ual.es

*******************************************************************************/
#include <iostream>
#include <stdlib.h>
#include "defines.h"
#include "utils.h" 
#include "iutils.hpp"

using namespace std;
using namespace kv;


/*---------------------------------------------------------------------------*/
bool iEQ(const itv& x, const itv &y)
{
 return x.lower()==y.lower() && x.upper()==y.upper();
// return ( EQ(x.lower(),y.lower()) && EQ(x.upper(),y.upper()));
}

/*---------------------------------------------------------------------------*/
bool iLT(const itv& x, const itv &y)
{
return (x.lower() <  y.lower() ) || 
       (x.lower() == y.lower()  && x.upper() < y.upper() );

// return ( LT (x.lower(),y.lower() ) || 
//          ( EQ(x.lower(),y.lower() ) && LT( x.upper(),y.upper() ) 
//          ) 
//        );
}
/*---------------------------------------------------------------------------*/
bool iLE(const itv& x, const itv &y)
{
 return ( iEQ(x,y) || iLT(x,y) );
}

/*---------------------------------------------------------------------------*/
bool iGT(const itv& x, const itv &y)
{
 return ( x.upper() >  y.upper()) || 
        ( x.upper() == y.upper() && x.lower()>y.lower() );


// return ( GT(x.upper(),y.upper()) || 
//          ( EQ(x.upper(),y.upper()) && GT(x.lower(),y.lower()) 
//          ) 
//        );
}
/*---------------------------------------------------------------------------*/
bool iGE(const itv& x, const itv &y)
{
 return ( iEQ(x,y) || iGT(x,y));
}

/*---------------------------------------------------------------------------*/
void iUnion(const itv& x, const itv &y, itv &result)
{
 result.lower()=x.lower() <= y.lower() ? x.lower(): y.lower();
 result.upper()=x.upper() >= y.upper() ? x.upper(): y.upper();
}

/*---------------------------------------------------------------------------*/
void iVUnion(const itvV &x, const itvV &y, itvV &result, const int NDim)
{
 for (int i=0;i<NDim;i++)
 	 iUnion(x[i],y[i],result[i]);
}


/*---------------------------------------------------------------------------*/
//Min Distance to Escape from zero.
double MinDE0 (const itv& x) 
{ 
 if (x.upper() < 0.0)
 	return x.upper();

 if (x.lower() > 0.0)
 	return x.lower();

 if (zero_in(x))
	return x.upper() < -x.lower() ? x.upper(): -x.lower();

 fprintf(stderr,"MinDE0: This point could not be reached.\n");
 exit(1);
}

/*---------------------------------------------------------------------------*/
void PrintitvV(FILE * FOut, itvV iV, int NElem)
{
 fprintf(stderr,"\n");
 for (int i=0;i<NElem;i++)
 	 fprintf(stderr,"[%30.30f, %30.30f], \n",iV[i].lower(),iV[i].upper());
 fprintf(stderr,"\n");
}


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
