#include "box.hpp"
#include "utils.h"

template <typename F, typename... Ts>
class box : public BOX<F, Ts...>
{
    itV F;

public:
    // Implementación de la función virtual
    BOX<F, Ts...> compareTo(const BOX<F, Ts...> &T1, const BOX<F, Ts...> &T2) const override
    {
        return BOX<F, Ts...>();
    }

    /**
     * @brief Get the new NBox value.
     *
     * This function increments the static variable NBox by 1 and returns its value.
     *
     * @return The new value of NBox.
     */

    static int GetNewNBox()
    {
        static int NBox = 0;
        NBox++;
        return NBox;
    }

private:
    // Método para obtener una nueva instancia de PBOX usando GetMemBox
    PBOX GetMemBox(const int NDim)
    {
        PBOX pB;
        pB = (PBOX)GetMem((SIZE)1, (SIZE)sizeof(BOX), "GetMemBox");
        // All generated simplices will be evaluated in F and G.
        pB->pX.resize(NDim);
        pB->G.resize(NDim);
        return pB;
    }

    void SizeBox(PBOX &pB, const INT NDim)
    {
        double Width;
        double Size = width(pB->pX[0]);

        for (int i = 1; i < NDim; i++)
        {
            Width = width(pB->pX[i]);
            if (Width > Size)
                Size = Width;
        }
        pB->Size = Size;

        return;
    }
};
