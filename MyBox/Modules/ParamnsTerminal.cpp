#include <iostream>
#include <map>
#include <cstring>
/***************************************************************************
                ParamnsTerminal.cpp  -  Template class
****************************************************************************/


std::map<std::string, double> ParamnsTerminal(int argc, char *argv[])
{
    std::map<std::string, double> mapArg;
    if (argc % 2 == 0)
    {
        throw std::invalid_argument("The number of parameters must be even.\n");
    }

    for (int i = 1; i < argc; i += 2)
    {
        // Caso -d
        if (std::strcmp(argv[i], "-d") == 0)
        {
            double valorD = std::stod(argv[i + 1]);

            if (valorD < 0)
            {
                // Manejo de error: número de -d debe ser no negativo
                throw std::invalid_argument("The number of -d must be non-negative.\n");
            }

            mapArg["-d"] = valorD;
        }
    }

    //check if map have -d parameter
    if (mapArg.find("-d") == mapArg.end())
    {
        // Manejo de error: -d es necesario
        throw std::invalid_argument("Parameter -d is necessary.\n");
    }

    return mapArg;
}

/*
 * This is for test if print correctly the map
 */

void printMap(const std::map<std::string, int> &mapa)
{
    for (const auto &par : mapa)
    {
        std::cout << par.first << ": " << par.second << std::endl;
    }
}