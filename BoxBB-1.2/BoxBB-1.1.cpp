#include <math.h>
#include <time.h>
#include <cfloat>	//DBL_MAX
#include <locale.h> //for milliards comma
#include <iostream>
#include <fstream>
#include <math.h>
#include "defines.h"
#include "argshand.h"
#include "utils.h"
#include "Functions.hpp"
#include "InputOutput.hpp"
#include "Box.hpp"
#include "test.hpp"
#include <map>
#define PRINT 0

using namespace std;

/*---------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{

	int i;
	double Alpha;  // Termination criterion diam([LB,incumb])<=Alpha.
	ConstData CtD; // ConstantData. See utils.h
	std::vector<BOX *> boxTemporales;
	bool result;
	int pCounters[NCounters]; // numero de veces que se ha mejorado
	int PrevNUpInc;			  // this variable save the incumben
	iTDAT iTDat;

	// std::cout.precision(17);
	setlocale(LC_NUMERIC, "en_US.UTF-8"); // Use thousands separators
	cout.imbue(std::locale("en_US.UTF-8"));
	cerr.imbue(std::locale("en_US.UTF-8"));

	// Init counters
	for (i = 0; i < NCounters; i++)
		pCounters[i] = 0;

	// Este
	GetParams(argc, argv, CtD, Alpha); // Cogemos los paremtro de entrada de la terminal
	PrintParams(stderr, CtD, Alpha);   // los imprime para ver que estan bien

	int NDim = CtD.NDim; // number of dimensions

	// Create a new Box with the paramns
	BOX *pB = new BOX(CtD.InitBox);
	// generate itad, in this pB we gonna save the initial box
	iTDat.pBPoint = pB;
	iTDat.pBIncumb = pB;
	iTDat.pBIncumb->F.upper() = DBL_MAX;
	iTDat.pBIncumb->F.lower() = DBL_MAX;
	iTDat.rVector.resize(NDim);
	// Eval de first Box
	fgEvalIA(CtD.NFunction, pB->X, pB->FX, pB->GX);
	//?? Y En el caso de que la rechace que pasa siendo la primera, creo que nunca sucederia no?

	//   while (pB != NULL && (&pB->FX.upper() - &pB->FX.lower() > Alpha))
	while (pB->Width > Alpha)
	{
		// Inicializar 2 divisores de caja
		BOX *pBoXG1 = new BOX(*pB); // Crear un nuevo BOX como copia de B
		BOX *pBoXG2 = new BOX(*pB); // Crear otro BOX como copia de B

		pB->Divides(*pBoXG1, *pBoXG2); // Divide B en BoXG1 y BoXG2
		fgEvalIA(CtD.NFunction, pBoXG1->X, pBoXG1->FX, pBoXG1->GX);
		fgEvalIA(CtD.NFunction, pBoXG2->X, pBoXG2->FX, pBoXG2->GX);
		// no se muestra si no tiene el tcl
		pB->DrawBox(CtD, true, "#00e000");
		// There we gonna pass the test, the test return a PBOX to, we gonna pass now, because the have been evaluated
		result = TestBox(pBoXG1, CtD, pCounters, pB);
		// print resultado
		std::cout << result << std::endl;
		//   ELIMINO LA CAJA PERDEDORA
		//     pinto la que selecciono nada más
		//      Evaluar cual de las dos es menor Flower
		boxTemporales.push_back(pBoXG1); // No olvides liberar el último B si ya no es necesarioAlmacenar punteros en el vector
		boxTemporales.push_back(pBoXG2);
		// pintarlas aqui
		pBoXG1 = nullptr;
		pBoXG2 = nullptr;
		delete pB; // Destruir B explícitamente
		pB = nullptr;
		pB = boxTemporales[boxTemporales.size() - 1];
		boxTemporales.pop_back(); // Liberar el último B creado
		i++;
	}

	BOX *pBTemp;
	// Recorrer todos los elementos y borrar su contenido
	for (size_t i = 0; i < boxTemporales.size(); i++)
	{
		pBTemp = boxTemporales[i];
		delete pBTemp;
	}
	boxTemporales.clear();

	// Liberar el ultimo B creado
	delete pB;

	return 0;
}
