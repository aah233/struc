/***************************************************************************
                          Functions.hpp  -  description
                             -------------------
    begin                : Nov 2000
    copyright            : (C) 2000 by L.G. Casado
    email                : leo@ace.ual.es
    
 ***************************************************************************
Purpose: Access to the automatic differentiation provided by C++ Toolbox for
	Verified Computing which was modified by M. Markot to use Profil soft.

 NamefProblem() : Returns the name of the function.
 DimfProblem()  : Returns the dimension of the function.
 ListFunctions(): Lists all functions.
 itvVAdifF()    : Evalautes interval vector in f with Automatic Differentation.
 LbAffF()       : returns the lower bound of f with Affine Arithmetic  

*******************************************************************************/
#ifndef __FUNCTIONS__
#define __FUNCTIONS__

/*----------------------------------------------------------------------------*/
PCHARCt NamefProblem  (const int NFunction);
int     DimfProblem   (const int NFunction);
void    ListFunctions (FILE * FOut);
void    fEvalIA       (const int NFunction, const itvV & X, itv &F);
void    fgEvalIA      (const int NFunction, const itvV & X, itv &F, itvV & G);
bool    Monotonous    (const itvV &G, const int NDim);


#endif /*__FUNCTIONS__*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
