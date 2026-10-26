#include "superia.h"

SuperIA::SuperIA()
{
}

Elemento&
SuperIA::seleccionarElemento()
{
    Elemento* mejor = nullptr;

    for(Elemento& e : elementos)
    {
        if(!e.estaVivo())
        {
            continue;
        }

        if(mejor == nullptr ||
            e.obtenerVida() >
                mejor->obtenerVida())
        {
            mejor = &e;
        }
    }

    if(mejor)
    {
        return *mejor;
    }

    return elementos[0];
}

Elemento& SuperIA::seleccionarContra(
    const Elemento& enemigo)
{
    Elemento* mejorMata = nullptr;

    int menorExceso =
        999999;

    int vidaEnemigo =
        enemigo.obtenerVida();

    // Buscar cartas que maten este turno.
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

        if(danio >= vidaEnemigo)
        {
            int exceso =
                danio - vidaEnemigo;

            if(mejorMata == nullptr ||
                exceso < menorExceso)
            {
                menorExceso =
                    exceso;

                mejorMata =
                    &e;
            }
            else if(exceso ==
                     menorExceso)
            {
                // Desempate por vida.
                if(e.obtenerVida() >
                    mejorMata->obtenerVida())
                {
                    mejorMata =
                        &e;
                }
                // Si tienen misma vida,
                // elegir la que mejor resista.
                else if(
                    e.obtenerVida() ==
                    mejorMata->obtenerVida())
                {
                    int danioActual =
                        configuracion->getDanio(
                            enemigo.obtenerAtaque(),
                            e.obtenerDefensa());

                    int danioMejor =
                        configuracion->getDanio(
                            enemigo.obtenerAtaque(),
                            mejorMata->obtenerDefensa());

                    if(danioActual <
                        danioMejor)
                    {
                        mejorMata =
                            &e;
                    }
                }
            }
        }
    }

    // Si encontró una carta que mata,
    // usar esa.
    if(mejorMata)
    {
        return *mejorMata;
    }

    // Si no puede matar,
    // elegir la que haga más daño.
    Elemento* mejor = nullptr;

    int mejorDanio =
        -1;

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

        if(mejor == nullptr ||
            danio > mejorDanio)
        {
            mejorDanio =
                danio;

            mejor =
                &e;
        }
        else if(danio ==
                 mejorDanio)
        {
            // Desempate por vida.
            if(e.obtenerVida() >
                mejor->obtenerVida())
            {
                mejor =
                    &e;
            }
            // Si tienen misma vida,
            // desempate por defensa.
            else if(
                e.obtenerVida() ==
                mejor->obtenerVida())
            {
                int danioActual =
                    configuracion->getDanio(
                        enemigo.obtenerAtaque(),
                        e.obtenerDefensa());

                int danioMejor =
                    configuracion->getDanio(
                        enemigo.obtenerAtaque(),
                        mejor->obtenerDefensa());

                if(danioActual <
                    danioMejor)
                {
                    mejor =
                        &e;
                }
            }
        }
    }

    if(mejor)
    {
        return *mejor;
    }

    return elementos[0];
}

bool SuperIA::recalcularAnteCambio() const
{
    return true;
}