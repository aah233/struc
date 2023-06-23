/***************************************************************************
                          Problems.h  -  description
                             -------------------
    begin                : Nov 2000
    copyright            : (C) 2000 by L.G. Casado
    email                : leo@ace.ual.es
    
 ***************************************************************************
Purpose: Access to the automatic differentiation provided by C++ Toolbox for
	Verified Computing which was modified by M. Markot to use Profil soft.

 fEvalProblem(): Compute the value of the function NProblem.
 fgEvalProblem(): Compute the value of the function NProblem and first 
 	derivative value. 

*******************************************************************************/
#ifndef __PROBLEMS__
#define __PROBLEMS__

/*----------------------------------------------------------------------------*/
void fEvalProblem  (int NProblem, PBOX pb, int & NEvalF);
void fgEvalProblem (int NProblem, PBOX pb, int & NEvalG);

#endif /*__PROBLEMS__*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
