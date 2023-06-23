/***************************************************************************
                          Box.cpp  -  description
                             -------------------
    begin                : May 2000
    copyright            : (C) 2000 by L.G. Casado
    email                : leo@aual.es
 ***************************************************************************/

#include <iostream>
#include "Box.hpp"

static int BoxCont = 0;

/*----------------------------------------------------------------------------*/
BOX::BOX ()
{
 M=false;
 BoxCont++;
 NBox=BoxCont;
}

/*----------------------------------------------------------------------------*/
BOX::BOX (int n)
{
 if (n<0)
    {
     cerr << "BOX::BOX(int) negative size" << endl;
     exit(1);
    }
 Resize(X,n);
 if (n>0)
    Resize(FX,3);
 Resize(GX,n);
 M=false;
 BoxCont++;
 NBox=BoxCont;  
}

/*----------------------------------------------------------------------------*/
BOX::BOX (const ivector & IV)
{
 X=IV;					//The contents are copies with memcpy.
 if (VecLen(IV)!=0)
    {
     Resize(FX,3);
     //Clear(FX);
    }
 Resize(GX,VecLen(IV));
 M=false;
 BoxCont++;
 NBox=BoxCont; 
}

/*----------------------------------------------------------------------------*/
BOX::BOX(const BOX & B)
{
 X=B.X;
 FX=B.FX;
 GX=B.GX;
 M=B.M;
 NBox=B.NBox;
}

/*----------------------------------------------------------------------------*/
BOX::~BOX ()
{
 Resize(X,0);
 Resize(FX,0);
 Resize(GX,0);
}

/*---------------------------------------------------------------------------*/
/* Not necessary because the data in Box is public.                          */
/*---------------------------------------------------------------------------*/
/*
ivector GetFX(BOX & B)
{
 return B.FX;
}
*/
/*----------------------------------------------------------------------------*/
int Dimension (const BOX & B)
{
 return VecLen(B.X);
}

/*----------------------------------------------------------------------------*/
void Resize (BOX & B, int n)
{
 if ( n<0 )
    {
     cerr << "Resize(BOX $, int): negative size" << endl;
     exit(1);
    }
    
 if ( VecLen(B.X)== n ) 
    return;
 
 Resize(B.X,n); //Profil IntervalVector.C, uses CheckMemory from Profil Error.C
 if (n==0)
    Resize(B.FX,0);
 else
    Resize(B.FX,3);
}

/*----------------------------------------------------------------------------*/
void Clear (BOX & B)
{
 //Clear(B.X);
 //Clear(B.FX);
 //Clear(B.GX);
 B.M=false;
}


/*----------------------------------------------------------------------------*/
/* Output the imput data of WindowsAI.tcl to draw the two dimensional box.    */
/*----------------------------------------------------------------------------*/
void BOX::Draw (const ivector & XLim, int WWidth, char const * color )
{
 real FYDiam,FXDiam;
 
 FXDiam = diam(XLim[1]);
 FYDiam = diam(XLim[2]);
 
 cout << "PintaBox" << endl;
 
 cout << (Inf(X[1])-Inf(XLim[1]))  / FXDiam * (real)(WWidth-1) << endl; 
 
 cout << ((Inf(X[2])-Inf(XLim[2])) / FYDiam * (real)(-1.0) + (real)1.0 ) *
         (real)(WWidth-1) << endl;
	 
 cout << (Sup(X[1])-Inf(XLim[1]))  / FXDiam * (real)(WWidth-1) << endl; 
 
 cout << ((Sup(X[2])-Inf(XLim[2])) /FYDiam  * (real)(-1.0) + (real)1.0 ) *
         (real)(WWidth-1) << endl; 
         
 cout << color << endl;
 cout << NBox << endl;
}

/*---------------------------------------------------------------------------*/
void BOX::UnDraw ()
{
 cout << "BorraBox" << endl;
 cout << NBox << endl;
}

/*----------------------------------------------------------------------------*/
ostream & operator << (ostream & os, const BOX & B)
{
  os << "\tX     = " << B.X  <<endl;
  os << "\tw(X)  = " << diam(B.X)<< endl;
  os << "\tFX    = " << B.FX << endl;
  os << "\tGX    = " << B.GX << endl;
  os << "\tMonot = " << B.M << endl;
  os << "\tNBox  = " << B.NBox << endl;
  return os;
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
