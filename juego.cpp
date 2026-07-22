#include "juego.h"
#include "jugadorhumano.h"

Juego::Juego(Jugador* jugador1, Jugador* jugador2)
{
    this->jugador1 = jugador1;
    this->jugador2 = jugador2;


    jugador1->repartirElementos();
    jugador2->repartirElementos();


    elementoActivoJugador = nullptr;
    elementoActivoIA = nullptr;

    mensajeEstado = "Seleccione un elemento";

}
void Juego::seleccionarElemento(int indice)
{
    JugadorHumano* humano = dynamic_cast<JugadorHumano*>(jugador1);

    if (humano)
    {
        humano->seleccionarPorIndice(indice);

        elementoActivoJugador = &humano->seleccionarElemento();

        elementoActivoIA = &jugador2->seleccionarElemento();

        mensajeEstado = "La IA está eligiendo un elemento...";
    }
}
Elemento* Juego::getElementoActivoJugador()
{
    return elementoActivoJugador;
}

Elemento* Juego::getElementoActivoIA()
{
    return elementoActivoIA;
}

bool Juego::hayElementosSeleccionados()
{
    return elementoActivoJugador != nullptr &&
           elementoActivoIA != nullptr;
}
void Juego::resolverTurno()
{
    if (!hayElementosSeleccionados())
    {
        return;
    }

    if (elementoActivoJugador->estaVivo())
    {
    sistema.aplicarDanio(*elementoActivoJugador,*elementoActivoIA);
    }

    if (elementoActivoIA->estaVivo())
    {
        sistema.aplicarDanio(*elementoActivoIA,*elementoActivoJugador);
    }

    if (iaDebeCambiar())
    {
        elementoActivoIA = &jugador2->seleccionarElemento();
    }

    mensajeEstado = "Turno finalizado";
}
QString Juego::getMensajeEstado() const
{
    return mensajeEstado;
}
void Juego::cancelarSeleccion()
{
    elementoActivoJugador = nullptr;
    elementoActivoIA = nullptr;

    mensajeEstado = "Seleccione un elemento";
}
bool Juego::jugadorDebeCambiar() const
{
    if (elementoActivoJugador == nullptr)
        return true;

    return !elementoActivoJugador->estaVivo();
}
bool Juego::iaDebeCambiar() const
{
    if (elementoActivoIA == nullptr)
        return true;

    return !elementoActivoIA->estaVivo();
}
bool Juego::termino() const
{
    return !jugador1->tieneElementosVivos() || !jugador2->tieneElementosVivos();
}
bool Juego::ganoJugador() const
{
    return jugador1->tieneElementosVivos() &&
           !jugador2->tieneElementosVivos();
}