#include "contrincanteia.h"      // Incluye la definición de la clase.

// ==========================
// Constructor
// ==========================
ContrincanteIA::ContrincanteIA()
{
    // No realiza ninguna acción.
}

// ==========================
// Selecciona un elemento.
// ==========================
Elemento &ContrincanteIA::seleccionarElemento()
{
    // Devuelve siempre el primer elemento del vector.
    return elementos[0];
}

// ==========================
// Selecciona un elemento para combatir.
// ==========================
Elemento &ContrincanteIA::seleccionarContra(const Elemento &enemigo)
{
    // El enemigo no se utiliza.
    Q_UNUSED(enemigo);

    // Devuelve siempre el primer elemento.
    return elementos[0];
}