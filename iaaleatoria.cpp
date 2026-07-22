#include "iaaleatoria.h"
#include <vector>
#include <cstdlib>

IAAleatoria::IAAleatoria()
{


}

Elemento& IAAleatoria::seleccionarContra(const Elemento &enemigo)
{
    (void)enemigo;
    return seleccionarElemento();
}

Elemento& IAAleatoria::seleccionarElemento()
{
    std::vector<int> disponibles;

    for (int i = 0; i < elementos.size(); i++)
    {
        if (elementos[i].estaVivo())
        {
            disponibles.push_back(i);
        }
    }

    int posicion = rand() % disponibles.size();

    return elementos[disponibles[posicion]];
}