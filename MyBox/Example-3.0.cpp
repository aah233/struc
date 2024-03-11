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
  int i = 0;
  //double alfa;
  itv  FXeval; //FX to evaluate
  FXeval.upper()=__DBL_MAX__;
  FXeval.lower()=-__DBL_MAX__;
  std::map<std::string, double> mapArg;
  std::vector<BOX> boxTemporales;
  itvV IvV;
  IvV.resize(2);
  IvV[0]=itv(-7., 2.);
  IvV[1]=itv(-10., 3.);
  BOX B(IvV);  //Inicialize a BOX with IvV
   //obtener por parámetro el -d que es alfa
  mapArg = ParamnsTerminal(argc, argv);
  //alfa = mapArg["-d"];
while (i < 2)
{
 //Init 2 box divider 
 BOX BoXG1(B);
 BOX BoXG2(B);
 B.Divide(BoXG1, BoXG2);
 boxTemporales.push_back(BoXG1);
 boxTemporales.push_back(BoXG2);
 B.~BOX (); //destruct B
 BOX B(boxTemporales[0]); //B is BoXG1
i++;
}
 //print boxTemporales 
  for (size_t i = 0; i < boxTemporales.size(); i++)
  {
    std::cout << "Box " << i << " " << boxTemporales[i] << std::endl;
  }
return 0;

}

void terminalParamns(){

}

