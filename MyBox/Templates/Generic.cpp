#include "box.hpp"
#include "utils.h"
#include "../defines.h"

template<itV F, typename... Ts>
class Generic {
    
public:
    //Constructor
    Generic(itV* intervalo) {
        this->intervalo = intervalo;
    }
    
    //return the interval of the inclusion
     F* getF() const {
        return this->intervalo;
    }
    
    private:
        itV* intervalo;  // Corregir la declaración del puntero
};