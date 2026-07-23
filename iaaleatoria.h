#ifndef IAALEATORIA_H // Evita que el archivo se incluya más de una vez.
#define IAALEATORIA_H

#include "contrincanteia.h" // Hereda de la clase ContrincanteIA.

// Esta clase representa una IA que elige sus elementos al azar.
class IAAleatoria : public ContrincanteIA
{
public:
    IAAleatoria(); // Constructor.

    // Implementa el método heredado.
    // Selecciona un elemento para atacar.
    Elemento &seleccionarElemento() override;

    // Implementa el método heredado.
    // En esta IA el enemigo no influye en la decisión.
    Elemento &seleccionarContra(const Elemento &enemigo) override;
};

#endif // IAALEATORIA_H
