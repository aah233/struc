/***************************************************************************
                          Problems.cpp  -  description
                             -------------------
    begin                : Jan 2020
    copyright            : (C) 2020 by L.G. Casado
    email                : leo@ual.es
    
 ***************************************************************************/
#include <iostream>
#include "hess_ari.hpp"
#include "imath.hpp"
#include "Box.hpp"
#include "Problems.hpp"

using namespace cxsc;
using namespace std;

/*----------------------------------------------------------------------------*/
HessType fKearEx1 ( const HTvector & x )
{
 return power(x[1],2)+power(x[2],3);
}

/*----------------------------------------------------------------------------*/
HessType fKearEx2 ( const HTvector & x )
{ 
 return 0.25*power(x[1],2)+x[1]+x[2]+0.25*x[1]*x[2]+0.25*power(x[2],3);
}


/*----------------------------------------------------------------------------*/
HessType fKearEx6 ( const HTvector & x )
{
 return 0.25*power(x[1],2)+x[1]+x[2]+0.25*x[1]*x[2]+0.25*power(x[2],2);
}


/*----------------------------------------------------------------------------*/
void fEvalProblem (int NProblem, PBOX pb, int & NEvalF)
{
 switch (NProblem)
        {
         case 1 :
         		fEvalH(fKearEx1,pb->X,pb->FX[1]);
         		break;	
         case 2 :
         		fEvalH(fKearEx2,pb->X,pb->FX[1]);
         		break;		
         case 3 :
         		fEvalH(fKearEx6,pb->X,pb->FX[1]);
         		break;					
         default:
         	cerr << "No such problem" << endl;
         	exit(1);
        }
 NEvalF++;
}

/*----------------------------------------------------------------------------*/
void fgEvalProblem (int NProblem, PBOX pb, int & NEvalG)
{
 int i, NDim;
 NDim = Dimension(*pb);

 switch (NProblem)
        {
         case 1 :
         		fgEvalH(fKearEx1,pb->X,pb->FX[1],pb->GX);
         		break;	
         case 2 :
         		fgEvalH(fKearEx2,pb->X,pb->FX[1],pb->GX);
         		break;
         case 3 :
         		fgEvalH(fKearEx6,pb->X,pb->FX[1],pb->GX);
         		break;        				
         default:
         	cerr << "No such problem" << endl;
         	exit(1);
        }
 NEvalG++;
 
 //cerr << "GX=" << GX << endl << endl;

 pb->M=false;
 for ( i=1; i<=NDim; i++ )
     if (  !((real)0.0 <= pb->GX[i])  )
        {
         pb->M=true;
         break;
        }     
}

