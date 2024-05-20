/******************************************************************************
                        Box.c  - description
                        ----------------------
        begin           : April 2023
        copywirght      : (C) 2023 by L.G.Casado.

*******************************************************************************/
#include "box.hpp"

/*---------------------------------------------------------------------------*/
INT GetNewNBox()
{
   static int NBox = 0;

   NBox++;
   return NBox;
}

/*---------------------------------------------------------------------------*/
PBOX GetMemBox(const int NDim)
{
   PBOX pB;

   pB = (PBOX)GetMem((SIZE)1, (SIZE)sizeof(BOX), "GetMemBox");
   // All generated simplices will be evaluatedin F and G.
   pB->pX.resize(NDim);
   pB->G.resize(NDim);

   return pB;
}

/*---------------------------------------------------------------------------*/
void SizeBox(PBOX &pB, const INT NDim)
{
   double Width;
   double Size = width(pB->pX[0]);

   for (int i = 1; i < NDim; i++)
   {
      Width = width(pB->pX[i]);
      if (Width > Size)
         Size = Width;
   }
   pB->Size = Size;

   return;
}

/*---------------------------------------------------------------------------*/
VOID PrintBox(FILE *FOut, PBOX pB, const INT NDim)
{
   if (pB == NULL)
   {
      fprintf(stderr, "PrintBox: pB==NULL.\n");
      exit(1);
   }
   fprintf(FOut, "------------------------Print-Box-----------------------\n");
   fprintf(FOut, "NBox\t = %d\n", pB->NBox);
   fprintf(FOut, "Size\t = %g\n", pB->Size);
   fprintf(FOut, "IsMon\t = ");
   if (pB->IsMon == True)
      fprintf(FOut, "T\n");
   else
      fprintf(FOut, "F\n");

   cerr << "pX\t = ";
   cerr << pB->pX << endl;

   cerr << "F\t = ";
   cerr << pB->F << endl;
   cerr << "G\t = ";
   cerr << pB->G << endl;

   fputs("\n", FOut);
   fputs("-----------------End-Print-Box-------------------\n", stderr);
}

/*---------------------------------------------------------------------------*/
VOID DrawBox(const PBOX pB, ConstData &CtD, bool Fill, PCHARCt color)
{
   double Pos;

   cout << CtD.NWin << endl;
   if (Fill)
      cout << "DrawFillBox" << endl;
   else
      cout << "DrawLineBox" << endl;

   Pos = Normalice(pB->pX[0].lower(), CtD.XLim(0).lower(), width(CtD.XLim(0)));
   printf("%f\n", Pos * CtD.WWidth);

   Pos = Normalice(pB->pX[1].lower(), CtD.XLim(1).lower(), width(CtD.XLim(1)));
   // Change pos in [0,1] to [1,0]
   Pos *= -1.0;
   Pos += 1.0;
   printf("%f\n", Pos * CtD.WWidth);

   Pos = Normalice(pB->pX[0].upper(), CtD.XLim(0).lower(), width(CtD.XLim(0)));
   printf("%f\n", Pos * CtD.WWidth);

   Pos = Normalice(pB->pX[1].upper(), CtD.XLim(1).lower(), width(CtD.XLim(1)));
   // Change pos in [0,1] to [1,0]
   Pos *= -1.0;
   Pos += 1.0;
   printf("%f\n", Pos * CtD.WWidth);

   if (Fill)
      cout << color << endl;
   else
   {
      if (zero_in(pB->G[0]))
         cout << "Black" << endl;
      else if (pB->G[0].upper() < 0.0) // Negative
         cout << "Blue" << endl;       // Decreases to right
      else                             // Positive
         cout << "Red" << endl;        // Decreases to left

      if (zero_in(pB->G[1]))
         cout << "Black" << endl;
      else if (pB->G[1].upper() < 0.0) // Negative
         cout << "Blue" << endl;       // Decreases up
      else                             // Positive
         cout << "Red" << endl;        // Decreases down
   }

   cout << pB->NBox << endl;
}

/*---------------------------------------------------------------------------*/
VOID DelBox(const int NWin, const int NBox)
{
   cout << NWin << endl;
   cout << "DelBox" << endl;
   cout << NBox << endl;
}

/*---------------------------------------------------------------------------*/
VOID DrawBPoint(PBOX pB, ConstData CtD, PCHARCt color)
{
   double Pos;

   printf("%d\n", CtD.NWin);
   printf("DrawPoint\n");

   Pos = Normalice(mid(pB->pX[0]), CtD.XLim(0).lower(), width(CtD.XLim(0)));
   printf("%f\n", Pos * CtD.WWidth);
   Pos = Normalice(mid(pB->pX[1]), CtD.XLim(1).lower(), width(CtD.XLim(1)));
   // Change pos in [0,1] to [1,0]
   Pos *= -1.0;
   Pos += 1.0;
   printf("%f\n", Pos * CtD.WWidth);

   printf("%s\n", color);

   printf("%d\n", pB->NBox);

   fflush(stdout);
}

/*---------------------------------------------------------------------------*/
VOID DelBPoint(const INT NWin, const INT NPoint)
{
   printf("%d\n", NWin);
   printf("DelPoint\n");
   printf("%d\n", NPoint);
}

/*---------------------------------------------------------------------------*/
VOID EvalBPoint(PBOX pBPoint, PBOX pBIncumb, ConstData CtD,
                PINT pCounters)
{
   fEvalIA(CtD.NFunction, pBPoint->pX, pBPoint->F);
   pCounters[CNEvalP]++;

   if (CtD.Draw)
      DrawBPoint(pBPoint, CtD, "Yellow");

   if (pBPoint->F.upper() < pBIncumb->F.upper())
   {
      if (CtD.Draw)
      {
         DrawColorPoint(CtD.Draw, 0, pBIncumb->NBox, "Yellow");
         DrawColorPoint(CtD.Draw, 0, pBPoint->NBox, "Red");
      }
      pCounters[CNIncumb]++;
      for (int i = 0; i < CtD.NDim; i++) // Copy pBCentre to pBIncumb
         pBIncumb->pX[i] = pBPoint->pX[i];
      pBIncumb->F = pBPoint->F;
      pBIncumb->NBox = pBPoint->NBox;
   }
}

/*---------------------------------------------------------------------------*/
void EvalBoxCentre(PBOX pB, ConstData CtD, iTDAT iTDat, PINT pCounters)
{
   PBOX pBCentre = iTDat.pBPoint;
   PBOX pBIncumb = iTDat.pBIncumb;

   // We need PREAL for ProcessPoint and rVector for innerprod
   for (int i = 0; i < CtD.NDim; i++)
      pBCentre->pX[i] = iTDat.rVector(i) = mid(pB->pX(i));

   pBCentre->NBox = pB->NBox;
   EvalBPoint(pBCentre, pBIncumb, CtD, pCounters);
}

/*---------------------------------------------------------------------------*/
void CFcBox(PBOX pB, ConstData CtD, iTDAT iTDat, PINT pCounters)
{
   PBOX pBCentre = iTDat.pBPoint;

   REAL Oldlb;
   itv iCFcBox;

   // Updates iTDat.rVector
   EvalBoxCentre(pB, CtD, iTDat, pCounters);

   Oldlb = pB->F.lower();
   // see kv/kv/optimize.hpp line 113
   iCFcBox = pBCentre->F + inner_prod(pB->G, pB->pX - iTDat.rVector);

   // cerr << "pB->F  =" << pB->F  << endl;
   // cerr << "iCFcBox=" << iCFcBox << endl;

   pB->F = intersect(pB->F, iCFcBox);
   pCounters[CNEvalLB]++;

   if (Oldlb < pB->F.lower())
      pCounters[CNSucLbF]++; // N. Inf(pB->F) Impro
}

/*---------------------------------------------------------------------------*/
void CFbBox(PBOX pB, ConstData CtD, iTDAT &iTDat, PINT pCounters)
{
   // pBaumman points to the temporal vertex ppTVertices[1].
   PBOX pBBaum = iTDat.pBPoint;
   PBOX pBIncumb = iTDat.pBIncumb;
   REAL Oldlb;
   itv iCFbBox;

   for (int i = 0; i < CtD.NDim; i++)
   {
      if (LE(pB->G[i].upper(), 0.0))
      {
         pBBaum->pX[i] = iTDat.rVector(i) = pB->pX[i].upper();
         continue;
      }
      if (GE(pB->G[i].lower(), 0.0))
      {
         pBBaum->pX[i] = iTDat.rVector(i) = pB->pX[i].lower();
         continue;
      }
      pBBaum->pX[i] = iTDat.rVector(i) =
          (pB->G[i].upper() * pB->pX[i].lower() -
           pB->G[i].lower() * pB->pX[i].upper()) /
          width(pB->G[i]);
   }

   pBBaum->NBox = pB->NBox;
   EvalBPoint(pBBaum, pBIncumb, CtD, pCounters);

   Oldlb = pB->F.lower();
   // see kv/kv/optimize.hpp line 113
   iCFbBox = pBBaum->F + inner_prod(pB->G, pB->pX - iTDat.rVector);

   // cerr << "pB->F  =" << pB->F  << endl;
   // cerr << "iCFbBox=" << iCFbBox << endl;

   pB->F = intersect(pB->F, iCFbBox);
   pCounters[CNEvalLB]++;

   if (Oldlb < pB->F.lower())
      pCounters[CNSucLbF]++; // N. Inf(pB->F) Impro
}

/*---------------------------------------------------------------------------*/
// Eval F and G.
VOID EvalFGInB(PBOX pB, ConstData &CtD, int &NEval)
{
   fgEvalIA(CtD.NFunction, pB->pX, pB->F, pB->G);
   NEval++;

   if (CtD.Draw)
   {
      DrawBox(pB, CtD, false, ""); // Not fill
      if (CtD.Draw == 2)
         DrawWait(CtD.NWin);
   }

   pB->IsMon = Monotonous(pB->G, CtD.NDim);
}

/*---------------------------------------------------------------------------*/
// Eval F
VOID EvalFInB(PBOX pB, ConstData &CtD, INT &NEval, PCHARCt Color)
{
   fEvalIA(CtD.NFunction, pB->pX, pB->F);
   NEval++;

   if (CtD.Draw)
   {
      DrawBox(pB, CtD, false, ""); // Do not fill.
      if (CtD.Draw == 2)
         DrawWait(CtD.NWin);
   }
}

/*---------------------------------------------------------------------------*/
void EvalBox(PBOX pB, ConstData &CtD, iTDAT &iTDat, PINT pCounters)
{
   EvalFGInB(pB, CtD, pCounters[CNEvalFG]);
   if (pB->IsMon)
      pCounters[CNMonB]++;

   if (GE(pB->F.lower(), iTDat.pBIncumb->F.upper()))
      return;

   switch (CtD.IncType)
   {
   case IncTypeIA: // we always evaluate F and G on X but centre
      EvalBoxCentre(pB, CtD, iTDat, pCounters);
      break;
   case IncTypeCFcBox:
      CFcBox(pB, CtD, iTDat, pCounters);
      break;
   case IncTypeCFbBox:
      CFbBox(pB, CtD, iTDat, pCounters);
      break;
   default:
      fprintf(stderr, "EvalBox: this point ca not be reached.\n");
      exit(1);
      break;
   }
}
/*---------------------------------------------------------------------------*/
PBOX InitBox(ConstData &CtD, iTDAT &iTDat, PINT pCounters)
{
   PBOX pB;

   pB = GetMemBox(CtD.NDim);
   pB->NBox = GetNewNBox();

   pB->pX = CtD.InititvV;
   SizeBox(pB, CtD.NDim);

   return pB;
}

/*---------------------------------------------------------------------------*/
PBOX FreeBox(PBOX pB, ConstData &CtD, const BOOL Fill, PCHARCt Color)
{
   if (pB == NULL)
   {
      fputs("FreeBox:null box pointer.", stderr);
      exit(1);
   }

   if (CtD.Draw)
   {
      DelBox(CtD.NWin, pB->NBox);
      if (Fill)
         DrawBox(pB, CtD, Fill, Color);
   }

   pB->G.resize(0);
   pB->pX.resize(0);
   free((void *)pB);
   return NULL;
}

/*---------------------------------------------------------------------------*/
void DivideBox(PBOX &pB, PBOX &pB1, PBOX &pB2, ConstData &CtD, iTDAT &iTDat,
               PINT pCounters)
{
   int NDim = CtD.NDim;
   int CoorToDivide = -1;
   double Middle;
   if (pB == NULL)
   {
      fputs("DivideBox:null box pointer.", stderr);
      exit(1);
   }

   for (int i = 0; i < NDim; i++)
   {
      //  if (pB->NBox==36629854)
      //   fprintf(stderr, "DivideBox: wid(pb->X[%d]=%lf.\n",i,width(pB->pX[i]));
      if (EQ(width(pB->pX[i]), pB->Size))
         CoorToDivide = i;
   }

   if (CoorToDivide == -1)
   {
      fprintf(stderr, "DivideBox: CoorToDivide not found.\n");
      fprintf(stderr, "DivideBox: NBox=%d"
                      ", pB->Size=%lf.\n",
              pB->NBox, pB->Size);
      raise(SIGINT); // signal an interrupt to stop gdb and see bt
      exit(1);
   }
   pB1 = GetMemBox(CtD.NDim);
   pB1->NBox = GetNewNBox();
   pB1->pX = pB->pX;

   pB2 = GetMemBox(CtD.NDim);
   pB2->NBox = GetNewNBox();
   pB2->pX = pB->pX;

   Middle = mid(pB->pX[CoorToDivide]);
   pB1->pX[CoorToDivide].upper() = Middle;
   SizeBox(pB1, CtD.NDim);
   pB2->pX[CoorToDivide].lower() = Middle;
   SizeBox(pB2, CtD.NDim);

   FreeBox(pB, CtD, false, "");
   pB = NULL;
}

/*---------------------------------------------------------------------------*/
bool ReduceBox(PBOX pB, ConstData &CtD)
{
   int NDim = CtD.NDim;
   bool Reduce = false;

   for (int i = 0; i < NDim; i++)
      if (!zero_in(pB->G[i]))
      {
         if (pB->G[i].upper() < 0.0 && pB->pX[i].upper() == CtD.InititvV[i].upper()) // negative -> to right
         {
            pB->pX[i].lower() = pB->pX[i].upper();
            Reduce = true;
         }
         if (pB->G[i].lower() > 0.0 && pB->pX[i].lower() == CtD.InititvV[i].lower()) // positive -> to left
         {
            pB->pX[i].upper() = pB->pX[i].lower();
            Reduce = true;
         }
      }
   if (Reduce)
      SizeBox(pB, CtD.NDim);
   return Reduce;
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
