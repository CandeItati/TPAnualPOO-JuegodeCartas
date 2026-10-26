#include "jugadorhumano.h" // Incluye la definición de la clase.

// ==========================
// Constructor
// ==========================
JugadorHumano::JugadorHumano()
{
    // No hace nada.
    // elementoSeleccionado ya vale 0 porque fue inicializado directamente en el archivo .h.
}

// ==========================
// Devuelve el elemento seleccionado.
// ==========================
Elemento &JugadorHumano::seleccionarElemento()
{
    // Devuelve una referencia al elemento cuya posición está almacenada en elementoSeleccionado.
    return elementos[elementoSeleccionado];
}

// ==========================
// Selecciona un elemento para enfrentar al enemigo.
// ==========================
Elemento &JugadorHumano::seleccionarContra(const Elemento &enemigo)
{
    (void)enemigo;

    return seleccionarElemento();
}

// ==========================
// Cambia el elemento seleccionado.
// ==========================
void JugadorHumano::seleccionarPorIndice(int indice)
{
    // Guarda la posición elegida por el usuario.
    elementoSeleccionado = indice;
}