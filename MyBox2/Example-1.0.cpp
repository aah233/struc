/***************************************************************************
                          Example-1.0.cpp  -  description
                             -------------------
    begin                : Jan 2020
    copyright            : (C) 2020 by L.G. Casado
    email                : leo@ual.es
 ***************************************************************************/

#include "Box.hpp"

/*---------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
 itvV IvV;
 IvV.resize(2);
 IvV[0]=itv(-2., 2.);
 IvV[1]=itv(-3., 3.);
 
 BOX B(IvV);
 
 cout << B << endl;
 
return 0;
}

