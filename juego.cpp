#include "juego.h"
#include "jugadorhumano.h" // Necesario para usar dynamic_cast.

// ==========================
// Constructor
// ==========================
Juego::Juego(Jugador *jugador1, Jugador *jugador2)
{
    // Guarda los jugadores recibidos.
    this->jugador1 = jugador1;
    this->jugador2 = jugador2;

    // Reparte 5 elementos a cada jugador.
    jugador1->repartirElementos();
    jugador2->repartirElementos();

    // Al comenzar todavía no hay elementos seleccionados.
    elementoActivoJugador = nullptr;
    elementoActivoIA = nullptr;

    // Mensaje inicial.
    mensajeEstado = "Seleccione un elemento";
}

// ==========================
// El jugador selecciona una carta.
// ==========================
void Juego::seleccionarElemento(int indice)
{
    // Intenta convertir jugador1 en JugadorHumano.
    JugadorHumano *humano = dynamic_cast<JugadorHumano *>(jugador1);

    // Si realmente era un JugadorHumano...
    if (humano) {
        // Guarda qué elemento eligió.
        humano->seleccionarPorIndice(indice);

        // Obtiene un puntero al elemento elegido.
        elementoActivoJugador = &humano->seleccionarElemento();

        // Actualiza el mensaje mostrado en pantalla.
        mensajeEstado = "La IA está eligiendo un elemento...";
    }

    // Condicional para evitar que la IA cambie de carta, si el jugador tambien cambia.
    if (elementoActivoIA == nullptr) {
        elementoActivoIA = &jugador2->seleccionarElemento();
    }
}

// ==========================
// Devuelve el elemento activo del jugador.
// ==========================
Elemento *Juego::getElementoActivoJugador()
{
    return elementoActivoJugador;
}

// ==========================
// Devuelve el elemento activo de la IA.
// ==========================
Elemento *Juego::getElementoActivoIA()
{
    return elementoActivoIA;
}

// ==========================
// Verifica si ambos eligieron.
// ==========================
bool Juego::hayElementosSeleccionados()
{
    // nullptr significa "no apunta a ningún objeto".
    return elementoActivoJugador != nullptr && elementoActivoIA != nullptr;
}

// ==========================
// Ejecuta un turno.
// ==========================
void Juego::resolverTurno()
{
    // Si todavía no eligieron cartas, no hace nada.
    if (!hayElementosSeleccionados()) {
        return;
    }

    // El jugador ataca primero.
    if (elementoActivoJugador->estaVivo()) {
        sistema.aplicarDanio(*elementoActivoJugador, *elementoActivoIA);
    }

    // Si la IA sigue viva, contraataca.
    if (elementoActivoIA->estaVivo()) {
        sistema.aplicarDanio(*elementoActivoIA, *elementoActivoJugador);
    }

    // Si la IA perdió su elemento,
    // selecciona otro automáticamente y ataca.
    if (iaDebeCambiar()) {
        //cambio
        elementoActivoIA = nullptr;
        elementoActivoIA = &jugador2->seleccionarElemento();
        sistema.aplicarDanio(*elementoActivoIA, *elementoActivoJugador);
    }

    mensajeEstado = "Turno finalizado";
}

// ==========================
// Devuelve el mensaje.
// ==========================
QString Juego::getMensajeEstado() const
{
    return mensajeEstado;
}

// ==========================
// Borra la selección.
// ==========================
void Juego::cancelarSeleccion()
{
    // Ambos punteros apuntan a null para cambiar el elemento activo.
    elementoActivoJugador = nullptr;
//    elementoActivoIA = nullptr;

    mensajeEstado = "Seleccione un elemento";
}

// ==========================
// ¿El jugador debe cambiar?
// ==========================
bool Juego::jugadorDebeCambiar() const
{
    // Si no hay elemento seleccionado...
    if (elementoActivoJugador == nullptr)
        return true;

    // Si murió, también debe cambiar.
    return !elementoActivoJugador->estaVivo();
}

// ==========================
// ¿La IA debe cambiar?
// ==========================
bool Juego::iaDebeCambiar() const
{
    if (elementoActivoIA == nullptr)
        return true;

    return !elementoActivoIA->estaVivo();
}

// ==========================
// ¿Terminó la partida?
// ==========================
bool Juego::termino() const
{
    // Si alguno ya no tiene elementos vivos,
    // el juego terminó.
    return !jugador1->tieneElementosVivos() || !jugador2->tieneElementosVivos();
}

// ==========================
// ¿Ganó el jugador?
// ==========================
bool Juego::ganoJugador() const
{
    // El jugador debe tener elementos vivos y la IA no.
    return !jugador1->tieneElementosVivos() && !jugador2->tieneElementosVivos();
}

void Juego::iniciarEnfrentamiento(){
    // Condicional para evitar que la IA cambie de carta, si el jugador tambien cambia.
    if (elementoActivoIA == nullptr) {
        elementoActivoIA = &jugador2->seleccionarElemento();
    }
}