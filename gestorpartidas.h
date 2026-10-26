#ifndef GESTORPARTIDAS_H
#define GESTORPARTIDAS_H

#include "estadopartida.h"

class Juego;

class GestorPartidas
{
public:
    GestorPartidas();

    bool guardarPartida( int slot, Juego* juego);

    EstadoPartida cargarPartida(int slot);

    bool existeSlot(int slot);

    bool guardarEstadoTemporal(
        const EstadoPartida& estado);

    EstadoPartida cargarEstadoTemporal();
};

#endif
