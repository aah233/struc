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
 Width=0;
}

/*----------------------------------------------------------------------------*/
BOX::BOX (int n)
{
 if (n<0)
    {
     cerr << "BOX::BOX(int) negative size" << endl;
     exit(1);
    }
 X.resize(n);
 GX.resize(n);
 M=false;
 BoxCont++;
 NBox=BoxCont;  
 Width=0;
}

/*---------------------------------------------------------------------------*/
double WidthItvV(itvV & IvV)
{
 int n=IvV.size();
 double LargerWidth;
 double Width=width(IvV[0]);

 for (int i=1;i<n;i++) {
  Width=width(IvV[i]);
  if (Width>LargerWidth)
  	 LargerWidth=Width;
 }

 return LargerWidth;
}

/*----------------------------------------------------------------------------*/
BOX::BOX (const itvV & IvV)
{
 int n=IvV.size();
 
 if (n<=0)
 {
  cerr << "BOX::BOX (const itvV & IvV), ivV.size<=0" << endl;
  exit(1);
 }

 X.resize(n);
 X=IvV;					//The contents are copies with memcpy.
 GX.resize(n);
 M=false;
 BoxCont++;
 NBox=BoxCont;
 Width=WidthItvV(X);
}

/*----------------------------------------------------------------------------*/
BOX::BOX(const BOX & B)
{
 int n=B.X.size();
 
 if (n<=0)
 {
  cerr << "BOX::BOX (const itvV & IvV), ivV.size<=0" << endl;
  exit(1);
 }
 X.resize(n);
 GX.resize(n);
 X=B.X;
 FX=B.FX;
 GX=B.GX;
 M=B.M;
 BoxCont++;
 NBox=BoxCont;
 Width=B.Width;
}

/*----------------------------------------------------------------------------*/
BOX::~BOX ()
{
 X.resize(0);
 GX.resize(0);
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
 return B.X.size();
}


/*----------------------------------------------------------------------------*/
ostream & operator << (ostream & os, const BOX & B)
{
  os << "\tX     = " << B.X  <<endl;
  os << "\tFX    = " << B.FX << endl;
  os << "\tGX    = " << B.GX << endl;
  os << "\tMonot = " << B.M << endl;
  os << "\tNBox  = " << B.NBox << endl;
  os << "\tw(X)  = " << B.Width << endl;
  return os;
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
