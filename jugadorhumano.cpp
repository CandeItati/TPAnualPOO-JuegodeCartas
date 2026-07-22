#include "jugadorhumano.h"


JugadorHumano::JugadorHumano()
{

}


Elemento& JugadorHumano::seleccionarElemento()
{
    return elementos[elementoSeleccionado];
}



Elemento& JugadorHumano::seleccionarContra(const Elemento &enemigo)
{
    Q_UNUSED(enemigo);

    return seleccionarElemento();
}



void JugadorHumano::seleccionarPorIndice(int indice)
{
    elementoSeleccionado = indice;
}