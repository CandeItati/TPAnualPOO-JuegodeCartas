#include "catalogoelementos.h" // Incluye la definición de la clase.

#include <random>

// ===============================================
// Catálogo de elementos disponibles.
// ===============================================

// Se define el arreglo declarado en el .h. Cada posición representa un elemento distinto.
const CatalogoElementos::DatosElemento CatalogoElementos::elementos[11] = {

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
    {"Plasma", RAYO, FUEGO}};

// ===============================================
// Crea un elemento aleatorio.
// ===============================================
Elemento CatalogoElementos::crearElementoAleatorio()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<>
        distribucion(0, 10);

    int indice =
        distribucion(gen);

    // Usa la información almacenada en el catálogo para construir un nuevo objeto Elemento.
    return Elemento(elementos[indice].nombre, elementos[indice].ataque, elementos[indice].defensa);
}

Elemento
CatalogoElementos::crearElementoPorNombre(
    const std::string& nombre)
{
    for(int i = 0; i < 11; i++)
    {
        if(elementos[i].nombre == nombre)
        {
            return Elemento(
                elementos[i].nombre,
                elementos[i].ataque,
                elementos[i].defensa);
        }
    }

    return Elemento(
        elementos[0].nombre,
        elementos[0].ataque,
        elementos[0].defensa);
}

// ===============================================
// Constructor
// ===============================================
CatalogoElementos::CatalogoElementos()
{
    // No realiza ninguna acción.
}