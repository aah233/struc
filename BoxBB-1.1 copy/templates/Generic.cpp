#include "box.hpp"
#include "utils.h"


template<typename F, typename... Ts>
class BOX {
    itV F*;
    
public:
    // Virtual function, must be implemented by derived classes
    virtual BOX<F, Ts...> compareTo(const BOX<F, Ts...>& T1, const BOX<F, Ts...>& T2) const = 0;
};

