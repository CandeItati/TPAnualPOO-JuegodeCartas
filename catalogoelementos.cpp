#include "catalogoelementos.h"   // Incluye la definición de la clase.

#include <QRandomGenerator>      // Permite generar números aleatorios.



// ===============================================
// Catálogo de elementos disponibles.
// ===============================================

// Se define el arreglo declarado en el .h.
// Cada posición representa un elemento distinto.
const CatalogoElementos::DatosElemento CatalogoElementos::elementos[11]=
    {

    // Elementos simples
    {"Agua", AGUA, AGUA},
    {"Fuego", FUEGO, FUEGO},
    {"Tierra", TIERRA, TIERRA},
    {"Rayo", RAYO, RAYO},
    {"Hielo", HIELO, HIELO},

    // Elementos mixtos
    {"Lava", FUEGO, TIERRA},
    {"Vapor", FUEGO, AGUA},
    {"Tormenta", RAYO, AGUA},
    {"Pantano", AGUA, TIERRA},
    {"Glaciar", HIELO, AGUA},
    {"Plasma", RAYO, FUEGO}
};



// ===============================================
// Crea un elemento aleatorio.
// ===============================================
Elemento CatalogoElementos::crearElementoAleatorio()
{
    // Genera un número aleatorio entre 0 y 10.
    // El 11 NO se incluye.
    int indice = QRandomGenerator::global()->bounded(11);

    // Usa la información almacenada en el catálogo
    // para construir un nuevo objeto Elemento.
    return Elemento(
        elementos[indice].nombre,
        elementos[indice].ataque,
        elementos[indice].defensa);
}



// ===============================================
// Constructor
// ===============================================
CatalogoElementos::CatalogoElementos()
{
    // No realiza ninguna acción.
}