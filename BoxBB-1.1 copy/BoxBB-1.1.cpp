/***************************************************************************
                          BoxBB-1.0.cpp  -  description
                             -------------------
    begin                : April 2023
    copyright            : (C) 2023 by L.G. Casado
    email                : leo@ual.es
 ***************************************************************************/

#include <math.h>
#include <time.h>
#include <cfloat>	//DBL_MAX
#include <locale.h>	//for milliards comma
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

#define PRINT 0

using namespace std;

/*---------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
 int i;
 double		Alpha;		//Termination criterion diam([LB,incumb])<=Alpha.
 PBTB		pbtb=NULL;	//AVL Tree of boxes.
 PBOX		pB =NULL;	//Pointer to a box. esta es la caja que se divide 
 PBOX		pB1=NULL; //esta es la caja que genera al dividir 
 PBOX		pB2=NULL; // segunda caja al dividir 
 int pCounters[NCounters];		//See defines.h.
 int PrevNUpInc;		//The number of N.Incumb impro. before an iteration. el mejor valor que se tiene y este es el 
 // numero de veces que se ha mejorado 
  
 //std::cout.precision(17);
 setlocale(LC_NUMERIC,  "en_US.UTF-8"); // Use thousands separators
 cout.imbue(std::locale("en_US.UTF-8"));
 cerr.imbue(std::locale("en_US.UTF-8"));

 //Initiate the counters.
 for(i=0;i<NCounters;i++)
    pCounters[i]=0;
 
 GetParams (argc,argv,CtD,Alpha); // Cogemos los paremtro de entrada de la terminal 
 PrintParams(stderr,CtD,Alpha); // los imprime para ver que estan bien 
 
 
 pbtb=NewBTB(pbtb);  //creamos un nuevo de arbol binario de cajas a null 

 //Init first Box
 pB=InitBox(CtD,iTDat,pCounters); // caja inicial 
 
 #if (PRINT==1)
 PrintBox(stderr,pB,NDim);
 //exit(1);
 #endif

 cerr<<"LB(f(S1))in["<< pB->F.lower()<<",";
 cerr				  << iTDat.pBIncumb->F.upper() << "]" << endl;
 pB=TestBox(pB,CtD,pbtb,pCounters,iTDat); //comprueba si hay que rechazarla o si se alamcena en el arbol binario 
 if (pB==NULL && pbtb->NElem>0)  // si esta nulo y hay en el arbol binario 
     ExtractSmallerBTB(pbtb,&pB,CtD,False,"");  // obtiene una caja del arbol 


 PrevNUpInc=pCounters[CNIncumb]; //N. Incumbent Impro. 
 #if (PRINT==1)
 cerr << "Incumbent =" << iTDat.pBIncumb->F << endl;
 #endif
 while (pB!=NULL && (iTDat.pBIncumb->F.upper() - pB->F.lower() > Alpha)) //alpha parametro de entrada 
 	   {
		pCounters[CNIters]++; //N. Ierations
		 #if (PRINT==1)
		 fprintf(stderr,"Iter=%d.\n",pCounters[CNIters]);
		 cerr << "Incumbent=" << iTDat.pBIncumb->F << endl;
		 if (pCounters[CNIters] > 2)
			exit(1);
		 #endif
		/*
			* Divide the box in two. The first one inherits the data structure	
		*/
		DivideBox (pB,pB1,pB2,CtD,iTDat,pCounters); //este cambia 
		#if (PRINT==1)
 		PrintBox(stderr,pB1,NDim);
 		PrintBox(stderr,pB2,NDim);
 		#endif
		pB1=TestBox(pB1,CtD,pbtb,pCounters,iTDat); //cambia ?¿ aqui elimina o inserta, claro la hace dentro y por lo tanto habria que ponerlo fuera 
		pB2=TestBox(pB2,CtD,pbtb,pCounters,iTDat); //cambia 

	   //CutOff test if the incumbent was updated  
	   if (PrevNUpInc<pCounters[CNIncumb]) //<N. Incumbent Impro
		  {
		   PrevNUpInc=pCounters[CNIncumb]; //=N. Incumbent Impro
		   CutOffTest(pbtb,CtD,iTDat); //ya generico 
		  }
	   
	   //Get new box from BTB
	   if ( pbtb->NElem>0 )
		  ExtractSmallerBTB(pbtb,&pB,CtD,False,""); // ya generico 
	   else
		  {
		   fprintf(stderr,"BoxBB: Empty pbtb.\n");
		   cerr<<"Incumbent = " << iTDat.pBIncumb->F.upper() << endl; 
		   fflush(stderr); 
		   exit(1);
		  }
	  } //End While

//hasta aqui 
 cerr <<"Counters-------------------------------------------------------"<<endl;
 for (i=0;i<NCounters;i++)
     cerr<< CounterDesc[i] << pCounters[i]	<< endl;

 #if (PRINT==1)
 fprintf(stderr,"Box with smaller LB =\n");
 PrintBox(stderr,pB,NDim);
 #endif

 if (pB==NULL)
 	{
 	 fprintf(stderr,"End of While without a box.\n");
 	 exit(1);
 	}

 cerr<<"------------------------------------------------------------"<<endl;
 cerr << "LB(f(S)) in " << pB->F.lower()<< ", " 
      << iTDat.pBIncumb->F.upper() << endl; 
 cerr << "Min =        " <<  CtD.Min << endl;
 cerr << "Incumbent value  - Min = " << iTDat.pBIncumb->F.upper()- CtD.Min 
 	  << endl;
 cerr<<"Incumbent at:";
 cerr<< iTDat.pBIncumb->pX << endl;

 cerr <<"==============================================================="<<endl;

//First Labels
 //N.boxes Eval. 
 cerr << "& " << "CNEvalFG  ";
 cerr << "& " << "CNEvalLB  ";
 cerr << "& " << "CNEvalP   ";
 cerr << "& " << "CNSucLBF  " << endl;
 
 cerr << setw(10) << right << pCounters[CNEvalFG]     << " & ";
 cerr << setw(10) << right << pCounters[CNEvalLB]     << " & ";
 cerr << setw(10) << right << pCounters[CNEvalP ]     << " & ";
 cerr << setw(10) << right << pCounters[CNSucLbF]     << " & " << endl;
 
 //---------------------------------
 if (CtD.Draw)
    CtD.XLim.resize(0);
 
 CtD.InitBox.resize(0);
 
 CtD.Draw=False; 
 if (pB!=NULL)
	 pB=FreeBox(pB,CtD,False,"");

 iTDat.pBIncumb=FreeBox(iTDat.pBIncumb,CtD,false,"");
 iTDat.pBPoint =FreeBox(iTDat.pBPoint, CtD,false,"");
 iTDat.rVector.resize(0);

 pbtb=FreeBTB(pbtb,CtD,False,"");
    
return 0;
}

