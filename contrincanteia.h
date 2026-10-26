#ifndef CONTRINCANTEIA_H // Evita que el archivo se incluya más de una vez.
#define CONTRINCANTEIA_H

#include "jugador.h"        // Hereda de la clase Jugador.
#include "configuracion.h"

// La clase ContrincanteIA representa cualquier jugador controlado por inteligencia artificial.
class ContrincanteIA : public Jugador
{
public:
    ContrincanteIA(); // Constructor.

    // Cada tipo de IA decidirá cómo seleccionar su elemento.
    // El '= 0' indica que esta clase NO implementa el método.
    virtual Elemento &seleccionarElemento() override = 0;

    // Cada IA decidirá cuál es el mejor elemento para enfrentar al enemigo.
    virtual Elemento &seleccionarContra(const Elemento &enemigo) override = 0;

    void setConfiguracion(Configuracion* config);

    virtual bool recalcularAnteCambio() const;

protected:
    Configuracion* configuracion = nullptr;
};

#endif