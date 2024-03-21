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

void GetParams   (int argc, PPCHAR argv, ConstData & CtD, double & Alpha);
void PrintParams (FILE * FOut, ConstData & CtD, double Alpha);

#endif /*__INPUTOUTPUT__*/                  
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/                
