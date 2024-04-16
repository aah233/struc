#include <math.h>
#include <time.h>
#include <cfloat>	//DBL_MAX
#include <locale.h> //for milliards comma
#include <iostream>
#include <fstream>
#include <math.h>
#include <cstdlib>
#include "defines.h"
#include "argshand.h"
#include "utils.h"
#include "iutils.hpp"
#include "Functions.hpp"
#include "Box.hpp"
#include "itdat.h"
#include "InputOutput.hpp"
#include "test.hpp"

#define PRINT 0

using namespace std;

/*---------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{

	double Alpha;			  // Termination criterion diam([LB,incumb])<=Alpha.
	ConstData CtD;			  // ConstantData. See utils.h
	int pCounters[NCounters]; // numero de veces que se ha mejorado
	// int PrevNUpInc;			  // this variable save the incumben
	iTDAT iTDat;
	bool result1, result2;

	// std::cout.precision(17);
	setlocale(LC_NUMERIC, "en_US.UTF-8"); // Use thousands separators
	cout.imbue(std::locale("en_US.UTF-8"));
	cerr.imbue(std::locale("en_US.UTF-8"));

	// Init counters
	for (int i = 0; i < NCounters; i++)
		pCounters[i] = 0;

	// Este
	GetParams(argc, argv, CtD, Alpha); // Cogemos los paremtro de entrada de la terminal
	PrintParams(stderr, CtD, Alpha);   // los imprime para ver que estan bien

	int NDim = CtD.NDim; // number of dimensions

	// Create a new Box with the paramns
	BOX *pB = new BOX(CtD.InitBox);
	// generate itad, in this pB we gonna save the initial box
	iTDat.pBPoint = new BOX(CtD.NDim);
	iTDat.pBIncumb = new BOX(CtD.NDim);
	iTDat.pBIncumb->FX.upper() = DBL_MAX;
	iTDat.pBIncumb->FX.lower() = DBL_MAX;
	iTDat.rVector.resize(NDim);

	iTDat.rVector.resize(NDim);
	// Eval de first Box
	fgEvalIA(CtD.NFunction, pB->X, pB->FX, pB->GX);
	pB->IsMon = Monotonous(pB->GX, NDim);
	if (TestBox(pB, CtD, pCounters, iTDat))
	{
		// stop the program and go out
		std::cout << "La primera caja no cumple con las condiciones." << std::endl;

		exit(EXIT_FAILURE);
	}

	//   while (pB != NULL && (&pB->FX.upper() - &pB->FX.lower() > Alpha))
	while (pB != nullptr && pB->Width > Alpha)
	{
		//  Inicializar 2 divisores de caja
		BOX *pBoXG1 = new BOX(*pB); // Crear un nuevo BOX como copia de B
		BOX *pBoXG2 = new BOX(*pB); // Crear otro BOX como copia de B

		pB->Divides(*pBoXG1, *pBoXG2); // Divide B en BoXG1 y BoXG2

		// teste de EvalIA
		fgEvalIA(CtD.NFunction, pBoXG1->X, pBoXG1->FX, pBoXG1->GX);
		fgEvalIA(CtD.NFunction, pBoXG2->X, pBoXG2->FX, pBoXG2->GX);

		if (CtD.Draw)
		{
			pBoXG1->DrawBox(CtD, false, ""); // Not fill
			if (CtD.Draw == 2)
				DrawWait(CtD.NWin);

			pBoXG2->DrawBox(CtD, false, "");
			if (CtD.Draw == 2)
				DrawWait(CtD.NWin);
		}
		// Eval Monotonous in the two Boxes
		pBoXG1->IsMon = Monotonous(pBoXG1->GX, NDim);
		pBoXG2->IsMon = Monotonous(pBoXG2->GX, NDim);

		// TestBox
		result1 = TestBox(pBoXG1, CtD, pCounters, iTDat);
		result2 = TestBox(pBoXG2, CtD, pCounters, iTDat);

		// EVALUAR EL CENTRO DE LA CAJA PARA MEJORAR EL INCUMBEN, SOLO SI HA PASADO LOS TEST
		// Box.cpp EvalBox
		// Cuando rechazo por monotonia hay que sumar el contador
		if (result1 == 0 && result2 == 0)
		{
			std::cerr << "En la evaluacion :" << pCounters[CNIters] << " no se descarta ninguna" << std::endl;
			// Comparativa de sus F
			if (pBoXG1->FX.lower() < pBoXG2->FX.lower())
			{
				// pBoXG1 es mejor
				delete pB;
				delete pBoXG2;
				pB = pBoXG1;
			}
			else
			{
				// pBoXG2 es mejor
				delete pB;
				delete pBoXG1;
				pB = pBoXG2;
			}
		}
		else if (result1 == 0 && result2 == 1)
		{
			std::cerr << "En la evaluacion :" << pCounters[CNIters] << " Ganadora 1" << std::endl;
			// pBoXG1 es mejor
			delete pB;
			delete pBoXG2;
			pB = pBoXG1;
		}
		else if (result2 == 0 && result1 == 1)
		{
			std::cerr << "En la evaluacion :" << pCounters[CNIters] << " Ganadora 2" << std::endl;
			// pBoXG2 es mejor
			delete pB;
			delete pBoXG1;
			pB = pBoXG2;
		}
		else
		{
			std::cerr << "En la evaluacion :" << pCounters[CNIters] << " Ninguna de las dos, procedemos a null" << std::endl;
			delete pB;
			delete pBoXG1;
			delete pBoXG2;
			pB = nullptr;
		}

		// pintarlas aqui
		pBoXG1 = nullptr;
		pBoXG2 = nullptr;
		pCounters[CNIters]++;
		std::cerr << "Antes del eval" << std::endl;
		if (pB != nullptr)
			EvalBoxCentre(pB, CtD, iTDat, pCounters);
		std::cerr << "Despues del eval" << std::endl;
	}

	// Liberar el ultimo B creado
	delete pB;
	//	delete pBoXG1;
	//	delete pBoXG2;

	return 0;
}
