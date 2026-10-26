#ifndef ESTADOPARTIDA_H
#define ESTADOPARTIDA_H

#include <string>
#include <vector>

struct DatosCarta
{
    std::string nombre;
    int vida;
};

class EstadoPartida
{
public:
    EstadoPartida();

    void setNombreJugador(
        const std::string& nombre);

    std::string getNombreJugador() const;

    void setTipoIA(
        const std::string& tipo);

    std::string getTipoIA() const;

    void setCantidadCartas(
        int cantidad);

    int getCantidadCartas() const;

    void agregarCartaJugador(
        const DatosCarta& carta);

    void agregarCartaIA(
        const DatosCarta& carta);

    const std::vector<DatosCarta>&
    getCartasJugador() const;

    const std::vector<DatosCarta>&
    getCartasIA() const;

    int getCartasVivasIA() const;

    void setCartaActivaJugador(
        const std::string& carta);

    void setCartaActivaIA(
        const std::string& carta);

    std::string
    getCartaActivaJugador() const;

    std::string
    getCartaActivaIA() const;

    int getCartasVivasJugador() const;

    int getVidaTotalJugador() const;

    void limpiarCartasJugador();
    void limpiarCartasIA();

private:
    std::string nombreJugador;
    std::string tipoIA;

    int cantidadCartas = 0;

    std::vector<DatosCarta> cartasJugador;
    std::vector<DatosCarta> cartasIA;

    std::string cartaActivaJugador;
    std::string cartaActivaIA;
};

#endif