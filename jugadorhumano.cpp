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
    // Esta macro de Qt indica que el parámetro no será utilizado.
    // Evita que el compilador muestre una advertencia.
    Q_UNUSED(enemigo);

    // El jugador humano simplemente usa el elemento que el usuario haya seleccionado previamente.
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