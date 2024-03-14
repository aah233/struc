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
	double Alpha;  // Termination criterion diam([LB,incumb])<=Alpha.
	ConstData CtD; // ConstantData. See utils.h
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

	return 0;
}
