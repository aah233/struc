#include <math.h>
#include <time.h>
#include <cfloat>   // DBL_MAX
#include <locale.h> // for thousands comma
#include <iostream>
#include <fstream>
#include <math.h>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>
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
// https://www.boost.org/doc/libs/1_77_0/libs/multi_index/doc/index.html
// https://cs.brown.edu/~jwicks/boost/libs/multi_index/doc/tutorial.html

//ESTE ES EL QUE NO EVALUA LAS CAJAS DEL LESS 
#define PRINT 0

using namespace std;
using namespace boost::multi_index;

/* Structure for Box */
struct Box
{
    kv::interval<double> F;
    PBOX pB;

    // Constructor
    Box(const kv::interval<double> &F, PBOX pB) : F(F), pB(pB) {}
};

// Tags for indexing
struct by_F
{
};

// Define Boost MultiIndex container
typedef multi_index_container<
    Box,
    indexed_by<
        ordered_non_unique<
            tag<by_F>, member<Box, kv::interval<double>, &Box::F>>>>
    BoxContainer;

// Define a container for boxes with F < incumbent's F
typedef multi_index_container<
    Box,
    indexed_by<
        ordered_non_unique<
            tag<by_F>, member<Box, kv::interval<double>, &Box::F>>>>
    LesserBoxContainer;

/*---------------------------------------------------------------------------*/
PBOX ProcessBox(PBOX pB, double Epsilon, ConstData &CtD, BoxContainer &pbtbWork, BoxContainer &pbtbEnd, LesserBoxContainer &lesserBoxes, int *pCounters, iTDAT &iTDat)
{
    EvalBox(pB, CtD, iTDat, pCounters);
    pB = TestBox(pB, CtD, iTDat, pCounters);
    if (pB != nullptr)
    {
        if (pB->Size <= Epsilon)
        {
            if (CtD.Draw)
                DrawBox(pB, CtD, true, "#c02020"); // Fill=true
            pbtbEnd.insert(Box(pB->F, pB));
            pCounters[CinsertE]++;
        }
        else
        {
            if (pB->F.upper() < iTDat.pBIncumb->F.upper())
            {
                lesserBoxes.insert(Box(pB->F, pB));
            }
            else
            {
                pbtbWork.insert(Box(pB->F, pB));
            }
            pCounters[CinsertW]++;
        }
    }
    return nullptr;
}

/*---------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    int i;
    double Epsilon; // Termination criterion w(X)<=Epsilon.
    ConstData CtD;  // ConstantData. See utils.h
    PBOX pB = NULL; // Pointer to a box.
    PBOX pB1 = NULL;
    PBOX pB2 = NULL;
    iTDAT iTDat;              // Temporal interval data
    int pCounters[NCounters]; // See defines.h.
    int PrevNUpInc;           // The number of N.Incumb impro. before an iteration.

    // std::cout.precision(17);
    setlocale(LC_NUMERIC, "en_US.UTF-8"); // Use thousands separators
    cout.imbue(std::locale("en_US.UTF-8"));
    cerr.imbue(std::locale("en_US.UTF-8"));
    std::cout.precision(30);

    // Initiate the counters.
    for (i = 0; i < NCounters; i++)
        pCounters[i] = 0;

    GetParams(argc, argv, CtD, Epsilon);
    PrintParams(stderr, CtD, Epsilon);
    int NDim = CtD.NDim;

    BoxContainer pbtbWork;
    BoxContainer pbtbEnd;
    LesserBoxContainer lesserBoxes;

    // Two temporal boxes and one rvector to avoid memory calls
    iTDat.pBPoint = GetMemBox(NDim);
    iTDat.pBIncumb = GetMemBox(NDim);
    iTDat.pBIncumb->F.upper() = DBL_MAX;
    iTDat.pBIncumb->F.lower() = DBL_MAX;
    iTDat.rVector.resize(NDim);

    // Init first Box
    pB = InitBox(CtD, iTDat, pCounters);
    pB = ProcessBox(pB, Epsilon, CtD, pbtbWork, pbtbEnd, lesserBoxes, pCounters, iTDat);

    PrevNUpInc = pCounters[CNIncumb]; // N. Incumbent Impro.

    while (!pbtbWork.empty())
    {
        auto it = pbtbWork.get<by_F>().begin();
        pB = it->pB;
        pbtbWork.get<by_F>().erase(it);
        pCounters[CNIters]++; // N. Iterations

        if (CtD.NCheckAVL > 0 && pCounters[CNIters] % CtD.NCheckAVL == 1)
        {
            // The order check is not required with Boost.MultiIndex as it maintains order.
        }

#if (PRINT == 1)
        fprintf(stderr, "Main: Iter=%d\n", pCounters[CNIters]);
#endif
        DivideBox(pB, pB1, pB2, CtD, iTDat, pCounters);

        pB1 = ProcessBox(pB1, Epsilon, CtD, pbtbWork, pbtbEnd, lesserBoxes, pCounters, iTDat);
        pB2 = ProcessBox(pB2, Epsilon, CtD, pbtbWork, pbtbEnd, lesserBoxes, pCounters, iTDat);

        // CutOff test if the incumbent was updated
        if (PrevNUpInc < pCounters[CNIncumb]) //<N. Incumbent Impro
        {
            PrevNUpInc = pCounters[CNIncumb]; //=N. Incumbent Impro

            auto &index = pbtbWork.get<by_F>();
            for (auto it = index.begin(); it != index.end();)
            {
                if (it->F > iTDat.pBIncumb->F)
                    it = index.erase(it);
                else
                    ++it;
            }

            auto &indexEnd = pbtbEnd.get<by_F>();
            for (auto it = indexEnd.begin(); it != indexEnd.end();)
            {
                if (it->F > iTDat.pBIncumb->F)
                    it = indexEnd.erase(it);
                else
                    ++it;
            }

            auto &indexLesser = lesserBoxes.get<by_F>();
            for (auto it = indexLesser.begin(); it != indexLesser.end();)
            {
                if (it->F > iTDat.pBIncumb->F)
                    it = indexLesser.erase(it);
                else
                    ++it;
            }
        }
    } // End While

    /*
       cerr << "     NElem in work AVL tree = " << pbtbWork->NElem << endl;
       cerr << "Max. NElem in work AVL tree = " << pbtbWork->MaxNElem << endl;
       cerr << "     NElem in end  AVL tree = " << pbtbEnd->NElem << endl;
       cerr << "Max. NElem in end  AVL tree = " << pbtbEnd->MaxNElem << endl;
    */
    cerr << "Counters-------------------------------------------------------" << endl;
    for (i = 0; i < NCounters; i++)
        cerr << CounterDesc[i] << pCounters[i] << endl;

    cerr << "------------------------------------------------------------" << endl;
    cerr << "Min =        " << CtD.Min << endl;
    cerr << "Incumbent value  - Min = " << iTDat.pBIncumb->F.upper() - CtD.Min << endl;
    cerr << "Incumbent value:";
    fprintf(stderr, "[%30.30f,%30.30f]\n", iTDat.pBIncumb->F.lower(), iTDat.pBIncumb->F.upper());
    cerr << "Incumbent value width =" << width(iTDat.pBIncumb->F) << endl;
    cerr << "Incumbent at:";
    cerr << iTDat.pBIncumb->pX << endl;
    cerr << "Incumbent at:";
    PrintitvV(stderr, iTDat.pBIncumb->pX, NDim);

    cerr << "===============================================================" << endl;

    // First Labels
    // N.boxes Eval.
    cerr << "& "
         << "CNEvalFG  ";
    cerr << "& "
         << "CNEvalLB  ";
    cerr << "& "
         << "CNEvalP   ";
    cerr << "& "
         << "CNSucLBF  " << endl;

    cerr << setw(10) << right << pCounters[CNEvalFG] << " & ";
    cerr << setw(10) << right << pCounters[CNEvalLB] << " & ";
    cerr << setw(10) << right << pCounters[CNEvalP] << " & ";
    cerr << setw(10) << right << pCounters[CNSucLbF] << " & " << endl;
    cerr << setw(10) << right << " Eliminaciones: " << pCounters[CinsertW] - pCounters[CNIters];
    //---------------------------------
    if (CtD.Draw)
        CtD.XLim.resize(0);

    CtD.InititvV.resize(0);

    CtD.Draw = False;

    iTDat.pBIncumb = FreeBox(iTDat.pBIncumb, CtD, false, "");
    iTDat.pBPoint = FreeBox(iTDat.pBPoint, CtD, false, "");
    iTDat.rVector.resize(0);

    return 0;
}
