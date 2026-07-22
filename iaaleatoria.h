#ifndef IAALEATORIA_H
#define IAALEATORIA_H

#include "contrincanteia.h"

class IAAleatoria : public ContrincanteIA
{
public:
    IAAleatoria();

    Elemento& seleccionarElemento() override;
    Elemento& seleccionarContra(const Elemento &enemigo) override;
};

#endif // IAALEATORIA_H
