#include "iaestrategica.h"

IAEstrategica::IAEstrategica()
{
}

Elemento&
IAEstrategica::seleccionarElemento()
{
    for(Elemento& e : elementos)
    {
        if(e.estaVivo())
        {
            return e;
        }
    }

    return elementos[0];
}

Elemento&
IAEstrategica::seleccionarContra(
    const Elemento& enemigo)
{
    Elemento* mejor =nullptr;

    int mejorDanio = -1;

    for(Elemento& e : elementos)
    {
        if(!e.estaVivo())
        {
            continue;
        }

        int danio =
            configuracion->getDanio(
                e.obtenerAtaque(),
                enemigo.obtenerDefensa());

        if(danio >
            mejorDanio)
        {
            mejorDanio =
                danio;

            mejor =
                &e;
        }
    }

    if(mejor != nullptr)
    {
        return *mejor;
    }

    return elementos[0];
}

bool IAEstrategica::recalcularAnteCambio() const
{
    return true;
}
