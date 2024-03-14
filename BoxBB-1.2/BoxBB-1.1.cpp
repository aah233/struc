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
#define PRINT 0

using namespace std;

/*---------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
	int i;
	double Alpha;  // Termination criterion diam([LB,incumb])<=Alpha.
	ConstData CtD; // ConstantData. See utils.h
	std::vector<BOX *> boxTemporales;
	// numero de veces que se ha mejorado

	// std::cout.precision(17);
	setlocale(LC_NUMERIC, "en_US.UTF-8"); // Use thousands separators
	cout.imbue(std::locale("en_US.UTF-8"));
	cerr.imbue(std::locale("en_US.UTF-8"));

	// Este
	GetParams(argc, argv, CtD, Alpha); // Cogemos los paremtro de entrada de la terminal
	PrintParams(stderr, CtD, Alpha);   // los imprime para ver que estan bien
	// Create a new Box with the paramns
	BOX *pB = new BOX(CtD.InitBox);
	// while dont have a better aplha
	while (pB != NULL && (&pB->FX.upper() - &pB->FX.lower() > Alpha)) // alpha parametro de entrada
	{
		// Inicializar 2 divisores de caja
		BOX *pBoXG1 = new BOX(*pB); // Crear un nuevo BOX como copia de B
		BOX *pBoXG2 = new BOX(*pB); // Crear otro BOX como copia de B
		std::cout << "Box B1 antes de dividir: " << *pBoXG1 << std::endl;
		std::cout << "Box B1 antes de dividir: " << *pBoXG2 << std::endl;

		pB->Divides(*pBoXG1, *pBoXG2); // Divide B en BoXG1 y BoXG2
		std::cout << "Box B1 despues de dividir: " << *pBoXG1 << std::endl;
		std::cout << "Box B1 despues de dividir: " << *pBoXG2 << std::endl;
		boxTemporales.push_back(pBoXG1); // No olvides liberar el último B si ya no es necesarioAlmacenar punteros en el vector
		boxTemporales.push_back(pBoXG2);
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
