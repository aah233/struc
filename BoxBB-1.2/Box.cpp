/***************************************************************************
                          Box.cpp  -  description
                             -------------------
    begin                : May 2000
    copyright            : (C) 2000 by L.G. Casado
    email                : leo@aual.es
 ***************************************************************************/

#include <iostream>
#include "defines.h"
#include "utils.h"
#include "iutils.hpp"
#include "Box.hpp"

static int BoxCont = 0;

/*----------------------------------------------------------------------------*/
BOX::BOX()
{
   M = false;
   BoxCont++;
   NBox = BoxCont;
   Width = 0;
   IsMon = false;
}

/*----------------------------------------------------------------------------*/
BOX::BOX(int n)
{
   if (n < 0)
   {
      cerr << "BOX::BOX(int) negative size" << endl;
      exit(1);
   }
   X.resize(n);
   GX.resize(n);
   M = false;
   BoxCont++;
   NBox = BoxCont;
   Width = 0;
   IsMon = false;
}

/*---------------------------------------------------------------------------*/
double WidthItvV(itvV &IvV)
{
   int n = IvV.size();
   double Width = width(IvV[0]);
   double LargerWidth = Width;

   for (int i = 1; i < n; i++)
   {
      Width = width(IvV[i]);
      if (Width > LargerWidth)
         LargerWidth = Width;
   }

   return LargerWidth;
}

/*----------------------------------------------------------------------------*/
BOX::BOX(const itvV &IvV)
{
   int n = IvV.size();

   if (n <= 0)
   {
      cerr << "BOX::BOX (const itvV & IvV), ivV.size<=0" << endl;
      exit(1);
   }

   X.resize(n);
   X = IvV; // The contents are copies with memcpy.
   GX.resize(n);
   M = false;
   BoxCont++;
   NBox = BoxCont;
   Width = WidthItvV(X);
   IsMon = false;
}

/*----------------------------------------------------------------------------*/
BOX::BOX(const BOX &B)
{
   int n = B.X.size();

   if (n <= 0)
   {
      cerr << "BOX::BOX (const itvV & IvV), ivV.size<=0" << endl;
      exit(1);
   }
   X.resize(n);
   GX.resize(n);
   X = B.X;
   FX = B.FX;
   GX = B.GX;
   M = B.M;
   BoxCont++;
   NBox = BoxCont;
   Width = B.Width;
   IsMon = false;
}

/*----------------------------------------------------------------------------*/
BOX::~BOX()
{
   X.resize(0);
   GX.resize(0);
}
/*----------------------------------------------------------------------------*/
void BOX::SetWidthBox(const INT NDim)
{
   double Width;
   double SizeBox = width(this->X[0]);

   for (int i = 1; i < NDim; i++)
   {
      Width = width(this->X[i]);
      if (Width > SizeBox)
         SizeBox = Width;
   }
   this->Width = SizeBox;
   return;
}
/*----------------------------------------------------------------------------*/
bool BOX::ReduceBox(ConstData &CtD)
{
   int NDim = CtD.NDim;
   bool Reduce = false;

   for (int i = 0; i < NDim; i++)
      if (!zero_in(this->GX[i]))
      {
         if (this->GX[i].upper() < 0.0 && this->X[i].upper() == CtD.InititvV[i].upper()) // negative -> to right
         {
            this->X[i].lower() = this->X[i].upper();
            Reduce = true;
         }
         if (this->GX[i].lower() > 0.0 && this->X[i].lower() == CtD.InititvV[i].lower()) // positive -> to left
         {
            this->X[i].upper() = this->X[i].lower();
            Reduce = true;
         }
      }
   if (Reduce)
      this.SetWidthBox(CtD.NDim);
   return Reduce;
}
/*----------------------------------------------------------------------------*/
void BOX::Divides(BOX &B1, BOX &B2)
{
   int itvWinner;            // Vector of itv to divide
   double coordenatesMiddle; // Middle of the itvWinner

   // check if the itvV is not empty
   if (this->X.size() <= 0)
   {
      std::cerr << "void Divide(const BOX & B1, const BOX & B2), ivV.size<=0" << std::endl;
      std::exit(1);
   }

   for (int i = 0; i < (int)this->X.size(); i++)
   {
      // ¿Es mas eficiente guardarlo en un itv o en un entero y luego acceder a esa posicion?
      if (width(this->X[i]) == this->Width)
      {
         itvWinner = i;
      }
   }
   coordenatesMiddle = mid(this->X[itvWinner]);
   // Divide the itvWinner in two coordenates and assignate the values to the children
   B1.X[itvWinner].upper() = coordenatesMiddle;
   B2.X[itvWinner].lower() = coordenatesMiddle;

   B1.Width = WidthItvV(B1.X);
   B2.Width = WidthItvV(B2.X);
}

/*---------------------------------------------------------------------------*/
void BOX::DrawBox(ConstData &CtD, bool Fill, PCHARCt color)
{
   double Pos;

   cout << CtD.NWin << endl;
   if (Fill)
      cout << "DrawFillBox" << endl;
   else
      cout << "DrawLineBox" << endl;
   Pos = Normalice(this->X[0].lower(), CtD.XLim(0).lower(), width(CtD.XLim(0)));
   printf("%f\n", Pos * CtD.WWidth);

   Pos = Normalice(this->X[1].lower(), CtD.XLim(1).lower(), width(CtD.XLim(1)));
   // Change pos in [0,1] to [1,0]
   Pos *= -1.0;
   Pos += 1.0;
   printf("%f\n", Pos * CtD.WWidth);

   Pos = Normalice(this->X[0].upper(), CtD.XLim(0).lower(), width(CtD.XLim(0)));
   printf("%f\n", Pos * CtD.WWidth);

   Pos = Normalice(this->X[1].upper(), CtD.XLim(1).lower(), width(CtD.XLim(1)));
   // Change pos in [0,1] to [1,0]
   Pos *= -1.0;
   Pos += 1.0;
   printf("%f\n", Pos * CtD.WWidth);

   if (Fill)
      cout << color << endl;
   else
   {
      if (zero_in(this->GX[0]))
         cout << "Black" << endl;
      else if (this->GX[0].upper() < 0.0) // Negative
         cout << "Blue" << endl;          // Decreases to right
      else                                // Positive
         cout << "Red" << endl;           // Decreases to left

      if (zero_in(this->GX[1]))
         cout << "Black" << endl;
      else if (this->GX[1].upper() < 0.0) // Negative
         cout << "Blue" << endl;          // Decreases up
      else                                // Positive
         cout << "Red" << endl;           // Decreases down
   }

   cout << this->NBox << endl;
}

/*---------------------------------------------------------------------------*/
void BOX::ReplaceBox(const BOX &B)
{
   int n = B.X.size();

   if (n <= 0)
   {
      cerr << "BOX::BOX (const itvV & IvV), ivV.size<=0" << endl;
      exit(1);
   }
   this->X.resize(n);
   this->GX.resize(n);
   this->X = B.X;
   this->FX = B.FX;
   this->GX = B.GX;
   this->M = B.M;
   BoxCont++;
   NBox = BoxCont;
   Width = B.Width;
}
/*----------------------------------------------------------------------------*/
int Dimension(const BOX &B)
{
   return B.X.size();
}

/*------------------------ overload -----------------------------------------*/
ostream &operator<<(ostream &os, const BOX &B)
{
   os << "\tX     = " << B.X << endl;
   os << "\tFX    = " << B.FX << endl;
   os << "\tGX    = " << B.GX << endl;
   os << "\tMonot = " << B.M << endl;
   os << "\tNBox  = " << B.NBox << endl;
   os << "\tw(X)  = " << B.Width << endl;
   return os;
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
