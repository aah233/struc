/***************************************************************************
                          Example-1.0.cpp  -  description
                             -------------------
    begin                : Jan 2020
    copyright            : (C) 2020 by L.G. Casado
    email                : leo@ual.es
@param -d  alfa (alfa is the first  parameter to divide the box)


***************************************************************************/

#include "Box.hpp"
#include "./Modules/ParamnsTerminal.cpp"
/*---------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
  double alfa;
  std::map<std::string, double> mapArg;

   //obtener por parámetro el -d que es alfa
   mapArg = ParamnsTerminal(argc, argv);
   alfa = mapArg["-d"];

   //Me quedo por aqui haciendo el while, para comparar si el width es menor que alfa
   
   /*
    
 itvV IvV;
 IvV.resize(2);
 IvV[0]=itv(-2., 2.);
 IvV[1]=itv(-3., 3.);
 BOX B(IvV);  //Inicialize a BOX with IvV
 cout << B << endl;  //print the BOX
 
 //Init 2 box divider 
 BOX BoXG1(B);
 BOX BoXG2(B);
 //Aqui necesito pedir los parámetros por consola y que no hacer el bucle hasta que el tamaño no sea menor que el alfa 
 //alfa es el parámetro -d 

 
 B.Divide(BoXG1, BoXG2);

 cout << BoXG1 << endl;  //print the BOX
 cout << BoXG2 << endl;  //print the BOX
*/
return 0;

}

void terminalParamns(){

}

