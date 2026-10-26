#include "configuracion.h"

Configuracion::Configuracion()
{
    cantidadCartas = 5;
    tipoIA = "ALEATORIA";
}

int Configuracion::getCantidadCartas() const
{
    return cantidadCartas;
}

std::string Configuracion::getTipoIA() const
{
    return tipoIA;
}

int Configuracion::getDanio(
    const std::string& atacante,
    const std::string& defensor) const
{
    std::string clave =
        atacante +
        "_" +
        defensor;

    auto it =
        tablaDanios.find(clave);

    if(it != tablaDanios.end())
    {
        return it->second;
    }

    return 0;
}

int Configuracion::getDanio(
    TipoElemento atacante,
    TipoElemento defensor) const
{
    static const std::string tipos[5] =
        {
            "fuego",
            "agua",
            "tierra",
            "rayo",
            "hielo"
        };

    return getDanio(
        tipos[atacante],
        tipos[defensor]
        );
}

void Configuracion::setCantidadCartas(int cantidad)
{
    cantidadCartas = cantidad;
}

void Configuracion::setTipoIA(
    const std::string& tipo)
{
    tipoIA = tipo;
}

void Configuracion::setDanio(
    const std::string& clave,
    int valor)
{
    tablaDanios[clave] = valor;
}