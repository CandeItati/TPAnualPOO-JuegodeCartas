#include "juego.h"
#include "jugadorhumano.h" // Necesario para usar dynamic_cast.
#include "contrincanteia.h"

// ==========================
// Constructor
// ==========================
Juego::Juego(Jugador *jugador1,Jugador *jugador2,Configuracion* config): sistema(config)
{
    this->jugador1 = jugador1;
    this->jugador2 = jugador2;
    this->configuracion = config;

    jugador1->repartirElementos(configuracion->getCantidadCartas());

    jugador2->repartirElementos(configuracion->getCantidadCartas());

    elementoActivoJugador = nullptr;
    elementoActivoIA = nullptr;
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
    }

    ContrincanteIA* ia =
        dynamic_cast<ContrincanteIA*>(
            jugador2);

    if(elementoActivoIA == nullptr)
    {
        elementoActivoIA =
            &jugador2->seleccionarContra(
                *elementoActivoJugador);
    }
    else if(
        ia &&
        ia->recalcularAnteCambio())
    {
        elementoActivoIA =
            &jugador2->seleccionarContra(
                *elementoActivoJugador);
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
    if (!hayElementosSeleccionados()) {
        return;
    }

    mensajeEstado.clear();
    ultimoResultado.limpiar();

    if (elementoActivoJugador->estaVivo()) {

        sistema.aplicarDanio(*elementoActivoJugador,*elementoActivoIA);

        ResultadoAtaque ataque;

        ataque.atacaJugador = true;

        ataque.atacante =
            elementoActivoJugador->obtenerNombre();

        ataque.defensor =
            elementoActivoIA->obtenerNombre();

        ataque.danio =
            sistema.calcularDanio(
                *elementoActivoJugador,
                *elementoActivoIA);

        ataque.defensorEliminado =
            !elementoActivoIA->estaVivo();

        ultimoResultado.agregarAtaque(
            ataque);

        mensajeEstado += elementoActivoJugador->obtenerNombre();

        mensajeEstado += " ataco a ";

        mensajeEstado += elementoActivoIA->obtenerNombre();
    }

    if (elementoActivoIA->estaVivo()) {

        sistema.aplicarDanio(*elementoActivoIA,*elementoActivoJugador);

        ResultadoAtaque ataque;

        ataque.atacaJugador = false;

        ataque.atacante =
            elementoActivoIA->obtenerNombre();

        ataque.defensor =
            elementoActivoJugador->obtenerNombre();

        ataque.danio =
            sistema.calcularDanio(
                *elementoActivoIA,
                *elementoActivoJugador);

        ataque.defensorEliminado =
            !elementoActivoJugador->estaVivo();

        ultimoResultado.agregarAtaque(
            ataque);

        mensajeEstado += "\n";

        mensajeEstado += elementoActivoIA->obtenerNombre();

        mensajeEstado += " ataco a ";

        mensajeEstado += elementoActivoJugador->obtenerNombre();
    }
}

// ==========================
// ¿La IA necesita elegir una carta nueva y atacar con ella?
// ==========================
bool Juego::iaNecesitaCambiarYAtacar() const
{
    return iaDebeCambiar() && jugador2->tieneElementosVivos();
}

// ==========================
// Segundo paso del turno: la IA cambia de carta (si la anterior murió) y ataca con la nueva, para no perder el turno.
// ==========================
void Juego::resolverCambioIA()
{
    mensajeEstado.clear();

    elementoActivoIA = nullptr;

    if (jugador2->tieneElementosVivos()) {

        elementoActivoIA =
            &jugador2->seleccionarContra(
                *elementoActivoJugador);

        mensajeEstado = "La IA elige una nueva carta: " + elementoActivoIA->obtenerNombre();

        if (elementoActivoJugador && elementoActivoJugador->estaVivo())
        {

            int danio =
                sistema.calcularDanio(
                    *elementoActivoIA,
                    *elementoActivoJugador);

            sistema.aplicarDanio(*elementoActivoIA,*elementoActivoJugador);

            mensajeEstado += "\n";

            mensajeEstado += elementoActivoIA->obtenerNombre();

            mensajeEstado += " ataco a ";

            mensajeEstado += elementoActivoJugador->obtenerNombre();

            mensajeEstado +=
                " (" +
                std::to_string(danio) +
                " daño)";
        }
    }
}



// ==========================
// Devuelve el mensaje.
// ==========================
std::string Juego::getMensajeEstado() const
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

Jugador* Juego::getJugador1() const
{
    return jugador1;
}

Jugador* Juego::getJugador2() const
{
    return jugador2;
}

Configuracion* Juego::getConfiguracion() const
{
    return configuracion;
}

const ResultadoRonda&
Juego::getUltimoResultado() const
{
    return ultimoResultado;
}

EstadoPartida Juego::crearEstadoPartida() const
{
    EstadoPartida estado;

    estado.setNombreJugador(
        jugador1->getNombre());

    estado.setTipoIA(
        configuracion->getTipoIA());

    estado.setCantidadCartas(
        configuracion->getCantidadCartas());

    for(const Elemento& e :
         jugador1->getElementos())
    {
        DatosCarta carta;

        carta.nombre =
            e.obtenerNombre();

        carta.vida =
            e.obtenerVida();

        estado.agregarCartaJugador(
            carta);
    }

    for(const Elemento& e :
         jugador2->getElementos())
    {
        DatosCarta carta;

        carta.nombre =
            e.obtenerNombre();

        carta.vida =
            e.obtenerVida();

        estado.agregarCartaIA(
            carta);
    }

    return estado;
}

void Juego::cargarDesdeEstado(
    const EstadoPartida& estado)
{
    jugador1->setNombre(
        estado.getNombreJugador());

    jugador1->cargarDesdeEstado(
        estado.getCartasJugador());

    jugador2->cargarDesdeEstado(
        estado.getCartasIA());

    elementoActivoJugador = nullptr;
    elementoActivoIA = nullptr;

    const auto& cartasJugador =
        jugador1->getElementos();

    for(size_t i = 0;
         i < cartasJugador.size();
         i++)
    {
        if(cartasJugador[i]
                .obtenerNombre() ==
            estado.getCartaActivaJugador())
        {
            elementoActivoJugador =
                const_cast<Elemento*>(
                    &cartasJugador[i]);
            break;
        }
    }

    const auto& cartasIA =
        jugador2->getElementos();

    for(size_t i = 0;
         i < cartasIA.size();
         i++)
    {
        if(cartasIA[i]
                .obtenerNombre() ==
            estado.getCartaActivaIA())
        {
            elementoActivoIA =
                const_cast<Elemento*>(
                    &cartasIA[i]);
            break;
        }
    }
}