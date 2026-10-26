#include "estadopartida.h"

EstadoPartida::EstadoPartida()
{
}

void EstadoPartida::setNombreJugador(
    const std::string& nombre)
{
    nombreJugador = nombre;
}

std::string EstadoPartida::getNombreJugador() const
{
    return nombreJugador;
}

void EstadoPartida::setTipoIA(
    const std::string& tipo)
{
    tipoIA = tipo;
}

std::string EstadoPartida::getTipoIA() const
{
    return tipoIA;
}

void EstadoPartida::setCantidadCartas(
    int cantidad)
{
    cantidadCartas = cantidad;
}

int EstadoPartida::getCantidadCartas() const
{
    return cantidadCartas;
}

void EstadoPartida::agregarCartaJugador(
    const DatosCarta& carta)
{
    cartasJugador.push_back(carta);
}

void EstadoPartida::agregarCartaIA(
    const DatosCarta& carta)
{
    cartasIA.push_back(carta);
}

const std::vector<DatosCarta>&
EstadoPartida::getCartasJugador() const
{
    return cartasJugador;
}

const std::vector<DatosCarta>&
EstadoPartida::getCartasIA() const
{
    return cartasIA;
}

void EstadoPartida::setCartaActivaJugador(
    const std::string& carta)
{
    cartaActivaJugador = carta;
}

void EstadoPartida::setCartaActivaIA(
    const std::string& carta)
{
    cartaActivaIA = carta;
}

std::string
EstadoPartida::getCartaActivaJugador() const
{
    return cartaActivaJugador;
}

std::string
EstadoPartida::getCartaActivaIA() const
{
    return cartaActivaIA;
}

int EstadoPartida::getCartasVivasJugador() const
{
    int cantidad = 0;

    for(const DatosCarta& carta
         : cartasJugador)
    {
        if(carta.vida > 0)
        {
            cantidad++;
        }
    }

    return cantidad;
}

int EstadoPartida::getVidaTotalJugador() const
{
    int total = 0;

    for(const DatosCarta& carta
         : cartasJugador)
    {
        total += carta.vida;
    }

    return total;
}

int EstadoPartida::getCartasVivasIA() const
{
    int cantidad = 0;

    for(const DatosCarta& carta
         : cartasIA)
    {
        if(carta.vida > 0)
        {
            cantidad++;
        }
    }

    return cantidad;
}

void EstadoPartida::limpiarCartasJugador()
{
    cartasJugador.clear();
}

void EstadoPartida::limpiarCartasIA()
{
    cartasIA.clear();
}