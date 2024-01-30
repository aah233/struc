#include "box.hpp"
#include "utils.h"


template<int F,int G, class... Ts> 
class GenericForm {
    int value = F;
    int value2 = G;
    iTDAT		iTDat;
    ConstData	CtD;
    int NDim = CtD.NDim;

    void initForm() {
        iTDat.pBPoint = GetMemBox(NDim);
        iTDat.pBIncumb = GetMemBox(NDim);
        iTDat.pBIncumb->F.upper() = DBL_MAX;
        iTDat.pBIncumb->F.lower() = DBL_MAX;
        iTDat.rVector.resize(NDim);
    }

public:
    DivideForm() {

    }
};

int main() {
    GenericForm<10,10, double> myObject;
}