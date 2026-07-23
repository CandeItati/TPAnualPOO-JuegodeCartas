#ifndef ELEMENTO_H // Si ELEMENTO_H todavía no fue definido...
#define ELEMENTO_H // ...lo definimos para evitar incluir este archivo dos veces.

#include <QString> // Permite usar la clase QString de Qt.
#include "enums.h" // Incluye el enum TipoElemento.

class Elemento // Declaración de la clase Elemento.
{
public:         // Todo lo que esté aquí podrá usarse desde otras clases.
    Elemento(); // Constructor por defecto.

    // Constructor que recibe el nombre, el tipo de ataque y el tipo de defensa.
    Elemento(QString nombre, TipoElemento Ataque, TipoElemento Defensa);

    /// Metodos:

    QString obtenerNombre() const;       // Devuelve el nombre.
    TipoElemento obtenerAtaque() const;  // Devuelve el tipo de ataque.
    TipoElemento obtenerDefensa() const; // Devuelve el tipo de defensa.
    int obtenerVida() const;             // Devuelve la vida actual del elemento.
    void recibirDanio(int danio);        // Resta vida según el daño recibido.
    bool estaVivo() const;               // Devuelve true si la vida es mayor que 0.
    bool esMixto() const;                // Devuelve true si ataque y defensa son distintos.

private: // Solo la propia clase puede acceder a estos atributos.
    /// Atributos

    QString nombre;           // Nombre del elemento.
    int vida;                 // Vida actual.
    TipoElemento tipoAtaque;  // Tipo elemental con el que ataca.
    TipoElemento tipoDefensa; // Tipo elemental con el que se defiende.
};

#endif // ELEMENTO_H