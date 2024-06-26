/***************************************************************************
                          InputOutput.h  -  description
                             -------------------
    begin                : Nov 2020
    copyright            : (C) 2020 by L.G. Casado
    email                : leo@ual.es
    
 ***************************************************************************
 Purpose: Routines to generate outputs and to get the imput parameters.

	OutPutStat(): Generate a report with the figures of the execution. It can
			be stored in a file or presented in the screen.
	GetParams(): Get the input parameters and initialize some variables,
			depending on them.	

*******************************************************************************/

#ifndef __INPUTOUTPUT__
#define __INPUTOUTPUT__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h>
#include <climits>
#include "defines.h"
#include "getmem.h"
#include "argshand.h"
#include "utils.h"
#include <kv/affine.hpp>
#include "Functions.hpp"
#include "box.hpp"

void GetParams   (int argc, PPCHAR argv, ConstData & CtD, double & Epsilon);
void PrintParams (FILE * FOut, ConstData & CtD, double Epsilon);

#endif /*__INPUTOUTPUT__*/                  
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/                
