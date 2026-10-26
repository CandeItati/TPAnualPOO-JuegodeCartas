#ifndef CATALOGOELEMENTOS_H // Evita que el archivo se incluya más de una vez.
#define CATALOGOELEMENTOS_H

#include <string>
#include "elemento.h" // Se necesita porque esta clase crea objetos Elemento.

// La clase CatalogoElementos funciona como una base de datos de todos los elementos disponibles en el juego.
class CatalogoElementos
{
public:
    CatalogoElementos(); // Constructor.

    // Método estático.
    // Permite crear un elemento aleatorio sin necesidad de crear un objeto CatalogoElementos.
    static Elemento crearElementoAleatorio();

    static Elemento crearElementoPorNombre(const std::string& nombre);

private:
    // Estructura auxiliar que almacena la información necesaria para crear un Elemento.
    struct DatosElemento
    {
        std::string nombre;
        TipoElemento ataque;
        TipoElemento defensa;
    };

    // Arreglo estático que contiene todos los elementos existentes en el juego.
    static const DatosElemento elementos[11];
};

#endif // CATALOGOELEMENTOS_H