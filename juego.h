#ifndef JUEGO_H // Evita que el archivo se incluya dos veces.
#define JUEGO_H

#include <QString> // Permite utilizar QString.

#include "catalogoelementos.h" // Incluye el catálogo de elementos.
#include "jugador.h"           // Incluye la clase Jugador.
#include "sistemacombate.h"    // Incluye la lógica del combate.

// La clase Juego controla toda la partida.
class Juego
{
public:
    // Constructor.
    // Recibe dos jugadores (humano e IA).
    Juego(Jugador *jugador1, Jugador *jugador2);

    // Permite al jugador humano seleccionar un elemento.
    void seleccionarElemento(int indice);

    // Devuelve el elemento actualmente seleccionado por el jugador.
    Elemento *getElementoActivoJugador();

    // Devuelve el elemento actualmente seleccionado por la IA.
    Elemento *getElementoActivoIA();

    // Indica si ambos jugadores ya tienen un elemento seleccionado.
    bool hayElementosSeleccionados();

    // Ejecuta un turno completo de combate.
    void resolverTurno();

    // Borra la selección actual.
    void cancelarSeleccion();

    // Devuelve true si el jugador debe elegir otro elemento.
    bool jugadorDebeCambiar() const;

    // Devuelve true si la IA debe elegir otro elemento.
    bool iaDebeCambiar() const;

    // Indica si la partida terminó.
    bool termino() const;

    // Devuelve true si ganó el jugador humano.
    bool ganoJugador() const;

    // Devuelve el mensaje que mostrará la interfaz.
    QString getMensajeEstado() const;

    void iniciarEnfrentamiento();

private:
    // Punteros a los jugadores.
    Jugador *jugador1;
    Jugador *jugador2;

    // Mensaje que se muestra en pantalla.
    QString mensajeEstado;

    // Elemento actualmente seleccionado por el jugador.
    Elemento *elementoActivoJugador;

    // Elemento actualmente seleccionado por la IA.
    Elemento *elementoActivoIA;

    // Catálogo de elementos.
    CatalogoElementos catalogo;

    // Sistema encargado del combate.
    SistemaCombate sistema;
};

#endif // JUEGO_H