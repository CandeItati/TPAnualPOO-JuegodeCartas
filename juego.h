#ifndef JUEGO_H
#define JUEGO_H

#include <QString>

#include "catalogoelementos.h"
#include "jugador.h"
#include "sistemacombate.h"

class Juego
{
public:

    Juego(Jugador* jugador1, Jugador* jugador2);

    void seleccionarElemento(int indice);

    Elemento* getElementoActivoJugador();
    Elemento* getElementoActivoIA();

    bool hayElementosSeleccionados();
    void resolverTurno();
    void cancelarSeleccion();
    bool jugadorDebeCambiar() const;
    bool iaDebeCambiar() const;
    bool termino() const;
    bool ganoJugador() const;

    QString getMensajeEstado() const;


private:

    Jugador* jugador1;
    Jugador* jugador2;

    QString mensajeEstado;

    Elemento* elementoActivoJugador;
    Elemento* elementoActivoIA;

    CatalogoElementos catalogo;

    SistemaCombate sistema;
};

#endif // JUEGO_H