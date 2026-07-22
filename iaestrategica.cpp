#include "iaestrategica.h"

IAEstrategica::IAEstrategica()
{


}

Elemento& IAEstrategica::seleccionarContra(const Elemento &enemigo)
{
    int mayorDanio = -1;
    int mejorElemento = 0;

    for(int i = 0; i < elementos.size(); i++)
    {
        if(elementos[i].estaVivo())
        {
            int danio = sistema.calcularDanio(
                elementos[i],
                enemigo
                );


            if(danio > mayorDanio)
            {
                mayorDanio = danio;
                mejorElemento = i;
            }
        }
    }

    return elementos[mejorElemento];
}