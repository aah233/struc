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
int main(int argc, char *argv[]) {
    int i = 0;
    std::map<std::string, double> mapArg;
    std::vector<BOX*> boxTemporales;
    itvV IvV;
    IvV.resize(2);
    IvV[0] = itv(-7., 2.);
    IvV[1] = itv(-10., 3.);

    // Inicializar B como un puntero a BOX con IvV
    BOX* pB = new BOX(IvV);

    mapArg = ParamnsTerminal(argc, argv);
    // double alfa = mapArg["-d"]; // Si necesitas usar alfa
    //imprimir BOXB 
    std::cout << "Box B: " << *pB << std::endl;
    while (i < 2) {
        // Inicializar 2 divisores de caja
        BOX* pBoXG1 = new BOX(*pB); // Crear un nuevo BOX como copia de B
        BOX* pBoXG2 = new BOX(*pB); // Crear otro BOX como copia de B
        std::cout << "Box B1 antes de dividir: " << *pBoXG1 << std::endl;
        std::cout << "Box B1 antes de dividir: " << *pBoXG2 << std::endl;

        pB->Divide(*pBoXG1, *pBoXG2); // Divide B en BoXG1 y BoXG2
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
    BOX* pBTemp;
    //Recorrer todos los elementos y borrar su contenido 
    for (size_t i = 0; i < boxTemporales.size(); i++) {
         pBTemp = boxTemporales[i];
         delete pBTemp;
    }
    boxTemporales.clear();

    // Liberar el ultimo B creado
    delete pB;

    return 0;
}


