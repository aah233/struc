/***************************************************************************
                          BoxBB-1.0.cpp  -  description
                             -------------------
    begin                : April 2023
    copyright            : (C) 2023 by L.G. Casado
    email                : leo@ual.es
 ***************************************************************************/
#include <math.h>
#include <time.h>
#include <cfloat>   //DBL_MAX
#include <locale.h> //for milliards comma
#include <set>
#include <iostream>
#include <fstream>
#include <math.h>
#include "defines.h"
#include "argshand.h"
#include "getmem.h"
#include "utils.h"
#include "iutils.hpp"
#include "Functions.hpp"
#include "box.hpp"
#include "listbox.h"
#include "btbox.h"
#include "InputOutput.hpp"
#include "test.hpp"
#include "avlTree.hpp"

#define PRINT 0

using namespace std;

struct CompareBoxes
{
   bool operator()(const PBOX &lhs, const PBOX &rhs) const
   {
      return lhs->F < rhs->F;
   }
};

/*---------------------------------------------------------------------------*/
PBOX ProcessBox(PBOX pB, double Epsilon, ConstData &CtD, multiset<PBOX, CompareBoxes> &msWork, multiset<PBOX, CompareBoxes> &msEnd, int *pCounters, iTDAT &iTDat)
{
   EvalBox(pB, CtD, iTDat, pCounters);
   pB = TestBox(pB, CtD, iTDat, pCounters);
   if (pB != nullptr)
   {
      if (pB->Size <= Epsilon)
      {
         if (CtD.Draw)
            DrawBox(pB, CtD, true, "#c02020"); // Fill=true
         msEnd.insert(pB);
         pCounters[CinsertE]++;
      }
      else
      {
         msWork.insert(pB);
         pCounters[CinsertW]++;
      }
   }
   return nullptr;
}

/*---------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
   int i;
   double Epsilon;    // Termination criterion w(X) <= Epsilon.
   ConstData CtD;     // ConstantData. See utils.h
   PBOX pB = nullptr; // Pointer to a box.
   PBOX pB1 = nullptr;
   PBOX pB2 = nullptr;
   iTDAT iTDat;              // Temporal interval data
   int pCounters[NCounters]; // See defines.h.
   int PrevNUpInc;           // The number of N. Incumbent improvements before an iteration.

   setlocale(LC_NUMERIC, "en_US.UTF-8"); // Use thousands separators
   cout.imbue(locale("en_US.UTF-8"));
   cerr.imbue(locale("en_US.UTF-8"));
   cout.precision(30);

   // Initialize the counters.
   for (i = 0; i < NCounters; i++)
      pCounters[i] = 0;

   GetParams(argc, argv, CtD, Epsilon);
   PrintParams(stderr, CtD, Epsilon);
   int NDim = CtD.NDim;

   multiset<PBOX, CompareBoxes> msWork;
   multiset<PBOX, CompareBoxes> msEnd;

   // Two temporal boxes and one rvector to avoid memory calls
   iTDat.pBPoint = GetMemBox(NDim);
   iTDat.pBIncumb = GetMemBox(NDim);
   iTDat.pBIncumb->F.upper() = DBL_MAX;
   iTDat.pBIncumb->F.lower() = DBL_MAX;
   iTDat.rVector.resize(NDim);

   // Initialize the first Box
   pB = InitBox(CtD, iTDat, pCounters);
   pB = ProcessBox(pB, Epsilon, CtD, msWork, msEnd, pCounters, iTDat);

   PrevNUpInc = pCounters[CNIncumb]; // N. Incumbent Improvements

   while (!msWork.empty())
   {
      pB = *msWork.begin();
      msWork.erase(msWork.begin());
      pCounters[CNIters]++; // N. Iterations

      if (CtD.NCheckAVL > 0 && pCounters[CNIters] % CtD.NCheckAVL == 1)
      {
      }

#if (PRINT == 1)
      fprintf(stderr, "Main: Iter=%d\n", pCounters[CNIters]);
#endif
      DivideBox(pB, pB1, pB2, CtD, iTDat, pCounters);

      pB1 = ProcessBox(pB1, Epsilon, CtD, msWork, msEnd, pCounters, iTDat);
      pB2 = ProcessBox(pB2, Epsilon, CtD, msWork, msEnd, pCounters, iTDat);

      // CutOff test if the incumbent was updated
      if (PrevNUpInc < pCounters[CNIncumb])
      {
         PrevNUpInc = pCounters[CNIncumb];
         for (auto it = msWork.begin(); it != msWork.end();)
         {
            if ((*it)->F > iTDat.pBIncumb->F)
               it = msWork.erase(it);
            else
               ++it;
         }
         for (auto it = msEnd.begin(); it != msEnd.end();)
         {
            if ((*it)->F > iTDat.pBIncumb->F)
               it = msEnd.erase(it);
            else
               ++it;
         }
      }
   }

   cerr << "Counters-------------------------------------------------------" << endl;
   for (i = 0; i < NCounters; i++)
      cerr << CounterDesc[i] << pCounters[i] << endl;

   cerr << "------------------------------------------------------------" << endl;
   cerr << "Min =        " << CtD.Min << endl;
   cerr << "Incumbent value  - Min = " << iTDat.pBIncumb->F.upper() - CtD.Min << endl;
   cerr << "Incumbent value:";
   fprintf(stderr, "[%30.30f,%30.30f]\n", iTDat.pBIncumb->F.lower(), iTDat.pBIncumb->F.upper());
   cerr << "Incumbent value width =" << width(iTDat.pBIncumb->F) << endl;
   cerr << "Incumbent at:" << iTDat.pBIncumb->pX << endl;
   cerr << "Incumbent at:";
   PrintitvV(stderr, iTDat.pBIncumb->pX, NDim);

   cerr << "===============================================================" << endl;

   // First Labels
   cerr << "& " << "CNEvalFG  ";
   cerr << "& " << "CNEvalLB  ";
   cerr << "& " << "CNEvalP   ";
   cerr << "& " << "CNSucLBF  " << endl;

   cerr << setw(10) << right << pCounters[CNEvalFG] << " & ";
   cerr << setw(10) << right << pCounters[CNEvalLB] << " & ";
   cerr << setw(10) << right << pCounters[CNEvalP] << " & ";
   cerr << setw(10) << right << pCounters[CNSucLbF] << " & " << endl;

   //---------------------------------
   if (CtD.Draw)
      CtD.XLim.resize(0);

   CtD.InititvV.resize(0);

   CtD.Draw = false;

   iTDat.pBIncumb = FreeBox(iTDat.pBIncumb, CtD, false, "");
   iTDat.pBPoint = FreeBox(iTDat.pBPoint, CtD, false, "");
   iTDat.rVector.resize(0);

   return 0;
}
