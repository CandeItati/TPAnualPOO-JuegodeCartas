#ifndef JUGADOR_H // Evita que este archivo se incluya más de una vez.
#define JUGADOR_H

#include "catalogoelementos.h" // Se necesita para crear elementos aleatorios.
#include "elemento.h"          // La clase Jugador trabaja con objetos Elemento.
#include <vector>              // Permite usar la clase vector.

using namespace std; // Evita escribir std::vector en todo el código.

class Jugador
{
public:        // Métodos públicos.
    Jugador(); // Constructor.

    // Destructor virtual.
    // Es importante porque esta clase será heredada por otras.
    // Cuando se elimine un Jugador mediante un puntero,
    // también se ejecutará correctamente el destructor de la clase hija.
    virtual ~Jugador() = default;

    // Reparte 5 elementos aleatorios al jugador.
    void repartirElementos();

    // Devuelve el vector de elementos.
    // Se devuelve por referencia constante para evitar copiar el vector
    // y para impedir que sea modificado desde afuera.
    const vector<Elemento> &getElementos() const;

    // Devuelve true si al menos un elemento sigue vivo.
    bool tieneElementosVivos() const;

    // Método virtual puro.
    // Cada clase hija deberá decidir cómo seleccionar un elemento.
    virtual Elemento &seleccionarElemento() = 0;

    // También es un método virtual puro.
    // Cada clase hija decidirá cuál es el mejor elemento
    // para enfrentar al enemigo.
    virtual Elemento &seleccionarContra(const Elemento &enemigo) = 0;

protected: // Solo esta clase y sus hijas pueden acceder.
    // Vector que almacena los elementos del jugador.
    vector<Elemento> elementos;
};

#endif