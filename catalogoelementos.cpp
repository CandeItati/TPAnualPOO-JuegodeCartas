#include "catalogoelementos.h"

#include <QRandomGenerator>

const CatalogoElementos::DatosElemento CatalogoElementos::elementos[11] =
    {
        {"Agua",     AGUA,  AGUA},
        {"Fuego",    FUEGO, FUEGO},
        {"Tierra",   TIERRA, TIERRA},
        {"Rayo",     RAYO,  RAYO},
        {"Hielo",    HIELO, HIELO},

        {"Lava",     FUEGO, TIERRA},
        {"Vapor",    FUEGO, AGUA},
        {"Tormenta", RAYO,  AGUA},
        {"Pantano",  AGUA,  TIERRA},
        {"Glaciar",  HIELO, AGUA},
        {"Plasma",   RAYO,  FUEGO}
};

Elemento CatalogoElementos::crearElementoAleatorio()
{
    int indice = QRandomGenerator::global()->bounded(11);

    return Elemento(
        elementos[indice].nombre,
        elementos[indice].ataque,
        elementos[indice].defensa
        );
}
CatalogoElementos::CatalogoElementos()
{

}