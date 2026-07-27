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

    mensajeEstado.clear();

    // El jugador ataca primero.
    if (elementoActivoJugador->estaVivo()) {
        sistema.aplicarDanio(*elementoActivoJugador, *elementoActivoIA);
        mensajeEstado += elementoActivoJugador->obtenerNombre() + " ataco a " + elementoActivoIA->obtenerNombre();
    }

    // Si la IA sigue viva, contraataca.
    if (elementoActivoIA->estaVivo()) {
        sistema.aplicarDanio(*elementoActivoIA, *elementoActivoJugador);
        mensajeEstado += "\n";
        mensajeEstado += elementoActivoIA->obtenerNombre() + " ataco a " + elementoActivoJugador->obtenerNombre();
    }

    // OJO: el cambio de carta de la IA (si murió) ya NO pasa acá.
    // Se resuelve aparte, en resolverCambioIA().
}

// ==========================
// ¿La IA necesita elegir una carta nueva y atacar con ella?
// ==========================
bool Juego::iaNecesitaCambiarYAtacar() const
{
    return iaDebeCambiar() && jugador2->tieneElementosVivos();
}

// ==========================
// Segundo paso del turno: la IA cambia de carta (si la
// anterior murió) y ataca con la nueva, para no perder el turno.
// ==========================
void Juego::resolverCambioIA()
{
    mensajeEstado.clear();

    elementoActivoIA = nullptr;
    if (jugador2->tieneElementosVivos()) {
        elementoActivoIA = &jugador2->seleccionarElemento();
        mensajeEstado = "La IA elige una nueva carta: " + elementoActivoIA->obtenerNombre();

        if (elementoActivoJugador && elementoActivoJugador->estaVivo()) {
            sistema.aplicarDanio(*elementoActivoIA, *elementoActivoJugador);
            mensajeEstado += "\n";
            mensajeEstado += elementoActivoIA->obtenerNombre() + " ataco a " + elementoActivoJugador->obtenerNombre();
        }
    }
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
    return jugador2->tieneElementosVivos() == false && jugador1->tieneElementosVivos() == true;
}