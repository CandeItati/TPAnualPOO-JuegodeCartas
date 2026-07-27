#ifndef JUGADORHUMANO_H // Evita que el archivo se incluya más de una vez.
#define JUGADORHUMANO_H

#include "jugador.h" // Incluye la clase base Jugador.

// La clase JugadorHumano hereda públicamente de Jugador.
// Esto significa que obtiene todos los atributos y métodos públicos y protegidos.
class JugadorHumano : public Jugador
{
public:              // Métodos públicos.
    JugadorHumano(); // Constructor.

    // Implementa el método virtual heredado de Jugador.
    // Devuelve el elemento actualmente seleccionado por el usuario.
    Elemento &seleccionarElemento() override;

    // También implementa el segundo método virtual.
    // En este caso simplemente devuelve el elemento seleccionado, sin analizar al enemigo.
    Elemento &seleccionarContra(const Elemento &enemigo) override;

    // Permite cambiar cuál elemento está seleccionado.
    // El índice normalmente será un número entre 0 y 4.
    void seleccionarPorIndice(int indice);

protected: // Visible para esta clase y futuras clases hijas.
    // Guarda la posición del elemento actualmente seleccionado.
    // Se inicializa en 0, por lo que al comenzar estará seleccionado el primer elemento del vector.
    int elementoSeleccionado = 0;
};

#endif