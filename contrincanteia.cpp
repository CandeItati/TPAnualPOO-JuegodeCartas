#include "contrincanteia.h" // Incluye la definición de la clase.

// ==========================
// Constructor
// ==========================
ContrincanteIA::ContrincanteIA()
{
    // No realiza ninguna acción.
}

void ContrincanteIA::setConfiguracion(
    Configuracion* config)
{
    configuracion = config;
}

bool ContrincanteIA::recalcularAnteCambio() const
{
    return false;
}