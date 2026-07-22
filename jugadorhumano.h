#ifndef JUGADORHUMANO_H
#define JUGADORHUMANO_H

#include "jugador.h"


class JugadorHumano : public Jugador
{
public:

    JugadorHumano();


    Elemento& seleccionarElemento() override;

    Elemento& seleccionarContra(const Elemento &enemigo) override;


    void seleccionarPorIndice(int indice);

protected:
    int elementoSeleccionado = 0;
};


#endif